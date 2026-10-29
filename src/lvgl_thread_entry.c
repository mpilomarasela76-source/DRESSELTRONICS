#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "lvgl_thread.h"
#include "hal_data.h"
#include "common_data.h"
#include "r_lcdc.h"
#include "r_mipi_dsi_b.h"
#include "r_mmu.h"
#include "lvgl.h"

/* Set to 1 to show both your Dresselhaus Logo AND DRESSELTRONIC text on startup */
#define USE_DRESSELHAUS_IMAGE  1

#if USE_DRESSELHAUS_IMAGE
LV_IMAGE_DECLARE(dresselhaus_logo);
#endif

/* Set to 1 if your IPS panel requires Inversion ON (0x21) instead of OFF (0x20) */
#define ILI9881C_INVERT_COLORS 1

/* EK-RZ/A3M Onboard Pins */
#define PIN_DISP_RST_BLUE_LED  BSP_IO_PORT_10_PIN_01  /* J32-24: DISP_RST# & LED1 Blue (Keep HIGH) */
#define PIN_DISP_BACKLIGHT     BSP_IO_PORT_10_PIN_02  /* J32-21: MIPI Backlight (Keep HIGH) */
#define PIN_LED_GREEN          BSP_IO_PORT_20_PIN_03  /* LED2 (Green) */
#define PIN_LED_RED            BSP_IO_PORT_20_PIN_04  /* LED3 (Red) */

/* Uncached DMA buffer for MIPI DSI commands */
static uint8_t g_dsi_cmd_buf[16] BSP_PLACE_IN_SECTION("UNCACHED_BSS") BSP_ALIGN_VARIABLE(8);

/* Global State */
static volatile uint8_t  g_hours          = 12;
static volatile uint8_t  g_minutes        = 30;
static volatile uint8_t  g_seconds        = 0;
static volatile bool     g_clock_paused   = false;
static volatile bool     g_touch_irq_flag = false;
static volatile bool     g_i2c_done_flag  = false;
static volatile bool     g_dsi_tx_done    = false;

#define UART_RX_BUF_SIZE  128
static char              g_uart_rx_line[UART_RX_BUF_SIZE];
static volatile uint32_t g_uart_rx_idx    = 0;
static volatile bool     g_uart_msg_rdy   = false;
static volatile bool     g_uart_tx_done   = false;
static char              g_latest_ra6m5_msg[UART_RX_BUF_SIZE] = "DRESSELTRONIC MVP Ready - Touch to set time";

static lv_obj_t * g_splash_scr     = NULL;
static lv_obj_t * g_main_scr       = NULL;
static lv_obj_t * g_lbl_time       = NULL;
static lv_obj_t * g_lbl_status     = NULL;
static lv_obj_t * g_lbl_pause_btn  = NULL;
static lv_obj_t * g_arc_seconds    = NULL;

/* ==========================================================================
 * ILI9881C MIPI DSI Panel Initialization (720x1280 4-Lane MIPI Panel)
 * ========================================================================== */
typedef struct
{
    uint8_t cmd;
    uint8_t data;
} ili9881c_reg_t;

static void ili9881c_dsi_write(const uint8_t * buf, uint16_t len, mipi_dsi_cmd_id_t cmd_id)
{
    memset(g_dsi_cmd_buf, 0, sizeof(g_dsi_cmd_buf));
    for (uint16_t i = 0; i < len && i < sizeof(g_dsi_cmd_buf); i++)
    {
        g_dsi_cmd_buf[i] = buf[i];
    }

    R_BSP_CACHE_CleanRange((uint64_t) g_dsi_cmd_buf, sizeof(g_dsi_cmd_buf));

    mipi_dsi_cmd_t dsi_cmd =
    {
        .channel     = 0,
        .cmd_id      = (mipi_cmd_id_t) cmd_id,
        .flags       = MIPI_DSI_CMD_FLAG_LOW_POWER,
        .tx_len      = len,
        .p_tx_buffer = g_dsi_cmd_buf,
    };

    g_dsi_tx_done = false;
    if (FSP_SUCCESS == R_MIPI_DSI_B_Command(&g_mipi_dsi0_ctrl, &dsi_cmd))
    {
        uint32_t timeout = 100000U;
        while (!g_dsi_tx_done && --timeout)
        {
            R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
        }

        timeout = 100000U;
        while (R_MIPI_DSI->LINKSR_b.SQCHRUN0 && --timeout)
        {
            R_BSP_SoftwareDelay(1, BSP_DELAY_UNITS_MICROSECONDS);
        }

        R_BSP_SoftwareDelay(50, BSP_DELAY_UNITS_MICROSECONDS);
    }
}

static void ili9881c_switch_page(uint8_t page)
{
    uint8_t seq[4] = { 0xFF, 0x98, 0x81, page };
    ili9881c_dsi_write(seq, 4, MIPI_DSI_CMD_ID_DCS_LONG_WRITE);
}

static void ili9881c_write_reg(uint8_t reg, uint8_t val)
{
    uint8_t seq[2] = { reg, val };
    ili9881c_dsi_write(seq, 2, MIPI_DSI_CMD_ID_DCS_SHORT_WRITE_1_PARAM);
}

static void ili9881c_write_cmd_0param(uint8_t cmd)
{
    uint8_t seq[2] = { cmd, 0x00 };
    ili9881c_dsi_write(seq, 1, MIPI_DSI_CMD_ID_DCS_SHORT_WRITE_0_PARAM);
}

static const ili9881c_reg_t g_ili9881c_page3[] =
{
    {0x01, 0x00}, {0x02, 0x00}, {0x03, 0x73}, {0x04, 0x03}, {0x05, 0x00}, {0x06, 0x06}, {0x07, 0x06}, {0x08, 0x00},
    {0x09, 0x18}, {0x0A, 0x04}, {0x0B, 0x00}, {0x0C, 0x02}, {0x0D, 0x03}, {0x0E, 0x00}, {0x0F, 0x25}, {0x10, 0x25},
    {0x11, 0x00}, {0x12, 0x00}, {0x13, 0x00}, {0x14, 0x00}, {0x15, 0x00}, {0x16, 0x0C}, {0x17, 0x00}, {0x18, 0x00},
    {0x19, 0x00}, {0x1A, 0x00}, {0x1B, 0x00}, {0x1C, 0x00}, {0x1D, 0x00}, {0x1E, 0xC0}, {0x1F, 0x80}, {0x20, 0x04},
    {0x21, 0x01}, {0x22, 0x00}, {0x23, 0x00}, {0x24, 0x00}, {0x25, 0x00}, {0x26, 0x00}, {0x27, 0x00}, {0x28, 0x33},
    {0x29, 0x03}, {0x2A, 0x00}, {0x2B, 0x00}, {0x2C, 0x00}, {0x2D, 0x00}, {0x2E, 0x00}, {0x2F, 0x00}, {0x30, 0x00},
    {0x31, 0x00}, {0x32, 0x00}, {0x33, 0x00}, {0x34, 0x04}, {0x35, 0x00}, {0x36, 0x00}, {0x37, 0x00}, {0x38, 0x3C},
    {0x39, 0x00}, {0x3A, 0x00}, {0x3B, 0x00}, {0x3C, 0x00}, {0x3D, 0x00}, {0x3E, 0x00}, {0x3F, 0x00}, {0x40, 0x00},
    {0x41, 0x00}, {0x42, 0x00}, {0x43, 0x00}, {0x44, 0x00},
    {0x50, 0x01}, {0x51, 0x23}, {0x52, 0x45}, {0x53, 0x67}, {0x54, 0x89}, {0x55, 0xAB}, {0x56, 0x01}, {0x57, 0x23},
    {0x58, 0x45}, {0x59, 0x67}, {0x5A, 0x89}, {0x5B, 0xAB}, {0x5C, 0xCD}, {0x5D, 0xEF},
    {0x5E, 0x11}, {0x5F, 0x02}, {0x60, 0x02}, {0x61, 0x02}, {0x62, 0x02}, {0x63, 0x02}, {0x64, 0x02}, {0x65, 0x02},
    {0x66, 0x02}, {0x67, 0x02}, {0x68, 0x02}, {0x69, 0x02}, {0x6A, 0x0C}, {0x6B, 0x02}, {0x6C, 0x0F}, {0x6D, 0x0E},
    {0x6E, 0x0D}, {0x6F, 0x06}, {0x70, 0x07}, {0x71, 0x02}, {0x72, 0x02}, {0x73, 0x02}, {0x74, 0x02}, {0x75, 0x02},
    {0x76, 0x02}, {0x77, 0x02}, {0x78, 0x02}, {0x79, 0x02}, {0x7A, 0x02}, {0x7B, 0x02}, {0x7C, 0x02}, {0x7D, 0x02},
    {0x7E, 0x02}, {0x7F, 0x02}, {0x80, 0x0C}, {0x81, 0x02}, {0x82, 0x0F}, {0x83, 0x0E}, {0x84, 0x0D}, {0x85, 0x06},
    {0x86, 0x07}, {0x87, 0x02}, {0x88, 0x02}, {0x89, 0x02}, {0x8A, 0x02}
};

static const ili9881c_reg_t g_ili9881c_page4[] =
{
    {0x6C, 0x15}, {0x6E, 0x22}, {0x6F, 0x33}, {0x3A, 0xA4}, {0x8D, 0x0D}, {0x87, 0xBA}, {0x26, 0x76}, {0xB2, 0xD1}
};

static const ili9881c_reg_t g_ili9881c_page1[] =
{
    {0x22, 0x0A}, {0x53, 0xDC}, {0x55, 0xA7}, {0x50, 0x78}, {0x51, 0x78}, {0x31, 0x02}, {0x60, 0x14},
    {0xA0, 0x2A}, {0xA1, 0x39}, {0xA2, 0x46}, {0xA3, 0x0E}, {0xA4, 0x12}, {0xA5, 0x25}, {0xA6, 0x19}, {0xA7, 0x1D},
    {0xA8, 0xA6}, {0xA9, 0x1C}, {0xAA, 0x29}, {0xAB, 0x85}, {0xAC, 0x1C}, {0xAD, 0x1B}, {0xAE, 0x51}, {0xAF, 0x22},
    {0xB0, 0x2D}, {0xB1, 0x4F}, {0xB2, 0x59}, {0xB3, 0x3F},
    {0xC0, 0x2A}, {0xC1, 0x3A}, {0xC2, 0x45}, {0xC3, 0x0E}, {0xC4, 0x11}, {0xC5, 0x24}, {0xC6, 0x1A}, {0xC7, 0x1C},
    {0xC8, 0xAA}, {0xC9, 0x1C}, {0xCA, 0x29}, {0xCB, 0x96}, {0xCC, 0x1C}, {0xCD, 0x1B}, {0xCE, 0x51}, {0xCF, 0x22},
    {0xD0, 0x2B}, {0xD1, 0x4B}, {0xD2, 0x59}, {0xD3, 0x3F}
};

static void mipi_panel_ili9881c_init(void)
{
    /* Page 3: GIP Timing */
    ili9881c_switch_page(3);
    for (size_t i = 0; i < sizeof(g_ili9881c_page3) / sizeof(g_ili9881c_page3[0]); i++)
    {
        ili9881c_write_reg(g_ili9881c_page3[i].cmd, g_ili9881c_page3[i].data);
    }

    /* Page 4: Power & Charge Pump */
    ili9881c_switch_page(4);
    for (size_t i = 0; i < sizeof(g_ili9881c_page4) / sizeof(g_ili9881c_page4[0]); i++)
    {
        ili9881c_write_reg(g_ili9881c_page4[i].cmd, g_ili9881c_page4[i].data);
    }

    /* Page 1: VCOM, VGH/VGL & Positive/Negative Gamma Curves */
    ili9881c_switch_page(1);
    for (size_t i = 0; i < sizeof(g_ili9881c_page1) / sizeof(g_ili9881c_page1[0]); i++)
    {
        ili9881c_write_reg(g_ili9881c_page1[i].cmd, g_ili9881c_page1[i].data);
    }

    /* Switch back to Page 0 (Standard MIPI DCS Commands) */
    ili9881c_switch_page(0);

    /* Explicitly configure 24-bit RGB888 Pixel Format (COLMOD 0x3A = 0x77) */
    ili9881c_write_reg(0x3A, 0x77);

#if ILI9881C_INVERT_COLORS
    /* Enter Invert Mode (0x21) */
    ili9881c_write_cmd_0param(0x21);
#else
    /* Exit Invert Mode (0x20) */
    ili9881c_write_cmd_0param(0x20);
#endif

    /* Tearing Effect Line ON (0x35 = 0x00) */
    ili9881c_write_reg(0x35, 0x00);

    /* Exit Sleep Mode (0x11) and wait 120ms for VGH/VGL/VCOM charge pumps */
    ili9881c_write_cmd_0param(0x11);
    R_BSP_SoftwareDelay(120, BSP_DELAY_UNITS_MILLISECONDS);

    /* Turn Display ON (0x29) */
    ili9881c_write_cmd_0param(0x29);
    R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MILLISECONDS);
}

/* ==========================================================================
 * Hardware Callbacks
 * ========================================================================== */
void mipi_dsi0_callback(mipi_dsi_callback_args_t * p_args)
{
    if (NULL == p_args) return;

    switch (p_args->event)
    {
        case MIPI_DSI_EVENT_SEQUENCE_0:
            if (p_args->tx_status & MIPI_DSI_SEQUENCE_STATUS_DESCRIPTORS_FINISHED)
            {
                g_dsi_tx_done = true;
            }
            break;

        case MIPI_DSI_EVENT_POST_OPEN:
            mipi_panel_ili9881c_init();
            break;

        default:
            break;
    }
}

void g_i2c_master1_cb(i2c_master_callback_args_t * p_args)
{
    if (NULL != p_args)
    {
        g_i2c_done_flag = true;
    }
}

void touch_irq_callback(external_irq_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    g_touch_irq_flag = true;
}

void ra6m5_uart_callback(uart_callback_args_t * p_args)
{
    if (NULL == p_args) return;

    if (UART_EVENT_RX_CHAR == p_args->event)
    {
        char c = (char) p_args->data;
        if (c == '\n' || c == '\r')
        {
            if (g_uart_rx_idx > 0)
            {
                g_uart_rx_line[g_uart_rx_idx] = '\0';
                strncpy(g_latest_ra6m5_msg, g_uart_rx_line, UART_RX_BUF_SIZE - 1);
                g_uart_rx_idx  = 0;
                g_uart_msg_rdy = true;

                int hh = 0, mm = 0, ss = 0;
                if (sscanf(g_latest_ra6m5_msg, "TIME:%d:%d:%d", &hh, &mm, &ss) == 3)
                {
                    g_hours   = (uint8_t)(hh % 24);
                    g_minutes = (uint8_t)(mm % 60);
                    g_seconds = (uint8_t)(ss % 60);
                }
            }
        }
        else if (g_uart_rx_idx < (UART_RX_BUF_SIZE - 1))
        {
            g_uart_rx_line[g_uart_rx_idx++] = c;
        }
    }
    else if (UART_EVENT_TX_COMPLETE == p_args->event)
    {
        g_uart_tx_done = true;
    }
}

static void send_to_ra6m5(const char * msg)
{
    g_uart_tx_done = false;
    R_SCIF_UART_Write(&g_ra6m5_uart_ctrl, (uint8_t const *)msg, (uint32_t)strlen(msg));
}

/* ==========================================================================
 * LVGL Capacitive Touch Read Callback
 * ========================================================================== */
static bool i2c_write_read(uint8_t slave_addr, uint8_t * tx, uint32_t tx_len, uint8_t * rx, uint32_t rx_len)
{
    R_RIIC_MASTER_SlaveAddressSet(&g_i2c_master0_ctrl, slave_addr, I2C_MASTER_ADDR_MODE_7BIT);

    g_i2c_done_flag = false;
    if (FSP_SUCCESS != R_RIIC_MASTER_Write(&g_i2c_master0_ctrl, tx, tx_len, (rx_len > 0)))
    {
        return false;
    }
    uint32_t timeout = 15000U;
    while (!g_i2c_done_flag && --timeout) { ; }
    if (0U == timeout) return false;

    if (rx_len > 0)
    {
        g_i2c_done_flag = false;
        if (FSP_SUCCESS != R_RIIC_MASTER_Read(&g_i2c_master0_ctrl, rx, rx_len, false))
        {
            return false;
        }
        timeout = 15000U;
        while (!g_i2c_done_flag && --timeout) { ; }
        if (0U == timeout) return false;
    }
    return true;
}

static void lvgl_touch_read_cb(lv_indev_t * indev, lv_indev_data_t * data)
{
    FSP_PARAMETER_NOT_USED(indev);
    static int32_t last_x = 0;
    static int32_t last_y = 0;
    bool touched = false;

    const uint8_t gt911_addrs[2] = { 0x5D, 0x14 };
    for (size_t i = 0; i < 2; i++)
    {
        uint8_t reg_stat[2] = { 0x81, 0x4E };
        uint8_t stat = 0;
        if (i2c_write_read(gt911_addrs[i], reg_stat, 2, &stat, 1))
        {
            if (stat & 0x80U)
            {
                uint8_t touches = stat & 0x0FU;
                uint8_t pt_buf[4] = {0};
                uint8_t reg_pt[2] = { 0x81, 0x50 };
                if (touches > 0 && i2c_write_read(gt911_addrs[i], reg_pt, 2, pt_buf, 4))
                {
                    last_x  = (int32_t)(pt_buf[0] | (pt_buf[1] << 8));
                    last_y  = (int32_t)(pt_buf[2] | (pt_buf[3] << 8));
                    touched = true;
                }
                uint8_t clr_cmd[3] = { 0x81, 0x4E, 0x00 };
                i2c_write_read(gt911_addrs[i], clr_cmd, 3, NULL, 0);
                break;
            }
        }
    }

    if (!touched)
    {
        uint8_t reg = 0x02;
        uint8_t buf[5] = {0};
        if (i2c_write_read(0x2A, &reg, 1, buf, 5))
        {
            uint8_t touches = buf[0] & 0x0FU;
            if (touches > 0 && touches <= 5)
            {
                last_x  = (int32_t)(((buf[1] & 0x0F) << 8) | buf[2]);
                last_y  = (int32_t)(((buf[3] & 0x0F) << 8) | buf[4]);
                touched = true;
            }
        }
    }

    R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_LED_RED, touched ? BSP_IO_LEVEL_HIGH : BSP_IO_LEVEL_LOW);

    data->point.x = last_x;
    data->point.y = last_y;
    data->state   = touched ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
}

/* ==========================================================================
 * Interactive UI Callbacks
 * ========================================================================== */
static void refresh_clock_labels(void)
{
    if (NULL != g_lbl_time)
    {
        lv_label_set_text_fmt(g_lbl_time, "%02u:%02u:%02u", g_hours, g_minutes, g_seconds);
    }
    if (NULL != g_arc_seconds)
    {
        lv_arc_set_value(g_arc_seconds, g_seconds);
    }
}

static void arc_seconds_scrub_cb(lv_event_t * e)
{
    if (LV_EVENT_VALUE_CHANGED == lv_event_get_code(e))
    {
        g_seconds = (uint8_t)(lv_arc_get_value(g_arc_seconds) % 60);
        if (NULL != g_lbl_time)
        {
            lv_label_set_text_fmt(g_lbl_time, "%02u:%02u:%02u", g_hours, g_minutes, g_seconds);
        }
    }
}

static void btn_add_hour_cb(lv_event_t * e)
{
    if (LV_EVENT_CLICKED == lv_event_get_code(e))
    {
        g_hours = (uint8_t)((g_hours + 1U) % 24U);
        refresh_clock_labels();
    }
}

static void btn_sub_hour_cb(lv_event_t * e)
{
    if (LV_EVENT_CLICKED == lv_event_get_code(e))
    {
        g_hours = (uint8_t)((g_hours + 23U) % 24U);
        refresh_clock_labels();
    }
}

static void btn_add_min_cb(lv_event_t * e)
{
    if (LV_EVENT_CLICKED == lv_event_get_code(e))
    {
        g_minutes = (uint8_t)((g_minutes + 1U) % 60U);
        refresh_clock_labels();
    }
}

static void btn_sub_min_cb(lv_event_t * e)
{
    if (LV_EVENT_CLICKED == lv_event_get_code(e))
    {
        g_minutes = (uint8_t)((g_minutes + 59U) % 60U);
        refresh_clock_labels();
    }
}

static void btn_reset_sec_cb(lv_event_t * e)
{
    if (LV_EVENT_CLICKED == lv_event_get_code(e))
    {
        g_seconds = 0U;
        refresh_clock_labels();
    }
}

static void btn_pause_toggle_cb(lv_event_t * e)
{
    if (LV_EVENT_CLICKED == lv_event_get_code(e))
    {
        g_clock_paused = !g_clock_paused;
        if (NULL != g_lbl_pause_btn)
        {
            lv_label_set_text(g_lbl_pause_btn, g_clock_paused ? "RESUME" : "PAUSE");
        }
        if (NULL != g_lbl_status)
        {
            lv_label_set_text(g_lbl_status, g_clock_paused ?
                "Clock Paused - Set Hours/Minutes/Seconds freely!" :
                "Clock Running - Touch buttons or ring to adjust time");
        }
    }
}

static void btn_sync_ra6m5_cb(lv_event_t * e)
{
    if (LV_EVENT_CLICKED == lv_event_get_code(e))
    {
        char tx_buf[64];
        snprintf(tx_buf, sizeof(tx_buf), "SYNC:%02u:%02u:%02u\r\n", g_hours, g_minutes, g_seconds);
        send_to_ra6m5(tx_buf);
        if (NULL != g_lbl_status)
        {
            lv_label_set_text_fmt(g_lbl_status, "UART TX -> SYNC:%02u:%02u:%02u", g_hours, g_minutes, g_seconds);
        }
    }
}

/* ==========================================================================
 * 1-Second LVGL Timer
 * ========================================================================== */
static void clock_update_timer_cb(lv_timer_t * timer)
{
    FSP_PARAMETER_NOT_USED(timer);

    if (!g_clock_paused)
    {
        g_seconds++;
        if (g_seconds >= 60U)
        {
            g_seconds = 0U;
            g_minutes++;
            if (g_minutes >= 60U)
            {
                g_minutes = 0U;
                g_hours = (uint8_t)((g_hours + 1U) % 24U);
            }
        }
        refresh_clock_labels();
    }

    if (g_uart_msg_rdy && (NULL != g_lbl_status))
    {
        g_uart_msg_rdy = false;
        lv_label_set_text_fmt(g_lbl_status, "RA6M5 RX: %s", g_latest_ra6m5_msg);
        refresh_clock_labels();
    }
}

/* ==========================================================================
 * Build the Main Interactive Clock Screen (DRESSELTRONIC MVP)
 * ========================================================================== */
static void build_main_clock_screen(void)
{
    g_main_scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(g_main_scr, lv_color_hex(0x0F172A), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(g_main_scr, LV_OPA_COVER, LV_PART_MAIN);

    /* Large DRESSELTRONIC Brand Header */
    lv_obj_t * brand = lv_label_create(g_main_scr);
    lv_label_set_text(brand, "DRESSELTRONIC");
    lv_obj_set_style_text_font(brand, &lv_font_montserrat_40, 0);
    lv_obj_set_style_text_color(brand, lv_color_hex(0x38BDF8), 0);
    lv_obj_align(brand, LV_ALIGN_TOP_MID, 0, 25);

    lv_obj_t * sub = lv_label_create(g_main_scr);
    lv_label_set_text(sub, "Dresselhaus - Jagdperfektion seit 1930");
    lv_obj_set_style_text_font(sub, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(sub, lv_color_hex(0xE2E8F0), 0);
    lv_obj_align(sub, LV_ALIGN_TOP_MID, 0, 75);

    g_arc_seconds = lv_arc_create(g_main_scr);
    lv_obj_set_size(g_arc_seconds, 320, 320);
    lv_arc_set_rotation(g_arc_seconds, 270);
    lv_arc_set_bg_angles(g_arc_seconds, 0, 360);
    lv_arc_set_range(g_arc_seconds, 0, 59);
    lv_arc_set_value(g_arc_seconds, g_seconds);
    lv_obj_align(g_arc_seconds, LV_ALIGN_CENTER, 0, -70);
    lv_obj_add_event_cb(g_arc_seconds, arc_seconds_scrub_cb, LV_EVENT_VALUE_CHANGED, NULL);

    g_lbl_time = lv_label_create(g_main_scr);
    lv_obj_set_style_text_font(g_lbl_time, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(g_lbl_time, lv_color_hex(0xFFFFFF), 0);
    lv_label_set_text_fmt(g_lbl_time, "%02u:%02u:%02u", g_hours, g_minutes, g_seconds);
    lv_obj_align_to(g_lbl_time, g_arc_seconds, LV_ALIGN_CENTER, 0, 0);

    /* Controls: Row 1 */
    lv_obj_t * btn_sub_hr = lv_button_create(g_main_scr);
    lv_obj_set_size(btn_sub_hr, 140, 55);
    lv_obj_align(btn_sub_hr, LV_ALIGN_CENTER, -230, 140);
    lv_obj_add_event_cb(btn_sub_hr, btn_sub_hour_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t * l1 = lv_label_create(btn_sub_hr);
    lv_label_set_text(l1, "-1 Hour");
    lv_obj_center(l1);

    lv_obj_t * btn_add_hr = lv_button_create(g_main_scr);
    lv_obj_set_size(btn_add_hr, 140, 55);
    lv_obj_align(btn_add_hr, LV_ALIGN_CENTER, -75, 140);
    lv_obj_add_event_cb(btn_add_hr, btn_add_hour_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t * l2 = lv_label_create(btn_add_hr);
    lv_label_set_text(l2, "+1 Hour");
    lv_obj_center(l2);

    lv_obj_t * btn_sub_mn = lv_button_create(g_main_scr);
    lv_obj_set_size(btn_sub_mn, 140, 55);
    lv_obj_align(btn_sub_mn, LV_ALIGN_CENTER, 75, 140);
    lv_obj_add_event_cb(btn_sub_mn, btn_sub_min_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t * l3 = lv_label_create(btn_sub_mn);
    lv_label_set_text(l3, "-1 Min");
    lv_obj_center(l3);

    lv_obj_t * btn_add_mn = lv_button_create(g_main_scr);
    lv_obj_set_size(btn_add_mn, 140, 55);
    lv_obj_align(btn_add_mn, LV_ALIGN_CENTER, 230, 140);
    lv_obj_add_event_cb(btn_add_mn, btn_add_min_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t * l4 = lv_label_create(btn_add_mn);
    lv_label_set_text(l4, "+1 Min");
    lv_obj_center(l4);

    /* Controls: Row 2 */
    lv_obj_t * btn_rst = lv_button_create(g_main_scr);
    lv_obj_set_size(btn_rst, 180, 55);
    lv_obj_align(btn_rst, LV_ALIGN_CENTER, -200, 210);
    lv_obj_add_event_cb(btn_rst, btn_reset_sec_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t * l5 = lv_label_create(btn_rst);
    lv_label_set_text(l5, "Zero Sec (:00)");
    lv_obj_center(l5);

    lv_obj_t * btn_pause = lv_button_create(g_main_scr);
    lv_obj_set_size(btn_pause, 180, 55);
    lv_obj_set_style_bg_color(btn_pause, lv_color_hex(0xF59E0B), 0);
    lv_obj_align(btn_pause, LV_ALIGN_CENTER, 0, 210);
    lv_obj_add_event_cb(btn_pause, btn_pause_toggle_cb, LV_EVENT_CLICKED, NULL);
    g_lbl_pause_btn = lv_label_create(btn_pause);
    lv_label_set_text(g_lbl_pause_btn, "PAUSE");
    lv_obj_center(g_lbl_pause_btn);

    lv_obj_t * btn_sync = lv_button_create(g_main_scr);
    lv_obj_set_size(btn_sync, 180, 55);
    lv_obj_set_style_bg_color(btn_sync, lv_color_hex(0x10B981), 0);
    lv_obj_align(btn_sync, LV_ALIGN_CENTER, 200, 210);
    lv_obj_add_event_cb(btn_sync, btn_sync_ra6m5_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t * l6 = lv_label_create(btn_sync);
    lv_label_set_text(l6, "Send to RA6M5");
    lv_obj_center(l6);

    /* Status Bar */
    lv_obj_t * panel_status = lv_obj_create(g_main_scr);
    lv_obj_set_size(panel_status, 620, 60);
    lv_obj_set_style_bg_color(panel_status, lv_color_hex(0x1E293B), 0);
    lv_obj_align(panel_status, LV_ALIGN_CENTER, 0, 290);

    g_lbl_status = lv_label_create(panel_status);
    lv_obj_set_style_text_font(g_lbl_status, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(g_lbl_status, lv_color_hex(0xFFFFFF), 0);
    lv_label_set_text(g_lbl_status, g_latest_ra6m5_msg);
    lv_obj_center(g_lbl_status);

    lv_timer_create(clock_update_timer_cb, 1000, NULL);
}

static void splash_done_timer_cb(lv_timer_t * timer)
{
    lv_timer_delete(timer);
    lv_screen_load_anim(g_main_scr, LV_SCR_LOAD_ANIM_FADE_IN, 600, 0, true);
}

static void show_startup_splash(void)
{
    g_splash_scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(g_splash_scr, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(g_splash_scr, LV_OPA_COVER, LV_PART_MAIN);

#if USE_DRESSELHAUS_IMAGE
    lv_obj_t * img = lv_image_create(g_splash_scr);
    lv_image_set_src(img, &dresselhaus_logo);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, -60);
#endif

    lv_obj_t * t1 = lv_label_create(g_splash_scr);
    lv_obj_set_style_text_font(t1, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(t1, lv_color_hex(0x0F172A), 0);
    lv_label_set_text(t1, "DRESSELTRONIC");
    lv_obj_align(t1, LV_ALIGN_CENTER, 0, 160);

    lv_obj_t * t2 = lv_label_create(g_splash_scr);
    lv_obj_set_style_text_font(t2, &lv_font_montserrat_28, 0);
    lv_obj_set_style_text_color(t2, lv_color_hex(0x475569), 0);
    lv_label_set_text(t2, "Jagdperfektion seit 1930");
    lv_obj_align(t2, LV_ALIGN_CENTER, 0, 220);

    lv_screen_load(g_splash_scr);
    lv_timer_create(splash_done_timer_cb, 4000, NULL);
}

/* ==========================================================================
 * Main Thread Entry:
 *  1) Hardware resets the MIPI display & enables backlight
 *  2) Pre-fills both hardware framebuffers with Pure Solid Blue (0x001F)
 *  3) Opens RM_LVGL_PORT_Open (initializes LCDC + MIPI DSI + ILI9881C Panel)
 *  4) Holds Solid Blue for 3 seconds while blinking Red <-> Green LEDs
 *  5) Launches Dresselhaus + DRESSELTRONIC Splash & Interactive Clock
 * ========================================================================== */
void lvgl_thread_entry(void * pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    /* 1. Pulse DISP_RST# (P10_1) LOW -> HIGH & Turn Backlight ON (P10_2 HIGH) */
    R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_DISP_RST_BLUE_LED, BSP_IO_LEVEL_LOW);
    R_BSP_SoftwareDelay(20, BSP_DELAY_UNITS_MILLISECONDS);
    R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_DISP_RST_BLUE_LED, BSP_IO_LEVEL_HIGH);
    R_BSP_SoftwareDelay(120, BSP_DELAY_UNITS_MILLISECONDS);

    R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_DISP_BACKLIGHT, BSP_IO_LEVEL_HIGH);
    R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_LED_GREEN,      BSP_IO_LEVEL_LOW);
    R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_LED_RED,        BSP_IO_LEVEL_LOW);

    /* 2. Open MMU & Initialize LVGL Core */
    R_MMU_Open(&g_mmu_ctrl, &g_mmu_cfg);
    lv_init();

    /* 3. Pre-fill both hardware framebuffers with Pure Blue (0x001F) BEFORE starting LCDC DMA */
    uint16_t * p_fb0 = (uint16_t *) &fb_background[0][0];
    uint16_t * p_fb1 = (uint16_t *) &fb_background[1][0];
    size_t total_pixels = (sizeof(fb_background[0]) / sizeof(uint16_t));
    for (size_t i = 0; i < total_pixels; i++)
    {
        p_fb0[i] = 0x001FU;
        p_fb1[i] = 0x001FU;
    }
    R_BSP_CACHE_CleanRange((uint64_t) fb_background, sizeof(fb_background));

    /* 4. Open RM_LVGL_PORT_Open
     *    NOTE: This automatically opens g_display0 (LCDC) and g_mipi_dsi0 (MIPI DSI),
     *    fires MIPI_DSI_EVENT_POST_OPEN -> mipi_panel_ili9881c_init(), and starts video! */
    fsp_err_t err = RM_LVGL_PORT_Open(&g_lvgl_port_ctrl, &g_lvgl_port_cfg);
    if (FSP_SUCCESS != err)
    {
        R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_LED_RED, BSP_IO_LEVEL_HIGH);
        while (1)
        {
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }

    /* Mask Video Channel 1 Underflow/Overflow IRQ storm if needed */
    R_MIPI_DSI->VICH1IER = 0U;

    /* 5. Hold 3-second Pure Hardware Solid Blue Test while alternating Red <-> Green LEDs */
    for (uint32_t step = 0; step < 12U; step++)
    {
        R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_LED_GREEN, (step & 1U) ? BSP_IO_LEVEL_HIGH : BSP_IO_LEVEL_LOW);
        R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_LED_RED,   (step & 1U) ? BSP_IO_LEVEL_LOW  : BSP_IO_LEVEL_HIGH);
        vTaskDelay(pdMS_TO_TICKS(250));
    }

    /* Turn Green LED Solid ON & Red LED OFF as we enter LVGL */
    R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_LED_GREEN, BSP_IO_LEVEL_HIGH);
    R_IOPORT_PinWrite(&g_ioport_ctrl, PIN_LED_RED,   BSP_IO_LEVEL_LOW);

    /* 6. Ensure LVGL uses standard RGB565 (not byte-swapped) & Open Touch I2C / UART */
    lv_display_set_default(g_lvgl_port_ctrl.p_lv_display);
    lv_display_set_color_format(g_lvgl_port_ctrl.p_lv_display, LV_COLOR_FORMAT_RGB565);

    R_RIIC_MASTER_Open(&g_i2c_master0_ctrl, &g_i2c_master0_cfg);

    lv_indev_t * touch_indev = lv_indev_create();
    lv_indev_set_type(touch_indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(touch_indev, lvgl_touch_read_cb);

    R_SCIF_UART_Open(&g_ra6m5_uart_ctrl, &g_ra6m5_uart_cfg);

    /* 7. Build & Show DRESSELTRONIC Screens */
    build_main_clock_screen();
    show_startup_splash();

    /* 8. Main LVGL Event Loop */
    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(time_till_next > 5U ? 5U : time_till_next));
    }
}
