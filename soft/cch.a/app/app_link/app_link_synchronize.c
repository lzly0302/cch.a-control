//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "..\app_cfg.h"
#include "stdlib.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
    SYN_STATUS_SEND_LIST_ACTIVE,                  //发送列表激活
    SYN_STATUS_SEND_LIST_ACTIVE_RESULT,           //激活结果
    SYN_STATUS_SEND_LIST,                         //发送列表
    SYN_STATUS_SEND_LIST_RESULT,                  //发送列表结果 
    SYN_STATUS_SEND_LIST_ROLL_BACK,              //发送更新帧回退  
    SYN_STATUS_RECEIVE_LIST,                      //接收结果 
    SYN_STATUS_RESEND_LIST_ACTIVE,                //重发发送列表激活
    SYN_STATUS_RESEND_LIST_ACTIVE_RESULT,         //重发激活结果
    SYN_STATUS_RESEND_LIST,                       //重发发送列表
    SYN_STATUS_RESEND_LIST_RESULT,               //重发发送列表结果 
    SYN_STATUS_RESEND_LIST_ROLL_BACK,             //发送更新帧回退   
    SYN_STATUS_RERECEIVE_LIST,                   //重发接收结果    
}synStatus_def;

uint32_t        padOccupyWord[MASTER_PAD_NUM];   //末端抢占字
uint32_t        dhmOccupyWord[MASTER_DHM_NUM];//除湿机抢占字


uint8_t deviceid_addr[6]={0xaa,0xaa,0xaa,0xaa,0xaa,0xaa};//写入设备ID时用的地址
#define  DEVICE_KEY 0XFA3456AF//写入设备密匙
const uint8_t dpPadLen_pad[MAX_DATA_POINT_LEN_PAD] = {1,2,2,1,1,1,4,10,5,32,14,7,4,4,6};//面板数据点长度
const uint8_t dpPadLen_hm[MAX_DATA_POINT_LEN_DHM]  = {1,1,1,1,1,6,3,3,7,7,7,15,7,7,4};//除湿模块数据点长度
const uint8_t dpPadLen_system[MAX_DATA_POINT_LEN_SYSTEM] = {1,1,2,2,1,1,2,2,2,2,2,1,1,2,3,3,11,11,11,15,11,2,10,43,8,6,6,7,4,168,148,4};//系统数据点长度


typedef struct
{
    synStatus_def   mainSynStatsus;       //主同步状态
    uint32_t        updataWord;           //更新字
    uint16_t        listWord;             //列表字
    bgk_comm_buff_def *in_rev_data;       //收到数据
    bool              receiveOneMessage;  //收到一帧数据
    timerClock_def    receive_timeout_delay;//接收超时
    timerClock_def    roll_back_delay;    //回退延时
    timerClock_def    answer_delay;       //应答延时
}msComm_t;

typedef struct
{
    uint8_t  blockNum;//块数量
    uint8_t  padNumber;//末端号
    uint16_t regAddr_pad[MAX_DATA_POINT_LEN_PAD];//寄存器地址
    uint16_t regAddr_system[MAX_DATA_POINT_LEN_SYSTEM];//寄存器地址
    uint8_t  control_answer;//应答控制
}synBlock_t;

msComm_t appModbusSyn[MAX_MODBUS_NUM];
/*系统集成信息*/
void app_pull_data_point_message_sys(uint16_t in_dpAddr,uint8_t *out_buff)
{//系统集成信息
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
            pbc_int16uToArray_bigEndian(app_general_pull_outdoor_temp(),&out_buff[0]);
            out_buff[2] = app_general_pull_outdoor_hum();
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_outdoor_hum(),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_outdoor_temp(),&out_buff[5]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_outdoor_co2(),&out_buff[7]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_outdoor_pm25(),&out_buff[9]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_BEFORE_FU_WEATHER:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_before_fu_temp(),&out_buff[0]);
            out_buff[2] = app_general_pull_before_fu_hum();
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_beforfu_hum(),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_beforfu_temp(),&out_buff[5]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_beforfu_co2(),&out_buff[7]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_beforfu_pm25(),&out_buff[9]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_AFTER_FU_WEATHER:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_after_fu_temp(),&out_buff[0]);
            out_buff[2] = app_general_pull_after_fu_hum();
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_afterfu_hum(),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_afterfu_temp(),&out_buff[5]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_afterfu_co2(),&out_buff[7]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_afterfu_pm25(),&out_buff[9]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_BACK_AIR_WEATHER:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_backair_temp(),&out_buff[0]);
            out_buff[2] = app_general_pull_backair_hum();
            pbc_int16uToArray_bigEndian(app_general_pull_backair_co2(),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_backair_pm25(),&out_buff[5]);    
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_backair_hum(),&out_buff[7]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_backair_temp(),&out_buff[9]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_backair_co2(),&out_buff[11]);
            pbc_int16uToArray_bigEndian(app_general_pull_adjust_backair_pm25(),&out_buff[13]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_EXHAST_AIR_WEATHER:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_exhastair_temp(),&out_buff[0]);
            out_buff[2] = app_general_pull_exhastair_hum();
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
			pbc_int16uToArray_bigEndian(app_general_pull_freshair_effciency(),&out_buff[8]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_OUT_STATUS:
        {          
            pbc_int16uToArray_bigEndian(app_general_pull_ae_error_word(),&out_buff[0]);
            out_buff[2] = app_general_pull_anergy_need();
            pbc_int16uToArray_bigEndian(app_general_pull_ae_ntc_error_word(),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_system_reset_word(),&out_buff[5]);
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
            pbc_int16uToArray_bigEndian(app_general_pull_error_word(),&out_buff[3]);
            out_buff[5] = app_pull_system_energy_need();
            pbc_int16uToArray_bigEndian(app_pull_max_low_temp(),&out_buff[6]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_MAIN_MACHINE_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_master_supply_temp(),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_general_pull_master_living_temp(),&out_buff[2]);
            pbc_int16uToArray_bigEndian(app_general_pull_master_outdoor_temp(),&out_buff[4]);
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_MIXWATER_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_pull_first_in_water_temp(),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_pull_back_water_temp(),&out_buff[2]);
            pbc_int16uToArray_bigEndian(app_pull_mix_water_temp(),&out_buff[4]);
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
		case DP_ADDR_SYSTEM_AIRCOD_COLD_BACK_WATER:
		{//制冷回水
			pbc_int16uToArray_bigEndian(app_general_pull_coolbackwater_set_temp(),&out_buff[0]);
			pbc_int16uToArray_bigEndian(app_general_pull_hotbackwater_set_temp(),&out_buff[0]);
			break;
		}
        default:
        {
            break;
        }           
    }
}
void app_push_data_point_message_sys(uint16_t in_dpAddr,uint8_t *in_buff)
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
            app_general_push_aircod_newair_speed(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_aircod_backair_speed(pbc_arrayToInt16u_bigEndian(&in_buff[2]));
            app_general_push_water_machine_fre(pbc_arrayToInt16u_bigEndian(&in_buff[4]));
            app_general_push_fu_machine_fre(pbc_arrayToInt16u_bigEndian(&in_buff[6]));
			app_general_push_freshair_effciency(pbc_arrayToInt16u_bigEndian(&in_buff[8]));
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_OUT_STATUS:
        {
            app_general_push_ae_error_word(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_anergy_need(in_buff[2]);
            app_general_push_ae_ntc_error_word(pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_system_reset_word(pbc_arrayToInt16u_bigEndian(&in_buff[5]));
            app_general_push_system_status_word(pbc_arrayToInt16u_bigEndian(&in_buff[7]));
            app_general_push_wind_value(in_buff[9]);
            app_general_push_hotwater_enable(in_buff[10]);
            app_general_push_filter_time(pbc_arrayToInt16u_bigEndian(&in_buff[11]));
            app_general_push_filter_usetime_inside(pbc_arrayToInt16u_bigEndian(&in_buff[13]));
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
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_MAIN_MACHINE_TEMP:
        {
            app_general_push_master_supply_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_master_living_temp(pbc_arrayToInt16u_bigEndian(&in_buff[2]));
            app_general_push_master_outdoor_temp(pbc_arrayToInt16u_bigEndian(&in_buff[4]));
            break;
        }   
        case DP_ADDR_SYSTEM_LIS_MIXWATER_TEMP:
        {
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
		case DP_ADDR_SYSTEM_AIRCOD_READ_ONLY_PAREMETER:
		{
			uint8_t i = 0;
			uint8_t j = 0;
			for(i = 1;i <= ARICOD_READ_ONLY_REG_NUM;i++)
			{
				APP_push_aricod_message(i,pbc_arrayToInt16u_bigEndian(&in_buff[j]));
				j += 2;
			}
			break;
		}
		case DP_ADDR_SYSTEM_AIRCOD_READ_WRITE_PAREMETER:
		{
			uint8_t i = 0;
			uint8_t j = 0;
			for(i = 1;i <= ARICOD_READ_WRITE_REG_NUM;i++)
			{
				APP_push_aricod_message((5000+i),pbc_arrayToInt16u_bigEndian(&in_buff[j]));
				j += 2;
			}
			break;
		}
		case DP_ADDR_SYSTEM_AIRCOD_COLD_BACK_WATER:
		{//制冷回水
			app_general_push_coolbackwater_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
			app_general_push_hotbackwater_set_temp(pbc_arrayToInt16u_bigEndian(&in_buff[0]));
			break;
		}
        default:
        {
            break;
        }              
    }
}
/*面板信息*/
void app_pull_data_point_message_pad(uint8_t in_solidNum,uint16_t in_dpAddr,uint8_t *out_buff)
{//面板获取信息
    switch (in_dpAddr)
    {
        case DP_ADDR_DHM_POWER:
        {
            out_buff[0] = app_general_pull_power_status();
            break;
        }   
        case DP_ADDR_DHM_WIND_SET_HUM:
        {
            out_buff[0] = app_general_pull_dhm_aircod_humidity(in_solidNum);
            break;
        }   
        case DP_ADDR_DHM_WIND_SET_MODE:
        {//
            out_buff[0] = app_general_pull_aircod_mode();
            break;
        }  
        case DP_ADDR_DHM_WIND_SET_SPEED:
        {
            out_buff[0] = app_general_pull_dhm_fanSpeed(in_solidNum);
            break;
        }   
        case DP_ADDR_DHM_DEHUM_NEDD:
        {
            out_buff[0] = app_general_pull_dhm_dehum_request(in_solidNum);
            break;
        }  
        case DP_ADDR_DHM_DEHUM_STATUS:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_ptc_temp(in_solidNum),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_iec5_temp(in_solidNum),&out_buff[2]);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_dm_output_status(in_solidNum),&out_buff[4]);
            break;
        }   
        case DP_ADDR_DHM_LIS_NEW_AIR_PWM:
        {
            out_buff[0] = app_general_pull_dhm_new_air_pwm_low(in_solidNum);
            out_buff[1] = app_general_pull_dhm_new_air_pwm_mid(in_solidNum);
            out_buff[2] = app_general_pull_dhm_new_air_pwm_high(in_solidNum);
            break;
        }   
        case DP_ADDR_DHM_LIS_BACK_AIR_PWM:
        {
            out_buff[0] = app_general_pull_dhm_back_air_pwm_low(in_solidNum);
            out_buff[1] = app_general_pull_dhm_back_air_pwm_mid(in_solidNum);
            out_buff[2] = app_general_pull_dhm_back_air_pwm_high(in_solidNum);
            break;
        }   
        case DP_ADDR_DHM_LIS_OUTDOOR_WEATHER:
        {   
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_outdoor_temp(in_solidNum),&out_buff[0]);
            out_buff[2] = app_general_pull_dhm_outdoor_hum(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_outdoor_hum(in_solidNum),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_outdoor_temp(in_solidNum),&out_buff[5]);
            break;
        }   
        case DP_ADDR_DHM_LIS_BEFORE_FU_WEATHER:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_before_fu_temp(in_solidNum),&out_buff[0]);
            out_buff[2] = app_general_pull_dhm_before_fu_hum(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_beforfu_hum(in_solidNum),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_beforfu_temp(in_solidNum),&out_buff[5]);
            break;
        }   
        case DP_ADDR_DHM_LIS_AFTER_FU_WEATHER:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_after_fu_temp(in_solidNum),&out_buff[0]);
            out_buff[2] = app_general_pull_dhm_after_fu_hum(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_afterfu_hum(in_solidNum),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_afterfu_temp(in_solidNum),&out_buff[5]);
            break;
        }   
        case DP_ADDR_DHM_LIS_BACK_AIR_WEATHER:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_backair_temp(in_solidNum),&out_buff[0]);
            out_buff[2] = app_general_pull_dhm_backair_hum(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_backair_co2(in_solidNum),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_backair_pm25(in_solidNum),&out_buff[5]);    
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_backair_hum(in_solidNum),&out_buff[7]);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_backair_temp(in_solidNum),&out_buff[9]);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_backair_co2(in_solidNum),&out_buff[11]);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_backair_pm25(in_solidNum),&out_buff[13]);
            break;
        }   
        case DP_ADDR_DHM_LIS_EXHAST_AIR_WEATHER:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_exhastair_temp(in_solidNum),&out_buff[0]);
            out_buff[2] = app_general_pull_dhm_exhastair_hum(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_exhastair_hum(in_solidNum),&out_buff[3]);
            pbc_int16uToArray_bigEndian(app_general_pull_dhm_adjust_exhastair_temp(in_solidNum),&out_buff[5]);
            break;
        }   
        case DP_ADDR_PAD_POWER:
        {
            out_buff[0] = app_general_pull_devive_power(in_solidNum);
            break;
        }   
        case  DP_ADDR_PAD_SET_COLD_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_pad_set_cold_temp(in_solidNum),out_buff);
            break;
        }    
        case  DP_ADDR_PAD_SET_HEAT_TEMP:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_pad_set_heat_temp(in_solidNum),out_buff);
            break;
        }    
        case  DP_ADDR_PAD_CHILD_LOCK:
        {
            out_buff[0] = app_general_pull_pad_child_lock(in_solidNum);
            break;
        }   
        case  DP_ADDR_PAD_SET_FAN:
        {
            out_buff[0] = app_general_pull_pad_set_fan_speed(in_solidNum);
            break;
        }   
        case  DP_ADDR_PAD_TWO_CNONTROL_MODE:
        {
            out_buff[0] = app_general_pull_pad_two_output_mode(in_solidNum);
            break;
        }    
        case  DP_ADDR_PAD_BIND_MESSAGE:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_pad_bind_list_warm(in_solidNum),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_bind_list_fan(in_solidNum),&out_buff[2]);
            break;
        }    
        case  DP_ADDR_PAD_STATUS_MESSAGE:
        {//0x0007
            out_buff[0] = app_general_pull_pad_warm_need(in_solidNum);
            out_buff[1] = app_general_pull_pad_fan_need(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_warm_need(in_solidNum),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_fan_need(in_solidNum),&out_buff[2]);
            out_buff[4] = app_general_pull_pad_lew_dorp_temp_output(in_solidNum);
            out_buff[5] = app_general_pull_pad_fan_out_speed(in_solidNum);
            out_buff[6] = app_general_pull_pad_cold_warm_status(in_solidNum);
            out_buff[7] = app_general_pull_pad_fan_speed_output(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_devive_error_word(in_solidNum),&out_buff[8]);
            break;
        }      
        case  DP_ADDR_PAD_MEASURE_MESSAGE:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_pad_measure_temp(in_solidNum),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_lew_drop_temp(in_solidNum),&out_buff[2]);
            out_buff[4] = app_general_pull_pad_measure_hum(in_solidNum);
            break;
        }   
        case  DP_ADDR_PAD_ADV_MESSAGE:
        {//0x0009
            out_buff[0] = app_general_pull_pad_freeze_protect(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_freeze_temp(in_solidNum),&out_buff[1]);
            out_buff[3] = app_general_pull_pad_onoff_memory(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_set_high_temp(in_solidNum),&out_buff[4]);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_set_low_temp(in_solidNum),&out_buff[6]);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_cold_comfortable_temp(in_solidNum),&out_buff[8]);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_heat_comfortable_temp(in_solidNum),&out_buff[10]);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_deadzone_temp(in_solidNum),&out_buff[12]);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_deadzone_lewtemp(in_solidNum),&out_buff[14]);
            out_buff[16] = app_general_pull_pad_cold_colla_enable(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_ai_cold_diff(in_solidNum),&out_buff[17]);
            out_buff[19] = app_general_pull_pad_warm_colla_enable(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_ai_heat_diff(in_solidNum),&out_buff[20]);
            out_buff[22] = app_general_pull_pad_fan_control(in_solidNum);
            out_buff[23] = app_general_pull_pad_set_pwm_low(in_solidNum);
            out_buff[24] = app_general_pull_pad_set_pwm_mid(in_solidNum);
            out_buff[25] = app_general_pull_pad_set_pwm_high(in_solidNum);
            out_buff[26] = app_general_pull_pad_two_output_mode(in_solidNum);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_adjust_temp(in_solidNum),&out_buff[27]);
            out_buff[29] = app_general_pull_pad_adjust_hum(in_solidNum);
            out_buff[30] = app_general_pull_pad_type_warm_choose(in_solidNum);
            out_buff[31] = app_general_pull_pad_room_area(in_solidNum);
            break;
        }    
        case  DP_ADDR_PAD_SYSTEM_MESSAGE:
        {//0x000a
            pbc_int16uToArray_bigEndian(app_general_pull_unbind_list_warm(),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_general_pull_unbind_list_fan(),&out_buff[2]);
            out_buff[4] = app_general_pull_power_status();
            out_buff[5] = app_general_pull_aircod_mode();
            #ifdef  DEBUG_TEST
            pbc_int16uToArray_bigEndian(0,&out_buff[6]);//测试方便，暂做屏蔽20210304
            #else
            pbc_int16uToArray_bigEndian(app_general_pull_master_error_word(),&out_buff[6]);
            #endif       
            pbc_int16uToArray_bigEndian(app_general_pull_pad_repeat_bind_list(),&out_buff[8]);
			pbc_int16uToArray_bigEndian(app_pull_mix_water_temp(),&out_buff[10]);
            pbc_int16uToArray_bigEndian(app_general_pull_system_lew_temp_status(),&out_buff[12]);
            break;
        }    
        case  DP_ADDR_PAD_SYSTEM_RTC:
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
        case DP_ADDR_PAD_DEVICE_TYPE:
        {
            pbc_int16uToArray_bigEndian(app_general_pull_devive_type(in_solidNum),&out_buff[0]);
            pbc_int16uToArray_bigEndian(app_general_pull_pad_version(in_solidNum),&out_buff[2]);
            break;
        }      
        default:
        {
            break;
        }
            
    }
}
void app_push_data_point_message_pad(uint8_t in_solidNum,uint16_t in_dpAddr,uint8_t *in_buff)
{//面板写入信息
    switch (in_dpAddr)
    {
        case DP_ADDR_DHM_POWER:
        {
            app_general_push_power_status(in_buff[0]);
            break;
        }   
        case DP_ADDR_DHM_WIND_SET_HUM:
        {
            app_general_push_dhm_aircod_humidity(in_solidNum,in_buff[0]);
            break;
        }   
        case DP_ADDR_DHM_WIND_SET_MODE:
        {//
            app_general_push_aircod_mode((AirRunMode_Def)in_buff[0]);
            break;
        }  
        case DP_ADDR_DHM_WIND_SET_SPEED:
        {
            app_general_push_dhm_fanSpeed(in_solidNum,(NewAirLevelSet_Def)in_buff[0]);
            break;
        }   
        case DP_ADDR_DHM_DEHUM_NEDD:
        {
            app_general_push_dhm_dehum_request(in_solidNum,in_buff[0]);
            break;
        }  
        case DP_ADDR_DHM_DEHUM_STATUS:
        {
            app_general_push_dhm_ptc_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_dhm_iec5_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_dhm_dm_output_status(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            break;
        }   
        case DP_ADDR_DHM_LIS_NEW_AIR_PWM:
        {
            app_general_push_dhm_new_air_pwm_low(in_solidNum,in_buff[0]);
            app_general_push_dhm_new_air_pwm_mid(in_solidNum,in_buff[0]);
            app_general_push_dhm_new_air_pwm_high(in_solidNum,in_buff[0]);
            break;
        }   
        case DP_ADDR_DHM_LIS_BACK_AIR_PWM:
        {
            app_general_push_dhm_back_air_pwm_low(in_solidNum,in_buff[0]);
            app_general_push_dhm_back_air_pwm_mid(in_solidNum,in_buff[0]);
            app_general_push_dhm_back_air_pwm_high(in_solidNum,in_buff[0]);
            break;
        }   
        case DP_ADDR_DHM_LIS_OUTDOOR_WEATHER:
        {   
            app_general_push_dhm_outdoor_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_dhm_outdoor_hum(in_solidNum,in_buff[2]);
            app_general_push_dhm_adjust_outdoor_hum(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_dhm_adjust_outdoor_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[5]));
            break;
        }   
        case DP_ADDR_DHM_LIS_BEFORE_FU_WEATHER:
        {
            app_general_push_dhm_before_fu_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_dhm_before_fu_hum(in_solidNum,in_buff[2]);
            app_general_push_dhm_adjust_beforfu_hum(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_dhm_adjust_beforfu_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[5]));
            break;
        }   
        case DP_ADDR_DHM_LIS_AFTER_FU_WEATHER:
        {
            app_general_push_dhm_after_fu_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_dhm_after_fu_hum(in_solidNum,in_buff[2]);
            app_general_push_dhm_adjust_afterfu_hum(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_dhm_adjust_afterfu_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[5]));
            break;
        }   
        case DP_ADDR_DHM_LIS_BACK_AIR_WEATHER:
        {
            app_general_push_dhm_backair_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_dhm_backair_hum(in_solidNum,in_buff[2]);
            app_general_push_dhm_backair_co2(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_dhm_backair_pm25(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[5]));    
            app_general_push_dhm_adjust_backair_hum(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[7]));
            app_general_push_dhm_adjust_backair_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[9]));    
            app_general_push_dhm_adjust_backair_co2(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[11]));
            app_general_push_dhm_adjust_backair_pm25(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[13]));    
            break;
        }   
        case DP_ADDR_DHM_LIS_EXHAST_AIR_WEATHER:
        {
            app_general_push_dhm_exhastair_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_dhm_exhastair_hum(in_solidNum,in_buff[2]);
            app_general_push_dhm_adjust_exhastair_hum(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[3]));
            app_general_push_dhm_adjust_exhastair_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[5]));
            break;
        }   
        case DP_ADDR_PAD_POWER:
        {
            app_general_push_devive_power(in_solidNum,in_buff[0]);
            break;
        }   
        case  DP_ADDR_PAD_SET_COLD_TEMP:
        {
            app_general_push_pad_set_cold_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            break;
        }    
        case  DP_ADDR_PAD_SET_HEAT_TEMP:
        {
            app_general_push_pad_set_heat_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            break;
        }    
        case  DP_ADDR_PAD_CHILD_LOCK:
        {
            app_general_push_pad_child_lock(in_solidNum,in_buff[0]);
            break;
        }   
        case  DP_ADDR_PAD_SET_FAN:
        {
            app_general_push_pad_set_fan_speed(in_solidNum,in_buff[0]);
            break;
        }   
        case  DP_ADDR_PAD_TWO_CNONTROL_MODE:
        {
            app_general_push_pad_two_output_mode(in_solidNum,in_buff[0]);
            break;
        }    
        case  DP_ADDR_PAD_BIND_MESSAGE:
        {
            #define MAX_BIND_NUM     12
            uint16_t bindList = 0;
            uint16_t unbindList_warm = 0;
			uint16_t unbindList_fan = 0;
			uint16_t bindList_warm = 0;
			uint16_t bindList_fan = 0;  
            uint8_t i = 0;
			uint8_t j =0;
			bindList_warm = app_general_pull_pad_bind_list_warm(in_solidNum);
            bindList = pbc_arrayToInt16u_bigEndian(&in_buff[0]);
			if(bindList_warm != bindList)
			{
				for(i = 0;i < MAX_BIND_NUM;i++)
				{
					if(bindList_warm&(0x01<<i))
					{//原来是绑定状态
						if((bindList & (0x01<<i)) == 0)
						{//解绑
							unbindList_warm = app_general_pull_unbind_list_warm();
							unbindList_warm |= (0x01<<i);
                            app_general_push_unbind_list_warm(unbindList_warm);
                            if(i >= 6)
                            {
                                unbindList_fan = app_general_pull_unbind_list_fan();
                                unbindList_fan |= (0x01<<i);                  
                                app_general_push_unbind_list_fan(unbindList_fan);
                            }					
							for(j = 0; j < MASTER_PAD_NUM;j++)
							{
								app_general_push_pad_dp_stamp(j,DP_ADDR_PAD_SYSTEM_MESSAGE,pbc_timeStamp_get_stamp());
							}							
						}
					}
					else
					{//原来未绑定状态
						if(bindList & (0x01<<i))
						{//加绑
							unbindList_warm = app_general_pull_unbind_list_warm();
							unbindList_warm &= (~(0x01<<i));
							app_general_push_unbind_list_warm(unbindList_warm);
                            if(i >= 6)
                            {
                                unbindList_fan = app_general_pull_unbind_list_fan();
                                unbindList_fan &= (~(0x01<<i));
                                app_general_push_unbind_list_fan(unbindList_fan);
                            }
							for(j = 0; j < MASTER_PAD_NUM;j++)
							{
								app_general_push_pad_dp_stamp(j,DP_ADDR_PAD_SYSTEM_MESSAGE,pbc_timeStamp_get_stamp());
							}
						}
					}
				}
                app_general_push_pad_bind_list_warm(in_solidNum,bindList);
            }			        
            bindList = pbc_arrayToInt16u_bigEndian(&in_buff[2]);
			bindList_fan = app_general_pull_pad_bind_list_fan(in_solidNum);
			if(bindList != bindList_fan)
			{
				for(i = 6;i < MAX_BIND_NUM;i++)
				{
					if(bindList_fan&(0x01<<i))
					{//原来是绑定状态
						if((bindList & (0x01<<i)) == 0)
						{//解绑
							unbindList_warm = app_general_pull_unbind_list_warm();
							unbindList_warm |= (0x01<<i);
							app_general_push_unbind_list_warm(unbindList_warm);
							unbindList_fan = app_general_pull_unbind_list_fan();
							unbindList_fan |= (0x01<<i);                  
							app_general_push_unbind_list_fan(unbindList_fan);
							for(j = 0; j < MASTER_PAD_NUM;j++)
							{
								app_general_push_pad_dp_stamp(j,DP_ADDR_PAD_SYSTEM_MESSAGE,pbc_timeStamp_get_stamp());
							}							
						}
					}
					else
					{//原来未绑定状态
						if(bindList & (0x01<<i))
						{//加绑
							unbindList_warm = app_general_pull_unbind_list_warm();
							unbindList_warm &= (~(0x01<<i));
							app_general_push_unbind_list_warm(unbindList_warm);
							unbindList_fan = app_general_pull_unbind_list_fan();
							unbindList_fan &= (~(0x01<<i));
							app_general_push_unbind_list_fan(unbindList_fan);
							for(j = 0; j < MASTER_PAD_NUM;j++)
							{
								app_general_push_pad_dp_stamp(j,DP_ADDR_PAD_SYSTEM_MESSAGE,pbc_timeStamp_get_stamp());
							}
						}
					}
				}
				app_general_push_pad_bind_list_fan(in_solidNum,bindList);
			}  
            check_rebind_list();   	
            break;
        }    
        case  DP_ADDR_PAD_STATUS_MESSAGE:
        {//0x0007
            app_general_push_pad_warm_need(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));//辐射需求
            app_general_push_pad_fan_need(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[2]));//风盘需求
            app_general_push_pad_lew_dorp_temp_output(in_solidNum,in_buff[4]);
            app_general_push_pad_fan_out_speed(in_solidNum,in_buff[5]);
            app_general_push_pad_cold_warm_status(in_solidNum,in_buff[6]);
            app_general_push_pad_fan_speed_output(in_solidNum,in_buff[7]);
            app_general_push_devive_error_word(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[8]));
            break;
        }      
        case  DP_ADDR_PAD_MEASURE_MESSAGE:
        {
            app_general_push_pad_measure_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_pad_lew_drop_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[2]));
            app_general_push_pad_measure_hum(in_solidNum,in_buff[4]);
            break;
        }   
        case  DP_ADDR_PAD_ADV_MESSAGE:
        {        
            app_general_push_pad_freeze_protect(in_solidNum,in_buff[0]);
            app_general_push_pad_freeze_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[1]));
            app_general_push_pad_onoff_memory(in_solidNum,in_buff[3]);
            app_general_push_pad_set_high_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[4]));
            app_general_push_pad_set_low_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[6]));
            app_general_push_pad_cold_comfortable_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[8]));
            app_general_push_pad_heat_comfortable_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[10]));
            app_general_push_pad_deadzone_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[12]));
            app_general_push_pad_deadzone_lewtemp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[14]));
            app_general_push_pad_cold_colla_enable(in_solidNum,in_buff[16]);
            app_general_push_pad_ai_cold_diff(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[17]));
            app_general_push_pad_warm_colla_enable(in_solidNum,in_buff[19]);
            app_general_push_pad_ai_heat_diff(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[20]));
            app_general_push_pad_fan_control(in_solidNum,in_buff[22]);
            app_general_push_pad_set_pwm_low(in_solidNum,in_buff[23]);
            app_general_push_pad_set_pwm_mid(in_solidNum,in_buff[24]);
            app_general_push_pad_set_pwm_high(in_solidNum,in_buff[25]);
            app_general_push_pad_two_output_mode(in_solidNum,in_buff[26]);
            app_general_push_pad_adjust_temp(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[27]));
            app_general_push_pad_adjust_hum(in_solidNum,in_buff[29]);
            app_general_push_pad_type_warm_choose(in_solidNum,in_buff[30]);
            app_general_push_pad_room_area(in_solidNum,in_buff[31]);
            break;
        }    
        case  DP_ADDR_PAD_SYSTEM_MESSAGE:
        {
            break;
        }    
        case  DP_ADDR_PAD_SYSTEM_RTC:
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
        case DP_ADDR_PAD_DEVICE_TYPE:
        {//版本号
            app_general_push_devive_type(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[0]));
            app_general_push_pad_version(in_solidNum,pbc_arrayToInt16u_bigEndian(&in_buff[2]));
            break;
        }   
        default:
        {
            break;
        }              
    }
}


/*发送同步数据块*/
void app_master_slave_send_syn_block(uint8_t in_solidNum,uint8_t *in_dest_addr,synBlock_t in_block)
{//输入 实例   目标地址   数据块内容结构体
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
            if(in_solidNum == SYSTEM_PAD)
            {
                for(i = 0; i < in_block.blockNum;i++)
                {
                    if(in_block.regAddr_pad[i] >= DP_ADDR_DHM_START)
                    {
                        stamp = app_general_pull_dhm_dp_stamp(in_block.padNumber,in_block.regAddr_pad[i]);     
                        tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                        tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                        tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                        tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                        tempLinkData->Payload[startIndex+4] = (dpPadLen_pad[in_block.regAddr_pad[i]] + 3);
                        tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr_pad[i]>>8);
                        tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr_pad[i]);
                        app_pull_data_point_message_pad(in_block.padNumber,in_block.regAddr_pad[i],&tempLinkData->Payload[startIndex+7]);
                        blockLen = (7+dpPadLen_pad[in_block.regAddr_pad[i]]);
                        tempLinkData->PayloadLength += blockLen;
                        startIndex += blockLen;
                    }
                    else
                    {
                        stamp = app_general_pull_pad_dp_stamp(in_block.padNumber,in_block.regAddr_pad[i]);     
                        tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                        tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                        tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                        tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                        tempLinkData->Payload[startIndex+4] = (dpPadLen_pad[in_block.regAddr_pad[i]] + 3);
                        tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr_pad[i]>>8);
                        tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr_pad[i]);
                        app_pull_data_point_message_pad(in_block.padNumber,in_block.regAddr_pad[i],&tempLinkData->Payload[startIndex+7]);
                        blockLen = (7+dpPadLen_pad[in_block.regAddr_pad[i]]);
                        tempLinkData->PayloadLength += blockLen;
                        startIndex += blockLen;
                    }           
                }
            }
            else if(in_solidNum == SYSTEM_MASTER)
            {
                for(i = 0; i < in_block.blockNum;i++)
                {
                    if(in_block.regAddr_system[i] >= DP_ADDR_START)
                    {
                        stamp = app_general_pull_system_dp_stamp(in_block.regAddr_system[i]);     
                        tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                        tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                        tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                        tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                        tempLinkData->Payload[startIndex+4] = (dpPadLen_system[(in_block.regAddr_system[i]-DP_ADDR_START)] + 3);
                        tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr_system[i]>>8);
                        tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr_system[i]);
                        app_pull_data_point_message_sys(in_block.regAddr_system[i],&tempLinkData->Payload[startIndex+7]);
                        blockLen = (7+dpPadLen_system[(in_block.regAddr_system[i]-DP_ADDR_START)]);
                        tempLinkData->PayloadLength += blockLen;
                        startIndex += blockLen;
                    }               
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
            if(in_solidNum == SYSTEM_PAD)
            {
                for(i = 0; i < in_block.blockNum;i++)
                {
                    if(in_block.regAddr_pad[i] >= DP_ADDR_DHM_START)
                    {
                        stamp = app_general_pull_dhm_dp_stamp(in_block.padNumber,in_block.regAddr_pad[i]);     
                        tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                        tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                        tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                        tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                        tempLinkData->Payload[startIndex+4] = (dpPadLen_pad[in_block.regAddr_pad[i]] + 3);
                        tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr_pad[i]>>8);
                        tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr_pad[i]);
                        app_pull_data_point_message_pad(in_block.padNumber,in_block.regAddr_pad[i],&tempLinkData->Payload[startIndex+7]);
                        blockLen = (7+dpPadLen_pad[in_block.regAddr_pad[i]]);
                        tempLinkData->PayloadLength += blockLen;
                        startIndex += blockLen;
                    }
                    else
                    {
                        stamp = app_general_pull_pad_dp_stamp(in_block.padNumber,in_block.regAddr_pad[i]);     
                        tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                        tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                        tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                        tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                        tempLinkData->Payload[startIndex+4] = (dpPadLen_pad[in_block.regAddr_pad[i]] + 3);
                        tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr_pad[i]>>8);
                        tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr_pad[i]);
                        app_pull_data_point_message_pad(in_block.padNumber,in_block.regAddr_pad[i],&tempLinkData->Payload[startIndex+7]);
                        blockLen = (7+dpPadLen_pad[in_block.regAddr_pad[i]]);
                        tempLinkData->PayloadLength += blockLen;
                        startIndex += blockLen;
                    }          
                }
            } 
            else if(in_solidNum == SYSTEM_MASTER)
            {
                for(i = 0; i < in_block.blockNum;i++)
                {
                    if(in_block.regAddr_system[i] >= DP_ADDR_START)
                    {
                        stamp = app_general_pull_system_dp_stamp(in_block.regAddr_system[i]);     
                        tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                        tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                        tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                        tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                        tempLinkData->Payload[startIndex+4] = (dpPadLen_system[(in_block.regAddr_system[i]-DP_ADDR_START)] + 3);
                        tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr_system[i]>>8);
                        tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr_system[i]);
                        app_pull_data_point_message_sys(in_block.regAddr_system[i],&tempLinkData->Payload[startIndex+7]);
                        blockLen = (7+dpPadLen_system[(in_block.regAddr_system[i]-DP_ADDR_START)]);
                        tempLinkData->PayloadLength += blockLen;
                        startIndex += blockLen;
                    }                   
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
            if(in_solidNum == SYSTEM_PAD)
            {
                for(i = 0; i < in_block.blockNum;i++)
                {
                    if(in_block.regAddr_pad[i] >= DP_ADDR_DHM_START)
                    {
                        stamp = app_general_pull_dhm_dp_stamp(in_block.padNumber,in_block.regAddr_pad[i]);     
                        tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                        tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                        tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                        tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                        tempLinkData->Payload[startIndex+4] = (dpPadLen_pad[in_block.regAddr_pad[i]] + 3);
                        tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr_pad[i]>>8);
                        tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr_pad[i]);
                        app_pull_data_point_message_pad(in_block.padNumber,in_block.regAddr_pad[i],&tempLinkData->Payload[startIndex+7]);
                        blockLen = (7+dpPadLen_pad[in_block.regAddr_pad[i]]);
                        tempLinkData->PayloadLength += blockLen;
                        startIndex += blockLen;
                    }
                    else
                    {
                        stamp = app_general_pull_pad_dp_stamp(in_block.padNumber,in_block.regAddr_pad[i]);     
                        tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                        tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                        tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                        tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                        tempLinkData->Payload[startIndex+4] = (dpPadLen_pad[in_block.regAddr_pad[i]] + 3);
                        tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr_pad[i]>>8);
                        tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr_pad[i]);
                        app_pull_data_point_message_pad(in_block.padNumber,in_block.regAddr_pad[i],&tempLinkData->Payload[startIndex+7]);
                        blockLen = (7+dpPadLen_pad[in_block.regAddr_pad[i]]);
                        tempLinkData->PayloadLength += blockLen;
                        startIndex += blockLen;
                    }          
                }
            } 
             else if(in_solidNum == SYSTEM_MASTER)
            {
                for(i = 0; i < in_block.blockNum;i++)
                {
                    if(in_block.regAddr_system[i] >= DP_ADDR_START)
                    {
                        stamp = app_general_pull_system_dp_stamp(in_block.regAddr_system[i]);     
                        tempLinkData->Payload[startIndex] = (uint8_t)(stamp>>24);//时间戳
                        tempLinkData->Payload[startIndex+1] =(uint8_t)(stamp>>16);
                        tempLinkData->Payload[startIndex+2] =(uint8_t)(stamp>>8);
                        tempLinkData->Payload[startIndex+3] =(uint8_t)(stamp);
                        tempLinkData->Payload[startIndex+4] = (dpPadLen_system[(in_block.regAddr_system[i]-DP_ADDR_START)] + 3);
                        tempLinkData->Payload[startIndex+5] = (uint8_t)(in_block.regAddr_system[i]>>8);
                        tempLinkData->Payload[startIndex+6] = (uint8_t)(in_block.regAddr_system[i]);
                        app_pull_data_point_message_sys(in_block.regAddr_system[i],&tempLinkData->Payload[startIndex+7]);
                        blockLen = (7+dpPadLen_system[(in_block.regAddr_system[i]-DP_ADDR_START)]);
                        tempLinkData->PayloadLength += blockLen;
                        startIndex += blockLen;
                    }             
                }
            }
            push_active_one_message_transmit(in_solidNum,false);//强上拉发送
            break;
        }
        default:
        {
            break;
        }
    }
}


bool _syn_pull_local_id(uint8_t *in_deviceId)
{//确认是否未自己的ID
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
bool _syn_pull_extend_cc(void)
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
                if(false == _syn_pull_local_id(&logList[i].DeviceID[0]))
                {
                    return true;
                }              
            }
        }
    }
    return false;
}

uint8_t* _syn_pull_extend_cc_id(void)
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
                if(false == _syn_pull_local_id(&logList[i].DeviceID[0]))
                {
                    return &logList[i].DeviceID[0];
                }              
            }
        }
    }
    return &deviceid_addr[0];
}

bool _syn_pull_write_device_id(uint8_t *in_deviceId)
{//烧录ID
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

uint8_t* _syn_pull_type_hc_id(void)
{//获取环控ID
    uint8_t i = 0;
    linkDeviceList_t* logList;
    logList = app_link_log_pull_device_list(SYSTEM_MASTER);
    for(i = 0; i < MAX_DEVICE_NUM;i++)
    {
        if(logList[i].onlineFlag)
        {
            if(logList[i].deviceType == DEVICE_TYPE_HC)
            {
                return &logList[i].DeviceID[0];
            }
        }
    }
    return &deviceid_addr[0];
}



bool _syn_pull_type_hc_online(void)
{
    uint8_t i = 0;
    linkDeviceList_t* logList;
    logList = app_link_log_pull_device_list(SYSTEM_MASTER);
    for(i = 0; i < MAX_DEVICE_NUM;i++)
    {
        if(logList[i].onlineFlag)
        {
            if(logList[i].deviceType == DEVICE_TYPE_HC)
            {
                return true;
            }
        }
    }
    return false;
}

void _master_system_syn_task(void)
{//输配环控同步任务
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
    uint32_t occupyWord_backup;
    pbc_timerMillRun_task(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay);//接收超时
    pbc_timerMillRun_task(&appModbusSyn[SYSTEM_MASTER].roll_back_delay);//发送回退
    pbc_timerMillRun_task(&appModbusSyn[SYSTEM_MASTER].answer_delay);//响应延时
    do
    {
        mainSynStatsu_backup = appModbusSyn[SYSTEM_MASTER].mainSynStatsus;
        switch(appModbusSyn[SYSTEM_MASTER].mainSynStatsus)
        {
            case SYN_STATUS_IDLE:
            {
                break;
            }
            case SYN_STATUS_WAIT_RECEIVE:
            {//等待接收
                if(appModbusSyn[SYSTEM_MASTER].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_MASTER].receiveOneMessage = false;
					if(appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[3] != 0x00)
					{//数据块数量不为0
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
									app_push_data_point_message_sys(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+7]);     
									appModbusSyn[SYSTEM_MASTER].updataWord =   occupyWord_backup;//恢复现场
								}
								else
								{                           
									synBlock.regAddr_system[synBlock.blockNum] = regAdd;
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
                            app_push_data_point_message_sys(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[11]); 
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
                else if(mde_upgrade_pull_ae_status())
                {
                    app_bough_update_master_ae_task();
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
                for(j = 0; j < MAX_DATA_POINT_LEN_SYSTEM;j++)
                {
                    if(appModbusSyn[SYSTEM_MASTER].updataWord & (0x01<<j))
                    {
                        app_general_push_system_dp_stamp((j+DP_ADDR_START),pbc_timeStamp_get_stamp());
                        synBlock.regAddr_system[synBlock.blockNum] = (j+DP_ADDR_START);
                        synBlock.blockNum++;                              
                    }
                }
                synBlock.control_answer = 0x01;
                synBlock.padNumber = i;
                app_master_slave_send_syn_block(SYSTEM_MASTER,_syn_pull_type_hc_id(),synBlock);
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
                    if(appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[3] != 0x00)
                    {
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
                                    app_push_data_point_message_sys(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+7]);     
                                    appModbusSyn[SYSTEM_MASTER].updataWord =   occupyWord_backup;//恢复现场
                                }
                                else
                                {                           
                                    synBlock.regAddr_system[synBlock.blockNum] = regAdd;
                                    synBlock.blockNum++;
                                } 
                                blockLen = (appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+4]+4);   //数据长度  
                                startIndex += blockLen;            
                            } 
                        }
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
                for(j = 0; j < MAX_DATA_POINT_LEN_SYSTEM;j++)
                {
                    if(appModbusSyn[SYSTEM_MASTER].updataWord & (0x01<<j))
                    {
                        app_general_push_system_dp_stamp((j+DP_ADDR_START),pbc_timeStamp_get_stamp());
                        synBlock.regAddr_system[synBlock.blockNum] = (j+DP_ADDR_START);
                        synBlock.blockNum++;                              
                    }
                }
                synBlock.control_answer = 0x01;
                synBlock.padNumber = i;
                app_master_slave_send_syn_block(SYSTEM_MASTER,_syn_pull_type_hc_id(),synBlock);
                appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD_RESULT;
                break;
            }
            case SYN_STATUS_RESEND_UPDATA_WORD_RESULT:
            {
                if(pull_bough_transmit_monitor(SYSTEM_MASTER) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_RERECEIVE_UPDATA_WORD;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_MASTER].receive_timeout_delay,RECEIVE_TIMEOUT);
                    failCount = 0;
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
                    if(appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[3] != 0x00)
                    {
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
                                    app_push_data_point_message_sys(regAdd,&appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+7]);     
                                    appModbusSyn[SYSTEM_MASTER].updataWord =   occupyWord_backup;//恢复现场
                                }
                                else
                                {                           
                                    synBlock.regAddr_system[synBlock.blockNum] = regAdd;
                                    synBlock.blockNum++;
                                } 
                                blockLen = (appModbusSyn[SYSTEM_MASTER].in_rev_data->Payload[startIndex+4]+4);   //数据长度  
                                startIndex += blockLen;            
                            } 
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
            default:
            {
                break;
            }
        }
    } while (mainSynStatsu_backup != appModbusSyn[SYSTEM_MASTER].mainSynStatsus);  
}
uint8_t test_pull_syn_status(void)
{
    return appModbusSyn[SYSTEM_PAD].mainSynStatsus;
}

void app_pad_check_rebind_task(void)
{  
    macro_createTimer(measure_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&measure_delay);
    if(pbc_pull_timerIsCompleted(&measure_delay))
    {
        pbc_reload_timerClock(&measure_delay,10000);
        check_rebind_list();
    }
}

uint8_t pull_syn_main_status(void)
{
    return appModbusSyn[0].mainSynStatsus;
}

void _pad_dispose_receive_data(void)
{
    uint8_t blockNum = 0;
    static synBlock_t  padSynBlock;
    uint8_t startIndex = 0;
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t k = 0;
    uint8_t num = 0;
    uint16_t id0,id1,id2;
    bool newIdFlag = true;
    uint16_t regAdd = 0;
    uint32_t receiveStamp = 0;
    uint32_t occupyWord_backup;
    uint32_t padOccupy_backup;
    linkDeviceList_t* logList;
    uint8_t blockLen = 0;
    if(appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[3] != 0x00)
    {//数据块不为0处理数据
        if(_syn_pull_local_id(&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkDstAddr[0]))
        {//自己地址
            blockNum = appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[3];//数据块
            padSynBlock.blockNum = 0;
            startIndex = 4;
            for(j = 0;j < blockNum;j++)
            {
                regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[startIndex+5]);
                id0 = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[0]);
                id1 = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[2]);
                id2 = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[4]);
                for(i = 0; i < MASTER_PAD_NUM;i++)
                {//已在末端列表内
                    if((app_general_pull_devive_id0(i) == id0) &&
                    (app_general_pull_devive_id1(i) == id1) && 
                    (app_general_pull_devive_id2(i) == id2))
                    {//找到ID
                        newIdFlag = false;
                        pbc_reload_timerClock(app_general_pull_pad_id_ocupy_time(i),DELAY_OCCPUY);//占用5分钟
                        app_general_push_pad_id_use_message(i,true);
                        app_general_push_devive_online(i,true);
                        receiveStamp = pbc_arrayToInt32u_bigEndian(&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[startIndex]);//发起方时间戳  
                        if(appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[0] == 0xF3)
                        {//除湿模块
                            for(num = 0; num < MASTER_DHM_NUM;num++)
                            {
                                if(app_general_pull_dhm_use_port(num) == i)
                                {
                                    if(receiveStamp >= app_general_pull_dhm_dp_stamp(num,regAdd))
                                    {//压入数据
                                        app_general_push_dhm_dp_stamp(num,regAdd,receiveStamp);
                                        occupyWord_backup =  appModbusSyn[SYSTEM_PAD].updataWord; //保存现场  
                                        app_push_data_point_message_pad(num,regAdd,&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[startIndex+7]);     
                                        appModbusSyn[SYSTEM_PAD].updataWord =   occupyWord_backup;//恢复现场
                                    }
                                    else
                                    {
                                        padSynBlock.regAddr_pad[padSynBlock.blockNum] = regAdd;
                                        padSynBlock.blockNum++;                           
                                    }    
                                    break;
                                }
                            }   
                        }
                        else
                        {                  
                            if(receiveStamp >= app_general_pull_pad_dp_stamp(i,regAdd))
                            {//压入数据
                                app_general_push_pad_dp_stamp(i,regAdd,receiveStamp);
                                occupyWord_backup =  appModbusSyn[SYSTEM_PAD].updataWord; //保存现场 
                                padOccupy_backup = padOccupyWord[i];
                                app_push_data_point_message_pad(i,regAdd,&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[startIndex+7]);     
                                appModbusSyn[SYSTEM_PAD].updataWord =   occupyWord_backup;//恢复现场
                                padOccupyWord[i] = padOccupy_backup;
                            }
                            else
                            {                           
                                padSynBlock.regAddr_pad[padSynBlock.blockNum] = regAdd;
                                padSynBlock.blockNum++;
                            }    
                        }
                        break;                    
                    }
                }
                if(newIdFlag)
                {//新的数据
                    for(i = 0; i < MASTER_PAD_NUM;i++)
                    {
                        if(app_general_pull_pad_id_use_message(i) == false)
                        {//端口未使用，压入ID
                            app_general_push_pad_id_use_message(i,true);
                            app_general_push_devive_id0(i,id0);
                            app_general_push_devive_id1(i,id1);
                            app_general_push_devive_id2(i,id2);
                            app_general_push_devive_online(i,true);
                            logList = app_link_log_pull_device_list(SYSTEM_PAD);
                            for(k = 0; k < MAX_DEVICE_NUM;k++)
                            {
                                if((logList[k].DeviceID[0] == appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[0])&&
                                    (logList[k].DeviceID[1] == appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[1])&&
                                        (logList[k].DeviceID[2] == appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[2]) &&
                                        (logList[k].DeviceID[3] == appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[3])&&
                                            (logList[k].DeviceID[4] == appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[4])&&
                                            (logList[k].DeviceID[5] == appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[5]))
                                {
                                    app_general_push_devive_type(i,logList[k].deviceType);
                                    break;
                                }
                            }
                            pbc_reload_timerClock(app_general_pull_pad_id_ocupy_time(i),DELAY_OCCPUY);
                            receiveStamp = pbc_arrayToInt32u_bigEndian(&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[startIndex]);//发起方时间戳
                            if(appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[0] == 0xF3)
                            {//除湿模块
                                for(num = 0; num < MASTER_DHM_NUM;num++)
                                {
                                    if(app_general_pull_dhm_id_use_message(num) == false)
                                    {
                                        app_general_push_dhm_id_use_message(num,true);
                                        app_general_push_dhm_use_port(num,i);//公共端占用端口
                                        if(receiveStamp >= app_general_pull_dhm_dp_stamp(num,regAdd))
                                        {//压入数据
                                            app_general_push_dhm_dp_stamp(num,regAdd,receiveStamp);
                                            occupyWord_backup =  appModbusSyn[SYSTEM_PAD].updataWord; //保存现场  
                                            app_push_data_point_message_pad(num,regAdd,&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[startIndex+7]);     
                                            appModbusSyn[SYSTEM_PAD].updataWord =   occupyWord_backup;//恢复现场
                                        }
                                        else
                                        {
                                            padSynBlock.regAddr_pad[padSynBlock.blockNum] = regAdd;
                                            padSynBlock.blockNum++;                           
                                        }    
                                        break;
                                    }
                                }
                            }  
                            else
                            {
                                if(receiveStamp >= app_general_pull_pad_dp_stamp(i,regAdd))
                                {//压入数据
                                    app_general_push_pad_dp_stamp(i,regAdd,receiveStamp);
                                    occupyWord_backup =  appModbusSyn[SYSTEM_PAD].updataWord; //保存现场  
                                    app_push_data_point_message_pad(i,regAdd,&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[startIndex+7]);     
                                    appModbusSyn[SYSTEM_PAD].updataWord =   occupyWord_backup;//恢复现场
                                }
                                else
                                {
                                    padSynBlock.regAddr_pad[padSynBlock.blockNum] = regAdd;
                                    padSynBlock.blockNum++;                           
                                }    
                            }                                                  
                            break;
                        }
                    }
                }
                blockLen = (appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[startIndex+4]+4);   //数据长度  
                startIndex += blockLen;   
            }                  
        }
    }
}
void _control_pad_syn_task(void)
{//输配面板同步任务
    // uint8_t startIndex = 0;
   // uint8_t blockLen = 0;
   //  uint8_t k = 0;
   // uint8_t blockNum = 0;
   // uint16_t id0,id1,id2;
   // uint32_t receiveStamp = 0;
   // bool newIdFlag = true;
   // uint32_t occupyWord_backup;
   // uint32_t padOccupy_backup;
    synStatus_def mainSynStatsu_backup;
    static synBlock_t  padSynBlock;
    static uint8_t failCount = 0;
    uint16_t regAdd = 0;
    uint8_t i = 0;
    uint8_t j = 0;
    static uint8_t updata_port = 0;
    static uint8_t list_port = 0;
    uint8_t idBuff[6];
    linkDeviceList_t* logList;
    pbc_timerMillRun_task(&appModbusSyn[SYSTEM_PAD].receive_timeout_delay);//接收超时
    pbc_timerMillRun_task(&appModbusSyn[SYSTEM_PAD].roll_back_delay);//发送回退
    pbc_timerMillRun_task(&appModbusSyn[SYSTEM_PAD].answer_delay);//响应延时
    app_pad_check_rebind_task();
    do
    {
        mainSynStatsu_backup = appModbusSyn[SYSTEM_PAD].mainSynStatsus;
        bool occpupyFlag = true;
        switch(appModbusSyn[SYSTEM_PAD].mainSynStatsus)
        {
            case SYN_STATUS_IDLE:
            {
                break;
            }
            case SYN_STATUS_WAIT_RECEIVE:
            {//等待接收
                if(appModbusSyn[SYSTEM_PAD].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_PAD].receiveOneMessage = false;
                    if(_syn_pull_write_device_id(&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkDstAddr[0]))
                    {
                        regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[9]);
                        app_push_data_point_message_sys(regAdd,&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[11]); 
                        padSynBlock.control_answer = 0x41; 
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER;
                        pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].answer_delay,ANSWER_DELAY);
                    }
                    else
                    {
                        _pad_dispose_receive_data(); 
                        if(appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[1] == 0x01)
                        {//确定是否需要应答
                            if(padSynBlock.blockNum)
                            {
                                padSynBlock.control_answer = 0x81;
                            }
                            else
                            {
                                padSynBlock.control_answer = 0x41;    
                            }  
                            appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER;
                            pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].answer_delay,ANSWER_DELAY);      
                        }           
                    }                             
                }
                else if(appModbusSyn[SYSTEM_PAD].updataWord)
                {
                    if(appModbusSyn[SYSTEM_PAD].listWord)
                    {

                    }
                    else
                    {
                        
                        logList = app_link_log_pull_device_list(SYSTEM_PAD);
                        for(i = 0; i < MAX_DEVICE_NUM;i++)
                        {
                            if(logList[i].onlineFlag)
                            {
                                if((logList[i].deviceType == DEVICE_TYPE_FAN)||
                                    (logList[i].deviceType == DEVICE_TYPE_ROMM))
                                {
                                    appModbusSyn[SYSTEM_PAD].listWord |= (0x01<<i);
                                }
                            }
                        }                       
                    }
                    if(appModbusSyn[SYSTEM_PAD].listWord == 0)
                    {//出现更新字但无末端列表则不再发送数据  20210425
                        appModbusSyn[SYSTEM_PAD].updataWord = 0;
                    }
                    else
                    {
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST_ACTIVE;
                    }
                    
                }
                else
                {
                    for(i = 0; i < MASTER_PAD_NUM; i++)
                    {
                        if(app_general_pull_devive_online(i))
                        {//在线
                            if(padOccupyWord[i])
                            {
                                appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_UPDATA_ACTIVE;
                                break;
                            }
                        }  
                        else
                        {
                            padOccupyWord[i] = 0;
                        }                                             
                    }
                    if(mde_upgrade_pull_pad_status()|| app_general_pull_version_pad_flag())
                    {//加入主动升级任务
                        if(app_updaBackup_pull_status() != BACKUP_UPDATING)
                        {
                            app_bough_update_master_task();
                        }                  
                    }
                    else if(mde_upgrade_pull_fan_status() || app_general_pull_version_fan_flag())
                    {//加入主动升级任务
                        if(app_updaBackup_pull_status() != BACKUP_UPDATING)
                        {
                            app_bough_update_master_task();
                        }                  
                    }
                }             
                break;
            }
            case SYN_STATUS_ANSWER:
            {//响应
                if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_PAD].answer_delay))
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                }
                else
                {
                    if(pull_bough_link_is_busy(SYSTEM_PAD))
                    {//忙碌先释放
                        
                    }
                    else
                    {
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER_RESULT; 
                        app_master_slave_send_syn_block(SYSTEM_PAD,&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkSrcAddr[0],padSynBlock);
                    }     
                }       
                break;
            }
            case SYN_STATUS_ANSWER_RESULT:
            {//响应结果
                if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                }
                else if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_conflict)
                {//冲突报文
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER;
                }
                else if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_error)
                {//未知错误
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER;
                }          
                break;
            }
            case SYN_STATUS_SEND_UPDATA_ACTIVE:
            {
                if(app_link_request_transmit_activation_request(SYSTEM_PAD))
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_UPDATA_ACTIVE_RESULT;
                }  
                else
                {
                  
                }   
                break;
            }
            case SYN_STATUS_SEND_UPDATA_ACTIVE_RESULT:
            {
                if(TRANSMIT_RESULT_FAIL == app_link_request_get_transmit_result(SYSTEM_PAD))
                {//发送失败
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_UPDATA_ACTIVE; 
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    } 
                } 
                else if(TRANSMIT_RESULT_SUCCESS == app_link_request_get_transmit_result(SYSTEM_PAD))
                {//发送成功
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_UPDATA_WORD; 
                    failCount = 0;
                }  
                break;
            }
            case SYN_STATUS_SEND_UPDATA_WORD:
            {
                padSynBlock.blockNum = 0;
                for(i = 0; i < MASTER_PAD_NUM;i++)
                {
                    if(padOccupyWord[i])
                    {
                        occpupyFlag = false;
                        for(j = 0; j < MAX_DATA_POINT_LEN_PAD;j++)
                        {
                            if(padOccupyWord[i] & (0x01<<j))
                            {
                                app_general_push_pad_dp_stamp(i,j,pbc_timeStamp_get_stamp());
                                padSynBlock.regAddr_pad[padSynBlock.blockNum] = j;
                                padSynBlock.blockNum++;                              
                            }
                        }
                        padSynBlock.control_answer = 0x01;
                        padSynBlock.padNumber = i;
                        updata_port = i;
                        pbc_int16uToArray_bigEndian(app_general_pull_devive_id0(i),&idBuff[0]);
                        pbc_int16uToArray_bigEndian(app_general_pull_devive_id1(i),&idBuff[2]);
                        pbc_int16uToArray_bigEndian(app_general_pull_devive_id2(i),&idBuff[4]);
                        app_master_slave_send_syn_block(SYSTEM_PAD,&idBuff[0],padSynBlock);
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_UPDATA_WORD_RESULT;
                        break;
                    }
                }
                if(occpupyFlag)
                {//无抢占数据结束
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                }            
                break;
            }
            case SYN_STATUS_SEND_UPDATA_WORD_RESULT:
            {
                if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RECEIVE_UPDATA_WORD;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].receive_timeout_delay,RECEIVE_TIMEOUT);
                    failCount = 0;
                }
                else if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_conflict)
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_UPDATA_WORD_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                else if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_error)
                {//冲突报文或者未知错误
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_UPDATA_WORD_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                break;
            }
            case SYN_STATUS_RECEIVE_UPDATA_WORD:
            {
                if(appModbusSyn[SYSTEM_PAD].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_PAD].receiveOneMessage = false;
                    _pad_dispose_receive_data();   
                    padOccupyWord[updata_port] = 0;
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;                     
                }
                else if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_PAD].receive_timeout_delay))
                {//接收超时
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_ACTIVE;
                }
                break;
            }
            case SYN_STATUS_SEND_UPDATA_WORD_ROLL_BACK:
            {
                if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_PAD].roll_back_delay))
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_UPDATA_WORD;;
                }
                break;
            }
            case SYN_STATUS_RESEND_UPDATA_ACTIVE:
            {
                if(app_link_request_transmit_activation_request(SYSTEM_PAD))
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_ACTIVE_RESULT;
                }  
                else
                {
                    if(appModbusSyn[SYSTEM_PAD].receiveOneMessage)
                    {
                        appModbusSyn[SYSTEM_PAD].receiveOneMessage = false;
                        if(_syn_pull_write_device_id(&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkDstAddr[0]))
                        {
                            regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[9]);
                            app_push_data_point_message_sys(regAdd,&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[11]); 
                            padSynBlock.control_answer = 0x41; 
                            appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER;
                            pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].answer_delay,ANSWER_DELAY);
                        }
                        else
                        {
                            _pad_dispose_receive_data();
                            if(appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[1] == 0x01)
                            {//确定是否需要应答
                                if(padSynBlock.blockNum)
                                {
                                    padSynBlock.control_answer = 0x81;
                                }
                                else
                                {
                                    padSynBlock.control_answer = 0x41;    
                                }  
                                appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER;
                                pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].answer_delay,ANSWER_DELAY);      
                            }         
                        }                 
                    }
                }   
                break;
            }
            case SYN_STATUS_RESEND_UPDATA_ACTIVE_RESULT:
            {
                if(TRANSMIT_RESULT_FAIL == app_link_request_get_transmit_result(SYSTEM_PAD))
                {//发送失败
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_ACTIVE;  
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    } 
                } 
                else if(TRANSMIT_RESULT_SUCCESS == app_link_request_get_transmit_result(SYSTEM_PAD))
                {//发送成功
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD; 
                    failCount = 0;
                }  
                break;
            }
             case SYN_STATUS_RESEND_UPDATA_WORD:
            {
                padSynBlock.blockNum = 0;
                for(i = 0; i < MASTER_PAD_NUM;i++)
                {
                    if(padOccupyWord[i])
                    {
                        occpupyFlag = false;
                        for(j = 0; j < MAX_DATA_POINT_LEN_PAD;j++)
                        {
                            if(padOccupyWord[i] & (0x01<<j))
                            {
                                app_general_push_pad_dp_stamp(i,j,pbc_timeStamp_get_stamp());
                                padSynBlock.regAddr_pad[padSynBlock.blockNum] = j;
                                padSynBlock.blockNum++;                              
                            }
                        }
                        padSynBlock.control_answer = 0x01;
                        padSynBlock.padNumber = i;
                        updata_port = i;
                        pbc_int16uToArray_bigEndian(app_general_pull_devive_id0(i),&idBuff[0]);
                        pbc_int16uToArray_bigEndian(app_general_pull_devive_id1(i),&idBuff[2]);
                        pbc_int16uToArray_bigEndian(app_general_pull_devive_id2(i),&idBuff[4]);
                        app_master_slave_send_syn_block(SYSTEM_PAD,&idBuff[0],padSynBlock);
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD_RESULT;
                        break;
                    }
                }
                if(occpupyFlag)
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                }  
                break;
            }
            case SYN_STATUS_RESEND_UPDATA_WORD_RESULT:
            {
                if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RERECEIVE_UPDATA_WORD;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].receive_timeout_delay,RECEIVE_TIMEOUT);
                    failCount = 0;
                }
                else if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_conflict)
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    } 
                }
                else if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_error)
                {//冲突报文或者未知错误
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    } 
                }
                break;
            }
            case SYN_STATUS_RERECEIVE_UPDATA_WORD:
            {
                if(appModbusSyn[SYSTEM_PAD].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_PAD].receiveOneMessage = false;
                   _pad_dispose_receive_data(); 
                    padOccupyWord[updata_port] = 0;
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE; 
                    
                }
                else if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_PAD].receive_timeout_delay))
                {//接收超时
					padOccupyWord[updata_port] = 0;
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                }
                break;
            }
            case SYN_STATUS_RESEND_UPDATA_WORD_ROLL_BACK:
            {
                if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_PAD].roll_back_delay))
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD;
                }
                break;
            }
            case SYN_STATUS_SEND_LIST_ACTIVE:
            {
               if(app_link_request_transmit_activation_request(SYSTEM_PAD))
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST_ACTIVE_RESULT;
                }  
                else
                {//发送之前可以接收数据2021/4/2
                    if(appModbusSyn[SYSTEM_PAD].receiveOneMessage)
                    {
                        appModbusSyn[SYSTEM_PAD].receiveOneMessage = false;
                        if(_syn_pull_write_device_id(&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkDstAddr[0]))
                        {
                            regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[9]);
                            app_push_data_point_message_sys(regAdd,&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[11]); 
                            padSynBlock.control_answer = 0x41; 
                            appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER;
                            pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].answer_delay,ANSWER_DELAY);
                        }
                        else
                        {
                            _pad_dispose_receive_data(); 
                            if(appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[1] == 0x01)
                            {//确定是否需要应答
                                if(padSynBlock.blockNum)
                                {
                                    padSynBlock.control_answer = 0x81;
                                }
                                else
                                {
                                    padSynBlock.control_answer = 0x41;    
                                }  
                                appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER;
                                pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].answer_delay,ANSWER_DELAY);      
                            }           
                        } 
                    }                 
                }   
                break;
            }
            case SYN_STATUS_SEND_LIST_ACTIVE_RESULT:
            {
                if(TRANSMIT_RESULT_FAIL == app_link_request_get_transmit_result(SYSTEM_PAD))
                {//发送失败
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST_ACTIVE;  
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                } 
                else if(TRANSMIT_RESULT_SUCCESS == app_link_request_get_transmit_result(SYSTEM_PAD))
                {//发送成功
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST; 
                    failCount = 0;
                }  
                break;
            }
            case SYN_STATUS_SEND_LIST:
            {
                if(pull_bough_link_is_busy(SYSTEM_PAD))
                {
                 
                }
                else
                {
                    for(i = 0;i < MAX_DEVICE_NUM;i++)
                    {
                        if(appModbusSyn[SYSTEM_PAD].listWord & (0x01<<i))
                        {
                            occpupyFlag = false;
                            logList = app_link_log_pull_device_list(SYSTEM_PAD);
                            padSynBlock.blockNum = 1;
                            padSynBlock.control_answer = 0x01;
                            padSynBlock.padNumber = i;
                            list_port = i;
                            app_general_push_pad_dp_stamp(i,DP_ADDR_PAD_SYSTEM_MESSAGE,pbc_timeStamp_get_stamp());
                            padSynBlock.regAddr_pad[0] = DP_ADDR_PAD_SYSTEM_MESSAGE;
                            app_master_slave_send_syn_block(SYSTEM_PAD,&logList[i].DeviceID[0],padSynBlock);
                            appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST_RESULT;
                            break;
                        }
                    }
                    if(occpupyFlag)
                    {
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }    
                }
                break;
            }
            case SYN_STATUS_SEND_LIST_RESULT:
            {
                if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RECEIVE_LIST;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].receive_timeout_delay,RECEIVE_TIMEOUT);
                    failCount = 0;
                }
                else if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_conflict)
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                else if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_error)
                {//冲突报文或者未知错误
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                break;
            }
            case SYN_STATUS_SEND_LIST_ROLL_BACK:
            {
                if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_PAD].roll_back_delay))
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST;;
                }
                break;
            }
            case SYN_STATUS_RECEIVE_LIST:
            {
                if(appModbusSyn[SYSTEM_PAD].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_PAD].receiveOneMessage = false;
                    if(_syn_pull_local_id(&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkDstAddr[0])) 
                    {//自己地址
                        appModbusSyn[SYSTEM_PAD].listWord &=  (~0x01<<list_port); 
                        _pad_dispose_receive_data();
                        if(appModbusSyn[SYSTEM_PAD].listWord == 0)
                        {
                            appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                            appModbusSyn[SYSTEM_PAD].updataWord = 0;
                        }   
                        else
                        {
                            appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST_ACTIVE;
                        }                                
                    }
                }
                else if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_PAD].receive_timeout_delay))
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_LIST_ACTIVE;
                }
                break;
            }
            case SYN_STATUS_RESEND_LIST_ACTIVE:
            {
                if(app_link_request_transmit_activation_request(SYSTEM_PAD))
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_LIST_ACTIVE_RESULT;
                }  
                else
                {
                    if(appModbusSyn[SYSTEM_PAD].receiveOneMessage)
                    {
                        appModbusSyn[SYSTEM_PAD].receiveOneMessage = false;
                        if(_syn_pull_write_device_id(&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkDstAddr[0]))
                        {
                            regAdd = pbc_arrayToInt16u_bigEndian(&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[9]);
                            app_push_data_point_message_sys(regAdd,&appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[11]); 
                            padSynBlock.control_answer = 0x41; 
                            appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER;
                            pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].answer_delay,ANSWER_DELAY);
                        }
                        else
                        {
                            _pad_dispose_receive_data(); 
                            if(appModbusSyn[SYSTEM_PAD].in_rev_data->Payload[1] == 0x01)
                            {//确定是否需要应答
                                if(padSynBlock.blockNum)
                                {
                                    padSynBlock.control_answer = 0x81;
                                }
                                else
                                {
                                    padSynBlock.control_answer = 0x41;    
                                }  
                                appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_ANSWER;
                                pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].answer_delay,ANSWER_DELAY);      
                            }           
                        }                       
                    }
                }   
                break;
            }
            case SYN_STATUS_RESEND_LIST_ACTIVE_RESULT:
            {
                if(TRANSMIT_RESULT_FAIL == app_link_request_get_transmit_result(SYSTEM_PAD))
                {//发送失败
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_LIST_ACTIVE;  
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                } 
                else if(TRANSMIT_RESULT_SUCCESS == app_link_request_get_transmit_result(SYSTEM_PAD))
                {//发送成功
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_LIST;
                    failCount = 0; 
                }  
                break;
            }
            case SYN_STATUS_RESEND_LIST:
            {
                if(pull_bough_link_is_busy(SYSTEM_PAD))
                {
                    
                }
                else
                {
                    for(i = 0;i < MAX_DEVICE_NUM;i++)
                    {
                        if(appModbusSyn[SYSTEM_PAD].listWord & (0x01<<i))
                        {
                            occpupyFlag = false;
                            logList = app_link_log_pull_device_list(SYSTEM_PAD);
                            padSynBlock.blockNum = 1;
                            padSynBlock.control_answer = 0x01;
                            padSynBlock.padNumber = i;
                            list_port = i;
                            app_general_push_pad_dp_stamp(i,DP_ADDR_PAD_SYSTEM_MESSAGE,pbc_timeStamp_get_stamp());
                            padSynBlock.regAddr_pad[0] = DP_ADDR_PAD_SYSTEM_MESSAGE;
                            app_master_slave_send_syn_block(SYSTEM_PAD,&logList[i].DeviceID[0],padSynBlock);
                            appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_LIST_RESULT;
                            break;
                        }
                    }  
                    if(occpupyFlag)
                    {
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }                  
                }
                break;
            }
            case SYN_STATUS_RESEND_LIST_RESULT:
            {
                if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_complete)
                {//发送完成
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RERECEIVE_LIST;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].receive_timeout_delay,RECEIVE_TIMEOUT);
                    failCount = 0;
                }
                else if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_conflict)
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                else if(pull_bough_transmit_monitor(SYSTEM_PAD) == bgk_trans_mon_error)
                {//冲突报文或者未知错误
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_UPDATA_WORD_ROLL_BACK;
                    pbc_reload_timerClock(&appModbusSyn[SYSTEM_PAD].roll_back_delay,ROLL_BACK_DELAY);
                    failCount++;
                    if(failCount >= MAX_FAIL_COUNT)
                    {
                        failCount = 0;
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                    }
                }
                break;
            }
            case SYN_STATUS_RERECEIVE_LIST:
            {
                if(appModbusSyn[SYSTEM_PAD].receiveOneMessage)
                {
                    appModbusSyn[SYSTEM_PAD].receiveOneMessage = false;
                    if(_syn_pull_local_id(&appModbusSyn[SYSTEM_PAD].in_rev_data->LinkDstAddr[0])) 
                    {//自己地址
                        appModbusSyn[SYSTEM_PAD].listWord &=  (~0x01<<list_port); 
                        _pad_dispose_receive_data();
                        if(appModbusSyn[SYSTEM_PAD].listWord == 0)
                        {
                            appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                            appModbusSyn[SYSTEM_PAD].updataWord = 0;
                        }   
                        else
                        {
                            appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST_ACTIVE;
                        }                                           
                    }                                           
                }
                else if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_PAD].receive_timeout_delay))
                {
                    appModbusSyn[SYSTEM_PAD].listWord &=  (~0x01<<list_port); 
                    if(appModbusSyn[SYSTEM_PAD].listWord == 0)
                    {
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
                        appModbusSyn[SYSTEM_PAD].updataWord = 0;
                    }   
                    else
                    {
                        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_SEND_LIST_ACTIVE;
                    }           
                }
                
                break;
            }
            case SYN_STATUS_RESEND_LIST_ROLL_BACK:
            {
                if(pbc_pull_timerIsCompleted(&appModbusSyn[SYSTEM_PAD].roll_back_delay))
                {
                    appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_RESEND_LIST;
                }
                break;
            }
            default:
            {
                break;
            }
        }
    } while (mainSynStatsu_backup != appModbusSyn[SYSTEM_PAD].mainSynStatsus);  
}

void app_link_syn_task(void)
{
    static bool cfg = false;
    if(cfg)
    {
        _control_pad_syn_task();//面板任务
        _master_system_syn_task();//系统集成
    }
    else
    {
        cfg = true;
        appModbusSyn[SYSTEM_PAD].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
        appModbusSyn[SYSTEM_MASTER].mainSynStatsus = SYN_STATUS_WAIT_RECEIVE;
    } 
}
void app_link_syn_push_receive_data(uint8_t in_solidNum,bgk_comm_buff_def *in_rev_data)
{
    appModbusSyn[in_solidNum].in_rev_data = in_rev_data;
    appModbusSyn[in_solidNum].receiveOneMessage = true;
    if(in_solidNum == SYSTEM_PAD)
    {      
        _control_pad_syn_task();
    }
    else if(in_solidNum == SYSTEM_MASTER)
    {
        _master_system_syn_task();
    }
}
void app_link_syn_push_outside_updata_word(uint8_t in_solidNum,uint32_t in_updataWord)
{   
    if(in_solidNum == SYSTEM_MASTER)
    {
        if(_syn_pull_type_hc_online())
        {
            appModbusSyn[in_solidNum].updataWord |= in_updataWord;
        }
    }
    else
    {
        appModbusSyn[in_solidNum].updataWord |= in_updataWord;
    }
}

void app_link_syn_push_pad_updata_word(uint8_t in_prot,uint32_t in_updataWord)
{
    padOccupyWord[in_prot] |= in_updataWord;
}

void app_link_syn_push_dhm_updata_word(uint8_t in_prot,uint32_t in_updataWord)
{
    dhmOccupyWord[in_prot] |= in_updataWord;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++