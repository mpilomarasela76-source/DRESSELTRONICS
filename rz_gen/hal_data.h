/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_uart_api.h"
#include "r_scif_uart.h"
#include "r_intc_irq.h"
#include "r_external_irq_api.h"
#include "r_riic_master.h"
#include "r_i2c_master_api.h"
#include "r_gtm.h"
#include "FreeRTOS.h"
#include "r_timer_api.h"
FSP_HEADER
/** UART on SCIF Instance. */
extern const uart_instance_t g_ra6m5_uart;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern scif_uart_instance_ctrl_t g_ra6m5_uart_ctrl;
extern const uart_cfg_t g_ra6m5_uart_cfg;
extern const scif_uart_extended_cfg_t g_ra6m5_uart_cfg_extend;

void ra6m5_uart_callback(uart_callback_args_t *p_args);

#define FSP_NOT_DEFINED (1)
#if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
#define g_ra6m5_uart_P_TRANSFER_TX (NULL)
#else
    #define g_ra6m5_uart_P_TRANSFER_TX (&FSP_NOT_DEFINED)
#endif
#if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
#define g_ra6m5_uart_P_TRANSFER_RX (NULL)
#else
    #define g_ra6m5_uart_P_TRANSFER_RX (&FSP_NOT_DEFINED)
#endif
#undef FSP_NOT_DEFINED
/** External IRQ on INTC_IRQ Instance. */
extern const external_irq_instance_t g_external_irq0;

/** Access the INTC_IRQ instance using these structures when calling API functions directly (::p_api is not used). */
extern intc_irq_instance_ctrl_t g_external_irq0_ctrl;
extern const external_irq_cfg_t g_external_irq0_cfg;

void touch_irq_callback(external_irq_callback_args_t *p_args);
/* I2C Master on RIIC Instance. */
extern const i2c_master_instance_t g_i2c_master0;

/** Access the I2C Master instance using these structures when calling API functions directly (::p_api is not used). */
extern iic_master_instance_ctrl_t g_i2c_master0_ctrl;
extern const i2c_master_cfg_t g_i2c_master0_cfg;

void g_i2c_master1_cb(i2c_master_callback_args_t *p_args);

#define FSP_NOT_DEFINED (1)
#if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
#define g_i2c_master0_P_TRANSFER_TX (NULL)
#else
    #define g_i2c_master0_P_TRANSFER_TX (&FSP_NOT_DEFINED)
#endif
#if (FSP_NOT_DEFINED == FSP_NOT_DEFINED)
#define g_i2c_master0_P_TRANSFER_RX (NULL)
#else
    #define g_i2c_master0_P_TRANSFER_RX (&FSP_NOT_DEFINED)
#endif
#undef FSP_NOT_DEFINED
/** GTM Timer Instance */
extern const timer_instance_t g_timer0;

/** Access the GTM instance using these structures when calling API functions directly (::p_api is not used). */
extern gtm_instance_ctrl_t g_timer0_ctrl;
extern const timer_cfg_t g_timer0_cfg;

extern void vPortSetupTimerInterrupt(void); /* PRIVILEGED_FUNCTION */
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
