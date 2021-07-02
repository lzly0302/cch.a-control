//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include "stm32f10x.h"
//------------------------------E N D-------------------------------------------
#define MIXWATER_PORT     GPIOC       //左边GPIO
#define MIXWATER_PIN      GPIO_Pin_7
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++ 
void bsp_mixwater_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* GPIOA clock enable, */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Pin = MIXWATER_PIN;
    GPIO_Init(MIXWATER_PORT, &GPIO_InitStructure); 
    GPIO_ResetBits(MIXWATER_PORT,MIXWATER_PIN);
}

void bsp_mixwater_on(void)
{
   GPIO_SetBits(MIXWATER_PORT,MIXWATER_PIN);
}

void bsp_mixwater_off(void)
{
    GPIO_ResetBits(MIXWATER_PORT,MIXWATER_PIN);
}
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//**************************IO口配置推挽****************************************

//-----------------------BSP_RelayPWM.c--END------------------------------------
