//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _MOD_W25Q64_H
#define _MOD_W25Q64_H
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include <stdint.h>
#include <stdbool.h>
//------------------------------E N D-------------------------------------------

/* Private typedef -----------------------------------------------------------*/
#define  sFLASH_ID                        0XEF6017     //W25Q64

//#define SPI_FLASH_PageSize            4096
#define SPI_FLASH_PageSize              256
#define SPI_FLASH_PerWritePageSize      256
#define STORAGE_ADDRESS                 0
#define PAD_UPDATA_TUF_ADDRESS          0x90000
#define AE_UPDATA_TUF_ADDRESS           0x50000
#define FAN_UPDATA_TUF_ADDRESS          0xd0000
/* Private define ------------------------------------------------------------*/
/*命令定义-开头*******************************/
#define W25X_WriteEnable		      0x06 
#define W25X_WriteDisable		      0x04 
#define W25X_ReadStatusReg		      0x05 
#define W25X_WriteStatusReg		      0x01 
#define W25X_ReadData			      0x03 
#define W25X_FastReadData		      0x0B 
#define W25X_FastReadDual		      0x3B 
#define W25X_PageProgram		      0x02 
#define W25X_BlockErase			      0xD8 
#define W25X_SectorErase		      0x20 
#define W25X_ChipErase			      0xC7 
#define W25X_PowerDown			      0xB9 
#define W25X_ReleasePowerDown	      0xAB 
#define W25X_DeviceID			      0xAB 
#define W25X_ManufactDeviceID   	  0x90 
#define W25X_JedecDeviceID		      0x9F 

#define WIP_Flag                      0x01  /* Write In Progress (WIP) flag */
#define Dummy_Byte                    0xFF
/*命令定义-结尾*******************************/

/*等待超时时间*/
#define SPIT_FLAG_TIMEOUT         ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT         ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))
/*参数初始化*/
void SPI_FLASH_Init(void);
/*擦除FLASH扇区*/
void SPI_FLASH_SectorErase(uint32_t SectorAddr);
/*整片擦除*/
void SPI_FLASH_BulkErase(void);
/*写入数据*/
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
/*读取数据*/
void SPI_FLASH_BufferRead(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
uint32_t SPI_FLASH_ReadID(void);
uint32_t SPI_FLASH_ReadDeviceID(void);
#endif
/* __SPI_FLASH_H */
