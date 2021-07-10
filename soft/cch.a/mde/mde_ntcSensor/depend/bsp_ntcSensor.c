#include ".\BSP_ntcSensor.h"
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***************************内部变量定义***************************************
 //宏定义NTC IO管脚寄存器宏定义
#define NTC1_PIN                            GPIO_PIN_0
#define NTC1_GPIO_PORT                      GPIOA

#define NTC2_PIN                            GPIO_PIN_2
#define NTC2_GPIO_PORT                      GPIOA

#define NTC3_PIN                            GPIO_PIN_3
#define NTC3_GPIO_PORT                      GPIOA

#define NTC4_PIN                            GPIO_PIN_1
#define NTC4_GPIO_PORT                      GPIOA

/*#define NTC5_PIN                            GPIO_Pin_0
#define NTC5_GPIO_PORT                      GPIOA

#define NTC6_PIN                            GPIO_Pin_1
#define NTC6_GPIO_PORT                      GPIOA

#define NTC7_PIN                            GPIO_Pin_6
#define NTC7_GPIO_PORT                      GPIOA*/
//------------------------------E N D-------------------------------------------

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***************************PC4口宏定义****************************************
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//**********************ADC_IO口配置为浮空输入**********************************
void BSP_ADC_Hardware_Configure(void)
{
      /* enable GPIOA clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    /* enable ADC clock */
    rcu_periph_clock_enable(RCU_ADC0);
    adc_clock_config(ADC_ADCCK_PCLK2_DIV6);
     /* config the GPIO as analog mode, for ADC */
    gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE,NTC1_PIN | NTC2_PIN | NTC3_PIN | NTC4_PIN);     
}
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***************************ADC软件配置****************************************
void BSP_ADC_Software_Configure(void)
{
    BSP_ADC_Hardware_Configure();
    adc_deinit();
    /* ADC mode config */
    adc_sync_mode_config(ADC_SYNC_MODE_INDEPENDENT);
    adc_resolution_config(ADC0,ADC_RESOLUTION_12B);
    /* ADC data alignment config */
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
     /* ADC SCAN function enable */
    adc_special_function_config(ADC0,ADC_SCAN_MODE,DISABLE);
    /* ADC external trigger enable */
    adc_external_trigger_config(ADC1,ADC_REGULAR_CHANNEL,EXTERNAL_TRIGGER_DISABLE);
    /* ADC channel length config */
    adc_channel_length_config(ADC0,ADC_REGULAR_CHANNEL,1);
     /* ADC discontinuous mode */
    adc_discontinuous_mode_config(ADC0, ADC_REGULAR_CHANNEL, 1);
     /* clear the ADC flag */
    adc_interrupt_flag_clear(ADC0, ADC_INT_FLAG_EOC);
         /* ADC regular channel config */
    adc_regular_channel_config(ADC0,0,ADC_CHANNEL_0,ADC_SAMPLETIME_15);

    adc_software_trigger_enable(ADC0,ADC_REGULAR_CHANNEL);
    adc_end_of_conversion_config(ADC0,ADC_EOC_SET_CONVERSION);
     /* enable ADC interface */
    adc_enable(ADC0);
     /* ADC calibration and reset calibration */
    adc_calibration_enable(ADC0);
}
//------------------------------E N D-------------------------------------------



//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//*************************ADC初始化配置****************************************
void BSP_ADC_Configure(void)
{
    BSP_ADC_Hardware_Configure();
    BSP_ADC_Software_Configure();
}
//------------------------------E N D-------------------------------------------



//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***************************ADC通道选择****************************************
//Function
//名称:  获取单次ADC值
//功能:  
//入口:  无
//出口:  INT16U 的ADC值
 
//------------------------------E N D-------------------------------------------
uint16_t BSP_ADC1_GetValue(void)
{
    uint16_t value;
    value = adc_regular_data_read(ADC0);
    return(value);
}

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***************************ADC开启转换****************************************
void BSP_ADC12_Start(void)
{
    adc_software_trigger_enable(ADC0,ADC_REGULAR_CHANNEL);
}
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***********************读取单次转换完成事件***********************************
 

bool BSP_ADC1_SampleOnceFinish(void)
{
    if(SET == adc_flag_get(ADC0,ADC_FLAG_EOC))
    {
        return true;
    }
    return false;
}
//------------------------------E N D-------------------------------------------
void BSP_ADC_ChannalSelect(uint8_t _In_Channel)
{
    //ADC_RegularChannelConfig(ADC1,_In_Channel,1,ADC_SampleTime_55Cycles5);
}


void BSP_ADC_Channal_one(void)
{
    adc_regular_channel_config(ADC0,0,ADC_CHANNEL_0,ADC_SAMPLETIME_15);
}

void BSP_ADC_Channal_two(void)
{
    adc_regular_channel_config(ADC0,0,ADC_CHANNEL_2,ADC_SAMPLETIME_15);
}
void BSP_ADC_Channal_three(void)
{
    adc_regular_channel_config(ADC0,0,ADC_CHANNEL_3,ADC_SAMPLETIME_15);
}

void BSP_ADC_Channal_four(void)
{
    adc_regular_channel_config(ADC0,0,ADC_CHANNEL_1,ADC_SAMPLETIME_15);
}
/*void BSP_ADC_Channal_five(void)
{
    BSP_ADC_ChannalSelect(ADC_Channel_0);
}

void BSP_ADC_Channal_six(void)
{
    BSP_ADC_ChannalSelect(ADC_Channel_1);
}

void BSP_ADC_Channal_seven(void)
{
    BSP_ADC_ChannalSelect(ADC_Channel_6);
}*/