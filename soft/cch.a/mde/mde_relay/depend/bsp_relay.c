//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include "gd32f4xx.h"
#include <stdbool.h>
//------------------------------E N D-------------------------------------------
#define RELAY1_PORT     GPIOB       
#define RELAY1_PIN      GPIO_PIN_11

#define RELAY2_PORT     GPIOB      
#define RELAY2_PIN      GPIO_PIN_10

#define RELAY3_PORT     GPIOE       
#define RELAY3_PIN      GPIO_PIN_15

#define RELAY4_PORT     GPIOE       
#define RELAY4_PIN      GPIO_PIN_14

#define RELAY5_PORT     GPIOE       
#define RELAY5_PIN      GPIO_PIN_13

#define RELAY6_PORT     GPIOE      
#define RELAY6_PIN      GPIO_PIN_12

#define RELAY7_PORT     GPIOD       
#define RELAY7_PIN      GPIO_PIN_13

#define RELAY8_PORT     GPIOD       
#define RELAY8_PIN      GPIO_PIN_14

#define RELAY9_PORT     GPIOD       
#define RELAY9_PIN      GPIO_PIN_15

#define RELAY10_PORT     GPIOC       
#define RELAY10_PIN      GPIO_PIN_6

#define RELAY11_PORT     GPIOC       
#define RELAY11_PIN      GPIO_PIN_7

#define RELAY12_PORT     GPIOC       
#define RELAY12_PIN      GPIO_PIN_8

#define RELAY13_PORT     GPIOE       
#define RELAY13_PIN      GPIO_PIN_10

#define RELAY14_PORT     GPIOE       
#define RELAY14_PIN      GPIO_PIN_9

#define RELAY15_PORT     GPIOE       
#define RELAY15_PIN      GPIO_PIN_11

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++ 
void bsp_relay_config(void)
{
    /* enable the RELAY clock */
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOC);
    rcu_periph_clock_enable(RCU_GPIOD);
    rcu_periph_clock_enable(RCU_GPIOE);
     /* configure RELAY GPIO port */ 
    gpio_mode_set(RELAY1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY1_PIN);
    gpio_output_options_set(RELAY1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY1_PIN);

    gpio_mode_set(RELAY2_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY2_PIN);
    gpio_output_options_set(RELAY2_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY2_PIN);  

    gpio_mode_set(RELAY3_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY3_PIN);
    gpio_output_options_set(RELAY3_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY3_PIN);  

    gpio_mode_set(RELAY4_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY4_PIN);
    gpio_output_options_set(RELAY4_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY4_PIN);

    gpio_mode_set(RELAY5_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY5_PIN);
    gpio_output_options_set(RELAY5_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY5_PIN);  

    gpio_mode_set(RELAY6_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY6_PIN);
    gpio_output_options_set(RELAY6_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY6_PIN);

    gpio_mode_set(RELAY7_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY7_PIN);
    gpio_output_options_set(RELAY7_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY7_PIN);

    gpio_mode_set(RELAY8_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY8_PIN);
    gpio_output_options_set(RELAY8_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY8_PIN);  

    gpio_mode_set(RELAY9_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY9_PIN);
    gpio_output_options_set(RELAY9_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY9_PIN);

    gpio_mode_set(RELAY10_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY10_PIN);
    gpio_output_options_set(RELAY10_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY10_PIN);

    gpio_mode_set(RELAY11_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY11_PIN);
    gpio_output_options_set(RELAY11_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY11_PIN);  

    gpio_mode_set(RELAY12_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY12_PIN);
    gpio_output_options_set(RELAY12_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY12_PIN);

     gpio_mode_set(RELAY13_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY13_PIN);
    gpio_output_options_set(RELAY13_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY13_PIN);

    gpio_mode_set(RELAY14_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY14_PIN);
    gpio_output_options_set(RELAY14_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY14_PIN);  

    gpio_mode_set(RELAY15_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,RELAY15_PIN);
    gpio_output_options_set(RELAY15_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,RELAY15_PIN);

    GPIO_BC(RELAY1_PORT) = RELAY1_PIN;
    GPIO_BC(RELAY2_PORT) = RELAY2_PIN;
    GPIO_BC(RELAY3_PORT) = RELAY3_PIN;
    GPIO_BC(RELAY4_PORT) = RELAY4_PIN;
    GPIO_BC(RELAY5_PORT) = RELAY5_PIN;
    GPIO_BC(RELAY6_PORT) = RELAY6_PIN;
    GPIO_BC(RELAY7_PORT) = RELAY7_PIN;
    GPIO_BC(RELAY8_PORT) = RELAY8_PIN;
    GPIO_BC(RELAY9_PORT) = RELAY9_PIN;
    GPIO_BC(RELAY10_PORT) = RELAY10_PIN;
    GPIO_BC(RELAY11_PORT) = RELAY11_PIN;
    GPIO_BC(RELAY12_PORT) = RELAY12_PIN;
    GPIO_BC(RELAY13_PORT) = RELAY13_PIN;
    GPIO_BC(RELAY14_PORT) = RELAY14_PIN;
    GPIO_BC(RELAY15_PORT) = RELAY15_PIN;
}

void BSP_Relay1_Enable(void)
{
    GPIO_BOP(RELAY1_PORT) = RELAY1_PIN;
}

void BSP_Relay2_Enable(void)
{
    GPIO_BOP(RELAY2_PORT) = RELAY2_PIN;
}
void BSP_Relay3_Enable(void)
{
    GPIO_BOP(RELAY3_PORT) = RELAY3_PIN;
}
void BSP_Relay4_Enable(void)
{
    GPIO_BOP(RELAY4_PORT) = RELAY4_PIN;
}
void BSP_Relay5_Enable(void)
{
    GPIO_BOP(RELAY5_PORT) = RELAY5_PIN;
}
void BSP_Relay6_Enable(void)
{
    GPIO_BOP(RELAY6_PORT) = RELAY6_PIN;
}
void BSP_Relay7_Enable(void)
{
    GPIO_BOP(RELAY7_PORT) = RELAY7_PIN;
}
void BSP_Relay8_Enable(void)
{
    GPIO_BOP(RELAY8_PORT) = RELAY8_PIN;
}
void BSP_Relay9_Enable(void)
{
    GPIO_BOP(RELAY9_PORT) = RELAY9_PIN;
}
void BSP_Relay10_Enable(void)
{
    GPIO_BOP(RELAY10_PORT) = RELAY10_PIN;
}
void BSP_Relay11_Enable(void)
{
    GPIO_BOP(RELAY10_PORT) = RELAY10_PIN;
}
void BSP_Relay12_Enable(void)
{
    GPIO_BOP(RELAY12_PORT) = RELAY12_PIN;
}
void BSP_Relay13_Enable(void)
{
    GPIO_BOP(RELAY13_PORT) = RELAY13_PIN;
}
void BSP_Relay14_Enable(void)
{
    GPIO_BOP(RELAY14_PORT) = RELAY14_PIN;
}
void BSP_Relay15_Enable(void)
{
   GPIO_BOP(RELAY15_PORT) = RELAY15_PIN;
}

void BSP_Relay1_Disable(void)
{
    GPIO_BC(RELAY1_PORT) = RELAY1_PIN;
}
void BSP_Relay2_Disable(void)
{
    GPIO_BC(RELAY2_PORT) = RELAY2_PIN;
}
void BSP_Relay3_Disable(void)
{
    GPIO_BC(RELAY3_PORT) = RELAY3_PIN;
}
void BSP_Relay4_Disable(void)
{
    GPIO_BC(RELAY4_PORT) = RELAY4_PIN;
}
void BSP_Relay5_Disable(void)
{
   GPIO_BC(RELAY5_PORT) = RELAY5_PIN;
}
void BSP_Relay6_Disable(void)
{
    GPIO_BC(RELAY6_PORT) = RELAY6_PIN;
}
void BSP_Relay7_Disable(void)
{
    GPIO_BC(RELAY7_PORT) = RELAY7_PIN;
}
void BSP_Relay8_Disable(void)
{
    GPIO_BC(RELAY8_PORT) = RELAY8_PIN;
}
void BSP_Relay9_Disable(void)
{
    GPIO_BC(RELAY9_PORT) = RELAY9_PIN;
}
void BSP_Relay10_Disable(void)
{
    GPIO_BC(RELAY10_PORT) = RELAY10_PIN;
}
void BSP_Relay11_Disable(void)
{
    GPIO_BC(RELAY11_PORT) = RELAY11_PIN;
}
void BSP_Relay12_Disable(void)
{
    GPIO_BC(RELAY12_PORT) = RELAY12_PIN;
}
void BSP_Relay13_Disable(void)
{
    GPIO_BC(RELAY13_PORT) = RELAY13_PIN;
}
void BSP_Relay14_Disable(void)
{
    GPIO_BC(RELAY14_PORT) = RELAY14_PIN;
}
void BSP_Relay15_Disable(void)
{
    GPIO_BC(RELAY15_PORT) = RELAY15_PIN;
}
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//**************************IO口配置推挽****************************************

//-----------------------BSP_RelayPWM.c--END------------------------------------
