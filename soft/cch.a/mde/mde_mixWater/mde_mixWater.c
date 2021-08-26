//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include ".\mde_mixWater.h"
#include ".\depend\BSP_PID.h"
#include "..\mde_pwm\mde_pwm.h"
//------------------------------E N D-------------------------------------------

typedef struct
{
    uint8_t currentDegree;
	mixWater_mode_t mode; 
}mixWater_def_t;
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***********************函数使用的内部变量*************************************
mixWater_def_t hal_mixWater;
//------------------------------E N D-------------------------------------------
#define TASK_STATUS_NO_INIT       0x00
#define TASK_STATUS_RUN           0x01



PID_ValueStr pidValue = {
    0,//int16_t target;   //目标量  
    0,//int16_t feedback; //反馈量  
    55,//uint16_t Kp;         
    5,//uint16_t Ki;  
    20,//uint16_t Kd;  
    0,//int16_t eSum;  
    0,//int16_t e0;       //当前误差  
    0//int16_t e1;       //上一次误差  
};

void mod_mixWater_adjust(mixWater_set_mode_t mode,int16_t _in_mixMeasureTemp,int16_t _in_backWaterMeasureTemp,uint16_t _in_mixSetTemp)
{//轻负载温差2度以内，重负载温差7度以内保持混水温度在+-1度之间波动，温差值混水温度跟回水温度之间的温差。
     
        uint16_t value = 0;  
        static int16_t lastSetTemp = 0;
        static uint8_t count = 0;
        static bool needAdjustFlag = false;//确定需要调节
        static bool noNeedAdjustFlag = false;//确定需要调节
        pidValue.feedback = _in_mixMeasureTemp;
        pidValue.target = _in_mixSetTemp;
        
        if(mode == SET_COLD) 
        {
			if(lastSetTemp != _in_mixSetTemp)
			{
				if(_in_mixSetTemp > lastSetTemp)
				{
					pidValue.err_sum = 0;
				}
				lastSetTemp = _in_mixSetTemp;
			} 	
            if(_in_mixSetTemp - _in_mixMeasureTemp > 10)
            {
                count++;
                if(count >= 1)
                {
                    count = 0;
                    pidValue.err_sum >>= 1;
                }
            }
            else
            {
                  count = 0;
            }
            if(noNeedAdjustFlag)
            {
                if((_in_mixMeasureTemp - _in_mixSetTemp) >= 20)
                {
                    noNeedAdjustFlag = false;
                }
                else if((_in_mixSetTemp - _in_mixMeasureTemp) >= 10)
                {
                    noNeedAdjustFlag = false;
                }
            }
            else
            {
                if(_in_mixMeasureTemp >  _in_mixSetTemp)
                {//到达设定温度后先不动
                    needAdjustFlag = true;
                }
                else if((_in_mixSetTemp - _in_mixMeasureTemp) >= 10)
                {
                    needAdjustFlag = true;
                }
                else
                {
                    needAdjustFlag = false;
                    noNeedAdjustFlag = true;
                }
            }
        }
        else
        {
            if(lastSetTemp != _in_mixSetTemp)
            {
                if(_in_mixSetTemp < lastSetTemp)
                {
                    pidValue.err_sum = 0;
                }
                lastSetTemp = _in_mixSetTemp;
            } 		
            if(_in_mixMeasureTemp - _in_mixSetTemp > 10)
            {
                count++;
                if(count >= 1)
                {
                    count = 0;
                    pidValue.err_sum >>= 1;
                }
            }
            else
            {
                  count = 0;
            }         
            if(noNeedAdjustFlag)
            {
                if((_in_mixSetTemp - _in_mixMeasureTemp) >= 20)
                {
                    noNeedAdjustFlag = false;
                }
                else if((_in_mixMeasureTemp - _in_mixSetTemp) >= 10)
                {
                    noNeedAdjustFlag = false;
                }
            }
            else
            {
                if(_in_mixSetTemp >  _in_mixMeasureTemp)
                {//到达设定温度后先不动
                    needAdjustFlag = true;
                }
                else if((_in_mixMeasureTemp - _in_mixSetTemp) >= 10)
                {
                    needAdjustFlag = true;
                }
                else
                {
                    needAdjustFlag = false;
                    noNeedAdjustFlag = true;
                }
            }
        }
        if(needAdjustFlag)
        {
            value = PID_get_pid_value(&pidValue,mode);
            //hal_mixWater.currentDegree = (100 - value/100);//阀门特性 0V全开，10V全关，逻辑需要反一下
            hal_mixWater.currentDegree = (value/100);
            uint16_t duty = ((uint32_t)hal_mixWater.currentDegree )*10000/13140;
            mde_SetInFanPwm(0,duty);
        }
       
}

void  mod_mixWater_set_puty(uint8_t _in_puty)
{
    mde_SetInFanPwm(0,_in_puty);
}

uint8_t mod_mixWater_current_puty(void)
{
    return hal_mixWater.currentDegree;
} 
