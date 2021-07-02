//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
#include "stdlib.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static uint16_t protection_cpor_bits;//
#define feedbcak_wind_error             sdt_bit0        //转速故障
#define rs1001_offline                  sdt_bit1       //综合传感器故障

typedef struct
{//共用数据     
        uint16_t                   system_error_word;       //主机集成故障字
        uint16_t                   ac_error_word;           //输配故障字
        uint16_t                   ae_error_word;           //环控故障字
        uint16_t                   system_ntc_error;       //系统传感器故障  
        uint16_t                   ae_ntc_error;            //环控传感器故障  
        uint16_t                   ac_ntc_error;            //输配传感器故障
        uint16_t                   system_status_word;      //状态字     
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
        uint16_t                   new_air_speed;
        uint16_t                   back_air_speed;
        uint16_t                   water_machine_fre;
        uint16_t                   fu_machine_fre;
        int16_t                    master_supply_temp;
        int16_t                    master_living_temp;
        int16_t                    master_outdoor_temp;
        int16_t                    max_lew_temp;// 最高露点温度
        uint16_t                   mixColdSetTemp;        //混水制冷设定温度
        uint16_t                   mixHeatSetTemp;        //混水制热设定温度    
        int16_t                    measure_mixTemp;       //混水测量温度
        int16_t                    backWaterMeasureTemp;  //回水测量温度
        int16_t                    inWaterMeasureTemp;    //进水测量温度
        int16_t                    dewPointTemp;          //露点温度   
        int16_t                    destTemp;              //目标温度  
        int16_t                    th7Temp;               //进水温度
        uint8_t                    padEnergyNeed;         //末端能需
        uint8_t                    lowTempProtectConfig;//防冻温度，0为关闭
        bool                       aiEnable;              //ai使能
        bool                       energyNeed;            //环控能需      
        bool                       output_pump:1;          //水泵输出
        bool                       output_threeWayValve:1;  //三通阀输出
        bool                       output_lowProtect:1;  //防冻输出
        bool                       lowProtectRequest:1;//防冻请求
        bool                       indoor_dehum_status:1;//户外除湿状态  
        bool                       water_machine_status:1;//水机状态     
        uint32_t                   dpStamp[MAX_DATA_POINT_LEN];
}SysPara_t;

SysPara_t s_sysPara = {
        .outdoor_temp = 220,
        .outdoor_hum = 50,
        .before_fu_temp= 220,
        .before_fu_hum= 50,
        .after_fu_temp= 220,
        .after_fu_hum= 50,
        .back_air_temp= 220,
        .back_air_hum= 50,
        .exhast_air_temp= 220,
        .exhast_air_hum= 50,
        .back_air_co2= 10,
        .back_air_pm25= 10,
        .master_living_temp = 500,
        .master_supply_temp = 400,
        .mixColdSetTemp = 160,
        .mixHeatSetTemp = 300,
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
/*系统主机故障字*/
uint16_t app_general_pull_master_error_word(void)
{
    return s_sysPara.system_error_word;
}
void app_general_push_master_error_word(uint16_t in_error)
{
    s_sysPara.system_error_word |=  in_error;
}
/*环控故障字*/
uint16_t app_general_pull_ae_error_word(void)
{
    return s_sysPara.ae_error_word;
}
void app_general_push_ae_error_word(uint16_t in_error)
{
    s_sysPara.system_error_word |=  in_error;   
    
    if((s_sysPara.ae_error_word & in_error) == 0)
    {
        s_sysPara.ae_error_word |=  in_error;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    }  
}
void app_general_clear_ae_error_word(uint16_t in_error)
{  
    s_sysPara.system_error_word &=  (~in_error);
    if(s_sysPara.ae_error_word & in_error)
    {
        s_sysPara.ae_error_word &=  (~in_error);
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    }
}
/*输配故障字*/
uint16_t app_general_pull_ac_error_word(void)
{
    return s_sysPara.ac_error_word;
}

void app_general_push_ac_error_word(uint16_t in_error)
{
    s_sysPara.ac_error_word =  in_error;
    s_sysPara.system_error_word &= 0xE7f8;
    s_sysPara.system_error_word |=  in_error;
}

/*系统状态字*/
uint16_t app_general_pull_system_status_word(void)
{
    return s_sysPara.system_status_word;
}
/*开关机*/
void app_general_push_power_status(bool in_power_status)
{  
    if(in_power_status != StoRunParameter.systemPower)
    {
        StoRunParameter.systemPower = in_power_status;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_POWER);        
        app_push_once_save_sto_parameter();
    }
	if(StoRunParameter.systemPower)
	{//开机
		APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,1);
	}
	else
	{//关机
		APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,0);
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
             (in_mode ==AIR_MODE_AUTO_COOL) || (in_mode ==AIR_MODE_AUTO_HEAT))
    {
		if(StoRunParameter.airRunmode != in_mode)
		{
			StoRunParameter.airRunmode = in_mode;
            app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_RUN_MODE);
			app_push_once_save_sto_parameter();           
		}
		APP_push_aricod_message(DRIVE_BOARD_SET_MODE,StoRunParameter.airRunmode);
    }
}
AirRunMode_Def app_general_pull_aircod_mode(void)
{
    return StoRunParameter.airRunmode;
}

/*设定湿度*/
void app_general_push_aircod_humidity(int16_t in_set_humidity)
{
    if(StoRunParameter.humidity_set != in_set_humidity)
    {
        StoRunParameter.humidity_set = in_set_humidity;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WIND_SET_HUM);
        app_push_once_save_sto_parameter();
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
            app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WIND_SET_SPEED);
			app_push_once_save_sto_parameter();
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
    if(StoRunParameter.coldTemp_set != in_set_temp)
    {
        StoRunParameter.coldTemp_set = in_set_temp;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WIND_SET_CLOD_TEMP);
        app_push_once_save_sto_parameter();
    }
}

void app_general_push_aircod_heat_temp(int16_t in_set_temp)
{
    if(StoRunParameter.hotTemp_set != in_set_temp)
    {
        StoRunParameter.hotTemp_set = in_set_temp;   
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WIND_SET_HEAT_TEMP);           
        app_push_once_save_sto_parameter();
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
/*制冷回风设置温度*/
int16_t app_general_pull_aircod_cold_temp(void)
{
    return StoRunParameter.coldTemp_set;
}
/*制冷回风设置停止温度*/
int16_t app_general_pull_aircod_cold_stop_temp(void)
{//温差3度，停止温差1.5度
    return (300);
}

int16_t app_general_pull_aircod_heat_temp(void)
{
    return StoRunParameter.hotTemp_set;
}

int16_t app_general_pull_aircod_heat_stop_temp(void)
{
    return (160);
}
int16_t app_general_pull_aircod_heat_start_temp(void)
{
    return (300);
}

/*新风PWM*/
uint8_t app_general_pull_new_air_pwm_low(void)
{
    return StoRunParameter.newAirLowPwm;
}
uint8_t app_general_pull_new_air_pwm_mid(void)
{
    return StoRunParameter.newAirMidPwm;
}
uint8_t app_general_pull_new_air_pwm_high(void)
{
    return StoRunParameter.newAirHighPwm;
}
void app_general_push_new_air_pwm_low(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        StoRunParameter.newAirLowPwm = in_pwm;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_NEW_AIR_PWM);
        app_push_once_save_sto_parameter();
    }
}
void app_general_push_new_air_pwm_mid(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        StoRunParameter.newAirMidPwm = in_pwm;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_NEW_AIR_PWM);
        app_push_once_save_sto_parameter();
    }
}
void app_general_push_new_air_pwm_high(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        StoRunParameter.newAirHighPwm = in_pwm;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_NEW_AIR_PWM);
        app_push_once_save_sto_parameter();
    }
}

/*回风风PWM*/
uint8_t app_general_pull_back_air_pwm_low(void)
{
    return StoRunParameter.backAirLowPwm;
}
uint8_t app_general_pull_back_air_pwm_mid(void)
{
    return StoRunParameter.backAirMidPwm;
}
uint8_t app_general_pull_back_air_pwm_high(void)
{
    return StoRunParameter.backAirHighPwm;
}
void app_general_push_back_air_pwm_low(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        StoRunParameter.backAirLowPwm = in_pwm;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_PWM);
        app_push_once_save_sto_parameter();
    }
}
void app_general_push_back_air_pwm_mid(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        StoRunParameter.backAirMidPwm = in_pwm;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_PWM);
        app_push_once_save_sto_parameter();
    }
}
void app_general_push_back_air_pwm_high(uint8_t in_pwm)
{
    if(in_pwm<=100)
    {
        StoRunParameter.backAirHighPwm = in_pwm;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_PWM);
        app_push_once_save_sto_parameter();
    }
}

/*主机制冷制热生活热水设定水温*/
void app_general_push_set_cold_water_temp(int16_t in_set_temp)
{
    if(StoRunParameter.set_cold_water_temp != in_set_temp)
    {
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WATER_SET_CLOD_TEMP);
        StoRunParameter.set_cold_water_temp = in_set_temp;
        app_push_once_save_sto_parameter();
    }
}

void app_general_push_set_heat_water_temp(int16_t in_set_temp)
{
    if(StoRunParameter.set_heat_water_temp != in_set_temp)
    {
        StoRunParameter.set_heat_water_temp = in_set_temp;   
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WATER_SET_HEAT_TEMP); 
        app_push_once_save_sto_parameter();   
    }        
}

void app_general_push_set_living_water_temp(int16_t in_set_temp)
{ ///生活热水设定温度
    if(StoRunParameter.set_living_water_temp != in_set_temp)
    {
        StoRunParameter.set_living_water_temp = in_set_temp;  
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_WATER_SET_LIVING_TEMP); 
        app_push_once_save_sto_parameter();
    } 
    APP_push_aricod_message(DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP,StoRunParameter.set_living_water_temp);       
}
/*制冷出水设置温度*/
int16_t app_general_pull_set_cold_water_temp(void)
{
    return StoRunParameter.set_cold_water_temp;
}
/*制冷出水设置温度*/
int16_t app_general_pull_set_water_machine_start_cold_temp(void)
{
    return (150);
}
/*水机停止运行温度*/
int16_t app_general_pull_set_water_machine_stop_cold_temp(void)
{
    return (250);
}

int16_t app_general_pull_set_heat_water_temp(void)
{//制热出水
    return StoRunParameter.set_heat_water_temp;
}
/*水机停止运行温度*/
int16_t app_general_pull_set_water_machine_stop_heat_temp(void)
{
    return (250);
}
int16_t app_general_pull_set_living_water_temp(void)
{
    return StoRunParameter.set_living_water_temp;
}
int16_t app_general_pull_set_cold_backwater_temp(void)
{
    return StoRunParameter.cool_backwater_settemp;
}
int16_t app_general_pull_set_heat_backwater_temp(void)
{
    return StoRunParameter.hot_backwater_settemp;
}
/*制冷无能需设定温度*/
void app_general_push_cold_no_need_set_temp(int16_t in_set_temp)
{
    if(StoRunParameter.cold_no_need_temp_set != in_set_temp)
    {
         StoRunParameter.cold_no_need_temp_set = in_set_temp;
         app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
         app_push_once_save_sto_parameter();
    }  
}
int16_t app_general_pull_cold_no_need_set_temp(void)
{
    return StoRunParameter.cold_no_need_temp_set;
}
/*制冷风盘能需设定温度*/
void app_general_push_cold_fan_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.cold_fan_need_temp_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_cold_fan_need_set_temp(void)
{
    return StoRunParameter.cold_fan_need_temp_set;
}
/*制冷辐射能需设定温度*/
void app_general_push_cold_warm_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.cold_warm_need_temp_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_cold_warm_need_set_temp(void)
{
    return StoRunParameter.cold_warm_need_temp_set;
}
/*制冷露点配置温度*/
void app_general_push_config_lew_set_temp(int16_t in_set_temp)
{
    StoRunParameter.config_lew_temp_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_config_lew_set_temp(void)
{
    return StoRunParameter.config_lew_temp_set;
}
/*制热无能需设定温度*/
void app_general_push_heat_no_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.heat_no_need_temp_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_heat_no_need_set_temp(void)
{
    return StoRunParameter.heat_no_need_temp_set;
}
/*制热风盘能需设定温度*/
void app_general_push_heat_fan_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.heat_fan_need_temp_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_heat_fan_need_set_temp(void)
{
    return StoRunParameter.heat_fan_need_temp_set;
}
/*制热辐射能需设定温度*/
void app_general_push_heat_warm_need_set_temp(int16_t in_set_temp)
{
    StoRunParameter.heat_warm_need_temp_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_heat_warm_need_set_temp(void)
{
    return StoRunParameter.heat_warm_need_temp_set;
}
/*制热回风配置温度*/
void app_general_push_config_back_wind_set_temp(int16_t in_set_temp)
{
    StoRunParameter.config_back_wind_temp_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_config_back_wind_set_temp(void)
{
    return StoRunParameter.config_back_wind_temp_set;
}

/*除湿设定配置*/
void app_general_push_config_hum_set(int16_t in_set_temp)
{
    StoRunParameter.config_hum_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_config_hum_set(void)
{
    return StoRunParameter.config_hum_set;
}
/*制冷风温最大设定温度*/
void app_general_push_cold_wind_max_set_temp(int16_t in_set_temp)
{
    StoRunParameter.cold_wind_max_temp_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_cold_wind_max_set_temp(void)
{
    return StoRunParameter.cold_wind_max_temp_set;
}
/*制热风温最小设定温度 */
void app_general_push_heat_wind_min_set_temp(int16_t in_set_temp)
{
    StoRunParameter.heat_wind_min_temp_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_heat_wind_min_set_temp(void)
{
    return StoRunParameter.heat_wind_min_temp_set;
}
/*制热风温最大设定温度*/
void app_general_push_heat_wind_max_set_temp(int16_t in_set_temp)
{
    StoRunParameter.heat_wind_max_temp_set = in_set_temp;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
int16_t app_general_pull_heat_wind_max_set_temp(void)
{
    return StoRunParameter.heat_wind_max_temp_set;
}


/*户外进风/氟盘前/氟盘后/回风/排风温湿度*/
void app_general_push_outdoor_temp(int16_t in_set_temp)
{
    s_sysPara.outdoor_temp = in_set_temp;
}
int16_t app_general_pull_outdoor_temp(void)
{
    return s_sysPara.outdoor_temp;
}
void app_general_push_outdoor_hum(int16_t in_set_hum)
{
    s_sysPara.outdoor_hum = in_set_hum;
}
int16_t app_general_pull_outdoor_hum(void)
{
    return s_sysPara.outdoor_hum;
}
void app_general_push_before_fu_temp(int16_t in_set_temp)
{
    s_sysPara.before_fu_temp = in_set_temp;
}
int16_t app_general_pull_before_fu_temp(void)
{
    return s_sysPara.before_fu_temp;
}
void app_general_push_before_fu_hum(int16_t in_set_hum)
{
    s_sysPara.before_fu_hum = in_set_hum;
}
int16_t app_general_pull_before_fu_hum(void)
{
    return s_sysPara.before_fu_hum;
}
void app_general_push_after_fu_temp(int16_t in_set_temp)
{
    s_sysPara.after_fu_temp = in_set_temp;
}
int16_t app_general_pull_after_fu_temp(void)
{
    return s_sysPara.after_fu_temp;
}
void app_general_push_after_fu_hum(int16_t in_set_hum)
{
    s_sysPara.after_fu_hum = in_set_hum;
}
int16_t app_general_pull_after_fu_hum(void)
{
    return s_sysPara.after_fu_hum;
}
void app_general_push_backair_temp(int16_t in_set_temp)
{
    s_sysPara.back_air_temp = in_set_temp;
}
int16_t app_general_pull_backair_temp(void)
{
    return s_sysPara.back_air_temp;
}
void app_general_push_backair_hum(int16_t in_set_hum)
{
    s_sysPara.back_air_hum = in_set_hum;
}
int16_t app_general_pull_backair_hum(void)
{
    return s_sysPara.back_air_hum;
}
void app_general_push_exhastair_temp(int16_t in_set_temp)
{
    s_sysPara.exhast_air_temp = in_set_temp;
}
int16_t app_general_pull_exhastair_temp(void)
{
    return s_sysPara.exhast_air_temp;
}
void app_general_push_exhastair_hum(int16_t in_set_hum)
{
    s_sysPara.exhast_air_hum = in_set_hum;
}
int16_t app_general_pull_exhastair_hum(void)
{
    return s_sysPara.exhast_air_hum;
}
/*回风co2 pm25*/
void app_general_push_backair_co2(int16_t in_set_co2)
{
    s_sysPara.back_air_co2 = in_set_co2;
}
int16_t app_general_pull_backair_co2(void)
{
    return s_sysPara.back_air_co2;
}
void app_general_push_backair_pm25(int16_t in_set_pm25)
{
    s_sysPara.back_air_pm25 = in_set_pm25;
}
int16_t app_general_pull_backair_pm25(void)
{
    return s_sysPara.back_air_pm25;
}
/*末端能需*/
uint8_t app_pull_system_energy_need(void)
{
    return s_sysPara.padEnergyNeed;
}
void app_push_system_energy_need(uint8_t in_need)
{
    s_sysPara.padEnergyNeed = in_need;
}

/*主控制策略*/
uint8_t app_general_pull_main_control_method(void)
{
    return StoRunParameter.control_method;
}
void app_general_push_main_control_method(uint8_t in_method)
{
    StoRunParameter.control_method = (control_method_Def)in_method;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}

/*设定温度带宽*/
void app_general_push_aircod_setTemp_deadZone(int16_t in_deadZone)
{
	if((in_deadZone >= 5) && (in_deadZone <= 100)&&(in_deadZone%5==0))
	{		
		if(StoRunParameter.temp_DeadZone != in_deadZone)
		{
			StoRunParameter.temp_DeadZone = in_deadZone;
            app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_DEAD_ZONE);
			app_push_once_save_sto_parameter();
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
    if(StoRunParameter.humidity_DeadZone != in_deadZone)
    {
        StoRunParameter.humidity_DeadZone = in_deadZone;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_DEAD_ZONE);
        app_push_once_save_sto_parameter();
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
    s_sysPara.new_air_speed = in_speed;
}
/*回风风机转速*/
uint16_t app_general_pull_aircod_backair_speed(void)
{	
	return s_sysPara.back_air_speed;
}
void app_general_push_aircod_backair_speed(uint16_t in_speed)
{
    s_sysPara.back_air_speed = in_speed;
}
/*氟机水机频率*/
void app_general_push_fu_machine_fre(uint16_t in_fre)
{
    s_sysPara.fu_machine_fre = in_fre;
}
uint16_t app_general_pull_fu_machine_fre(void)
{
   uint16_t pull_fre;
   APP_pull_aricod_message(DRIVE_BOARD_CUTRENT_FU_FRE,&pull_fre);//2 氟机
   s_sysPara.fu_machine_fre = (int16_t)pull_fre;
   return s_sysPara.fu_machine_fre;
}
void app_general_push_water_machine_fre(uint16_t in_fre)
{
    s_sysPara.water_machine_fre = in_fre;
}
uint16_t app_general_pull_water_machine_fre(void)
{
   uint16_t pull_fre;
   APP_pull_aricod_message(DRIVE_BOARD_CUTRENT_WATER_FRE,&pull_fre);//28 水机
   s_sysPara.water_machine_fre = (int16_t)pull_fre;
   return s_sysPara.water_machine_fre; 
}
//主机供水温度、生活热水温度、户外温度
int16_t app_general_pull_master_supply_temp(void)
{
	uint16_t aircod_th7_temp;
    APP_pull_aricod_message(DRIVE_BOARD_TH7_TEMP,&aircod_th7_temp);
	s_sysPara.master_supply_temp = aircod_th7_temp;
    return s_sysPara.master_supply_temp;
}

void app_general_push_master_supply_temp(int16_t in_temp)
{
    s_sysPara.master_supply_temp = in_temp;
}
int16_t app_general_pull_master_living_temp(void)
{
	uint16_t aircod_th14_temp;
    APP_pull_aricod_message(DRIVE_BOARD_TH14_TEMP,&aircod_th14_temp);
	s_sysPara.master_living_temp = aircod_th14_temp;
    return s_sysPara.master_living_temp;
}
void app_general_push_master_living_temp(int16_t in_temp)
{
    s_sysPara.master_living_temp = in_temp;
}
int16_t app_general_pull_master_outdoor_temp(void)
{
    return s_sysPara.master_outdoor_temp;
}
void app_general_push_master_outdoor_temp(int16_t in_temp)
{
    s_sysPara.master_outdoor_temp = in_temp;
}
/*湿度温度co2pm25修正系数  回风 户外 氟盘前 氟盘后 回风 排风*/

int16_t app_general_pull_adjust_outdoor_hum(void)
{
    return StoRunParameter.adjust_outdoor_hum;
}
int16_t app_general_pull_adjust_outdoor_temp(void)
{
    return StoRunParameter.adjust_outdoor_temp;
}
int16_t app_general_pull_adjust_outdoor_co2(void)
{
    return StoRunParameter.adjust_outdoor_co2;
}
int16_t app_general_pull_adjust_outdoor_pm25(void)
{
    return StoRunParameter.adjust_outdoor_pm25;
}
int16_t app_general_pull_adjust_beforfu_hum(void)
{
    return StoRunParameter.adjust_befor_fu_hum;
}
int16_t app_general_pull_adjust_beforfu_temp(void)
{
    return StoRunParameter.adjust_befor_fu_temp;
}
int16_t app_general_pull_adjust_beforfu_co2(void)
{
    return StoRunParameter.adjust_befor_fu_co2;
}
int16_t app_general_pull_adjust_beforfu_pm25(void)
{
    return StoRunParameter.adjust_befor_fu_pm25;
}
int16_t app_general_pull_adjust_afterfu_hum(void)
{
    return StoRunParameter.adjust_after_fu_hum;
}
int16_t app_general_pull_adjust_afterfu_temp(void)
{
    return StoRunParameter.adjust_after_fu_temp;
}
int16_t app_general_pull_adjust_afterfu_co2(void)
{
    return StoRunParameter.adjust_after_fu_co2;
}
int16_t app_general_pull_adjust_afterfu_pm25(void)
{
    return StoRunParameter.adjust_after_fu_pm25;
}

int16_t app_general_pull_adjust_backair_hum(void)
{
    return StoRunParameter.adjust_back_air_hum;
}
int16_t app_general_pull_adjust_backair_temp(void)
{
    return StoRunParameter.adjust_back_air_temp;
}
int16_t app_general_pull_adjust_backair_co2(void)
{
    return StoRunParameter.adjust_back_air_co2;
}
int16_t app_general_pull_adjust_backair_pm25(void)
{
    return StoRunParameter.adjust_back_air_pm25;
}
int16_t app_general_pull_adjust_exhastair_hum(void)
{
    return StoRunParameter.adjust_exhast_air_hum;
}
int16_t app_general_pull_adjust_exhastair_temp(void)
{
    return StoRunParameter.adjust_exhast_air_temp;
}
int16_t app_general_pull_adjust_exhastair_co2(void)
{
    return StoRunParameter.adjust_exhast_air_co2;
}
int16_t app_general_pull_adjust_exhastair_pm25(void)
{
    return StoRunParameter.adjust_exhast_air_pm25;
}
void app_general_push_adjust_outdoor_hum(int16_t in_hum)
{
    StoRunParameter.adjust_outdoor_hum = in_hum;
    app_push_once_save_sto_parameter();
}
void app_general_push_adjust_outdoor_temp(int16_t in_temp)
{
    StoRunParameter.adjust_outdoor_temp = in_temp;
    app_push_once_save_sto_parameter();
}
void app_general_push_adjust_outdoor_co2(int16_t in_co2)
{
    StoRunParameter.adjust_outdoor_co2 = in_co2;
    app_push_once_save_sto_parameter();
}
void app_general_push_adjust_outdoor_pm25(int16_t in_pm25)
{
    StoRunParameter.adjust_outdoor_pm25 = in_pm25;
    app_push_once_save_sto_parameter();
}

void app_general_push_adjust_beforfu_hum(int16_t in_hum)
{
    StoRunParameter.adjust_befor_fu_hum = in_hum;
    app_push_once_save_sto_parameter();
}
void app_general_push_adjust_beforfu_temp(int16_t in_temp)
{
    StoRunParameter.adjust_befor_fu_temp = in_temp;
    app_push_once_save_sto_parameter();
}
void app_general_push_adjust_beforfu_co2(int16_t in_co2)
{
    StoRunParameter.adjust_befor_fu_co2 = in_co2;
    app_push_once_save_sto_parameter();
}
void app_general_push_adjust_beforfu_pm25(int16_t in_pm25)
{
    StoRunParameter.adjust_befor_fu_pm25 = in_pm25;
    app_push_once_save_sto_parameter();
}

void app_general_push_adjust_afterfu_hum(int16_t in_hum)
{
    StoRunParameter.adjust_after_fu_hum = in_hum;
    app_push_once_save_sto_parameter();
}
void app_general_push_adjust_afterfu_temp(int16_t in_temp)
{
    StoRunParameter.adjust_after_fu_temp = in_temp;
	app_push_once_save_sto_parameter();
}
void app_general_push_adjust_afterfu_co2(int16_t in_co2)
{
    StoRunParameter.adjust_after_fu_co2 = in_co2;
	app_push_once_save_sto_parameter();
}
void app_general_push_adjust_afterfu_pm25(int16_t in_pm25)
{
    StoRunParameter.adjust_after_fu_pm25 = in_pm25;
	app_push_once_save_sto_parameter();
}

void app_general_push_adjust_backair_hum(int16_t in_hum)
{
    StoRunParameter.adjust_back_air_hum = in_hum;
	app_push_once_save_sto_parameter();
}
void app_general_push_adjust_backair_temp(int16_t in_temp)
{
    StoRunParameter.adjust_back_air_temp = in_temp;
	app_push_once_save_sto_parameter();
}
void app_general_push_adjust_backair_co2(int16_t in_co2)
{
    StoRunParameter.adjust_back_air_co2 = in_co2;
	app_push_once_save_sto_parameter();
}
void app_general_push_adjust_backair_pm25(int16_t in_pm25)
{
    StoRunParameter.adjust_back_air_pm25 = in_pm25;
	app_push_once_save_sto_parameter();
}

void app_general_push_adjust_exhastair_hum(int16_t in_hum)
{
    StoRunParameter.adjust_exhast_air_hum = in_hum;
	app_push_once_save_sto_parameter();
}
void app_general_push_adjust_exhastair_temp(int16_t in_temp)
{
    StoRunParameter.adjust_exhast_air_temp = in_temp;
	app_push_once_save_sto_parameter();
}
void app_general_push_adjust_exhastair_co2(int16_t in_co2)
{
    StoRunParameter.adjust_exhast_air_co2 = in_co2;
	app_push_once_save_sto_parameter();
}
void app_general_push_adjust_exhastair_pm25(int16_t in_pm25)
{
    StoRunParameter.adjust_exhast_air_pm25 = in_pm25;
	app_push_once_save_sto_parameter();
}

/*环控能需预冷预热阀*/
bool app_general_pull_anergy_need(void)
{
    return s_sysPara.energyNeed;
}
void app_general_push_anergy_need(bool in_status)
{
    if(s_sysPara.energyNeed != in_status)
    {
        s_sysPara.energyNeed = in_status;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
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
/*绑定的阀门列表 (风盘)*/

/*绑定的阀门列表 (辐射)*/

/*阀门绑定故障*/

/*混水制冷/制热设定温度 */
void app_general_push_set_mixwater_cold_temp(int16_t in_set_temp)
{
    if(s_sysPara.mixColdSetTemp != in_set_temp)
    {
        s_sysPara.mixColdSetTemp = in_set_temp;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_MIXWATER_SET_CLOD_TEMP);
    }
}

void app_general_push_set_mixwater_heat_temp(int16_t in_set_temp)
{
    if(s_sysPara.mixHeatSetTemp != in_set_temp)
    {
        s_sysPara.mixHeatSetTemp = in_set_temp; 
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_MIXWATER_SET_HEAT_TEMP);          
    }
}

int16_t app_general_pull_set_mixwater_cold_temp(void)
{
    return s_sysPara.mixColdSetTemp;
}

int16_t app_general_pull_set_mixwater_heat_temp(void)
{
    return s_sysPara.mixHeatSetTemp;
}

/*输配进水温度*/
int16_t app_general_pull_in_water_measure_temp(void)
{
    return s_sysPara.inWaterMeasureTemp;
}

//th7
int16_t app_general_pull_th7_measure_temp(void)
{
	uint16_t pull_temp;
	APP_pull_aricod_message(45,&pull_temp);//0x0045
	s_sysPara.th7Temp = (int16_t)pull_temp;
    return s_sysPara.th7Temp;
}

void app_general_push_in_water_measure_temp(int16_t in_temp)
{
    s_sysPara.inWaterMeasureTemp = in_temp;
}
/*输配回水温度*/
int16_t app_general_pull_back_water_measure_temp(void)
{
    return s_sysPara.backWaterMeasureTemp;
}
void app_general_push_back_water_measure_temp(int16_t in_temp)
{
    s_sysPara.backWaterMeasureTemp = in_temp;
}
/*输配混水温度*/
int16_t app_general_pull_mix_water_measure_temp(void)
{
    return s_sysPara.measure_mixTemp;
}
void app_general_push_mix_water_measure_temp(int16_t in_temp)
{
    s_sysPara.measure_mixTemp = in_temp;
}

/*输配水泵状态*/
bool app_general_pull_pump_output(void)
{
    return s_sysPara.output_pump;
}
void app_general_push_pump_output(bool in_status)
{
    s_sysPara.output_pump = in_status;
}
/*输配三通阀门输出状态*/
bool app_general_pull_three_vavle_output(void)
{
    return s_sysPara.output_threeWayValve;
}
void app_general_push_three_vavle_output(bool in_status)
{
    s_sysPara.output_threeWayValve = in_status;
}

/*输配防冻输出状态*/
bool app_general_pull_low_protect_output(void)
{
    return s_sysPara.output_lowProtect;
}
void app_general_push_low_protect_output(bool in_status)
{
    s_sysPara.output_lowProtect = in_status;
}

/*输配混水AI目标温度 */
int16_t app_general_pull_ai_dest_temp(void)
{
    return s_sysPara.destTemp;
}
void app_general_push_ai_dest_temp(int16_t in_temp)
{
    s_sysPara.destTemp = in_temp;
}
/*输配混水AI使能*/
bool app_general_pull_ai_enable_status(void)
{
    return s_sysPara.aiEnable;
}
void app_general_push_ai_enable_status(bool in_status)
{
    s_sysPara.aiEnable = in_status;
}
/*输配防冻保护*/
uint8_t app_general_pull_mix_freeze_protect(void)
{
    return s_sysPara.lowTempProtectConfig;
}
void app_general_push_mix_freeze_protect(uint8_t  in_set_temp)
{
    if((in_set_temp >= 50) && (in_set_temp <= 100)&&(in_set_temp%5==0))
    {
        if(in_set_temp != s_sysPara.lowTempProtectConfig)
        {         
            s_sysPara.lowTempProtectConfig = in_set_temp;
            app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_MIXWATER_LOW_TEMP_PROTECT);
        }
    }  
}

void app_general_push_coolbackwater_set_temp(int16_t  in_set_temp)
{
	if(StoRunParameter.cool_backwater_settemp != in_set_temp)
	{
		StoRunParameter.cool_backwater_settemp = in_set_temp;  
		app_push_once_save_sto_parameter();
		app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_COLD_WARM_BACK_WATER);		  //需确认
	} 
	APP_push_aricod_message(DRIVE_BOARD_COOL_BACKWATER_SETTEMP,StoRunParameter.cool_backwater_settemp);		 
}

void app_general_push_hotbackwater_set_temp(int16_t  in_set_temp)
{
	if(StoRunParameter.hot_backwater_settemp != in_set_temp)
	{
		StoRunParameter.hot_backwater_settemp = in_set_temp;  
		app_push_once_save_sto_parameter();
		app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_COLD_WARM_BACK_WATER);//
	} 
	APP_push_aricod_message(DRIVE_BOARD_HOT_BACKWATER_SETTEMP,StoRunParameter.hot_backwater_settemp);		 
}

//新风效率计算
void app_general_push_freshaireffciency_set_temp(int16_t oa,int16_t sa,int16_t ra)
{
	int16_t effciency = 0;
    
	if(oa != ra)
	{
		effciency = (oa - sa)*100/(oa - ra);
		if(effciency > 100)
		{
             effciency = 100;
		}
        else if(effciency < 0)
        {
            effciency = (0-effciency);
        }
	}
	else
	{
        effciency = 100;
	}
	StoRunParameter.freshair_effciency = effciency;
}

int16_t app_general_pull_freshaireffciency_set_temp(void)
{
    return StoRunParameter.freshair_effciency;
}
//读取风阀设置
void app_general_push_wind_value(bool reg_dat)
{
	if(reg_dat <= 1)
	{
		StoRunParameter.wind_value = reg_dat;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
		app_push_once_save_sto_parameter();
	}
}

bool app_general_pull_wind_value(void)
{
	return StoRunParameter.wind_value;
}

//读取热水使能
int16_t app_general_pull_hotwater_enable(void)
{
	return StoRunParameter.hotwater_enable;
}
void app_general_push_hotwater_enable(uint16_t reg_dat)
{
	if(reg_dat <= 1)
	{
		StoRunParameter.hotwater_enable = reg_dat;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
		app_push_once_save_sto_parameter();
	}
}
//485地址 波特率 校验位
void app_general_push_adress485(uint8_t in_address)
{
    if((in_address >=1) && (in_address < 32))
    {
        StoRunParameter.deviceAddress = in_address;
        app_modbus_remote_reCfg_parmeter(StoRunParameter.deviceAddress,StoRunParameter.baudrateValue,StoRunParameter.evenOddCheck);
        app_push_once_save_sto_parameter();
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
    app_push_once_save_sto_parameter();     
}

void app_general_push_checkbit(uint8_t in_check)
{
	if(in_check <= 2)
	{
		StoRunParameter.evenOddCheck = in_check;
		app_push_once_save_sto_parameter();
        app_modbus_remote_reCfg_parmeter(StoRunParameter.deviceAddress,StoRunParameter.baudrateValue,StoRunParameter.evenOddCheck); 
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


//制冷回风设置温度
int16_t app_general_pull_coolbackwind_set_temp(void)
{
	return StoRunParameter.coldTemp_set;
}


//制冷出水设置温度
int16_t app_general_pull_cooloutwater_set_temp(void)
{
    return StoRunParameter.set_cold_water_temp;//cool_outwater_settemp;
}

//制冷回水设置温度
int16_t app_general_pull_coolbackwater_set_temp(void)
{
    return StoRunParameter.cool_backwater_settemp;
}


int16_t app_general_pull_hotbackwater_set_temp(void)
{
    return StoRunParameter.hot_backwater_settemp;
}


bool app_pull_low_protect_reguest(void)
{//产生防冻请求
    return s_sysPara.lowProtectRequest;
}
void app_push_low_protect_reguest(bool in_status)
{//产生防冻请求
    s_sysPara.lowProtectRequest = in_status;
}

/*滤芯更换周期*/
void app_general_push_filter_time(int16_t in_time)
{
	if(StoRunParameter.filter_time != in_time)
	{
		StoRunParameter.filter_time = in_time;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
		app_push_once_save_sto_parameter();
	}
}
int16_t app_general_pull_filter_time(void)
{
    return StoRunParameter.filter_time;
}
/*滤芯使用时间*/
void app_general_push_filter_usetime(int16_t in_time)
{
	if(0x00 == in_time)
	{
		StoRunParameter.filter_usetime = 0;
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
		app_push_once_save_sto_parameter();
	}
}
int16_t app_general_pull_filter_usetime(void)
{
    return StoRunParameter.filter_usetime;
}

/*滤网更换提示*/
bool app_general_pull_full_dust(void)
{
    if(StoRunParameter.filter_time > StoRunParameter.filter_usetime)
    {
        return false;
    }
    return true;
}
/*调试使能*/
bool app_general_pull_debug_enable(void)
{
    return StoRunParameter.debug_enable;
}
void app_general_push_debug_enable(bool in_status)
{
    StoRunParameter.debug_enable = in_status;
    app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    app_push_once_save_sto_parameter();
}
/*最高露点温度*/
int16_t app_general_pull_max_lew_temp(void)
{
    return s_sysPara.max_lew_temp;
}
void app_general_push_max_lew_temp(int16_t in_temp)
{
    s_sysPara.max_lew_temp = in_temp;
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
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
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
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUT_STATUS);
    }   
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//过滤网运行时间检测
#define STORAGE_TIME      24*60  //24 Hour Save RunTime
#define OneDayMinutes     (1440-1)
#define ONEMINUTE         60
#define FILTER_FULL       0x01
//-----------------------------------------------------------------------------
void FillScreenUseTimeTask(void)
{
    static uint16_t filter_used_minute;

    #ifdef NDEBUG
    macro_createTimer(storage_delay,timerType_minute,0);
    #else
    macro_createTimer(storage_delay,timerType_second,0); //调试模式 s运行
    #endif
    pbc_timerClockRun_task(&storage_delay); 
    if(pbc_pull_timerIsCompleted(&storage_delay))
    {
        while(filter_used_minute>OneDayMinutes)
        {
            StoRunParameter.filter_usetime++;
            filter_used_minute = filter_used_minute-OneDayMinutes;
            app_push_once_save_sto_parameter();
        }
        pbc_reload_timerClock(&storage_delay,STORAGE_TIME);        
    }
    
    #ifdef NDEBUG
    macro_createTimer(oneminute_delay,timerType_second,0);
    #else
    macro_createTimer(oneminute_delay,timerType_second,0);//调试模式 ms运行, 1.4 minute == one day
    #endif
    pbc_timerClockRun_task(&oneminute_delay); 
    if(pbc_pull_timerIsCompleted(&oneminute_delay))
    {
        pbc_reload_timerClock(&oneminute_delay,ONEMINUTE);
        if(app_general_pull_power_status())
        {
            filter_used_minute++;
        }
    }
    if(app_general_pull_full_dust())
    {
        s_sysPara.system_status_word |= FILTER_FULL;
    }
    else
    {
        s_sysPara.system_status_word &= (~FILTER_FULL);
    }
}
/*新风风机输出*/
uint8_t   aircod_ec_newwind_s = 0;//新风风机
uint8_t app_general_pull_ecNewWind_output(void)
{
	return aircod_ec_newwind_s;
}
/*回风风机输出*/
uint8_t  aircod_ec_backwind_s = 0;//回风风机
uint8_t app_general_pull_ecBackWind_output(void)
{
	return aircod_ec_backwind_s;
}


/*综合传感器故障*/
bool pull_integrated_sensor_error(void)
{
	if(protection_cpor_bits & rs1001_offline)
	{
		return true;
	}
	return false;
}
/*除湿输出*/
static bool air_humidity_s_output = false;
bool  app_general_pull_humidity_output(void)
{
	return air_humidity_s_output;
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
/*采暖输出*/
static bool air_warm_s_output = false;
bool  app_general_pull_warm_output(void)
{
	return air_warm_s_output;
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

uint8_t app_pull_newAir_pwm_value(NewAirLevelSet_Def in_fanSpeed)
{
    uint8_t pwmValue = 0;
    switch (in_fanSpeed)
    {
        case LowFanSet:
        {
            pwmValue = StoRunParameter.newAirLowPwm;
            break;
        }   
        case MiddleFanSet:
        {
            pwmValue = StoRunParameter.newAirMidPwm;
            break;
        }   
        case HighFanSet:
        {
            pwmValue = StoRunParameter.newAirHighPwm;
            break;
        }   
        default:
        {
            pwmValue = StoRunParameter.newAirLowPwm;
            break;
        }       
    }
    return pwmValue;
}
uint8_t app_pull_backAir_pwm_value(NewAirLevelSet_Def in_fanSpeed)
{
    uint8_t pwmValue = 0;
    switch (in_fanSpeed)
    {
        case LowFanSet:
        {
            pwmValue = StoRunParameter.backAirLowPwm;
            break;
        }   
        case MiddleFanSet:
        {
            pwmValue = StoRunParameter.backAirMidPwm;
            break;
        }   
        case HighFanSet:
        {
            pwmValue = StoRunParameter.backAirHighPwm;
            break;
        }   
        default:
        {
            pwmValue = StoRunParameter.backAirLowPwm;
            break;
        }       
    }
    return pwmValue;
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
        humidityFlag = app_dehumidification_logic((int16_t)Pull_RSS1001H_Humidity(3),StoRunParameter.humidity_set,StoRunParameter.humidity_DeadZone);
    }
    return humidityFlag;
}

bool app_pull_aircod_warm_output(void)
{
    bool warmFlag = false;
    if(pull_integrated_sensor_error())
    {//传感器错误
        warmFlag = false;        
    }
    else
    {
        warmFlag = app_temp_logic((int16_t)Pull_RSS1001H_Temperature(3),StoRunParameter.hotTemp_set,StoRunParameter.temp_DeadZone);
    }
    return warmFlag;
}

void app_pull_ec_fan_speed(void)
{  
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&measure_delay);
    if(pbc_pull_timerIsCompleted(&measure_delay))
    {
        pbc_reload_timerClock(&measure_delay,10000);
        mde_tachFan_Task();   
        s_sysPara.new_air_speed = mde_pull_airTach(0);
        s_sysPara.back_air_speed = mde_pull_airTach(1);
        if(Pull_RSS1001H_OnlineState(SENSOR_OUTDOOR))
        {
            app_general_clear_ae_error_word(SYS_ERROR_OUTDOOR_AIR_NTC);
        }
        else
        {
            app_general_push_ae_error_word(SYS_ERROR_OUTDOOR_AIR_NTC);
        }
        if(Pull_RSS1001H_OnlineState(SENSOR_BEFOREFU))
        {
            app_general_clear_ae_error_word(SYS_ERROR_BEFORE_FU_AIR_NTC);
        }
        else
        {
            app_general_push_ae_error_word(SYS_ERROR_BEFORE_FU_AIR_NTC);
        }
        if(Pull_RSS1001H_OnlineState(SENSOR_AFTERFU))
        {
            app_general_clear_ae_error_word(SYS_ERROR_AFTER_FU_AIR_NTC);
        }
        else
        {
            app_general_push_ae_error_word(SYS_ERROR_AFTER_FU_AIR_NTC);
        }
        if(Pull_RSS1001H_OnlineState(SENSOR_BACKAIR))
        {
            app_general_clear_ae_error_word(SYS_ERROR_BACK_AIR_NTC);
        }
        else
        {
            app_general_push_ae_error_word(SYS_ERROR_BACK_AIR_NTC);
        }
        if(Pull_RSS1001H_OnlineState(SENSOR_EXHASTAIR))
        {
            app_general_clear_ae_error_word(SYS_ERROR_EXHAST_AIR_NTC);
        }
        else
        {
            app_general_push_ae_error_word(SYS_ERROR_EXHAST_AIR_NTC);
        }
        if(StoRunParameter.systemPower)
        {//开机
            if(mde_pull_airTach(0) == 0)
            {//无转速
                app_general_push_ae_error_word(SYS_ERROR_IN_AIR_FAN);
            }
            else
            {
                app_general_clear_ae_error_word(SYS_ERROR_IN_AIR_FAN);
            }
            if(mde_pull_airTach(1) == 0)
            {
                app_general_push_ae_error_word(SYS_ERROR_BACK_AIR_FAN);
            }
            else
            {
                app_general_clear_ae_error_word(SYS_ERROR_BACK_AIR_FAN);
            }
        } 
        else
        {//关机
            if(mde_pull_airTach(0))
            {
                app_general_push_ae_error_word(SYS_ERROR_IN_AIR_FAN);
            }
            else
            {
                app_general_clear_ae_error_word(SYS_ERROR_IN_AIR_FAN);
            }
            if(mde_pull_airTach(1))
            {
                app_general_push_ae_error_word(SYS_ERROR_BACK_AIR_FAN);
            }
            else
            {
                app_general_clear_ae_error_word(SYS_ERROR_BACK_AIR_FAN);
            }
        }
        
    }
}
void app_push_aircod_message(void)
{  
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&measure_delay);
    if(pbc_pull_timerIsCompleted(&measure_delay))
    {
        pbc_reload_timerClock(&measure_delay,10000);
        
       // APP_push_aricod_message(DRIVE_BOARD_INDOOR_MESSAGE,Pull_RSS1001H_Temperature(SENSOR_AFTERFU));
      //  APP_push_aricod_message((DRIVE_BOARD_INDOOR_MESSAGE+1),Pull_RSS1001H_Humidity(SENSOR_AFTERFU));
      //  APP_push_aricod_message((DRIVE_BOARD_INDOOR_MESSAGE+2),Pull_RSS1001H_Temperature(SENSOR_BEFOREFU));
      //  APP_push_aricod_message((DRIVE_BOARD_INDOOR_MESSAGE+3),Pull_RSS1001H_Humidity(SENSOR_BEFOREFU));
      //  APP_push_aricod_message(DRIVE_BOARD_FAN_FEEDBACK_SPEED,mde_pull_airTach(0));
    }
}

static uint16_t protection_cpor_bits;//
#define drain_water_error                     0x01        //排水故障
static uint16_t restart_control_bits;
#define restart_drain_water_error             0x01

void app_general_aircod_comp_error(void)
{
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&measure_delay);
    if(pbc_pull_timerIsCompleted(&measure_delay))
    {               
        pbc_reload_timerClock(&measure_delay,1000);
        uint8_t i = 0;
        uint16_t value = 0;
        bool errorFlag = false;
        for(i =0; i < 12;i++)
        {
            APP_pull_aricod_message((49+i),&value);
            if(value)
            {
                errorFlag = true;
            }
        }
        APP_pull_aricod_message(5051,&value);
        if(value)
        {
            errorFlag = true;
        }
        if(errorFlag)
        {
            app_general_push_ae_error_word(SYS_ERROR_AIRCOD);
        }
        else
        {
             app_general_clear_ae_error_word(SYS_ERROR_AIRCOD);
        }        
    }
}

void app_timing_push_temp_hum(void)
{  
    macro_createTimer(measure_delay,timerType_minute,0);
    pbc_timerClockRun_task(&measure_delay);
    if(pbc_pull_timerIsCompleted(&measure_delay))
    {
        pbc_reload_timerClock(&measure_delay,3);
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_OUTDOOR_WEATHER);
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BEFORE_FU_WEATHER);
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_AFTER_FU_WEATHER);
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_BACK_AIR_WEATHER);
        app_link_syn_push_outside_updata_word(SYSTEM_MASTER,OCCUPY_SYSTEM_LIS_EXHAST_AIR_WEATHER);
    }
}

bool   new_liftpump_s = false;
#define  ENGER_NEED_RADIATION_BIT              0X01//辐射位
#define  ENGER_NEED_FAN_BIT                    0X02//风盘位
#define  ENGER_NEED_CLOD_BIT                   0X04//制冷位
#define  ENGER_NEED_LEW_TEMP_PROTECT_BIT       0X08//露点保护位
#define  MIX_VAVLE_ERROR_BIT                   0X10//混水阀故障
int16_t app_general_pull_auto_set_hum(void)
{
    if(Pull_RSS1001H_Humidity(SENSOR_BACKAIR) > 20)
    {
        if((Pull_RSS1001H_Humidity(SENSOR_BACKAIR) - 20) < 40)
        {
            return 40;
        }
        else if((Pull_RSS1001H_Humidity(SENSOR_BACKAIR) - 20) > 60)
        {
            return 60;
        }
        else
        {
            return (Pull_RSS1001H_Humidity(SENSOR_BACKAIR) - 20);
        }
        
    }
    else
    {
        return 40;
    }
    
}

void reset_daran_water_error(uint16_t in_error)
{
    if(in_error & drain_water_error)
    {
        restart_control_bits |= restart_drain_water_error;
        StoRunParameter.drainWaterError &= ~drain_water_error;
        app_general_clear_ae_error_word(SYS_ERROR_EXHAST_WATER);
        app_push_once_save_sto_parameter(); 
    }     
}

#define  RESET_FULL_DUST   0x8000
/*系统故障复位*/
void app_general_push_reset_word(uint16_t in_error)
{
    reset_daran_water_error(in_error);
    if(in_error & 0x8000)
    {
        app_general_push_filter_usetime(0);
    }
    if(in_error & 0x4000)
    {//软复位
        while(1)
        {
        }
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
        for(i = 0; i < MAX_DATA_POINT_LEN;i++)
        {
            if(s_sysPara.dpStamp[i] > pbc_timeStamp_get_stamp())
            {
                s_sysPara.dpStamp[i] = pbc_timeStamp_get_stamp();
            }
        }              
    }
}

void app_general_aircod_run_task(void)
{
	bool powerOff_now = false;
    uint16_t fanControlEnable = 0;//风机控制使能
    uint16_t airFanSpeed = 0;//室外机控制风机转速
    static uint16_t sendairfanspeed = 0;
    app_pull_ec_fan_speed();
    app_timing_push_temp_hum();//定时发送综合传感器数据
    FillScreenUseTimeTask();//滤芯使用时间
//-----------------------------------------------------------------------------
    if(StoRunParameter.systemPower)
    {//开机
        powerOff_now=false;
    }
    else
    {
        powerOff_now=true;
    }    
//-----------------------------------------------------------------------------
    switch(StoRunParameter.control_method)
    {
        case METHOD_BASIC:
        {//基础策略
            if(powerOff_now)
            {//关机        
                
                if(app_general_pull_low_protect_output())
                {//有防冻请求
                    APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,1);//空调开机
                    APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_AUTO_HEAT);//空调制热模式
                    s_sysPara.energyNeed = true;
                    aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                    aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                    
                }
                else
                {
                    APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,0);//空调关机
                    aircod_ec_newwind_s = 0;//新风风机
                    aircod_ec_backwind_s = 0;//回风风机
                    s_sysPara.energyNeed = false;
                }           
            }
            else
            { //开机   
                APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,1);//空调开机      
                APP_push_aricod_message(DRIVE_BOARD_COOL_BACKWATER_SETTEMP,app_general_pull_set_cold_backwater_temp());//制冷回水设置温度   
                APP_push_aricod_message(DRIVE_BOARD_HOT_BACKWATER_SETTEMP,app_general_pull_set_heat_backwater_temp());//制热回水设置温度 
                APP_push_aricod_message(DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP,app_general_pull_set_living_water_temp());//设定生活热水温度       
            //  APP_push_aricod_message(DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP,400);//设定生活热水温度  
                macro_createTimer(timer_temp_updata,timerType_second,0);  //温度更新
                pbc_timerClockRun_task(&timer_temp_updata);
                if(pbc_pull_timerIsCompleted(&timer_temp_updata))
                {
                    pbc_reload_timerClock(&timer_temp_updata,5);
                    APP_push_aricod_message(DRIVE_BOARD_INWIND_HUMIDITY,Pull_RSS1001H_Humidity(SENSOR_OUTDOOR)*10);
                    APP_push_aricod_message(DRIVE_BOARD_INWIND_TEMP,Pull_RSS1001H_Temperature(SENSOR_OUTDOOR));
                    APP_push_aricod_message(DRIVE_BOARD_BACKWIND_TEMP,Pull_RSS1001H_Temperature(SENSOR_BACKAIR));
                    APP_push_aricod_message(DRIVE_BOARD_BACKWIND_HUMIDITY,Pull_RSS1001H_Humidity(SENSOR_BACKAIR)*10);
                    app_general_push_freshaireffciency_set_temp(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR), \
                        Pull_RSS1001H_Temperature(SENSOR_AFTERFU), \
                        Pull_RSS1001H_Temperature(SENSOR_BACKAIR));//5s计算一次新风效率
                }
                sendairfanspeed = (95 + ((StoRunParameter.NewAirLevelSet-1) * 5));
                APP_push_aricod_message(DRIVE_BOARD_FAN_FEEDBACK_SPEED,sendairfanspeed);
                APP_push_aricod_message(DRIVE_BOARD_HOTWATER_ENABLE,app_general_pull_hotwater_enable());
                switch(StoRunParameter.airRunmode)
                {					
                    case AIR_MODE_FAN://新风模式
                    {               
                        s_sysPara.energyNeed = false;
                        aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_FAN);//AIR_MODE_LIVING_WATER);//空调新风模式
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);              
                        break;
                    }
                    case AIR_MODE_AUTO_COOL:
                    case AIR_MODE_COOL://制冷模式
                    {   
                        if(StoRunParameter.debug_enable)
                        {
                           // s_sysPara.energyNeed = true; 
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,StoRunParameter.airRunmode);//模式
                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,StoRunParameter.coldTemp_set);//氟机
                            APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,StoRunParameter.set_cold_water_temp);//水机
                            APP_push_aricod_message(DRIVE_BOARD_WATER_MACHINE_POWER,app_general_pull_water_machine_status());//水机开关机
                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,StoRunParameter.humidity_set*10);//设定相对湿度,固定50%
                            
                        }
                        else
                        {
                            s_sysPara.energyNeed = true; 
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_AUTO_COOL);//空调夏季自动模式
                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,app_general_pull_cold_wind_max_set_temp());//氟机保证不制冷  
                        //  APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,180);//氟机保证不制冷 
                            if((s_sysPara.system_error_word & SYS_ERROR_MIX_WATER) ||  (s_sysPara.system_error_word & SYS_ERROR_BEFORE_FU_AIR_NTC) ||
                            (s_sysPara.system_error_word & SYS_ERROR_BACK_AIR_NTC) || (app_pull_system_energy_need() & MIX_VAVLE_ERROR_BIT)) 
                            {//故障
                                APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_cold_no_need_set_temp());//停止水机运行
                            }   
                            else
                            {
                                if(((app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT) == 0) && 
                                ((app_pull_system_energy_need() & ENGER_NEED_FAN_BIT) == 0))
                                {//所有末端无能需
                                    
                                    APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_cold_no_need_set_temp());//停止水机运行
                                    APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_config_hum_set()*10);//设定相对湿度,固定50%
                                }
                                else
                                {
                                    if(app_pull_system_energy_need() & ENGER_NEED_FAN_BIT)
                                    {//风盘能需
                                        APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_cold_fan_need_set_temp());//制冷出水设置温度
                                    }
                                    else
                                    {
                                        APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_cold_warm_need_set_temp());//制冷出水设置温度
                                    }
                                    if(app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT)
                                    {//有辐射能需
                                        if(app_pull_system_energy_need() & ENGER_NEED_CLOD_BIT)
                                        {//除湿状态
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_auto_set_hum()*10);//自动计算相对湿度
                                        }
                                        else
                                        {
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_config_hum_set()*10);//设定相对湿度,固定50%
                                        }
                                        
                                    }
                                    else
                                    {//无辐射能需
                                        if(app_pull_system_energy_need() & ENGER_NEED_LEW_TEMP_PROTECT_BIT)
                                        {//露点保护
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_auto_set_hum()*10);//自动计算相对湿度
                                        }
                                        else
                                        {
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_config_hum_set()*10);//设定相对湿度,固定50%
                                        }           
                                    }                   
                                }           
                            }                    
                        }                                                   
                        APP_pull_aricod_message(DRIVE_BOARD_FAN_CONTROL_ENABLE,&fanControlEnable);
                        if(fanControlEnable)
                        {//启用
                            APP_pull_aricod_message(DRIVE_BOARD_FAN_SPEED,&airFanSpeed);//获取风机转速倍数
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }
                        else
                        {//禁用
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }        
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);
                        break;
                    }
                    case AIR_MODE_AUTO_HEAT:
                    case AIR_MODE_HEAT://制热模式
                    {  
                        if(StoRunParameter.debug_enable)
                        {
                           // s_sysPara.energyNeed = true; 
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,StoRunParameter.airRunmode);//模式
                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,StoRunParameter.hotTemp_set);//氟机
                            APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,StoRunParameter.set_heat_water_temp);//水机
                            APP_push_aricod_message(DRIVE_BOARD_WATER_MACHINE_POWER,app_general_pull_water_machine_status());//水机开关机
                        }
                        else
                        {
                            s_sysPara.energyNeed = true;
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_AUTO_HEAT);//空调自动制热模式  
                            if((s_sysPara.system_error_word & SYS_ERROR_MIX_WATER) ||  (s_sysPara.system_error_word & SYS_ERROR_BEFORE_FU_AIR_NTC) ||
                            (s_sysPara.system_error_word & SYS_ERROR_BACK_AIR_NTC) ) 
                            {//故障
                                APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_heat_no_need_set_temp());//停止水机运行
                                APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_aircod_heat_stop_temp());//制热回风设定温度
                            }   
                            else
                            {
                                if(((app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT) == 0) && 
                                ((app_pull_system_energy_need() & ENGER_NEED_FAN_BIT) == 0))
                                {//所有末端无能需
                                     
                                    APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_heat_no_need_set_temp());//停止水机运行
                                }  
                                else
                                {
                                    if(app_pull_system_energy_need() & ENGER_NEED_FAN_BIT)
                                    {//风盘能需
                                        APP_push_aricod_message(DRIVE_BOARD_HOT_OUTWATER_SETTEMP,app_general_pull_heat_fan_need_set_temp());//制热出水设置温度
                                    }
                                    else
                                    {
                                        APP_push_aricod_message(DRIVE_BOARD_HOT_OUTWATER_SETTEMP,app_general_pull_heat_warm_need_set_temp());//制热出水设置温度
                                    }
                                    if((Pull_RSS1001H_Temperature(SENSOR_BACKAIR) - Pull_RSS1001H_Temperature(SENSOR_BEFOREFU)) >= 30)
                                    {//氟机制热模式
                                        APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_heat_wind_max_set_temp());//制热回风设定温度
                                    }
                                    else
                                    {
                                        if(Pull_RSS1001H_Temperature(SENSOR_BACKAIR) >= (app_general_pull_config_back_wind_set_temp()+20))
                                        {//氟机停机
                                            APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_heat_wind_min_set_temp());//制热回风设定温度
                                        }
                                        else if(Pull_RSS1001H_Temperature(SENSOR_BACKAIR) < app_general_pull_config_back_wind_set_temp())
                                        {//氟机制热
                                            APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_heat_wind_max_set_temp());//制热回风设定温度
                                        }
                                    }
                                }   
                            }              
                        }              
                        APP_pull_aricod_message(DRIVE_BOARD_FAN_CONTROL_ENABLE,&fanControlEnable);
                        if(fanControlEnable)
                        {//启用
                            APP_pull_aricod_message(DRIVE_BOARD_FAN_SPEED,&airFanSpeed);//获取风机转速倍数  
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);              
                        }
                        else
                        {//禁用
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);
                        break;
                    }
                    case AIR_MODE_HUMIDITY://除湿模式
                    {	 
                        s_sysPara.energyNeed = true;                   
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,1);
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_HUMIDITY);//空调除湿模式                        
                        APP_pull_aricod_message(DRIVE_BOARD_FAN_CONTROL_ENABLE,&fanControlEnable);	
                        APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_aircod_humidity()*10);//设定相对湿度			
                        if(fanControlEnable)
                        {//启用
                            APP_pull_aricod_message(DRIVE_BOARD_FAN_SPEED,&airFanSpeed);//获取风机转速倍数
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        }
                        else
                        {//禁用
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }    
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,1);
                        break;
                    }
                    case AIR_MODE_WATER://热水模式
                    {
                        s_sysPara.energyNeed = false;
                        aircod_ec_newwind_s = 0;
                        aircod_ec_backwind_s = 0;
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_FAN);//空调生活热水模式
                        break;
                    }
                    default:
                    {//新风模式                            
                        s_sysPara.energyNeed = false;
                        aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_FAN);//空调生活热水模式
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);
                        break;
                    }
                }      
            }
            break;
        }
        case METHOD_ONE:
        {//策略一
            if(powerOff_now)
            {//关机        
                
                if(app_general_pull_low_protect_output())
                {//有防冻请求
                    APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,1);//空调开机
                    APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_AUTO_HEAT);//空调制热模式
                    s_sysPara.energyNeed = true;
                    aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                    aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                    
                }
                else
                {
                    APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,0);//空调关机
                    aircod_ec_newwind_s = 0;//新风风机
                    aircod_ec_backwind_s = 0;//回风风机
                    s_sysPara.energyNeed = false;
                }           
            }
            else
            { //开机   
                APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,1);//空调开机      
                APP_push_aricod_message(DRIVE_BOARD_COOL_BACKWATER_SETTEMP,app_general_pull_set_cold_backwater_temp());//制冷回水设置温度   
                APP_push_aricod_message(DRIVE_BOARD_HOT_BACKWATER_SETTEMP,app_general_pull_set_heat_backwater_temp());//制热回水设置温度 
                APP_push_aricod_message(DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP,app_general_pull_set_living_water_temp());//设定生活热水温度       
            //  APP_push_aricod_message(DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP,400);//设定生活热水温度  
                macro_createTimer(timer_temp_updata,timerType_second,0);  //温度更新
                pbc_timerClockRun_task(&timer_temp_updata);
                if(pbc_pull_timerIsCompleted(&timer_temp_updata))
                {
                    pbc_reload_timerClock(&timer_temp_updata,5);
                    APP_push_aricod_message(DRIVE_BOARD_INWIND_HUMIDITY,Pull_RSS1001H_Humidity(SENSOR_OUTDOOR)*10);
                    APP_push_aricod_message(DRIVE_BOARD_INWIND_TEMP,Pull_RSS1001H_Temperature(SENSOR_OUTDOOR));
                    APP_push_aricod_message(DRIVE_BOARD_BACKWIND_TEMP,Pull_RSS1001H_Temperature(SENSOR_BACKAIR));
                    APP_push_aricod_message(DRIVE_BOARD_BACKWIND_HUMIDITY,Pull_RSS1001H_Humidity(SENSOR_BACKAIR)*10);
                    app_general_push_freshaireffciency_set_temp(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR), \
                        Pull_RSS1001H_Temperature(SENSOR_AFTERFU), \
                        Pull_RSS1001H_Temperature(SENSOR_BACKAIR));//5s计算一次新风效率
                }
                sendairfanspeed = (95 + ((StoRunParameter.NewAirLevelSet-1) * 5));
                APP_push_aricod_message(DRIVE_BOARD_FAN_FEEDBACK_SPEED,sendairfanspeed);
                APP_push_aricod_message(DRIVE_BOARD_HOTWATER_ENABLE,app_general_pull_hotwater_enable());
                switch(StoRunParameter.airRunmode)
                {					
                    case AIR_MODE_FAN://新风模式
                    {               
                        s_sysPara.energyNeed = false;
                        aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_FAN);//AIR_MODE_LIVING_WATER);//空调新风模式
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);              
                        break;
                    }
                    case AIR_MODE_AUTO_COOL:
                    case AIR_MODE_COOL://制冷模式
                    {   
                        if(StoRunParameter.debug_enable)
                        {
                           // s_sysPara.energyNeed = true; 
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,StoRunParameter.airRunmode);//模式
                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,StoRunParameter.coldTemp_set);//氟机
                            APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,StoRunParameter.set_cold_water_temp);//水机
                            APP_push_aricod_message(DRIVE_BOARD_WATER_MACHINE_POWER,app_general_pull_water_machine_status());//水机开关机
                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,StoRunParameter.humidity_set*10);//设定相对湿度,固定50%
                        }
                        else
                        {
                            #define INDOOR_TEMP                       240
                            #define SET_COLD_WIND_TEMP_INDOOR_LOW     350
                            #define SET_HUM_INDOOR_LOW                500
                            #define SET_COLD_WATER_TEMP_INDOOR        350
                            #define SET_COLD_WIND_TEMP_INDOOR_HIGH    240
                            #define SET_HUM_INDOOR_HIGH               550
                            #define DELAY_12_HOUR                     720
                            #define DELAY_4_HOUR                      14400
                            #define DELAY_1000MS                      1000
                            macro_createTimer(measure_delay,timerType_millisecond,0);
                            macro_createTimer(status_delay,timerType_minute,0);
                            pbc_timerClockRun_task(&measure_delay);//4小时强制退出驻留
                            pbc_timerClockRun_task(&status_delay);//状态驻留12小时
                            s_sysPara.energyNeed = true; 
                            static uint16_t second_count = 0;
                            typedef enum
                            {
                                STATUS_INIT      = 0x00,  
                                STATUS_ONE       = 0x01,  
                                STATUS_TWO       = 0x02,  
                            }run_status_Def;
                            static bool indoor_temp_low_status = false;
                            static run_status_Def  run_status = STATUS_INIT;
                            switch (run_status)
                            {
                                case STATUS_INIT:
                                {
                                    if(Pull_RSS1001H_OnlineState(SENSOR_OUTDOOR))   
                                    {
                                        if(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR) <= INDOOR_TEMP)
                                        {
                                            run_status = STATUS_ONE;
                                            second_count = 0;
                                        }
                                        else if(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR) >= (INDOOR_TEMP + 20))
                                        {
                                            run_status = STATUS_TWO;
                                            second_count = 0;
                                        }
                                        else
                                        {
                                            run_status = STATUS_ONE;
                                            second_count = 0;
                                        }
                                        pbc_reload_timerClock(&status_delay,DELAY_12_HOUR);
                                    }
                                    else
                                    {
                                        run_status = STATUS_ONE;
                                        second_count = 0;
                                    }
                                    break;
                                }    
                                case STATUS_ONE:
                                {
                                    if(pbc_pull_timerIsCompleted(&status_delay))
                                    {//12小时后
                                        if(Pull_RSS1001H_OnlineState(SENSOR_OUTDOOR))  
                                        {
                                            if(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR) >= (INDOOR_TEMP + 20))
                                            {
                                                second_count = 0;
                                                run_status = STATUS_TWO;
                                                pbc_reload_timerClock(&status_delay,DELAY_12_HOUR);
                                            }
                                        }   
                                    }
                                    else
                                    {//未到12小时                                       
                                        if(pbc_pull_timerIsCompleted(&measure_delay))
                                        {
                                            pbc_reload_timerClock(&measure_delay,DELAY_1000MS);
                                            if(Pull_RSS1001H_OnlineState(SENSOR_OUTDOOR)) 
                                            {
                                                if(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR) >= (INDOOR_TEMP + 20)) 
                                                {
                                                    second_count++;
                                                    if(second_count >= DELAY_4_HOUR)
                                                    {
                                                        second_count = 0;
                                                        run_status = STATUS_TWO;
                                                        pbc_reload_timerClock(&status_delay,DELAY_12_HOUR);
                                                    }
                                                }  
                                                else
                                                {
                                                    second_count = 0;
                                                } 
                                            }                                          
                                        }                                       
                                    }
                                    indoor_temp_low_status = true;
                                    break;
                                }  
                                case STATUS_TWO:
                                {
                                    if(pbc_pull_timerIsCompleted(&status_delay))
                                    {//12小时后
                                        if(Pull_RSS1001H_OnlineState(SENSOR_OUTDOOR))  
                                        {
                                            if(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR) <= INDOOR_TEMP)
                                            {
                                                second_count = 0;
                                                run_status = STATUS_ONE;
                                                pbc_reload_timerClock(&status_delay,DELAY_12_HOUR);
                                            }
                                        } 
                                        else
                                        {
                                            second_count = 0;
                                            run_status = STATUS_ONE;
                                            pbc_reload_timerClock(&status_delay,DELAY_12_HOUR);
                                        }  
                                    }
                                    else
                                    {//未到12小时                                       
                                        if(pbc_pull_timerIsCompleted(&measure_delay))
                                        {
                                            pbc_reload_timerClock(&measure_delay,DELAY_1000MS);
                                            if(Pull_RSS1001H_OnlineState(SENSOR_OUTDOOR)) 
                                            {
                                                if(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR) <= INDOOR_TEMP) 
                                                {
                                                    second_count++;
                                                    if(second_count >= DELAY_4_HOUR)
                                                    {
                                                        second_count = 0;
                                                        run_status = STATUS_ONE;
                                                        pbc_reload_timerClock(&status_delay,DELAY_12_HOUR);
                                                    }
                                                }  
                                                else
                                                {
                                                    second_count = 0;
                                                } 
                                            } 
                                            else
                                            {
                                                second_count = 0;
                                                run_status = STATUS_ONE;
                                                pbc_reload_timerClock(&status_delay,DELAY_12_HOUR);
                                            }                                         
                                        }                                       
                                    }
                                    indoor_temp_low_status = false;
                                    break;
                                }                         
                                default:break;
                            }
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_AUTO_COOL);//空调夏季自动模式
                            app_general_push_indoor_dehum_status(indoor_temp_low_status);
                            if(indoor_temp_low_status)
                            {
                                APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,SET_COLD_WIND_TEMP_INDOOR_LOW);//氟机
                                APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,SET_HUM_INDOOR_LOW);//设定相对湿度
                                APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,SET_COLD_WATER_TEMP_INDOOR);//水机
                                app_general_push_water_machine_status(false);
                                APP_push_aricod_message(DRIVE_BOARD_WATER_MACHINE_POWER,app_general_pull_water_machine_status());//水机
                            }
                            else  
                            {
                                app_general_push_water_machine_status(true);
                                APP_push_aricod_message(DRIVE_BOARD_WATER_MACHINE_POWER,app_general_pull_water_machine_status());//水机
                                if((s_sysPara.system_error_word & SYS_ERROR_MIX_WATER) ||  (s_sysPara.system_error_word & SYS_ERROR_BEFORE_FU_AIR_NTC) ||
                                (s_sysPara.system_error_word & SYS_ERROR_BACK_AIR_NTC) || (app_pull_system_energy_need() & MIX_VAVLE_ERROR_BIT)) 
                                {//故障
                                    APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,SET_COLD_WATER_TEMP_INDOOR);//水机
                                }   
                                else
                                {
                                    if(((app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT) == 0) && 
                                    ((app_pull_system_energy_need() & ENGER_NEED_FAN_BIT) == 0))
                                    {//所有末端无能需
                                        APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,SET_COLD_WATER_TEMP_INDOOR);//水机
                                        APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,SET_HUM_INDOOR_HIGH);//设定相对湿度
                                        APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,SET_COLD_WIND_TEMP_INDOOR_HIGH);//氟机 
                                    }
                                    else
                                    {
                                        if((app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT) && 
                                            ((app_pull_system_energy_need() & ENGER_NEED_FAN_BIT) == 0))
                                        {//仅辐射能需
                                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,SET_COLD_WIND_TEMP_INDOOR_HIGH);//氟机 
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,SET_HUM_INDOOR_HIGH);//设定相对湿度
                                            APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_max_lew_temp());//水机
                                        }
                                        else if(((app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT) == 0) && 
                                            (app_pull_system_energy_need() & ENGER_NEED_FAN_BIT))
                                        {//仅风盘能需
                                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,SET_COLD_WIND_TEMP_INDOOR_HIGH);//氟机 
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,SET_HUM_INDOOR_HIGH);//设定相对湿度
                                            APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_max_lew_temp());//水机
                                        }   
                                        else if((app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT) && 
                                            (app_pull_system_energy_need() & ENGER_NEED_FAN_BIT))
                                        {//风盘辐射能需
                                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,SET_COLD_WIND_TEMP_INDOOR_HIGH);//氟机 
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,SET_HUM_INDOOR_HIGH);//设定相对湿度
                                            APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_max_lew_temp());//水机
                                        }                
                                    }           
                                }    
                            }                
                        }                                                   
                        APP_pull_aricod_message(DRIVE_BOARD_FAN_CONTROL_ENABLE,&fanControlEnable);
                        if(fanControlEnable)
                        {//启用
                            APP_pull_aricod_message(DRIVE_BOARD_FAN_SPEED,&airFanSpeed);//获取风机转速倍数
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }
                        else
                        {//禁用
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }        
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);
                        break;
                    }
                    case AIR_MODE_AUTO_HEAT:
                    case AIR_MODE_HEAT://制热模式
                    {  
                        if(StoRunParameter.debug_enable)
                        {
                           // s_sysPara.energyNeed = true; 
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,StoRunParameter.airRunmode);//模式
                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,StoRunParameter.hotTemp_set);//氟机
                            APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,StoRunParameter.set_heat_water_temp);//水机
                            APP_push_aricod_message(DRIVE_BOARD_WATER_MACHINE_POWER,app_general_pull_water_machine_status());//水机开关机
                        }
                        else
                        {
                            s_sysPara.energyNeed = true; 
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_AUTO_HEAT);//空调自动制热模式  
                            if((s_sysPara.system_error_word & SYS_ERROR_MIX_WATER) ||  (s_sysPara.system_error_word & SYS_ERROR_BEFORE_FU_AIR_NTC) ||
                            (s_sysPara.system_error_word & SYS_ERROR_BACK_AIR_NTC) ) 
                            {//故障
                                APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_heat_no_need_set_temp());//停止水机运行
                                APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_aircod_heat_stop_temp());//制热回风设定温度
                            }   
                            else
                            {
                                if(((app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT) == 0) && 
                                ((app_pull_system_energy_need() & ENGER_NEED_FAN_BIT) == 0))
                                {//所有末端无能需
                                    
                                    APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_heat_no_need_set_temp());//停止水机运行
                                }  
                                else
                                {
                                    if(app_pull_system_energy_need() & ENGER_NEED_FAN_BIT)
                                    {//风盘能需
                                        APP_push_aricod_message(DRIVE_BOARD_HOT_OUTWATER_SETTEMP,app_general_pull_heat_fan_need_set_temp());//制热出水设置温度
                                    }
                                    else
                                    {
                                        APP_push_aricod_message(DRIVE_BOARD_HOT_OUTWATER_SETTEMP,app_general_pull_heat_warm_need_set_temp());//制热出水设置温度
                                    }
                                    if((Pull_RSS1001H_Temperature(SENSOR_BACKAIR) - Pull_RSS1001H_Temperature(SENSOR_BEFOREFU)) >= 30)
                                    {//氟机制热模式
                                        APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_heat_wind_max_set_temp());//制热回风设定温度
                                    }
                                    else
                                    {
                                        if(Pull_RSS1001H_Temperature(SENSOR_BACKAIR) >= (app_general_pull_config_back_wind_set_temp()+20))
                                        {//氟机停机
                                            APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_heat_wind_min_set_temp());//制热回风设定温度
                                        }
                                        else if(Pull_RSS1001H_Temperature(SENSOR_BACKAIR) < app_general_pull_config_back_wind_set_temp())
                                        {//氟机制热
                                            APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_heat_wind_max_set_temp());//制热回风设定温度
                                        }
                                    }
                                }   
                            }              
                        }              
                        APP_pull_aricod_message(DRIVE_BOARD_FAN_CONTROL_ENABLE,&fanControlEnable);
                        if(fanControlEnable)
                        {//启用
                            APP_pull_aricod_message(DRIVE_BOARD_FAN_SPEED,&airFanSpeed);//获取风机转速倍数  
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);              
                        }
                        else
                        {//禁用
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);
                        break;
                    }
                    case AIR_MODE_HUMIDITY://除湿模式
                    {	                    
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,1);
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_HUMIDITY);//空调除湿模式
                        s_sysPara.energyNeed = true;
                        APP_pull_aricod_message(DRIVE_BOARD_FAN_CONTROL_ENABLE,&fanControlEnable);	
                        APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_aircod_humidity()*10);//设定相对湿度			
                        if(fanControlEnable)
                        {//启用
                            APP_pull_aricod_message(DRIVE_BOARD_FAN_SPEED,&airFanSpeed);//获取风机转速倍数
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        }
                        else
                        {//禁用
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }    
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,1);
                        break;
                    }
                    case AIR_MODE_WATER://热水模式
                    {
                        s_sysPara.energyNeed = false;
                        aircod_ec_newwind_s = 0;
                        aircod_ec_backwind_s = 0;
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_FAN);//空调生活热水模式
                        break;
                    }
                    default:
                    {//新风模式                            
                        s_sysPara.energyNeed = false;
                        aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_FAN);//空调生活热水模式
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);
                        break;
                    }
                }      
            }
            break;
        }
        default:
        {//默认按基础策略走
            if(powerOff_now)
            {//关机        
                
                if(app_general_pull_low_protect_output())
                {//有防冻请求
                    APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,1);//空调开机
                    APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_AUTO_HEAT);//空调制热模式
                    s_sysPara.energyNeed = true;
                    aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                    aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                    
                }
                else
                {
                    APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,0);//空调关机
                    aircod_ec_newwind_s = 0;//新风风机
                    aircod_ec_backwind_s = 0;//回风风机
                    s_sysPara.energyNeed = false;
                }           
            }
            else
            { //开机   
                APP_push_aricod_message(DRIVE_BOARD_POWER_ON_OFF,1);//空调开机      
                APP_push_aricod_message(DRIVE_BOARD_COOL_BACKWATER_SETTEMP,app_general_pull_set_cold_backwater_temp());//制冷回水设置温度   
                APP_push_aricod_message(DRIVE_BOARD_HOT_BACKWATER_SETTEMP,app_general_pull_set_heat_backwater_temp());//制热回水设置温度 
                APP_push_aricod_message(DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP,app_general_pull_set_living_water_temp());//设定生活热水温度       
            //  APP_push_aricod_message(DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP,400);//设定生活热水温度  
                macro_createTimer(timer_temp_updata,timerType_second,0);  //温度更新
                pbc_timerClockRun_task(&timer_temp_updata);
                if(pbc_pull_timerIsCompleted(&timer_temp_updata))
                {
                    pbc_reload_timerClock(&timer_temp_updata,5);
                    APP_push_aricod_message(DRIVE_BOARD_INWIND_HUMIDITY,Pull_RSS1001H_Humidity(SENSOR_OUTDOOR)*10);
                    APP_push_aricod_message(DRIVE_BOARD_INWIND_TEMP,Pull_RSS1001H_Temperature(SENSOR_OUTDOOR));
                    APP_push_aricod_message(DRIVE_BOARD_BACKWIND_TEMP,Pull_RSS1001H_Temperature(SENSOR_BACKAIR));
                    APP_push_aricod_message(DRIVE_BOARD_BACKWIND_HUMIDITY,Pull_RSS1001H_Humidity(SENSOR_BACKAIR)*10);
                    app_general_push_freshaireffciency_set_temp(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR), \
                        Pull_RSS1001H_Temperature(SENSOR_AFTERFU), \
                        Pull_RSS1001H_Temperature(SENSOR_BACKAIR));//5s计算一次新风效率
                }
                sendairfanspeed = (95 + ((StoRunParameter.NewAirLevelSet-1) * 5));
                APP_push_aricod_message(DRIVE_BOARD_FAN_FEEDBACK_SPEED,sendairfanspeed);
                APP_push_aricod_message(DRIVE_BOARD_HOTWATER_ENABLE,app_general_pull_hotwater_enable());
                switch(StoRunParameter.airRunmode)
                {					
                    case AIR_MODE_FAN://新风模式
                    {               
                        s_sysPara.energyNeed = false;
                        aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_FAN);//AIR_MODE_LIVING_WATER);//空调新风模式
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);              
                        break;
                    }
                    case AIR_MODE_AUTO_COOL:
                    case AIR_MODE_COOL://制冷模式
                    {   
                        if(StoRunParameter.debug_enable)
                        {
                          //  s_sysPara.energyNeed = true; 
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,StoRunParameter.airRunmode);//模式
                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,StoRunParameter.coldTemp_set);//氟机
                            APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,StoRunParameter.set_cold_water_temp);//水机
                            APP_push_aricod_message(DRIVE_BOARD_WATER_MACHINE_POWER,app_general_pull_water_machine_status());//水机开关机
                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,StoRunParameter.humidity_set*10);//设定相对湿度,固定50%
                        }
                        else
                        {
                            s_sysPara.energyNeed = true; 
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_AUTO_COOL);//空调夏季自动模式
                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,app_general_pull_cold_wind_max_set_temp());//氟机保证不制冷  
                        //  APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,180);//氟机保证不制冷 
                            if((s_sysPara.system_error_word & SYS_ERROR_MIX_WATER) ||  (s_sysPara.system_error_word & SYS_ERROR_BEFORE_FU_AIR_NTC) ||
                            (s_sysPara.system_error_word & SYS_ERROR_BACK_AIR_NTC) || (app_pull_system_energy_need() & MIX_VAVLE_ERROR_BIT)) 
                            {//故障
                                APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_cold_no_need_set_temp());//停止水机运行
                            }   
                            else
                            {
                                if(((app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT) == 0) && 
                                ((app_pull_system_energy_need() & ENGER_NEED_FAN_BIT) == 0))
                                {//所有末端无能需
                                    
                                    APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_cold_no_need_set_temp());//停止水机运行
                                    APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_config_hum_set()*10);//设定相对湿度,固定50%
                                }
                                else
                                {
                                    if(app_pull_system_energy_need() & ENGER_NEED_FAN_BIT)
                                    {//风盘能需
                                        APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_cold_fan_need_set_temp());//制冷出水设置温度
                                    }
                                    else
                                    {
                                        APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_cold_warm_need_set_temp());//制冷出水设置温度
                                    }
                                    if(app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT)
                                    {//有辐射能需
                                        if(app_pull_system_energy_need() & ENGER_NEED_CLOD_BIT)
                                        {//除湿状态
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_auto_set_hum()*10);//自动计算相对湿度
                                        }
                                        else
                                        {
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_config_hum_set()*10);//设定相对湿度,固定50%
                                        }
                                        
                                    }
                                    else
                                    {//无辐射能需
                                        if(app_pull_system_energy_need() & ENGER_NEED_LEW_TEMP_PROTECT_BIT)
                                        {//露点保护
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_auto_set_hum()*10);//自动计算相对湿度
                                        }
                                        else
                                        {
                                            APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_config_hum_set()*10);//设定相对湿度,固定50%
                                        }           
                                    }                   
                                }           
                            }                    
                        }                                                   
                        APP_pull_aricod_message(DRIVE_BOARD_FAN_CONTROL_ENABLE,&fanControlEnable);
                        if(fanControlEnable)
                        {//启用
                            APP_pull_aricod_message(DRIVE_BOARD_FAN_SPEED,&airFanSpeed);//获取风机转速倍数
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }
                        else
                        {//禁用
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }        
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);
                        break;
                    }
                    case AIR_MODE_AUTO_HEAT:
                    case AIR_MODE_HEAT://制热模式
                    {  
                        if(StoRunParameter.debug_enable)
                        {
                          //  s_sysPara.energyNeed = true; 
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,StoRunParameter.airRunmode);//模式
                            APP_push_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,StoRunParameter.hotTemp_set);//氟机
                            APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,StoRunParameter.set_heat_water_temp);//水机
                            APP_push_aricod_message(DRIVE_BOARD_WATER_MACHINE_POWER,app_general_pull_water_machine_status());//水机开关机
                        }
                        else
                        {
                            s_sysPara.energyNeed = true;
                            APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_AUTO_HEAT);//空调自动制热模式  
                            if((s_sysPara.system_error_word & SYS_ERROR_MIX_WATER) ||  (s_sysPara.system_error_word & SYS_ERROR_BEFORE_FU_AIR_NTC) ||
                            (s_sysPara.system_error_word & SYS_ERROR_BACK_AIR_NTC) ) 
                            {//故障
                                APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_heat_no_need_set_temp());//停止水机运行
                                APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_aircod_heat_stop_temp());//制热回风设定温度
                            }   
                            else
                            {
                                if(((app_pull_system_energy_need() & ENGER_NEED_RADIATION_BIT) == 0) && 
                                ((app_pull_system_energy_need() & ENGER_NEED_FAN_BIT) == 0))
                                {//所有末端无能需
                                     
                                    APP_push_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,app_general_pull_heat_no_need_set_temp());//停止水机运行
                                }  
                                else
                                {
                                    if(app_pull_system_energy_need() & ENGER_NEED_FAN_BIT)
                                    {//风盘能需
                                        APP_push_aricod_message(DRIVE_BOARD_HOT_OUTWATER_SETTEMP,app_general_pull_heat_fan_need_set_temp());//制热出水设置温度
                                    }
                                    else
                                    {
                                        APP_push_aricod_message(DRIVE_BOARD_HOT_OUTWATER_SETTEMP,app_general_pull_heat_warm_need_set_temp());//制热出水设置温度
                                    }
                                    if((Pull_RSS1001H_Temperature(SENSOR_BACKAIR) - Pull_RSS1001H_Temperature(SENSOR_BEFOREFU)) >= 30)
                                    {//氟机制热模式
                                        APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_heat_wind_max_set_temp());//制热回风设定温度
                                    }
                                    else
                                    {
                                        if(Pull_RSS1001H_Temperature(SENSOR_BACKAIR) >= (app_general_pull_config_back_wind_set_temp()+20))
                                        {//氟机停机
                                            APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_heat_wind_min_set_temp());//制热回风设定温度
                                        }
                                        else if(Pull_RSS1001H_Temperature(SENSOR_BACKAIR) < app_general_pull_config_back_wind_set_temp())
                                        {//氟机制热
                                            APP_push_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,app_general_pull_heat_wind_max_set_temp());//制热回风设定温度
                                        }
                                    }
                                }   
                            }              
                        }              
                        APP_pull_aricod_message(DRIVE_BOARD_FAN_CONTROL_ENABLE,&fanControlEnable);
                        if(fanControlEnable)
                        {//启用
                            APP_pull_aricod_message(DRIVE_BOARD_FAN_SPEED,&airFanSpeed);//获取风机转速倍数  
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);              
                        }
                        else
                        {//禁用
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);
                        break;
                    }
                    case AIR_MODE_HUMIDITY://除湿模式
                    {	                    
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,1);
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_HUMIDITY);//空调除湿模式
                        s_sysPara.energyNeed = true;
                        APP_pull_aricod_message(DRIVE_BOARD_FAN_CONTROL_ENABLE,&fanControlEnable);	
                        APP_push_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,app_general_pull_aircod_humidity()*10);//设定相对湿度			
                        if(fanControlEnable)
                        {//启用
                            APP_pull_aricod_message(DRIVE_BOARD_FAN_SPEED,&airFanSpeed);//获取风机转速倍数
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        }
                        else
                        {//禁用
                            aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                            aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet); 
                        }    
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,1);
                        break;
                    }
                    case AIR_MODE_WATER://热水模式
                    {
                        s_sysPara.energyNeed = false;
                        aircod_ec_newwind_s = 0;
                        aircod_ec_backwind_s = 0;
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_FAN);//空调生活热水模式
                        break;
                    }
                    default:
                    {//新风模式                            
                        s_sysPara.energyNeed = false;
                        aircod_ec_newwind_s = app_pull_newAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        aircod_ec_backwind_s = app_pull_backAir_pwm_value(StoRunParameter.NewAirLevelSet);
                        APP_push_aricod_message(DRIVE_BOARD_SET_MODE,AIR_MODE_FAN);//空调生活热水模式
                        APP_push_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,0);
                        break;
                    }
                }      
            }
            break;
        }
    }
//-----------------------------------------------------------------------------
//------------------------------------------------------------------------------
//protection liftPump   提水泵输出  
    #define INPUT_WATER_FULL   3
    #define WATER_FULL   0x02
//    static uint8_t drainWaterError = 0;
    static enum
    {
        liftpump_st_idle   =  0,
        liftpump_st_high_check,
        liftpump_st_run,
        liftpump_st_run_delay,
        liftpump_st_run_warning,
    }liftpump_protection_st;

    macro_createTimer(timer_liftPump_output,timerType_second,0);//提水泵输出时间
    macro_createTimer(timer_liftPump_protect,timerType_second,0);//提水泵保护时间
    bool water_full_flag;
    static bool last_liftpump_output_s = false;
    pbc_timerClockRun_task(&timer_liftPump_output);
    pbc_timerClockRun_task(&timer_liftPump_protect);
    water_full_flag = mde_gigit_pull_status(INPUT_WATER_FULL);
    if(water_full_flag == false)
    {
        s_sysPara.system_status_word |= WATER_FULL;
    }
    else
    {
       s_sysPara.system_status_word &= (~WATER_FULL); 
    }
    if(restart_drain_water_error  & restart_control_bits)//reset drain water error
    {
        restart_control_bits &= ~restart_drain_water_error;
        protection_cpor_bits &= ~drain_water_error;
        liftpump_protection_st = liftpump_st_idle;
        app_general_clear_ae_error_word(SYS_ERROR_EXHAST_WATER);
    }
    if(StoRunParameter.drainWaterError & drain_water_error)
    {//上电保存的排水故障存在
        new_liftpump_s = false;
        app_general_push_ae_error_word(SYS_ERROR_EXHAST_WATER);
    }
    else
    {//正常状态下进行检测
        switch(liftpump_protection_st)
        {
            case liftpump_st_idle:
            {
                if(water_full_flag == false)
                {//180s滤波，后期考虑改为占空比滤波
                    pbc_reload_timerClock(&timer_liftPump_output,180);
                    liftpump_protection_st = liftpump_st_high_check;
                }
                break;
            }
            case liftpump_st_high_check:
            {
                if(water_full_flag)
                {
                    liftpump_protection_st = liftpump_st_idle;
                }
                else
                {
                    if(pbc_pull_timerIsCompleted(&timer_liftPump_output))
                    {
                        new_liftpump_s = true;
                        liftpump_protection_st = liftpump_st_run;
                    }
                }                  
                break;
            }
            case liftpump_st_run:
            {
                if(water_full_flag)
                {//水位正常后继续输出150s
                    pbc_reload_timerClock(&timer_liftPump_output,150);
                    liftpump_protection_st = liftpump_st_run_delay;
                }  
                break;
            }
            case liftpump_st_run_delay:
            {
                if(pbc_pull_timerIsCompleted(&timer_liftPump_output))
                {
                    new_liftpump_s = false;
                    liftpump_protection_st = liftpump_st_idle;
                }
                break;
            }   
            default:
            {
                liftpump_protection_st = liftpump_st_idle;
                break;
            }
        } 

        if(last_liftpump_output_s != new_liftpump_s)
        {
            last_liftpump_output_s = new_liftpump_s;
            if(last_liftpump_output_s)
            {//提水泵输出时
                pbc_reload_timerClock(&timer_liftPump_protect,180);//开启3分钟检测
            }
        }  
        else if((last_liftpump_output_s == true) && (water_full_flag == false))
        {//提水泵输出时3分钟水
            if(pbc_pull_timerIsCompleted(&timer_liftPump_protect))
            {
                protection_cpor_bits |= drain_water_error;
                app_general_push_ae_error_word(SYS_ERROR_EXHAST_WATER);
            }
        }       
        if(protection_cpor_bits &(drain_water_error))//排水故障停提水泵，故障需断电保存
        {
            new_liftpump_s = false;
            if((StoRunParameter.drainWaterError & drain_water_error) == 0)
            {
                StoRunParameter.drainWaterError |= drain_water_error;  
                app_push_once_save_sto_parameter();  
            }
        }  
    }
//-----------------------------------------------------------------------------
    macro_createTimer(timer_sys_pwoerup,timerType_second,0);  //上电延时
    static bool sys_powered = false;
    pbc_timerClockRun_task(&timer_sys_pwoerup);
	if(sys_powered)
    {
        if(pbc_pull_timerIsCompleted(&timer_sys_pwoerup))
        {   
//-----------------------------------------------------------------------------
//提水泵输出
            #define RELAY_LIFT_PUMP   5
            static bool liftpump_s_backup = false;
            static bool liftpump_output_backup = false;
            if(new_liftpump_s != liftpump_s_backup)
            {
                liftpump_s_backup = new_liftpump_s;
                if(new_liftpump_s)
                {
                    mde_relay_on(RELAY_LIFT_PUMP,20);
                }
                else
                {
                    mde_relay_off(RELAY_LIFT_PUMP,0);//
                }
            }
//--------------------------------------------------------------------
//提水泵特殊情况处理
//运行24小时不输出则提水泵开启30s
            #define DELAY_24_HOUR    1440
			#define DELAY_20_MIN     1200            

            macro_createTimer(timer_liftpump_output_delay,timerType_second,0);//提水泵输出延时
            macro_createTimer(timer_fu_machine_output_delay,timerType_millisecond,0);//压缩机输出延时
            macro_createTimer(timer_liftpump_1min_delay,timerType_minute,0);//提水泵开启1min计时
            pbc_timerClockRun_task(&timer_liftpump_output_delay);
            pbc_timerClockRun_task(&timer_liftpump_1min_delay);
            pbc_timerClockRun_task(&timer_fu_machine_output_delay);

            static uint16_t fu_output_count = 0;
            static bool fu_machine_has_output = false;
            if((new_liftpump_s== true) || (liftpump_output_backup == true))
			{
				pbc_reload_timerClock(&timer_liftpump_1min_delay,DELAY_24_HOUR);//开启24小时检测检测
			}
			else
			{//不输出
				if(pbc_pull_timerIsCompleted(&timer_liftpump_1min_delay))
				{//24小时到
					mde_relay_on(RELAY_LIFT_PUMP,20);     //提水泵开始输出
					liftpump_output_backup = true;
                    if(fu_machine_has_output)
                    {
                        fu_machine_has_output = false;
                        pbc_reload_timerClock(&timer_liftpump_output_delay,180);
                    }
                    else
                    {
                        pbc_reload_timerClock(&timer_liftpump_output_delay,30);
                    }				
				}
                else
                {//未到24小时时
                    if(app_general_pull_fu_machine_fre() > 0)
                    {//氟机有输出过
                        fu_machine_has_output = true;
                        if(pbc_pull_timerIsCompleted(&timer_fu_machine_output_delay))
                        {
                            pbc_reload_timerClock(&timer_fu_machine_output_delay,1000);
                            fu_output_count++;
                            if(fu_output_count >= DELAY_20_MIN)
                            {
                                fu_output_count = 0;
                                fu_machine_has_output = false;
                                mde_relay_on(RELAY_LIFT_PUMP,20);     //提水泵开始输出
                                liftpump_output_backup = true;
                                pbc_reload_timerClock(&timer_liftpump_output_delay,180);
                            }
                        }                      
                    }                   
                }               
			}
			if(liftpump_output_backup)
			{
				if(pbc_pull_timerIsCompleted(&timer_liftpump_output_delay))
				{
					liftpump_output_backup = false;
					mde_relay_off(RELAY_LIFT_PUMP,0);     //提水泵物理关闭
				}
			}
//--------------------------------------------------------------------	 
//------------------------------------------------------------------           
//EC风机			
            #define EC_PWM_OUTPUT_NEW_AIR   0
            #define EC_PWM_OUTPUT_BACK_AIR  1
            if(StoRunParameter.wind_value)
            {//开启风阀互换
                mde_SetInFanPwm(EC_PWM_OUTPUT_NEW_AIR,aircod_ec_backwind_s);
                mde_SetInFanPwm(EC_PWM_OUTPUT_BACK_AIR,aircod_ec_newwind_s);
            }
            else
            {
                mde_SetInFanPwm(EC_PWM_OUTPUT_NEW_AIR,aircod_ec_newwind_s);
                mde_SetInFanPwm(EC_PWM_OUTPUT_BACK_AIR,aircod_ec_backwind_s);
            }            
        }
    }
    else
    {
        pbc_reload_timerClock(&timer_sys_pwoerup,20);
        sys_powered = true;
    }			
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: 通用应用task
//-----------------------------------------------------------------------------
void app_general_task(void)
{
    static sdt_bool sys_cfged = sdt_false;
    mde_IWDG_FeedDog();
    if(sys_cfged)
    {
        mde_hc595_task();        
        app_sto_run_parameter_task();  
		app_pwm_control_task();
        app_logic_realy_task();
        app_master_comp_task();
        app_master_sensor_task();
        app_link_scheduler_task();  
        app_modbus_onewire_task();
        app_modbus_remote_task();      
        app_real_time_clock_task();      
        app_upgrade_easy_task();
        app_digti_in_task();
        app_general_aircod_run_task();   
        time_stamp_task();           
        app_led_task();
    }
    else
    {
        sys_cfged = sdt_true;      
        app_read_run_parameter();    
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
