//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "..\app_cfg.h"
#include "stdlib.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define  TIMING_SEND_BLOCK1_NUM     14
#define  TIMING_SEND_BLOCK2_NUM     8
#define  TIMING_SEND_BLOCK3_NUM     7

typedef enum
{
    SYN_STATUS_IDLE                = 0x00,
    SYN_STATUS_WAIT_RECEIVE,                     //等待接收
    SYN_STATUS_ANSWER,                           //响应
    SYN_STATUS_ANSWER_RESULT,                    //响应结果
    SYN_STATUS_SEND_UPDATA_ACTIVE,               //更新激活
    SYN_STATUS_SEND_UPDATA_ACTIVE_RESULT,        //激活结果
    SYN_STATUS_SEND_UPDATA_WORD,                 //发送更新帧   
    SYN_STATUS_SEND_UPDATA_WORD_RESULT,          //发送更新帧结果
    SYN_STATUS_SEND_UPDATA_WORD_ROLL_BACK,        //发送更新帧回退
    SYN_STATUS_RECEIVE_UPDATA_WORD,               //接收注册帧数据 
    SYN_STATUS_RESEND_UPDATA_ACTIVE,              //更新激活
    SYN_STATUS_RESEND_UPDATA_ACTIVE_RESULT,       //激活结果
    SYN_STATUS_RESEND_UPDATA_WORD,                //发送更新帧   
    SYN_STATUS_RESEND_UPDATA_WORD_RESULT,         //发送更新帧结果
    SYN_STATUS_RESEND_UPDATA_WORD_ROLL_BACK,      //发送更新帧回退
    SYN_STATUS_RERECEIVE_UPDATA_WORD,             //接收注册帧数据 
    SYN_STATUS_TIMING_SEND_ACTIVE,                  //发送列表激活
    SYN_STATUS_TIMING_SEND_ACTIVE_RESULT,           //激活结果
    SYN_STATUS_TIMING_SEND,                         //发送列表
    SYN_STATUS_TIMING_SEND_RESULT,                  //发送列表结果 
    SYN_STATUS_TIMING_SEND_ROLL_BACK,              //发送更新帧回退  
    SYN_STATUS_RECEIVE_TIMING,                      //接收结果 
    SYN_STATUS_TIMING_RESEND_ACTIVE,                //重发发送列表激活
    SYN_STATUS_TIMING_RESEND_ACTIVE_RESULT,         //重发激活结果
    SYN_STATUS_TIMING_RESEND,                       //重发发送列表
    SYN_STATUS_TIMING_RESEND_RESULT,               //重发发送列表结果 
    SYN_STATUS_TIMING_RESEND_ROLL_BACK,             //发送更新帧回退   
    SYN_STATUS_RERECEIVE_TIMING,                   //重发接收结果 
}synStatus_def;

uint8_t deviceid_addr[6]={0xaa,0xaa,0xaa,0xaa,0xaa,0xaa};//写入设备ID时用的地址
#define  DEVICE_KEY 0XFA3456AF//写入设备密匙
const uint8_t dpPadLen[MAX_DATA_POINT_LEN] = {1,1,2,2,1,1,2,2,2,2,2,1,1,2,3,3,11,11,11,15,11,2,10,43,8,6,6,7,4,168,148,4};

typedef struct
{
    synStatus_def   mainSynStatsus;       //主同步状态
    uint32_t        updataWord;           //更新字
	uint32_t        updataWord1;           //更新字1
    uint16_t        timingSendWord;        //定时发送字
    bgk_comm_buff_def *in_rev_data;       //收到数据
    bool              receiveOneMessage;  //收到一帧数据
    timerClock_def    receive_timeout_delay;//接收超时
    timerClock_def    roll_back_delay;    //回退延时
    timerClock_def    answer_delay;       //应答延时
    timerClock_def    timing_send_dalay;   //定时发送
}msComm_t;

msComm_t appModbusSyn[MAX_MODBUS_NUM];


void app_pull_data_point_message(uint16_t in_dpAddr,uint8_t *out_buff)
{
    switch (in_dpAddr)
    {
        case DP_ADDR_SYSTEM_POWER:
        {
            out_buff[0] = app_general_pull_power_status();
            break;
        }   
        case DP_ADDR_SYSTEM_RUN_MODE:
        {
            out_buff[0] = app_general_pull_aircod_mode();
            break;
        }   
        case DP_ADDR_SYSTEM_WIND_SET_CLOD_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_aircod_cold_temp(),out_buff);
            break;
        }   
        case DP_ADDR_SYSTEM_WIND_SET_HEAT_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_aircod_heat_temp(),out_buff);
            break;
        }   
        case DP_ADDR_SYSTEM_WIND_SET_HUM:
        {
            out_buff[0] = app_general_pull_aircod_humidity();
            break;
        }   
        case DP_ADDR_SYSTEM_WIND_SET_SPEED:
        {
            out_buff[0] = app_general_pull_aircod_fanSpeed();
            break;
        }   
        case DP_ADDR_SYSTEM_WATER_SET_CLOD_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_set_cold_water_temp(),out_buff);
            break;
        }   
        case DP_ADDR_SYSTEM_WATER_SET_HEAT_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_set_heat_water_temp(),out_buff);
            break;
        }   
        case DP_ADDR_SYSTEM_WATER_SET_LIVING_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_set_living_water_temp(),out_buff);
            break;
        }   
        case DP_ADDR_SYSTEM_MIXWATER_SET_CLOD_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_set_mixwater_cold_temp(),out_buff);
            break;
        }   
        case DP_ADDR_SYSTEM_MIXWATER_SET_HEAT_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_set_mixwater_heat_temp(),out_buff);
            break;
        }   
        case DP_ADDR_SYSTEM_MIXWATER_AI_ENABLE:
        {
            out_buff[0] = app_general_pull_ai_enable_status();
            break;
        }   
        case DP_ADDR_SYSTEM_MIXWATER_LOW_TEMP_PROTECT:
        {
            out_buff[0] = app_general_pull_mix_freeze_protect();
            break;
        }   
        case DP_ADDR_SYSTEM_MIXWATER_AI_DEST_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_ai_dest_temp(),out_buff);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_NEW_AIR_PWM:
        {
            out_buff[0] = app_general_pull_new_air_pwm_low();
            out_buff[1] = app_general_pull_new_air_pwm_mid();
            out_buff[2] = app_general_pull_new_air_pwm_high();
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_BACK_AIR_PWM:
        {
            out_buff[0] = app_general_pull_back_air_pwm_low();
            out_buff[1] = app_general_pull_back_air_pwm_mid();
            out_buff[2] = app_general_pull_back_air_pwm_high();
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_OUTDOOR_WEATHER:
        {   
            pbc_int16uToArray_bigEndian(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR),&out_buff[0]);
            out_buff[2] = Pull_RSS1001H_Humidity(SENSOR_OUTDOOR);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_outdoor_hum(),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_outdoor_temp(),&out_buff[5]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_outdoor_co2(),&out_buff[7]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_outdoor_pm25(),&out_buff[9]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_BEFORE_FU_WEATHER:
        {
            pbc_int16uToArray_bigEndian(Pull_RSS1001H_Temperature(SENSOR_BEFOREFU),&out_buff[0]);
            out_buff[2] = Pull_RSS1001H_Humidity(SENSOR_BEFOREFU);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_beforfu_hum(),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_beforfu_temp(),&out_buff[5]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_beforfu_co2(),&out_buff[7]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_beforfu_pm25(),&out_buff[9]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_AFTER_FU_WEATHER:
        {
            pbc_int16uToArray_bigEndian(Pull_RSS1001H_Temperature(SENSOR_AFTERFU),&out_buff[0]);
            out_buff[2] = Pull_RSS1001H_Humidity(SENSOR_AFTERFU);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_afterfu_hum(),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_afterfu_temp(),&out_buff[5]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_afterfu_co2(),&out_buff[7]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_afterfu_pm25(),&out_buff[9]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_BACK_AIR_WEATHER:
        {
            pbc_int16uToArray_bigEndian(Pull_RSS1001H_Temperature(SENSOR_BACKAIR),&out_buff[0]);
            out_buff[2] = Pull_RSS1001H_Humidity(SENSOR_BACKAIR);
            pbc_int16uToArray_bigEndian(Pull_RSS1001H_CO2(SENSOR_BACKAIR),&out_buff[3]);
            pbc_int16uToArray_bigEndian(Pull_RSS1001H_PM25(SENSOR_BACKAIR),&out_buff[5]);    
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_backair_hum(),&out_buff[7]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_backair_temp(),&out_buff[9]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_backair_co2(),&out_buff[11]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_backair_pm25(),&out_buff[13]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_EXHAST_AIR_WEATHER:
        {
            pbc_int16uToArray_bigEndian(Pull_RSS1001H_Temperature(SENSOR_EXHASTAIR),&out_buff[0]);
            out_buff[2] = Pull_RSS1001H_Humidity(SENSOR_EXHASTAIR);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_exhastair_hum(),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_exhastair_temp(),&out_buff[5]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_exhastair_co2(),&out_buff[7]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_exhastair_pm25(),&out_buff[9]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_DEAD_ZONE:
        {
            out_buff[0] = app_general_pull_aircod_setHum_deadZone();
            out_buff[1] = app_general_pull_aircod_setTemp_deadZone();
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_OUT_VALVE:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_aircod_newair_speed(),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_general_pull_aircod_backair_speed(),&out_buff[2]);
            pbc_int16uToArray_bigEndian(app_general_pull_water_machine_fre(),&out_buff[4]);
            pbc_int16uToArray_bigEndian(app_general_pull_fu_machine_fre(),&out_buff[6]);
			pbc_int16uToArray_bigEndian(app_general_pull_freshaireffciency_set_temp(),&out_buff[8]);//新风效率值20210413
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_OUT_STATUS:
        {           
            pbc_int16uToArray_bigEndian(app_general_pull_ae_error_word(),&out_buff[0]);
            out_buff[2] = app_general_pull_anergy_need();
            pbc_int16uToArray_bigEndian(app_general_pull_ae_ntc_error_word(),&out_buff[3]);
            pbc_int16uToArray_bigEndian(0x00,&out_buff[5]);
            pbc_int16uToArray_bigEndian(app_general_pull_system_status_word(),&out_buff[7]);
            out_buff[9] = app_general_pull_wind_value();
            out_buff[10] = app_general_pull_hotwater_enable();
            pbc_int16uToArray_bigEndian(app_general_pull_filter_time(),&out_buff[11]);
            pbc_int16uToArray_bigEndian(app_general_pull_filter_usetime(),&out_buff[13]);
            out_buff[15] = app_general_pull_debug_enable();
            out_buff[16] = app_general_pull_main_control_method();
            pbc_int16uToArray_bigEndian(app_general_pull_cold_no_need_set_temp(),&out_buff[17]);
            pbc_int16uToArray_bigEndian(app_general_pull_cold_fan_need_set_temp(),&out_buff[19]);
            pbc_int16uToArray_bigEndian(app_general_pull_cold_warm_need_set_temp(),&out_buff[21]);
            pbc_int16uToArray_bigEndian(app_general_pull_config_lew_set_temp(),&out_buff[23]);
            pbc_int16uToArray_bigEndian(app_general_pull_heat_no_need_set_temp(),&out_buff[25]);
            pbc_int16uToArray_bigEndian(app_general_pull_heat_fan_need_set_temp(),&out_buff[27]);
            pbc_int16uToArray_bigEndian(app_general_pull_heat_warm_need_set_temp(),&out_buff[29]);
            pbc_int16uToArray_bigEndian(app_general_pull_config_back_wind_set_temp(),&out_buff[31]);
            pbc_int16uToArray_bigEndian(app_general_pull_config_hum_set(),&out_buff[33]);
            pbc_int16uToArray_bigEndian(app_general_pull_cold_wind_max_set_temp(),&out_buff[35]);
            pbc_int16uToArray_bigEndian(app_general_pull_heat_wind_min_set_temp(),&out_buff[37]);
            pbc_int16uToArray_bigEndian(app_general_pull_heat_wind_max_set_temp(),&out_buff[39]);
            out_buff[41] = app_general_pull_indoor_dehum_status();
            out_buff[42] = app_general_pull_water_machine_status();
            break;
        } 
         case DP_ADDR_SYSTEM_LIS_MIXWATER_OUT:
        {
            out_buff[0] = app_general_pull_pump_output();
            out_buff[1] = app_general_pull_three_vavle_output();
            out_buff[2] = app_pull_low_protect_reguest();//防冻请求
            pbc_int16uToArray_bigEndian(app_general_pull_ac_error_word(),&out_buff[3]);
            out_buff[5] = app_pull_system_energy_need();
            pbc_int16uToArray_bigEndian(app_general_pull_max_lew_temp(),&out_buff[6]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_MAIN_MACHINE_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_master_supply_temp(),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_general_pull_master_living_temp(),&out_buff[2]);
            pbc_int16uToArray_bigEndian(Pull_RSS1001H_Temperature(SENSOR_OUTDOOR),&out_buff[4]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_MIXWATER_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_in_water_measure_temp(),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_general_pull_back_water_measure_temp(),&out_buff[2]);
            pbc_int16uToArray_bigEndian(app_general_pull_mix_water_measure_temp(),&out_buff[4]);
            break;
        }      
        case  DP_ADDR_SYSTEM_LIS_RTC:
        {
            realTime_t* rtc;
            rtc = app_real_time_pull_rtc();
            out_buff[0] = rtc->second;
            out_buff[1] = rtc->minute;
            out_buff[2] = rtc->hour;
            out_buff[3] = rtc->week;
            out_buff[4] = rtc->day;
            out_buff[5] = rtc->month;
            out_buff[6] = rtc->year;
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_485_PAREMETER:
        {
            out_buff[0] = 0x01;
            out_buff[1] = 0x02;
            out_buff[2] = 0x03;
            out_buff[3] = 0x04;
            break;
        }   
		case DP_ADDR_SYSTEM_AIRCOD_READ_ONLY_PAREMETER:
		{
			uint8_t i = 0;
			uint8_t j = 0;
			uint16_t value = 0;
			for(i = 1;i <= ARICOD_READ_ONLY_REG_NUM;i++)
			{
				APP_pull_aricod_message(i,&value);
				pbc_int16uToArray_bigEndian(value,&out_buff[j]);
				j += 2;
			}
			break;
		}
		case DP_ADDR_SYSTEM_AIRCOD_READ_WRITE_PAREMETER:
		{
			uint8_t i = 0;
			uint8_t j = 0;
			uint16_t value = 0;
			for(i = 1;i <= ARICOD_READ_WRITE_REG_NUM;i++)
			{
				APP_pull_aricod_message((5000+i),&value);
				pbc_int16uToArray_bigEndian(value,&out_buff[j]);
				j += 2;
			}
			break;
		}
		case DP_ADDR_SYSTEM_AIRCOD_COLD_BACK_WATER:
		{//制冷回水
			pbc_int16uToArray_bigEndian(app_general_pull_coolbackwater_set_temp(),&out_buff[0]);
			pbc_int16uToArray_bigEndian(app_general_pull_hotbackwater_set_temp(),&out_buff[0]);
			break;
		}
		case DP_ADDR_SYSTEM_AIRCOD_WARM_BACK_WATER:
		{//制热回水			
			break;
		}
        default:
        {
            break;
        }           
    }
}
void app_push_data_point_message(uint16_t in_dpAddr,uint8_t *in_buff)
{
    switch (in_dpAddr)
    {       
        case DP_ADDR_SYSTEM_POWER:
        {
            app_general_push_power_status(in_buff[0]);
            break;
        }   
        case DP_ADDR_SYSTEM_RUN_MODE:
        {
            app_general_push_aircod_mode((AirRunMode_Def)in_buff[0]);
            break;
        }   
        case DP_ADDR_SYSTEM_WIND_SET_CLOD_TEMP:
        {
            app_general_push_aircod_cold_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            break;
        }   
        case DP_ADDR_SYSTEM_WIND_SET_HEAT_TEMP:
        {
            app_general_push_aircod_heat_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            break;
        }   
        case DP_ADDR_SYSTEM_WIND_SET_HUM:
        {
            app_general_push_aircod_humidity(in_buff[0]);
            break;
        }   
        case DP_ADDR_SYSTEM_WIND_SET_SPEED:
        {
            app_general_push_aircod_fanSpeed((NewAirLevelSet_Def)in_buff[0]);
            break;
        }   
        case DP_ADDR_SYSTEM_WATER_SET_CLOD_TEMP:
        {
            app_general_push_set_cold_water_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            break;
        }   
        case DP_ADDR_SYSTEM_WATER_SET_HEAT_TEMP:
        {
            app_general_push_set_heat_water_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            break;
        }   
        case DP_ADDR_SYSTEM_WATER_SET_LIVING_TEMP:
        {
            app_general_push_set_living_water_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            break;
        }   
        case DP_ADDR_SYSTEM_MIXWATER_SET_CLOD_TEMP:
        {
            app_general_push_set_mixwater_cold_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            break;
        }   
        case DP_ADDR_SYSTEM_MIXWATER_SET_HEAT_TEMP:
        {
            app_general_push_set_mixwater_heat_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            break;
        }   
        case DP_ADDR_SYSTEM_MIXWATER_AI_ENABLE:
        {
            app_general_push_ai_enable_status(in_buff[0]);
            break;
        }   
        case DP_ADDR_SYSTEM_MIXWATER_LOW_TEMP_PROTECT:
        {
            app_general_push_mix_freeze_protect(in_buff[0]);
            break;
        }   
        case DP_ADDR_SYSTEM_MIXWATER_AI_DEST_TEMP:
        {
            app_general_push_ai_dest_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0])); 
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_NEW_AIR_PWM:
        {
            app_general_push_new_air_pwm_low(in_buff[0]);
            app_general_push_new_air_pwm_mid(in_buff[1]);
            app_general_push_new_air_pwm_high(in_buff[2]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_BACK_AIR_PWM:
        {
            app_general_push_back_air_pwm_low(in_buff[0]);
            app_general_push_back_air_pwm_mid(in_buff[1]);
            app_general_push_back_air_pwm_high(in_buff[2]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_OUTDOOR_WEATHER:
        {
            app_general_push_outdoor_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_outdoor_hum(in_buff[2]);
            app_general_push_adjust_outdoor_hum(pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_adjust_outdoor_temp(pbc_arrayToInt16u_bigEndian(&in_buff[5]));
            app_general_push_adjust_outdoor_co2(pbc_arrayToInt16u_bigEndian(&in_buff[7]));
            app_general_push_adjust_outdoor_pm25(pbc_arrayToInt16u_bigEndian(&in_buff[9]));
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_BEFORE_FU_WEATHER:
        {
            app_general_push_before_fu_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_before_fu_hum(in_buff[2]);
            app_general_push_adjust_beforfu_hum(pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_adjust_beforfu_temp(pbc_arrayToInt16u_bigEndian(&in_buff[5]));
            app_general_push_adjust_beforfu_co2(pbc_arrayToInt16u_bigEndian(&in_buff[7]));
            app_general_push_adjust_beforfu_pm25(pbc_arrayToInt16u_bigEndian(&in_buff[9]));
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_AFTER_FU_WEATHER:
        {
            app_general_push_after_fu_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_after_fu_hum(in_buff[2]);
            app_general_push_adjust_afterfu_hum(pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_adjust_afterfu_temp(pbc_arrayToInt16u_bigEndian(&in_buff[5]));
            app_general_push_adjust_afterfu_co2(pbc_arrayToInt16u_bigEndian(&in_buff[7]));
            app_general_push_adjust_afterfu_pm25(pbc_arrayToInt16u_bigEndian(&in_buff[9]));
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_BACK_AIR_WEATHER:
        {
            app_general_push_backair_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_backair_hum(in_buff[2]);
            app_general_push_backair_co2(pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_backair_pm25(pbc_arrayToInt16u_bigEndian(&in_buff[5]));
            app_general_push_adjust_backair_hum(pbc_arrayToInt16u_bigEndian(&in_buff[7]));
            app_general_push_adjust_backair_temp(pbc_arrayToInt16u_bigEndian(&in_buff[9]));
            app_general_push_adjust_backair_co2(pbc_arrayToInt16u_bigEndian(&in_buff[11]));
            app_general_push_adjust_backair_pm25(pbc_arrayToInt16u_bigEndian(&in_buff[13]));
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_EXHAST_AIR_WEATHER:
        {
            app_general_push_exhastair_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_exhastair_hum(in_buff[2]);
            app_general_push_adjust_exhastair_hum(pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_adjust_exhastair_temp(pbc_arrayToInt16u_bigEndian(&in_buff[5]));
            app_general_push_adjust_exhastair_co2(pbc_arrayToInt16u_bigEndian(&in_buff[7]));
            app_general_push_adjust_exhastair_pm25(pbc_arrayToInt16u_bigEndian(&in_buff[9]));
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_DEAD_ZONE:
        {
            app_general_push_aircod_setHum_deadZone(in_buff[0]);
            app_general_push_aircod_setTemp_deadZone(in_buff[1]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_OUT_VALVE:
        {
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_OUT_STATUS:
        {   
            app_general_push_anergy_need(in_buff[2]);
            app_general_push_reset_word(pbc_arrayToInt16u_bigEndian(&in_buff[5]));   //故障复位 
            app_general_push_wind_value(in_buff[9]);//风机切换 
            app_general_push_hotwater_enable(in_buff[10]);//热水使能 
            app_general_push_filter_time(pbc_arrayToInt16u_bigEndian(&in_buff[11]));   //更换周期 
            app_general_push_filter_usetime(pbc_arrayToInt16u_bigEndian(&in_buff[13]));   //使用周期
            app_general_push_debug_enable(in_buff[15]); 
            app_general_push_main_control_method(in_buff[16]);
            app_general_push_cold_no_need_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[17]));  
            app_general_push_cold_fan_need_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[19]));  
            app_general_push_cold_warm_need_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[21]));  
            app_general_push_config_lew_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[23])); 
            app_general_push_heat_no_need_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[25]));  
            app_general_push_heat_fan_need_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[27]));  
            app_general_push_heat_warm_need_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[29]));  
            app_general_push_config_back_wind_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[31]));
            app_general_push_config_hum_set(pbc_arrayToInt16u_bigEndian(&in_buff[33]));  
            app_general_push_cold_wind_max_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[35]));  
            app_general_push_heat_wind_min_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[37]));  
            app_general_push_heat_wind_max_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[39]));
            app_general_push_indoor_dehum_status(in_buff[41]);
            app_general_push_water_machine_status(in_buff[42]);
            break;
        } 
        case DP_ADDR_SYSTEM_LIS_MIXWATER_OUT:
        {
            app_general_push_pump_output(in_buff[0]);
            app_general_push_three_vavle_output(in_buff[1]);
            app_push_low_protect_reguest(in_buff[2]);
            app_general_push_ac_error_word(pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_push_system_energy_need(in_buff[5]);
            app_general_push_max_lew_temp(pbc_arrayToInt16u_bigEndian(&in_buff[6]));
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_MAIN_MACHINE_TEMP:
        {
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_MIXWATER_TEMP:
        {
            app_general_push_in_water_measure_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_back_water_measure_temp(pbc_arrayToInt16u_bigEndian(&in_buff[2]));
            app_general_push_mix_water_measure_temp(pbc_arrayToInt16u_bigEndian(&in_buff[4]));
            break;
        }      
        case  DP_ADDR_SYSTEM_LIS_RTC:
        {
            realTime_t* rtc;
            rtc = app_real_time_pull_rtc();
            rtc->second = in_buff[0];
            rtc->minute= in_buff[1];
            rtc->hour= in_buff[2];
            rtc->week= in_buff[3];
            rtc->day= in_buff[4];
            rtc->month= in_buff[5];
            rtc->year= in_buff[6];
			app_push_once_save_write_rtc();
            //app_real_time_push_rtc(rtc);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_485_PAREMETER:
        {
            break;
        }  
        case DP_ADDR_WRITE_DEVICE_ID:
        {
            if((in_buff[0] == ((uint8_t)(DEVICE_KEY>>24))) && 
                (in_buff[1] == ((uint8_t)(DEVICE_KEY>>16))) &&
                (in_buff[2] == ((uint8_t)(DEVICE_KEY>>8)))&& 
                (in_buff[3] == ((uint8_t)(DEVICE_KEY))))
            {
                uint8_t *local_addr;
                local_addr = app_pull_local_id(); 
                local_addr[0] = in_buff[4];
                local_addr[1] = in_buff[5];
                local_addr[2] = in_buff[6];
                local_addr[3] = in_buff[7];
                local_addr[4] = in_buff[8];
                local_addr[5] = in_buff[9];
                app_push_once_save_sto_parameter();
            }
            break;
        }   
		case DP_ADDR_SYSTEM_AIRCOD_COLD_BACK_WATER:
		{//制冷回水
			app_general_push_coolbackwater_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
			app_general_push_hotbackwater_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
			break;
		}
		case DP_ADDR_SYSTEM_AIRCOD_WARM_BACK_WATER:
		{//制热回水			
			break;
		}
        default:
        {
            break;
        }              
    }
}

typedef struct
{
    uint8_t  blockNum;//块数量
    uint8_t  padNumber;//末端号
    uint16_t regAddr[MAX_DATA_POINT_LEN];//寄存器地址
    uint8_t  control_answer;//应答控制
}synBlock_t;

void app_master_slave_send_syn_block(uint8_t in_solidNum,uint8_t *in_dest_addr,synBlock_t in_block)
{
    bgk_comm_buff_def* tempLinkData;
    tempLinkData = pull_bough_message_pBuff(in_solidNum);
    tempLinkData->ProcotolType = PROTOL_SYN;
    tempLinkData->LinkDstAddr[0] = in_dest_addr[0];
    tempLinkData->LinkDstAddr[1] = in_dest_addr[1];
    tempLinkData->LinkDstAddr[2] = in_dest_addr[2];
    tempLinkData->LinkDstAddr[3] = in_dest_addr[3];
    tempLinkData->LinkDstAddr[4] = in_dest_addr[4];
    tempLinkData->LinkDstAddr[5] = in_dest_addr[5];
    uint8_t *local_addr;
    local_addr = app_pull_local_id();
    tempLinkData->LinkSrcAddr[0] = local_addr[0];
    tempLinkData->LinkSrcAddr[1] = local_addr[1];
    tempLinkData->LinkSrcAddr[2] = local_addr[2];
    tempLinkData->LinkSrcAddr[3] = local_addr[3];
    tempLinkData->LinkSrcAddr[4] = local_addr[4];
    tempLinkData->LinkSrcAddr[5] = local_addr[5];

    uint32_t stamp;
    uint8_t i = 0;
    uint8_t startIndex = 0;
    uint8_t blockLen = 0;

    tempLinkData->Payload[0] = PROTOL_VERSION;
    tempLinkData->Payload[1] = in_block.control_answer;
    tempLinkData->Payload[2] = 0x00;//预留
    switch(in_block.control_answer)
    {
        case 0x00:
        {
            tempLinkData->Payload[3] = in_block.blockNum;//块数量
            startIndex = 4;
            tempLinkData->PayloadLength = 4;
            for(i = 0; i < in_block.blockNum;i++)
            {
                if(in_block.regAddr[i] >= DP_ADDR_START)
                {
                    stamp = app_general_pull_system_dp_stamp(in_block.regAddr[i]);     
                    tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                    tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                    tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                    tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                    tempLinkData->Payload[startIndex+4] = (dpPadLen[(in_block.regAddr[i]-DP_ADDR_START)] + 3);
                    tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr[i]>>8);
                    tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr[i]);
                    app_pull_data_point_message(in_block.regAddr[i],&tempLinkData->Payload[startIndex+7]);
                    blockLen = (7+dpPadLen[(in_block.regAddr[i]-DP_ADDR_START)]);
                    tempLinkData->PayloadLength += blockLen;
                    startIndex += blockLen;
                }
            }
            push_active_one_message_transmit(in_solidNum,false);
            break;
        }
        case 0x01:
        {
            tempLinkData->Payload[3] = in_block.blockNum;//块数量
            startIndex = 4;
            tempLinkData->PayloadLength = 4;
            for(i = 0; i < in_block.blockNum;i++)
            {
                if(in_block.regAddr[i] >= DP_ADDR_START)
                {
                    stamp = app_general_pull_system_dp_stamp(in_block.regAddr[i]);     
                    tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                    tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                    tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                    tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                    tempLinkData->Payload[startIndex+4] = (dpPadLen[(in_block.regAddr[i]-DP_ADDR_START)] + 3);
                    tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr[i]>>8);
                    tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr[i]);
                    app_pull_data_point_message(in_block.regAddr[i],&tempLinkData->Payload[startIndex+7]);
                    blockLen = (7+dpPadLen[(in_block.regAddr[i]-DP_ADDR_START)]);
                    tempLinkData->PayloadLength += blockLen;
                    startIndex += blockLen;
                }           
            }
            push_active_one_message_transmit(in_solidNum,false);
            break;
        }
        case 0x41:
        {
            tempLinkData->Payload[3] = 0;
            tempLinkData->PayloadLength = 4;
            push_active_one_message_transmit(in_solidNum,false);
            break;
        }
        case 0x81:
        {
            tempLinkData->Payload[3] = in_block.blockNum;//块数量
            startIndex = 4;
            tempLinkData->PayloadLength = 4;
            for(i = 0; i < in_block.blockNum;i++)
            {
                if(in_block.regAddr[i] >= DP_ADDR_START)
                {
                    stamp = app_general_pull_system_dp_stamp(in_block.regAddr[i]);     
                    tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                    tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                    tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                    tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                    tempLinkData->Payload[startIndex+4] = (dpPadLen[(in_block.regAddr[i]-DP_ADDR_START)] + 3);
                    tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr[i]>>8);
                    tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr[i]);
                    app_pull_data_point_message(in_block.regAddr[i],&tempLinkData->Payload[startIndex+7]);
                    blockLen = (7+dpPadLen[(in_block.regAddr[i]-DP_ADDR_START)]);
                    tempLinkData->PayloadLength += blockLen;
                    startIndex += blockLen;
                }            
            }
            push_active_one_message_transmit(in_solidNum,false);
            break;
        }
        default:
        {
            break;
        }
    }
}


bool _syn_pull_local_id(uint8_t *in_deviceId)
{
    uint8_t *local_addr;
   local_addr = app_pull_local_id(); 
    if((in_deviceId[0] == local_addr[0])&&\
        (in_deviceId[1] == local_addr[1])&&\
        (in_deviceId[2] == local_addr[2])&&\
        (in_deviceId[3] == local_addr[3])&&\
        (in_deviceId[4] == local_addr[4])&&\
        (in_deviceId[5] == local_addr[5]))
    {
        return true;
    }
    return false;
}

bool _syn_pull_write_device_id(uint8_t *in_deviceId)
{
    if((in_deviceId[0] == deviceid_addr[0])&&\
        (in_deviceId[1] == deviceid_addr[1])&&\
        (in_deviceId[2] == deviceid_addr[2])&&\
        (in_deviceId[3] == deviceid_addr[3])&&\
        (in_deviceId[4] == deviceid_addr[4])&&\
        (in_deviceId[5] == deviceid_addr[5]))
    {
        return true;
    }
    return false;
}

bool _syn_pull_type_cc_online(void)
{
    uint8_t i = 0;
    linkDeviceList_t* logList;
    logList = app_link_log_pull_device_list(SYSTEM_MASTER);
    for(i = 0; i < MAX_DEVICE_NUM;i++)
    {
        if(logList[i].onlineFlag)
        {
            if(logList[i].deviceType == DEVICE_TYPE_CC)
            {
                return true;
            }
        }
    }
    return false;
}

uint8_t* _syn_pull_type_cc_id(void)
{
    uint8_t i = 0;
    linkDeviceList_t* logList;
    logList = app_link_log_pull_device_list(SYSTEM_MASTER);
    for(i = 0; i < MAX_DEVICE_NUM;i++)
    {
        if(logList[i].onlineFlag)
        {
            if(logList[i].deviceType == DEVICE_TYPE_CC)
            {
                return &logList[i].DeviceID[0];
            }
        }
    }
    return 0;
}


void _master_syn_task(void)
{//输配同步任务
    synStatus_def mainSynStatsu_backup;
    static synBlock_t  synBlock;
    static uint8_t failCount = 0;
    uint16_t regAdd = 0;
    uint8_t startIndex = 0;
    uint8_t blockLen = 0;
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t blockNum = 0;
    uint32_t receiveStamp = 0;
    static uint8_t list_port = 0;
    uint32_t occupyWord_backup;
    pbc_timerMillRun_task(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay);//接收超时
    pbc_timerMillRun_task(&appModbusSyn[SYSTEM_MASTER].roll_back_delay);//发送回退
    pbc_timerMillRun_task(&appModbusSyn[SYSTEM_MASTER].answer_delay);//响应延时
    pbc_timerClockRun_task(&appModbusSyn[SYSTEM_MASTER].timing_send_dalay);//定时发送
    do
    {
        mainSynStatsu_backup = appModbusSyn[SYSTEM_MASTER].mainSynStatsus;
        switch(appModbusSyn[SYSTEM_MASTER].mainSynStatsus)
        {
            case SYN_STATUS_IDLE:
            {
                if(appModbusSyn[SYSTEM_MASTER].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_MASTER].receiveOneMessage = false;
                    if(_syn_pull_write_device_id(&appModbusSyn[SYSTEM_MASTER].in_rev_data->LinkDstAddr[0]))
                    {
                        regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[9]);
                        app_push_data_point_message(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[11]); 
                        synBlock.control_answer = 0x41; 
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_ANSWER;
                        pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].answer_delay,ANSWER_DELAY);
                    }
                }
                break;
            }
            case SYN_STATUS_WAIT_RECEIVE:
            {//等待接收
                if(appModbusSyn[SYSTEM_MASTER].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_MASTER].receiveOneMessage = false;
					if(appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[3] != 0x00)
					{
						if(_syn_pull_local_id(&appModbusSyn[SYSTEM_MASTER].in_rev_data->LinkDstAddr[0]))
						{//自己地址
							blockNum = appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[3];//数据块
							synBlock.blockNum = 0;
							startIndex = 4;
							for(j = 0;j < blockNum;j++)
							{
								regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+5]);
								receiveStamp = pbc_arrayToInt32u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex]);//发起方时间戳  
								if(receiveStamp >= app_general_pull_system_dp_stamp(regAdd))
								{//压入数据
									app_general_push_system_dp_stamp(regAdd,receiveStamp);
									occupyWord_backup =  appModbusSyn[SYSTEM_MASTER].updataWord; //保存现场 
									app_push_data_point_message(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+7]);     
									appModbusSyn[SYSTEM_MASTER].updataWord =   occupyWord_backup;//恢复现场
								}
								else
								{                           
									synBlock.regAddr[synBlock.blockNum] = regAdd;
									synBlock.blockNum++;
								} 
								blockLen = (appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+4]+4);   //数据长度  
								startIndex += blockLen;            
							} 
							if(appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[1] == 0x01)
							{
								if(synBlock.blockNum)
								{
									synBlock.control_answer = 0x81;
								}
								else
								{
									synBlock.control_answer = 0x41;    
								} 
								appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_ANSWER;
								pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].answer_delay,ANSWER_DELAY);
							}
							
						}
                        else if(_syn_pull_write_device_id(&appModbusSyn[SYSTEM_MASTER].in_rev_data->LinkDstAddr[0]))
                        {
                            regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[9]);
                            app_push_data_point_message(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[11]); 
                            synBlock.control_answer = 0x41; 
                            appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_ANSWER;
							pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].answer_delay,ANSWER_DELAY);
                        }
					}                  
                }
                else if(appModbusSyn[SYSTEM_MASTER].updataWord)
                {//更新字
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_SEND_UPDATA_ACTIVE;
                }
                else if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_MASTER].timing_send_dalay))
                {//定时发送字
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].timing_send_dalay,TIMING_SEND_COUNT);
                    if(appModbusSyn[SYSTEM_MASTER].timingSendWord)
                    {

                    }
                    else
                    {//分6块发送                   
                        appModbusSyn[SYSTEM_MASTER].timingSendWord = 0x3f;
                    }
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND_ACTIVE;
                }
                break;
            }
            case SYN_STATUS_ANSWER:
            {//响应
                if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_MASTER].answer_delay))
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                }
                else
                {
                    if(pull_bough_link_is_busy(SYSTEM_MASTER))
                    {//忙碌先释放
                        
                    }
                    else
                    {
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_ANSWER_RESULT; 
                        app_master_slave_send_syn_block(SYSTEM_MASTER,&appModbusSyn[SYSTEM_MASTER].in_rev_data->LinkSrcAddr[0],synBlock);
                    }     
                }       
                break;
            }
            case SYN_STATUS_ANSWER_RESULT:
            {//响应结果
                if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                }
                else if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_conflict)
                {//冲突报文
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_ANSWER;
                }
                else if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_error)
                {//未知错误
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_ANSWER;
                }          
                break;
            }
            case SYN_STATUS_SEND_UPDATA_ACTIVE:
            {
                if(app_link_request_transmit_activation_request(SYSTEM_MASTER))
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_SEND_UPDATA_ACTIVE_RESULT;
                }  
                else
                {
                   
                }   
                break;
            }
            case SYN_STATUS_SEND_UPDATA_ACTIVE_RESULT:
            {
                if(TRANSMIT_RESULT_FAIL == app_link_request_get_transmit_result(SYSTEM_MASTER))
                {//发送失败
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_SEND_UPDATA_ACTIVE;  
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                } 
                else if(TRANSMIT_RESULT_SUCCESS == app_link_request_get_transmit_result(SYSTEM_MASTER))
                {//发送成功
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_SEND_UPDATA_WORD; 
                    failCount = 0;
                }  
                break;
            }
            case SYN_STATUS_SEND_UPDATA_WORD:
            {
                synBlock.blockNum = 0;
                for(j = 0; j < MAX_DATA_POINT_LEN;j++)
                {
                    if(appModbusSyn[SYSTEM_MASTER].updataWord & (0x01<<j))
                    {
                        app_general_push_system_dp_stamp((j+DP_ADDR_START),pbc_timeStamp_get_stamp());
                        synBlock.regAddr[synBlock.blockNum] = (j+DP_ADDR_START);
                        synBlock.blockNum++;                              
                    }
                }
                synBlock.control_answer = 0x01;
                synBlock.padNumber = i;
                app_master_slave_send_syn_block(SYSTEM_MASTER,_syn_pull_type_cc_id(),synBlock);
                appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_SEND_UPDATA_WORD_RESULT;
                break;
            }
            case SYN_STATUS_SEND_UPDATA_WORD_RESULT:
            {
                if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RECEIVE_UPDATA_WORD;
                    failCount = 0;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay,RECEIVE_TIMEOUT);
                }
                else if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_conflict)
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_SEND_UPDATA_WORD_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                else if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_error)
                {//冲突报文或者未知错误
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_SEND_UPDATA_WORD_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                break;
            }
            case SYN_STATUS_RECEIVE_UPDATA_WORD:
            {
                if(appModbusSyn[SYSTEM_MASTER].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_MASTER].receiveOneMessage = false;
                    blockNum = appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[3];//数据块
                    synBlock.blockNum = 0;
                    startIndex = 4;
                    for(j = 0;j < blockNum;j++)
                    {
                        regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+5]);
						receiveStamp = pbc_arrayToInt32u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex]);//发起方时间戳  
                        if(receiveStamp >= app_general_pull_system_dp_stamp(regAdd))
                        {//压入数据
                            app_general_push_system_dp_stamp(regAdd,receiveStamp);
                            occupyWord_backup =  appModbusSyn[SYSTEM_MASTER].updataWord; //保存现场 
                            app_push_data_point_message(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+7]);     
                            appModbusSyn[SYSTEM_MASTER].updataWord =   occupyWord_backup;//恢复现场
                        }
                        else
                        {                           
                            synBlock.regAddr[synBlock.blockNum] = regAdd;
                            synBlock.blockNum++;
                        } 
                        blockLen = (appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+4]+4);   //数据长度  
                        startIndex += blockLen;            
                    } 
                    appModbusSyn[SYSTEM_MASTER].updataWord = 0;
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE; 
                    
                }
                else if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay))
                {//接收超时
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_ACTIVE;
                }
                break;
            }
            case SYN_STATUS_SEND_UPDATA_WORD_ROLL_BACK:
            {
                if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_MASTER].roll_back_delay))
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_SEND_UPDATA_WORD;;
                }
                break;
            }
            case SYN_STATUS_RESEND_UPDATA_ACTIVE:
            {
                if(app_link_request_transmit_activation_request(SYSTEM_MASTER))
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_ACTIVE_RESULT;
                }  
                else
                {
                  
                }   
                break;
            }
            case SYN_STATUS_RESEND_UPDATA_ACTIVE_RESULT:
            {
                if(TRANSMIT_RESULT_FAIL == app_link_request_get_transmit_result(SYSTEM_MASTER))
                {//发送失败
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_ACTIVE;  
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                } 
                else if(TRANSMIT_RESULT_SUCCESS == app_link_request_get_transmit_result(SYSTEM_MASTER))
                {//发送成功
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD; 
                    failCount = 0;
                }  
                break;
            }
             case SYN_STATUS_RESEND_UPDATA_WORD:
            {
                synBlock.blockNum = 0;
                for(j = 0; j < MAX_DATA_POINT_LEN;j++)
                {
                    if(appModbusSyn[SYSTEM_MASTER].updataWord & (0x01<<j))
                    {
                        app_general_push_system_dp_stamp((j+DP_ADDR_START),pbc_timeStamp_get_stamp());
                        synBlock.regAddr[synBlock.blockNum] =  (j+DP_ADDR_START);
                        synBlock.blockNum++;                              
                    }
                }
                synBlock.control_answer = 0x01;
                synBlock.padNumber = i;
                app_master_slave_send_syn_block(SYSTEM_MASTER,_syn_pull_type_cc_id(),synBlock);
                appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD_RESULT;
                break;
            }
            case SYN_STATUS_RESEND_UPDATA_WORD_RESULT:
            {
                if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RERECEIVE_UPDATA_WORD;
                    failCount = 0;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay,RECEIVE_TIMEOUT);
                }
                else if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_conflict)
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                else if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_error)
                {//冲突报文或者未知错误
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                break;
            }
            case SYN_STATUS_RERECEIVE_UPDATA_WORD:
            {
                if(appModbusSyn[SYSTEM_MASTER].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_MASTER].receiveOneMessage = false;
                    if(_syn_pull_local_id(&appModbusSyn[SYSTEM_MASTER].in_rev_data->LinkDstAddr[0])) 
                    {
                        blockNum = appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[3];//数据块
                        synBlock.blockNum = 0;
                        startIndex = 4;
                        for(j = 0;j < blockNum;j++)
                        {
                            regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+5]);
                            receiveStamp = pbc_arrayToInt32u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex]);//发起方时间戳  
                            if(receiveStamp >= app_general_pull_system_dp_stamp(regAdd))
                            {//压入数据
                                app_general_push_system_dp_stamp(regAdd,receiveStamp);
                                occupyWord_backup =  appModbusSyn[SYSTEM_MASTER].updataWord; //保存现场 
                                app_push_data_point_message(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+7]);     
                                appModbusSyn[SYSTEM_MASTER].updataWord =   occupyWord_backup;//恢复现场
                            }
                            else
                            {                           
                                synBlock.regAddr[synBlock.blockNum] = regAdd;
                                synBlock.blockNum++;
                            } 
                            blockLen = (appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+4]+4);   //数据长度  
                            startIndex += blockLen;            
                        } 
                    }        
                    appModbusSyn[SYSTEM_MASTER].updataWord = 0;
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE; 
                    
                }
                else if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay))
                {//接收超时
					appModbusSyn[SYSTEM_MASTER].updataWord = 0;
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                }
                break;
            }
            case SYN_STATUS_RESEND_UPDATA_WORD_ROLL_BACK:
            {
                if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_MASTER].roll_back_delay))
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD;
                }
                break;
            }
            case SYN_STATUS_TIMING_SEND_ACTIVE:
            {
               if(app_link_request_transmit_activation_request(SYSTEM_MASTER))
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND_ACTIVE_RESULT;
                }  
                else
                {
                   
                }   
                break;
            }
            case SYN_STATUS_TIMING_SEND_ACTIVE_RESULT:
            {
                if(TRANSMIT_RESULT_FAIL == app_link_request_get_transmit_result(SYSTEM_MASTER))
                {//发送失败
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND_ACTIVE;  
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                } 
                else if(TRANSMIT_RESULT_SUCCESS == app_link_request_get_transmit_result(SYSTEM_MASTER))
                {//发送成功
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND; 
                    failCount = 0;
                }  
                break;
            }
            case SYN_STATUS_TIMING_SEND:
            {
                if(pull_bough_link_is_busy(SYSTEM_MASTER))
                {
                   
                }
                else
                {
                    for(i = 0;i < 16;i++)
                    {
                        if(appModbusSyn[SYSTEM_MASTER].timingSendWord & (0x01<<i))
                        {
                            if(i == 0)
                            {
                                synBlock.blockNum = TIMING_SEND_BLOCK1_NUM;
                                for(j = 0;j < synBlock.blockNum;j++)
                                {
                                   
                                    synBlock.regAddr[j] = (j+DP_ADDR_START);
                                }
                            }
                            else if(i == 1)
                            {
                                synBlock.blockNum = TIMING_SEND_BLOCK2_NUM;
                                for(j = 0;j < synBlock.blockNum;j++)
                                {
                                   
                                    synBlock.regAddr[j] = (j+DP_ADDR_START+TIMING_SEND_BLOCK1_NUM);
                                }
                            }
                            else if(i == 2)
                            {
                                synBlock.blockNum = TIMING_SEND_BLOCK3_NUM;
                                for(j = 0;j < synBlock.blockNum;j++)
                                {
                                  
                                    synBlock.regAddr[j] = (j+DP_ADDR_START+TIMING_SEND_BLOCK1_NUM+TIMING_SEND_BLOCK2_NUM);
                                }
                            }
							else if(i == 3)
							{
								synBlock.blockNum = 1;
								synBlock.regAddr[0] = DP_ADDR_SYSTEM_AIRCOD_READ_ONLY_PAREMETER;
							}
							else if(i == 4)
							{
								synBlock.blockNum = 1;
								synBlock.regAddr[0] = DP_ADDR_SYSTEM_AIRCOD_READ_WRITE_PAREMETER;
							}
							else if(i == 5)
							{
								synBlock.blockNum = 1;
								synBlock.regAddr[0] = DP_ADDR_SYSTEM_AIRCOD_COLD_BACK_WATER;
							}
                            synBlock.control_answer = 0x01;
                            synBlock.padNumber = i;
                            list_port = i;
                            app_master_slave_send_syn_block(SYSTEM_MASTER,_syn_pull_type_cc_id(),synBlock);
                            appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND_RESULT;
                            break;
                        }
                    }
                }
                break;
            }
            case SYN_STATUS_TIMING_SEND_RESULT:
            {
                if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RECEIVE_TIMING;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay,RECEIVE_TIMEOUT);
                    failCount = 0;
                }
                else if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_conflict)
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                else if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_error)
                {//冲突报文或者未知错误
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                break;
            }
            case SYN_STATUS_TIMING_SEND_ROLL_BACK:
            {
                if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_MASTER].roll_back_delay))
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND;;
                }
                break;
            }
            case SYN_STATUS_RECEIVE_TIMING:
            {
                if(appModbusSyn[SYSTEM_MASTER].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_MASTER].receiveOneMessage = false;
                    if(_syn_pull_local_id(&appModbusSyn[SYSTEM_MASTER].in_rev_data->LinkDstAddr[0])) 
                    {//自己地址
                        blockNum = appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[3];//数据块
						if(blockNum != 0)
						{
							synBlock.blockNum = 0;
							startIndex = 4;
							for(j = 0;j < blockNum;j++)
							{
								regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+5]);
								receiveStamp = pbc_arrayToInt32u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex]);//发起方时间戳  
								if(receiveStamp >= app_general_pull_system_dp_stamp(regAdd))
								{//压入数据
									app_general_push_system_dp_stamp(regAdd,receiveStamp);
									occupyWord_backup =  appModbusSyn[SYSTEM_MASTER].updataWord; //保存现场 
									app_push_data_point_message(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+7]);     
									appModbusSyn[SYSTEM_MASTER].updataWord =   occupyWord_backup;//恢复现场
								}
								else
								{                           
									synBlock.regAddr[synBlock.blockNum] = regAdd;
									synBlock.blockNum++;
								} 
								blockLen = (appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+4]+4);   //数据长度  
								startIndex += blockLen;            
							} 
						}                      
                        appModbusSyn[SYSTEM_MASTER].timingSendWord &=  (~0x01<<list_port); 
                        if(appModbusSyn[SYSTEM_MASTER].timingSendWord == 0)
                        {
                            appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                            appModbusSyn[SYSTEM_MASTER].updataWord = 0;
                        }   
                        else
                        {
                            appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND_ACTIVE;
                        }
                                                    
                    }
                }
                else if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay))
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_RESEND_ACTIVE;
                }
                break;
            }
            case SYN_STATUS_TIMING_RESEND_ACTIVE:
            {
                if(app_link_request_transmit_activation_request(SYSTEM_MASTER))
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_RESEND_ACTIVE_RESULT;
                }  
                else
                {
                
                }   
                break;
            }
            case SYN_STATUS_TIMING_RESEND_ACTIVE_RESULT:
            {
                if(TRANSMIT_RESULT_FAIL == app_link_request_get_transmit_result(SYSTEM_MASTER))
                {//发送失败
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_RESEND_ACTIVE;  
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                } 
                else if(TRANSMIT_RESULT_SUCCESS == app_link_request_get_transmit_result(SYSTEM_MASTER))
                {//发送成功
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_RESEND;
                    failCount = 0;
                }  
                break;
            }
            case SYN_STATUS_TIMING_RESEND:
            {
                if(pull_bough_link_is_busy(SYSTEM_MASTER))
                {
                   
                }
                else
                {
                    for(i = 0;i < 16;i++)
                    {
                        if(appModbusSyn[SYSTEM_MASTER].timingSendWord & (0x01<<i))
                        {
                            if(i == 0)
                            {
                                synBlock.blockNum = TIMING_SEND_BLOCK1_NUM;
                                for(j = 0;j < synBlock.blockNum;j++)
                                {
                                    synBlock.regAddr[j] = (j+DP_ADDR_START);
                                }
                            }
                            else if(i == 1)
                            {
                                synBlock.blockNum = TIMING_SEND_BLOCK2_NUM;
                                for(j = 0;j < synBlock.blockNum;j++)
                                {
                                    synBlock.regAddr[j] = (j+DP_ADDR_START+TIMING_SEND_BLOCK1_NUM);
                                }
                            }
                            else if(i == 2)
                            {
                                synBlock.blockNum = TIMING_SEND_BLOCK3_NUM;
                                for(j = 0;j < synBlock.blockNum;j++)
                                {
                                    synBlock.regAddr[j] = (j+DP_ADDR_START+TIMING_SEND_BLOCK1_NUM+TIMING_SEND_BLOCK2_NUM);
                                }
                            }
							else if(i == 3)
							{
								synBlock.blockNum = 1;
								synBlock.regAddr[0] = DP_ADDR_SYSTEM_AIRCOD_READ_ONLY_PAREMETER;
							}
							else if(i == 4)
							{
								synBlock.blockNum = 1;
								synBlock.regAddr[0] = DP_ADDR_SYSTEM_AIRCOD_READ_WRITE_PAREMETER;
							}
							else if(i == 5)
							{
								synBlock.blockNum = 1;
								synBlock.regAddr[0] = DP_ADDR_SYSTEM_AIRCOD_COLD_BACK_WATER;
							}
                            synBlock.control_answer = 0x01;
                            synBlock.padNumber = i;
                            list_port = i;
                            app_master_slave_send_syn_block(SYSTEM_MASTER,_syn_pull_type_cc_id(),synBlock);
                            appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND_RESULT;
                            break;
                        }
                    }
                }
                break;
            }
            case SYN_STATUS_TIMING_RESEND_RESULT:
            {
                if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RERECEIVE_TIMING;
                    failCount = 0;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay,RECEIVE_TIMEOUT);
                }
                else if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_conflict)
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_RESEND_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                else if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_error)
                {//冲突报文或者未知错误
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_RESEND_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                break;
            }
            case SYN_STATUS_RERECEIVE_TIMING:
            {
               if(appModbusSyn[SYSTEM_MASTER].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_MASTER].receiveOneMessage = false;
                    if(_syn_pull_local_id(&appModbusSyn[SYSTEM_MASTER].in_rev_data->LinkDstAddr[0])) 
                    {//自己地址
                        appModbusSyn[SYSTEM_MASTER].timingSendWord &=  (~0x01<<list_port); 
                        blockNum = appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[3];//数据块
                        synBlock.blockNum = 0;
                        startIndex = 4;
                        for(j = 0;j < blockNum;j++)
                        {
                            regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+5]);
							receiveStamp = pbc_arrayToInt32u_bigEndian(&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex]);//发起方时间戳  
                            if(receiveStamp >= app_general_pull_system_dp_stamp(regAdd))
                            {//压入数据
                                app_general_push_system_dp_stamp(regAdd,receiveStamp);
                                occupyWord_backup =  appModbusSyn[SYSTEM_MASTER].updataWord; //保存现场 
                                app_push_data_point_message(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+7]);     
                                appModbusSyn[SYSTEM_MASTER].updataWord =   occupyWord_backup;//恢复现场
                            }
                            else
                            {                           
                                synBlock.regAddr[synBlock.blockNum] = regAdd;
                                synBlock.blockNum++;
                            } 
                            blockLen = (appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+4]+4);   //数据长度  
                            startIndex += blockLen;            
                        } 
                        if(appModbusSyn[SYSTEM_MASTER].timingSendWord == 0)
                        {
                            appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                        }   
                        else
                        {
                            appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND_ACTIVE;
                        }                                             
                    }                                           
                }
                else if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay))
                {
                    appModbusSyn[SYSTEM_MASTER].timingSendWord &=  (~0x01<<list_port); 
                    if(appModbusSyn[SYSTEM_MASTER].timingSendWord == 0)
                    {
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }   
                    else
                    {
                        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_SEND_ACTIVE;
                    }           
                }
                
                break;
            }
            case SYN_STATUS_TIMING_RESEND_ROLL_BACK:
            {
                if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_MASTER].roll_back_delay))
                {
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_TIMING_RESEND;
                }
                break;
            }
            default:
            {
                break;
            }
        }
    } while (mainSynStatsu_backup != appModbusSyn[SYSTEM_MASTER].mainSynStatsus);  
}

void app_link_syn_task(void)
{
    static bool cfg = false;
    static bool lastOnlineFlag = false;
    if(cfg)
    {    
        if(_syn_pull_type_cc_online() && app_link_log_pull_local_device_online(SYSTEM_MASTER))
        {   
            _master_syn_task();			
            if(lastOnlineFlag == false)
            {
                lastOnlineFlag = true;
                appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
            }
        }
        else
        {
            appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_IDLE;
			lastOnlineFlag = false;
            pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].timing_send_dalay,2);
        }      
    }
    else
    {
        cfg = true;
        appModbusSyn[SYSTEM_MASTER].timing_send_dalay.timStatusBits = timerType_second;
        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_IDLE;
    } 
}

void app_link_syn_push_receive_data(uint8_t in_solidNum,bgk_comm_buff_def *in_rev_data)
{
    if(in_solidNum == SYSTEM_MASTER)
    {
        appModbusSyn[in_solidNum].in_rev_data = in_rev_data;
        appModbusSyn[in_solidNum].receiveOneMessage = true;
        _master_syn_task();
    } 
}

void app_link_syn_push_outside_updata_word(uint8_t in_solidNum,uint32_t in_updataWord)
{
    if(in_solidNum == SYSTEM_MASTER)
    {
        if(_syn_pull_type_cc_online())
        {
            appModbusSyn[in_solidNum].updataWord |= in_updataWord;
        }
    }   
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++