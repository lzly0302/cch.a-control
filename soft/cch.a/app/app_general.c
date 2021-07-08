//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
#include "stdlib.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define  feedbcak_wind_error             sdt_bit0        //转速故障
#define  rs1001_offline                  sdt_bit1       //综合传感器故障
#define  ONE_HOUR                        1800
/*system run status*/
typedef struct
{//面板数据   
        uint32_t   dpStamp[MAX_DATA_POINT_LEN_PAD];
        uint16_t   padErrorWord;//面板故障字
        uint16_t   deviceType;//设备类型 
        uint16_t   version_pad;//面板版本號
        uint16_t   outputFanSpeed;//转速
        int16_t    measureTemp;//测量温度
        uint16_t   humility;//湿度
        uint16_t   set_coldTemp;//制冷设定温度
        uint16_t   set_warmTemp;//采暖设定温度
        uint16_t   adjTemp;//校温
        uint16_t   coldCollaDiff;//制冷协同带宽
        uint16_t   warmCollaDiff;//采暖协同带宽
        int16_t   coldComfortTemp;//制冷舒适温度
        int16_t   warmComfortTemp;//采暖舒适温度    
        int16_t   minSetTemp;//最小设定温度
        int16_t   maxSetTemp;//最大设定温度
        int16_t   lewDropTemp;//露点温度
        uint16_t   sameIdList;//相同ID列表
        uint16_t   pad_bind_warm;//辐射绑定列表
        uint16_t   pad_bind_fan;//风盘绑定列表
        uint16_t   bindError;    //绑定故障  
        int16_t    adjust_temp;//校温
        int16_t    adjust_hum;//校湿
        uint16_t   warmNedd;//辐射阀门需求
        uint16_t   fanNedd;//风机阀门需求
        uint8_t    type_warm_choose;//辐射类型
        timerClock_def  id_ocupy_delay;//ID占用
        uint8_t    deviceId[6]; 
        uint8_t    lowFanPwm;//
        uint8_t    midFanPwm;
        uint8_t    highFanPwm;   
        uint8_t    chDevicePowerStatus;//开关机
        uint8_t    padHcmode;//冷热模式
        uint8_t    setFanSpeed;//设定风速  
        uint8_t    outFanSpeed;//输出风速  
        uint8_t    bandDifferent;//带宽   
        uint8_t    coldDropDiff;//冷凝带宽
        uint8_t    freezeTemp;//防冻温度   
        uint8_t    contror_num;//末端数量
        uint8_t    two_output_mode;//双末端模式选择 
        uint8_t    room_area;//房间面积 
        bool       coldCollaEnable;//制冷协同使能
        bool       warmCollaEnable;//采暖协同使能
        bool       output_terminal;   //终端输出
        bool       onlineFlag;//在线状态
        bool       sensorErrorFlag;//传感器错误
        bool       fanControlFalg;//风机受控
        bool       lockFlag;//锁键
        bool       powerOffFlag;//上电关机
        bool       lowTempProtectFlag;//防冻保护
        bool       lewDropProtect;//露点保护
        bool       idUsedFlag;//id使用标志
        bool       output_remote;//远程输出
}control_masterPara_t;

typedef struct
{//共用数据    
       
        uint16_t                   word_error;              //故障字   
        uint16_t                   system_ntc_error;       //系统传感器故障  
        uint16_t                   ae_ntc_error;            //环控传感器故障  
        uint16_t                   ac_ntc_error;            //输配传感器故障  
        int16_t                    dewPointTemp;            //露点温度   
        int16_t                    destTemp;                //目标温度  
        uint16_t                   system_error_word;       //主机集成故障字
        uint16_t                   ac_error_word;           //输配故障字
        uint16_t                   ae_error_word;           //环控故障字
        uint16_t                   unbind_warm;             //辐射未绑定列表
        uint16_t                   unbind_fan;              //风盘未绑定列表
        uint16_t                   repeat_bind;             //辐射重复绑定列表
        uint16_t                   system_status_word;      //系统状态字
        uint16_t                   pad_output_status;       //末端输出状态
        int16_t                    set_cold_water_temp;
        int16_t                    set_heat_water_temp;
        int16_t                    set_living_water_temp;
        int16_t                    outdoor_temp;
        int16_t                    outdoor_hum;
        int16_t                    before_fu_temp;
        int16_t                    before_fu_hum;
        int16_t                    after_fu_temp;
        int16_t                    after_fu_hum;
        int16_t                    back_air_temp;
        int16_t                    back_air_hum;
        int16_t                    exhast_air_temp;
        int16_t                    exhast_air_hum;
        int16_t                    back_air_co2;
        int16_t                    back_air_pm25;
        int16_t                    deadzone_fan_hum;
        int16_t                    deadzone_fan_temp;
        uint16_t                   new_air_speed;
        uint16_t                   back_air_speed;
        uint16_t                   water_machine_fre;
        uint16_t                   fu_machine_fre;
        int16_t                    master_supply_temp;
        int16_t                    master_living_temp;
        int16_t                    master_outdoor_temp;
        int16_t                    adjust_outdoor_hum;
        int16_t                    adjust_outdoor_temp;
        int16_t                    adjust_outdoor_co2;
        int16_t                    adjust_outdoor_pm25;
        int16_t                    adjust_befor_fu_hum;
        int16_t                    adjust_befor_fu_temp;
        int16_t                    adjust_befor_fu_co2;
        int16_t                    adjust_befor_fu_pm25;
        int16_t                    adjust_after_fu_hum;
        int16_t                    adjust_after_fu_temp;
        int16_t                    adjust_after_fu_co2;
        int16_t                    adjust_after_fu_pm25;
        int16_t                    adjust_back_air_hum;
        int16_t                    adjust_back_air_temp;
        int16_t                    adjust_back_air_co2;
        int16_t                    adjust_back_air_pm25;
        int16_t                    adjust_exhast_air_hum;
        int16_t                    adjust_exhast_air_temp;
        int16_t                    adjust_exhast_air_co2;
        int16_t                    adjust_exhast_air_pm25;
		int16_t                    hot_backwater_settemp; 
		int16_t                    cool_backwater_settemp;
        uint16_t                   lewTempStatus;//露点状态
        uint16_t                   hotwater_enable;//热水使能
        uint16_t				   filter_time;//滤芯更换周期
		uint16_t				   filter_usetime;//滤芯使用时间
        uint16_t                   system_reset_word;//系统复位字
        uint8_t                    valveOpenDegree;         //阀门开度          
        uint8_t                    newAirLowPwm;
        uint8_t                    newAirMidPwm;
        uint8_t                    newAirHighPwm;
        uint8_t                    backAirLowPwm;
        uint8_t                    backAirMidPwm;
        uint8_t                    backAirHighPwm;
        control_masterPara_t       padPara[MASTER_PAD_NUM];//面板参数 
        bool                       output_pump;          //水泵输出
        bool                       output_threeWayValve;  //三通阀输出
        bool                       energyNeed;               //环控能需预冷阀
        bool                       remoteControlFlag;     //远程受控
        bool                       wind_value; //风阀切换
        bool                       debug_enable;//调试使能
        bool                       indoor_dehum_status;//户外除湿状态 
        bool                       water_machine_status:1;//水机状态
        uint32_t                   dpStamp[MAX_DATA_POINT_LEN_SYSTEM];
}SysPara_t;

SysPara_t s_sysPara = {
    .destTemp = 200,
    .unbind_warm = 0x0fff,             //辐射未绑定列表
    .unbind_fan = 0x0fc0,              //风盘未绑定列表
    .newAirLowPwm = 30,
    .newAirMidPwm = 60,
    .newAirHighPwm = 90,
    .backAirLowPwm = 30,
    .backAirMidPwm = 60,
    .backAirHighPwm = 90,
    .set_cold_water_temp = 100,
    .set_heat_water_temp = 400,
    .set_living_water_temp = 500,
    .outdoor_temp = 220,
    .outdoor_hum = 60,
    .before_fu_temp = 220, 
    .before_fu_hum = 60,
    .after_fu_temp = 220,
    .after_fu_hum = 60,
    .back_air_temp = 220,
    .back_air_hum = 60,
    .exhast_air_temp = 220,
    .exhast_air_hum = 60,
    .back_air_co2 = 2000,
    .back_air_pm25 = 500,
    .master_supply_temp = 220,
    .master_living_temp = 220,
    .debug_enable = false,
};

uint16_t GetRandomDelayTime(void)
{//20-3020ms的随机数
    uint16_t result = 0;
    result = (rand()&0x0190)*5+ 300;/* random factor 0-47*/      
    return  result;
}
/*时间戳*/
void app_general_push_system_dp_stamp(uint16_t in_index,uint32_t in_stamp)
{
    if(in_index >= DP_ADDR_START)
    {
        s_sysPara.dpStamp[(in_index-DP_ADDR_START)] = in_stamp;
    }   
}
uint32_t app_general_pull_system_dp_stamp(uint16_t in_index)
{
    if(in_index >= DP_ADDR_START)
    {
        return s_sysPara.dpStamp[(in_index-DP_ADDR_START)];
    } 
    return 0;
}
uint16_t app_general_pull_error_word(void)
{
    return s_sysPara.word_error;
}
void app_general_push_error_word(uint16_t in_errorBit)
{
    s_sysPara.word_error |= in_errorBit;
}
void app_general_clear_error_word(uint16_t in_errorBit)
{
    s_sysPara.word_error &= (~in_errorBit);
}


macro_createTimer(remote_control_delay,timerType_second ,0);
/*远程受控模式*/
void app_general_push_remote_control(bool in_remote_control)
{ 
    if(in_remote_control)
    {//压入10分钟的时间
        s_sysPara.remoteControlFlag = true;
        pbc_reload_timerClock(&remote_control_delay,600);
    }
    else
    {
        s_sysPara.remoteControlFlag = false;
    }
}

bool  app_general_pull_remote_control(void)
{
    if(s_sysPara.remoteControlFlag)
    {
        return true;
    }
    return false;
}
void remote_control_task(void)
{
    uint8_t i = 0;
    pbc_timerClockRun_task(&remote_control_delay);
    if(pbc_pull_timerIsCompleted(&remote_control_delay))
    {
        s_sysPara.remoteControlFlag = false;
        for(i = 0; i <  MASTER_PAD_NUM;i++)
        {
            s_sysPara.padPara[i].output_remote = false;
        }
    }
}

/*远程继电器*/
void app_general_push_remote_relay(uint8_t in_port,bool in_remote_control)
{ 
    if(in_remote_control)
    {
        s_sysPara.padPara[in_port].output_remote = true;
    }
    else
    {
        s_sysPara.padPara[in_port].output_remote = false;
    }
}
bool  app_general_pull_remote_relay(uint8_t in_port)
{
    if(s_sysPara.padPara[in_port].output_remote)
    {
        return true;
    }
    return false;
}

/*系统主机故障字*/
uint16_t app_general_pull_master_error_word(void)
{
    return s_sysPara.system_error_word;
}
void app_general_push_master_error_word(uint16_t in_error)
{
    s_sysPara.system_error_word |=  in_error;
}
void app_general_clear_master_error_word(uint16_t in_error)
{
    s_sysPara.system_error_word &=  (~in_error);
}
/*环控故障字*/
uint16_t app_general_pull_ae_error_word(void)
{
    return s_sysPara.ae_error_word;
}
void app_general_push_ae_error_word(uint16_t in_error)
{
    s_sysPara.ae_error_word =  in_error;
    s_sysPara.system_error_word &= 0xd807;
    s_sysPara.system_error_word |= in_error;
}
/*输配故障字*/
uint16_t app_general_pull_ac_error_word(void)
{
    return s_sysPara.ac_error_word;
}
void app_general_push_ac_error_word(uint16_t in_error)
{
    s_sysPara.ac_error_word =  in_error;
}
/*能需*/
/*系统复位字*/
uint16_t app_general_pull_system_reset_word(void)
{   
    uint16_t temp;
    temp = s_sysPara.system_reset_word;
    s_sysPara.system_reset_word = 0;
    return temp;
}
void app_general_push_system_reset_word(uint16_t in_status)
{
    s_sysPara.system_reset_word = in_status;
    if(in_status & 0x01)
    {//复位排水故障
        s_sysPara.system_error_word &= (~0x2000);
    }
 //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS); 
}

/*系统状态字*/
uint16_t app_general_pull_system_status_word(void)
{
    return s_sysPara.system_status_word;
}
void app_general_push_system_status_word(uint16_t in_status)
{
    s_sysPara.system_status_word |= in_status;
}
/*开关机*/
void app_general_push_power_status(bool in_power_status)
{ 
    if(in_power_status != StoRunParameter.systemPower)
    {
        StoRunParameter.systemPower = in_power_status;
        //app_push_once_save_sto_parameter();
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_POWER);
       // app_link_syn_push_outside_updata_word(SYSTEM_PAD,OCCUPY_PAD_SYSTEM_MESSAGE);
    }
}

bool  app_general_pull_power_status(void)
{
    if(StoRunParameter.systemPower)
    {
        return true;
    }
    return false;
}
/*模式*/
void app_general_push_aircod_mode(AirRunMode_Def in_mode)
{
	if((in_mode ==AIR_MODE_COOL) || (in_mode ==AIR_MODE_HEAT)||
	   (in_mode ==AIR_MODE_HUMIDITY)||(in_mode ==AIR_MODE_FAN) ||
		(in_mode ==AIR_MODE_AUTO_COOL)||(in_mode ==AIR_MODE_AUTO_HEAT))
	{
		if(StoRunParameter.airRunmode != in_mode)
		{
			StoRunParameter.airRunmode = in_mode;
         //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_RUN_MODE);
         //   app_link_syn_push_outside_updata_word(SYSTEM_PAD,OCCUPY_PAD_SYSTEM_MESSAGE);
		//	app_push_once_save_sto_parameter();
		}
    }
}
AirRunMode_Def app_general_pull_aircod_mode(void)
{
    if(StoRunParameter.airRunmode == 0)
	{
		StoRunParameter.airRunmode = AIR_MODE_FAN;
	}
    return StoRunParameter.airRunmode;
}
/*设定湿度*/
void app_general_push_aircod_humidity(int16_t in_set_humidity)
{
	if((in_set_humidity > 0) && (in_set_humidity<=100))
	{
		if(StoRunParameter.humidity_set != in_set_humidity)
		{
			StoRunParameter.humidity_set = in_set_humidity;
        //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WIND_SET_HUM);
			//app_push_once_save_sto_parameter();
		}
	}
}
int16_t app_general_pull_aircod_humidity(void)
{
    return StoRunParameter.humidity_set;
}
/*设定风速*/
void app_general_push_aircod_fanSpeed(NewAirLevelSet_Def in_speed)
{
    if((in_speed ==LowFanSet)||
	   (in_speed ==MiddleFanSet)||(in_speed ==HighFanSet))
	{
		if(StoRunParameter.NewAirLevelSet != in_speed)
		{
			StoRunParameter.NewAirLevelSet = in_speed;
          //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WIND_SET_SPEED);
		//	app_push_once_save_sto_parameter();
		}
    }
}
NewAirLevelSet_Def app_general_pull_aircod_fanSpeed(void)
{
    return StoRunParameter.NewAirLevelSet;
}
/*通风制冷设定温度、制热设定温度*/
void app_general_push_aircod_cold_temp(int16_t in_set_temp)
{
	if((in_set_temp >= 50) && (in_set_temp <= 350)&&(in_set_temp%5==0))
	{
		if(StoRunParameter.coldTemp_set != in_set_temp)
		{
			StoRunParameter.coldTemp_set = in_set_temp;
         //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WIND_SET_CLOD_TEMP);
		//	app_push_once_save_sto_parameter();
		}
	}
}

void app_general_push_aircod_heat_temp(int16_t in_set_temp)
{
	if((in_set_temp >= 50) && (in_set_temp <= 350)&&(in_set_temp%5==0))
	{
		if(StoRunParameter.hotTemp_set != in_set_temp)
		{
			StoRunParameter.hotTemp_set = in_set_temp;   
       //     app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WIND_SET_HEAT_TEMP);      
		//	app_push_once_save_sto_parameter();
		}
        
	}
}

int16_t app_general_pull_aircod_set_temp(void)
{
    int16_t  runSetTemp = 0;
	if(StoRunParameter.airRunmode == AIR_MODE_COOL)
	{
		runSetTemp = StoRunParameter.coldTemp_set;
	}
	else if(StoRunParameter.airRunmode == AIR_MODE_HEAT)
	{
		runSetTemp = StoRunParameter.hotTemp_set;
	}
	else
	{
		runSetTemp = StoRunParameter.coldTemp_set;
	}
	return runSetTemp;
}

int16_t app_general_pull_aircod_cold_temp(void)
{
    return StoRunParameter.coldTemp_set;
}
int16_t app_general_pull_aircod_heat_temp(void)
{
    return StoRunParameter.hotTemp_set;
}
/*新风PWM*/
uint8_t app_general_pull_new_air_pwm_low(void)
{
    return s_sysPara.newAirLowPwm;
}
uint8_t app_general_pull_new_air_pwm_mid(void)
{
    return s_sysPara.newAirMidPwm;
}
uint8_t app_general_pull_new_air_pwm_high(void)
{
    return s_sysPara.newAirHighPwm;
}
void app_general_push_new_air_pwm_low(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        if(in_pwm != s_sysPara.newAirLowPwm)
        {
            s_sysPara.newAirLowPwm = in_pwm;
        //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_NEW_AIR_PWM);
        }
        
    }
}
void app_general_push_new_air_pwm_mid(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        if(in_pwm != s_sysPara.newAirMidPwm)
        {
            s_sysPara.newAirMidPwm = in_pwm;
        //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_NEW_AIR_PWM);
        }        
    }
}
void app_general_push_new_air_pwm_high(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        if(in_pwm != s_sysPara.newAirHighPwm)
        {
            s_sysPara.newAirHighPwm = in_pwm;
          //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_NEW_AIR_PWM);
        }        
    }
}

/*回风风PWM*/
uint8_t app_general_pull_back_air_pwm_low(void)
{
    return s_sysPara.backAirLowPwm;
}
uint8_t app_general_pull_back_air_pwm_mid(void)
{
    return s_sysPara.backAirMidPwm;
}
uint8_t app_general_pull_back_air_pwm_high(void)
{
    return s_sysPara.backAirHighPwm;
}
void app_general_push_back_air_pwm_low(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        if(in_pwm != s_sysPara.backAirLowPwm)
        {
            s_sysPara.backAirLowPwm = in_pwm;
        //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_PWM);
        }  
    }
}
void app_general_push_back_air_pwm_mid(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        if(in_pwm != s_sysPara.backAirMidPwm)
        {
            s_sysPara.backAirMidPwm = in_pwm;
        //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_PWM);
        } 
    }
}
void app_general_push_back_air_pwm_high(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        if(in_pwm != s_sysPara.backAirHighPwm)
        {
            s_sysPara.backAirHighPwm = in_pwm;
       //     app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_PWM);
        } 
    }
}

/*主机制冷制热生活热水设定水温*/
void app_general_push_set_cold_water_temp(int16_t in_set_temp)
{
	//if((in_set_temp >= 50) && (in_set_temp <= 350)&&(in_set_temp%5==0))
	//{
		if(s_sysPara.set_cold_water_temp != in_set_temp)
		{
			s_sysPara.set_cold_water_temp = in_set_temp;
         //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WATER_SET_CLOD_TEMP);
		}
	//}
}

void app_general_push_set_heat_water_temp(int16_t in_set_temp)
{
	//if((in_set_temp >= 50) && (in_set_temp <= 350)&&(in_set_temp%5==0))
	//{
		if(s_sysPara.set_heat_water_temp != in_set_temp)
		{
			s_sysPara.set_heat_water_temp = in_set_temp;
       //     app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WATER_SET_HEAT_TEMP); 
		}        
	//}
}

void app_general_push_set_living_water_temp(int16_t in_set_temp)
{ 
	//if((in_set_temp >= 50) && (in_set_temp <= 350)&&(in_set_temp%5==0))
	//{
		if(s_sysPara.set_living_water_temp != in_set_temp)
		{
			s_sysPara.set_living_water_temp = in_set_temp; 
      //      app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WATER_SET_LIVING_TEMP);
		}        
	//}
}

int16_t app_general_pull_set_cold_water_temp(void)
{
    return s_sysPara.set_cold_water_temp;
}
int16_t app_general_pull_set_heat_water_temp(void)
{
    return s_sysPara.set_heat_water_temp;
}
int16_t app_general_pull_set_living_water_temp(void)
{
    return s_sysPara.set_living_water_temp;
}

/*户外进风/氟盘前/氟盘后/回风/排风温湿度*/
void app_general_push_outdoor_temp(int16_t in_temp)
{
    if(in_temp != s_sysPara.outdoor_temp)
    {
        s_sysPara.outdoor_temp = in_temp;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUTDOOR_WEATHER);
    }
    
}
int16_t app_general_pull_outdoor_temp(void)
{
    return s_sysPara.outdoor_temp;
}
void app_general_push_outdoor_hum(int16_t in_hum)
{
    if(in_hum != s_sysPara.outdoor_hum)
    {
        s_sysPara.outdoor_hum = in_hum;
     //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUTDOOR_WEATHER);
    }
}
int16_t app_general_pull_outdoor_hum(void)
{
    return s_sysPara.outdoor_hum;
}
void app_general_push_before_fu_temp(int16_t in_temp)
{
    if(in_temp != s_sysPara.before_fu_temp)
    {
        s_sysPara.before_fu_temp = in_temp;
   //     app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BEFORE_FU_WEATHER);
    }
}
int16_t app_general_pull_before_fu_temp(void)
{
    return s_sysPara.before_fu_temp;
}
void app_general_push_before_fu_hum(int16_t in_hum)
{
    if(in_hum != s_sysPara.before_fu_hum)
    {
        s_sysPara.before_fu_hum = in_hum;
     //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BEFORE_FU_WEATHER);
    }
}
int16_t app_general_pull_before_fu_hum(void)
{
    return s_sysPara.before_fu_hum;
}
void app_general_push_after_fu_temp(int16_t in_temp)
{
    if(in_temp != s_sysPara.after_fu_temp)
    {
        s_sysPara.after_fu_temp = in_temp;
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_AFTER_FU_WEATHER);
    }
}
int16_t app_general_pull_after_fu_temp(void)
{
    return s_sysPara.after_fu_temp;
}
void app_general_push_after_fu_hum(int16_t in_hum)
{
    if(in_hum != s_sysPara.after_fu_hum)
    {
        s_sysPara.after_fu_hum = in_hum;
  //      app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_AFTER_FU_WEATHER);
    }
}
int16_t app_general_pull_after_fu_hum(void)
{
    return s_sysPara.after_fu_hum;
}
void app_general_push_backair_temp(int16_t in_temp)
{
    if(in_temp != s_sysPara.back_air_temp)
    {
        s_sysPara.back_air_temp = in_temp;
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_WEATHER);
    }
}
int16_t app_general_pull_backair_temp(void)
{
    return s_sysPara.back_air_temp;
}
void app_general_push_backair_hum(int16_t in_hum)
{
    if(in_hum != s_sysPara.back_air_hum)
    {
        s_sysPara.back_air_hum = in_hum;
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_WEATHER); 
    }
}
int16_t app_general_pull_backair_hum(void)
{
    return s_sysPara.back_air_hum;
}
void app_general_push_exhastair_temp(int16_t in_temp)
{
    if(in_temp != s_sysPara.exhast_air_temp)
    {
        s_sysPara.exhast_air_temp = in_temp;
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_EXHAST_AIR_WEATHER);
    }
}
int16_t app_general_pull_exhastair_temp(void)
{
    return s_sysPara.exhast_air_temp;
}
void app_general_push_exhastair_hum(int16_t in_hum)
{
    if(in_hum != s_sysPara.exhast_air_hum)
    {
        s_sysPara.exhast_air_hum = in_hum;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_EXHAST_AIR_WEATHER);
    }
}
int16_t app_general_pull_exhastair_hum(void)
{
    return s_sysPara.exhast_air_hum;
}

/*回风co2 pm25*/
void app_general_push_backair_co2(int16_t in_set_co2)
{
    if(in_set_co2 != s_sysPara.back_air_co2)
    {
        s_sysPara.back_air_co2 = in_set_co2;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_WEATHER);
    }   
}
int16_t app_general_pull_backair_co2(void)
{
    return s_sysPara.back_air_co2;
}
void app_general_push_backair_pm25(int16_t in_set_pm25)
{
    if(in_set_pm25 != s_sysPara.back_air_pm25)
    {
        s_sysPara.back_air_pm25 = in_set_pm25;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_WEATHER);
    }
    
}
int16_t app_general_pull_backair_pm25(void)
{
    return s_sysPara.back_air_pm25;
}

/*设定温度带宽*/
void app_general_push_aircod_setTemp_deadZone(int16_t in_deadZone)
{
	if((in_deadZone >= 5) && (in_deadZone <= 100)&&(in_deadZone%5==0))
	{		
		if(StoRunParameter.temp_DeadZone != in_deadZone)
		{
			StoRunParameter.temp_DeadZone = in_deadZone;
//            app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_DEAD_ZONE);
//			app_push_once_save_sto_parameter();
		}
	}
}
int16_t app_general_pull_aircod_setTemp_deadZone(void)
{
    return StoRunParameter.temp_DeadZone;
}
/*设定湿度带宽*/
void app_general_push_aircod_setHum_deadZone(int16_t in_deadZone)
{
	if((in_deadZone <= 20) && (in_deadZone > 0))
	{		
		if(StoRunParameter.humidity_DeadZone != in_deadZone)
		{
//            app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_DEAD_ZONE); 
//			StoRunParameter.humidity_DeadZone = in_deadZone;
			app_push_once_save_sto_parameter();
		}
	}
}
int16_t app_general_pull_aircod_setHum_deadZone(void)
{
    return StoRunParameter.humidity_DeadZone;
}

/*新风风机转速*/
uint16_t app_general_pull_aircod_newair_speed(void)
{
    return s_sysPara.new_air_speed;
}
void app_general_push_aircod_newair_speed(uint16_t in_speed)
{
    if(in_speed != s_sysPara.new_air_speed)
    {
        s_sysPara.new_air_speed = in_speed;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_VALVE); 
    }
    
}
/*回风风机转速*/
uint16_t app_general_pull_aircod_backair_speed(void)
{	
	return s_sysPara.back_air_speed;
}
void app_general_push_aircod_backair_speed(uint16_t in_speed)
{
    if(in_speed != s_sysPara.back_air_speed)
    {
        s_sysPara.back_air_speed = in_speed;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_VALVE);
    }
}
/*氟机水机频率*/
void app_general_push_fu_machine_fre(uint16_t in_fre)
{
    if(s_sysPara.fu_machine_fre != in_fre)
    {
        s_sysPara.fu_machine_fre = in_fre;
     //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_VALVE);
    }  
}
uint16_t app_general_pull_fu_machine_fre(void)
{
    return s_sysPara.fu_machine_fre;
}
void app_general_push_water_machine_fre(uint16_t in_fre)
{
    if(s_sysPara.water_machine_fre != in_fre)
    {
        s_sysPara.water_machine_fre = in_fre;
     //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_VALVE);
    } 
}
uint16_t app_general_pull_water_machine_fre(void)
{
   return s_sysPara.water_machine_fre; 
}
/*主机供水温度、生活热水温度、户外温度*/
int16_t app_general_pull_master_supply_temp(void)
{
    return s_sysPara.master_supply_temp;
}
void app_general_push_master_supply_temp(int16_t in_temp)
{
    if(s_sysPara.master_supply_temp != in_temp)
    {
        s_sysPara.master_supply_temp = in_temp;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_MAIN_MACHINE_TEMP);
    }   
}
int16_t app_general_pull_master_living_temp(void)
{
    return s_sysPara.master_living_temp;
}
void app_general_push_master_living_temp(int16_t in_temp)
{
    if(s_sysPara.master_living_temp != in_temp)
    {
        s_sysPara.master_living_temp = in_temp;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_MAIN_MACHINE_TEMP);
    }
    
}
int16_t app_general_pull_master_outdoor_temp(void)
{
    return s_sysPara.master_outdoor_temp;
}
void app_general_push_master_outdoor_temp(int16_t in_temp)
{
    if(s_sysPara.master_outdoor_temp != in_temp)
    {
        s_sysPara.master_outdoor_temp = in_temp;
       // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_MAIN_MACHINE_TEMP);
    } 
}
/*湿度温度co2pm25修正系数  户外 氟盘前 氟盘后 回风 排风*/
int16_t app_general_pull_adjust_outdoor_hum(void)
{
    return s_sysPara.adjust_outdoor_hum;
}
int16_t app_general_pull_adjust_outdoor_temp(void)
{
    return s_sysPara.adjust_outdoor_temp;
}
int16_t app_general_pull_adjust_outdoor_co2(void)
{
    return s_sysPara.adjust_outdoor_co2;
}

int16_t app_general_pull_adjust_outdoor_pm25(void)
{
    return s_sysPara.adjust_outdoor_pm25;
}
int16_t app_general_pull_adjust_beforfu_hum(void)
{
    return s_sysPara.adjust_befor_fu_hum;
}
int16_t app_general_pull_adjust_beforfu_temp(void)
{
    return s_sysPara.adjust_befor_fu_temp;
}
int16_t app_general_pull_adjust_beforfu_co2(void)
{
    return s_sysPara.adjust_befor_fu_co2;
}
int16_t app_general_pull_adjust_beforfu_pm25(void)
{
    return s_sysPara.adjust_befor_fu_pm25;
}
int16_t app_general_pull_adjust_afterfu_hum(void)
{
    return s_sysPara.adjust_after_fu_hum;
}
int16_t app_general_pull_adjust_afterfu_temp(void)
{
    return s_sysPara.adjust_after_fu_temp;
}
int16_t app_general_pull_adjust_afterfu_co2(void)
{
    return s_sysPara.adjust_after_fu_co2;
}
int16_t app_general_pull_adjust_afterfu_pm25(void)
{
    return s_sysPara.adjust_after_fu_pm25;
}

int16_t app_general_pull_adjust_backair_hum(void)
{
    return s_sysPara.adjust_back_air_hum;
}
int16_t app_general_pull_adjust_backair_temp(void)
{
    return s_sysPara.adjust_back_air_temp;
}
int16_t app_general_pull_adjust_backair_co2(void)
{
    return s_sysPara.adjust_back_air_co2;
}
int16_t app_general_pull_adjust_backair_pm25(void)
{
    return s_sysPara.adjust_back_air_pm25;
}
int16_t app_general_pull_adjust_exhastair_hum(void)
{
    return s_sysPara.adjust_exhast_air_hum;
}
int16_t app_general_pull_adjust_exhastair_temp(void)
{
    return s_sysPara.adjust_exhast_air_temp;
}
int16_t app_general_pull_adjust_exhastair_co2(void)
{
    return s_sysPara.adjust_exhast_air_co2;
}
int16_t app_general_pull_adjust_exhastair_pm25(void)
{
    return s_sysPara.adjust_exhast_air_pm25;
}

void app_general_push_adjust_outdoor_hum(int16_t in_hum)
{
    if(s_sysPara.adjust_outdoor_hum != in_hum)
    {
        s_sysPara.adjust_outdoor_hum = in_hum;
       // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUTDOOR_WEATHER);
    } 
}
void app_general_push_adjust_outdoor_temp(int16_t in_temp)
{
    if(s_sysPara.adjust_outdoor_temp != in_temp)
    {
        s_sysPara.adjust_outdoor_temp = in_temp;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUTDOOR_WEATHER);
    } 
}
void app_general_push_adjust_outdoor_co2(int16_t in_co2)
{
    if(s_sysPara.adjust_outdoor_co2 != in_co2)
    {
        s_sysPara.adjust_outdoor_co2 = in_co2;
        //app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUTDOOR_WEATHER);
    } 
}
void app_general_push_adjust_outdoor_pm25(int16_t in_pm25)
{
    if(s_sysPara.adjust_outdoor_pm25 != in_pm25)
    {
        s_sysPara.adjust_outdoor_pm25 = in_pm25;
       // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUTDOOR_WEATHER);
    }
    
}

void app_general_push_adjust_beforfu_hum(int16_t in_hum)
{
    if(s_sysPara.adjust_befor_fu_hum != in_hum)
    {
        s_sysPara.adjust_befor_fu_hum = in_hum;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BEFORE_FU_WEATHER);
    }
    
}
void app_general_push_adjust_beforfu_temp(int16_t in_temp)
{
    if(s_sysPara.adjust_befor_fu_temp != in_temp)
    {
        s_sysPara.adjust_befor_fu_temp = in_temp;
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BEFORE_FU_WEATHER);
    }  
}
void app_general_push_adjust_beforfu_co2(int16_t in_co2)
{
    if(s_sysPara.adjust_befor_fu_co2 != in_co2)
    {
        s_sysPara.adjust_befor_fu_co2 = in_co2;
     //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BEFORE_FU_WEATHER);
    }    
}
void app_general_push_adjust_beforfu_pm25(int16_t in_pm25)
{
    if(s_sysPara.adjust_befor_fu_pm25 != in_pm25)
    {
        s_sysPara.adjust_befor_fu_pm25 = in_pm25;
     //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BEFORE_FU_WEATHER);
    }
    
}

void app_general_push_adjust_afterfu_hum(int16_t in_hum)
{
    if(s_sysPara.adjust_after_fu_hum != in_hum)
    {
        s_sysPara.adjust_after_fu_hum = in_hum;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_AFTER_FU_WEATHER);
    } 
}
void app_general_push_adjust_afterfu_temp(int16_t in_temp)
{
    if(s_sysPara.adjust_after_fu_temp != in_temp)
    {
        s_sysPara.adjust_after_fu_temp = in_temp;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_AFTER_FU_WEATHER);
    }   
}
void app_general_push_adjust_afterfu_co2(int16_t in_co2)
{
    if(s_sysPara.adjust_after_fu_co2 != in_co2)
    {
        s_sysPara.adjust_after_fu_co2 = in_co2;
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_AFTER_FU_WEATHER);
    }
    
}
void app_general_push_adjust_afterfu_pm25(int16_t in_pm25)
{
    if(s_sysPara.adjust_after_fu_pm25 != in_pm25)
    {
        s_sysPara.adjust_after_fu_pm25 = in_pm25;
       // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_AFTER_FU_WEATHER);
    }
    
}

void app_general_push_adjust_backair_hum(int16_t in_hum)
{
    if(s_sysPara.adjust_back_air_hum != in_hum)
    {
        s_sysPara.adjust_back_air_hum = in_hum;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_WEATHER);
    }
    
}
void app_general_push_adjust_backair_temp(int16_t in_temp)
{
    if(s_sysPara.adjust_back_air_temp != in_temp)
    {
        s_sysPara.adjust_back_air_temp = in_temp;
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_WEATHER);
    }
    
}
void app_general_push_adjust_backair_co2(int16_t in_co2)
{
    if(s_sysPara.adjust_back_air_co2 != in_co2)
    {
        s_sysPara.adjust_back_air_co2 = in_co2;
     //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_WEATHER);
    }
    
}
void app_general_push_adjust_backair_pm25(int16_t in_pm25)
{
    if(s_sysPara.adjust_back_air_pm25 != in_pm25)
    {
        s_sysPara.adjust_back_air_pm25 = in_pm25;
     //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_WEATHER);
    }
    
}

void app_general_push_adjust_exhastair_hum(int16_t in_hum)
{
    if(s_sysPara.adjust_exhast_air_hum != in_hum)
    {
        s_sysPara.adjust_exhast_air_hum = in_hum;
  //      app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_EXHAST_AIR_WEATHER);
    }
    
}
void app_general_push_adjust_exhastair_temp(int16_t in_temp)
{
    if(s_sysPara.adjust_exhast_air_temp != in_temp)
    {
        s_sysPara.adjust_exhast_air_temp = in_temp;    
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_EXHAST_AIR_WEATHER);
    }

}
void app_general_push_adjust_exhastair_co2(int16_t in_co2)
{
    if(s_sysPara.adjust_exhast_air_co2 != in_co2)
    {
        s_sysPara.adjust_exhast_air_co2 = in_co2;
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_EXHAST_AIR_WEATHER);
    }   
    
}
void app_general_push_adjust_exhastair_pm25(int16_t in_pm25)
{
    if(s_sysPara.adjust_exhast_air_pm25 != in_pm25)
    {
        s_sysPara.adjust_exhast_air_pm25 = in_pm25;
   //     app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_EXHAST_AIR_WEATHER);
    }

}
/*环控能需预冷预热输出*/
bool app_general_pull_anergy_need(void)
{
    return s_sysPara.energyNeed;
}
void app_general_push_anergy_need(bool in_status)
{
    if(s_sysPara.energyNeed != in_status)
    {
        s_sysPara.energyNeed = in_status;
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    }  
}

/*系统传感器错误*/
uint16_t app_general_pull_ntc_error_word(void)
{
    return s_sysPara.system_ntc_error;
}
void app_general_push_ntc_error_word(uint16_t in_error)
{
    s_sysPara.system_ntc_error =  in_error;
}
/*输配传感器错误*/
uint16_t app_general_pull_ac_ntc_error_word(void)
{
    return s_sysPara.ac_ntc_error;
}
void app_general_push_ac_ntc_error_word(uint16_t in_error)
{
    s_sysPara.ac_ntc_error =  in_error;
}
/*环控传感器错误*/
uint16_t app_general_pull_ae_ntc_error_word(void)
{
    return s_sysPara.ae_ntc_error;
}
void app_general_push_ae_ntc_error_word(uint16_t in_error)
{
    s_sysPara.ae_ntc_error =  in_error;
}
/*冷热运行状态*/

/*绑定的阀门列表 (风盘)*/

/*绑定的阀门列表 (辐射)*/

/*阀门绑定故障*/

/*混水制冷/制热设定温度 */
void app_general_push_set_mixwater_cold_temp(int16_t in_set_temp)
{
	//if((in_set_temp >= 50) && (in_set_temp <= 350)&&(in_set_temp%5==0))
	//{
		if(StoRunParameter.mixColdSetTemp != in_set_temp)
		{
			StoRunParameter.mixColdSetTemp = in_set_temp;
     //       app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_MIXWATER_SET_CLOD_TEMP);
		//	app_push_once_save_sto_parameter();
		}
	//}
}

void app_general_push_set_mixwater_heat_temp(int16_t in_set_temp)
{
	//if((in_set_temp >= 50) && (in_set_temp <= 350)&&(in_set_temp%5==0))
	//{
		if(StoRunParameter.mixHeatSetTemp != in_set_temp)
		{
			StoRunParameter.mixHeatSetTemp = in_set_temp;    
       //     app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_MIXWATER_SET_HEAT_TEMP);       
		//	app_push_once_save_sto_parameter();
		}
        
	//}
}

int16_t app_general_pull_set_mixwater_cold_temp(void)
{
    return StoRunParameter.mixColdSetTemp;
}

int16_t app_general_pull_set_mixwater_heat_temp(void)
{
    return StoRunParameter.mixHeatSetTemp;
}

/*输配进水温度*/

/*输配回水温度*/

/*输配水泵状态*/
bool app_general_pull_pump_output(void)
{
    return s_sysPara.output_pump;
}
/*输配三通阀门输出状态*/
bool app_general_pull_three_vavle_output(void)
{
    return s_sysPara.output_threeWayValve;
}
/*输配混水AI目标温度 */
int16_t app_general_pull_ai_dest_temp(void)
{
    return s_sysPara.destTemp;
}
/*输配混水AI使能*/
bool app_general_pull_ai_enable_status(void)
{
    return StoRunParameter.aiEnable;
}
void app_general_push_ai_enable_status(bool in_status)
{
    if(StoRunParameter.aiEnable != in_status)
    {
        StoRunParameter.aiEnable = in_status;
    //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_MIXWATER_AI_ENABLE);
    }
    
}
/*输配防冻保护*/
uint8_t app_general_pull_mix_freeze_protect(void)
{
    return StoRunParameter.lowTempProtectConfig;
}
void app_general_push_mix_freeze_protect(uint8_t  in_set_temp)
{
    if((in_set_temp >= 50) && (in_set_temp <= 100)&&(in_set_temp%5==0))
    {
        if(in_set_temp != StoRunParameter.lowTempProtectConfig)
        {         
            StoRunParameter.lowTempProtectConfig = in_set_temp;
        //    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_MIXWATER_LOW_TEMP_PROTECT);
        //    app_push_once_save_sto_parameter();
        }
    }  
}
/*传感器错误*/
/*输配未绑定的阀门列表(风盘) */
uint16_t app_general_pull_unbind_list_fan(void)
{
    return s_sysPara.unbind_fan;
}
void app_general_push_unbind_list_fan(uint16_t in_unbind)
{
    if(s_sysPara.unbind_fan != in_unbind)
    {
         s_sysPara.unbind_fan = in_unbind;
    }
   
}
/*输配未绑定的阀门列表(辐射)*/
uint16_t app_general_pull_unbind_list_warm(void)
{
    return s_sysPara.unbind_warm;
}
void app_general_push_unbind_list_warm(uint16_t in_unbind)
{
    if(s_sysPara.unbind_warm != in_unbind)
    {
         s_sysPara.unbind_warm = in_unbind;
    }
   
}
/*输配末端能量需求(主机联动)*/

//读取风阀设置
void app_general_push_wind_value(bool reg_dat)
{
	if(reg_dat <= 1)
	{
		s_sysPara.wind_value = reg_dat;
     //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
	}
}

bool app_general_pull_wind_value(void)
{
	return s_sysPara.wind_value;
}

//读取热水使能
int16_t app_general_pull_hotwater_enable(void)
{
	return s_sysPara.hotwater_enable;
}
void app_general_push_hotwater_enable(uint16_t reg_dat)
{
	if(reg_dat <= 1)
	{
		s_sysPara.hotwater_enable = reg_dat;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
	}
}
/*滤芯更换周期*/
void app_general_push_filter_time(int16_t in_time)
{
	if(s_sysPara.filter_time != in_time)
	{
		s_sysPara.filter_time = in_time;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
	}
}
int16_t app_general_pull_filter_time(void)
{
    return s_sysPara.filter_time;
}

/*滤芯使用时间*/
void app_general_push_filter_usetime(int16_t in_time)
{
	if(0x00 == in_time)
	{
		s_sysPara.filter_usetime = 0;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
	}
}
void app_general_push_filter_usetime_inside(int16_t in_time)
{
    s_sysPara.filter_usetime = in_time;
}
int16_t app_general_pull_filter_usetime(void)
{
    return s_sysPara.filter_usetime;
}

/*末端接口*/

timerClock_def* app_general_pull_pad_id_ocupy_time(uint8_t in_solidNum)
{
    return &s_sysPara.padPara[in_solidNum].id_ocupy_delay;
}

/*物理端口绑定信息*/
uint8_t  app_general_pull_pad_phy_port_bind_message(uint8_t in_solidNum)
{
    uint8_t i = 0;
    for(i = 0; i < MASTER_PAD_NUM;i++)
    {
        if(s_sysPara.padPara[i].idUsedFlag)
        {
            if(s_sysPara.padPara[i].pad_bind_warm & (0x01<< in_solidNum))
            {//辐射列表
                return i;
            }
            if(s_sysPara.padPara[i].pad_bind_fan & (0x01<< in_solidNum))
            {//风盘列表
                return i;
            }
        }       
    }
    return PAD_NO_PHY_BIND;
}
/*末端id占用信息*/
void app_general_push_pad_id_use_message(uint8_t in_solidNum,bool in_status)
{
    s_sysPara.padPara[in_solidNum].idUsedFlag = in_status;
}
bool app_general_pull_pad_id_use_message(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].idUsedFlag;
}
void app_general_pad_iduse_task(void)
{
    uint8_t i;
    
    for(i = 0; i < MASTER_PAD_NUM;i++)
    {
        pbc_timerClockRun_task(&s_sysPara.padPara[i].id_ocupy_delay);
        if(pbc_pull_timerIsCompleted(&s_sysPara.padPara[i].id_ocupy_delay))
        {
            s_sysPara.padPara[i].idUsedFlag = false;
            app_general_push_pad_warm_need(i,false);
            app_general_push_pad_fan_need(i,false);
        }
    }
}

/*末端时间戳*/
void app_general_push_pad_dp_stamp(uint8_t in_solidNum,uint8_t in_index,uint32_t in_stamp)
{
    if(in_index < MAX_DATA_POINT_LEN_PAD)
    {
        s_sysPara.padPara[in_solidNum].dpStamp[in_index] = in_stamp;
    }
    
}
uint32_t app_general_pull_pad_dp_stamp(uint8_t in_solidNum,uint8_t in_index)
{
    return s_sysPara.padPara[in_solidNum].dpStamp[in_index];
}
/*设备故障字*/
#define NO_AC_ERROE   0x02
void app_general_push_devive_error_word(uint8_t in_solidNum,uint16_t in_error)
{
    if(s_sysPara.padPara[in_solidNum].padErrorWord != in_error)
    {
        s_sysPara.padPara[in_solidNum].padErrorWord = in_error;
        if(s_sysPara.padPara[in_solidNum].padErrorWord & NO_AC_ERROE)
        {//退出登录
    //        app_link_log_out(SYSTEM_PAD);
        }
    }
}

uint16_t app_general_pull_devive_error_word(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].padErrorWord;
}
/*在线状态*/
void app_general_push_devive_online(uint8_t in_solidNum,bool in_status)
{
    s_sysPara.padPara[in_solidNum].onlineFlag = in_status;
}
bool app_general_pull_devive_online(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].onlineFlag;
}

/*设备类型*/
void app_general_push_devive_type(uint8_t in_solidNum,uint16_t in_type)
{
    s_sysPara.padPara[in_solidNum].deviceType = in_type;
}
uint16_t app_general_pull_devive_type(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].deviceType;
}
/*版本號*/
void app_general_push_pad_version(uint8_t in_solidNum,uint16_t in_type)
{
    s_sysPara.padPara[in_solidNum].version_pad = in_type;
}
uint16_t app_general_pull_pad_version(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].version_pad;
}
/*设备ID*/
void app_general_push_devive_id0(uint8_t in_solidNum,uint16_t in_id)
{
    pbc_int16uToArray_bigEndian(in_id,&s_sysPara.padPara[in_solidNum].deviceId[0]);
}
uint16_t app_general_pull_devive_id0(uint8_t in_solidNum)
{
    return pbc_arrayToInt16u_bigEndian(&s_sysPara.padPara[in_solidNum].deviceId[0]);
}

void app_general_push_devive_id1(uint8_t in_solidNum,uint16_t in_id)
{
    pbc_int16uToArray_bigEndian(in_id,&s_sysPara.padPara[in_solidNum].deviceId[2]);
}
uint16_t app_general_pull_devive_id1(uint8_t in_solidNum)
{
    return pbc_arrayToInt16u_bigEndian(&s_sysPara.padPara[in_solidNum].deviceId[2]);
}

void app_general_push_devive_id2(uint8_t in_solidNum,uint16_t in_id)
{
    pbc_int16uToArray_bigEndian(in_id,&s_sysPara.padPara[in_solidNum].deviceId[4]);
}
uint16_t app_general_pull_devive_id2(uint8_t in_solidNum)
{
    return pbc_arrayToInt16u_bigEndian(&s_sysPara.padPara[in_solidNum].deviceId[4]);
}


/*开关机*/
void app_general_push_devive_power(uint8_t in_solidNum,uint8_t in_status)
{
    if(in_status < 2)
    {
        if(in_status != s_sysPara.padPara[in_solidNum].chDevicePowerStatus)
        {
            s_sysPara.padPara[in_solidNum].chDevicePowerStatus = in_status;
          //  app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_POWER);
        }       
    }    
}
bool app_general_pull_devive_power(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].chDevicePowerStatus;
}
/*制冷设定温度*//*制热设定温度 */
void app_general_push_pad_set_cold_temp(uint8_t in_solidNum,int16_t in_set_temp)
{
	if((in_set_temp >= 50) && (in_set_temp <= 350)&&(in_set_temp%5==0))
	{
		if(s_sysPara.padPara[in_solidNum].set_coldTemp != in_set_temp)
		{
			s_sysPara.padPara[in_solidNum].set_coldTemp = in_set_temp;
        //    app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_SET_COLD_TEMP);
		}
	}
}

void app_general_push_pad_set_heat_temp(uint8_t in_solidNum,int16_t in_set_temp)
{
	if((in_set_temp >= 50) && (in_set_temp <= 350)&&(in_set_temp%5==0))
	{
		if(s_sysPara.padPara[in_solidNum].set_warmTemp != in_set_temp)
		{
			s_sysPara.padPara[in_solidNum].set_warmTemp = in_set_temp;  
            //app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_SET_HEAT_TEMP);         
		}
        
	}
}
int16_t app_general_pull_pad_set_cold_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].set_coldTemp;
}
int16_t app_general_pull_pad_set_heat_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].set_warmTemp;
}
/*露点温度*/
void app_general_push_pad_lew_drop_temp(uint8_t in_solidNum,int16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].lewDropTemp != in_temp)
    {
        s_sysPara.padPara[in_solidNum].lewDropTemp = in_temp;    
    }
	
}
int16_t app_general_pull_pad_lew_drop_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].lewDropTemp;
}
/*冷热运行状态*/
void app_general_push_pad_cold_warm_status(uint8_t in_solidNum,uint8_t in_status)
{
    if(s_sysPara.padPara[in_solidNum].padHcmode != in_status)
    {
        s_sysPara.padPara[in_solidNum].padHcmode = in_status;  
    }
	  
}
uint8_t app_general_pull_pad_cold_warm_status(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].padHcmode;
}
/*防冻保护*/
void app_general_push_pad_freeze_protect(uint8_t in_solidNum,bool in_status)
{
    if(s_sysPara.padPara[in_solidNum].lowTempProtectFlag != in_status)
    {
        s_sysPara.padPara[in_solidNum].lowTempProtectFlag = in_status;   
   //     app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);
    } 
}
bool app_general_pull_pad_freeze_protect(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].lowTempProtectFlag;
}
/*防冻温度*/
void app_general_push_pad_freeze_temp(uint8_t in_solidNum,int16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].freezeTemp != in_temp)
    {
        s_sysPara.padPara[in_solidNum].freezeTemp = in_temp; 
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);
    }
	   
}
int16_t app_general_pull_pad_freeze_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].freezeTemp;
}
/*童锁功能*/
void app_general_push_pad_child_lock(uint8_t in_solidNum,bool in_status)
{
    if(s_sysPara.padPara[in_solidNum].lockFlag != in_status)
    {
        s_sysPara.padPara[in_solidNum].lockFlag = in_status; 
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_CHILD_LOCK);
    }
	   
}
bool app_general_pull_pad_child_lock(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].lockFlag;
}
/*上电(关机)/(记忆)*/
void app_general_push_pad_onoff_memory(uint8_t in_solidNum,bool in_status)
{
    if(s_sysPara.padPara[in_solidNum].powerOffFlag != in_status)
    {
        s_sysPara.padPara[in_solidNum].powerOffFlag = in_status; 
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE); 
    }	  
}
bool app_general_pull_pad_onoff_memory(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].powerOffFlag;
}
/*制冷舒适温度*/
void app_general_push_pad_cold_comfortable_temp(uint8_t in_solidNum,int16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].coldComfortTemp != in_temp)
    {
        s_sysPara.padPara[in_solidNum].coldComfortTemp = in_temp; 
   //     app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE); 
    }	   
}
int16_t app_general_pull_pad_cold_comfortable_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].coldComfortTemp;
}
/*制热舒适温度*/
void app_general_push_pad_heat_comfortable_temp(uint8_t in_solidNum,int16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].warmComfortTemp != in_temp)
    {
        s_sysPara.padPara[in_solidNum].warmComfortTemp = in_temp;
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE); 
    }
	    
}
int16_t app_general_pull_pad_heat_comfortable_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].warmComfortTemp;
}
/*最高设定温度*/
void app_general_push_pad_set_high_temp(uint8_t in_solidNum,int16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].maxSetTemp != in_temp)
    {
        s_sysPara.padPara[in_solidNum].maxSetTemp = in_temp;  
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE); 
    }
  
}
int16_t app_general_pull_pad_set_high_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].maxSetTemp;
}
/*最低设定温度*/
void app_general_push_pad_set_low_temp(uint8_t in_solidNum,int16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].minSetTemp != in_temp)
    {
        s_sysPara.padPara[in_solidNum].minSetTemp = in_temp;
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE); 
    }
	    
}
int16_t app_general_pull_pad_set_low_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].minSetTemp;
}
/*控温带宽*/
void app_general_push_pad_deadzone_temp(uint8_t in_solidNum,int16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].bandDifferent != in_temp)
    {
        s_sysPara.padPara[in_solidNum].bandDifferent = in_temp; 
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);  
    }
  
}
int16_t app_general_pull_pad_deadzone_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].bandDifferent;
}
/*露点带宽*/
void app_general_push_pad_deadzone_lewtemp(uint8_t in_solidNum,int16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].coldDropDiff != in_temp)
    {
        s_sysPara.padPara[in_solidNum].coldDropDiff = in_temp;  
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE); 
    }
  
}
int16_t app_general_pull_pad_deadzone_lewtemp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].coldDropDiff;
}
/*测量温度*/
void app_general_push_pad_measure_temp(uint8_t in_solidNum,int16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].measureTemp != in_temp)
    {
        s_sysPara.padPara[in_solidNum].measureTemp = in_temp; 
    }  
}

int16_t app_general_pull_pad_measure_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].measureTemp;
}
/*测量湿度*/
void app_general_push_pad_measure_hum(uint8_t in_solidNum,uint16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].humility != in_temp)
    {
        s_sysPara.padPara[in_solidNum].humility = in_temp;    
    }
}
uint16_t app_general_pull_pad_measure_hum(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].humility;
}
/*辐射阀门需求*/
void app_general_push_pad_warm_need(uint8_t in_solidNum,uint16_t in_status)
{
    //if(s_sysPara.padPara[in_solidNum].warmNedd != in_status)
   // {
        s_sysPara.padPara[in_solidNum].warmNedd = in_status; 
        uint8_t i = 0;
        for(i = 0; i < MASTER_PAD_NUM;i++)
        {//根据绑定信息输出
            if(s_sysPara.padPara[in_solidNum].pad_bind_warm & (0x01<<i))
            {
               // s_sysPara.padPara[i].output_terminal = in_status;
                s_sysPara.padPara[i].output_terminal = (in_status & (0x01<<i));
            }
        }     
   // } 
}
uint16_t app_general_pull_pad_warm_need(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].warmNedd;
}
/*设定风速 */
void app_general_push_pad_set_fan_speed(uint8_t in_solidNum,uint8_t in_speded)
{
    if(s_sysPara.padPara[in_solidNum].setFanSpeed != in_speded)
    {
        s_sysPara.padPara[in_solidNum].setFanSpeed = in_speded;
    //    app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_SET_FAN); 
    }
	    
}
uint8_t app_general_pull_pad_set_fan_speed(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].setFanSpeed;
}
/*风机受控*/
void app_general_push_pad_fan_control(uint8_t in_solidNum,bool in_status)
{
    if(s_sysPara.padPara[in_solidNum].fanControlFalg != in_status)
    {
        s_sysPara.padPara[in_solidNum].fanControlFalg = in_status; 
      //  app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE); 
    }
	  
}
bool app_general_pull_pad_fan_control(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].fanControlFalg;
}
/*低风量PWM值*/
void app_general_push_pad_set_pwm_low(uint8_t in_solidNum,uint16_t in_pwm)
{
    if(s_sysPara.padPara[in_solidNum].lowFanPwm != in_pwm)
    {
        s_sysPara.padPara[in_solidNum].lowFanPwm = in_pwm;
    //    app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);
    }	    
}
uint16_t app_general_pull_pad_set_pwm_low(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].lowFanPwm;
}
/*中风量PWM值*/
void app_general_push_pad_set_pwm_mid(uint8_t in_solidNum,uint16_t in_pwm)
{
    if(s_sysPara.padPara[in_solidNum].midFanPwm != in_pwm)
    {
        s_sysPara.padPara[in_solidNum].midFanPwm = in_pwm; 
      //  app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);
    }  
}
uint16_t app_general_pull_pad_set_pwm_mid(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].midFanPwm;
}
/*高风量PWM值*/
void app_general_push_pad_set_pwm_high(uint8_t in_solidNum,uint16_t in_pwm)
{
    if(s_sysPara.padPara[in_solidNum].highFanPwm != in_pwm)
    {
        s_sysPara.padPara[in_solidNum].highFanPwm = in_pwm;  
   //     app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);
    }	  
}
uint16_t app_general_pull_pad_set_pwm_high(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].highFanPwm;
}

/*AI制冷协同带宽*/
void app_general_push_pad_ai_cold_diff(uint8_t in_solidNum,int16_t in_diff)
{
    if(s_sysPara.padPara[in_solidNum].coldCollaDiff != in_diff)
    {
        s_sysPara.padPara[in_solidNum].coldCollaDiff = in_diff;  
    //    app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);  
    }
	
}
int16_t app_general_pull_pad_ai_cold_diff(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].coldCollaDiff;
}
/*AI制热协同带宽 */
void app_general_push_pad_ai_heat_diff(uint8_t in_solidNum,int16_t in_diff)
{
    if(s_sysPara.padPara[in_solidNum].warmCollaDiff != in_diff)
    {
        s_sysPara.padPara[in_solidNum].warmCollaDiff = in_diff; 
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);
    }
	   
}
int16_t app_general_pull_pad_ai_heat_diff(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].warmCollaDiff;
}
/*制冷协同使能 */
void app_general_push_pad_cold_colla_enable(uint8_t in_solidNum,bool in_status)
{
    if(s_sysPara.padPara[in_solidNum].coldCollaEnable != in_status)
    {
        s_sysPara.padPara[in_solidNum].coldCollaEnable = in_status;
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);  
    }
	  
}
bool app_general_pull_pad_cold_colla_enable(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].coldCollaEnable;
}
int16_t  freshair_effciency;
/*新风效率*/
void app_general_push_freshair_effciency(int16_t in_effciency)
{
     freshair_effciency = in_effciency;
}
int16_t app_general_pull_freshair_effciency(void)
{
    return freshair_effciency;
}
/*制热协同使能 */
void app_general_push_pad_warm_colla_enable(uint8_t in_solidNum,bool in_status)
{
    if(s_sysPara.padPara[in_solidNum].warmCollaEnable != in_status)
    {
        s_sysPara.padPara[in_solidNum].warmCollaEnable = in_status;  
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);
    }	  
}

bool app_general_pull_pad_warm_colla_enable(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].warmCollaEnable;
}
/*风阀需求*/
void app_general_push_pad_fan_need(uint8_t in_solidNum,uint16_t in_status)
{
    s_sysPara.padPara[in_solidNum].fanNedd = in_status;
    uint8_t i = 0;
    for(i = 0; i < MASTER_PAD_NUM;i++)
    {//根据绑定信息输出
        if(s_sysPara.padPara[in_solidNum].pad_bind_fan & (0x01<<i))
        {
            // s_sysPara.padPara[i].output_terminal = in_status;
            s_sysPara.padPara[i].output_terminal = (in_status & (0x01<<i));
        }
    }         
}
uint16_t app_general_pull_pad_fan_need(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].fanNedd;
}
/*风机输出状态*/
void app_general_push_pad_fan_out_speed(uint8_t in_solidNum,uint8_t in_speed)
{
    if(s_sysPara.padPara[in_solidNum].outFanSpeed != in_speed)
    {
        s_sysPara.padPara[in_solidNum].outFanSpeed = in_speed; 
    }	   
}
uint8_t app_general_pull_pad_fan_out_speed(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].outFanSpeed;
}

/*风机转速*/
void app_general_push_pad_fan_speed_output(uint8_t in_solidNum,uint16_t in_speed)
{
    if(s_sysPara.padPara[in_solidNum].outputFanSpeed != in_speed)
    {
        s_sysPara.padPara[in_solidNum].outputFanSpeed = in_speed;
    }	    
}
uint16_t app_general_pull_pad_fan_speed_output(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].outputFanSpeed;
}

/*末端数量*/
void app_general_push_pad_control_num(uint8_t in_solidNum,uint8_t in_num)
{
    if(s_sysPara.padPara[in_solidNum].contror_num != in_num)
    {
        s_sysPara.padPara[in_solidNum].contror_num = in_num; 
  //      app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);
    }	   
}
uint8_t app_general_pull_pad_control_num(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].contror_num;
}
/*双末端模式选择*/
void app_general_push_pad_two_output_mode(uint8_t in_solidNum,uint8_t in_mode)
{
    if(s_sysPara.padPara[in_solidNum].two_output_mode != in_mode)
    {
        s_sysPara.padPara[in_solidNum].two_output_mode = in_mode; 
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_TWO_CNONTROL_MODE);
    }   
}
uint8_t app_general_pull_pad_two_output_mode(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].two_output_mode;
}
/*绑定的阀门列表 (风盘)*/
void app_general_push_pad_bind_list_fan(uint8_t in_solidNum,uint16_t in_list)
{
	s_sysPara.padPara[in_solidNum].pad_bind_fan = in_list;    
}
uint16_t app_general_pull_pad_bind_list_fan(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].pad_bind_fan;
}
/*绑定的阀门列表 (辐射)*/
void app_general_push_pad_bind_list_warm(uint8_t in_solidNum,uint16_t in_list)
{
	s_sysPara.padPara[in_solidNum].pad_bind_warm = in_list;    
}
uint16_t app_general_pull_pad_bind_list_warm(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].pad_bind_warm;
}
/*重复绑定信息*/
void app_general_push_pad_repeat_bind_list(uint16_t in_list)
{
	s_sysPara.repeat_bind |= in_list;    
}
uint16_t app_general_pull_pad_repeat_bind_list(void)
{
    return s_sysPara.repeat_bind;
}

/*校温*/
void app_general_push_pad_adjust_temp(uint8_t in_solidNum,int16_t in_temp)
{
    if(s_sysPara.padPara[in_solidNum].adjust_temp != in_temp)
    {
        s_sysPara.padPara[in_solidNum].adjust_temp = in_temp; 
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);  
    }
  
}
int16_t app_general_pull_pad_adjust_temp(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].adjust_temp;
}

/*校湿*/
void app_general_push_pad_adjust_hum(uint8_t in_solidNum,int16_t in_hum)
{
    if(s_sysPara.padPara[in_solidNum].adjust_hum != in_hum)
    {
        s_sysPara.padPara[in_solidNum].adjust_hum = in_hum; 
   //     app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);  
    }
  
}
int16_t app_general_pull_pad_adjust_hum(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].adjust_hum;
}
/*制冷制热回水设定温度*/
//制冷回水设置温度
int16_t app_general_pull_coolbackwater_set_temp(void)
{
    return s_sysPara.cool_backwater_settemp;
}

int16_t app_general_pull_hotbackwater_set_temp(void)
{
    return s_sysPara.hot_backwater_settemp;
}
void app_general_push_coolbackwater_set_temp(int16_t  in_set_temp)
{
	if(s_sysPara.cool_backwater_settemp != in_set_temp)
	{
		s_sysPara.cool_backwater_settemp = in_set_temp;  
	//	app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_COLD_WARM_BACK_WATER);		  //需确认
	} 
}

void app_general_push_hotbackwater_set_temp(int16_t  in_set_temp)
{
	if(s_sysPara.hot_backwater_settemp != in_set_temp)
	{
		s_sysPara.hot_backwater_settemp = in_set_temp;  
	//	app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_COLD_WARM_BACK_WATER);//
	} 
}

/*辐射类型选择*/
void app_general_push_pad_type_warm_choose(uint8_t in_solidNum,uint8_t in_mode)
{
    if(s_sysPara.padPara[in_solidNum].type_warm_choose != in_mode)
    {
        s_sysPara.padPara[in_solidNum].type_warm_choose = in_mode; 
    //    app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);
    }   
}
uint8_t app_general_pull_pad_type_warm_choose(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].type_warm_choose;
}
/*房间面积*/
void app_general_push_pad_room_area(uint8_t in_solidNum,uint8_t in_mode)
{
    if(s_sysPara.padPara[in_solidNum].room_area != in_mode)
    {
        s_sysPara.padPara[in_solidNum].room_area = in_mode; 
     //   app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_ADV_MESSAGE);
    }   
}
uint8_t app_general_pull_pad_room_area(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].room_area;
}

/*绑定故障*/
void app_general_push_pad_bind_error(uint8_t in_solidNum,uint16_t in_error)
{
	s_sysPara.padPara[in_solidNum].bindError = in_error;    
}
uint16_t app_general_pull_pad_bind_error(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].bindError;
}
//485地址 波特率 校验位
void app_general_push_adress485(uint8_t in_address)
{
    if((in_address >=1) && (in_address < 32))
    {
        StoRunParameter.deviceAddress = in_address;
        app_modbus_remote_reCfg_parmeter(StoRunParameter.deviceAddress,StoRunParameter.baudrateValue,StoRunParameter.evenOddCheck);
        //app_push_once_save_sto_parameter();
    }
}

void app_general_push_baudrate(uint16_t in_baudRate)
{
    if(in_baudRate == 2400)
    {
        StoRunParameter.baudrateValue = 0x00;
    }
    else if(in_baudRate == 4800)
    {
        StoRunParameter.baudrateValue = 0x01;
    }
    else if(in_baudRate == 9600)
    {
        StoRunParameter.baudrateValue = 0x02;
    }
    else if(in_baudRate == 19200)
    {
        StoRunParameter.baudrateValue = 0x03;
    }   
    app_modbus_remote_reCfg_parmeter(StoRunParameter.deviceAddress,StoRunParameter.baudrateValue,StoRunParameter.evenOddCheck);
    //app_push_once_save_sto_parameter();     
}

void app_general_push_checkbit(uint8_t in_check)
{
	if(in_check <= 2)
	{
		StoRunParameter.evenOddCheck = in_check;
        app_modbus_remote_reCfg_parmeter(StoRunParameter.deviceAddress,StoRunParameter.baudrateValue,StoRunParameter.evenOddCheck);
		//app_push_once_save_sto_parameter();
	}
}

uint8_t app_general_pull_adress485(void)
{
	return StoRunParameter.deviceAddress;
}

uint16_t app_general_pull_baudrate(void)
{
	if(StoRunParameter.baudrateValue == 0x00)
	{
		return 2400;
	}
    if(StoRunParameter.baudrateValue == 0x01)
	{
		return 4800;
	}
    if(StoRunParameter.baudrateValue == 0x02)
	{
		return 9600;
	}
    if(StoRunParameter.baudrateValue == 0x03)
	{
		return 19200;
	}
	return 9600;
}

uint8_t app_general_pull_checkbit(void)
{
	return StoRunParameter.evenOddCheck;
}


/*露点保护状态*/
void app_general_push_pad_lew_dorp_temp_output(uint8_t in_solidNum,bool in_status)
{
    if(s_sysPara.padPara[in_solidNum].lewDropProtect != in_status)
    {
        s_sysPara.padPara[in_solidNum].lewDropProtect = in_status; 
    //    app_link_syn_push_pad_updata_word(in_solidNum,OCCUPY_PAD_STATUS_MESSAGE);
    }   
}
bool app_general_pull_pad_lew_dorp_temp_output(uint8_t in_solidNum)
{
    return s_sysPara.padPara[in_solidNum].lewDropProtect;
}

/*露点状态*/
void app_general_push_system_lew_temp_status(uint16_t in_status)
{
    s_sysPara.lewTempStatus = in_status;
}

uint16_t app_general_pull_system_lew_temp_status(void)
{
    return s_sysPara.lewTempStatus;
}

/*除湿输出*/
static bool air_humidity_s_output = false;
bool  app_general_pull_humidity_output(void)
{
	return air_humidity_s_output;
}
/*调试使能*/
bool app_general_pull_debug_enable(void)
{
    return s_sysPara.debug_enable;
}
void app_general_push_debug_enable(bool in_status)
{
    if(s_sysPara.debug_enable != in_status)
    {
        s_sysPara.debug_enable = in_status;
      //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS); 
    }  
}
/*制冷无能需设定温度*/
void app_general_push_cold_no_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.cold_no_need_temp_set = in_set_temp;
 //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
 //   app_push_once_save_sto_parameter();
}
int16_t app_general_pull_cold_no_need_set_temp(void)
{
    return StoRunParameter.cold_no_need_temp_set;
}
/*制冷风盘能需设定温度*/
void app_general_push_cold_fan_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.cold_fan_need_temp_set = in_set_temp;
  //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
  //  app_push_once_save_sto_parameter();
}
int16_t app_general_pull_cold_fan_need_set_temp(void)
{
    return StoRunParameter.cold_fan_need_temp_set;
}
/*制冷辐射能需设定温度*/
void app_general_push_cold_warm_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.cold_warm_need_temp_set = in_set_temp;
   // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
   // app_push_once_save_sto_parameter();
}
int16_t app_general_pull_cold_warm_need_set_temp(void)
{
    return StoRunParameter.cold_warm_need_temp_set;
}
/*制冷露点配置温度*/
void app_general_push_config_lew_set_temp(int16_t in_set_temp)
{
    StoRunParameter.config_lew_temp_set = in_set_temp;
  //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
  //  app_push_once_save_sto_parameter();
}
int16_t app_general_pull_config_lew_set_temp(void)
{
    return StoRunParameter.config_lew_temp_set;
}
/*制热无能需设定温度*/
void app_general_push_heat_no_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.heat_no_need_temp_set = in_set_temp;
  //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
   // app_push_once_save_sto_parameter();
}
int16_t app_general_pull_heat_no_need_set_temp(void)
{
    return StoRunParameter.heat_no_need_temp_set;
}
/*制热风盘能需设定温度*/
void app_general_push_heat_fan_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.heat_fan_need_temp_set = in_set_temp;
   // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
   // app_push_once_save_sto_parameter();
}
int16_t app_general_pull_heat_fan_need_set_temp(void)
{
    return StoRunParameter.heat_fan_need_temp_set;
}
/*制热辐射能需设定温度*/
void app_general_push_heat_warm_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.heat_warm_need_temp_set = in_set_temp;
  //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
   // app_push_once_save_sto_parameter();
}
int16_t app_general_pull_heat_warm_need_set_temp(void)
{
    return StoRunParameter.heat_warm_need_temp_set;
}
/*制热回风配置温度*/
void app_general_push_config_back_wind_set_temp(int16_t in_set_temp)
{
    StoRunParameter.config_back_wind_temp_set = in_set_temp;
  //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
   // app_push_once_save_sto_parameter();
}
int16_t app_general_pull_config_back_wind_set_temp(void)
{
    return StoRunParameter.config_back_wind_temp_set;
}

/*除湿设定配置*/
void app_general_push_config_hum_set(int16_t in_set_temp)
{
    StoRunParameter.config_hum_set = in_set_temp;
   // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
   // app_push_once_save_sto_parameter();
}
int16_t app_general_pull_config_hum_set(void)
{
    return StoRunParameter.config_hum_set;
}
/*制冷风温最大设定温度*/
void app_general_push_cold_wind_max_set_temp(int16_t in_set_temp)
{
    StoRunParameter.cold_wind_max_temp_set = in_set_temp;
  //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
   // app_push_once_save_sto_parameter();
}
int16_t app_general_pull_cold_wind_max_set_temp(void)
{
    return StoRunParameter.cold_wind_max_temp_set;
}
/*制热风温最小设定温度 */
void app_general_push_heat_wind_min_set_temp(int16_t in_set_temp)
{
    StoRunParameter.heat_wind_min_temp_set = in_set_temp;
   // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
   // app_push_once_save_sto_parameter();
}
int16_t app_general_pull_heat_wind_min_set_temp(void)
{
    return StoRunParameter.heat_wind_min_temp_set;
}
/*制热风温最大设定温度*/
void app_general_push_heat_wind_max_set_temp(int16_t in_set_temp)
{
    StoRunParameter.heat_wind_max_temp_set = in_set_temp;
  //  app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
   // app_push_once_save_sto_parameter();
}
int16_t app_general_pull_heat_wind_max_set_temp(void)
{
    return StoRunParameter.heat_wind_max_temp_set;
}
/*主控制策略*/
uint8_t app_general_pull_main_control_method(void)
{
    return StoRunParameter.control_method;
}
void app_general_push_main_control_method(uint8_t in_method)
{
    StoRunParameter.control_method = (control_method_Def)in_method;
   // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
   // app_push_once_save_sto_parameter();
}
/*户外除湿状态*/
bool app_general_pull_indoor_dehum_status(void)
{
    return s_sysPara.indoor_dehum_status;
}
void app_general_push_indoor_dehum_status(bool in_status)
{
    if(s_sysPara.indoor_dehum_status != in_status)
    {
        s_sysPara.indoor_dehum_status = in_status;
     //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    }   
}

/*露点状态上限(开启)带宽 */
void app_general_push_lew_status_open_status(int16_t in_set_temp)
{
    StoRunParameter.lew_status_open_diff = in_set_temp;
    //app_push_once_save_sto_parameter();
}
int16_t app_general_pull_lew_status_open_status(void)
{
    return StoRunParameter.lew_status_open_diff;
}
/*露点状态下限(关闭)带宽 */
void app_general_push_lew_status_close_status(int16_t in_set_temp)
{
    StoRunParameter.lew_status_close_diff = in_set_temp;
    //app_push_once_save_sto_parameter();
}
int16_t app_general_pull_lew_status_close_status(void)
{
    return StoRunParameter.lew_status_close_diff;
}
/*输配软件复位 */
void app_general_push_cc_reset(uint16_t in_code)
{
    if(in_code == 0x3589)
    {
        while (1)
        {
           
        }
        
    }
}
/*环控软件复位 */
void app_general_push_hc_reset(uint16_t in_code)
{
    if(in_code == 0x3589)
    {
        app_general_push_system_reset_word(0x01<<14);
    }
}
/*水机开关机*/
bool app_general_pull_water_machine_status(void)
{
    return s_sysPara.water_machine_status;
}
void app_general_push_water_machine_status(bool in_status)
{
    if(s_sysPara.water_machine_status != in_status)
    {
        s_sysPara.water_machine_status = in_status;
     //   app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    }   
}
//-----------------------------------------------------------------------------
//除湿逻辑
//BN_TRUE 输出
//-----------------------------------------------------------------------------
#define MAX_HUM_VALVE   100
bool app_dehumidification_logic(int16_t _in_current_humitity,int16_t _in_set_huminty,int16_t _in_hum_deadZone)
{
    static bool lastOutputFlag = false;
    if((_in_current_humitity > MAX_HUM_VALVE) ||
       (_in_set_huminty > MAX_HUM_VALVE) ||
         (_in_hum_deadZone > MAX_HUM_VALVE))
    {
        return false;
    }
    if(_in_set_huminty <= _in_hum_deadZone)
    {
        return false;
    }
    if(_in_current_humitity > (_in_set_huminty + _in_hum_deadZone))
    {
        lastOutputFlag = true;
    }
    else if(_in_current_humitity < (_in_set_huminty - _in_hum_deadZone))
    {
        lastOutputFlag = false;
    }
    return lastOutputFlag;
}
/*采暖逻辑*/
#define MAX_TEMP_VALVE   1000
bool app_temp_logic(int16_t _in_current_temp,int16_t _in_set_temp,int16_t _in_temp_deadZone)
{
    static bool lastOutputFlag = false;
    if((_in_current_temp > MAX_TEMP_VALVE) ||
       (_in_set_temp > MAX_TEMP_VALVE) ||
         (_in_temp_deadZone > MAX_TEMP_VALVE))
    {
        return false;
    }
    if(_in_set_temp <= _in_temp_deadZone)
    {
        return false;
    }
    if(_in_current_temp >= (_in_set_temp + _in_temp_deadZone))
    {
        lastOutputFlag = false;
    }
    else if(_in_current_temp <= (_in_set_temp - _in_temp_deadZone))
    {
        lastOutputFlag = true;
    }
    return lastOutputFlag;
}


bool app_pull_aircod_humidity_output(void)
{
    bool humidityFlag = false;
    if(pull_integrated_sensor_error())
    {//传感器错误
        humidityFlag = false;        
    }
    else
    {
       // humidityFlag = app_dehumidification_logic((int16_t)Pull_RSS1001H_Humidity(),StoRunParameter.humidity_set,StoRunParameter.humidity_DeadZone);
    }
    return humidityFlag;
}

void time_stamp_task(void)
{  
    macro_createTimer(timer_stamp,timerType_millisecond,0);
    pbc_timerClockRun_task(&timer_stamp);
    if(pbc_pull_timerIsCompleted(&timer_stamp))
    {
        pbc_timeStamp_100ms_run_task();
        pbc_reload_timerClock(&timer_stamp,100);
    }
}
#define AI_STATUS_IDLE     0x01
#define AI_STATUS_CAL      0x02
#define AI_STATUS_DELAY    0x03
#define AI_STATUS_INIT     0x04
static uint8_t  aiStatus = AI_STATUS_INIT;
typedef struct
{//共用数据           
        int16_t    startOutputTemp;
        bool       lastOutputFlag;
}ai_parameter_t;
static ai_parameter_t aiParameter[MASTER_PAD_NUM];
uint16_t control_cal_ai_set_warm_temp(void)
{
    static uint16_t aiSetTemp = 400;
    static uint16_t oneSecondCount = 0;
    uint8_t i;
    uint8_t count = 0;
    int16_t total_temp = 0;
    uint16_t total_stratTemp = 0;
    static uint8_t hourCount = 0;
    bool adjustFlag = false;
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&measure_delay);
    switch(aiStatus)
    {
        case AI_STATUS_INIT:
        {
            aiSetTemp = 400;
            aiStatus = AI_STATUS_IDLE;
            break;
        }
        case AI_STATUS_DELAY:
        {
            if(pbc_pull_timerIsCompleted(&measure_delay))
            {
                pbc_reload_timerClock(&measure_delay,1000);
                oneSecondCount--;
                if(oneSecondCount == 0)
                {
                    aiStatus = AI_STATUS_CAL;
                }
                for(i = 0;i < MASTER_PAD_NUM;i++)
                {
                    if((s_sysPara.padPara[i].output_terminal) && (s_sysPara.padPara[i].onlineFlag))
                    {
                        if(false == aiParameter[i].lastOutputFlag)
                        {
                            aiParameter[i].lastOutputFlag = true;
                            aiParameter[i].startOutputTemp = s_sysPara.padPara[i].measureTemp;
                        }                    
                    }
                    else
                    {
                         aiParameter[i].lastOutputFlag = false;
                    }
                }
            }
            break;
        }
          
        case AI_STATUS_IDLE:
        {       
            for(i = 0;i < MASTER_PAD_NUM;i++)
            {
                if((s_sysPara.padPara[i].output_terminal) && (s_sysPara.padPara[i].onlineFlag))
                {//在线有加热需求
                    count++;
                    aiParameter[i].startOutputTemp = s_sysPara.padPara[i].measureTemp;
                    aiParameter[i].lastOutputFlag = true;
                }
                else
                {
                    aiParameter[i].lastOutputFlag = false;
                }
            }
            if(count)
            {
                oneSecondCount = ONE_HOUR;
                aiStatus = AI_STATUS_DELAY;
            }
            break;
        }
        
        case AI_STATUS_CAL:
        {     
            oneSecondCount = ONE_HOUR;
            aiStatus = AI_STATUS_DELAY;
            for(i = 0;i < MASTER_PAD_NUM;i++)
            {
                if((s_sysPara.padPara[i].output_terminal) && (s_sysPara.padPara[i].onlineFlag))
                {//在线有加热需求
                    count++;
                    total_temp+= s_sysPara.padPara[i].measureTemp;
                    total_stratTemp+=aiParameter[i].startOutputTemp;
                }
            }
            if(count)
            {             
                if(total_temp = total_stratTemp)
                {
                    hourCount++;
                    if(hourCount >= 6)
                    {
                        hourCount = 0;
                        aiSetTemp = aiSetTemp+10;
                        adjustFlag = true;
                    }
                }
                else
                {
                    hourCount = 0;
                    if(total_temp < total_stratTemp)
                    {
                        aiSetTemp = aiSetTemp+10;
                        adjustFlag = true;
                    }
                    else if(total_temp > total_stratTemp)
                    {
                         if((total_temp - total_stratTemp) / count >= 20)
                         {
                              aiSetTemp = aiSetTemp-10;
                              adjustFlag = true;
                         }
                    }
                }
            }
            if(aiSetTemp <=200)
            {
                aiSetTemp = 200;
            }
            if(aiSetTemp >600)
            {
                aiSetTemp = 600;
            }
            if(adjustFlag == true)
            {
               aiStatus = AI_STATUS_IDLE;
            }  
            else
            {
                aiStatus = AI_STATUS_DELAY;
            }
            break;
        }
       
        default:break;
    }
    return aiSetTemp;
}

uint16_t lewDropTemp_control(void)
{
    uint8_t i = 0;
    uint16_t minLewDropTemp = 900;
    for(i = 0;i < MASTER_PAD_NUM;i++)
    {                    
        if((s_sysPara.padPara[i].output_terminal) && (s_sysPara.padPara[i].onlineFlag))
        {
            if(minLewDropTemp > (mde_pull_drop_temp(s_sysPara.padPara[i].measureTemp,s_sysPara.padPara[i].humility)+StoRunParameter.coldDropDiff))
            {
                minLewDropTemp = (mde_pull_drop_temp(s_sysPara.padPara[i].measureTemp,s_sysPara.padPara[i].humility)+StoRunParameter.coldDropDiff);
            }
        }
    }
    return minLewDropTemp;
}

uint16_t control_cal_ai_set_cold_temp(void)
{
    static uint16_t aiSetTemp = 200;
    uint8_t i = 0;   
    uint8_t count = 0;
    static uint8_t hourCount = 0;
    int16_t total_temp = 0;
    uint16_t total_stratTemp = 0;
    static uint16_t oneSecondCount = 0;
    bool adjustFlag = false;
    uint16_t minLewDropTemp = 0;
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&measure_delay);
    minLewDropTemp = lewDropTemp_control();
    
    switch(aiStatus)
    {
        case AI_STATUS_INIT:
        {
            aiSetTemp = 200;
            aiStatus = AI_STATUS_IDLE;
            break;
        }
        case AI_STATUS_IDLE:
        {    
            for(i = 0;i < MASTER_PAD_NUM;i++)
            {
                if((s_sysPara.padPara[i].output_terminal) && (s_sysPara.padPara[i].onlineFlag))
                {//在线有加热需求
                    count++;
                    aiParameter[i].startOutputTemp = s_sysPara.padPara[i].measureTemp;
                    aiParameter[i].lastOutputFlag = true;
                }
                else
                {
                    aiParameter[i].lastOutputFlag = false;
                }
            }
            if(count)
            {
                oneSecondCount = ONE_HOUR;
                aiStatus = AI_STATUS_DELAY;
            }
            break;
        }
        case AI_STATUS_CAL:
        {          
            oneSecondCount = ONE_HOUR;
            aiStatus = AI_STATUS_DELAY;
            for(i = 0;i < MASTER_PAD_NUM;i++)
            {
                if((s_sysPara.padPara[i].output_terminal) && (s_sysPara.padPara[i].onlineFlag))
                {//在线有加热需求
                    count++;
                    total_temp+= s_sysPara.padPara[i].measureTemp;
                    total_stratTemp+=aiParameter[i].startOutputTemp;
                }
            }
            if(count)
            {             
                if(total_temp = total_stratTemp)
                {
                    hourCount++;
                    if(hourCount >= 6)
                    {
                        hourCount = 0;
                        aiSetTemp = aiSetTemp-10;
                        adjustFlag = true;
                    }
                }
                else
                {
                    hourCount = 0;
                    if(total_temp > total_stratTemp)
                    {
                        aiSetTemp = aiSetTemp-10;
                        adjustFlag = true;
                    }
                    else if(total_temp < total_stratTemp)
                    {
                         if((total_stratTemp - total_temp) / count >= 20)
                         {
                              aiSetTemp = aiSetTemp+10;
                              adjustFlag = true;
                         }
                    }
                }
            }
            if(aiSetTemp <=50)
            {
                aiSetTemp = 50;
            }
            if(aiSetTemp >350)
            {
                aiSetTemp = 350;
            }
            if(adjustFlag == true)
            {
               aiStatus = AI_STATUS_IDLE;
            }  
            else
            {
                aiStatus = AI_STATUS_DELAY;
            }     
            break;
        }
        case AI_STATUS_DELAY:
        {
            if(pbc_pull_timerIsCompleted(&measure_delay))
            {
                pbc_reload_timerClock(&measure_delay,1000);
                oneSecondCount--;
                if(oneSecondCount == 0)
                {
                    aiStatus = AI_STATUS_CAL;
                }
                for(i = 0;i < MASTER_PAD_NUM;i++)
                {                    
                    if((s_sysPara.padPara[i].output_terminal) && (s_sysPara.padPara[i].onlineFlag))
                    {
                        if(false == aiParameter[i].lastOutputFlag)
                        {
                            aiParameter[i].lastOutputFlag = true;
                            aiParameter[i].startOutputTemp = s_sysPara.padPara[i].measureTemp;
                        }                    
                    }
                    else
                    {
                         aiParameter[i].lastOutputFlag = false;
                    }
                } 
                if(aiSetTemp < minLewDropTemp)
                {
                    aiSetTemp = minLewDropTemp;
                    aiStatus = AI_STATUS_IDLE;
                }               
            }        
            break;
        }
        default:break;
    }  
    return aiSetTemp;
}
bool lowTempProtectFlag = false;
bool app_pull_low_protect_reguest(void)
{//产生防冻请求
    return lowTempProtectFlag;
}
/*运行设定温度*/
int16_t app_pull_mix_water_run_set_temp(void)
{
    if(lowTempProtectFlag)
    {//有防冻请求
        return StoRunParameter.mixHeatSetTemp;
    }
    else
    {
//        if(app_pull_mix_water_mode() == SET_COLD)
//        {//制冷设定温度
//            if(StoRunParameter.aiEnable)
//            {
//                s_sysPara.destTemp = control_cal_ai_set_cold_temp();
//                return s_sysPara.destTemp;
//            }
//            return StoRunParameter.mixColdSetTemp;
//        }
//        else
//        {//制热设定温度
//            if(StoRunParameter.aiEnable)
//            {
//                s_sysPara.destTemp = control_cal_ai_set_warm_temp();
//                return s_sysPara.destTemp;
//            }
//            return StoRunParameter.mixHeatSetTemp;
//        }   
        return StoRunParameter.mixColdSetTemp;
    }   
}

bool output_aircod_backup = false;//预冷阀输出
bool output_terminal_backup[MASTER_PAD_NUM];
void app_low_temp_prtect(void)
{
    uint8_t i = 0;
    if(s_sysPara.word_error&ERROR_NTC_BACK_WATER)
    {//回水传感器错误
        s_sysPara.output_pump = false;
        lowTempProtectFlag = false;//解除防冻请求
        s_sysPara.output_threeWayValve = false;      
        for(i = 0; i <  MASTER_PAD_NUM;i++)
        {
            output_terminal_backup[i] = false;
        }
    }
    else
    {
        if(app_pull_back_water_temp() < 50)
        {
            s_sysPara.output_pump = true;
            lowTempProtectFlag = true;//产生防冻请求
            s_sysPara.output_threeWayValve = true;
            for(i = 0; i <  MASTER_PAD_NUM;i++)
            {
                output_terminal_backup[i] = false;
            }
        }
        else if(app_pull_back_water_temp() > 100)
        {
            lowTempProtectFlag = false;//解除防冻请求
            s_sysPara.output_pump = false;
            s_sysPara.output_threeWayValve = false;       
            for(i = 0; i <  MASTER_PAD_NUM;i++)
            {
                output_terminal_backup[i] = false;
            }
        }
    }
}

/*辐射能需*/
bool app_pull_energy_need(void)
{
    uint8_t i = 0;
    uint8_t j = 0;
    if(s_sysPara.remoteControlFlag)
    {
        for(i = 0; i < (MASTER_PAD_NUM-2);i++)
        {
            if(s_sysPara.padPara[i].output_remote)
            {
                return true;
            }
        }
    }
    else
    {
        for(i = 0; i < MASTER_PAD_NUM;i++)
        {
            if(s_sysPara.padPara[i].pad_bind_warm)
            {
                for(j = 0; j < MASTER_PAD_NUM; j++)
                {
                    if(s_sysPara.padPara[i].pad_bind_warm & (0x01 << j))
                    {
                        if((s_sysPara.padPara[j].output_terminal) && ((s_sysPara.lewTempStatus & (0x01<<j)) == 0))
                        {//有输出同时没有露点状态
                            return true;
                        }
                    }       
                }
            }
        }	
    }	
    return false; 
}

#define  ENGER_NEED_RADIATION_BIT              0X01//辐射位
#define  ENGER_NEED_FAN_BIT                    0X02//风盘位
#define  ENGER_NEED_CLOD_BIT                   0X04//制冷位
#define  ENGER_NEED_LEW_TEMP_PROTECT_BIT       0X08//露点保护位
#define  MIX_VAVLE_ERROR_BIT                   0X10//混水阀故障
uint8_t system_need = 0;
int16_t max_lew_temp = 0;
/*获取开机辐射末端最大露点温度*/
int16_t app_pull_max_low_temp(void)
{
    return max_lew_temp;
}

/*露点逻辑*/
#define FIX_LEW_TEMP   160
void app_lew_temp_logic(void)
{
    static bool output = false;
    if(app_pull_max_low_temp() > FIX_LEW_TEMP)
    {
         output = true; 
    }
    else  if(app_pull_max_low_temp() <= (FIX_LEW_TEMP-10))
    {
        output = false;
    }
    if(output)
    {
        system_need |= ENGER_NEED_CLOD_BIT;
        s_sysPara.system_status_word |= 0x10;
    }
    else
    {
        system_need &= (~ENGER_NEED_CLOD_BIT);
        s_sysPara.system_status_word &= (~0x10);
    }
    if((StoRunParameter.airRunmode == AIR_MODE_HEAT) || (StoRunParameter.airRunmode == AIR_MODE_HUMIDITY)
       ||(StoRunParameter.airRunmode == AIR_MODE_FAN) || (StoRunParameter.airRunmode == AIR_MODE_AUTO_HEAT))
    {
        system_need &= (~ENGER_NEED_CLOD_BIT);
        s_sysPara.system_status_word &= (~0x10);
    }
}
/*辐射露点保护*/
void app_lew_temp_protect(void)
{
    bool output = false;
    uint8_t i = 0;
    uint8_t bind_warm_num = 0;
    uint8_t warm_lew_protec_num = 0;
    for(i = 0; i < MASTER_PAD_NUM;i++)
    {
        if((s_sysPara.padPara[i].onlineFlag) && (s_sysPara.padPara[i].chDevicePowerStatus))
        {//在线开机的情况下
            if(s_sysPara.padPara[i].pad_bind_warm)
            {//有辐射绑定输出
                bind_warm_num++;
                if(s_sysPara.lewTempStatus & s_sysPara.padPara[i].warmNedd)
                {
                    warm_lew_protec_num++;              
                }
            }     
        }       
    }
    if((bind_warm_num == warm_lew_protec_num) && (bind_warm_num != 0))
    {
        output = true;
    }
    if(output)
    {
        system_need |= ENGER_NEED_LEW_TEMP_PROTECT_BIT;
        s_sysPara.system_status_word |= 0x20;
    }
    else
    {
        if(app_pull_mix_water_temp() > (app_pull_max_low_temp()+20))
        {
            system_need &= (~ENGER_NEED_LEW_TEMP_PROTECT_BIT);
            s_sysPara.system_status_word &= (~0x20);
        }    
    }
    if((StoRunParameter.airRunmode == AIR_MODE_HEAT) || (StoRunParameter.airRunmode == AIR_MODE_HUMIDITY)
       ||(StoRunParameter.airRunmode == AIR_MODE_FAN) || (StoRunParameter.airRunmode == AIR_MODE_AUTO_HEAT))
    {
        system_need &= (~ENGER_NEED_LEW_TEMP_PROTECT_BIT);
        system_need &= (~MIX_VAVLE_ERROR_BIT);
        s_sysPara.system_status_word &= (~0x20);
    } 
}

uint8_t app_pull_system_energy_need(void)
{  
    return system_need;
}

//void app_check_feedback_degree_task(void)
//{
//    macro_createTimer(measure_delay,timerType_millisecond,0);
//    pbc_timerClockRun_task(&measure_delay);
//    if(s_sysPara.output_threeWayValve)
//    {//三通阀输出
//        if(pbc_pull_timerIsCompleted(&measure_delay))
//        {
//            pbc_reload_timerClock(&measure_delay,10000);
//            int16_t feedbackDegree;
//            feedbackDegree = mde_NTCSensor_pull_feedback_degree();
//            if(feedbackDegree)
//            {
//                app_general_clear_error_word(ERROR_THREE_WAY_VAVLE);
//                app_general_clear_master_error_word(SYS_ERROR_THREE_WAY_VAVLE);
//            }
//            else
//            {
//                app_general_push_error_word(ERROR_THREE_WAY_VAVLE);
//                app_general_push_master_error_word(SYS_ERROR_THREE_WAY_VAVLE);
//            }
//        }
//    }
//    else
//    {
//        pbc_reload_timerClock(&measure_delay,10000);
//        app_general_clear_error_word(ERROR_THREE_WAY_VAVLE);
//    }
//}

bool app_pull_id_in_list(uint8_t *in_id)
{
  //  uint8_t i = 0;
//    for(i = 0; i < MAX_DEVICE_NUM;i++)
//    {
//        linkDeviceList_t* logList;       
//        logList = app_link_log_pull_device_list(SYSTEM_PAD);
//        if(logList[i].onlineFlag)
//        {
//            if((logList[i].DeviceID[0] == in_id[0])&&
//              (logList[i].DeviceID[1] == in_id[1])&&
//              (logList[i].DeviceID[2] == in_id[2]) &&
//              (logList[i].DeviceID[3] == in_id[3])&&
//              (logList[i].DeviceID[4] == in_id[4])&&
//              (logList[i].DeviceID[5] == in_id[5]))
//            {
//                return true;
//            }
//        }      
//    }
    return false;
}

/*末端ID占用任务*/
void app_general_id_ocupy_task(void)
{
    uint8_t i = 0;

    macro_createTimer(check_list_delay,timerType_second,0);
    pbc_timerClockRun_task(&check_list_delay);
    if(pbc_pull_timerIsCompleted(&check_list_delay))
    {//1分钟监控一次
        pbc_reload_timerClock(&check_list_delay,60);
        for(i = 0; i < MASTER_PAD_NUM;i++)
        {
            if(false == app_pull_id_in_list(&s_sysPara.padPara[i].deviceId[0]))
            {
                s_sysPara.padPara[i].idUsedFlag = false;
                app_general_push_pad_warm_need(i,false);
                app_general_push_pad_fan_need(i,false);
            }
        }
    }
    for(i = 0; i < MASTER_PAD_NUM;i++)
    {//占用15分钟
        pbc_timerClockRun_task(app_general_pull_pad_id_ocupy_time(i));
        if(pbc_pull_timerIsOnceTriggered(app_general_pull_pad_id_ocupy_time(i)))
        {//释放
            s_sysPara.padPara[i].idUsedFlag = false;
			app_general_push_pad_warm_need(i,false);
            app_general_push_pad_fan_need(i,false);
        }
    }
}

/*末端输出状态*/
uint16_t app_general_pull_pad_output_status(void)
{
    return s_sysPara.pad_output_status;
}

/*检测数据状态改变*/
void app_general_check_parameter_change_task(void)
{
    static int16_t tempDestTemp = 0;
    static bool tempPump = false;
    static bool tempThreeVavle = false;
    static bool tempLowTempRequest = false;
    static uint16_t tempError = 0;
    static uint8_t tempSystemNeed = false;
    static uint16_t temp_lew_status = 0xff;
    static int16_t  max_lew_temp = 0;
    uint8_t i = 0;
    if(s_sysPara.destTemp != tempDestTemp)
    {
        tempDestTemp = s_sysPara.destTemp;
       // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_MIXWATER_AI_DEST_TEMP);
    }  
    if((tempPump != s_sysPara.output_pump) || (tempThreeVavle != s_sysPara.output_threeWayValve) 
       || (tempLowTempRequest != lowTempProtectFlag) || (tempError != s_sysPara.word_error) ||
         (app_pull_system_energy_need() != tempSystemNeed) || (app_pull_max_low_temp() != max_lew_temp))
    {
        tempPump = s_sysPara.output_pump;
        tempThreeVavle = s_sysPara.output_threeWayValve;
        tempLowTempRequest = lowTempProtectFlag;
        tempError = s_sysPara.word_error;
        tempSystemNeed = app_pull_system_energy_need();
        max_lew_temp = app_pull_max_low_temp();
       // app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_MIXWATER_OUT);
    }
    for(i = 0; i < MASTER_PAD_NUM;i++)
    {//露点状态不同通知面板
        if((s_sysPara.lewTempStatus & (0x01<<i)) != (temp_lew_status & (0x01<<i)))
        {
            temp_lew_status &= (~(0x01<<i));
            temp_lew_status |= (s_sysPara.lewTempStatus & (0x01<<i));
        //    app_link_syn_push_pad_updata_word(app_general_pull_pad_phy_port_bind_message(i),OCCUPY_PAD_SYSTEM_MESSAGE);
        }
    }
}
/*重复绑定*/
void check_rebind_list(void)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t num = 0;
    for(i = 0; i < MASTER_PAD_NUM;i++)
    {//辐射端
        if(s_sysPara.padPara[i].onlineFlag)
        {//在线
            for(j = (i+1);j < MASTER_PAD_NUM;j++)
            {   
                if(s_sysPara.padPara[j].onlineFlag)
                {
                    if(s_sysPara.padPara[i].pad_bind_warm & s_sysPara.padPara[j].pad_bind_warm)
                    {//辐射
                        s_sysPara.repeat_bind |= (s_sysPara.padPara[i].pad_bind_warm & s_sysPara.padPara[j].pad_bind_warm);
                    }
                    if(s_sysPara.padPara[i].pad_bind_warm & s_sysPara.padPara[j].pad_bind_fan)
                    {//风盘
                        s_sysPara.repeat_bind |= (s_sysPara.padPara[i].pad_bind_warm & s_sysPara.padPara[j].pad_bind_fan);
                    }
                }
                
            }
        }
       
    }
    for(i = 0; i < MASTER_PAD_NUM;i++)
    {//风盘端
        if(s_sysPara.padPara[i].onlineFlag)
        {
            for(j = (i+1);j < MASTER_PAD_NUM;j++)
            {
                if(s_sysPara.padPara[j].onlineFlag)
                {
                    if(s_sysPara.padPara[i].pad_bind_fan & s_sysPara.padPara[j].pad_bind_fan)
                    {
                        s_sysPara.repeat_bind |= (s_sysPara.padPara[i].pad_bind_fan & s_sysPara.padPara[j].pad_bind_fan);
                    }
                    if(s_sysPara.padPara[i].pad_bind_fan & s_sysPara.padPara[j].pad_bind_warm)
                    {
                        s_sysPara.repeat_bind |= (s_sysPara.padPara[i].pad_bind_fan & s_sysPara.padPara[j].pad_bind_warm);
                    }
                }              
            }
        }      
    }
    if(s_sysPara.repeat_bind)
    {
        for(i =0; i < MASTER_PAD_NUM;i++)
        {
            num = 0;
            if(s_sysPara.repeat_bind & (0x01<<i))
            {
                for(j = 0; j < MASTER_PAD_NUM;j++)
                {
                    if(s_sysPara.padPara[j].onlineFlag)
                    {
                        if(s_sysPara.padPara[j].pad_bind_warm & (0x01 << i))
                        {
                            num++;
                        }
                        if(s_sysPara.padPara[j].pad_bind_fan & (0x01 << i))
                        {
                           num++;
                        }
                    }               
                }
                if(num < 2)
                {
                    s_sysPara.repeat_bind &= (~(0x01<<i));
                }
            }
        }
    }
}

/*检测露点状态*/
/*开机状态下检测*/
void app_general_check_system_lew_temp_status(void)
{
    uint8_t i = 0;
    if((StoRunParameter.airRunmode == AIR_MODE_COOL) || (StoRunParameter.airRunmode == AIR_MODE_AUTO_COOL))
    {//制冷模式下
        for(i = 0; i < MASTER_PAD_NUM;i++)
        {
            if((s_sysPara.padPara[i].chDevicePowerStatus) && (s_sysPara.padPara[i].onlineFlag) && (s_sysPara.padPara[i].pad_bind_warm))
            {//在线并处于开机状态
                if(app_pull_mix_water_temp() <= (s_sysPara.padPara[i].lewDropTemp+StoRunParameter.lew_status_open_diff))
                {
                    s_sysPara.lewTempStatus |= (s_sysPara.padPara[i].pad_bind_warm);
                }
                else if(app_pull_mix_water_temp() >= (s_sysPara.padPara[i].lewDropTemp+StoRunParameter.lew_status_close_diff))
                {
                    s_sysPara.lewTempStatus &= (~s_sysPara.padPara[i].pad_bind_warm);
                }
            }
            else
            {
                s_sysPara.lewTempStatus &= (~s_sysPara.padPara[i].pad_bind_warm);
            }
        }
    }
    else
    {
        s_sysPara.lewTempStatus = 0;
    }   
}

/*时间戳监控*/
void app_general_check_dpstamp(void)
{
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&measure_delay);
    if(pbc_pull_timerIsCompleted(&measure_delay))
    {
        pbc_reload_timerClock(&measure_delay,10000);
        uint8_t i = 0;
        uint8_t j = 0;
        for(i = 0; i < MAX_DATA_POINT_LEN_SYSTEM;i++)
        {
            if(s_sysPara.dpStamp[i] > pbc_timeStamp_get_stamp())
            {
                s_sysPara.dpStamp[i] = pbc_timeStamp_get_stamp();
            }
        }  
        for(i = 0;i < MASTER_PAD_NUM;i++)
        {
            for(j = 0;j < MAX_DATA_POINT_LEN_PAD;j++)
            {
                if(s_sysPara.padPara[i].dpStamp[j] >  pbc_timeStamp_get_stamp())
                {
                    s_sysPara.padPara[i].dpStamp[j] = pbc_timeStamp_get_stamp();
                }
            }
            
        }            
    }
}

void app_general_para_updata_task(void)
{//1s更新一次
    uint8_t i = 0;
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&measure_delay);
    if(pbc_pull_timerIsCompleted(&measure_delay))
    {
        pbc_reload_timerClock(&measure_delay,1000);
        app_general_check_parameter_change_task();    
        app_lew_temp_logic();//辐射露点保护
        app_lew_temp_protect();//末端露点状态
        app_general_check_system_lew_temp_status();
        if(app_pull_energy_need())
        {//辐射能需
            system_need |= ENGER_NEED_RADIATION_BIT;
            s_sysPara.system_status_word |= 0x04;
        }
        else
        {
            system_need &= (~ENGER_NEED_RADIATION_BIT);
            s_sysPara.system_status_word &= (~0x04);
        }
        if(s_sysPara.remoteControlFlag)
        {
            if((s_sysPara.padPara[6].output_remote) ||
            (s_sysPara.padPara[7].output_remote) )
            {//风盘能需
                system_need |= ENGER_NEED_FAN_BIT;
                s_sysPara.system_status_word |= 0x08;
            }
            else
            {
                system_need &= (~ENGER_NEED_FAN_BIT);
                s_sysPara.system_status_word &= (~0x08);
            }
        }
        else
        {
            if((s_sysPara.padPara[6].output_terminal) ||
            (s_sysPara.padPara[7].output_terminal) )
            {
                system_need |= ENGER_NEED_FAN_BIT;
                s_sysPara.system_status_word |= 0x08;
            }
            else
            {
                system_need &= (~ENGER_NEED_FAN_BIT);
                s_sysPara.system_status_word &= (~0x08);
            }
        } 
        /*最高露点*/
        for(i = 0; i < MASTER_PAD_NUM;i++)
        {
            if((s_sysPara.padPara[i].chDevicePowerStatus) && (s_sysPara.padPara[i].pad_bind_warm) && (s_sysPara.padPara[i].onlineFlag))
            {//辐射开机
                if(s_sysPara.padPara[i].lewDropTemp > max_lew_temp)
                {
                    max_lew_temp = s_sysPara.padPara[i].lewDropTemp;
                }
            }
        }
        if(max_lew_temp == 0)
        {//无能需不需要除湿
            max_lew_temp = 100;
        }
        /*末端输出状态*/
        if(s_sysPara.remoteControlFlag)
        {//远程绝对控制
            for(i = 0; i <  MASTER_PAD_NUM;i++)
            {
                if(s_sysPara.padPara[i].output_remote)
                {
                    s_sysPara.pad_output_status |= (0x01<<i);
                }
                else
                {
                    s_sysPara.pad_output_status &= (~(0x01<<i));
                }     
            }
        }
        else
        {
            for(i = 0; i <  MASTER_PAD_NUM;i++)
            {
                if(output_terminal_backup[i])
                {
                    s_sysPara.pad_output_status |= (0x01<<i);
                }
                else
                {
                    s_sysPara.pad_output_status &= (~(0x01<<i));
                }     
            }
        }
        if(output_aircod_backup)
        {//预冷阀
            s_sysPara.pad_output_status |= (0x01 << 8);
        }
        else
        {   
            s_sysPara.pad_output_status &= (~(0x01<<8));
        }
    }
}
void app_general_mix_water_task(void)
{
    static bool cfg = false;
    if(cfg)
    {
        uint8_t i = 0;
        static bool start_energy_need = false;
        static int16_t start_mixTemp = 0;
        static bool inloop_checkFlag = false;
        macro_createTimer(energy_delay,timerType_second,0);
        macro_createTimer(inloop_check_delay,timerType_second,0);
        pbc_timerClockRun_task(&inloop_check_delay);
        pbc_timerClockRun_task(&energy_delay);
        remote_control_task();//20210426远程控制释放功能
        app_general_id_ocupy_task();//末端ID占用任务
        app_general_para_updata_task();//参数更新  
        app_general_check_dpstamp();//时间戳校准
        static uint8_t   pump_status = 0;    //水泵输出
        if(StoRunParameter.systemPower)
        {
            if(StoRunParameter.airRunmode == AIR_MODE_FAN)
            {//通风模式
                if(StoRunParameter.lowTempProtectConfig)
                {//开启防冻保护
                    app_low_temp_prtect();
                }
                else
                {//13個輸出全部關閉
                    s_sysPara.output_pump = false;
                    s_sysPara.output_threeWayValve = false;
                    output_aircod_backup = false;        
                    for(i = 0; i <  MASTER_PAD_NUM;i++)
                    {
                        output_terminal_backup[i] = false;
                    }
                }
            }
            else
            {//制冷、制热、除湿    
                switch(StoRunParameter.control_method)
                {
                    case METHOD_BASIC:
                    {
                        output_aircod_backup = s_sysPara.energyNeed;
                        if((system_need & ENGER_NEED_LEW_TEMP_PROTECT_BIT))
                        {//露点保护内循环
                            s_sysPara.output_threeWayValve = false;//关闭混水阀
                            if(inloop_checkFlag == false)
                            {
                                inloop_checkFlag = true;
                                start_mixTemp = app_pull_mix_water_temp();
                                pbc_reload_timerClock(&inloop_check_delay,180);
                            }
                            s_sysPara.output_pump = true;
                            for(i = 0; i <  MASTER_PAD_NUM;i++)
                            {
                                output_terminal_backup[i] = s_sysPara.padPara[i].output_terminal;
                            }
                        }
                        else
                        {
                            inloop_checkFlag = false;
                            system_need &= (~MIX_VAVLE_ERROR_BIT);
                            if((system_need & ENGER_NEED_RADIATION_BIT))
                            {//有辐射能需
                                if(s_sysPara.word_error&ERROR_NTC_MIX_WATER)
                                {//混水传感器错误
                                    s_sysPara.output_pump = false;
                                    s_sysPara.output_threeWayValve = false;       
                                    for(i = 0; i <  MASTER_PAD_NUM;i++)
                                    {
                                        output_terminal_backup[i] = false;
                                    }
                                }
                                else
                                {
                                    if(start_energy_need)
                                    {
                                        if(pbc_pull_timerIsCompleted(&energy_delay))
                                        {//120s后开启水泵跟三通阀
                                            s_sysPara.output_pump = true;
                                            s_sysPara.output_threeWayValve = true;
                                        }
                                    }
                                    else
                                    {//初始需求
                                        start_energy_need = true;
                                        pbc_reload_timerClock(&energy_delay,120);                      
                                    }
                                    for(i = 0; i <  MASTER_PAD_NUM;i++)
                                    {
                                        if((s_sysPara.padPara[i].output_terminal) && ((s_sysPara.lewTempStatus & (0x01<<i)) == 0))
                                        {//不处于露点状态下
                                            output_terminal_backup[i] = true;
                                        }
                                        else
                                        {
                                            output_terminal_backup[i] = false;
                                        }
                                    }
                                }  
                                pump_status = 0;
                            }
                            else
                            {//无辐射能需
                                start_energy_need = false;
                                switch (pump_status)
                                {
                                    case 0:
                                    {
                                        s_sysPara.output_pump = false;
                                        if((s_sysPara.master_supply_temp - app_pull_mix_water_temp()) >= 20)
                                        {
                                            s_sysPara.output_pump = true;
                                            pump_status = 1;
                                        }
                                        break;
                                    }
                                    case 1:
                                    {
                                        if((s_sysPara.master_supply_temp - app_pull_mix_water_temp()) >= 20)
                                        {//防止水泵停止运行后混水温度一直无变化
                                            s_sysPara.output_pump = true;
                                        }
                                        else if((s_sysPara.master_supply_temp - app_pull_mix_water_temp()) <= 10)
                                        {
                                            s_sysPara.output_pump = false;
                                        } 
                                        break;
                                    }                                                               
                                    default: break;
                                }                                
                                s_sysPara.output_threeWayValve = false;       
                                for(i = 0; i <  MASTER_PAD_NUM;i++)
                                {
                                    output_terminal_backup[i] = false;
                                }
                                /*两路风盘保持不变*/
                                output_terminal_backup[6] = s_sysPara.padPara[6].output_terminal;
                                output_terminal_backup[7] = s_sysPara.padPara[7].output_terminal;
                            }   
                        } 
                        if(inloop_checkFlag)
                        {
                            if(pbc_pull_timerIsCompleted(&inloop_check_delay))
                            {
                                if(start_mixTemp >= (app_pull_mix_water_temp()+20))
                                {//3分钟下降2度
                                    system_need |= MIX_VAVLE_ERROR_BIT;
                                }
                                else
                                {
                                    pbc_reload_timerClock(&inloop_check_delay,180);
                                    start_mixTemp = app_pull_mix_water_temp();
                                }
                            }
                        }     
                        break;
                    }
                    case METHOD_ONE:
                    {
                        output_aircod_backup = s_sysPara.energyNeed;
                        if((system_need & ENGER_NEED_LEW_TEMP_PROTECT_BIT))
                        {//露点保护内循环
                            s_sysPara.output_threeWayValve = false;//关闭混水阀
                            if(inloop_checkFlag == false)
                            {
                                inloop_checkFlag = true;
                                start_mixTemp = app_pull_mix_water_temp();
                                pbc_reload_timerClock(&inloop_check_delay,180);
                            }
                            s_sysPara.output_pump = true;
                            for(i = 0; i <  MASTER_PAD_NUM;i++)
                            {
                                output_terminal_backup[i] = s_sysPara.padPara[i].output_terminal;
                            }
                        }
                        else if(s_sysPara.indoor_dehum_status)
                        {//户外除湿状态
                            s_sysPara.output_pump = false;
                            s_sysPara.output_threeWayValve = false;      
                            for(i = 0; i <  MASTER_PAD_NUM;i++)
                            {
                                output_terminal_backup[i] = false;
                            }
                        }
                        else
                        {
                            inloop_checkFlag = false;
                            system_need &= (~MIX_VAVLE_ERROR_BIT);
                            if(system_need & ENGER_NEED_RADIATION_BIT)
                            {//有辐射能需
                                if(s_sysPara.word_error&ERROR_NTC_MIX_WATER)
                                {//混水传感器错误
                                    s_sysPara.output_pump = false;
                                    s_sysPara.output_threeWayValve = false;        
                                    for(i = 0; i <  MASTER_PAD_NUM;i++)
                                    {
                                        output_terminal_backup[i] = false;
                                    }
                                }
                                else
                                {
                                    int16_t max_lew_temp_backup = app_pull_max_low_temp();
                                    if(s_sysPara.debug_enable)
                                    {
                                        
                                    }
                                    else
                                    {
                                        StoRunParameter.mixColdSetTemp = max_lew_temp_backup;
                                    }
                                    if(start_energy_need)
                                    {
                                        if(pbc_pull_timerIsCompleted(&energy_delay))
                                        {//120s后开启水泵跟三通阀
                                            s_sysPara.output_pump = true;
                                            s_sysPara.output_threeWayValve = true;
                                        }
                                    }
                                    else
                                    {//初始需求
                                        start_energy_need = true;
                                        pbc_reload_timerClock(&energy_delay,120);                      
                                    }
                                   
                                    for(i = 0; i <  MASTER_PAD_NUM;i++)
                                    {
                                        if((s_sysPara.padPara[i].output_terminal) && ((s_sysPara.lewTempStatus & (0x01<<i)) == 0))
                                        {//不处于露点状态下
                                            output_terminal_backup[i] = true;
                                        }
                                        else
                                        {
                                            output_terminal_backup[i] = false;
                                        }
                                    }
                                } 
                                pump_status = 0;                                       
                            }
                            else
                            {//无辐射能需
                                start_energy_need = false;
                                switch (pump_status)
                                {
                                    case 0:
                                    {
                                        s_sysPara.output_pump = false;
                                        if((s_sysPara.master_supply_temp - app_pull_mix_water_temp()) >= 20)
                                        {
                                            s_sysPara.output_pump = true;
                                            pump_status = 1;
                                        }
                                        break;
                                    }
                                    case 1:
                                    {
                                        if((s_sysPara.master_supply_temp - app_pull_mix_water_temp()) >= 20)
                                        {//防止水泵停止运行后混水温度一直无变化
                                            s_sysPara.output_pump = true;
                                        }
                                        else if((s_sysPara.master_supply_temp - app_pull_mix_water_temp()) <= 10)
                                        {
                                            s_sysPara.output_pump = false;
                                        } 
                                        break;
                                    }                                                               
                                    default: break;
                                }           
                                s_sysPara.output_threeWayValve = false;        
                                for(i = 0; i <  MASTER_PAD_NUM;i++)
                                {
                                    output_terminal_backup[i] = false;
                                }
                                /*两路风盘保持不变*/
                                output_terminal_backup[6] = s_sysPara.padPara[6].output_terminal;
                                output_terminal_backup[7] = s_sysPara.padPara[7].output_terminal;
                            }   
                        } 
                        if(inloop_checkFlag)
                        {
                            if(pbc_pull_timerIsCompleted(&inloop_check_delay))
                            {
                                if(start_mixTemp >= (app_pull_mix_water_temp()+20))
                                {//3分钟下降2度
                                    system_need |= MIX_VAVLE_ERROR_BIT;
                                }
                                else
                                {
                                    pbc_reload_timerClock(&inloop_check_delay,180);
                                    start_mixTemp = app_pull_mix_water_temp();
                                }
                            }
                        }     
                        break;
                    }
                    default:
                    {
                        if((system_need & ENGER_NEED_LEW_TEMP_PROTECT_BIT))
                        {//露点保护内循环
                            s_sysPara.output_threeWayValve = false;//关闭混水阀
                            if(inloop_checkFlag == false)
                            {
                                inloop_checkFlag = true;
                                start_mixTemp = app_pull_mix_water_temp();
                                pbc_reload_timerClock(&inloop_check_delay,180);
                            }
                            s_sysPara.output_pump = true;
                            for(i = 0; i <  MASTER_PAD_NUM;i++)
                            {
                                output_terminal_backup[i] = s_sysPara.padPara[i].output_terminal;
                            }
                        }
                        else
                        {
                            output_aircod_backup = s_sysPara.energyNeed;
                            inloop_checkFlag = false;
                            system_need &= (~MIX_VAVLE_ERROR_BIT);
                            if((system_need & ENGER_NEED_RADIATION_BIT))
                            {//有辐射能需
                                if(s_sysPara.word_error&ERROR_NTC_MIX_WATER)
                                {//混水传感器错误
                                    s_sysPara.output_pump = false;
                                    s_sysPara.output_threeWayValve = false;      
                                    for(i = 0; i <  MASTER_PAD_NUM;i++)
                                    {
                                        output_terminal_backup[i] = false;
                                    }
                                }
                                else
                                {
                                    if(start_energy_need)
                                    {
                                        if(pbc_pull_timerIsCompleted(&energy_delay))
                                        {//120s后开启水泵跟三通阀
                                            s_sysPara.output_pump = true;
                                            s_sysPara.output_threeWayValve = true;
                                        }
                                    }
                                    else
                                    {//初始需求
                                        start_energy_need = true;
                                        pbc_reload_timerClock(&energy_delay,120);                      
                                    }
                                    
                                    for(i = 0; i <  MASTER_PAD_NUM;i++)
                                    {
                                        if((s_sysPara.padPara[i].output_terminal) && ((s_sysPara.lewTempStatus & (0x01<<i)) == 0))
                                        {//不处于露点状态下
                                            output_terminal_backup[i] = true;
                                        }
                                        else
                                        {
                                            output_terminal_backup[i] = false;
                                        }
                                    }
                                }  
                                pump_status = 0;                                      
                            }
                            else
                            {//无辐射能需
                                start_energy_need = false;
                                switch (pump_status)
                                {
                                    case 0:
                                    {
                                        s_sysPara.output_pump = false;
                                        if((s_sysPara.master_supply_temp - app_pull_mix_water_temp()) >= 20)
                                        {
                                            s_sysPara.output_pump = true;
                                            pump_status = 1;
                                        }
                                        break;
                                    }
                                    case 1:
                                    {
                                        if((s_sysPara.master_supply_temp - app_pull_mix_water_temp()) >= 20)
                                        {//防止水泵停止运行后混水温度一直无变化
                                            s_sysPara.output_pump = true;
                                        }
                                        else if((s_sysPara.master_supply_temp - app_pull_mix_water_temp()) <= 10)
                                        {
                                            s_sysPara.output_pump = false;
                                        } 
                                        break;
                                    }                                                               
                                    default: break;
                                }           
                                s_sysPara.output_threeWayValve = false;        
                                for(i = 0; i <  MASTER_PAD_NUM;i++)
                                {
                                    output_terminal_backup[i] = false;
                                }
                                /*两路风盘保持不变*/
                                output_terminal_backup[6] = s_sysPara.padPara[6].output_terminal;
                                output_terminal_backup[7] = s_sysPara.padPara[7].output_terminal;
                            }   
                        } 
                        if(inloop_checkFlag)
                        {
                            if(pbc_pull_timerIsCompleted(&inloop_check_delay))
                            {
                                if(start_mixTemp >= (app_pull_mix_water_temp()+20))
                                {//3分钟下降2度
                                    system_need |= MIX_VAVLE_ERROR_BIT;
                                }
                                else
                                {
                                    pbc_reload_timerClock(&inloop_check_delay,180);
                                    start_mixTemp = app_pull_mix_water_temp();
                                }
                            }
                        }     
                        break;
                    }
                }                 
            }       
        }
        else
        {//关机
            if(StoRunParameter.lowTempProtectConfig)
            {//开启防冻保护
                app_low_temp_prtect();
            }
            else
            {//13個輸出全部關閉
                s_sysPara.output_pump = false;
                s_sysPara.output_threeWayValve = false;
                output_aircod_backup = false;
                for(i = 0; i <  MASTER_PAD_NUM;i++)
                {
                    output_terminal_backup[i] = false;
                }
            }    
        }
        if(s_sysPara.word_error&ERROR_THREE_WAY_VAVLE)
        {//三通阀故障关闭水泵跟执行器
            s_sysPara.output_pump = false;
            for(i = 0; i <  MASTER_PAD_NUM;i++)
            {
                output_terminal_backup[i] = false;
            }
        }
        //----------实际输出，12组实际只需8组输出
        uint8_t delay_count = 0;
        macro_createTimer(adjust_delay,timerType_millisecond,3000);
        pbc_timerClockRun_task(&adjust_delay);
        if(output_aircod_backup)
        {
            mde_relay_on(RELAY_AIRCOD,(10+delay_count*10));
            delay_count++;
        }
        else
        {
            mde_relay_off(RELAY_AIRCOD,0);
        }
        if(s_sysPara.remoteControlFlag)
        {//远程绝对控制
            for(i = 0; i <  (MASTER_PAD_NUM-MASTER_PAD_VIRTUAL_NUM);i++)
            {
                if(s_sysPara.padPara[i].output_remote)
                {
                    mde_relay_on(i,(10+delay_count*10));
                    delay_count++;
                }
                else
                {
                    mde_relay_off(i,0);
                }     
            }
        }
        else
        {
            for(i = 0; i <  (MASTER_PAD_NUM-MASTER_PAD_VIRTUAL_NUM);i++)
            {
                if(output_terminal_backup[i])
                {
                    mde_relay_on(i,(10+delay_count*10));
                    delay_count++;
                }
                else
                {
                    mde_relay_off(i,0);
                }     
            }
        }
        
        if(s_sysPara.output_pump)
        {
            mde_relay_on(RELAY_PUMP,(10+delay_count*10));
        }
        else
        {
            mde_relay_off(RELAY_PUMP,0);
        }
      //  mod_mixWater_set_puty(50);
        if(s_sysPara.output_threeWayValve)
        {
            if(pbc_pull_timerIsCompleted(&adjust_delay))
            {
                pbc_reload_timerClock(&adjust_delay,3000); 
                //mod_mixWater_adjust(app_pull_mix_water_mode(),app_pull_mix_water_temp(),app_pull_back_water_temp(),app_pull_mix_water_run_set_temp());
            }
        }
        else
        {
           // mod_mixWater_set_puty(0);//关闭三通阀  
        }
    }
    else
    {
        cfg = true;
        uint8_t  j;
        for(j = 0; j < MASTER_PAD_NUM;j++)
        {
            s_sysPara.padPara[j].id_ocupy_delay.timStatusBits = timerType_second;
        }       
    }   
}
uint16_t aircodMesBuff_1[ARICOD_READ_ONLY_REG_NUM]={
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //0-15
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//16-31
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //32-47
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //48-63
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //64-79
            0x0000,0x0000,0x0000,0x0000,                                                                                     //80-83
                            };

uint16_t aircodMesBuff_5001[ARICOD_READ_WRITE_REG_NUM]={
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //0-15
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//16-31
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //32-47
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//48-63
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,                                                 //64-72
                                };
bool APP_pull_aricod_message(uint16_t in_reg_add,uint16_t *out_reg_value)
{
    if((in_reg_add >= 1) && (in_reg_add <= ARICOD_READ_ONLY_REG_NUM))
    {
        *out_reg_value = aircodMesBuff_1[(in_reg_add-1)];
        return true;
    }  
    else if((in_reg_add >= 5001) && (in_reg_add <= (5000+ARICOD_READ_WRITE_REG_NUM)))
    {
        *out_reg_value = aircodMesBuff_5001[(in_reg_add-5001)];
        return true;
    }  
    return false;
}
bool APP_push_aricod_message(uint16_t in_reg_add,uint16_t in_reg_value)
{
    if((in_reg_add >= 1) && (in_reg_add <= ARICOD_READ_ONLY_REG_NUM))
    {     
       aircodMesBuff_1[(in_reg_add-1)] = in_reg_value;
       return true;
    } 
    else if((in_reg_add >= 5001) && (in_reg_add <= (5000+ARICOD_READ_WRITE_REG_NUM)))
    {
		aircodMesBuff_5001[(in_reg_add-5001)] = in_reg_value;       
        return true;
    } 
    return false;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: 通用应用task
//-----------------------------------------------------------------------------
void app_general_task(void)
{
    static sdt_bool sys_cfged = sdt_false;
    mde_IWDG_FeedDog();
    if(sys_cfged)
    {     
        //app_sto_run_parameter_task();
		app_pwm_control_task();      
        app_logic_realy_task();
       // app_link_scheduler_task();   
      //  app_modbus_onewire_task();
        app_modbus_remote_task();      
        app_real_time_clock_task();
        app_temperature_task();    
       // app_upgrade_easy_task();
        time_stamp_task();
        //app_general_mix_water_task();
        app_led_task();   
    }
    else
    {
        sys_cfged = sdt_true;      
      //  app_read_run_parameter();      
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++