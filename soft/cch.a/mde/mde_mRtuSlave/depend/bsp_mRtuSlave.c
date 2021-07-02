//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "stm32f10x.h"
#include ".\snail_macro.h"
#include ".\snail_data_types.h"
#include "..\..\mde_bough_link\mde_bough_link_half.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*波特率、奇偶校验位设置*/
/*串口0*/
//uart0 txd--Pb6  rxd--Pb7   trol pb5
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_creat_queueBasce(uart4_queue_rxd,64);
macro_creat_queueBasce(uart4_queue_txd,255);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//中断服务函数
//-----------------------------------------------------------------------------
void USART0_IRQHandler(void)
{
    if((RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_ERR_ORERR)) && 
       (RESET != usart_flag_get(USART0, USART_FLAG_RBNE)))
    {
        /* receive data */
         usart_data_receive(USART0);
    }
    else if((RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_ERR_NERR)) && 
       (RESET != usart_flag_get(USART0, USART_FLAG_RBNE)))
    {
        /* receive data */
         usart_data_receive(USART0);
    }
    else if((RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_ERR_FERR)) && 
       (RESET != usart_flag_get(USART0, USART_FLAG_RBNE)))
    {
        /* receive data */
        usart_data_receive(USART0); 
    }
    else if((RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_PERR)) && 
       (RESET != usart_flag_get(USART0, USART_FLAG_RBNE)))
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
        macro_pull_queueBasce_bytes(uart4_queue_rxd,n_bytes);

        sdt_bool queunIsFull;
        macro_pull_queueBasce_full(uart4_queue_rxd,n_bytes,queunIsFull);
        if(queunIsFull)
        {
        }
        else
        {
            macro_push_queueBasce_data(uart4_queue_rxd,n_bytes,Read_reg);
        } 
    }
    if((RESET != usart_flag_get(USART0, USART_FLAG_TBE)) && 
       (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_TBE)))
    {          
        /* transmit data */
        sdt_int8u n_bytes,rd_byte_details;
        macro_pull_queueBasce_bytes(uart4_queue_txd,n_bytes);
        if(n_bytes)
        {
            macro_pull_queueBasce_data(uart4_queue_txd,n_bytes,rd_byte_details);
            usart_data_transmit(USART0,rd_byte_details);
        }
        else
        {
            usart_interrupt_disable(USART0, USART_INT_TBE);
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
    rcu_periph_clock_enable( RCU_GPIOB);
     /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);
     /* connect port to USARTx_Tx */
    gpio_af_set(GPIOA, EVAL_COM0_AF, GPIO_PIN_10);

    /* connect port to USARTx_Rx */
    gpio_af_set(GPIOA, EVAL_COM0_AF,GPIO_PIN_10);

    /* configure USART Tx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_10);

    /* configure USART Rx as alternate function push-pull */
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_10);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_10);

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
    usart_interrupt_enable(USART0, USART_INT_TBE);
    usart_interrupt_enable(USART0, USART_INT_RBNE);
}

void bsp_timer1_cfg(void)
{
    /* ---------------------------------------------------------------
    TIMER1 Configuration: 
    TIMER1CLK = SystemCoreClock / 336 = 500K,
    --------------------------------------------------------------- */
    timer_oc_parameter_struct timer_ocintpara;
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
sdt_bool bsp_pull_oneByte_uart4_rxd(sdt_int8u* out_byte_details)
{
    sdt_int8u n_bytes,rd_byte_details;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart4_queue_rxd,n_bytes);
    __enable_interrupt();
    if(n_bytes)
    {
        __disable_interrupt();
        macro_pull_queueBasce_data(uart4_queue_rxd,n_bytes,rd_byte_details);
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
sdt_bool bsp_push_oneByte_uart4_txd(sdt_int8u in_byte_details)
{
    sdt_int8u n_bytes;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart4_queue_txd,n_bytes);
    __enable_interrupt();
    sdt_bool queunIsFull;
    macro_pull_queueBasce_full(uart4_queue_txd,n_bytes,queunIsFull);
    if(queunIsFull)
    {
        return(sdt_false);
    }
    else
    {
        __disable_interrupt();
        macro_push_queueBasce_data(uart4_queue_txd,n_bytes,in_byte_details);
        __enable_interrupt();
        USART_ITConfig(UART4,USART_IT_TXE,ENABLE);
        return(sdt_true);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
sdt_bool bsp_uart4_busFree(sdt_int8u t_char_dis)
{
    //static sdt_int16u rd_rxd_depart_cnt;
    static  sdt_int16u rd_cnt;
    static  sdt_int16u free_cnt;

    rd_cnt = TIM3->CNT;
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
void bsp_restart_tim3(void)
{
   TIM3->CNT = 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool bsp_pull_uart4_txd_cmp(void)
{
    sdt_int8u n_bytes;
    
    macro_pull_queueBasce_bytes(uart4_queue_txd,n_bytes);
    if(n_bytes)
    {
        return(sdt_false);
    }
    else
    {
        if(SET==USART_GetITStatus(UART4,USART_IT_TXE))
        {
            return(sdt_false);
        }
        else
        {
            return(sdt_true);
        }      
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart4_into_receive(void)
{
    USART_ITConfig(UART4,USART_IT_RXNE,ENABLE); 
    GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart4_into_transmit(void)
{
    USART_ITConfig(UART4,USART_IT_RXNE,DISABLE); 
    GPIO_SetBits(GPIOB,GPIO_Pin_13);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_uart_phyReCfg(sdt_int32u sys_fre,sdt_int32u baud_rate,sdt_int8u parity,sdt_int8u stop_bits)
{
    //static sdt_int32u bak_sys_fre = 0,bak_baud_rate = 0;
    //static sdt_int8u bak_parity = 0,bak_stop_bits = 0;
    USART_InitTypeDef   USART4_INIT;

    USART_DeInit(UART4);
    USART4_INIT.USART_BaudRate=9600;
    USART4_INIT.USART_Parity=USART_Parity_No;
    USART4_INIT.USART_WordLength=USART_WordLength_8b;    

    USART4_INIT.USART_StopBits=USART_StopBits_1;
    USART4_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART4_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(UART4,&USART4_INIT);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void get_queue_data(sdt_int8u* out_inx,sdt_int8u* out_otx,sdt_int8u* out_nbyte)
{
    __disable_interrupt();
    *out_inx = uart4_queue_rxd_in_idx;
    *out_otx = uart4_queue_rxd_out_idx;
    *out_nbyte = uart4_queue_rxd_bytes;
    __enable_interrupt();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*串口1*/
//uart1 txd--PA9  rxd--PA10   trol PA8
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*串口1配置*/
macro_creat_queueBasce(uart1_queue_rxd,64);
macro_creat_queueBasce(uart1_queue_txd,255);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//中断服务函数
//void DMA1_Channel4_IRQHandler(void)
//{
//	if(DMA_GetITStatus(DMA1_IT_TC4)==SET)
//	{
//		DMA_ClearITPendingBit(DMA1_IT_TC4);
//	}	
//}
//-----------------------------------------------------------------------------
void USART1_IRQHandler(void)
{
    if((SET==USART_GetFlagStatus(USART1,USART_FLAG_ORE))||\
       (SET==USART_GetFlagStatus(USART1,USART_FLAG_NE))||\
       (SET==USART_GetFlagStatus(USART1,USART_FLAG_FE)))
    {
        USART_GetFlagStatus(USART1,USART_FLAG_ORE);
        USART_ReceiveData(USART1);
    }
    else if(SET==USART_GetFlagStatus(USART1,USART_FLAG_PE))
    {
        USART_GetFlagStatus(USART1,USART_FLAG_PE);
        USART_ReceiveData(USART1);
    }
    else if(SET==USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
    {
        sdt_int8u Read_reg;
        Read_reg = USART_ReceiveData(USART1);
       
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
    if(SET==USART_GetITStatus(USART1,USART_IT_TXE))
    {
        if(SET==USART_GetFlagStatus(USART1,USART_FLAG_TXE))
        {
            sdt_int8u n_bytes,rd_byte_details;
            macro_pull_queueBasce_bytes(uart1_queue_txd,n_bytes);
            if(n_bytes)
            {
                macro_pull_queueBasce_data(uart1_queue_txd,n_bytes,rd_byte_details);
                USART_SendData(USART1,rd_byte_details);
            }
            else
            {
                USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
            }
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
void bsp_uart1_cfg(void)
{
    GPIO_InitTypeDef    GPIO_USART1INIT; 
    USART_InitTypeDef   USART1_INIT;
    NVIC_InitTypeDef    USART1_NVIC_INIT;

 //-----------------------------------------------------------------------------   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);  //开启串口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //开启GPIOA口时钟
//-----------------------------------------------------------------------------  
    GPIO_USART1INIT.GPIO_Pin=GPIO_Pin_9;                   //PA9 U1_TXD
    GPIO_USART1INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART1INIT.GPIO_Mode=GPIO_Mode_AF_PP;            //输出复用推挽
    GPIO_Init(GPIOA,&GPIO_USART1INIT);
    GPIO_SetBits(GPIOA,GPIO_Pin_9);
//-----------------------------------------------------------------------------     
    GPIO_USART1INIT.GPIO_Pin=GPIO_Pin_10;                  //PA10 U1_RXD
    GPIO_USART1INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART1INIT.GPIO_Mode=GPIO_Mode_IPU;               //输入上拉
    GPIO_Init(GPIOA,&GPIO_USART1INIT);
//-----------------------------------------------------------------------------  
    GPIO_USART1INIT.GPIO_Pin=GPIO_Pin_8;                   //PA8 U1_CTROL
    GPIO_USART1INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART1INIT.GPIO_Mode=GPIO_Mode_Out_PP;            //输出推挽
    GPIO_Init(GPIOA,&GPIO_USART1INIT);
    GPIO_ResetBits(GPIOA,GPIO_Pin_8);
//-----------------------------------------------------------------------------   
    USART_DeInit(USART1);
    USART1_INIT.USART_BaudRate=9600;
    USART1_INIT.USART_Parity=USART_Parity_No;
    USART1_INIT.USART_WordLength=USART_WordLength_8b;    

    USART1_INIT.USART_StopBits=USART_StopBits_1;
    USART1_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART1_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(USART1,&USART1_INIT);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);           //使能接收中断
    USART_ITConfig(USART1,USART_IT_PE,ENABLE);           //奇偶校验中断
    USART_Cmd(USART1,ENABLE);
   // USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);// 采用空闲中断，目的是在产生空闲中断时，说明接收或者发送已经结束，此时可以读取DMA中的数据了。
//-----------------------------------------------------------------------------
    USART1_NVIC_INIT.NVIC_IRQChannel=USART1_IRQn;
    USART1_NVIC_INIT.NVIC_IRQChannelPreemptionPriority=0;  //主优先级
    USART1_NVIC_INIT.NVIC_IRQChannelSubPriority=0;         //子优先级
    USART1_NVIC_INIT.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&USART1_NVIC_INIT);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;              //TIM1 3.5T的时序管理
//----------------------------------------------------------------------------- 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); 
//-----------------------------------------------------------------------------
    TIM_DeInit(TIM6);
    /* Time base configuration */    
    TIM_TimeBaseStructure.TIM_Prescaler =(72*2)-1;                    //72M 500k ,2us
    TIM_TimeBaseStructure.TIM_Period =0xffff;                      // 当定时器从0计数到999，即为1000次，为一个定时周期,1个unit 2us
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;        //设置时钟分频系数：不分频(这里用不到)
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //向上计数模式
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
//-----------------------------------------------------------------------------
    TIM_Cmd(TIM6,ENABLE);                              //开启时钟  
}

//u8 sendbuf[2];
//u8 receivebuf[2];
//void _uart1_dma_configuration()
//{
//    DMA_InitTypeDef DMA_InitStructure;
//
//    /* DMA1 Channel6 (triggered by USART1 Rx event) Config */
//    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 ,ENABLE);
//
//    /* DMA1 Channel5 (triggered by USART1 Rx event) Config */
//    DMA_DeInit(DMA1_Channel5);
//    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);// 初始化外设地址 
//    DMA_InitStructure.DMA_MemoryBaseAddr =(u32)receivebuf;// 内存地址，
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//外设作为数据来源，
//    DMA_InitStructure.DMA_BufferSize = 10 ;// 缓存容量
//    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; // 外设地址不递增，即柜子对应的快递不变
//    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;// 内存递增
//    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //外设字节宽度，即快递运输快件大小度量（按重量算，还是按体积算） 
//    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;// 内存字节宽度，即店主封装快递的度量(按重量，还是按体质进行封装)
//    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// 正常模式，即满了就不在接收了，而不是循环存储
//    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;// 优先级很高，对应快递就是加急
//    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; // 内存与外设通信，而非内存到内存 
//    DMA_Init(DMA1_Channel5, &DMA_InitStructure);// 把参数初始化，即拟好与快递公司的协议
//
//    DMA_Cmd(DMA1_Channel5, ENABLE);// 启动DMA，即与快递公司签订合同，正式生效
//
//    /* DMA1 Channel4 (triggered by USART1 Tx event) Config */
//    DMA_DeInit(DMA1_Channel4);
//    DMA_InitStructure.DMA_PeripheralBaseAddr =  (uint32_t)(&USART1->DR);  // 外设地址，串口1， 
//    DMA_InitStructure.DMA_MemoryBaseAddr =(u32)sendbuf;// 发送内存地址
//    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;// 外设为传送数据目的地，即发送数据，
//    DMA_InitStructure.DMA_BufferSize = 0;  //发送长度为0
//    DMA_Init(DMA1_Channel4, &DMA_InitStructure);//初始化
//   // DMA_ITConfig(DMA1_Channel4,DMA_IT_TC, ENABLE);//使能DMA传输完成通道
//    USART_ITConfig(USART1, USART_IT_TC, ENABLE);// 使能串口发送完成中断
//    USART_DMACmd(USART1, USART_DMAReq_Tx|USART_DMAReq_Rx, ENABLE);// 使能DMA串口发送和接受请求
//}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:获取一个字节的接收数据
//out: sdt_true 获取成功，sdt_falas 获取失败
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_oneByte_uart1_rxd(sdt_int8u* out_byte_details)
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
        *out_byte_details = rd_byte_details;
       // push_bough_one_receive_byte(0,rd_byte_details);
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
sdt_bool bsp_push_oneByte_uart1_txd(sdt_int8u in_byte_details)
{
    sdt_int8u n_bytes;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart1_queue_txd,n_bytes);
    __enable_interrupt();
    sdt_bool queunIsFull;
    macro_pull_queueBasce_full(uart1_queue_txd,n_bytes,queunIsFull);
    if(queunIsFull)
    {
        return(sdt_false);
    }
    else
    {
        __disable_interrupt();
        macro_push_queueBasce_data(uart1_queue_txd,n_bytes,in_byte_details);
        __enable_interrupt();
        USART_ITConfig(USART1,USART_IT_TXE,ENABLE);
        return(sdt_true);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
sdt_bool bsp_uart1_busFree(sdt_int8u t_char_dis)
{
    static  sdt_int16u rd_cnt;
    static  sdt_int16u free_cnt;

    rd_cnt = TIM6->CNT;
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
void bsp_restart_tim6(void)
{
   TIM6->CNT = 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool bsp_pull_uart1_txd_cmp(void)
{
    sdt_int8u n_bytes;
    
    macro_pull_queueBasce_bytes(uart1_queue_txd,n_bytes);
    if(n_bytes)
    {
        return(sdt_false);
    }
    else
    {
        if(SET==USART_GetITStatus(USART1,USART_IT_TXE))
        {
            return(sdt_false);
        }
        else
        {
            return(sdt_true);
        }      
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart1_into_receive(void)
{
    
    GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart1_into_transmit(void)
{
    
    GPIO_SetBits(GPIOA,GPIO_Pin_8);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_uart1_phyReCfg(sdt_int8u baud_rate,sdt_int8u parity)
{
    USART_InitTypeDef   USART1_INIT;
    USART_DeInit(USART1);
   // USART1_INIT.USART_BaudRate=baud_rate;
  //  USART1_INIT.USART_Parity=USART_Parity_No;
  //  USART1_INIT.USART_WordLength=USART_WordLength_8b;    
    switch(baud_rate)
    {
        case 0x02:
        {
            USART1_INIT.USART_BaudRate=9600;
            break;
        }
        case 0x01:
        {
            USART1_INIT.USART_BaudRate = 4800;
            break;
        }
        case 0x00:
        {
            USART1_INIT.USART_BaudRate = 2400;
            break;
        }
        case 0x03:
        {
            USART1_INIT.USART_BaudRate = 19200;
            break;
        }
        default:
        {
            USART1_INIT.USART_BaudRate = 9600;
            break;
        }
    }
    switch(parity)
    {
        case 0x00 : 
        {
            USART1_INIT.USART_WordLength = USART_WordLength_8b;
            USART1_INIT.USART_Parity     = USART_Parity_No;
            break;
        }
        case  0x01:
        {
            USART1_INIT.USART_WordLength = USART_WordLength_9b;
            USART1_INIT.USART_Parity     = USART_Parity_Odd;
            break;
        }
        case  0x02:
        {
            USART1_INIT.USART_WordLength = USART_WordLength_9b;
            USART1_INIT.USART_Parity = USART_Parity_Even;
            break;
        }
        default:
        {
            USART1_INIT.USART_WordLength = USART_WordLength_8b;
            USART1_INIT.USART_Parity     = USART_Parity_No;
            break;
        }
    }     
    USART1_INIT.USART_StopBits=USART_StopBits_1;
    USART1_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART1_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(USART1,&USART1_INIT);
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);           //使能接收中断
    USART_ITConfig(USART1,USART_IT_PE,ENABLE);           //奇偶校验中断
    USART_Cmd(USART1,ENABLE);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void get_queue1_data(sdt_int8u* out_inx,sdt_int8u* out_otx,sdt_int8u* out_nbyte)
{
    __disable_interrupt();
    *out_inx = uart1_queue_rxd_in_idx;
    *out_otx = uart1_queue_rxd_out_idx;
    *out_nbyte = uart1_queue_rxd_bytes;
    __enable_interrupt();
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*串口3*/
//uart3 txd--PB10  rxd--PB11  TROL--PB12
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*串口3配置*/
macro_creat_queueBasce(uart3_queue_rxd,100);
macro_creat_queueBasce(uart3_queue_txd,255);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//中断服务函数
//-----------------------------------------------------------------------------
void USART3_IRQHandler(void)
{
    if((SET==USART_GetFlagStatus(USART3,USART_FLAG_ORE))||\
       (SET==USART_GetFlagStatus(USART3,USART_FLAG_NE))||\
       (SET==USART_GetFlagStatus(USART3,USART_FLAG_FE)))
    {
        USART_GetFlagStatus(USART3,USART_FLAG_ORE);
        USART_ReceiveData(USART3);
    }
    else if(SET==USART_GetFlagStatus(USART3,USART_FLAG_PE))
    {
        USART_GetFlagStatus(USART3,USART_FLAG_PE);
        USART_ReceiveData(USART3);
    }
    else if(SET==USART_GetFlagStatus(USART3,USART_FLAG_RXNE))
    {
        sdt_int8u Read_reg;
        Read_reg = USART_ReceiveData(USART3);
       
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
    if(SET==USART_GetITStatus(USART3,USART_IT_TXE))
    {
        if(SET==USART_GetFlagStatus(USART3,USART_FLAG_TXE))
        {
            sdt_int8u n_bytes,rd_byte_details;
            macro_pull_queueBasce_bytes(uart3_queue_txd,n_bytes);
            if(n_bytes)
            {
                macro_pull_queueBasce_data(uart3_queue_txd,n_bytes,rd_byte_details);
                USART_SendData(USART3,rd_byte_details);
            }
            else
            {
                USART_ITConfig(USART3,USART_IT_TXE,DISABLE);
            }
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++interface++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
void bsp_uart3_cfg(void)
{
    GPIO_InitTypeDef    GPIO_USART3INIT; 
    USART_InitTypeDef   USART3_INIT;
    NVIC_InitTypeDef    USART3_NVIC_INIT;

 //-----------------------------------------------------------------------------   
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);  //开启串口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //开启GPIOB口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//-----------------------------------------------------------------------------  
    GPIO_USART3INIT.GPIO_Pin=GPIO_Pin_10;                   //PB10 U3_TXD
    GPIO_USART3INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART3INIT.GPIO_Mode=GPIO_Mode_AF_PP;            //输出复用推挽
    GPIO_Init(GPIOB,&GPIO_USART3INIT);
    GPIO_SetBits(GPIOB,GPIO_Pin_10);
//-----------------------------------------------------------------------------     
    GPIO_USART3INIT.GPIO_Pin=GPIO_Pin_11;                  //PB11 U3_RXD
    GPIO_USART3INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART3INIT.GPIO_Mode=GPIO_Mode_IPU;               //输入上拉
    GPIO_Init(GPIOB,&GPIO_USART3INIT);
//-----------------------------------------------------------------------------  
    GPIO_USART3INIT.GPIO_Pin=GPIO_Pin_12;                   //PB12 U3_CTROL
    GPIO_USART3INIT.GPIO_Speed=GPIO_Speed_2MHz;
    GPIO_USART3INIT.GPIO_Mode=GPIO_Mode_Out_PP;            //输出推挽
    GPIO_Init(GPIOB,&GPIO_USART3INIT);
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);

//-----------------------------------------------------------------------------   
    USART_DeInit(USART3);
    USART3_INIT.USART_BaudRate=9600;
    USART3_INIT.USART_Parity=USART_Parity_No;
    USART3_INIT.USART_WordLength=USART_WordLength_8b;    

    USART3_INIT.USART_StopBits=USART_StopBits_1;
    USART3_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART3_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(USART3,&USART3_INIT);
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);           //使能接收中断
    USART_Cmd(USART3,ENABLE);
//-----------------------------------------------------------------------------
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    USART3_NVIC_INIT.NVIC_IRQChannel=USART3_IRQn;
    USART3_NVIC_INIT.NVIC_IRQChannelPreemptionPriority=0;  //主优先级
    USART3_NVIC_INIT.NVIC_IRQChannelSubPriority=0;         //子优先级
    USART3_NVIC_INIT.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&USART3_NVIC_INIT);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;              //TIM3 3.5T的时序管理
//----------------------------------------------------------------------------- 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 
//-----------------------------------------------------------------------------
    TIM_DeInit(TIM4);
    /* Time base configuration */    
    TIM_TimeBaseStructure.TIM_Prescaler =(72*2)-1;                    //72M 500k ,2us
    TIM_TimeBaseStructure.TIM_Period =0xffff;                      // 当定时器从0计数到999，即为1000次，为一个定时周期,1个unit 2us
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;        //设置时钟分频系数：不分频(这里用不到)
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;     //向上计数模式
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
//-----------------------------------------------------------------------------
    TIM_Cmd(TIM4,ENABLE);                              //开启时钟  
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name:获取一个字节的接收数据
//out: sdt_true 获取成功，sdt_falas 获取失败
//-----------------------------------------------------------------------------
sdt_bool bsp_pull_oneByte_uart3_rxd(sdt_int8u* out_byte_details)
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
        *out_byte_details = rd_byte_details;
      //  push_bough_one_receive_byte(0,rd_byte_details);
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
sdt_bool bsp_push_oneByte_uart3_txd(sdt_int8u in_byte_details)
{
    sdt_int8u n_bytes;
    __disable_interrupt();
    macro_pull_queueBasce_bytes(uart3_queue_txd,n_bytes);
    __enable_interrupt();
    sdt_bool queunIsFull;
    macro_pull_queueBasce_full(uart3_queue_txd,n_bytes,queunIsFull);
    if(queunIsFull)
    {
        return(sdt_false);
    }
    else
    {
        __disable_interrupt();
        macro_push_queueBasce_data(uart3_queue_txd,n_bytes,in_byte_details);
        __enable_interrupt();
        USART_ITConfig(USART3,USART_IT_TXE,ENABLE);
        return(sdt_true);
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
sdt_bool bsp_uart3_busFree(sdt_int8u t_char_dis)
{
    static  sdt_int16u rd_cnt;
    static  sdt_int16u free_cnt;

    rd_cnt = TIM4->CNT;
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
void bsp_restart_tim4(void)
{
   TIM4->CNT = 0;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
sdt_bool bsp_pull_uart3_txd_cmp(void)
{
    sdt_int8u n_bytes;
    
    macro_pull_queueBasce_bytes(uart3_queue_txd,n_bytes);
    if(n_bytes)
    {
        return(sdt_false);
    }
    else
    {
        if(SET==USART_GetITStatus(USART3,USART_IT_TXE))
        {
            return(sdt_false);
        }
        else
        {
            return(sdt_true);
        }      
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart3_into_receive(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bps_uart3_into_transmit(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_12);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_uart3_phyReCfg(sdt_int32u sys_fre,sdt_int32u baud_rate,sdt_int8u parity,sdt_int8u stop_bits)
{
    USART_InitTypeDef   USART3_INIT;
    USART_DeInit(USART3);
    USART3_INIT.USART_BaudRate=9600;
    USART3_INIT.USART_Parity=USART_Parity_No;
    USART3_INIT.USART_WordLength=USART_WordLength_8b;    

    USART3_INIT.USART_StopBits=USART_StopBits_1;
    USART3_INIT.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART3_INIT.USART_Mode=(USART_Mode_Rx+USART_Mode_Tx);  //收发使能
//-----------------------------------------------------------------------------
    USART_Init(USART3,&USART3_INIT);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void get_queue3_data(sdt_int8u* out_inx,sdt_int8u* out_otx,sdt_int8u* out_nbyte)
{
    __disable_interrupt();
    *out_inx = uart3_queue_rxd_in_idx;
    *out_otx = uart3_queue_rxd_out_idx;
    *out_nbyte = uart3_queue_rxd_bytes;
    __enable_interrupt();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++