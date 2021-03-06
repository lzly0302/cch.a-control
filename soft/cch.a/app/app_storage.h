//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef app_storage_H
#define app_storage_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
    AIR_MODE_STOP             =0x00,  //停机
    AIR_MODE_COOL             =0x01,  //制冷
    AIR_MODE_HEAT             =0x02,  //制热
    AIR_MODE_HUMIDITY         =0x03,  //除湿
	AIR_MODE_FAN              =0x04,  //通风(热水)
	AIR_MODE_AUTO_COOL        =0x05,  //夏季自动
	AIR_MODE_AUTO_HEAT        =0x06,  //冬季自动
    AIR_MODE_WATER            =0x07,  //热水  
    AIR_MODE_NONE             =0XFF,
}AirRunMode_Def;


typedef enum
{   
    AutoFanSet   =0x00,
    LowFanSet    =0x01,
    MiddleFanSet =0x02,
    HighFanSet   =0x03,
}NewAirLevelSet_Def;

typedef enum
{
   METHOD_BASIC     = 0x00,  //基础策略
   METHOD_ONE       = 0x01,  //策略一
   METHOD_TWO       = 0x02,  //策略二
}control_method_Def;

typedef union
{
    sdt_int32u sto_data[256];
    struct
    {
        uint8_t                    localId[6];               //本地ID
        uint8_t                    deviceAddress;            //485地址
        uint8_t                    baudrateValue;            //485波特率
        uint8_t                    evenOddCheck;             //485奇偶校验位 
        uint8_t                    stopBit;                  //停止位   
        uint8_t                    lowTempProtectConfig;     //防冻温度，0为关闭
        control_method_Def         control_method;           //控制策略
        AirRunMode_Def             airRunmode;               //模式
        NewAirLevelSet_Def         NewAirLevelSet;           //设定风速
        int8_t                     coldDropDiff;             //露点带宽
        uint8_t                    hum_set;                  //设定湿度
        int16_t                    humidity_DeadZone;        //湿度带宽
        int16_t                    temp_DeadZone;            //温度带宽
        uint16_t                   mixColdSetTemp;           //混水制冷设定温度
        uint16_t                   mixHeatSetTemp;           //混水制热设定温度   
        int16_t                    lew_status_open_diff;     //露点开启带宽
        int16_t                    lew_status_close_diff;    //露点关闭带宽
        int16_t                    set_living_water_temp;   //主机生活热水设定水温
        int16_t                    set_cold_water_temp;     //主机制冷模式出水设定水温
        int16_t                    set_heat_water_temp;     //主机制热模式出水设定水温
        bool                       powerOffStatus;          //上电关机功能
        bool                       systemPower;             //开关机
        bool                       debug_enable;            //调试使能
        bool                       hotwater_enable;         //热水使能
    };
}StoRunParamter_Def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_read_run_parameter(void);
void app_sto_run_parameter_task(void);
void app_push_once_save_sto_parameter(void);
uint8_t * app_pull_local_id(void);
/*恢复出厂设置*/
void RestoreFactoryStorage(void);
//uint16_t app_storage_pull_pad_version(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern StoRunParamter_Def  StoRunParameter;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
