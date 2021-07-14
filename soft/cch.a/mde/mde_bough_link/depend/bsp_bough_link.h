//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef _BSP_BOUGHLINK_H
#define _BSP_BOUGHLINK_H
//------------------------------------------------------------------------------
#ifndef snail_data_types
    #include ".\snail_data_types.h"
#endif
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------------------------------------
//Task
//------------------------------------------------------------------------------
//Event
//------------------------------------------------------------------------------
//Status
//------------------------------------------------------------------------------
//Function
//------------------------------------------------------------------------------
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_uart3_cfg(void);
void bsp_timer4_cfg(void);
void bsp_look_for_byte_rx_uart3(void);
sdt_int16u bsp_transfet_bytes_tx_uart3(sdt_int8u* in_pByte,sdt_int16u in_expect_bytes,sdt_bool in_conflict_check);
sdt_bool bsp_pull_complete_tx_uart3(void);
sdt_bool bsp_pull_pyh_busy_uart3(void);
void bsp_phy_baudrate_calibrate_uart3(void);
void bsp_entry_phy_rx_uart3(void);
void bsp_entry_phy_tx_uart3(void);

void bsp_uart1_cfg(void);
void bsp_timer2_cfg(void);
void bsp_look_for_byte_rx_uart1(void);
sdt_int16u bsp_transfet_bytes_tx_uart1(sdt_int8u* in_pByte,sdt_int16u in_expect_bytes,sdt_bool in_conflict_check);
sdt_bool bsp_pull_complete_tx_uart1(void);
sdt_bool bsp_pull_pyh_busy_uart1(void);
void bsp_phy_baudrate_calibrate_uart1(void);
void bsp_entry_phy_rx_uart1(void);
void bsp_entry_phy_tx_uart1(void);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
//++++++++++++++++++++++++++++++++++End+++++++++++++++++++++++++++++++++++++++++