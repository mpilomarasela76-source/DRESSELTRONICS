/* generated common source file - do not edit */
#include "common_data.h"
/* MIPI PHY Macros */
#define MIPI_PHY_CLKSTPT   (39 + 1)
#define MIPI_PHY_CLKBFHT   (13 + 1)
#define MIPI_PHY_CLKKPT    (11 + 1)
#define MIPI_PHY_GOLPBKT   (13 + 3)

#define MIPI_PHY_TINIT     (79801)
#define MIPI_PHY_TCLKPREP  (8)
#define MIPI_PHY_THSPREP   (10)
#define MIPI_PHY_TCLKTRAIL (7)
#define MIPI_PHY_TCLKPOST  (35)
#define MIPI_PHY_TCLKPRE   (4)
#define MIPI_PHY_TCLKZERO  (33)
#define MIPI_PHY_THSEXIT   (13)
#define MIPI_PHY_THSTRAIL  (9)
#define MIPI_PHY_THSZERO   (16)
#define MIPI_PHY_TLPEXIT   (6)

/* MIPI PHY Structures */
const mipi_phy_b_timing_t g_mipi_phy0_timing =
{ .t_init = 0x3FFFF & (uint32_t)MIPI_PHY_TINIT, .t_clk_prep = (uint8_t)MIPI_PHY_TCLKPREP, .t_hs_prep =
          (uint8_t)MIPI_PHY_THSPREP,
  .t_clk_trail = (uint32_t)MIPI_PHY_TCLKTRAIL, .t_clk_post = (uint32_t)MIPI_PHY_TCLKPOST, .t_clk_pre =
          (uint32_t)MIPI_PHY_TCLKPRE,
  .t_clk_zero = (uint32_t)MIPI_PHY_TCLKZERO, .t_hs_exit = (uint32_t)MIPI_PHY_THSEXIT, .t_hs_trail =
          (uint32_t)MIPI_PHY_THSTRAIL,
  .t_hs_zero = (uint32_t)MIPI_PHY_THSZERO, .t_lp_exit = (uint32_t)MIPI_PHY_TLPEXIT, };

mipi_phy_b_ctrl_t g_mipi_phy0_ctrl;
const mipi_phy_b_cfg_t g_mipi_phy0_cfg =
{ .p_timing = &g_mipi_phy0_timing, };
/* Instance structure to use this module. */
const mipi_phy_instance_t g_mipi_phy0 =
{ .p_ctrl = &g_mipi_phy0_ctrl, .p_cfg = &g_mipi_phy0_cfg, .p_api = &g_mipi_phy };
mipi_dsi_b_instance_ctrl_t g_mipi_dsi0_ctrl;

const mipi_dsi_timing_t g_mipi_dsi0_timing =
{ .clock_stop_time = MIPI_PHY_CLKSTPT,
  .clock_beforehand_time = MIPI_PHY_CLKBFHT,
  .clock_keep_time = MIPI_PHY_CLKKPT,
  .go_lp_and_back = MIPI_PHY_GOLPBKT, };

const mipi_dsi_b_extended_cfg_t g_mipi_dsi0_extended_cfg =
        { .dsi_seq0.ipl = (24),
          .dsi_seq0.irq = DSI_INT_SEQ0_IRQn,

          .dsi_seq1.ipl = (24),
          .dsi_seq1.irq = DSI_INT_SEQ1_IRQn,

          .dsi_vin1.ipl = (24),
          .dsi_vin1.irq = DSI_INT_VIN1_IRQn,

          .dsi_rcv.ipl = (24),
          .dsi_rcv.irq = DSI_INT_RCV_IRQn,

          .dsi_ferr.ipl = (24),
          .dsi_ferr.irq = DSI_INT_FERR_IRQn,

          .dsi_ppi.ipl = (24),
          .dsi_ppi.irq = DSI_INT_PPI_IRQn,

          .dsi_rxie = R_MIPI_DSI_RXIER_BTAREQEND_Msk | R_MIPI_DSI_RXIER_LRXHTO_Msk | R_MIPI_DSI_RXIER_TATO_Msk
                  | R_MIPI_DSI_RXIER_RXRESP_Msk | R_MIPI_DSI_RXIER_RXEOTP_Msk | R_MIPI_DSI_RXIER_RXACK_Msk
                  | R_MIPI_DSI_RXIER_MLFERR_Msk | R_MIPI_DSI_RXIER_ECCERR_Msk | R_MIPI_DSI_RXIER_UEXPKTERR_Msk
                  | R_MIPI_DSI_RXIER_WCERR_Msk | R_MIPI_DSI_RXIER_CRCERR_Msk | R_MIPI_DSI_RXIER_IBERR_Msk
                  | R_MIPI_DSI_RXIER_RXOVFERR_Msk | R_MIPI_DSI_RXIER_PRESPTOERR_Msk | R_MIPI_DSI_RXIER_NORETERR_Msk
                  | R_MIPI_DSI_RXIER_MAXRPSZERR_Msk | R_MIPI_DSI_RXIER_ECCERR1B_Msk | R_MIPI_DSI_RXIER_RXAKE_Msk | 0x0,
          .dsi_ferrie = R_MIPI_DSI_FERRIER_HTXTO_Msk | R_MIPI_DSI_FERRIER_LRXHTO_Msk | R_MIPI_DSI_FERRIER_TATO_Msk
                  | R_MIPI_DSI_FERRIER_ERRESC_Msk | R_MIPI_DSI_FERRIER_ERRSYNESC_Msk | R_MIPI_DSI_FERRIER_ERRCTRL_Msk
                  | R_MIPI_DSI_FERRIER_ERRCLP0_Msk | R_MIPI_DSI_FERRIER_ERRCLP1_Msk | 0x0,
          .dsi_plie = 0x0,
          .dsi_vmie = R_MIPI_DSI_VICH1IER_VBUFUDF_Msk | R_MIPI_DSI_VICH1IER_VBUFOVF_Msk | 0x0,
          .dsi_sqch0ie = R_MIPI_DSI_SQCH0IER_AACTFIN_Msk | R_MIPI_DSI_SQCH0IER_ADESFIN_Msk
                  | R_MIPI_DSI_SQCH0IER_TXIBERR_Msk | R_MIPI_DSI_SQCH0IER_RXFATALERR_Msk
                  | R_MIPI_DSI_SQCH0IER_RXFAIL_Msk | R_MIPI_DSI_SQCH0IER_RXPKTDFAIL_Msk
                  | R_MIPI_DSI_SQCH0IER_RXCORERR_Msk | R_MIPI_DSI_SQCH0IER_RXAKE_Msk | 0x0,
          .dsi_sqch1ie = R_MIPI_DSI_SQCH1IER_AACTFIN_Msk | R_MIPI_DSI_SQCH1IER_ADESFIN_Msk
                  | R_MIPI_DSI_SQCH1IER_PKTBIGERR_Msk | R_MIPI_DSI_SQCH1IER_TXIBERR_Msk
                  | R_MIPI_DSI_SQCH1IER_RXFATALERR_Msk | R_MIPI_DSI_SQCH1IER_RXFAIL_Msk
                  | R_MIPI_DSI_SQCH1IER_RXPKTDFAIL_Msk | R_MIPI_DSI_SQCH1IER_RXCORERR_Msk
                  | R_MIPI_DSI_SQCH1IER_RXAKE_Msk | 0x0, };

const mipi_dsi_cfg_t g_mipi_dsi0_cfg =
{ .p_mipi_phy_instance = &g_mipi_phy0,

  .p_timing = &g_mipi_dsi0_timing,

  .sync_pulse = (1),
  .data_type = MIPI_DSI_VIDEO_DATA_24RGB_PIXEL_STREAM,
  .virtual_channel_id = 0,

  .vertical_active_lines = 1280,
  .vertical_sync_lines = 6,
  .vertical_back_porch = (21 - 6),
  .vertical_front_porch = (1317 - 1280 - 21),
  .vertical_sync_polarity = (DISPLAY_SIGNAL_POLARITY_LOACTIVE != DISPLAY_SIGNAL_POLARITY_HIACTIVE),

  .horizontal_active_lines = 720,
  .horizontal_sync_lines = 8,
  .horizontal_back_porch = (56 - 8),
  .horizontal_front_porch = (828 - 720 - 56),
  .horizontal_sync_polarity = (DISPLAY_SIGNAL_POLARITY_LOACTIVE != DISPLAY_SIGNAL_POLARITY_HIACTIVE),

  .video_mode_delay = 216, //FSP_NOT_DEFINED,

  .hsa_no_lp = ((0x0) & R_MIPI_DSI_VICH1SET0R_HSANOLP_Msk),
  .hbp_no_lp = ((0x0) & R_MIPI_DSI_VICH1SET0R_HBPNOLP_Msk),
  .hfp_no_lp = ((0x0) & R_MIPI_DSI_VICH1SET0R_HFPNOLP_Msk),

  .num_lanes = 4,
  .ulps_wakeup_period = 130,
  .continuous_clock = (1),

  .hs_tx_timeout = 0,
  .lp_rx_timeout = 0,
  .turnaround_timeout = 0,
  .bta_timeout = 0,
  .lprw_timeout = (0 << R_MIPI_DSI_PRESPTOLPSETR_PRESPTOLPR_Pos) | 0,
  .hsrw_timeout = (0 << R_MIPI_DSI_PRESPTOHSSETR_PRESPTOHSR_Pos) | 0,

  .max_return_packet_size = 1,
  .ecc_enable = (1),
  .crc_check_mask = (mipi_dsi_vc_t) (MIPI_DSI_VC_0 | 0x0),
  .scramble_enable = (0),

  .eotp_enable = (1),

  .p_extend = &g_mipi_dsi0_extended_cfg,
  .p_callback = mipi_dsi0_callback,
  .p_context = NULL, };

/* Instance structure to use this module. */
const mipi_dsi_instance_t g_mipi_dsi0 =
{ .p_ctrl = &g_mipi_dsi0_ctrl, .p_cfg = &g_mipi_dsi0_cfg, .p_api = &g_mipi_dsi };
/** Display framebuffer */

#if LCDC_CFG_LAYER_1_ENABLE
        #ifdef fb_background_DEFINE_CRU
        #else
        #ifdef DISPLAY_INPUT0_BUFFER_NUM_0
        /** FSP do not set buffer for layer1 */
        #else
        uint8_t fb_background[2][DISPLAY_BUFFER_STRIDE_BYTES_INPUT0 * DISPLAY_VSIZE_INPUT0] BSP_ALIGN_VARIABLE(64) BSP_PLACE_IN_SECTION("UNCACHED_BSS")__attribute__ ((__aligned__(512)));
        #ifdef DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR_0
        uint8_t fb_background_CB[2][DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT0 * DISPLAY_VSIZE_UV_INPUT0] BSP_ALIGN_VARIABLE(64) BSP_PLACE_IN_SECTION("UNCACHED_BSS")__attribute__ ((__aligned__(512)));
        uint8_t fb_background_CR[2][DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT0 * DISPLAY_VSIZE_UV_INPUT0] BSP_ALIGN_VARIABLE(64) BSP_PLACE_IN_SECTION("UNCACHED_BSS")__attribute__ ((__aligned__(512)));
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
        uint8_t fb_foreground[1][DISPLAY_BUFFER_STRIDE_BYTES_INPUT1 * DISPLAY_VSIZE_INPUT1] BSP_ALIGN_VARIABLE(64) BSP_PLACE_IN_SECTION("UNCACHED_BSS")__attribute__ ((__aligned__(512)));
        #ifdef DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR_1
        uint8_t fb_foreground_CB[1][DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT1 * DISPLAY_VSIZE_UV_INPUT1]BSP_ALIGN_VARIABLE(64) BSP_PLACE_IN_SECTION("UNCACHED_BSS")__attribute__ ((__aligned__(512)));
		uint8_t fb_foreground_CR[1][DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT1 * DISPLAY_VSIZE_UV_INPUT1]BSP_ALIGN_VARIABLE(64) BSP_PLACE_IN_SECTION("UNCACHED_BSS")__attribute__ ((__aligned__(512)));
        #endif
        #define fb_foreground_DEFINE_LCDC
        #endif
        #endif
        #else
/** Graphics Layer 2 is specified not to be used when starting */
#endif

/** Display control block instance */
lcdc_instance_ctrl_t g_display0_ctrl;

/* Display devie extended configuration */
const lcdc_extended_cfg_t g_display0_extend_cfg =
{ .frame_end_ipl = 24, .underrun_ipl = 24, .frame_end_irq = LCDC_VSPD_INT_IRQn, .underrun_irq = LCDC_VSPD_INT_IRQn, };

/** Display interface configuration */
const display_cfg_t g_display0_cfg =
{
/** Input1(Graphics1 layer) configuration */
.input[0
          ] =
          {
#if LCDC_CFG_LAYER_1_ENABLE
                #ifdef DISPLAY_INPUT0_BUFFER_NUM_0
                .p_base              = NULL,
                #else
                .p_base              = (uint32_t *)&fb_background,
                #ifdef DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR_0
                .p_base_cb           = (uint32_t *)&fb_background_CB,
                .p_base_cr           = (uint32_t *)&fb_background_CR,
                .hstride_cbcr        = DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT0,
                #endif
                #endif
                #else
            .p_base = NULL,
#endif
            .hsize = DISPLAY_HSIZE_INPUT0,
            .vsize = DISPLAY_VSIZE_INPUT0, .coordinate_x = 0, .coordinate_y = 0, .hstride =
                    DISPLAY_BUFFER_STRIDE_BYTES_INPUT0,
            .format = DISPLAY_IN_FORMAT_16BITS_RGB565, .data_swap = DISPLAY_DATA_SWAP_64BIT | DISPLAY_DATA_SWAP_32BIT
                    | DISPLAY_DATA_SWAP_16BIT | false, },

  /** Input2(Graphics2 layer) configuration */
  .input[1
          ] =
          {
#if LCDC_CFG_LAYER_2_ENABLE
                #ifdef DISPLAY_INPUT1_BUFFER_NUM_0
                .p_base              = NULL,
                #else
                .p_base              = (uint32_t *)&fb_foreground,
                #ifdef DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR_1
                .p_base_cb              = (uint32_t *)&fb_foreground_CB,
                .p_base_cr              = (uint32_t *)&fb_foreground_CR,
                .hstride_cbcr           = DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT1,
                #endif
                #endif
                #else
            .p_base = NULL,
#endif
            .hsize = DISPLAY_HSIZE_INPUT1,
            .vsize = DISPLAY_VSIZE_INPUT1, .coordinate_x = 0, .coordinate_y = 0, .hstride =
                    DISPLAY_BUFFER_STRIDE_BYTES_INPUT1,
            .format = DISPLAY_IN_FORMAT_32BITS_ARGB8888, .data_swap = false | false | false | false, },

  /** Output configuration */
  .output =
  { .htiming =
  { .total_cyc = 828, .display_cyc = 720, .back_porch = 56, .sync_width = 8, .sync_polarity =
            DISPLAY_SIGNAL_POLARITY_LOACTIVE },
    .vtiming =
    { .total_cyc = 1317, .display_cyc = 1280, .back_porch = 21, .sync_width = 6, .sync_polarity =
              DISPLAY_SIGNAL_POLARITY_LOACTIVE },
    .format = DISPLAY_OUT_FORMAT_24BITS_RGB888, .data_enable_polarity = DISPLAY_SIGNAL_POLARITY_HIACTIVE, .sync_edge =
            DISPLAY_SIGNAL_SYNC_EDGE_FALLING,
    .bg_color =
    { .byte =
    { .a = 0, .r = 0, .g = 0, .b = 0 } },
    .dithering_on = false, },

  /** Display device callback function pointer */
  .p_callback = _rm_lvgl_port_display_callback,
  .p_context = NULL,

  /** Display device extended configuration */
  .p_extend = (void*) (&g_display0_extend_cfg), };

#if LCDC_CFG_LAYER_1_ENABLE
        /** Display on LCDC run-time configuration(for the graphics1 layer) */
        display_runtime_cfg_t g_display0_runtime_cfg_bg =
        {
            .input =
            {
                #if (true)
                #ifdef DISPLAY_INPUT0_BUFFER_NUM_0
                .p_base              = NULL,
                #else
                .p_base              = (uint32_t *)&fb_background,
                #ifdef DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR_0
                .p_base_cb              = (uint32_t *)&fb_background_CB,
                .p_base_cr              = (uint32_t *)&fb_background_CR,
                .hstride_cbcr           = DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT0,
                #endif
                #endif
                #else
                .p_base              = NULL,
                #endif
                .hsize               = DISPLAY_HSIZE_INPUT0,
                .vsize               = DISPLAY_VSIZE_INPUT0,
                .coordinate_x        = 0,
                .coordinate_y        = 0,
                .hstride             = DISPLAY_BUFFER_STRIDE_BYTES_INPUT0,
                .format              = DISPLAY_IN_FORMAT_16BITS_RGB565,
                .data_swap			 = DISPLAY_DATA_SWAP_64BIT | DISPLAY_DATA_SWAP_32BIT | DISPLAY_DATA_SWAP_16BIT | false,
            },
        };
#endif
#if LCDC_CFG_LAYER_2_ENABLE

        /** Display on LCDC run-time configuration(for the graphics2 layer) */
        display_runtime_cfg_t g_display0_runtime_cfg_fg =
        {
            .input =
            {
                #if (false)
                #ifdef DISPLAY_INPUT1_BUFFER_NUM_0
                .p_base              = NULL,
                #else
                .p_base              = (uint32_t *)&fb_foreground,
                #ifdef DISPLAY_IN_FORMAT_16BITS_YCBCR420_PLANAR_1
                .p_base_cb              = (uint32_t *)&fb_foreground_CB,
                .p_base_cr              = (uint32_t *)&fb_foreground_CR,
                .hstride_cbcr           = DISPLAY_BUFFER_STRIDE_UV_BYTES_INPUT1,
                #endif
                #endif
                #else
                .p_base              = NULL,
                #endif
                .hsize               = DISPLAY_HSIZE_INPUT1,
                .vsize               = DISPLAY_VSIZE_INPUT1,
                .coordinate_x        = 0,
                .coordinate_y        = 0,
                .hstride             = DISPLAY_BUFFER_STRIDE_BYTES_INPUT1,
                .format              = DISPLAY_IN_FORMAT_32BITS_ARGB8888,
                .data_swap			 = false | false | false | false,
             },
        };
#endif

/** Color Keying Configuration */
display_colorkeying_layer_t g_display0_ckey_cfg =
{ .layer[0] =
{ .src_color =
{ .byte =
{ .a = 0, .r = 0, .g = 0, .b = 0, }, },
  .dst_color =
  { .byte =
  { .a = 0, .r = 0, .g = 0, .b = 0, }, },
  .enable_ckey = DISPLAY_COLOR_KEYING_DISABLE, },

  .layer[1] =
  { .src_color =
  { .byte =
  { .a = 0, .r = 0, .g = 0, .b = 0 }, },
    .dst_color =
    { .byte =
    { .a = 0, .r = 0, .g = 0, .b = 0 }, },
    .enable_ckey = DISPLAY_COLOR_KEYING_DISABLE, } };

/* Instance structure to use this module. */
const display_instance_t g_display0 =
{ .p_ctrl = &g_display0_ctrl, .p_cfg = (display_cfg_t*) &g_display0_cfg, .p_api = (display_api_t*) &g_display_on_lcdc };
#if (RM_LVGL_PORT_CFG_PROVIDE_TICK_CALLBACK)
            /* Setup timer for LVGL tick */
            #if (BSP_CFG_RTOS == 0)
            extern void SysTick_Handler(timer_callback_args_t * args);
            __attribute__( ( weak ) ) void _rm_lvgl_port_setup_lvgl_tick( void )
            {
                /* Stop and reset the SysTick. */
                FSP_NOT_DEFINED.p_api->open(FSP_NOT_DEFINED.p_ctrl, FSP_NOT_DEFINED.p_cfg);
                /* Configure SysTick to interrupt at the requested rate. */
                FSP_NOT_DEFINED.p_api->callbackSet(FSP_NOT_DEFINED.p_ctrl, SysTick_Handler, NULL, NULL);
                /* Start the SysTick. */
                FSP_NOT_DEFINED.p_api->start(FSP_NOT_DEFINED.p_ctrl);
            }
            #endif
            #endif

/* Display Driver Frame Buffer 0 Configuration */
#if (1 == 1) /* Inherit Frame Buffer Name from Graphics Screen 1 */
#define LVGL_FRAMEBUFFER_0 (&fb_background[0]) /* Always array[0] is used */
#else /* Inherit Frame Buffer Name from Graphics Screen 2 */
             #define LVGL_FRAMEBUFFER_0 (&fb_foreground[0]) /* Always array[0] is used */
            #endif

/* Display Driver Frame Buffer 1 Configuration */
#if (1 == 1) /* Inherit Frame Buffer Name from Graphics Screen 1 */
#if (2 > 1) /* Multiple frame buffers are used for Graphics Screen 1 */
#define LVGL_FRAMEBUFFER_1 (&fb_background[1]) /* Always array[1] is used */
#else /* Single Frame Buffer is used for Graphics Screen 1 */
              #define LVGL_FRAMEBUFFER_1 (NULL)
             #endif
#else /* Inherit Frame Buffer Name from Graphics Screen 2 */
             #if (1 > 1) /* Multiple frame buffers are used for Graphics Screen 2 */
              #define LVGL_FRAMEBUFFER_1 (&fb_foreground[1]) /* Always array[1] is used */
             #else /* Single Frame Buffer is used for Graphics Screen 2 */
              #define LVGL_FRAMEBUFFER_1 (NULL)
             #endif
            #endif

#if (1)
/* Partial framebuffer */
uint8_t fb_partial[2][LVGL_DISPLAY_BUFFER_STRIDE_BYTES_INPUT * LVGL_DISPLAY_VSIZE_INPUT / LVGL_DISPLAY_BUFFER_SIZE_DIVISOR] BSP_ALIGN_VARIABLE(64) BSP_PLACE_IN_SECTION("UNCACHED_BSS")__attribute__ ((__aligned__(512)));

#define LVGL_PARTIAL_FRAMEBUFFER_0 (&fb_partial[0]) /* Always array[0] is used */
#if (2 > 1) /* Multiple frame buffers are used for Graphics Screen 1 */
#define LVGL_PARTIAL_FRAMEBUFFER_1 (&fb_partial[1]) /* Always array[1] is used */
#else /* Single Frame Buffer is used for Graphics Screen 1 */
#define LVGL_PARTIAL_FRAMEBUFFER_1 (NULL)
#endif
#else
#define LVGL_PARTIAL_FRAMEBUFFER_0 (NULL)
#define LVGL_PARTIAL_FRAMEBUFFER_1 (NULL)
#endif

/** LVGL Port module control block instance */
rm_lvgl_port_instance_ctrl_t g_lvgl_port_ctrl;

/** LVGL Port module configuration */
const rm_lvgl_port_cfg_t g_lvgl_port_cfg =
{ .p_display_instance = (display_instance_t*) &g_display0,
#if (1 == 1)
  .inherit_frame_layer = DISPLAY_FRAME_LAYER_1,
#else
	            .inherit_frame_layer = DISPLAY_FRAME_LAYER_2,
            #endif
  .p_framebuffer_0 = LVGL_FRAMEBUFFER_0,
  .p_framebuffer_1 = LVGL_FRAMEBUFFER_1,
  .p_partial_framebuffer_0 = LVGL_PARTIAL_FRAMEBUFFER_0,
  .p_partial_framebuffer_1 = LVGL_PARTIAL_FRAMEBUFFER_1,
  .render_mode = LV_DISPLAY_RENDER_MODE_PARTIAL,
  .rotation = LV_DISPLAY_ROTATION_0,
  .p_callback = NULL, };
mmu_instance_ctrl_t g_mmu_ctrl;
const mmu_cfg_t g_mmu_cfg;
/* Instance structure to use this module. */
const mmu_instance_t g_mmu =
{ .p_api = &g_mmu_on_mmu, .p_ctrl = &g_mmu_ctrl, .p_cfg = &g_mmu_cfg, };
/** IOPORT interface configuration for event link **/

ioport_event_group_output_t g_port_group_output_cfg[] =
{
{ .pin_select = (uint8_t) (uintptr_t) NULL, .operation = (ioport_event_output_operation_t) NULL }, };

ioport_event_group_input_t g_port_group_input_cfg[] =
{
{ .event_control = (ioport_event_control_t) NULL,
  .edge_detection = (ioport_event_detection_t) NULL,
  .overwrite_control = (ioport_event_control_t) NULL,
  .pin_select = (uintptr_t) NULL,
  .buffer_init_value = (uintptr_t) NULL }, };

ioport_event_single_t g_single_port_cfg[] =
{
{ .event_control = (ioport_event_control_t) NULL, .direction = (ioport_event_direction_t) NULL, .port_num =
          (uintptr_t) NULL,
  .operation = (ioport_event_output_operation_t) NULL, .edge_detection = (ioport_event_detection_t) NULL }, };

const ioport_extend_cfg_t g_ioport_cfg_extend =
{ .p_port_group_output_cfg = &g_port_group_output_cfg[0],
  .p_port_group_input_cfg = &g_port_group_input_cfg[0],
  .p_single_port_cfg = &g_single_port_cfg[0] };

ioport_instance_ctrl_t g_ioport_ctrl;
const ioport_instance_t g_ioport =
{ .p_api = &g_ioport_on_ioport, .p_ctrl = &g_ioport_ctrl, .p_cfg = &g_bsp_pin_cfg, };
void g_common_init(void)
{
}
