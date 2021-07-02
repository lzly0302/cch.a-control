//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"

StoRunParamter_Def  StoRunParameter = 
{
        .localId[0] = 0xae,
        .localId[1] = 0x21,
        .localId[2] = 0x05,
        .localId[3] = 0x12,
        .localId[4] = 0x00,
        .localId[5] = 0x01,
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static sdt_bool cfged = sdt_false;
//-------------------------------------------------------------------------------
static void sto_run_parameter_cfg(void)
{
    mde_storage_block_set_length_w(0,sizeof(StoRunParameter));
}
uint8_t * app_pull_local_id(void)
{
    return &StoRunParameter.localId[0];
}
//-----------------------------------------------------------------------------
void RestoreFactoryStorage(void)
{
    StoRunParameter.airRunmode = AIR_MODE_AUTO_COOL;
    StoRunParameter.hotTemp_set = 200;
    StoRunParameter.coldTemp_set = 260;
    StoRunParameter.humidity_set = 50;//除湿
    StoRunParameter.humidity_DeadZone = 3;
    StoRunParameter.temp_DeadZone = 10;
    StoRunParameter.newAirLowPwm = 30;
    StoRunParameter.newAirMidPwm =60;
    StoRunParameter.newAirHighPwm = 90;
    StoRunParameter.backAirLowPwm = 30;
    StoRunParameter.backAirMidPwm = 60;
    StoRunParameter.backAirHighPwm = 90;
    StoRunParameter.set_cold_water_temp = 100;
    StoRunParameter.set_heat_water_temp = 400;
    StoRunParameter.set_living_water_temp = 550; //生活热水
    StoRunParameter.NewAirLevelSet = MiddleFanSet;
    StoRunParameter.airInFanPwmValue_Low = 35;
    StoRunParameter.airInFanPwmValue_Middle =65;
    StoRunParameter.airInFanPwmValue_High = 95;
    StoRunParameter.airOutFanPwmValue_Low = 35;
    StoRunParameter.airOutFanPwmValue_Middle = 65;
    StoRunParameter.airOutFanPwmValue_High = 95;
  //  StoRunParameter.control_method = METHOD_BASIC;
    StoRunParameter.cold_no_need_temp_set = 200;
    StoRunParameter.cold_fan_need_temp_set = 100;
    StoRunParameter.cold_warm_need_temp_set = 160;
    StoRunParameter.config_lew_temp_set = 160;
    StoRunParameter.heat_no_need_temp_set = 300;
    StoRunParameter.heat_fan_need_temp_set = 450;
    StoRunParameter.heat_warm_need_temp_set = 350;
    StoRunParameter.config_back_wind_temp_set = 200;
    StoRunParameter.config_hum_set = 50;
    StoRunParameter.cold_wind_max_temp_set = 300;
    StoRunParameter.heat_wind_min_temp_set = 160;
    StoRunParameter.heat_wind_max_temp_set = 300;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_read_run_parameter(void)
{
    if(cfged)
    {     
    }
    else
    {
        cfged = sdt_true;
        sto_run_parameter_cfg();
    }
    if(mde_read_storage_block(0,&StoRunParameter.sto_data[0]))
    {
        StoRunParameter.localId[0] = 0xae;
        StoRunParameter.localId[1] = 0x21;
        StoRunParameter.localId[2] = 0x04;
        StoRunParameter.localId[3] = 0x12;
        StoRunParameter.localId[4] = 0x00;
        StoRunParameter.localId[5] = 0x03;
        if((StoRunParameter.deviceAddress == 0) || (StoRunParameter.deviceAddress == 0xff))
        {
            StoRunParameter.deviceAddress = 0x01;   
        }
        if(StoRunParameter.baudrateValue == 0xff)
        {
            StoRunParameter.baudrateValue = 0x02;
        }
        if(StoRunParameter.evenOddCheck == 0xff)
        {
            StoRunParameter.evenOddCheck = 0;
        }
        StoRunParameter.deviceAddress = 0x03;
        StoRunParameter.baudrateValue = 0x02;
        StoRunParameter.evenOddCheck = 0;
        StoRunParameter.stopBit = 0;
        StoRunParameter.filter_usetime = 0;
        StoRunParameter.drainWaterError = 0;
        RestoreFactoryStorage();
    }
    else
    {
        RestoreFactoryStorage();
        app_push_once_save_sto_parameter();
    }   
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
macro_createTimer(timer_notSave,(timerType_millisecond | timStatusBits_onceTriggered),0);
//-------------------------------------------------------------------------------
void app_sto_run_parameter_task(void)
{
    if(cfged)
    {     
    }
    else
    {
        cfged = sdt_true;
        sto_run_parameter_cfg();
    }
    
    pbc_timerClockRun_task(&timer_notSave);
    if(pbc_pull_timerIsOnceTriggered(&timer_notSave))
    {
        StoRunParamter_Def rd_sto;
        sdt_int32u i;
        sdt_bool enable_write = sdt_false;
        
        if(mde_read_storage_block(0,&rd_sto.sto_data[0]))
        {
            for(i = 0;i < (sizeof(StoRunParameter)/4);i ++)
            {
                if(rd_sto.sto_data[i] != StoRunParameter.sto_data[i])//数据有变化存储
                {
                    enable_write = sdt_true;
                    break;
                }
            }
        }
        else
        {
            enable_write = sdt_true;
        }
        if(enable_write)
        {
            mde_write_storage_block(0,&StoRunParameter.sto_data[0]);
        }
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_push_once_save_sto_parameter(void)
{
    pbc_reload_timerClock(&timer_notSave,3000);//3s后存储一次
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++