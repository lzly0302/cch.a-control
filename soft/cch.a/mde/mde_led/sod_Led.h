//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _SOD_LED_H
#define _SOD_LED_H
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include ".\depend\bsp_Led.h"
#include <stdint.h>
#include <stdbool.h>
//------------------------------E N D-------------------------------------------
#define max_solid    1

static led_device_t  mde_led[max_solid];
void mde_led_solid_cfg(void)
{
    bsp_led1_config();
    mde_led[0].led_on = BSP_Led1_Enable;
    mde_led[0].led_off = BSP_Led1_Disable;
    mde_led[0].ledonFlag = false;
}
#endif

