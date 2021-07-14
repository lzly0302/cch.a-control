//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef bsp_mRtuSlave_H
#define bsp_mRtuSlave_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//-----------------------------------------------------------------------------
void bsp_uart0_cfg(void);
void bsp_timer1_cfg(void);
sdt_bool bsp_pull_oneByte_uart0_rxd(sdt_int8u* out_byte_details);
sdt_bool bsp_push_oneByte_uart0_txd(sdt_int8u in_byte_details);
sdt_bool bsp_uart0_busFree(sdt_int8u t_char_dis);
void bsp_restart_tim1(void);
sdt_bool bsp_pull_uart0_txd_cmp(void);
void bps_uart0_into_receive(void);
void bps_uart0_into_transmit(void);

void bsp_uart2_cfg(void);
void bsp_timer3_cfg(void);
sdt_bool bsp_pull_oneByte_uart2_rxd(sdt_int8u* out_byte_details);
sdt_bool bsp_push_oneByte_uart2_txd(sdt_int8u in_byte_details);
sdt_bool bsp_uart2_busFree(sdt_int8u t_char_dis);
void bsp_restart_tim3(void);
sdt_bool bsp_pull_uart2_txd_cmp(void);
void bps_uart2_into_receive(void);
void bps_uart2_into_transmit(void);

void bsp_uart5_cfg(void);
void bsp_timer5_cfg(void);
sdt_bool bsp_pull_oneByte_uart5_rxd(sdt_int8u* out_byte_details);
sdt_bool bsp_push_oneByte_uart5_txd(sdt_int8u in_byte_details);
sdt_bool bsp_uart5_busFree(sdt_int8u t_char_dis);
void bsp_restart_tim5(void);
sdt_bool bsp_pull_uart5_txd_cmp(void);
void bps_uart5_into_receive(void);
void bps_uart5_into_transmit(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++