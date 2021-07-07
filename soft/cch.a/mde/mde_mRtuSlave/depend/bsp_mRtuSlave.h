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

/*void bsp_uart3_cfg(void);
sdt_bool bsp_pull_oneByte_uart3_rxd(sdt_int8u* out_byte_details);
sdt_bool bsp_push_oneByte_uart3_txd(sdt_int8u in_byte_details);
sdt_bool bsp_uart3_busFree(sdt_int8u t_char_dis);
void bsp_restart_tim4(void);
sdt_bool bsp_pull_uart3_txd_cmp(void);
void bps_uart3_into_receive(void);
void bps_uart3_into_transmit(void);

void bsp_uart1_cfg(void);
sdt_bool bsp_pull_oneByte_uart1_rxd(sdt_int8u* out_byte_details);
sdt_bool bsp_push_oneByte_uart1_txd(sdt_int8u in_byte_details);
sdt_bool bsp_uart1_busFree(sdt_int8u t_char_dis);
void bsp_restart_tim6(void);
sdt_bool bsp_pull_uart1_txd_cmp(void);
void bps_uart1_into_receive(void);
void bps_uart1_into_transmit(void);
void bsp_uart1_phyReCfg(sdt_int8u baud_rate,sdt_int8u parity);*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#endif 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++