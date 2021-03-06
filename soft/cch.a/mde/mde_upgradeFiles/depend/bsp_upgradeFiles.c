//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\snail_data_types.h"
#include "gd32f4xx.h"
#include "..\..\mde_w25q64\mde_w25q64.h"
#include "..\..\mde_watchDog\mde_watchDog.h"
#include "..\..\..\pbc\pbc_dataConvert\pbc_dataConvert.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//flash map gd32f407vet6
//512k flash
//0x0800 0000 -- 0x0807 FFFF
//boot
//0x0800 0000 -- 0x0800 3FFF     16k     
//user.app 运行区
//0x0800 4000 -- 0x0803 FFFF     240k  
//user.upgrade 升级区
//0x10000 -- 0x4bFFF             240k   
//reserve                    
//0x0804 0000 -- 0x0807 FFFF     256k
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define user_app_start_addr      0x08004000
#define user_app_inf_addr        0x0803FFE0
#define user_upgrade_start_addr  0x10000
#define user_upgrade_inf_addr    0x4BfE0
#define page_unit_size           4096
#define information_size         32
#define user_upgrade_inf_page    0x4B000
//温控器面板升级区地址0x90000-0xCffff   256K
#define user_upgrade_pad_start_addr  0x90000//温控器升级程序存储地址
#define user_upgrade_pad_inf_addr    0xCFFE0
#define user_upgrade_pad_inf_page    0xCF000
#define user_upgrade_pad_inf_version_addr    0xCFFCE  //版本号存储地址
//风盘控制器升级区地址0xd0000-0x10ffff   256K
#define user_upgrade_fan_start_addr  0xD0000//风盘控制器升级程序存储地址
#define user_upgrade_fan_inf_addr    0x10FFE0
#define user_upgrade_fan_inf_version_addr    0x10FFCE  //版本号存储地址
#define user_upgrade_fan_inf_page    0x10F000
//环控中心升级区地址0x50000-0x8ffff   256K
#define user_upgrade_ae_start_addr   0x50000//环控中心升级程序存储地址
#define user_upgrade_ae_inf_addr     0x8FFE0
#define user_upgrade_ae_inf_page     0x8F000
//------------------------------------------------------------------------------
//名称:读取app区的信息内容32bytes
//入口:返回的数据指针

void bsp_read_information_user_app(sdt_int8u* out_pBuff)
{
    sdt_int8u *pAddr;
    sdt_int8u i;
    pAddr = (sdt_int8u*)user_app_inf_addr;
    for(i = 0;i < information_size;i++)
    {
        *out_pBuff = *pAddr;
        pAddr ++;
        out_pBuff ++;
    }
}
//------------------------------------------------------------------------------
//名称:写入一个块的数据到upgrade 128bytes
//入口:块序号(从0开始)， 写入的数据指针
//uint8_t readBbuff[128];
void bsp_write_block_user_upgrade(sdt_int16u in_block_num,sdt_int8u* in_pBuff)
{
    sdt_int32u falsh_addr;
    
    falsh_addr = user_upgrade_start_addr + in_block_num*128;
    if(0 == (falsh_addr%page_unit_size))  //4k地址
    {
         SPI_FLASH_SectorErase(falsh_addr);
    }
    SPI_FLASH_BufferWrite(in_pBuff,falsh_addr,128);
}
//------------------------------------------------------------------------------
//名称:读取upgrade区的信息内容32bytes
//入口:返回的数据指针

void bsp_read_information_user_upgrade(sdt_int8u* out_pBuff)
{
   SPI_FLASH_BufferRead(out_pBuff,user_upgrade_inf_addr,information_size);
}
//------------------------------------------------------------------------------
//名称:写入upgrade区的信息内容32bytes
//入口:写入的数据指针

void bsp_write_information_user_upgrade(sdt_int8u* in_pBuff)
{
    sdt_int32u falsh_addr;
    sdt_int32u upgrade_falsh_addr;
    falsh_addr = user_upgrade_inf_page;
    SPI_FLASH_SectorErase(falsh_addr);
    upgrade_falsh_addr = user_upgrade_inf_addr;
    SPI_FLASH_BufferWrite(in_pBuff,upgrade_falsh_addr,32);  
}
//温控器面板升级区信息
void bsp_read_information_user_pad_upgrade(sdt_int8u* out_pBuff)
{
   SPI_FLASH_BufferRead(out_pBuff,user_upgrade_pad_inf_addr,information_size);
}
void bsp_write_information_user_pad_version_upgrade(sdt_int8u* in_pBuff,sdt_int8u* in_version)
{
    sdt_int32u falsh_addr;
    sdt_int32u upgrade_falsh_addr;
    falsh_addr = user_upgrade_pad_inf_page;
    SPI_FLASH_SectorErase(falsh_addr);
    upgrade_falsh_addr = user_upgrade_pad_inf_addr;
    SPI_FLASH_BufferWrite(in_pBuff,upgrade_falsh_addr,32);  
    upgrade_falsh_addr = user_upgrade_pad_inf_version_addr;
    SPI_FLASH_BufferWrite(in_version,upgrade_falsh_addr,2);
}
void bsp_write_information_user_pad_upgrade(sdt_int8u* in_pBuff)
{
    sdt_int32u falsh_addr;
    sdt_int32u upgrade_falsh_addr;
    falsh_addr = user_upgrade_pad_inf_page;
    SPI_FLASH_SectorErase(falsh_addr);
    upgrade_falsh_addr = user_upgrade_pad_inf_addr;
    SPI_FLASH_BufferWrite(in_pBuff,upgrade_falsh_addr,32);  
}
void bsp_write_block_user_pad_upgrade(sdt_int16u in_block_num,sdt_int8u* in_pBuff)
{
    sdt_int32u falsh_addr;
    
    falsh_addr = user_upgrade_pad_start_addr + in_block_num*128;
    if(0 == (falsh_addr%page_unit_size))  //4k地址
    {
         SPI_FLASH_SectorErase(falsh_addr);
    }
    SPI_FLASH_BufferWrite(in_pBuff,falsh_addr,128);
}

//风盘控制器升级区信息
void bsp_read_information_user_fan_upgrade(sdt_int8u* out_pBuff)
{
   SPI_FLASH_BufferRead(out_pBuff,user_upgrade_fan_inf_addr,information_size);
}
void bsp_write_information_user_fan_version_upgrade(sdt_int8u* in_pBuff,sdt_int8u* in_version)
{
    sdt_int32u falsh_addr;
    sdt_int32u upgrade_falsh_addr;
    falsh_addr = user_upgrade_fan_inf_page;
    SPI_FLASH_SectorErase(falsh_addr);
    upgrade_falsh_addr = user_upgrade_fan_inf_addr;
    SPI_FLASH_BufferWrite(in_pBuff,upgrade_falsh_addr,32);
    upgrade_falsh_addr = user_upgrade_fan_inf_version_addr;
    SPI_FLASH_BufferWrite(in_version,upgrade_falsh_addr,2);  
}

void bsp_write_block_user_fan_upgrade(sdt_int16u in_block_num,sdt_int8u* in_pBuff)
{
    sdt_int32u falsh_addr;
    
    falsh_addr = user_upgrade_fan_start_addr + in_block_num*128;
    if(0 == (falsh_addr%page_unit_size))  //4k地址
    {
        SPI_FLASH_SectorErase(falsh_addr);
    }
    SPI_FLASH_BufferWrite(in_pBuff,falsh_addr,128);
}

//环控中心升级区信息
void bsp_read_information_user_ae_upgrade(sdt_int8u* out_pBuff)
{
   SPI_FLASH_BufferRead(out_pBuff,user_upgrade_ae_inf_addr,information_size);
}
void bsp_write_information_user_ae_upgrade(sdt_int8u* in_pBuff)
{
    sdt_int32u falsh_addr;
    sdt_int32u upgrade_falsh_addr;
    falsh_addr = user_upgrade_ae_inf_page;
    SPI_FLASH_SectorErase(falsh_addr);
    upgrade_falsh_addr = user_upgrade_ae_inf_addr;
    SPI_FLASH_BufferWrite(in_pBuff,upgrade_falsh_addr,32);  
}
void bsp_write_block_user_ae_upgrade(sdt_int16u in_block_num,sdt_int8u* in_pBuff)
{
    sdt_int32u falsh_addr;
    
    falsh_addr = user_upgrade_ae_start_addr + in_block_num*128;
    if(0 == (falsh_addr%page_unit_size))  //4k地址
    {
        SPI_FLASH_SectorErase(falsh_addr);
    }
    SPI_FLASH_BufferWrite(in_pBuff,falsh_addr,128);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++