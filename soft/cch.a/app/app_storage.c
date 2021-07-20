//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"

StoRunParamter_Def  StoRunParameter = 
{
        .localId[0] = 0xac,
        .localId[1] = 0x21,
        .localId[2] = 0x07,
        .localId[3] = 0x14,
        .localId[4] = 0x00,
        .localId[5] = 0x01,
};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static sdt_bool cfged = sdt_false;
//-------------------------------------------------------------------------------
static void sto_run_parameter_cfg(void)
{ 
     uint32_t in_w25q64_id; 
     SPI_FLASH_Init();
     
     in_w25q64_id = SPI_FLASH_ReadID();
     if(in_w25q64_id == sFLASH_ID)
     {
        mde_storage_block_set_length_w(0,sizeof(StoRunParameter));
     }
}
uint8_t * app_pull_local_id(void)
{
    return &StoRunParameter.localId[0];
}
//-----------------------------------------------------------------------------
void RestoreFactoryStorage(void)
{
    StoRunParameter.systemPower = false;
    StoRunParameter.airRunmode = AIR_MODE_AUTO_COOL;
    StoRunParameter.NewAirLevelSet = MiddleFanSet;
    StoRunParameter.humidity_set = 60;
    StoRunParameter.humidity_DeadZone =3;
    StoRunParameter.temp_DeadZone = 10;
    StoRunParameter.mixColdSetTemp = 160;
    StoRunParameter.mixHeatSetTemp = 300;
    StoRunParameter.deviceAddress = 0x01;
    StoRunParameter.baudrateValue = 0x02;
    StoRunParameter.evenOddCheck = 0x00;
    StoRunParameter.stopBit = 0;
    StoRunParameter.aiEnable = 0;
    StoRunParameter.coldDropDiff = 30;
    StoRunParameter.lowTempProtectConfig = 50;
    StoRunParameter.powerOffStatus = 0;
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
    StoRunParameter.lew_status_open_diff = 0;
    StoRunParameter.lew_status_close_diff = 10;
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
      //  RestoreFactoryStorage();//调试功能，需删除
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