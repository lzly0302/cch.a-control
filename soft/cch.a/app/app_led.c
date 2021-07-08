#include ".\app_cfg.h"

void app_led_task(void)
{
//    mde_led_blink(LED_3,5,5);
//    if(app_link_log_pull_local_device_online(SYSTEM_MASTER))
//    {
//        mde_led_blink(LED_2,5,5);
//    }
//    else
//    {   
//        mde_led_off(LED_2);
//    }
//    if(app_link_log_pull_local_device_online(SYSTEM_PAD))
//    {
//        mde_led_blink(LED_1,5,5);
//    }
//    else
//    {
//        mde_led_off(LED_1);
//    }
    mde_led_blink(LED_1,5,5);
    mde_led_task();
}
//------------------------------E N D-------------------------------------------



