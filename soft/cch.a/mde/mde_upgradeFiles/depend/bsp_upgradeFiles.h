//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef _bsp_upgradeFiles_H
#define _bsp_upgradeFiles_H
//-----------------------------------------------------------------------------
#ifndef snail_data_types
    #include ".\snail_data_types.h"
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//------------------------------------------------------------------------------
//interface
//------------------------------------------------------------------------------
//名称:读取app区的信息内容32bytes
//入口:返回的数据指针

void bsp_read_information_user_app(sdt_int8u* out_pBuff);
//------------------------------------------------------------------------------
//名称:写入一个块的数据到upgrade 128bytes
//入口:块序号(从0开始)， 写入的数据指针

void bsp_write_block_user_upgrade(sdt_int16u in_block_num,sdt_int8u* in_pBuff);
//------------------------------------------------------------------------------
//名称:读取upgrade区的信息内容32bytes
//入口:返回的数据指针

void bsp_read_information_user_upgrade(sdt_int8u* out_pBuff);
//------------------------------------------------------------------------------
//名称:写入upgrade区的信息内容32bytes
//入口:写入的数据指针

void bsp_write_information_user_upgrade(sdt_int8u* in_pBuff);

//温控器面板升级区信息
void bsp_read_information_user_pad_upgrade(sdt_int8u* out_pBuff);
void bsp_write_information_user_pad_upgrade(sdt_int8u* in_pBuff);
void bsp_write_block_user_pad_upgrade(sdt_int16u in_block_num,sdt_int8u* in_pBuff);
//风盘控制器升级区信息
void bsp_read_information_user_fan_upgrade(sdt_int8u* out_pBuff);
void bsp_write_information_user_fan_upgrade(sdt_int8u* in_pBuff);
void bsp_write_block_user_fan_upgrade(sdt_int16u in_block_num,sdt_int8u* in_pBuff);
//环控中心升级区信息
void bsp_read_information_user_ae_upgrade(sdt_int8u* out_pBuff);
void bsp_write_information_user_ae_upgrade(sdt_int8u* in_pBuff);
void bsp_write_block_user_ae_upgrade(sdt_int16u in_block_num,sdt_int8u* in_pBuff);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++