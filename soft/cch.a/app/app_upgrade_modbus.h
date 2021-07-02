//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef __UPDATE_MODBUS_APP_H__
#define __UPDATE_MODBUS_APP_H__

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
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
//++++++++++++++++++++++++++++++++++End++++++++++++++++++++++++++++++++++++++++
