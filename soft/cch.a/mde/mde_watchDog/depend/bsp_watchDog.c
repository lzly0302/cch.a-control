
/*******************************************************************************
*
*	模块名称 : 独立看门狗
*	文件名称 : BSP_IWDG.c
*	版    本 : V1.0
*	说    明 : 1、配置和喂狗函数
*                  
*                    
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0   2018-08-23  jinzh 正式发布
*	Copyright (C), 2015-2020,   menredGroup
*       编译环境 ：IAR FOR STM8 V2.2      
*******************************************************************************/


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include "gd32f4xx.h"
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//*********************配置看门狗4S超时时间**********************************
void BSP_IWDG_Configure(void)
{ 
     /* enable IRC32K */
    rcu_osci_on(RCU_IRC32K);
    
    /* wait till IRC32K is ready */
    while(SUCCESS != rcu_osci_stab_wait(RCU_IRC32K)){
    }
     /* confiure FWDGT counter clock: 32KHz(IRC32K) / 64 = 0.5 KHz */
    fwdgt_config(2*500,FWDGT_PSC_DIV64);
    
    /* After 2 seconds to generate a reset */
    fwdgt_enable();
    /* check if the system has resumed from FWDGT reset */
    if (RESET != rcu_flag_get(RCU_FLAG_FWDGTRST))
    {
        /* clear the FWDGT reset flag */
        rcu_all_reset_flag_clear();       
    }
}
//------------------------------E N D-------------------------------------------



//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//******************************喂狗********************************************
void BSP_IWDG_FeedDog(void)
{
	fwdgt_counter_reload();
}
//------------------------------E N D-------------------------------------------
