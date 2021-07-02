#include ".\app_cfg.h"

void app_step_motor_test(void)
{  
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&measure_delay);
    static bool closeFlag = false;
    if(pbc_pull_timerIsCompleted(&measure_delay))
    {
        if(closeFlag)
        {
            closeFlag = false;
            mde_motor_GotoClose(0);
        }
        else
        {
            closeFlag = true;
            mde_motor_GotoOpen(0);
        }
        pbc_reload_timerClock(&measure_delay,60000);     
    }
}

void app_led_task(void)
{
    mde_led_blink(LED_4,5,5);
    if(app_link_log_pull_local_device_online(SYSTEM_MASTER))
    {
        mde_led_blink(LED_1,5,5);
    }
    else
    {
        mde_led_off(LED_1);
    }
    mde_led_task();
}
//------------------------------E N D-------------------------------------------



