#include ".\app_cfg.h"

macro_createTimer(timer_notWrite,(timerType_millisecond | timStatusBits_onceTriggered),0);
static realTime_t currentTime;
void software_time_run(void)
{
    currentTime.second++;
    if(currentTime.second>59)
    {
        currentTime.second = 0;
        currentTime.minute++;
        if(currentTime.minute>59)
        {
            currentTime.hour++;
            if(currentTime.hour>23)
            {
                currentTime.day++;
                currentTime.week++;
            }
        }
    }
}
void stamp_updata(void)
{
    uint8_t i = 0;
    for(i = 0; i < MASTER_PAD_NUM;i++)
    {//面板dp时间戳更新
        app_general_push_pad_dp_stamp(i,DP_ADDR_PAD_SYSTEM_RTC,pbc_timeStamp_get_stamp());  
        app_general_push_pad_dp_stamp(i,DP_ADDR_PAD_SYSTEM_MESSAGE,pbc_timeStamp_get_stamp());
    } 
    for(i = 0;i < MASTER_DHM_NUM;i++)
    {//除湿dp时间戳更新
        app_general_push_dhm_dp_stamp(i,DP_ADDR_DHM_LIS_RTC,pbc_timeStamp_get_stamp());//时间
        app_general_push_dhm_dp_stamp(i,DP_ADDR_DHM_POWER,pbc_timeStamp_get_stamp());//开关机
        app_general_push_dhm_dp_stamp(i,DP_ADDR_DHM_WIND_SET_MODE,pbc_timeStamp_get_stamp());//模式
    }   
    for(i = 9; i < 14;i++)
    {//主机集成dp时间戳更新
        app_general_push_system_dp_stamp((DP_ADDR_START+i),pbc_timeStamp_get_stamp());
    }
    app_general_push_system_dp_stamp(DP_ADDR_SYSTEM_LIS_RTC,pbc_timeStamp_get_stamp());
    app_general_push_system_dp_stamp(DP_ADDR_SYSTEM_LIS_MIXWATER_OUT,pbc_timeStamp_get_stamp());
    app_general_push_system_dp_stamp(DP_ADDR_SYSTEM_LIS_MIXWATER_TEMP,pbc_timeStamp_get_stamp());
}
void app_clock_timing_read(void)
{  
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&measure_delay);
    if(pbc_pull_timerIsCompleted(&measure_delay))
    {
        pbc_reload_timerClock(&measure_delay,1000);
        mde_sd3078_read(&currentTime);   
        stamp_updata();
    }
}
bool writeRTCFlag = false;
void app_real_time_clock_task(void)
{
    static sdt_bool sys_cfged = sdt_false;
    if(sys_cfged)
    {
        pbc_timerClockRun_task(&timer_notWrite);      
		if(writeRTCFlag)
		{
			if(pbc_pull_timerIsOnceTriggered(&timer_notWrite))
			{
				mde_sd3078_write(&currentTime);
				writeRTCFlag = false;
				stamp_updata();
			}				
		}
		else
		{
			app_clock_timing_read();
		}
    }
    else
    {
        mde_sd3078_configure();
//        currentTime.hour = 13;
//        currentTime.minute = 52;
//        currentTime.week = 5;
//        currentTime.day = 27;
//        currentTime.month = 8;
//        currentTime.year = 21;
//        mde_sd3078_write(&currentTime);
        sys_cfged = true;
        mde_sd3078_read(&currentTime);
        pbc_timeStamp_get_absolutely_time(((uint8_t *)&currentTime));
        stamp_updata();
    } 
}
realTime_t* app_real_time_pull_rtc(void)
{
    return &currentTime;
}

void app_real_time_push_rtc(realTime_t in_rtc)
{
    if((in_rtc.second <= 59) && 
    (in_rtc.minute <= 59) &&
    (in_rtc.hour <= 23)&&
    (in_rtc.day <= 31)&&
    (in_rtc.month <= 12))
    {
        currentTime = in_rtc;
    }
}

void app_push_once_save_write_rtc(void)
{
    pbc_reload_timerClock(&timer_notWrite,3000);//3s后写一次
	writeRTCFlag = true;
}
//------------------------------E N D-------------------------------------------




