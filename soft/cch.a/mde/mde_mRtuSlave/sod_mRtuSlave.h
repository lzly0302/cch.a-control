#ifndef med_mRtuSlave_H
#define mde_mRtuSlave_H
//-----------------------------------------------------------------------------
#ifndef snail_data_types
    #include ".\depend\snail_data_types.h"
#endif
#include ".\depend\bsp_mRtuSlave.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
//+++++++++++++++++++++++++++++++solid+++++++++++++++++++++++++++++++++++++++++
#define max_solid    2
//-----------------------------------------------------------------------------
static modbus_oper_def modbus_oper_solid[max_solid];
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void modbus_solid_cfg(void)
{
//-----------------------------------------------------------------------------
    bsp_uart0_cfg();
    bsp_timer1_cfg();
    modbus_oper_solid[0].pull_receive_byte = bsp_pull_oneByte_uart0_rxd;
    modbus_oper_solid[0].push_transmit_byte = bsp_push_oneByte_uart0_txd;
    modbus_oper_solid[0].pull_busFree = bsp_uart0_busFree;
    modbus_oper_solid[0].restart_busFree_timer = bsp_restart_tim1;
    modbus_oper_solid[0].phy_into_receive = bps_uart0_into_receive;
    modbus_oper_solid[0].phy_into_transmit_status = bps_uart0_into_transmit;
    modbus_oper_solid[0].pull_transmit_complete =bsp_pull_uart0_txd_cmp;
         
    bsp_uart5_cfg();
    bsp_timer5_cfg();
    modbus_oper_solid[1].pull_receive_byte = bsp_pull_oneByte_uart5_rxd;
    modbus_oper_solid[1].push_transmit_byte = bsp_push_oneByte_uart5_txd;
    modbus_oper_solid[1].pull_busFree = bsp_uart5_busFree;
    modbus_oper_solid[1].restart_busFree_timer = bsp_restart_tim5;
    modbus_oper_solid[1].phy_into_receive = bps_uart5_into_receive;
    modbus_oper_solid[1].phy_into_transmit_status = bps_uart5_into_transmit;
    modbus_oper_solid[1].pull_transmit_complete =bsp_pull_uart5_txd_cmp;
    
//    bsp_uart2_cfg();
//    bsp_timer3_cfg();
//    modbus_oper_solid[2].pull_receive_byte = bsp_pull_oneByte_uart2_rxd;
//    modbus_oper_solid[2].push_transmit_byte = bsp_push_oneByte_uart2_txd;
//    modbus_oper_solid[2].pull_busFree = bsp_uart2_busFree;
//    modbus_oper_solid[2].restart_busFree_timer = bsp_restart_tim3;
//    modbus_oper_solid[2].phy_into_receive = bps_uart2_into_receive;
//    modbus_oper_solid[2].phy_into_transmit_status = bps_uart2_into_transmit;
//    modbus_oper_solid[2].pull_transmit_complete =bsp_pull_uart2_txd_cmp;
//
//-----------------------------------------------------------------------------
}
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++