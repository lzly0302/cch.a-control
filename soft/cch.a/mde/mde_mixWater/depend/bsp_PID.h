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

#ifndef __BSP_PID_H__
#define __BSP_PID_H__

/*============================ INCLUDES ======================================*/
#include <stdbool.h>
#include <stdint.h>
/*============================ MACROS ========================================*/


typedef struct PID_Value
{  
    int16_t target;   //目标量  
    int16_t feedback; //反馈量  
    uint16_t Kp;       //比例  
    uint16_t Ki;      //积分
    uint16_t Kd;      //微分
    int16_t err_cur;      //当前偏差值
    int16_t err_last;     //上一次偏差值
    int16_t err_sum;      //累加偏差
}PID_ValueStr;;  
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*! \note initialize application
 *  \param none
 *  \retval true platform initialization succeeded.
 *  \retval false platform initialization failed
 */
/*! \brief   
 *! \param  
 *! \retval  
 *! \retval  
 */
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
 //Init
//名称: 获取PID调节值
//功能:  
//入口:  无
//出口:  uint16_t  adc的值
uint16_t PID_get_pid_value(PID_ValueStr *_in_pidValue,uint8_t mode);
#endif
/* EOF */
