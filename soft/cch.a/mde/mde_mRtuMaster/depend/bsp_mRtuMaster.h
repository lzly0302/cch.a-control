//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef bsp_mRtuMaster_H
#define bsp_mRtuMaster_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
#ifndef snail_data_types
    #include ".\snail_data_types.h"
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
void bsp_uart2_cfg(void);
void bsp_timer3_cfg(void);
sdt_bool bsp_pull_oneByte_uart2_rxd(sdt_int8u* out_byte_details);
sdt_bool bsp_push_oneByte_uart2_txd(sdt_int8u in_byte_details);
sdt_bool bsp_uart2_busFree(sdt_int8u t_char_dis);
void bsp_restart_tim3(void);
sdt_bool bsp_pull_uart2_txd_cmp(void);
void bps_uart2_into_receive(void);
void bps_uart2_into_transmit(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++