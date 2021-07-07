//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "gd32f4xx.h"
#include "intrinsics.h"
#include ".\bsp_pwm.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//PA9   TIM0_CH1  
//PA8   TIM0_CH0 
//PC9   TIM7_CH3
#define T0_CH1_PORT     GPIOA        
#define T0_CH1_PIN      GPIO_PIN_9

#define T0_CH0_PORT     GPIOA        
#define T0_CH0_PIN      GPIO_PIN_8
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define PWM_FREQENCY   500
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void TIM0CH0_Loading_PwmDutyOut(INT8U PwmData)
{
    if(PwmData>100)
    {
        PwmData=100;
    }
   // PwmData=100-PwmData;
    timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,(PwmData * PWM_FREQENCY )/100);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void TIM0CH1_Loading_PwmDutyOut(INT8U PwmData)
{
    if(PwmData>100)
    {
        PwmData=100;
    }
   // PwmData=100-PwmData;
    timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,(PwmData * PWM_FREQENCY )/100);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*void TIM8CH3_Loading_PwmDutyOut(INT8U PwmData)
{
    if(PwmData>100)
    {
        PwmData=100;
    }
    PwmData=100-PwmData;
    TIM_SetCompare3(TIM8,(PwmData * PWM_FREQENCY )/100);
}*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void PwmControl_Configure(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_GPIOC);
    
    /*Configure PB3 PB10 PB11(TIMER1 CH1 CH2 CH3) as alternate function*/
    gpio_mode_set(T0_CH1_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, T0_CH1_PIN);
    gpio_output_options_set(T0_CH1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,T0_CH1_PIN);

    gpio_mode_set(T0_CH0_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, T0_CH0_PIN);
    gpio_output_options_set(T0_CH0_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,T0_CH0_PIN);

    gpio_af_set(T0_CH1_PORT, GPIO_AF_1, T0_CH1_PIN);
    gpio_af_set(T0_CH0_PORT, GPIO_AF_1, T0_CH0_PIN);
        /* -----------------------------------------------------------------------
    TIMER1 configuration: generate 3 PWM signals with 3 different duty cycles:
    TIMER1CLK = SystemCoreClock / 200 = 1MHz

    TIMER1 channel1 duty cycle = (4000/ 16000)* 100  = 25%
    TIMER1 channel2 duty cycle = (8000/ 16000)* 100  = 50%
    TIMER1 channel3 duty cycle = (12000/ 16000)* 100 = 75%
    ----------------------------------------------------------------------- */
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_TIMER0);
    rcu_timer_clock_prescaler_config(RCU_TIMER_PSC_MUL4);

    timer_deinit(TIMER0);

    /* TIMER1 configuration */
    timer_initpara.prescaler         = 167;
    timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    timer_initpara.period            = (PWM_FREQENCY-1);
    timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER0,&timer_initpara);

    /* CH1,CH2 and CH3 configuration in PWM mode */
    timer_ocintpara.ocpolarity  = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
    timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    timer_channel_output_config(TIMER0,TIMER_CH_0,&timer_ocintpara);
    timer_channel_output_config(TIMER0,TIMER_CH_1,&timer_ocintpara);

    /* CH0 configuration in PWM mode1,duty cycle 25% */
    timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_0,0);
    timer_channel_output_mode_config(TIMER0,TIMER_CH_0,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER0,TIMER_CH_0,TIMER_OC_SHADOW_DISABLE);

    /* CH2 configuration in PWM mode1,duty cycle 50% */
    timer_channel_output_pulse_value_config(TIMER0,TIMER_CH_1,0);
    timer_channel_output_mode_config(TIMER0,TIMER_CH_1,TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER0,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);
    /* auto-reload preload enable */
    timer_auto_reload_shadow_enable(TIMER0);
    /* auto-reload preload enable */
    timer_enable(TIMER0);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++