//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include "gd32f4xx.h"
#include <stdbool.h>
//------------------------------E N D-------------------------------------------
#define LED1_PORT     GPIOC       //左边GPIO
#define LED1_PIN      GPIO_PIN_0

void bsp_led1_config(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOC);
     /* configure led GPIO port */ 
    gpio_mode_set(LED1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,LED1_PIN);
    gpio_output_options_set(LED1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,LED1_PIN);
    
    GPIO_BOP(LED1_PORT) = LED1_PIN;
}


void BSP_Led1_Enable(void)
{
    GPIO_BC(LED1_PORT) = LED1_PIN;
}

void BSP_Led1_Disable(void)
{
    GPIO_BOP(LED1_PORT) = LED1_PIN;
}
//-----------------------BSP_LED.c--END-----------------------------------
