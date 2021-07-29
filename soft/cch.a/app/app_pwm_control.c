
#include ".\app_cfg.h"

void app_pwm_control_task(void)
{
   mde_SetInFanPwm(PWM_PUMP,30);
   //mde_SetInFanPwm(PWM_THREE_VAVLE,30);
   mde_EcMotorControlTask();
}
//------------------------------E N D-------------------------------------------



