/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "r_mipi_phy_b.h"
#include "r_mipi_dsi_b.h"
#include "r_mipi_dsi_api.h"
#include "r_display_api.h"
#include "r_lcdc.h"
#include "r_display_api.h"
#include "lv_init.h"
#include "lv_timer.h"
#include "rm_lvgl_port.h"
#include "r_mmu.h"
#include "r_ioport.h"
#include "bsp_pin_cfg.h"
FSP_HEADER
/* MIPI PHY on MIPI PHY Instance. */
extern const mipi_phy_instance_t g_mipi_phy0;

/* Access the MIPI DSI instance using these structures when calling API functions directly (::p_api is not used). */
extern mipi_phy_b_ctrl_t g_mipi_phy0_ctrl;
extern const mipi_phy_b_cfg_t g_mipi_phy0_cfg;
/* MIPI DSI on MIPI DSI Instance. */
extern const mipi_dsi_instance_t g_mipi_dsi0;

/* Access the MIPI DSI instance using these structures when calling API functions directly (::p_api is not used). */
extern mipi_dsi_b_instance_ctrl_t g_mipi_dsi0_ctrl;
extern const mipi_dsi_cfg_t g_mipi_dsi0_cfg;

#ifndef mipi_dsi0_callback
void mipi_dsi0_callback(mipi_dsi_callback_args_t *p_args);
#endif
#define LCDC_CFG_LAYER_1_ENABLE (true)
#define LCDC_CFG_LAYER_2_ENABLE (false)

/* Display on LCDC Instance. */
extern const display_instance_t g_display0;
extern display_runtime_cfg_t g_display0_runtime_cfg_fg;
extern display_runtime_cfg_t g_display0_runtime_cfg_bg;
extern display_colorkeying_layer_t g_display0_ckey_cfg;

/** Access the LCDC instance using these structures when calling API functions directly (::p_api is not used). */
extern lcdc_instance_ctrl_t g_display0_ctrl;
extern const display_cfg_t g_display0_cfg;

void _rm_lvgl_port_display_callback(display_callback_args_t *p_args);

#define DISPLAY_IN_FORMAT_16BITS_RGB565_0
#if defined (DISPLAY_IN_FORMAT_32BITS_ARGB8888_0) || defined (DISPLAY_IN_FORMAT_32BITS_RGBA8888_0) || defined (DISPLAY_IN_FORMAT_32BITS_ABGR8888_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (32)
            #elif defined (DISPLAY_IN_FORMAT_24BITS_RGB888_0) || defined (DISPLAY_IN_FORMAT_24BITS_BGR888_0) || defined (DISPLAY_IN_FORMAT_24BITS_YCBCR444_INTERLEAVED_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (24)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_RGB565_0) || defined (DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE0_UYVY_0) || defined (DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE0_YUY2_0) || defined (DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE0_YVYU_0) || defined (DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE1_0)
#define DISPLAY_BITS_PER_PIXEL_INPUT0 (16)
#elif defined (DISPLAY_IN_FORMAT_16BITS_YCBCR420_INTERLEAVED_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (24)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR_0)
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (8)
            #else
            #define DISPLAY_BITS_PER_PIXEL_INPUT0 (1)
            #endif
#define DISPLAY_HSIZE_INPUT0                 (720)
#define DISPLAY_HSIZE_UV_INPUT0              (720 >> 1)
#define DISPLAY_VSIZE_INPUT0                 (1280)
#define DISPLAY_VSIZE_UV_INPUT0              (1280 >> 1)
#define DISPLAY_BUFFER_STRIDE_BYTES_INPUT0   ((DISPLAY_HSIZE_INPUT0 * DISPLAY_BITS_PER_PIXEL_INPUT0) >> 3)
#define DISPLAY_BUFFER_STRIDE_PIXELS_INPUT0  ((DISPLAY_BUFFER_STRIDE_BYTES_INPUT0 * 8) / DISPLAY_BITS_PER_PIXEL_INPUT0)
#define DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT0   ((DISPLAY_HSIZE_UV_INPUT0 * DISPLAY_BITS_PER_PIXEL_INPUT0) >> 3)
#define DISPLAY_INPUT0_BUFFER_NUM_2 (true)

#define DISPLAY_IN_FORMAT_32BITS_ARGB8888_1
#if defined (DISPLAY_IN_FORMAT_32BITS_ARGB8888_1) || defined (DISPLAY_IN_FORMAT_32BITS_RGBA8888_1) || defined (DISPLAY_IN_FORMAT_32BITS_ABGR8888_1)
#define DISPLAY_BITS_PER_PIXEL_INPUT1 (32)
#elif defined (DISPLAY_IN_FORMAT_24BITS_RGB888_1) || defined (DISPLAY_IN_FORMAT_24BITS_BGR888_1) || defined (DISPLAY_IN_FORMAT_24BITS_YCBCR444_INTERLEAVED_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (24)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_RGB565_1) || defined (DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE0_UYVY_1) || defined (DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE0_YUY2_1) || defined (DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE0_YVYU_1) || defined (DISPLAY_IN_FORMAT_16BITS_YCBCR422_INTERLEAVED_TYPE1_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (16)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_YCBCR420_INTERLEAVED_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (24)
            #elif defined (DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR_1)
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (8)
            #else
            #define DISPLAY_BITS_PER_PIXEL_INPUT1 (1)
            #endif
#define DISPLAY_HSIZE_INPUT1                 (1280)
#define DISPLAY_HSIZE_UV_INPUT1              (1280 >> 1)
#define DISPLAY_VSIZE_INPUT1                 (800)
#define DISPLAY_VSIZE_UV_INPUT1              (800 >> 1)
#define DISPLAY_BUFFER_STRIDE_BYTES_INPUT1   ((DISPLAY_HSIZE_INPUT1 * DISPLAY_BITS_PER_PIXEL_INPUT1) >> 3)
#define DISPLAY_BUFFER_STRIDE_PIXELS_INPUT1  ((DISPLAY_BUFFER_STRIDE_BYTES_INPUT1 * 8) / DISPLAY_BITS_PER_PIXEL_INPUT1)
#define DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT1   ((DISPLAY_HSIZE_UV_INPUT1 * DISPLAY_BITS_PER_PIXEL_INPUT1) >> 3)
#define DISPLAY_INPUT1_BUFFER_NUM_1 (true)

#if LCDC_CFG_LAYER_1_ENABLE
        #ifdef fb_background_DEFINE_CRU
        #else
        #ifdef DISPLAY_INPUT0_BUFFER_NUM_0
        /** FSP do not set buffer for layer1 */
        #else
        extern uint8_t fb_background[2][DISPLAY_BUFFER_STRIDE_BYTES_INPUT0 * DISPLAY_VSIZE_INPUT0];
        #ifdef DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR_0
        extern uint8_t fb_background_CB[2][DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT0 * DISPLAY_VSIZE_UV_INPUT0];
        extern uint8_t fb_background_CR[2][DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT0 * DISPLAY_VSIZE_UV_INPUT0];
        #endif
        #define fb_background_DEFINE_LCDC
        #endif
        #endif
        #else
/** Graphics Layer 1 is specified not to be used when starting */
#endif

#if LCDC_CFG_LAYER_2_ENABLE
        #ifdef fb_foreground_DEFINE_CRU
        #else
        #ifdef DISPLAY_INPUT1_BUFFER_NUM_0
        /** FSP do not set buffer for layer2 */
        #else
        extern uint8_t fb_foreground[1][DISPLAY_BUFFER_STRIDE_BYTES_INPUT1 * DISPLAY_VSIZE_INPUT1];
        #ifdef DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR_1
        extern uint8_t fb_foreground_CB[1][DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT1 * DISPLAY_VSIZE_UV_INPUT1];
		extern uint8_t fb_foreground_CR[1][DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT1 * DISPLAY_VSIZE_UV_INPUT1];
        #endif
        #define fb_foreground_DEFINE_LCDC
        #endif
        #endif
        #else
/** Graphics Layer 2 is specified not to be used when starting */
#endif
#if (1 == 1)
#define LVGL_DISPLAY_HSIZE_INPUT                (DISPLAY_HSIZE_INPUT0)
#define LVGL_DISPLAY_VSIZE_INPUT                (DISPLAY_VSIZE_INPUT0)
#define LVGL_DISPLAY_BUFFER_STRIDE_BYTES_INPUT  (DISPLAY_BUFFER_STRIDE_BYTES_INPUT0)
#define LVGL_DISPLAY_BUFFER_STRIDE_PIXELS_INPUT (DISPLAY_BUFFER_STRIDE_PIXELS_INPUT0)
#else
                #define LVGL_DISPLAY_HSIZE_INPUT                (DISPLAY_HSIZE_INPUT1)
                #define LVGL_DISPLAY_VSIZE_INPUT                (DISPLAY_VSIZE_INPUT1)
                #define LVGL_DISPLAY_BUFFER_STRIDE_BYTES_INPUT  (DISPLAY_BUFFER_STRIDE_BYTES_INPUT1)
                #define LVGL_DISPLAY_BUFFER_STRIDE_PIXELS_INPUT (DISPLAY_BUFFER_STRIDE_PIXELS_INPUT1)
            #endif

#define LVGL_DISPLAY_BUFFER_SIZE_DIVISOR (10)

#ifndef NULL
extern void NULL(rm_lvgl_port_callback_args_t *p_arg);
#endif

#if (RM_LVGL_PORT_CFG_PROVIDE_TICK_CALLBACK)
            /* Display callback prototype for LVGL */
            extern void _rm_lvgl_port_display_callback(display_callback_args_t * p_args);

            /* Setup timer for LVGL tick */
            #if (BSP_CFG_RTOS == 0)
            extern void _rm_lvgl_port_setup_lvgl_tick( void );
            #endif
            #endif
/* MMU Instance */
extern const mmu_instance_t g_mmu;

/* MMU control structure. */
extern mmu_instance_ctrl_t g_mmu_ctrl;
extern const mmu_cfg_t g_mmu_cfg;
#define IOPORT_CFG_NAME g_bsp_pin_cfg
#define IOPORT_CFG_OPEN R_IOPORT_Open
#define IOPORT_CFG_CTRL g_ioport_ctrl

/* IOPORT Instance */
extern const ioport_instance_t g_ioport;

/* IOPORT control structure. */
extern ioport_instance_ctrl_t g_ioport_ctrl;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */
