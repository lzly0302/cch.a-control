//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef snail_data_types
    #include ".\snail_data_types.h"
#endif
//-------------------------------------------------------------------------------------------------
#include "..\mde_bough_link_half.h"
#include ".\snail_macro.h"
#include "gd32f4xx.h"
#include "intrinsics.h"
//-------------------------------------------------------------------------------------------------
#define bgk_s0    0
#define bgk_s1    1
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*串口3接面板风盘控制器*/  
//uart3 txd--PC10  rxd--Pc11  EN3 Pc12  BY3 PA14 
#define UART3_EXIT_PORT   GPIOA       
#define UART3_EXIT_PIN    GPIO_PIN_15
#define UART3_EN_PORT     GPIOC       
#define UART3_EN_PIN      GPIO_PIN_12
#define UART3_TX_PORT     GPIOC       
#define UART3_TX_PIN      GPIO_PIN_10
#define UART3_RX_PORT     GPIOC       
#define UART3_RX_PIN      GPIO_PIN_11
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_creat_queueBasce(uart3_queue_rxd,255);
macro_creat_queueBasce(uart3_queue_txd,255);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//中断服务函数
//-----------------------------------------------------------------------------
void UART3_IRQHandler(void)
{
    if((RESET != usart_flag_get(UART3, USART_FLAG_ORERR)) || 
         (RESET != usart_flag_get(UART3, USART_FLAG_NERR)) || 
           (RESET != usart_flag_get(UART3, USART_FLAG_FERR)))
    {
        /* receive data */
        usart_data_receive(UART3);
    }
    else if((RESET != usart_interrupt_flag_get(UART3, USART_INT_FLAG_PERR)) && 
       (RESET != usart_flag_get(UART3, USART_FLAG_PERR)))
    {
        /* receive data */
        usart_data_receive(UART3);
    }
    else if((RESET != usart_interrupt_flag_get(UART3, USART_INT_FLAG_RBNE)) && 
       (RESET != usart_flag_get(UART3, USART_FLAG_RBNE)))
    {//接收到的数据可以读取
        /* receive data */
        sdt_int8u Read_reg;
        Read_reg = usart_data_receive(UART3);
       
        sdt_int8u n_bytes;
        macro_pull_queueBasce_bytes(uart3_queue_rxd,n_bytes);

        sdt_bool queunIsFull;
        macro_pull_queueBasce_full(uart3_queue_rxd,n_bytes,queunIsFull);
        if(queunIsFull)
        {
        }
        else
        {
            macro_push_queueBasce_data(uart3_queue_rxd,n_bytes,Read_reg);
        } 
    }
    if((RESET != usart_flag_get(UART3, USART_FLAG_TC)) && 
       (RESET != usart_interrupt_flag_get(UART3, USART_INT_FLAG_TC)))
    { //发送完成         
        /* transmit data */
        sdt_int8u n_bytes,rd_byte_details;
        macro_pull_queueBasce_bytes(uart3_queue_txd,n_bytes);
        if(n_bytes)
        {
            macro_pull_queueBasce_data(uart3_queue_txd,n_bytes,rd_byte_details);
            usart_data_transmit(UART3,rd_byte_details);
        }
        else
        {
            usart_interrupt_disable(UART3, USART_INT_TC);
        }
    }
}
volatile static sdt_bool  phyBusBusyFlag3 = sdt_false;
void TIMER4_IRQHandler(void)
{
    if(SET==timer_interrupt_flag_get(TIMER4,TIMER_INT_FLAG_UP))
    {
        timer_interrupt_flag_clear(TIMER4,TIMER_INT_FLAG_UP);
        phyBusBusyFlag3 = sdt_false;
        timer_flag_clear(TIMER4,TIMER_FLAG_UP);   
        timer_interrupt_disable(TIMER4,TIMER_INT_UP); 
    }
}
void EXTI10_15_IRQHandler(void)
{
    if(SET==exti_interrupt_flag_get(EXTI_15))
    {//串口5
        exti_interrupt_flag_clear(EXTI_15);
        phyBusBusyFlag3 = sdt_true;
        TIMER_CNT(TIMER4) = 0;
        timer_flag_clear(TIMER4,TIMER_FLAG_UP);
        timer_interrupt_flag_clear(TIMER4,TIMER_INT_FLAG_UP);
        timer_interrupt_enable(TIMER4,TIMER_INT_UP);
    }   
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
void bsp_uart3_cfg(void)
{
    /* USART interrupt configuration */
    nvic_irq_enable(UART3_IRQn, 0, 0);
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
     /* enable USART clock */
    rcu_periph_clock_enable(RCU_UART3);
     /* connect port to USARTx_Tx */
    gpio_af_set(UART3_TX_PORT, GPIO_AF_8, UART3_TX_PIN);

    /* connect port to USARTx_Rx */
    gpio_af_set(UART3_RX_PORT, GPIO_AF_8,UART3_RX_PIN);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(UART3_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,UART3_TX_PIN);
    gpio_output_options_set(UART3_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART3_TX_PIN);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(UART3_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,UART3_RX_PIN);
    gpio_output_options_set(UART3_RX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART3_RX_PIN);

    /* configure usart en port */ 
    gpio_mode_set(UART3_EN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,UART3_EN_PIN);

    /* configure usart exit port */ 
    gpio_mode_set(UART3_EXIT_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,UART3_EXIT_PIN);
    /* enable and set key EXTI interrupt to the lowest priority */
    nvic_irq_enable(EXTI10_15_IRQn, 0U, 0U);
     /* connect key EXTI line to key GPIO pin */
    syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN15);
    /* configure key EXTI line */
    exti_init(EXTI_15, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
    exti_interrupt_flag_clear(EXTI_15);

    /* USART configure */
    usart_deinit(UART3);
    usart_baudrate_set(UART3,9600);
    usart_parity_config(UART3,USART_PM_NONE);
    usart_word_length_set(UART3,USART_WL_8BIT);
    usart_stop_bit_set(UART3,USART_STB_1BIT);
    usart_receive_config(UART3, USART_RECEIVE_ENABLE);
    usart_transmit_config(UART3, USART_TRANSMIT_ENABLE);
    usart_enable(UART3);
     /* enable USART TBE interrupt */  
    usart_interrupt_enable(UART3, USART_INT_RBNE);
}

void bsp_timer4_cfg(void)
{
    /* ---------------------------------------------------------------
    TIMER1 Configuration: 
    TIMER1CLK = SystemCoreClock / 1680 = 100K,
    --------------------------------------------------------------- */
    nvic_irq_enable(TIMER4_IRQn, 0, 0);
    timer_parameter_struct timer_initpara;
    
    rcu_periph_clock_enable(RCU_TIMER4);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    timer_deinit(TIMER4);
    /* TIMER1 configuration */
    timer_initpara.prescaler         = (1679);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (200-1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER4,&timer_initpara);   
     /* TIMER0 channel control update interrupt enable */
 //   timer_interrupt_enable(TIMER4,TIMER_INT_UP);
    timer_interrupt_disable(TIMER4,TIMER_INT_UP);
    /* enable the update event */
    timer_update_event_enable(TIMER4);
    /* set TIMER counter up direction */
    timer_counter_up_direction(TIMER4);
    /* TIMER0 break interrupt disable */
    timer_interrupt_disable(TIMER4,TIMER_INT_BRK);
    timer_enable(TIMER4);
}

sdt_bool bsp_ms_tim4_busFree(void)
{
    sdt_int16u free_cnt;
    free_cnt = timer_counter_read(TIMER4);
    if(free_cnt > 50)      //9600 3.5T 1040*3.25/2
    {
        return(sdt_true);
    }
    else
    {
        return(sdt_false);
    }
}

void bsp_check_uart3_phy_bus(void)
{
    if(phyBusBusyFlag3)
    {
        if(bsp_ms_tim4_busFree())
        {
            phyBusBusyFlag3 = sdt_false;
        }
    }
}

sdt_bool bsp_ms_pull_uart3_phyBus_status(void)
{
   return phyBusBusyFlag3;
}

sdt_int8u bsp_ms_pull_uart3_rxd_num(void)
{
    sdt_int8u n_bytes;
    macro_pull_queueBasce_bytes(uart3_queue_rxd,n_bytes);
    return n_bytes;
}

void bsp_look_for_byte_rx_uart3(void)
{
 
    sdt_int8u n_bytes,rd_byte_details;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart3_queue_rxd,n_bytes);
    __enable_interrupt();
    if(n_bytes)
    {
        __disable_interrupt();
        macro_pull_queueBasce_data(uart3_queue_rxd,n_bytes,rd_byte_details);
        __enable_interrupt();
        push_bough_one_receive_byte(bgk_s0,rd_byte_details);     //压入一个字节的数据到link
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_entry_phy_rx_uart3(void)
{
    gpio_mode_set(UART3_EN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,UART3_EN_PIN);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//对等总线，由发送报文时选择发送方式，此处采用空函数
//------------------------------------------------------------------------------
void bsp_entry_phy_tx_uart3(void)
{
    ;
}
sdt_bool bsp_pull_complete_tx_uart3(void)
{
    sdt_int8u n_bytes;
    
    macro_pull_queueBasce_bytes(uart3_queue_txd,n_bytes);
    if(n_bytes)
    {
        return(sdt_false);
    }
    else
    {
        if(SET==usart_interrupt_flag_get(UART3, USART_INT_FLAG_TC))
        {
            return(sdt_false);
        }
        else
        {
            bsp_entry_phy_rx_uart3();
            return(sdt_true);
        }      
    }
}
sdt_bool bsp_pull_pyh_busy_uart3(void)
{
    if(phyBusBusyFlag3)
    {
        return(sdt_true);
    }
    return(sdt_false);
}
void bsp_phy_baudrate_calibrate_uart3(void)
{
}


sdt_int16u bsp_transfet_bytes_tx_uart3(sdt_int8u* in_pByte,sdt_int16u in_expect_bytes,sdt_bool in_conflict_check)
{
    //sdt_int16u i = 0;
    if(0 != in_expect_bytes)
    {
        if(in_conflict_check)
        {
            gpio_mode_set(UART3_EN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,UART3_EN_PIN);//冲突检测，弱上拉发送
        }
        else
        {
             //推挽发送
			gpio_mode_set(UART3_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,UART3_EN_PIN);
            gpio_output_options_set(UART3_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART3_EN_PIN);
            GPIO_BOP(UART3_EN_PORT) = UART3_EN_PIN;
        }
		sdt_int8u n_bytes;
		__disable_interrupt();
		macro_pull_queueBasce_bytes(uart3_queue_txd,n_bytes);
		__enable_interrupt();
		sdt_bool queunIsFull;
		macro_pull_queueBasce_full(uart3_queue_txd,n_bytes,queunIsFull);
		if(queunIsFull)
		{
			return(0);
		}
		else
		{
			__disable_interrupt();
			macro_push_queueBasce_data(uart3_queue_txd,n_bytes,in_pByte[0]);
			__enable_interrupt();
			usart_interrupt_enable(UART3, USART_INT_TC);
			return(in_expect_bytes-1);                              
		}     
    }
    return(0);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_ms_uart3_phyReCfg(sdt_int32u sys_fre,sdt_int32u baud_rate,sdt_int8u parity,sdt_int8u stop_bits)
{
    
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*串口1接除湿模块*/  
//uart1 txd--PD5  rxd--PD6  EN PD7  EXIT PB3 
#define UART1_EXIT_PORT   GPIOB       
#define UART1_EXIT_PIN    GPIO_PIN_3
#define UART1_EN_PORT     GPIOD       
#define UART1_EN_PIN      GPIO_PIN_7
#define UART1_TX_PORT     GPIOD       
#define UART1_TX_PIN      GPIO_PIN_5
#define UART1_RX_PORT     GPIOD       
#define UART1_RX_PIN      GPIO_PIN_6
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_creat_queueBasce(uart1_queue_rxd,255);
macro_creat_queueBasce(uart1_queue_txd,255);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//中断服务函数
//-----------------------------------------------------------------------------
void USART1_IRQHandler(void)
{
    if((RESET != usart_flag_get(USART1, USART_FLAG_ORERR)) || 
         (RESET != usart_flag_get(USART1, USART_FLAG_NERR)) || 
           (RESET != usart_flag_get(USART1, USART_FLAG_FERR)))
    {
        /* receive data */
        usart_data_receive(USART1);
    }
    else if((RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_PERR)) && 
       (RESET != usart_flag_get(USART1, USART_FLAG_PERR)))
    {
        /* receive data */
        usart_data_receive(USART1);
    }
    else if((RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_RBNE)) && 
       (RESET != usart_flag_get(USART1, USART_FLAG_RBNE)))
    {//接收到的数据可以读取
        /* receive data */
        sdt_int8u Read_reg;
        Read_reg = usart_data_receive(USART1);
       
        sdt_int8u n_bytes;
        macro_pull_queueBasce_bytes(uart1_queue_rxd,n_bytes);

        sdt_bool queunIsFull;
        macro_pull_queueBasce_full(uart1_queue_rxd,n_bytes,queunIsFull);
        if(queunIsFull)
        {
        }
        else
        {
            macro_push_queueBasce_data(uart1_queue_rxd,n_bytes,Read_reg);
        } 
    }
    if((RESET != usart_flag_get(USART1, USART_FLAG_TC)) && 
       (RESET != usart_interrupt_flag_get(USART1, USART_INT_FLAG_TC)))
    { //发送完成         
        /* transmit data */
        sdt_int8u n_bytes,rd_byte_details;
        macro_pull_queueBasce_bytes(uart1_queue_txd,n_bytes);
        if(n_bytes)
        {
            macro_pull_queueBasce_data(uart1_queue_txd,n_bytes,rd_byte_details);
            usart_data_transmit(USART1,rd_byte_details);
        }
        else
        {
            usart_interrupt_disable(USART1, USART_INT_TC);
        }
    }
}
volatile static sdt_bool  phyBusBusyFlag1 = sdt_false;
void TIMER2_IRQHandler(void)
{
    if(SET==timer_interrupt_flag_get(TIMER2,TIMER_INT_FLAG_UP))
    {
        timer_interrupt_flag_clear(TIMER2,TIMER_INT_FLAG_UP);
        phyBusBusyFlag1 = sdt_false;
        timer_flag_clear(TIMER2,TIMER_FLAG_UP);   
        timer_interrupt_disable(TIMER2,TIMER_INT_UP); 
    }
}
void EXTI3_IRQHandler(void)
{
    if(SET==exti_interrupt_flag_get(EXTI_3))
    {//串口5
        exti_interrupt_flag_clear(EXTI_3);
        phyBusBusyFlag1 = sdt_true;
        TIMER_CNT(TIMER2) = 0;
        timer_flag_clear(TIMER2,TIMER_FLAG_UP);
        timer_interrupt_flag_clear(TIMER2,TIMER_INT_FLAG_UP);
        timer_interrupt_enable(TIMER2,TIMER_INT_UP);
    }   
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
void bsp_uart1_cfg(void)
{
    /* USART interrupt configuration */
    nvic_irq_enable(USART1_IRQn, 0, 0);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOD);
     /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART1);
     /* connect port to USARTx_Tx */
    gpio_af_set(UART1_TX_PORT, GPIO_AF_7, UART1_TX_PIN);

    /* connect port to USARTx_Rx */
    gpio_af_set(UART1_RX_PORT, GPIO_AF_7,UART1_RX_PIN);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(UART1_TX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,UART1_TX_PIN);
    gpio_output_options_set(UART1_TX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART1_TX_PIN);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(UART1_RX_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP,UART1_RX_PIN);
    gpio_output_options_set(UART1_RX_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART1_RX_PIN);

    /* configure usart en port */ 
    gpio_mode_set(UART1_EN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,UART1_EN_PIN);

    /* configure usart exit port */ 
    gpio_mode_set(UART1_EXIT_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,UART1_EXIT_PIN);
    /* enable and set key EXTI interrupt to the lowest priority */
    nvic_irq_enable(EXTI3_IRQn, 0U, 0U);
     /* connect key EXTI line to key GPIO pin */
    syscfg_exti_line_config(EXTI_SOURCE_GPIOA, EXTI_SOURCE_PIN3);
    /* configure key EXTI line */
    exti_init(EXTI_3, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
    exti_interrupt_flag_clear(EXTI_3);

    /* USART configure */
    usart_deinit(USART1);
    usart_baudrate_set(USART1,9600);
    usart_parity_config(USART1,USART_PM_NONE);
    usart_word_length_set(USART1,USART_WL_8BIT);
    usart_stop_bit_set(USART1,USART_STB_1BIT);
    usart_receive_config(USART1, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);
    usart_enable(USART1);
     /* enable USART TBE interrupt */  
    usart_interrupt_enable(USART1, USART_INT_RBNE);
}

void bsp_timer2_cfg(void)
{
    /* ---------------------------------------------------------------
    TIMER1 Configuration: 
    TIMER1CLK = SystemCoreClock / 1680 = 100K,
    --------------------------------------------------------------- */
    nvic_irq_enable(TIMER2_IRQn, 0, 0);
    timer_parameter_struct timer_initpara;
    
    rcu_periph_clock_enable(RCU_TIMER2);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);
    timer_deinit(TIMER2);
    /* TIMER1 configuration */
    timer_initpara.prescaler         = (1679);
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (200-1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER2,&timer_initpara);   
     /* TIMER0 channel control update interrupt enable */
 //   timer_interrupt_enable(TIMER4,TIMER_INT_UP);
    timer_interrupt_disable(TIMER2,TIMER_INT_UP);
    /* enable the update event */
    timer_update_event_enable(TIMER2);
    /* set TIMER counter up direction */
    timer_counter_up_direction(TIMER2);
    /* TIMER0 break interrupt disable */
    timer_interrupt_disable(TIMER2,TIMER_INT_BRK);
    timer_enable(TIMER2);
}

sdt_bool bsp_ms_tim2_busFree(void)
{
    sdt_int16u free_cnt;
    free_cnt = timer_counter_read(TIMER2);
    if(free_cnt > 50)      //9600 3.5T 1040*3.25/2
    {
        return(sdt_true);
    }
    else
    {
        return(sdt_false);
    }
}

void bsp_check_uart1_phy_bus(void)
{
    if(phyBusBusyFlag1)
    {
        if(bsp_ms_tim2_busFree())
        {
            phyBusBusyFlag1 = sdt_false;
        }
    }
}

sdt_bool bsp_ms_pull_uart1_phyBus_status(void)
{
   return phyBusBusyFlag1;
}

sdt_int8u bsp_ms_pull_uart1_rxd_num(void)
{
    sdt_int8u n_bytes;
    macro_pull_queueBasce_bytes(uart1_queue_rxd,n_bytes);
    return n_bytes;
}

void bsp_look_for_byte_rx_uart1(void)
{
 
    sdt_int8u n_bytes,rd_byte_details;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart1_queue_rxd,n_bytes);
    __enable_interrupt();
    if(n_bytes)
    {
        __disable_interrupt();
        macro_pull_queueBasce_data(uart1_queue_rxd,n_bytes,rd_byte_details);
        __enable_interrupt();
        push_bough_one_receive_byte(bgk_s1,rd_byte_details);     //压入一个字节的数据到link
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_entry_phy_rx_uart1(void)
{
    gpio_mode_set(UART1_EN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,UART1_EN_PIN);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//对等总线，由发送报文时选择发送方式，此处采用空函数
//------------------------------------------------------------------------------
void bsp_entry_phy_tx_uart1(void)
{
    ;
}
sdt_bool bsp_pull_complete_tx_uart1(void)
{
    sdt_int8u n_bytes;
    
    macro_pull_queueBasce_bytes(uart1_queue_txd,n_bytes);
    if(n_bytes)
    {
        return(sdt_false);
    }
    else
    {
        if(SET==usart_interrupt_flag_get(USART1, USART_INT_FLAG_TC))
        {
            return(sdt_false);
        }
        else
        {
            bsp_entry_phy_rx_uart1();
            return(sdt_true);
        }      
    }
}
sdt_bool bsp_pull_pyh_busy_uart1(void)
{
    if(phyBusBusyFlag1)
    {
        return(sdt_true);
    }
    return(sdt_false);
}
void bsp_phy_baudrate_calibrate_uart1(void)
{
}


sdt_int16u bsp_transfet_bytes_tx_uart1(sdt_int8u* in_pByte,sdt_int16u in_expect_bytes,sdt_bool in_conflict_check)
{
    //sdt_int16u i = 0;
    if(0 != in_expect_bytes)
    {
        if(in_conflict_check)
        {
            gpio_mode_set(UART1_EN_PORT, GPIO_MODE_INPUT, GPIO_PUPD_NONE,UART1_EN_PIN);//冲突检测，弱上拉发送
        }
        else
        {
             //推挽发送
			gpio_mode_set(UART1_EN_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,UART1_EN_PIN);
            gpio_output_options_set(UART1_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,UART1_EN_PIN);
            GPIO_BOP(UART1_EN_PORT) = UART1_EN_PIN;
        }
		sdt_int8u n_bytes;
		__disable_interrupt();
		macro_pull_queueBasce_bytes(uart1_queue_txd,n_bytes);
		__enable_interrupt();
		sdt_bool queunIsFull;
		macro_pull_queueBasce_full(uart1_queue_txd,n_bytes,queunIsFull);
		if(queunIsFull)
		{
			return(0);
		}
		else
		{
			__disable_interrupt();
			macro_push_queueBasce_data(uart1_queue_txd,n_bytes,in_pByte[0]);
			__enable_interrupt();
			usart_interrupt_enable(USART1, USART_INT_TC);
			return(in_expect_bytes-1);                              
		}     
    }
    return(0);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_ms_uart1_phyReCfg(sdt_int32u sys_fre,sdt_int32u baud_rate,sdt_int8u parity,sdt_int8u stop_bits)
{
    
}