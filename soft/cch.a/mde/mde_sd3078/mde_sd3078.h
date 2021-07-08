#ifndef _MOD_REAL_TIME_H
#define _MOD_REAL_TIME_H
//------------------------------E N D-------------------------------------------

#include <stdbool.h>
#include <stdint.h>



//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***************************RTC类型定义*****************************************


typedef union
{
    struct
    {
        uint8_t minute;
        uint8_t hour;      
        uint8_t week;
        uint8_t second;
        uint8_t day;
        uint8_t month;
        uint8_t year;
    };
    uint16_t hm;  
}realTime_t;
//------------------------------E N D-------------------------------------------



//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Init
//名称:  mod_real_time_configure
//功能:  实时时钟配置
//入口:  无
//出口:  无
bool mde_sd3078_configure(void);
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称:  mod_real_time_write
//功能:  将修改的时间写入实时时钟
//入口:  结构体指针,传入需要写的时间
//       realTime_t类型指针  <<-------------------------------------------传入
//出口:  无
void mde_sd3078_write(realTime_t *ptRT);
//------------------------------E N D-------------------------------------------

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称:  mod_real_time_read
//功能:  从实时时钟中读取时间
//入口:  结构体指针,传出读到的时间
//       *realTime_t类型指针  ------------------------------------------->>传出
//
//出口:  无
void mde_sd3078_read(realTime_t *_out_ptRT);
//------------------------------E N D-------------------------------------------
#endif


//-------------------------Mod_SD3078.h--END------------------------------------