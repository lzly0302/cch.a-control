/*============================ INCLUDES ======================================*/
#include ".\APP_Cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define REG_UPDATA_STAR_WORD             0x1800
#define REG_UPDATA_VERSION               0x1801
#define REG_TOTAL_MESAAGE_NUM            0x1802
#define REG_CHECKSUM_HIGH                0x1805
#define REG_CHECKSUM_LOW                 0x1806

#define REG_SLAVE_STATUS_WORD            0x1810
#define REG_REQUEST_SERIAL               0x1811

#define REG_UPDATA_CURRENT_SERIAL         0x187F  //129 register
#define REG_MESSAGE_FIRST_TWO_BYTE        0x1880
#define REG_MESSAGE_LAST_TWO_BYTE         0x18BF

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define STAR_UPDATA_WORD      0x3589  //升级字
#define RESTAR_UPDATA_WORD    0x3795  //重新开始升级
#define UPDATA_VERSION        0x0001  //升级方法版本
#define MIN_MESSAGE_NUM       3//10
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint16_t currentSerial = 0;//当前序列号
//-----------------------------------------------------------------------------


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
updateStatusW_def    slaveStatusWord = BACKUP_IDLE;
updateStatusW_def app_updaBackup_pull_status(void)
{
    return slaveStatusWord;
}
static updateStatusW_def lastSlaveStatus = BACKUP_IDLE;
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//-----------------------------------------------------------------------------
void app_updataBackup_readRegister(uint16_t regAddr,uint16_t* pDataBuff)
{
    switch(regAddr)
    {
        case REG_SLAVE_STATUS_WORD:
        {//从机状态字
            *pDataBuff = slaveStatusWord;
            break;
        }
        case REG_REQUEST_SERIAL:
        {//从机报文当前需求序号
            sdt_bool completed;
            sdt_int16u next_block_number;
            if(lastSlaveStatus != slaveStatusWord)
            {
                lastSlaveStatus = slaveStatusWord;
                *pDataBuff = 0;
            }
            else
            {
                completed = mde_pull_upgrade_next_block(&next_block_number);
                if(completed)
                {
                     slaveStatusWord = BACKUP_IDLE;//空闲状态
                     lastSlaveStatus = BACKUP_IDLE;
                     
                }
                else
                {
                    *pDataBuff = next_block_number;//序列号
                }
            }
            break;
        } 
        default:
        {
            break;
        }
    }  
}

void app_updataBackup_writeRegister(uint16_t regAddr,uint16_t pDataBuff)
{
    static uint8_t buff[128];
    static uint16_t totalNum = 0;
    uint8_t error = 0;
    if((regAddr>=REG_MESSAGE_FIRST_TWO_BYTE)&&(regAddr<=REG_MESSAGE_LAST_TWO_BYTE))
    {//接收128byte数据
        buff[(regAddr - REG_MESSAGE_FIRST_TWO_BYTE) << 1] = (uint8_t)(pDataBuff>>8);
        buff[((regAddr - REG_MESSAGE_FIRST_TWO_BYTE) << 1) +1] = (uint8_t)(pDataBuff);
        if(regAddr==REG_MESSAGE_LAST_TWO_BYTE)
        {
            if(currentSerial == 0)
            {
                error = mde_push_fileMap(buff,sdt_false);//压入描述区数据
                if(error == 0x08)
                {//版本错误
                    slaveStatusWord = BACKUP_VERSION_TYPE_ERROR;
                }
            }
            else
            {
                mde_push_files_one_block(currentSerial,buff);  //压入报文数据
            }           
        }
    }
    else
    {
        switch(regAddr)
        {
            case REG_UPDATA_STAR_WORD:
            {//升级启动字 
                if((STAR_UPDATA_WORD==pDataBuff) || (RESTAR_UPDATA_WORD==pDataBuff))
                {                                
                    slaveStatusWord=BACKUP_UPDATING;//升级中
					lastSlaveStatus = BACKUP_IDLE;
                    currentSerial = 0;
                }
                break;
            }
            case REG_UPDATA_VERSION:
            { //升级方法版本
                break;
            }
            case REG_TOTAL_MESAAGE_NUM:
            {  //报文总序号   
                totalNum = pDataBuff;
                break;
            }
            case REG_CHECKSUM_HIGH:
            {
                break;
            }
            case REG_CHECKSUM_LOW:
            { 
                break;
            }
            case REG_UPDATA_CURRENT_SERIAL:
            {//当前序号
                currentSerial = pDataBuff;
                if(currentSerial == totalNum)
                {
                    slaveStatusWord=BACKUP_FINISH;//升级完成
                }
                break;
            }  
            default:
            {
                break;
            }
        }  
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++