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
void bsp_uart5_cfg(void);
void bsp_look_for_byte_rx_uart5(void);
sdt_int16u bsp_transfet_bytes_tx_uart5(sdt_int8u* in_pByte,sdt_int16u in_expect_bytes,sdt_bool in_conflict_check);
sdt_bool bsp_pull_complete_tx_uart5(void);
sdt_bool bsp_pull_pyh_busy_uart5(void);
void bsp_phy_baudrate_calibrate_uart5(void);
void bsp_entry_phy_rx_uart5(void);
void bsp_entry_phy_tx_uart5(void);

void bsp_uart2_cfg(void);
void bsp_look_for_byte_rx_uart2(void);
sdt_int16u bsp_transfet_bytes_tx_uart2(sdt_int8u* in_pByte,sdt_int16u in_expect_bytes,sdt_bool in_conflict_check);
sdt_bool bsp_pull_complete_tx_uart2(void);
sdt_bool bsp_pull_pyh_busy_uart2(void);
void bsp_phy_baudrate_calibrate_uart2(void);
void bsp_entry_phy_rx_uart2(void);
void bsp_entry_phy_tx_uart2(void);
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
//++++++++++++++++++++++++++++++++++End+++++++++++++++++++++++++++++++++++++++++