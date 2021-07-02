//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include ".\mde_mixWater.h"
#include ".\depend\BSP_PID.h"
#include ".\depend\bsp_mixwater.h"
#include "..\..\pbc\pbc_sysTick\pbc_sysTick.h"
//------------------------------E N D-------------------------------------------

typedef struct
{
    uint8_t currentDegree; 
    uint16_t  pwmValve;
}mixWater_def_t;
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***********************函数使用的内部变量*************************************
mixWater_def_t hal_mixWater;
//------------------------------E N D-------------------------------------------

PID_ValueStr pidValue = {
    0,//int16_t target;   //目标量  
    0,//int16_t feedback; //反馈量  
    60,//uint16_t Kp;         
    0,//uint16_t Ki;  
    40,//uint16_t Kd;  
    0,//int16_t eSum;  
    0,//int16_t e0;       //当前误差  
    0//int16_t e1;       //上一次误差  
};

#define DELAY_1S   1000
void mde_mixWater_task(void)
{//1s时间内输出ms的高电平
    static bool  cfged = false;
    if(cfged)
    {
        macro_createTimer(measure_delay,timerType_millisecond,DELAY_1S);
        macro_createTimer(output_delay,timerType_millisecond,0);
        pbc_timerClockRun_task(&measure_delay);
        pbc_timerClockRun_task(&output_delay);
        if(pbc_pull_timerIsCompleted(&measure_delay))
        {//1s时间到
            pbc_reload_timerClock(&measure_delay,DELAY_1S);
            pbc_reload_timerClock(&output_delay,(hal_mixWater.pwmValve/10));
            bsp_mixwater_on();
        }
        if(pbc_pull_timerIsCompleted(&output_delay)) 
        {
            bsp_mixwater_off();
        }
    }
    else
    {
        cfged = true;
        bsp_mixwater_config();
    }
}
void mod_mixWater_adjust(mixWater_set_mode_t mode,int16_t _in_mixMeasureTemp,int16_t _in_backWaterMeasureTemp,uint16_t _in_mixSetTemp)
{//轻负载温差2度以内，重负载温差7度以内保持混水温度在+-1度之间波动，温差值混水温度跟回水温度之间的温差。
     
   // static int16_t lastSetTemp = 0;
  //  static uint8_t count = 0;
    pidValue.feedback = _in_mixMeasureTemp;
    pidValue.target = _in_mixSetTemp;
    
//    if(mode == SET_COLD) 
//    {//制冷
//        if(lastSetTemp != _in_mixSetTemp)
//        {
//            if(_in_mixSetTemp > lastSetTemp)
//            {
//                pidValue.err_sum = 0;
//            }
//            lastSetTemp = _in_mixSetTemp;
//        } 	
//        if(_in_mixSetTemp - _in_mixMeasureTemp > 10)
//        {
//            count++;
//            if(count >= 1)
//            {
//                count = 0;
//                pidValue.err_sum >>= 1;
//            }
//        }
//        else
//        {
//            count = 0;
//        }
//    }
//    else
//    {//制热
//        if(lastSetTemp != _in_mixSetTemp)
//        {
//            if(_in_mixSetTemp < lastSetTemp)
//            {
//                pidValue.err_sum = 0;
//            }
//            lastSetTemp = _in_mixSetTemp;
//        } 		
//        if(_in_mixMeasureTemp - _in_mixSetTemp > 10)
//        {
//            count++;
//            if(count >= 1)
//            {
//                count = 0;
//                pidValue.err_sum >>= 1;
//            }
//        }
//        else
//        {
//            count = 0;
//        }         
//    }
    hal_mixWater.pwmValve = PID_get_pid_value(&pidValue,mode);   
    mde_mixWater_task();
}


void  mod_mixWater_set_puty(uint8_t _in_puty)
{
    //mde_SetInFanPwm(0,_in_puty);
}

uint8_t mod_mixWater_current_puty(void)
{
    return hal_mixWater.currentDegree;
} 
