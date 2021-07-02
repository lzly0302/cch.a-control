/***************************************************************************
* Designed by Osman Li <Li.haimeng@menred.com> 
* Copyright , Menred Group Corporation.
* This software is owned by Menred Group and is protected by and subject to 
* worldwide patent protection (china and foreign)
 ***************************************************************************/
 /***************************************************************************
* Release Notes:
*     V1.1  
*         Data: 
*          
*     V1.0  
*         Data:2015.1.26
*         Official release
****************************************************************************/

/*============================ INCLUDES ======================================*/
 #include "BSP_PID.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/


/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/


/*! \brief   
 *! \param  
 *! \retval  
 *! \retval  
 */

  
uint16_t PID_get_pid_value(PID_ValueStr *me,uint8_t mode)  
{  
    int32_t out=0;  
  //  uint8_t index = 0;
    //计算当前误差 
    if(mode == 0x00)
    {//制冷
        me->err_cur =me->feedback - me->target; 
    }
    else
    {//制热
        me->err_cur =me->target - me->feedback; 
    }
//    if(me->err_cur >= 10)
//    {
//        me->err_cur = 10;
//    }
    me->err_sum += me->err_cur;  
    if(me->err_sum < -20)
    {   
         me->err_sum = -20;
    }
    if(me->err_sum > 110)
    {   
         me->err_sum = 110;
    }
    //误差微分  
    me->err_last = me->err_cur;  
    out = me->err_cur*(me->Kp) +  me->err_sum*(me->Ki) + (me->err_cur - me->err_last)*(me->Kd);  //位置型
	
    //输出限幅   
    if(out < 0)
    {
        out= 0;
    }
    if(out > 8000)
    {
        out = 8000;
    }
    return out;  
}  
/* EOF */
