//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _APP_TEMPERATURE_H
#define _APP_TEMPERATURE_H
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
void app_temperature_task(void);
/*一次侧进水温度*/
int16_t app_pull_first_in_water_temp(void);
/*一次侧回水温度*/
int16_t app_pull_first_back_water_temp(void);
/*回水温度*/
int16_t app_pull_back_water_temp(void);
/*混水温度*/
int16_t app_pull_mix_water_temp(void);
//------------------------------E N D-------------------------------------------
#endif