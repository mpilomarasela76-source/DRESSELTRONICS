/* generated HAL source file - do not edit */
#include "hal_data.h"
#define FSP_NOT_DEFINED (UINT32_MAX)
#if (FSP_NOT_DEFINED) != (FSP_NOT_DEFINED)

/* If the transfer module is DMAC, define a DMAC transfer callback. */
#include "r_dmac.h"
extern void scif_uart_tx_dmac_callback(scif_uart_instance_ctrl_t const * const p_ctrl);

void g_ra6m5_uart_tx_transfer_callback (dmac_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    scif_uart_tx_dmac_callback(&g_ra6m5_uart_ctrl);
}
#endif

#if (FSP_NOT_DEFINED) != (FSP_NOT_DEFINED)

/* If the transfer module is DMAC, define a DMAC transfer callback. */
#include "r_dmac.h"
extern void scif_uart_rx_dmac_callback(scif_uart_instance_ctrl_t const * const p_ctrl);

void g_ra6m5_uart_rx_transfer_callback (dmac_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    scif_uart_rx_dmac_callback(&g_ra6m5_uart_ctrl);
}
#endif
#undef FSP_NOT_DEFINED

scif_uart_instance_ctrl_t g_ra6m5_uart_ctrl;

scif_baud_setting_t g_ra6m5_uart_baud_setting =
        {
        /* Baud rate calculated with 0.469% error. */.semr_baudrate_bits_b.abcs = 0,
          .semr_baudrate_bits_b.bgdm = 1, .semr_baudrate_bits_b.cks = 0, .brr = 53, .mddr = (uint8_t) 256, .semr_baudrate_bits_b.brme =
                  false };

/** UART extended configuration for UARTonSCIF HAL driver */
const scif_uart_extended_cfg_t g_ra6m5_uart_cfg_extend =
{ .bri_ipl = 24, .bri_irq = SCIF4_BRK_IRQn, .clock = SCIF_UART_CLOCK_INT, .noise_cancel =
          SCIF_UART_NOISE_CANCELLATION_DISABLE,
  .p_baud_setting = &g_ra6m5_uart_baud_setting, .rx_fifo_trigger = SCIF_UART_RX_FIFO_TRIGGER_MAX, .rts_fifo_trigger =
          SCIF_UART_RTS_TRIGGER_14,
  .uart_mode = SCIF_UART_MODE_RS232, .flow_control = SCIF_UART_FLOW_CONTROL_NONE, .rs485_setting =
  { .enable = (scif_uart_rs485_enable_t) NULL, .polarity = SCIF_UART_RS485_DE_POLARITY_HIGH, .de_control_pin =
            (bsp_io_port_pin_t) SCIF_UART_INVALID_16BIT_PARAM, },
  .p_reg = R_SCIFA4, };

/** UART interface configuration */
const uart_cfg_t g_ra6m5_uart_cfg =
{ .channel = 4,
  .data_bits = UART_DATA_BITS_8,
  .parity = UART_PARITY_OFF,
  .stop_bits = UART_STOP_BITS_1,
  .p_callback = ra6m5_uart_callback,
  .p_context = NULL,
  .p_extend = &g_ra6m5_uart_cfg_extend,
  .p_transfer_tx = g_ra6m5_uart_P_TRANSFER_TX,
  .p_transfer_rx = g_ra6m5_uart_P_TRANSFER_RX,
  .rxi_ipl = 24,
  .txi_ipl = 24,
  .tei_ipl = 24,
  .eri_ipl = 24,
  .rxi_irq = SCIF4_RXI_IRQn,
  .txi_irq = SCIF4_TXI_IRQn,
  .tei_irq = SCIF4_TEI_DRI_IRQn,
  .eri_irq = SCIF4_RERR_IRQn, };

/* Instance structure to use this module. */
const uart_instance_t g_ra6m5_uart =
{ .p_ctrl = &g_ra6m5_uart_ctrl, .p_cfg = &g_ra6m5_uart_cfg, .p_api = &g_uart_on_scif };
intc_irq_instance_ctrl_t g_external_irq0_ctrl;
const external_irq_cfg_t g_external_irq0_cfg =
{ .channel = 1, .trigger = EXTERNAL_IRQ_TRIG_FALLING, .filter_enable = false, .clock_source_div =
          EXTERNAL_IRQ_CLOCK_SOURCE_DIV_1,
  .p_callback = touch_irq_callback, .p_context = NULL, .p_extend = NULL, .ipl = 24, .irq = GPIO_IRQ1_IRQn, };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irq0 =
{ .p_ctrl = &g_external_irq0_ctrl, .p_cfg = &g_external_irq0_cfg, .p_api = &g_external_irq_on_intc_irq };
#define FSP_NOT_DEFINED (UINT32_MAX)
#if (FSP_NOT_DEFINED) != (FSP_NOT_DEFINED)

/* If the transfer module is DMAC, define a DMAC transfer callback. */
#include "r_dmac.h"
extern void riic_master_tx_dmac_callback(iic_master_instance_ctrl_t * p_ctrl);

void g_i2c_master0_tx_transfer_callback (dmac_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    riic_master_tx_dmac_callback(&g_i2c_master0_ctrl);
}
#endif

#if (FSP_NOT_DEFINED) != (FSP_NOT_DEFINED)

/* If the transfer module is DMAC, define a DMAC transfer callback. */
#include "r_dmac.h"
extern void riic_master_rx_dmac_callback(iic_master_instance_ctrl_t * p_ctrl);

void g_i2c_master0_rx_transfer_callback (dmac_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    riic_master_rx_dmac_callback(&g_i2c_master0_ctrl);
}
#endif
#undef FSP_NOT_DEFINED

iic_master_instance_ctrl_t g_i2c_master0_ctrl;
const riic_master_extended_cfg_t g_i2c_master0_extend =
{ .timeout_mode = IIC_MASTER_TIMEOUT_MODE_SHORT,
  .timeout_scl_low = IIC_MASTER_TIMEOUT_SCL_LOW_ENABLED,
  /* Actual calculated bitrate: 396825. Actual calculated duty cycle: 51%. */.clock_settings.brl_value = 25,
  .clock_settings.brh_value = 26,
  .clock_settings.cks_value = 2,
  .noise_filter_stage = 1,
  .naki_irq = RIIC1_NAKI_IRQn,
  .spi_irq = RIIC1_SPI_IRQn,
  .sti_irq = RIIC1_STI_IRQn,
  .ali_irq = RIIC1_ALI_IRQn,
  .tmoi_irq = RIIC1_TMOI_IRQn,
  .p_reg = R_RIIC1, };
const i2c_master_cfg_t g_i2c_master0_cfg =
{ .channel = 1, .rate = I2C_MASTER_RATE_FAST, .slave = 0x2A, .addr_mode = I2C_MASTER_ADDR_MODE_7BIT, .p_transfer_tx =
          g_i2c_master0_P_TRANSFER_TX,
  .p_transfer_rx = g_i2c_master0_P_TRANSFER_RX, .p_callback = g_i2c_master1_cb, .p_context = NULL, .rxi_irq =
          RIIC1_RI_IRQn,
  .txi_irq = RIIC1_TI_IRQn, .tei_irq = RIIC1_TEI_IRQn, .ipl = 24, .p_extend = &g_i2c_master0_extend, };
/* Instance structure to use this module. */
const i2c_master_instance_t g_i2c_master0 =
{ .p_ctrl = &g_i2c_master0_ctrl, .p_cfg = &g_i2c_master0_cfg, .p_api = &g_i2c_master_on_iic };
gtm_instance_ctrl_t g_timer0_ctrl;
const gtm_extended_cfg_t g_timer0_extend =
{ .generate_interrupt_when_starts = GTM_GIWS_TYPE_DISABLED, .gtm_mode = GTM_TIMER_MODE_INTERVAL, .p_reg = R_GTM0, };
const timer_cfg_t g_timer0_cfg =
{ .mode = TIMER_MODE_PERIODIC,
  .period_counts = (uint32_t) 0x1869f /* Actual period: 0.001 seconds. */,
  .channel = 0,
  .p_callback = NULL,
  .p_context = NULL,
  .cycle_end_ipl = 30,
  .p_extend = &g_timer0_extend,
#if defined(VECTOR_NUMBER_GTM0_COUNTER_OVERFLOW)
    .cycle_end_irq       = VECTOR_NUMBER_GTM0_COUNTER_OVERFLOW,
#else
  .cycle_end_irq = GTM0_OSTM0INT_IRQn,
#endif
        };
/* Instance structure to use this module. */
const timer_instance_t g_timer0 =
{ .p_ctrl = &g_timer0_ctrl, .p_cfg = &g_timer0_cfg, .p_api = &g_timer_on_gtm };
extern void FreeRTOS_Tick_Handler(timer_callback_args_t*);
__attribute__( ( weak ) ) void vPortSetupTimerInterrupt(void) /* PRIVILEGED_FUNCTION */
{
    /* Stop and reset the SysTick. */
    g_timer0.p_api->open (g_timer0.p_ctrl, g_timer0.p_cfg);
    /* Configure SysTick to interrupt at the requested rate. */
    g_timer0.p_api->callbackSet (g_timer0.p_ctrl, FreeRTOS_Tick_Handler, NULL, NULL);
    /* Start the SysTick. */
    g_timer0.p_api->start (g_timer0.p_ctrl);

}
#if configGENERATE_RUN_TIME_STATS
__attribute__( ( weak ) ) void vPortConfigureTimerForRunTimeStatus( void )
{
    /* Stop and reset the Status Timer. */
    FSP_NOT_DEFINED.p_api->open(FSP_NOT_DEFINED.p_ctrl, FSP_NOT_DEFINED.p_cfg);
    /* Start the Status Timer. */
    FSP_NOT_DEFINED.p_api->start(FSP_NOT_DEFINED.p_ctrl);
}

/* Count clock = 100MHz
   10-bits-right-shift makes 10.24us counting interval */
#define runtimeCLOCK_SCALE_SHIFT    ( 10 )

/* GTM overflows 32bit */
#define runtimeOVERFLOW_SHIFT       ( 32 - runtimeCLOCK_SCALE_SHIFT )
__attribute__( ( weak ) ) unsigned long ulGetRunTimeCounterValue( void )
{
    static unsigned long ulLastCounterValue = 0UL, ulOverflows = 0;
    unsigned long ulValueNow = 0;
    timer_status_t timer_status;

    /* Get count value */
    if (FSP_SUCCESS == FSP_NOT_DEFINED.p_api->statusGet(FSP_NOT_DEFINED.p_ctrl, &timer_status))
    {
        ulValueNow = timer_status.counter;

        /* Has the value overflowed since it was last read. */
        if( ulValueNow < ulLastCounterValue )
        {
            ulOverflows++;
        }
        ulLastCounterValue = ulValueNow;

        /* move the count value to  */
        ulValueNow >>= runtimeCLOCK_SCALE_SHIFT;
        ulValueNow += ulOverflows << runtimeOVERFLOW_SHIFT;
    }

    return ulValueNow;
}
#endif
void g_hal_init(void)
{
    g_common_init ();
}
