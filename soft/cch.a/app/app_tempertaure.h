//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _APP_TEMPERATURE_H
#define _APP_TEMPERATURE_H
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
void app_temperature_task(void);
/*һ�β��ˮ�¶�*/
int16_t app_pull_first_in_water_temp(void);
/*һ�β��ˮ�¶�*/
int16_t app_pull_first_back_water_temp(void);
/*��ˮ�¶�*/
int16_t app_pull_back_water_temp(void);
/*��ˮ�¶�*/
int16_t app_pull_mix_water_temp(void);
//------------------------------E N D-------------------------------------------
#endif