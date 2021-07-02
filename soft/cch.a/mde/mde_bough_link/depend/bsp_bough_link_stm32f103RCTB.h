//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef snail_data_types
    #include ".\snail_data_types.h"
#endif
//-------------------------------------------------------------------------------------------------
#include "..\mde_bough_link_half.h"
#include ".\snail_macro.h"
#include "stm32f10x.h"
#include "intrinsics.h"
//-------------------------------------------------------------------------------------------------
#define bgk_s0    0
#define bgk_s1    1
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*串口5*/
//uart5 txd--PC12  rxd--PD2   EN5 PC6  BY5 PC7 改为  EN5 PB15  BY5 PB14 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_creat_queueBasce(uart5_queue_rxd,255);
macro_creat_queueBasce(uart5_queue_txd,255);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//中断服务函数
//-----------------------------------------------------------------------------
void UART5_IRQHandler(void)
{
    if((SET==USART_GetFlagStatus(UART5,USART_FLAG_ORE))||\
       (SET==USART_GetFlagStatus(UART5,USART_FLAG_NE))||\
       (SET==USART_GetFlagStatus(UART5,USART_FLAG_FE)))
    {
        USART_GetFlagStatus(UART5,USART_FLAG_ORE);
        USART_ReceiveData(UART5);
    }
    else if(SET==USART_GetFlagStatus(UART5,USART_FLAG_PE))
    {
        USART_GetFlagStatus(UART5,USART_FLAG_PE);
        USART_ReceiveData(UART5);
    }
    else if(SET==USART_GetFlagStatus(UART5,USART_FLAG_RXNE))
    {
        sdt_int8u Read_reg;
        Read_reg = USART_ReceiveData(UART5);
       
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
    if(SET==USART_GetITStatus(UART5,USART_IT_TC))
    {
        if(SET==USART_GetFlagStatus(UART5,USART_FLAG_TC))
        {
            sdt_int8u n_bytes,rd_byte_details;
            macro_pull_queueBasce_bytes(uart5_queue_txd,n_bytes);
            if(n_bytes)
            {
                macro_pull_queueBasce_data(uart5_queue_txd,n_bytes,rd_byte_details);
                USART_SendData(UART5,rd_byte_details);
            }
            else
            {
                USART_ITConfig(UART5,USART_IT_TC,DISABLE);
            }
        }
    }
}
volatile static sdt_bool  phyBusBusyFlag5 = sdt_false;
void TIM7_IRQHandler(void)
{
    if(SET==TIM_GetFlagStatus(TIM7,TIM_FLAG_Update))
    {
        TIM_ClearFlag(TIM7,TIM_FLAG_Update); 
        phyBusBusyFlag5 = sdt_false;
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
        TIM_ClearFlag(TIM7,TIM_FLAG_Update);               //清除溢出中断标志  
        TIM_ITConfig(TIM7,TIM_IT_Update,DISABLE);  
    }
}
void EXTI15_10_IRQHandler(void)
{
   if(EXTI_GetITStatus(EXTI_Line14) != RESET) 
    {//串口5
        EXTI_ClearITPendingBit(EXTI_Line14);
        phyBusBusyFlag5 = sdt_true;
        TIM7->CNT = 0;
        TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
        TIM_ClearFlag(TIM7,TIM_FLAG_Update);               //清除溢出中断标志  
        TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);  
    }   
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
void bsp_uart5_cfg(void)
{
    GPIO_InitTypeDef    GPIO_USART5INIT; 
    USART_InitTypeDef   USART5_INIT;
    NVIC_InitTypeDef    USART5_NVIC_INIT;

 //-----------------------------------------------------------------------------   
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);  //开启串口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   //开启GPIOC口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //开启GPIOB口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);   //开启GPIOD口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启GPIOA口时钟
//-----------------------------------------------------------------------------  
    GPIO_USART5INIT.GPIO_Pin=GPIO_Pin_12;                   //PC12 U5_TXD
    GPIO_USART5INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART5INIT.GPIO_Mode=GPIO_Mode_AF_PP;            //输出复用推挽
    GPIO_Init(GPIOC,&GPIO_USART5INIT);
//-----------------------------------------------------------------------------     
    GPIO_USART5INIT.GPIO_Pin=GPIO_Pin_2;                   //PD2 U5_RXD
    GPIO_USART5INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART5INIT.GPIO_Mode=GPIO_Mode_IPU;               //输入上拉
    GPIO_Init(GPIOD,&GPIO_USART5INIT);
//-----------------------------------------------------------------------------  
    GPIO_USART5INIT.GPIO_Pin=GPIO_Pin_15;                   //PC6 TRSEL  PB15
    GPIO_USART5INIT.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOB,&GPIO_USART5INIT);
    GPIO_ResetBits(GPIOB,GPIO_Pin_15);
    
     /*pc7  PB14*/
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_EXTILineConfig( GPIO_PortSourceGPIOB,  GPIO_PinSource14); 
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line =  EXTI_Line14;
 
      /* EXTI为中断模式 */
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
     /* 上升沿下降沿中断 */
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//EXTI_Trigger_Rising;//EXTI_Trigger_Rising_Falling
    /* 使能中断 */
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置NVIC为优先级组1 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* 配置中断源：按键1 */
    NVIC_InitStructure.NVIC_IRQChannel =  EXTI15_10_IRQn;
  /* 配置抢占优先级 */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  /* 配置子优先级 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
//-----------------------------------------------------------------------------   
    USART_DeInit(UART5);
    USART5_INIT.USART_BaudRate=9600;
    USART5_INIT.USART_Parity=USART_Parity_No;
    USART5_INIT.USART_WordLength=USART_WordLength_8b;    

    USART5_INIT.USART_StopBits=USART_StopBits_1;
    USART5_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART5_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(UART5,&USART5_INIT);
    USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);           //使能接收中断
    USART_Cmd(UART5,ENABLE);
//-----------------------------------------------------------------------------
    USART5_NVIC_INIT.NVIC_IRQChannel=UART5_IRQn;
    USART5_NVIC_INIT.NVIC_IRQChannelPreemptionPriority=0;  //主优先级
    USART5_NVIC_INIT.NVIC_IRQChannelSubPriority=0;         //子优先级
    USART5_NVIC_INIT.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&USART5_NVIC_INIT);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;              //TIM4 3.5T的时序管理
//-----------------------------------------------------------------------------  
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); 
    TIM_DeInit(TIM7);
    /* Time base configuration */    
    TIM_TimeBaseStructure.TIM_Prescaler =(720)-1;                    //72M 100k ,10us
    TIM_TimeBaseStructure.TIM_Period =(200-1);                      // 当定时器从0计数到999，即为1000次，为一个定时周期,1个unit 10us
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;        //设置时钟分频系数：不分频(这里用不到)
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //向上计数模式
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
//-----------------------------------------------------------------------------
    TIM_Cmd(TIM7,ENABLE);                              //开启时钟  
    //--------------------------------------------------------------------------------------------
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;       
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
//-------------------------------------------------------------------------------------------
    TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
    TIM_ClearFlag(TIM7,TIM_FLAG_Update);               //清除溢出中断标志  
    TIM_ITConfig(TIM7,TIM_IT_Update,DISABLE);  
    TIM_Cmd(TIM7,ENABLE);                              //开启时钟  
}

sdt_bool bsp_ms_tim7_busFree(void)
{
    sdt_int16u free_cnt;
    free_cnt = TIM7->CNT;
    if(free_cnt > 50)      //9600 3.5T 1040*3.25/2
    {
        return(sdt_true);
    }
    else
    {
        return(sdt_false);
    }
}

void bsp_check_uart5_phy_bus(void)
{
    if(phyBusBusyFlag5)
    {
        if(bsp_ms_tim7_busFree())
        {
            phyBusBusyFlag5 = sdt_false;
        }
    }
}

sdt_bool bsp_ms_pull_uart5_phyBus_status(void)
{
   return phyBusBusyFlag5;
}
sdt_int8u bsp_ms_pull_uart5_rxd_num(void)
{
    sdt_int8u n_bytes;
    macro_pull_queueBasce_bytes(uart5_queue_rxd,n_bytes);
    return n_bytes;
}

void bsp_look_for_byte_rx_uart5(void)
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
        push_bough_one_receive_byte(bgk_s0,rd_byte_details);     //压入一个字节的数据到link
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_entry_phy_rx_uart5(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; 
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//对等总线，由发送报文时选择发送方式，此处采用空函数
//------------------------------------------------------------------------------
void bsp_entry_phy_tx_uart5(void)
{
    ;
}
sdt_bool bsp_pull_complete_tx_uart5(void)
{
    sdt_int8u n_bytes;
    
    macro_pull_queueBasce_bytes(uart5_queue_txd,n_bytes);
    if(n_bytes)
    {
        return(sdt_false);
    }
    else
    {
        if(SET==USART_GetITStatus(UART5,USART_IT_TC))
        {
            return(sdt_false);
        }
        else
        {
            bsp_entry_phy_rx_uart5();
            return(sdt_true);
        }      
    }
}
sdt_bool bsp_pull_pyh_busy_uart5(void)
{
    if(phyBusBusyFlag5)
    {
        return(sdt_true);
    }
    return(sdt_false);
}
void bsp_phy_baudrate_calibrate_uart5(void)
{
}


sdt_int16u bsp_transfet_bytes_tx_uart5(sdt_int8u* in_pByte,sdt_int16u in_expect_bytes,sdt_bool in_conflict_check)
{
    //sdt_int16u i = 0;
    if(0 != in_expect_bytes)
    {
        if(in_conflict_check)
        {
            GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; 
			GPIO_Init(GPIOB,&GPIO_InitStructure);
			GPIO_ResetBits(GPIOB,GPIO_Pin_15);//冲突检测，弱上拉发送
        }
        else
        {
             //推挽发送
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;                   //PB15 TRSEL
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;            //推挽输出
			GPIO_Init(GPIOB,&GPIO_InitStructure);
			GPIO_SetBits(GPIOB,GPIO_Pin_15);
        }
		sdt_int8u n_bytes;
		__disable_interrupt();
		macro_pull_queueBasce_bytes(uart5_queue_txd,n_bytes);
		__enable_interrupt();
		sdt_bool queunIsFull;
		macro_pull_queueBasce_full(uart5_queue_txd,n_bytes,queunIsFull);
		if(queunIsFull)
		{
			return(0);
		}
		else
		{
			__disable_interrupt();
			macro_push_queueBasce_data(uart5_queue_txd,n_bytes,in_pByte[0]);
			__enable_interrupt();
			USART_ITConfig(UART5,USART_IT_TC,ENABLE);
			return(in_expect_bytes-1);                              
		}     
    }
    return(0);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:压入一个字节的数据到发送队列
//out: sdt_true 压入成功，sdt_false 压入失败
//-----------------------------------------------------------------------------

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//sdt_bool bsp_ms_pull_uart5_txd_cmp(void)
//{
//    sdt_int8u n_bytes;
//    
//    macro_pull_queueBasce_bytes(uart5_queue_txd,n_bytes);
//    if(n_bytes)
//    {
//        return(sdt_false);
//    }
//    else
//    {
//        if(SET==USART_GetITStatus(UART5,USART_IT_TXE))
//        {
//            return(sdt_false);
//        }
//        else
//        {
//            return(sdt_true);
//        }      
//    }
//}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_ms_uart5_phyReCfg(sdt_int32u sys_fre,sdt_int32u baud_rate,sdt_int8u parity,sdt_int8u stop_bits)
{
    USART_InitTypeDef   USART5_INIT;

    USART_DeInit(UART5);
    USART5_INIT.USART_BaudRate=9600;
    USART5_INIT.USART_Parity=USART_Parity_No;
    USART5_INIT.USART_WordLength=USART_WordLength_8b;    

    USART5_INIT.USART_StopBits=USART_StopBits_1;
    USART5_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART5_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(UART5,&USART5_INIT);
}



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*串口2*/
//uart2 txd--PA2  rxd--PA3   EN2 PA4  BY2 PA5  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_creat_queueBasce(uart2_queue_rxd,255);
macro_creat_queueBasce(uart2_queue_txd,255);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//中断服务函数
//-----------------------------------------------------------------------------
void USART2_IRQHandler(void)
{
    if((SET==USART_GetFlagStatus(USART2,USART_FLAG_ORE))||\
       (SET==USART_GetFlagStatus(USART2,USART_FLAG_NE))||\
       (SET==USART_GetFlagStatus(USART2,USART_FLAG_FE)))
    {
        USART_GetFlagStatus(USART2,USART_FLAG_ORE);
        USART_ReceiveData(USART2);
    }
    else if(SET==USART_GetFlagStatus(USART2,USART_FLAG_PE))
    {
        USART_GetFlagStatus(USART2,USART_FLAG_PE);
        USART_ReceiveData(USART2);
    }
    else if(SET==USART_GetFlagStatus(USART2,USART_FLAG_RXNE))
    {
        sdt_int8u Read_reg;
        Read_reg = USART_ReceiveData(USART2);
       
        sdt_int8u n_bytes;
        macro_pull_queueBasce_bytes(uart2_queue_rxd,n_bytes);

        sdt_bool queunIsFull;
        macro_pull_queueBasce_full(uart2_queue_rxd,n_bytes,queunIsFull);
        if(queunIsFull)
        {
        }
        else
        {
            macro_push_queueBasce_data(uart2_queue_rxd,n_bytes,Read_reg);
        }
    }
    if(SET==USART_GetITStatus(USART2,USART_IT_TXE))
    {
        if(SET==USART_GetFlagStatus(USART2,USART_FLAG_TXE))
        {
            sdt_int8u n_bytes,rd_byte_details;
            macro_pull_queueBasce_bytes(uart2_queue_txd,n_bytes);
            if(n_bytes)
            {
                macro_pull_queueBasce_data(uart2_queue_txd,n_bytes,rd_byte_details);
                USART_SendData(USART2,rd_byte_details);
            }
            else
            {
                USART_ITConfig(USART2,USART_IT_TXE,DISABLE);
            }
        }
    }
}
sdt_bool  phyBusBusyFlag2 = sdt_false;

void TIM2_IRQHandler(void)
{
    if(SET==TIM_GetFlagStatus(TIM2,TIM_FLAG_Update))
    {
        TIM_ClearFlag(TIM2,TIM_FLAG_Update); 
        phyBusBusyFlag2 = sdt_false;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        TIM_ClearFlag(TIM2,TIM_FLAG_Update);               //清除溢出中断标志  
        TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);  
    }
}

void EXTI9_5_IRQHandler(void)
{
    
    if(EXTI_GetITStatus(EXTI_Line5) != RESET) 
    {//串口2
        EXTI_ClearITPendingBit(EXTI_Line5);
        phyBusBusyFlag2 = sdt_true;
        TIM2->CNT = 0;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        TIM_ClearFlag(TIM2,TIM_FLAG_Update);               //清除溢出中断标志  
        TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);     
    }
}

////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
void bsp_uart2_cfg(void)
{
    GPIO_InitTypeDef    GPIO_USART2INIT; 
    USART_InitTypeDef   USART2_INIT;
    NVIC_InitTypeDef    USART2_NVIC_INIT;

 //-----------------------------------------------------------------------------   
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);  //开启串口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启GPIOA口时钟
//-----------------------------------------------------------------------------  
    GPIO_USART2INIT.GPIO_Pin=GPIO_Pin_2;                   //PA2 U2_TXD
    GPIO_USART2INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART2INIT.GPIO_Mode=GPIO_Mode_AF_PP;            //输出复用推挽
    GPIO_Init(GPIOA,&GPIO_USART2INIT);
    GPIO_SetBits(GPIOA,GPIO_Pin_2);
//-----------------------------------------------------------------------------     
    GPIO_USART2INIT.GPIO_Pin=GPIO_Pin_3;                   //PA3 U2_RXD
    GPIO_USART2INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART2INIT.GPIO_Mode=GPIO_Mode_IPU;               //输入上拉
    GPIO_Init(GPIOA,&GPIO_USART2INIT);
//-----------------------------------------------------------------------------  
    GPIO_USART2INIT.GPIO_Pin=GPIO_Pin_4;                   //PA4 TRSEL
    GPIO_USART2INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART2INIT.GPIO_Mode=GPIO_Mode_IN_FLOATING;            //浮空输入
    GPIO_Init(GPIOA,&GPIO_USART2INIT);
    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
//-----------------------------------------------------------------------------   
    GPIO_USART2INIT.GPIO_Pin = GPIO_Pin_5;               //PA5 BY2  
    GPIO_USART2INIT.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_USART2INIT);
    GPIO_ResetBits(GPIOA,GPIO_Pin_5);

    GPIO_EXTILineConfig( GPIO_PortSourceGPIOA,  GPIO_PinSource5); 
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line =  EXTI_Line5;
 
      /* EXTI为中断模式 */
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
     /* 上升沿下降沿中断 */
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//EXTI_Trigger_Rising;//EXTI_Trigger_Rising_Falling
    /* 使能中断 */
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 配置NVIC为优先级组1 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* 配置中断源：按键1 */
    NVIC_InitStructure.NVIC_IRQChannel =  EXTI9_5_IRQn;
  /* 配置抢占优先级 */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 配置子优先级 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断通道 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
//-----------------------------------------------------------------------------   
    USART_DeInit(USART2);
    USART2_INIT.USART_BaudRate=9600;
    USART2_INIT.USART_Parity=USART_Parity_No;
    USART2_INIT.USART_WordLength=USART_WordLength_8b;    

    USART2_INIT.USART_StopBits=USART_StopBits_1;
    USART2_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART2_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(USART2,&USART2_INIT);
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);           //使能接收中断
    USART_Cmd(USART2,ENABLE);
//-----------------------------------------------------------------------------
    USART2_NVIC_INIT.NVIC_IRQChannel=USART2_IRQn;
    USART2_NVIC_INIT.NVIC_IRQChannelPreemptionPriority=0;  //主优先级
    USART2_NVIC_INIT.NVIC_IRQChannelSubPriority=0;         //子优先级
    USART2_NVIC_INIT.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&USART2_NVIC_INIT);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;              //TIM4 3.5T的时序管理
//----------------------------------------------------------------------------- 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
//-----------------------------------------------------------------------------
    TIM_DeInit(TIM2);
    /* Time base configuration */    
    TIM_TimeBaseStructure.TIM_Prescaler =(720)-1;                    //72M 500k ,2us
    TIM_TimeBaseStructure.TIM_Period =(200-1);                      // 当定时器从0计数到999，即为1000次，为一个定时周期,1个unit 2us
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;        //设置时钟分频系数：不分频(这里用不到)
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //向上计数模式
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
//-----------------------------------------------------------------------------
    TIM_Cmd(TIM2,ENABLE);                              //开启时钟  

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;       
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;   
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
//-------------------------------------------------------------------------------------------
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);               //清除溢出中断标志  
    TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);  
    TIM_Cmd(TIM2,ENABLE);                              //开启时钟  
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_int8u bsp_ms_pull_uart2_rxd_num(void)
{
    sdt_int8u n_bytes;
    macro_pull_queueBasce_bytes(uart2_queue_rxd,n_bytes);
    return n_bytes;
}

void bsp_look_for_byte_rx_uart2(void)
{
 
    sdt_int8u n_bytes,rd_byte_details;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart2_queue_rxd,n_bytes);
    __enable_interrupt();
    if(n_bytes)
    {
        __disable_interrupt();
        macro_pull_queueBasce_data(uart2_queue_rxd,n_bytes,rd_byte_details);
        __enable_interrupt();
        push_bough_one_receive_byte(bgk_s1,rd_byte_details);     //压入一个字节的数据到link
    }
}
sdt_bool bsp_pull_complete_tx_uart2(void)
{
    sdt_int8u n_bytes;
    
    macro_pull_queueBasce_bytes(uart2_queue_txd,n_bytes);
    if(n_bytes)
    {
        return(sdt_false);
    }
    else
    {
        if(SET==USART_GetITStatus(USART2,USART_IT_TXE))
        {
            return(sdt_false);
        }
        else
        {
            return(sdt_true);
        }      
    }
}
sdt_bool bsp_pull_pyh_busy_uart2(void)
{
    if(phyBusBusyFlag2)
    {
        return(sdt_true);
    }
    return(sdt_false);
}

void bsp_phy_baudrate_calibrate_uart2(void)
{
}

void bsp_entry_phy_rx_uart2(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; 
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}

void bsp_entry_phy_tx_uart2(void)
{
    ;
}
sdt_int16u bsp_transfet_bytes_tx_uart2(sdt_int8u* in_pByte,sdt_int16u in_expect_bytes,sdt_bool in_conflict_check)
{
    if(0 != in_expect_bytes)
    {
        if(in_conflict_check)
        {
            GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; 
			GPIO_Init(GPIOA,&GPIO_InitStructure);
			GPIO_ResetBits(GPIOA,GPIO_Pin_4);//冲突检测，弱上拉发送
        }
        else
        {
             //推挽发送
			GPIO_InitTypeDef GPIO_InitStructure;
			GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;                   //PA15 TRSEL
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz;
			GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;            //推挽输出
			GPIO_Init(GPIOA,&GPIO_InitStructure);
			GPIO_SetBits(GPIOA,GPIO_Pin_4);//推挽发送
        }
        sdt_int8u n_bytes;
        __disable_interrupt();
        macro_pull_queueBasce_bytes(uart2_queue_txd,n_bytes);
        __enable_interrupt();
        sdt_bool queunIsFull;
        macro_pull_queueBasce_full(uart2_queue_txd,n_bytes,queunIsFull);
        if(queunIsFull)
        {
            return(sdt_false);
        }
        else
        {
            __disable_interrupt();
            macro_push_queueBasce_data(uart2_queue_txd,n_bytes,in_pByte[0]);
                __enable_interrupt();
            USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
            return(in_expect_bytes-1);                              
        }     
    }
    return(0);
}
//sdt_bool bsp_ms_pull_uart2_txd_cmp(void)
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
//        if(SET==USART_GetITStatus(USART2,USART_IT_TXE))
//        {
//            return(sdt_false);
//        }
//        else
//        {
//            return(sdt_true);
//        }      
//    }
//}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_uart2_phyReCfg(sdt_int32u sys_fre,sdt_int32u baud_rate,sdt_int8u parity,sdt_int8u stop_bits)
{
    USART_InitTypeDef   USART2_INIT;

    USART_DeInit(USART2);
    USART2_INIT.USART_BaudRate=9600;
    USART2_INIT.USART_Parity=USART_Parity_No;
    USART2_INIT.USART_WordLength=USART_WordLength_8b;    

    USART2_INIT.USART_StopBits=USART_StopBits_1;
    USART2_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART2_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(USART2,&USART2_INIT);
}
//tr_select  PB1
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//input floating

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
