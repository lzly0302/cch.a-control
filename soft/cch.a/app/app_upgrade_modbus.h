//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __UPDATE_MODBUS_APP_H__
#define __UPDATE_MODBUS_APP_H__
typedef enum
{
   BACKUP_IDLE                  =0x0000,//????״̬
   BACKUP_UPDATING              =0x0001,//????״̬
   BACKUP_FINISH                =0x0002,//????????
   BACKUP_CHECKSUM_ERROR        =0x0004,//У??????
   BACKUP_VERSION_TYPE_ERROR    =0x0008,//?̼?????
   BACKUP_SERIOL_ERROR          =0x0010,//???????Ŵ???
   BACKUP_OTHER_ERROR           =0x0020,//????????
}updateStatusW_def;  //״̬??
/*============================ INCLUDES ======================================*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
//Task
//-----------------------------------------------------------------------------
//Event
//-----------------------------------------------------------------------------
//Status
//-----------------------------------------------------------------------------
//Function
void app_updataBackup_readRegister(uint16_t regAddr,uint16_t* pDataBuff);
void app_updataBackup_writeRegister(uint16_t regAddr,uint16_t pDataBuff);
updateStatusW_def app_updaBackup_pull_status(void);
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
//++++++++++++++++++++++++++++++++++End++++++++++++++++++++++++++++++++++++++++
