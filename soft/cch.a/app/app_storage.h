//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef app_storage_H
#define app_storage_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef enum
{
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
   AIR_WIND_HEAT         = 0x00,  //热交换(新风)
   AIR_WIND_BYPASS       = 0x01,  //旁通
   AIR_WIND_INLOOP       = 0x02,  //内循环
}airWindPathStatus_Def;

typedef enum
{
   METHOD_BASIC     = 0x00,  //基础策略
   METHOD_ONE       = 0x01,  //策略一
   METHOD_TWO       = 0x02,  //策略二
}control_method_Def;

typedef enum
{   
    AutoFanSet   =0x00,
    LowFanSet    =0x01,
    MiddleFanSet =0x02,
    HighFanSet   =0x03,

}NewAirLevelSet_Def;

typedef union
{
    sdt_int32u sto_data[256];
    struct
    {
        uint8_t                  localId[6];               //本地ID
        uint8_t                  deviceAddress;            //485地址
        uint8_t                  baudrateValue;            //485波特率
        uint8_t                  evenOddCheck;             //485奇偶校验位 
        uint8_t                  stopBit;                  //停止位  
        uint8_t                  drainWaterError;          //排水故障  
        uint8_t                  newAirLowPwm;
        uint8_t                  newAirMidPwm;
        uint8_t                  newAirHighPwm;
        uint8_t                  backAirLowPwm;
        uint8_t                  backAirMidPwm;
        uint8_t                  backAirHighPwm;
        uint8_t                  airInFanPwmValue_Low;      //10-100
        uint8_t                  airInFanPwmValue_Middle;   
        uint8_t                  airInFanPwmValue_High;
        uint8_t                  airOutFanPwmValue_Low;     //10-100
        uint8_t                  airOutFanPwmValue_Middle;  
        uint8_t                  airOutFanPwmValue_High;
        control_method_Def       control_method;          //控制策略
        AirRunMode_Def           airRunmode;           //运行模式
        NewAirLevelSet_Def       NewAirLevelSet;       //设定风速 
        uint16_t                 DeviceStatusWord;     //状态字   开关机  目前没用      
        uint16_t                 PM25_DeadZone;        //PM25死区值  目前没用      
        uint16_t                 CO2_DeadZone;         //CO2死区值	目前没用      	      
        int16_t                  humidity_set;         //设定湿度      
        int16_t                  hotTemp_set;          //制冷回风设定温度(控制回风温度)
		int16_t                  coldTemp_set;         //制热回风设定温度     
        int16_t                  set_cold_water_temp;   //主机制冷模式出水设定水温
        int16_t                  config_hum_set;        //除湿设定配置
        int16_t                  cold_wind_max_temp_set;//制冷风温最大设定温度
        int16_t                  heat_wind_min_temp_set;//制热风温最小设定温度 
        int16_t                  heat_wind_max_temp_set;//制热风温最大设定温度
        int16_t                  cold_no_need_temp_set;//无能需设定温度
        int16_t                  cold_fan_need_temp_set;//风盘能需设定温度   
        int16_t                  cold_warm_need_temp_set;//辐射能需设定温度   
        int16_t                  config_lew_temp_set;    //露点温度配置   
        int16_t                  set_heat_water_temp;   //主机制热模式出水设定水温
        int16_t                  heat_no_need_temp_set;//无能需设定温度
        int16_t                  heat_fan_need_temp_set;//风盘能需设定温度   
        int16_t                  heat_warm_need_temp_set;//辐射能需设定温度   
        int16_t                  config_back_wind_temp_set; //回风温度配置   
        int16_t                  set_living_water_temp; //主机生活热水设定水温
        int16_t                  humidity_DeadZone;     //通风湿度带宽 
        int16_t                  temp_DeadZone;         //通风温度带宽 
        int16_t                  adjust_outdoor_hum;    //户外
        int16_t                  adjust_outdoor_temp;
        int16_t                  adjust_outdoor_co2;
        int16_t                  adjust_outdoor_pm25;
        int16_t                  adjust_befor_fu_hum;    //氟盘后
        int16_t                  adjust_befor_fu_temp;
        int16_t                  adjust_befor_fu_co2;
        int16_t                  adjust_befor_fu_pm25;
        int16_t                  adjust_after_fu_hum;   //氟盘前
        int16_t                  adjust_after_fu_temp;
        int16_t                  adjust_after_fu_co2;
        int16_t                  adjust_after_fu_pm25;
        int16_t                  adjust_back_air_hum;   //回风口
        int16_t                  adjust_back_air_temp;
        int16_t                  adjust_back_air_co2;
        int16_t                  adjust_back_air_pm25;
        int16_t                  adjust_exhast_air_hum;  //排风
        int16_t                  adjust_exhast_air_temp;
        int16_t                  adjust_exhast_air_co2;
        int16_t                  adjust_exhast_air_pm25;    
        uint16_t                 freshair_effciency;     
        uint16_t                 hotwater_enable;       //热水使能
        uint16_t                 cool_backwater_settemp; 
        uint16_t                 hot_backwater_settemp; 
        uint16_t				 filter_time;          //滤芯更换周期
		uint16_t				 filter_usetime;       //滤芯使用时间
        bool                     mildewFlag;           //除霉  未使用
        bool                     systemPower;          //开关机
        bool                     wind_value;           //风阀切换
        bool                     debug_enable;         //调试使能
    };
}StoRunParamter_Def;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void app_read_run_parameter(void);
void app_sto_run_parameter_task(void);
void app_push_once_save_sto_parameter(void);
uint8_t * app_pull_local_id(void);
void RestoreFactoryStorage(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
extern StoRunParamter_Def  StoRunParameter;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
