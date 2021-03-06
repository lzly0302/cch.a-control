//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "gd32f4xx.h"
#include ".\snail_macro.h"
#include ".\snail_data_types.h"
#include "..\..\mde_bough_link\mde_bough_link_half.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*波特率、奇偶校验位设置*/
/*串口0*/
//uart0 txd--Pb6  rxd--Pb7   trol pb5
#define UART0_EN_PORT     GPIOB       //usart0_en
#define UART0_EN_PIN      GPIO_PIN_5
#define UART0_TX_PORT     GPIOB       //usart0_en
#define UART0_TX_PIN      GPIO_PIN_6
#define UART0_RX_PORT     GPIOB       //usart0_en
#define UART0_RX_PIN      GPIO_PIN_7
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_creat_queueBasce(uart0_queue_rxd,64);
macro_creat_queueBasce(uart0_queue_txd,255);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//中断服务函数
//-----------------------------------------------------------------------------
void USART0_IRQHandler(void)
{
    if((RESET != usart_flag_get(USART0, USART_FLAG_ORERR)) ||
        (RESET != usart_flag_get(USART0, USART_FLAG_FERR)) || 
         (RESET != usart_flag_get(USART0, USART_FLAG_NERR)))
    {
        /* receive data */
        usart_data_receive(USART0);
    }
    else if((RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_PERR)) && 
       (RESET != usart_flag_get(USART0, USART_FLAG_PERR)))
    {
        /* receive data */
        usart_data_receive(USART0);
    }
    else if((RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE)) && 
       (RESET != usart_flag_get(USART0, USART_FLAG_RBNE)))
    {
        /* receive data */
        sdt_int8u Read_reg;
        Read_reg = usart_data_receive(USART0);
       
        sdt_int8u n_bytes;
        macro_pull_queueBasce_bytes(uart0_queue_rxd,n_bytes);

        sdt_bool queunIsFull;
        macro_pull_queueBasce_full(uart0_queue_rxd,n_bytes,queunIsFull);
        if(queunIsFull)
        {
        }
        else
        {
            macro_push_queueBasce_data(uart0_queue_rxd,n_bytes,Read_reg);
        } 
    }
    if((RESET != usart_flag_get(USART0, USART_FLAG_TC)) && 
       (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_TC)))
    {          
        /* transmit data */
        sdt_int8u n_bytes,rd_byte_details;
        macro_pull_queueBasce_bytes(uart0_queue_txd,n_bytes);
        if(n_bytes)
        {
            macro_pull_queueBasce_data(uart0_queue_txd,n_bytes,rd_byte_details);
            usart_data_transmit(USART0,rd_byte_details);
        }
        else
        {
            usart_interrupt_disable(USART0, USART_INT_TC);
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
void bsp_uart0_cfg(void)
{   
    /* USART interrupt configuration */
    nvic_irq_enable(USART0_IRQn, 0, 0);
    rcu_periph_clock_enable(RCU_GPIOB);
     /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);
     /* connect port to USARTx_Tx */
    gpio_af_set(UART0_TX_PORT, GPIO_AF_7, UART0_TX_PIN);

    /* connect port to USARTx_Rx */
    gpio_af_set(UART0_RX_PORT, GPIO_AF_7,UART0_RX_PIN);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(UART0_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,UART0_TX_PIN);
    gpio_output_options_set(UART0_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART0_TX_PIN);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(UART0_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,UART0_RX_PIN);
    gpio_output_options_set(UART0_RX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART0_RX_PIN);

    /* configure usart0 en port */ 
    gpio_mode_set(UART0_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,UART0_EN_PIN);
    gpio_output_options_set(UART0_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART0_EN_PIN);

    /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0,9600);
    usart_parity_config(USART0,USART_PM_NONE);
    usart_word_length_set(USART0,USART_WL_8BIT);
    usart_stop_bit_set(USART0,USART_STB_1BIT);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);
     /* enable USART TBE interrupt */  
    usart_interrupt_enable(USART0, USART_INT_TC);
    usart_interrupt_enable(USART0, USART_INT_RBNE);
}

void bsp_timer1_cfg(void)
{
    /* ---------------------------------------------------------------
    TIMER1 Configuration: 
    TIMER1CLK = SystemCoreClock / 336 = 500K,
    --------------------------------------------------------------- */
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER1);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);

    timer_deinit(TIMER1);

    /* TIMER1 configuration */
    timer_initpara.prescaler         = 335;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 65535;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER1,&timer_initpara);   
    timer_enable(TIMER1);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:获取一个字节的接收数据
//out: sdt_true 获取成功，sdt_falas 获取失败
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_oneByte_uart0_rxd(sdt_int8u* out_byte_details)
{
    sdt_int8u n_bytes,rd_byte_details;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart0_queue_rxd,n_bytes);
    __enable_interrupt();
    if(n_bytes)
    {
        __disable_interrupt();
        macro_pull_queueBasce_data(uart0_queue_rxd,n_bytes,rd_byte_details);
        __enable_interrupt();
        *out_byte_details = rd_byte_details;
        return(sdt_true);
    }
    else
    {
        
        return(sdt_false);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:压入一个字节的数据到发送队列
//out: sdt_true 压入成功，sdt_false 压入失败
//-----------------------------------------------------------------------------
sdt_bool bsp_push_oneByte_uart0_txd(sdt_int8u in_byte_details)
{
    sdt_int8u n_bytes;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart0_queue_txd,n_bytes);
    __enable_interrupt();
    sdt_bool queunIsFull;
    macro_pull_queueBasce_full(uart0_queue_txd,n_bytes,queunIsFull);
    if(queunIsFull)
    {
        return(sdt_false);
    }
    else
    {
        __disable_interrupt();
        macro_push_queueBasce_data(uart0_queue_txd,n_bytes,in_byte_details);
        __enable_interrupt();
        usart_interrupt_enable(USART0, USART_INT_TC);
        return(sdt_true);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
sdt_bool bsp_uart0_busFree(sdt_int8u t_char_dis)
{
    //static sdt_int16u rd_rxd_depart_cnt;
    static  sdt_int16u rd_cnt;
    static  sdt_int16u free_cnt;

    rd_cnt = timer_counter_read(TIMER1);
    free_cnt = rd_cnt;

    sdt_int16u limit_ft;
    
    limit_ft = 104*t_char_dis/2;  //9600 T == 104us
    if(free_cnt > limit_ft)  //9600 3.5T 1040*3.25/2
    {
        return(sdt_true);
    }
    else
    {
        return(sdt_false);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_restart_tim1(void)
{
   TIMER_CNT(TIMER1) = 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool bsp_pull_uart0_txd_cmp(void)
{
    sdt_int8u n_bytes;
    
    macro_pull_queueBasce_bytes(uart0_queue_txd,n_bytes);
    if(n_bytes)
    {
        return(sdt_false);
    }
    else
    {
       /* if(RESET != usart_flag_get(USART0, USART_FLAG_TC))
        {
            return(sdt_false);
        }
        else
        {
            return(sdt_true);
        }  */
        return(sdt_true);    
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart0_into_receive(void)
{
    usart_interrupt_enable(USART0, USART_INT_RBNE);
    GPIO_BC(UART0_EN_PORT) = UART0_EN_PIN;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart0_into_transmit(void)
{
    usart_interrupt_disable(USART0, USART_INT_RBNE);
    GPIO_BOP(UART0_EN_PORT) = UART0_EN_PIN;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_uart_phyReCfg(sdt_int32u sys_fre,sdt_int32u baud_rate,sdt_int8u parity,sdt_int8u stop_bits)
{
    //static sdt_int32u bak_sys_fre = 0,bak_baud_rate = 0;
    //static sdt_int8u bak_parity = 0,bak_stop_bits = 0;
   /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0,9600);
    usart_parity_config(USART0,USART_PM_NONE);
    usart_word_length_set(USART0,USART_WL_8BIT);
    usart_stop_bit_set(USART0,USART_STB_1BIT);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void get_queue_data(sdt_int8u* out_inx,sdt_int8u* out_otx,sdt_int8u* out_nbyte)
{
    __disable_interrupt();
    *out_inx = uart0_queue_rxd_in_idx;
    *out_otx = uart0_queue_rxd_out_idx;
    *out_nbyte = uart0_queue_rxd_bytes;
    __enable_interrupt();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*串口2*/
//uart2 txd--PD8  rxd--PD9   trol pD10
//#define UART2_EN_PORT     GPIOD       //usart0_en
//#define UART2_EN_PIN      GPIO_PIN_10
//#define UART2_TX_PORT     GPIOD       //usart0_en
//#define UART2_TX_PIN      GPIO_PIN_8
//#define UART2_RX_PORT     GPIOD       //usart0_en
//#define UART2_RX_PIN      GPIO_PIN_9
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//macro_creat_queueBasce(uart2_queue_rxd,64);
//macro_creat_queueBasce(uart2_queue_txd,255);
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////中断服务函数
////-----------------------------------------------------------------------------
//void USART2_IRQHandler(void)
//{
//    if((RESET != usart_flag_get(USART2, USART_FLAG_ORERR)) || 
//         (RESET != usart_flag_get(USART2, USART_FLAG_NERR)) || 
//           (RESET != usart_flag_get(USART2, USART_FLAG_FERR)))
//    {
//        /* receive data */
//        usart_data_receive(USART2);
//    }
//    else if((RESET != usart_interrupt_flag_get(USART2, USART_INT_FLAG_PERR)) && 
//       (RESET != usart_flag_get(USART2, USART_FLAG_PERR)))
//    {
//        /* receive data */
//        usart_data_receive(USART2);
//    }
//    else if((RESET != usart_interrupt_flag_get(USART2, USART_INT_FLAG_RBNE)) && 
//       (RESET != usart_flag_get(USART2, USART_FLAG_RBNE)))
//    {
//        /* receive data */
//        sdt_int8u Read_reg;
//        Read_reg = usart_data_receive(USART2);
//       
//        sdt_int8u n_bytes;
//        macro_pull_queueBasce_bytes(uart2_queue_rxd,n_bytes);
//
//        sdt_bool queunIsFull;
//        macro_pull_queueBasce_full(uart2_queue_rxd,n_bytes,queunIsFull);
//        if(queunIsFull)
//        {
//        }
//        else
//        {
//            macro_push_queueBasce_data(uart2_queue_rxd,n_bytes,Read_reg);
//        } 
//    }
//    if(RESET != usart_interrupt_flag_get(USART2, USART_INT_FLAG_TC))    
//    {          
//        /* transmit data */
//        if(RESET != usart_flag_get(USART2, USART_FLAG_TC))
//        {
//            sdt_int8u n_bytes,rd_byte_details;
//            macro_pull_queueBasce_bytes(uart2_queue_txd,n_bytes);
//            if(n_bytes)
//            {
//                macro_pull_queueBasce_data(uart2_queue_txd,n_bytes,rd_byte_details);
//                usart_data_transmit(USART2,rd_byte_details);
//            }
//            else
//            {
//                usart_interrupt_disable(USART2, USART_INT_TC);
//            }
//        }        
//    }
//}
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
////-----------------------------------------------------------------------------
//void bsp_uart2_cfg(void)
//{   
//    /* USART interrupt configuration */
//    nvic_irq_enable(USART2_IRQn, 0, 0);
//    rcu_periph_clock_enable(RCU_GPIOD);
//     /* enable USART clock */
//    rcu_periph_clock_enable(RCU_USART2);
//     /* connect port to USARTx_Tx */
//    gpio_af_set(UART2_TX_PORT, GPIO_AF_7, UART2_TX_PIN);
//
//    /* connect port to USARTx_Rx */
//    gpio_af_set(UART2_RX_PORT, GPIO_AF_7,UART2_RX_PIN);
//
//    /* configure USART Tx as alternate function push-pull */
//    gpio_mode_set(UART2_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,UART2_TX_PIN);
//    gpio_output_options_set(UART2_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART2_TX_PIN);
//
//    /* configure USART Rx as alternate function push-pull */
//    gpio_mode_set(UART2_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,UART2_RX_PIN);
//    gpio_output_options_set(UART2_RX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART2_RX_PIN);
//
//    /* configure usart0 en port */ 
//    gpio_mode_set(UART2_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,UART2_EN_PIN);
//    gpio_output_options_set(UART2_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART2_EN_PIN);
//
//    /* USART configure */
//    usart_deinit(USART2);
//    usart_baudrate_set(USART2,9600);
//    usart_parity_config(USART2,USART_PM_NONE);
//    usart_word_length_set(USART2,USART_WL_8BIT);
//    usart_stop_bit_set(USART2,USART_STB_1BIT);
//    usart_receive_config(USART2, USART_RECEIVE_ENABLE);
//    usart_transmit_config(USART2, USART_TRANSMIT_ENABLE);
//    usart_enable(USART2);
//     /* enable USART TBE interrupt */  
//    usart_interrupt_enable(USART2, USART_INT_TC);
//    usart_interrupt_enable(USART2, USART_INT_RBNE);
//}
//
//void bsp_timer3_cfg(void)
//{
//    /* ---------------------------------------------------------------
//    TIMER1 Configuration: 
//    TIMER1CLK = SystemCoreClock / 336 = 500K,
//    --------------------------------------------------------------- */
//    timer_parameter_struct timer_initpara;
//
//    rcu_periph_clock_enable(RCU_TIMER3);
//    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
//
//    timer_deinit(TIMER3);
//
//    /* TIMER1 configuration */
//    timer_initpara.prescaler         = 335;
//    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
//    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
//    timer_initpara.period            = 65535;
//    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
//    timer_initpara.repetitioncounter = 0;
//    timer_init(TIMER3,&timer_initpara);   
//    timer_enable(TIMER3);
//}
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////name:获取一个字节的接收数据
////out: sdt_true 获取成功，sdt_falas 获取失败
////-----------------------------------------------------------------------------
//sdt_bool bsp_pull_oneByte_uart2_rxd(sdt_int8u* out_byte_details)
//{
//    sdt_int8u n_bytes,rd_byte_details;
//    __disable_interrupt();
//    macro_pull_queueBasce_bytes(uart2_queue_rxd,n_bytes);
//    __enable_interrupt();
//    if(n_bytes)
//    {
//        __disable_interrupt();
//        macro_pull_queueBasce_data(uart2_queue_rxd,n_bytes,rd_byte_details);
//        __enable_interrupt();
//        *out_byte_details = rd_byte_details;
//        return(sdt_true);
//    }
//    else
//    {      
//        return(sdt_false);
//    }
//}
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////name:压入一个字节的数据到发送队列
////out: sdt_true 压入成功，sdt_false 压入失败
////-----------------------------------------------------------------------------
//sdt_bool bsp_push_oneByte_uart2_txd(sdt_int8u in_byte_details)
//{
//    sdt_int8u n_bytes;
//    __disable_interrupt();
//    macro_pull_queueBasce_bytes(uart2_queue_txd,n_bytes);
//    __enable_interrupt();
//    sdt_bool queunIsFull;
//    macro_pull_queueBasce_full(uart2_queue_txd,n_bytes,queunIsFull);
//    if(queunIsFull)
//    {
//        return(sdt_false);
//    }
//    else
//    {
//        __disable_interrupt();
//        macro_push_queueBasce_data(uart2_queue_txd,n_bytes,in_byte_details);
//        __enable_interrupt();
//        usart_interrupt_enable(USART2, USART_INT_TC);
//        return(sdt_true);
//    }
//}
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////-----------------------------------------------------------------------------
//sdt_bool bsp_uart2_busFree(sdt_int8u t_char_dis)
//{
//    //static sdt_int16u rd_rxd_depart_cnt;
//    static  sdt_int16u rd_cnt;
//    static  sdt_int16u free_cnt;
//
//    rd_cnt = timer_counter_read(TIMER3);
//    free_cnt = rd_cnt;
//
//    sdt_int16u limit_ft;
//    
//    limit_ft = 104*t_char_dis/2;  //9600 T == 104us
//    if(free_cnt > limit_ft)  //9600 3.5T 1040*3.25/2
//    {
//        return(sdt_true);
//    }
//    else
//    {
//        return(sdt_false);
//    }
//}
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//void bsp_restart_tim3(void)
//{
//   TIMER_CNT(TIMER3) = 0;
//}
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//sdt_bool bsp_pull_uart2_txd_cmp(void)
//{
//    sdt_int8u n_bytes;
//    
//    macro_pull_queueBasce_bytes(uart2_queue_txd,n_bytes);
//    if(n_bytes)
//    {
//        return(sdt_false);
//    }
//    else
//    { 
//        return(sdt_true);
//    }
//}
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//void bps_uart2_into_receive(void)
//{
//    usart_interrupt_enable(USART2, USART_INT_RBNE);
//    GPIO_BC(UART2_EN_PORT) = UART2_EN_PIN;
//}
////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//void bps_uart2_into_transmit(void)
//{
//    usart_interrupt_disable(USART2, USART_INT_RBNE);
//    GPIO_BOP(UART2_EN_PORT) = UART2_EN_PIN;
//}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*串口5*/
//uart5 txd--PA11  rxd--PA12   trol pA10
#define UART5_EN_PORT     GPIOA       //usart0_en
#define UART5_EN_PIN      GPIO_PIN_10
#define UART5_TX_PORT     GPIOA       //usart0_en
#define UART5_TX_PIN      GPIO_PIN_11
#define UART5_RX_PORT     GPIOA       //usart0_en
#define UART5_RX_PIN      GPIO_PIN_12
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_creat_queueBasce(uart5_queue_rxd,64);
macro_creat_queueBasce(uart5_queue_txd,255);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//中断服务函数
//-----------------------------------------------------------------------------
void USART5_IRQHandler(void)
{
     if((RESET != usart_flag_get(USART5, USART_FLAG_ORERR)) || 
         (RESET != usart_flag_get(USART5, USART_FLAG_NERR)) || 
           (RESET != usart_flag_get(USART5, USART_FLAG_FERR)))
    {
        /* receive data */
        usart_data_receive(USART5);
    }
    else if((RESET != usart_interrupt_flag_get(USART5, USART_INT_FLAG_PERR)) && 
       (RESET != usart_flag_get(USART5, USART_FLAG_PERR)))
    {
        /* receive data */
        usart_data_receive(USART5);
    }
    else if((RESET != usart_interrupt_flag_get(USART5, USART_INT_FLAG_RBNE)) && 
       (RESET != usart_flag_get(USART5, USART_FLAG_RBNE)))
    {
        /* receive data */
        sdt_int8u Read_reg;
        Read_reg = usart_data_receive(USART5);
       
        sdt_int8u n_bytes;
        macro_pull_queueBasce_bytes(uart5_queue_rxd,n_bytes);

        sdt_bool queunIsFull;
        macro_pull_queueBasce_full(uart5_queue_rxd,n_bytes,queunIsFull);
        if(queunIsFull)
        {
        }
        else
        {
            macro_push_queueBasce_data(uart5_queue_rxd,n_bytes,Read_reg);
        } 
    }
    if((RESET != usart_flag_get(USART5, USART_FLAG_TC)) && 
       (RESET != usart_interrupt_flag_get(USART5, USART_INT_FLAG_TC)))
    {          
        /* transmit data */
        sdt_int8u n_bytes,rd_byte_details;
        macro_pull_queueBasce_bytes(uart5_queue_txd,n_bytes);
        if(n_bytes)
        {
            macro_pull_queueBasce_data(uart5_queue_txd,n_bytes,rd_byte_details);
            usart_data_transmit(USART5,rd_byte_details);
        }
        else
        {
            usart_interrupt_disable(USART5, USART_INT_TC);
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
void bsp_uart5_cfg(void)
{   
    /* USART interrupt configuration */
    nvic_irq_enable(USART5_IRQn, 0, 0);
    rcu_periph_clock_enable(RCU_GPIOA);
     /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART5);
     /* connect port to USARTx_Tx */
    gpio_af_set(UART5_TX_PORT, GPIO_AF_8, UART5_TX_PIN);

    /* connect port to USARTx_Rx */
    gpio_af_set(UART5_RX_PORT, GPIO_AF_8,UART5_RX_PIN);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(UART5_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,UART5_TX_PIN);
    gpio_output_options_set(UART5_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART5_TX_PIN);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(UART5_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,UART5_RX_PIN);
    gpio_output_options_set(UART5_RX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART5_RX_PIN);

    /* configure usart0 en port */ 
    gpio_mode_set(UART5_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,UART5_EN_PIN);
    gpio_output_options_set(UART5_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART5_EN_PIN);

    /* USART configure */
    usart_deinit(USART5);
    usart_baudrate_set(USART5,19200);
    usart_parity_config(USART5,USART_PM_NONE);
    usart_word_length_set(USART5,USART_WL_8BIT);
    usart_stop_bit_set(USART5,USART_STB_1BIT);
    usart_receive_config(USART5, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART5, USART_TRANSMIT_ENABLE);
    usart_enable(USART5);
     /* enable USART TBE interrupt */  
    usart_interrupt_enable(USART5, USART_INT_TC);
    usart_interrupt_enable(USART5, USART_INT_RBNE);
}

void bsp_timer5_cfg(void)
{
    /* ---------------------------------------------------------------
    TIMER1 Configuration: 
    TIMER1CLK = SystemCoreClock / 336 = 500K,
    --------------------------------------------------------------- */
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER5);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);

    timer_deinit(TIMER5);

    /* TIMER1 configuration */
    timer_initpara.prescaler         = 335;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = 65535;
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER5,&timer_initpara);   
    timer_enable(TIMER5);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:获取一个字节的接收数据
//out: sdt_true 获取成功，sdt_falas 获取失败
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_oneByte_uart5_rxd(sdt_int8u* out_byte_details)
{
    sdt_int8u n_bytes,rd_byte_details;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart5_queue_rxd,n_bytes);
    __enable_interrupt();
    if(n_bytes)
    {
        __disable_interrupt();
        macro_pull_queueBasce_data(uart5_queue_rxd,n_bytes,rd_byte_details);
        __enable_interrupt();
        *out_byte_details = rd_byte_details;
        return(sdt_true);
    }
    else
    {
        
        return(sdt_false);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:压入一个字节的数据到发送队列
//out: sdt_true 压入成功，sdt_false 压入失败
//-----------------------------------------------------------------------------
sdt_bool bsp_push_oneByte_uart5_txd(sdt_int8u in_byte_details)
{
    sdt_int8u n_bytes;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart5_queue_txd,n_bytes);
    __enable_interrupt();
    sdt_bool queunIsFull;
    macro_pull_queueBasce_full(uart5_queue_txd,n_bytes,queunIsFull);
    if(queunIsFull)
    {
        return(sdt_false);
    }
    else
    {
        __disable_interrupt();
        macro_push_queueBasce_data(uart5_queue_txd,n_bytes,in_byte_details);
        __enable_interrupt();
        usart_interrupt_enable(USART5, USART_INT_TC);
        return(sdt_true);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
sdt_bool bsp_uart5_busFree(sdt_int8u t_char_dis)
{
    //static sdt_int16u rd_rxd_depart_cnt;
    static  sdt_int16u rd_cnt;
    static  sdt_int16u free_cnt;

    rd_cnt = timer_counter_read(TIMER5);
    free_cnt = rd_cnt;

    sdt_int16u limit_ft;
    
    limit_ft = 104*t_char_dis/2;  //9600 T == 104us
    if(free_cnt > limit_ft)  //9600 3.5T 1040*3.25/2
    {
        return(sdt_true);
    }
    else
    {
        return(sdt_false);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_restart_tim5(void)
{
   TIMER_CNT(TIMER5) = 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool bsp_pull_uart5_txd_cmp(void)
{
    sdt_int8u n_bytes;
    
    macro_pull_queueBasce_bytes(uart5_queue_txd,n_bytes);
    if(n_bytes)
    {
        return(sdt_false);
    }
    else
    {
       /* if(RESET != usart_flag_get(USART5, USART_FLAG_TBE))
        {
            return(sdt_false);
        }
        else
        {
            return(sdt_true);
        }  */  
        return(sdt_true);  
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart5_into_receive(void)
{
    usart_interrupt_enable(USART5, USART_INT_RBNE);
    GPIO_BC(UART5_EN_PORT) = UART5_EN_PIN;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart5_into_transmit(void)
{
    usart_interrupt_disable(USART5, USART_INT_RBNE);
    GPIO_BOP(UART5_EN_PORT) = UART5_EN_PIN;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++