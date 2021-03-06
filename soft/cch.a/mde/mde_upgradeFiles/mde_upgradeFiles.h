//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef mde_upgradeFiles_H
#define mde_upgradeFiles_H
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef snail_data_types
    #include ".\depend\snail_data_types.h"
#endif
typedef enum
{
   TYPE_PAD      = 0x00,  //温控器
   TYPE_FAN      = 0x01,  //风盘
   TYPE_CC       = 0x02,  //输配中心
   TYPE_HC       = 0x03,  //环控中心
}device_type_Def;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define BGEUERR_NoneError          0x00
#define BGEUERR_Length             0x01
#define BGEUERR_Version            0x02
#define BGEUERR_Command            0x03
#define BGEUERR_FileMapCheckSum    0x04
#define BGEUERR_FileCheckSum       0x05
#define BGEUERR_BlockNumber        0x06
#define BGEUERR_Fireware           0x07
#define BGEUERR_Other              0xFE
#define HARDWARE_AIO5              0xAC02
//task++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void mde_upgrade_files_task(void);
//interface+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//名称:推入一个块的数据到文件模块
//入口:块序号、块数据指针，块大小默认为128bytes
//出口:错误指示

sdt_int16u mde_push_files_one_block(sdt_int16u in_block_num,sdt_int8u* in_pBuff);
//--------------------------------------------------------------------------------------------------------------------------
//名称:推入文件分布maps数据到文件模块
//入口:map数据指针(128bytes)，是否续传 sdt_true 续传
//出口:错误指示

sdt_int8u mde_push_fileMap(sdt_int8u* in_pBuff,sdt_bool in_resume);
//--------------------------------------------------------------------------------------------------------------------------
//名称:获取下一个数据块的序号值
//入口:序号块指针
//出口:是否传输完毕，sdt_true -- 传输完毕

sdt_bool mde_pull_upgrade_next_block(sdt_int16u* out_pBlock_num);
//面板需要升级
sdt_bool mde_upgrade_pull_pad_status(void);
void mde_upgrade_clear_pad_status(void);
void mde_upgrade_set_pad_status(void);
//环控中心需要升级
sdt_bool mde_upgrade_pull_ae_status(void);
void mde_upgrade_clear_ae_status(void);
//风盘需要升级
sdt_bool mde_upgrade_pull_fan_status(void);
void mde_upgrade_clear_fan_status(void);
//end+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++