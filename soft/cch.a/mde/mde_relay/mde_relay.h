//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _MOD_RELAY_H
#define _MOD_RELAY_H
//------------------------------E N D-------------------------------------------

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++

#include<stdint.h>
#include<stdio.h>
#include<stdbool.h>
//------------------------------E N D-------------------------------------------
#define RELAY_DELAY_TIME   20
#define RELAY_RECLOSE_TIME  50
#define RELAY_PORT1    0
#define RELAY_PORT2    1
#define RELAY_PORT3    2
#define RELAY_PORT4    3
#define RELAY_PORT5    4
#define RELAY_PORT6    5
#define RELAY_PORT7    6
#define RELAY_PORT8    7
#define RELAY_PORT9    8
#define RELAY_PORT10   9
#define RELAY_AIRCOD   11
#define RELAY_PUMP     14
typedef enum
{
    RELAY_1  = (uint8_t)0,
    RELAY_2,
    RELAY_3,
    RELAY_4,
    RELAY_5,
    RELAY_6,
    RELAY_7,
    RELAY_8,
    RELAY_9,
    RELAY_10,
    RELAY_11,
    RELAY_12,
    RELAY_13,
    RELAY_14,
    RELAY_15,
}relay_number_t;

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Task
//名称: 继电器开启带延时功能
//功能: 应用模块调用    
//入口: emNumber        继电器编号             <<-------------------------传入
//      _in_100msOnDelay 延时开启时间 单位100ms<<-------------------------传入
//出口: 无
void mde_relay_on(uint8_t in_solidNum,uint16_t _in_100msOnDelay);
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Task
//名称: 继电器关闭带延时功能
//功能: 应用模块调用     
//入口:  emNumber        继电器编号          <<-------------------------传入
//      _in_100msOffDelay延时关闭时 单位100ms<<-------------------------传入
//出口: 无
void mde_relay_off(uint8_t in_solidNum,uint16_t _in_100msOffDelay);
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Task
//名称: 继电器扫描任务
//功能: 放入主函数或应用模块定时调用    
//      _in_ms_tick ms级延时周期      <<-------------------------传入
//入口:
//出口: 
//void Mod_Relay_ScanTask(void);
void mde_relay_task(void);
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++ 
//------------------------------E N D-------------------------------------------

#endif


//-----------------------Mod_Relay.h--END------------------------------------
