#include ".\app_cfg.h"

int16_t firstInWaterTemp = 220;
int16_t firstBackWaterTemp = 220;
int16_t backWaterTemp = 220;
int16_t mixWaterTemp = 220;

int16_t app_pull_first_in_water_temp(void)
{
    return firstInWaterTemp;
}
int16_t app_pull_first_back_water_temp(void)
{
    return firstBackWaterTemp;
}
int16_t app_pull_back_water_temp(void)
{
    return backWaterTemp;
}
int16_t app_pull_mix_water_temp(void)
{
    return mixWaterTemp;
}

void app_temperature_task(void)
{
    mde_NTCSensor_ScanTask();
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerMillRun_task(&measure_delay);
    if(pbc_pull_timerIsCompleted(&measure_delay))
    {
        pbc_reload_timerClock(&measure_delay,1000);
        mixWaterTemp = mde_NTCSensor_GetTemperature(SENSOR_ONE,B_3380_10K,Res01_Degree);
        backWaterTemp = mde_NTCSensor_GetTemperature(SENSOR_TWO,B_3380_10K,Res01_Degree);
        firstInWaterTemp = mde_NTCSensor_GetTemperature(SENSOR_THREE,B_3380_10K,Res01_Degree); 
        firstBackWaterTemp = mde_NTCSensor_GetTemperature(SENSOR_FOUR,B_3380_10K,Res01_Degree); 
        #define SEND_TEMP_COUNT   60
        static uint8_t secondCount = 0;
        secondCount++;
        if(secondCount >= SEND_TEMP_COUNT)
        {//1分钟更新一次
            secondCount = 0;
            app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_MIXWATER_TEMP);
        }      
        if(firstInWaterTemp == SensorError)
        {
            app_general_push_master_error_word(SYS_ERROR_FIRST_SUPPLY_WATER);
        }
        else
        {
            app_general_clear_master_error_word(SYS_ERROR_FIRST_SUPPLY_WATER);
        }
        if(firstBackWaterTemp == SensorError)
        {
            app_general_push_master_error_word(SYS_ERROR_FIRST_BACK_WATER);
        }
        else
        {
            app_general_clear_master_error_word(SYS_ERROR_FIRST_BACK_WATER);
        }
        if(backWaterTemp == SensorError)
        {
            app_general_push_error_word(ERROR_NTC_BACK_WATER);
            app_general_push_master_error_word(SYS_ERROR_BACK_WATER);
        }
        else
        {
            app_general_clear_error_word(ERROR_NTC_BACK_WATER);
            app_general_clear_master_error_word(SYS_ERROR_BACK_WATER);
        }
        if(mixWaterTemp == SensorError)
        {
            app_general_push_error_word(ERROR_NTC_MIX_WATER);
            app_general_push_master_error_word(SYS_ERROR_MIX_WATER);
        }
        else
        {
            app_general_clear_error_word(ERROR_NTC_MIX_WATER);
            app_general_clear_master_error_word(SYS_ERROR_MIX_WATER);
        }
    }
}
//------------------------------E N D-------------------------------------------



