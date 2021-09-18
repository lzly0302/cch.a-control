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
    StoRunParameter.systemPower = false;// //开关机
    StoRunParameter.airRunmode = AIR_MODE_AUTO_COOL;//模式
    StoRunParameter.humidity_DeadZone =5;//湿度带宽
    StoRunParameter.temp_DeadZone = 10; //温度带宽
    StoRunParameter.mixColdSetTemp = 160; //混水制冷设定温度
    StoRunParameter.mixHeatSetTemp = 300;//混水制热设定温度   
    StoRunParameter.deviceAddress = 0x01;
    StoRunParameter.baudrateValue = 0x02;
    StoRunParameter.evenOddCheck = 0x00;
    StoRunParameter.stopBit = 0;
    StoRunParameter.coldDropDiff = 30;//露点带宽
    StoRunParameter.lowTempProtectConfig = 50;//防冻温度
    StoRunParameter.powerOffStatus = 0;//上电关机功能
    StoRunParameter.lew_status_open_diff = 0; //露点开启带宽
    StoRunParameter.lew_status_close_diff = 10;//露点关闭带宽
    StoRunParameter.set_cold_water_temp = 100;//主机制冷模式出水设定水温
    StoRunParameter.set_heat_water_temp = 400;//主机制热模式出水设定水温
    StoRunParameter.set_living_water_temp = 550; //生活热水
    StoRunParameter.debug_enable = false;//调试使能
    StoRunParameter.control_method = METHOD_BASIC;//基础策略
    StoRunParameter.hum_set = 60;                 //设定湿度
    StoRunParameter.NewAirLevelSet = MiddleFanSet;//设定风速
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