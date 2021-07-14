//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//bough link solid
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef solid_bough_link_half_H
#define solid_bough_link_half_H
//------------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++solid+++++++++++++++++++++++++++++++++++++++++
#define max_solid    2
//-----------------------------------------------------------------------------
static bgk_oper_def bgk_oper_solid[max_solid];
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void bgk_solid_cfg(void)
{
//-----------------------------------------------------------------------------
    bsp_uart3_cfg();
    bsp_timer4_cfg();
    bgk_oper_solid[0].pull_look_for_byte_rx = bsp_look_for_byte_rx_uart3;
    bgk_oper_solid[0].transfet_bytes_to_phy_tx = bsp_transfet_bytes_tx_uart3;
    bgk_oper_solid[0].pull_complete_tx_data = bsp_pull_complete_tx_uart3;
    bgk_oper_solid[0].pull_phy_busy = bsp_pull_pyh_busy_uart3;
    bgk_oper_solid[0].phy_baudrate_calibrate = bsp_phy_baudrate_calibrate_uart3;
    bgk_oper_solid[0].entry_phy_rx = bsp_entry_phy_rx_uart3;
    bgk_oper_solid[0].entry_phy_tx = bsp_entry_phy_tx_uart3;
    bgk_oper_solid[0].timer_brate_cal.timStatusBits &= ~timStatusBits_typeMask;
    bgk_oper_solid[0].timer_brate_cal.timStatusBits |= timStatusBits_typeSecond;

    bsp_uart1_cfg();
    bsp_timer2_cfg();
    bgk_oper_solid[1].pull_look_for_byte_rx = bsp_look_for_byte_rx_uart1;
    bgk_oper_solid[1].transfet_bytes_to_phy_tx = bsp_transfet_bytes_tx_uart1;
    bgk_oper_solid[1].pull_complete_tx_data = bsp_pull_complete_tx_uart1;
    bgk_oper_solid[1].pull_phy_busy = bsp_pull_pyh_busy_uart1;
    bgk_oper_solid[1].phy_baudrate_calibrate = bsp_phy_baudrate_calibrate_uart1;
    bgk_oper_solid[1].entry_phy_rx = bsp_entry_phy_rx_uart1;
    bgk_oper_solid[1].entry_phy_tx = bsp_entry_phy_tx_uart1;
    bgk_oper_solid[1].timer_brate_cal.timStatusBits &= ~timStatusBits_typeMask;
    bgk_oper_solid[1].timer_brate_cal.timStatusBits |= timStatusBits_typeSecond;

 
//-----------------------------------------------------------------------------
}
#endif
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
