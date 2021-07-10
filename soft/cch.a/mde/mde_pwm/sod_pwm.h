//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef _SOD_PWM_H
#define _SOD_PWM_H
//----------------------------------------------------------------------------------
#include<stdint.h>
#include<stdio.h>
#include<stdbool.h>
#include ".\depend\bsp_pwm.h"
#define max_solid    2

static PwmControlParameter_Def mde_pwm[max_solid];

void mde_pwm_solid_cfg(void)
{
    PwmControl_Configure();
    mde_pwm[0].LoadPwmToPort = TIM0CH0_Loading_PwmDutyOut;
    mde_pwm[1].LoadPwmToPort = TIM0CH1_Loading_PwmDutyOut;
}
#endif
//++++++++++++++++++++++++++++++++++End+++++++++++++++++++++++++++++++++++++++++