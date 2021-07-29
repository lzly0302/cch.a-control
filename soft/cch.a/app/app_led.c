#include ".\app_cfg.h"

void app_led_task(void)
{
    mde_led_blink(LED_1,5,5);
    mde_led_task();
}
//------------------------------E N D-------------------------------------------



