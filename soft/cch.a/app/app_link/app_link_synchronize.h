#ifndef app_modbus_synchronize_H
#define app_modbus_synchronize_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define OCCUPY_PAD_POWER                     0X01
#define OCCUPY_PAD_SET_COLD_TEMP             0X02
#define OCCUPY_PAD_SET_HEAT_TEMP             0X04
#define OCCUPY_PAD_CHILD_LOCK                0X08
#define OCCUPY_PAD_SET_FAN                   0X10
#define OCCUPY_PAD_TWO_CNONTROL_MODE         0X20

#define OCCUPY_PAD_BIND_MESSAGE              0X40
#define OCCUPY_PAD_STATUS_MESSAGE            0X80
#define OCCUPY_PAD_MEASURE_MESSAGE           0X0100
#define OCCUPY_PAD_ADV_MESSAGE               0X0200//末端高级设置
#define OCCUPY_PAD_SYSTEM_MESSAGE            0X0400
#define OCCUPY_PAD_SYSTEM_RTC                0X0800

#define OCCUPY_SYSTEM_POWER                             0X0001//系统开关机
#define OCCUPY_SYSTEM_RUN_MODE                          0X0002//系统运行模式 
#define OCCUPY_SYSTEM_WIND_SET_CLOD_TEMP                0X0004//通风制冷设定温度(控制回风温度)
#define OCCUPY_SYSTEM_WIND_SET_HEAT_TEMP                0X0008//通风制热设定温度(控制回风温度)  
#define OCCUPY_SYSTEM_WIND_SET_HUM                      0X0010//通风制冷/除湿模式设定相对湿度    
#define OCCUPY_SYSTEM_WIND_SET_SPEED                    0X0020//通风设定风速 
#define OCCUPY_SYSTEM_WATER_SET_CLOD_TEMP               0X0040//主机制冷模式设定水温
#define OCCUPY_SYSTEM_WATER_SET_HEAT_TEMP               0X0080//主机制热模式设定水温
#define OCCUPY_SYSTEM_WATER_SET_LIVING_TEMP             0X0100//主机生活热水设定水温
#define OCCUPY_SYSTEM_MIXWATER_SET_CLOD_TEMP            0X0200//混水制冷设定温度 
#define OCCUPY_SYSTEM_MIXWATER_SET_HEAT_TEMP            0X0400//混水制热设定温度
#define OCCUPY_SYSTEM_MIXWATER_AI_ENABLE                0X0800//输配混水AI使能
#define OCCUPY_SYSTEM_MIXWATER_LOW_TEMP_PROTECT         0X1000//输配防冻保护
#define OCCUPY_SYSTEM_MIXWATER_AI_DEST_TEMP             0X2000//输配混水AI目标温度 
#define OCCUPY_SYSTEM_LIS_NEW_AIR_PWM                   0X4000//新风PWM值
#define OCCUPY_SYSTEM_LIS_BACK_AIR_PWM                  0X8000//回风PWM值
#define OCCUPY_SYSTEM_LIS_OUTDOOR_WEATHER               0X00010000//户外温湿度
#define OCCUPY_SYSTEM_LIS_BEFORE_FU_WEATHER             0X00020000//氟盘前温湿度
#define OCCUPY_SYSTEM_LIS_AFTER_FU_WEATHER              0X00040000//氟盘后温湿度
#define OCCUPY_SYSTEM_LIS_BACK_AIR_WEATHER              0X00080000//回风口综合传感器
#define OCCUPY_SYSTEM_LIS_EXHAST_AIR_WEATHER            0X00100000//排风口温湿度
#define OCCUPY_SYSTEM_LIS_DEAD_ZONE                     0X00200000//通风湿度带宽 
#define OCCUPY_SYSTEM_LIS_OUT_VALVE                     0X00400000//新风风机转速
#define OCCUPY_SYSTEM_LIS_OUT_STATUS                    0X00800000//环控主机故障字
#define OCCUPY_SYSTEM_LIS_MIXWATER_OUT                  0X01000000//输配水泵状态
#define OCCUPY_SYSTEM_LIS_MAIN_MACHINE_TEMP             0X02000000//主机供水温度
#define OCCUPY_SYSTEM_LIS_MIXWATER_TEMP                 0X04000000//输配进水温度T11
#define OCCUPY_SYSTEM_LIS_RTC                           0X08000000//系统RTC
#define OCCUPY_SYSTEM_LIS_485_PAREMETER                 0X10000000//485参数
#define OCCUPY_SYSTEM_COLD_WARM_BACK_WATER              0X80000000
#define DELAY_OCCPUY              900
#define MAX_FAIL_COUNT            10
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//interface list  4
1:同步任务:调度器使用         
void app_link_syn_task(void);  

2:数据压入接口:调度器使用
void app_link_syn_push_receive_data(uint8_t in_solidNum,bgk_comm_buff_def *in_rev_data);

3:对外同步接口
void app_link_syn_push_outside_updata_word(uint8_t in_solidNum，uint32_t in_updataWord);

--------------------------------E N D-----------------------------------------*/
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++*/
//序号: 1  
//名称: app_link_syn_task
//功能: 注册列表维护:调度器使用
//入口: 无                           
//出口: 无
void app_link_syn_task(void);
uint8_t test_pull_syn_status(void);
//------------------------------E N D-------------------------------------------

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++*/
//序号: 2
//名称: app_link_syn_push_receive_data
//功能: 数据压入接口:调度器使用
//入口: in_solidNum 对应实例   in_rev_data  接收到的数据                       
//出口: 无
void app_link_syn_push_receive_data(uint8_t in_solidNum,bgk_comm_buff_def *in_rev_data);
//------------------------------E N D-------------------------------------------

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++*/
//序号: 3
//名称: app_link_syn_push_outside_updata_word
//功能:对外同步接口
//入口: in_solidNum 对应实例     in_updataWord:数据点更新字                          
//出口: 
void app_link_syn_push_outside_updata_word(uint8_t in_solidNum,uint32_t in_updataWord);

void app_link_syn_push_pad_updata_word(uint8_t in_prot,uint32_t in_updataWord);

uint8_t pull_syn_main_status(void);
//------------------------------E N D-------------------------------------------




//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif