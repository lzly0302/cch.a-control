
#include ".\app_cfg.h"

void app_pwm_control_task(void)
{
   mde_SetInFanPwm(PWM_PUMP,80);
   mde_EcMotorControlTask();
}
//------------------------------E N D-------------------------------------------



