#ifndef app_general_H
#define app_general_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"

#define  MAX_DATA_POINT_LEN_PAD                16//DP最大长度
#define  MAX_DATA_POINT_LEN_DHM                15//DP最大长度
#define  MAX_DATA_POINT_LEN_SYSTEM             32//DP最大长度

#define  MASTER_PAD_NUM                 12//最大末端数量
#define  MASTER_PAD_VIRTUAL_NUM         4//虚拟末端数量
#define  MASTER_DHM_NUM                 2//最大除湿数量
#define  DHM_PORT_0                     10//除湿自动绑定端口
#define  DHM_PORT_1                     9

#define  ERROR_NTC_MIX_WATER            0X0001
#define  ERROR_NTC_IN_WATER             0X0002
#define  ERROR_NTC_BACK_WATER           0X0002
#define  ERROR_THREE_WAY_VAVLE          0X0004
#define  ERROR_AIRCOD_OFFLINE           0X0010
#define  ERROR_PORT1_OFFLINE            0X0020
#define  ERROR_PORT2_OFFLINE            0X0040
#define  ERROR_PORT3_OFFLINE            0X0080
#define  ERROR_AIRC4D_OFFLINE           0X0100
#define  ERROR_PORT5_OFFLINE            0X0200
#define  ERROR_PORT6_OFFLINE            0X0400
#define  ERROR_PORT7_OFFLINE            0X0800
#define  ERROR_PORT8_OFFLINE            0X1000
#define  ERROR_PORT9_OFFLINE            0X2000
#define  ERROR_PORT10_OFFLINE           0X4000
#define  PAD_NO_PHY_BIND                0Xff
/*系统故障*/
#define  SYS_ERROR_MIX_WATER             0X0001//混水故障
#define  SYS_ERROR_BACK_WATER            0X0002//回水故障
#define  SYS_ERROR_THREE_WAY_VAVLE       0X0004//三通阀故障
#define  SYS_ERROR_AIRCOD                0X0008//空调外机故障
#define  SYS_ERROR_IN_AIR_FAN            0X0010//进风风机故障
#define  SYS_ERROR_BACK_AIR_FAN          0X0020//回风风机故障
#define  SYS_ERROR_OUTDOOR_AIR_NTC       0X0040//户外综合传感器故障
#define  SYS_ERROR_BEFORE_FU_AIR_NTC     0X0080//氟盘前综合传感器故障
#define  SYS_ERROR_AFTER_FU_AIR_NTC      0X0100//氟盘后综合传感器故障
#define  SYS_ERROR_BACK_AIR_NTC          0X0200//回风综合传感器故障
#define  SYS_ERROR_EXHAST_AIR_NTC        0X0400//排风综合传感器故障
#define  SYS_ERROR_FIRST_SUPPLY_WATER    0X0800//一次侧供水故障
#define  SYS_ERROR_FIRST_BACK_WATER      0X0100//一次侧回水故障

#define ARICOD_READ_ONLY_REG_NUM            72
#define ARICOD_READ_WRITE_REG_NUM           60
enum
{
    Power_OFF               =0x0000,  //关机
    Power_ON                =0x0001,  //开机   
    ChildrenLock_ON         =0x0004,
    ChildrenLock_OFF        =0x0008,
    FillClear               =0x0010,  //
    PowerONSlt_ON           =0x0040,
    PowerONSlt_OFF          =0x0080,
    PrgTimeRun_ON           =0x0100,
    PrgTimeRun_OFF          =0x0200,
    OnceAM4100PM25          =0x0400, //测量一次AM4100的PM2.5值
};

void app_general_task(void);
/*时间戳*/
void app_general_push_system_dp_stamp(uint16_t in_index,uint32_t in_stamp);
uint32_t app_general_pull_system_dp_stamp(uint16_t in_index);
/*系统故障字*/
uint16_t app_general_pull_master_error_word(void);
void app_general_push_master_error_word(uint16_t in_error);
void app_general_clear_master_error_word(uint16_t in_error);
/*环控故障字*/
uint16_t app_general_pull_ae_error_word(void);
void app_general_push_ae_error_word(uint16_t in_error);
/*输配故障字*/
uint16_t app_general_pull_ac_error_word(void);
void app_general_push_ac_error_word(uint16_t in_error);
/*系统复位字*/
uint16_t app_general_pull_system_reset_word(void);
void app_general_push_system_reset_word(uint16_t in_status);
/*系统状态字*/
uint16_t app_general_pull_system_status_word(void);
void app_general_push_system_status_word(uint16_t in_status);
/*开关机*/
void app_general_push_power_status(bool in_power_status);
bool  app_general_pull_power_status(void);
/*模式*/
void app_general_push_aircod_mode(AirRunMode_Def in_mode);
AirRunMode_Def app_general_pull_aircod_mode(void);
/*设定湿度*/
void app_general_push_aircod_humidity(int16_t in_set_humidity);
int16_t app_general_pull_aircod_humidity(void);
/*设定风速*/
void app_general_push_aircod_fanSpeed(NewAirLevelSet_Def in_speed);
NewAirLevelSet_Def app_general_pull_aircod_fanSpeed(void);
/*制冷设定温度、制热设定温度*/
void app_general_push_aircod_cold_temp(int16_t in_set_temp);
void app_general_push_aircod_heat_temp(int16_t in_set_temp);
int16_t app_general_pull_aircod_cold_temp(void);
int16_t app_general_pull_aircod_heat_temp(void);
/*新风PWM*/
uint8_t app_general_pull_new_air_pwm_low(void);
uint8_t app_general_pull_new_air_pwm_mid(void);
uint8_t app_general_pull_new_air_pwm_high(void);
void app_general_push_new_air_pwm_low(uint8_t in_pwm);
void app_general_push_new_air_pwm_mid(uint8_t in_pwm);
void app_general_push_new_air_pwm_high(uint8_t in_pwm);

/*回风风PWM*/
uint8_t app_general_pull_back_air_pwm_low(void);
uint8_t app_general_pull_back_air_pwm_mid(void);
uint8_t app_general_pull_back_air_pwm_high(void);
void app_general_push_back_air_pwm_low(uint8_t in_pwm);
void app_general_push_back_air_pwm_mid(uint8_t in_pwm);
void app_general_push_back_air_pwm_high(uint8_t in_pwm);

/*主机制冷制热生活热水设定水温*/
void app_general_push_set_cold_water_temp(int16_t in_set_temp);
void app_general_push_set_heat_water_temp(int16_t in_set_temp);
void app_general_push_set_living_water_temp(int16_t in_set_temp);
int16_t app_general_pull_set_cold_water_temp(void);
int16_t app_general_pull_set_heat_water_temp(void);
int16_t app_general_pull_set_living_water_temp(void);
/*户外进风/氟盘前/氟盘后/回风/排风温湿度*/
void app_general_push_outdoor_temp(int16_t in_temp);
int16_t app_general_pull_outdoor_temp(void);
void app_general_push_outdoor_hum(int16_t in_hum);
int16_t app_general_pull_outdoor_hum(void);
void app_general_push_before_fu_temp(int16_t in_temp);
int16_t app_general_pull_before_fu_temp(void);
void app_general_push_before_fu_hum(int16_t in_hum);
int16_t app_general_pull_before_fu_hum(void);
void app_general_push_after_fu_temp(int16_t in_temp);
int16_t app_general_pull_after_fu_temp(void);
void app_general_push_after_fu_hum(int16_t in_hum);
int16_t app_general_pull_after_fu_hum(void);
void app_general_push_backair_temp(int16_t in_temp);
int16_t app_general_pull_backair_temp(void);
void app_general_push_backair_hum(int16_t in_hum);
int16_t app_general_pull_backair_hum(void);
void app_general_push_exhastair_temp(int16_t in_temp);
int16_t app_general_pull_exhastair_temp(void);
void app_general_push_exhastair_hum(int16_t in_hum);
int16_t app_general_pull_exhastair_hum(void);
/*回风co2 pm25*/
void app_general_push_backair_co2(int16_t in_set_co2);
int16_t app_general_pull_backair_co2(void);
void app_general_push_backair_pm25(int16_t in_set_pm25);
int16_t app_general_pull_backair_pm25(void);
/*设定温度带宽*/
void app_general_push_aircod_setTemp_deadZone(int16_t in_deadZone);
int16_t app_general_pull_aircod_setTemp_deadZone(void);
/*设定湿度带宽*/
void app_general_push_aircod_setHum_deadZone(int16_t in_deadZone);
int16_t app_general_pull_aircod_setHum_deadZone(void);
/*新风风机转速*/
uint16_t   app_general_pull_aircod_newair_speed(void);
void app_general_push_aircod_newair_speed(uint16_t in_speed);
/*回风风机转速*/
uint16_t app_general_pull_aircod_backair_speed(void);
void app_general_push_aircod_backair_speed(uint16_t in_speed);
/*氟机水机频率*/
void app_general_push_fu_machine_fre(uint16_t in_fre);
uint16_t app_general_pull_fu_machine_fre(void);
void app_general_push_water_machine_fre(uint16_t in_fre);
uint16_t app_general_pull_water_machine_fre(void);

/*主机供水温度、生活热水温度、户外温度*/
int16_t app_general_pull_master_supply_temp(void);
void app_general_push_master_supply_temp(int16_t in_temp);
int16_t app_general_pull_master_living_temp(void);
void app_general_push_master_living_temp(int16_t in_temp);
int16_t app_general_pull_master_outdoor_temp(void);
void app_general_push_master_outdoor_temp(int16_t in_temp);

/*湿度温度co2pm25修正系数  户外 氟盘前 氟盘后 回风 排风*/
int16_t app_general_pull_adjust_outdoor_hum(void);
int16_t app_general_pull_adjust_outdoor_temp(void);
int16_t app_general_pull_adjust_outdoor_co2(void);
int16_t app_general_pull_adjust_outdoor_pm25(void);
int16_t app_general_pull_adjust_beforfu_hum(void);
int16_t app_general_pull_adjust_beforfu_temp(void);
int16_t app_general_pull_adjust_beforfu_co2(void);
int16_t app_general_pull_adjust_beforfu_pm25(void);
int16_t app_general_pull_adjust_afterfu_hum(void);
int16_t app_general_pull_adjust_afterfu_temp(void);
int16_t app_general_pull_adjust_afterfu_co2(void);
int16_t app_general_pull_adjust_afterfu_pm25(void);
int16_t app_general_pull_adjust_backair_hum(void);
int16_t app_general_pull_adjust_backair_temp(void);
int16_t app_general_pull_adjust_backair_co2(void);
int16_t app_general_pull_adjust_backair_pm25(void);
int16_t app_general_pull_adjust_exhastair_hum(void);
int16_t app_general_pull_adjust_exhastair_temp(void);
int16_t app_general_pull_adjust_exhastair_co2(void);
int16_t app_general_pull_adjust_exhastair_pm25(void);
void app_general_push_adjust_outdoor_hum(int16_t in_hum);
void app_general_push_adjust_outdoor_temp(int16_t in_temp);
void app_general_push_adjust_outdoor_co2(int16_t in_co2);
void app_general_push_adjust_outdoor_pm25(int16_t in_pm25);
void app_general_push_adjust_beforfu_hum(int16_t in_hum);
void app_general_push_adjust_beforfu_temp(int16_t in_temp);
void app_general_push_adjust_beforfu_co2(int16_t in_co2);
void app_general_push_adjust_beforfu_pm25(int16_t in_pm25);
void app_general_push_adjust_afterfu_hum(int16_t in_hum);
void app_general_push_adjust_afterfu_temp(int16_t in_temp);
void app_general_push_adjust_afterfu_co2(int16_t in_co2);
void app_general_push_adjust_afterfu_pm25(int16_t in_pm25);
void app_general_push_adjust_backair_hum(int16_t in_hum);
void app_general_push_adjust_backair_temp(int16_t in_temp);
void app_general_push_adjust_backair_co2(int16_t in_co2);
void app_general_push_adjust_backair_pm25(int16_t in_pm25);
void app_general_push_adjust_exhastair_hum(int16_t in_hum);
void app_general_push_adjust_exhastair_temp(int16_t in_temp);
void app_general_push_adjust_exhastair_co2(int16_t in_co2);
void app_general_push_adjust_exhastair_pm25(int16_t in_pm25);
/*环控能需预冷预热输出*/
bool app_general_pull_anergy_need(void);
void app_general_push_anergy_need(bool in_status);
/*系统传感器错误*/
uint16_t app_general_pull_ntc_error_word(void);
void app_general_push_ntc_error_word(uint16_t in_error);
/*输配传感器错误*/
uint16_t app_general_pull_ac_ntc_error_word(void);
void app_general_push_ac_ntc_error_word(uint16_t in_error);
/*环控传感器错误*/
uint16_t app_general_pull_ae_ntc_error_word(void);
void app_general_push_ae_ntc_error_word(uint16_t in_error);

/*混水制冷/制热设定温度 */
void app_general_push_set_mixwater_cold_temp(int16_t in_set_temp);
void app_general_push_set_mixwater_heat_temp(int16_t in_set_temp);
int16_t app_general_pull_set_mixwater_cold_temp(void);
int16_t app_general_pull_set_mixwater_heat_temp(void);

/*输配水泵状态*/
bool app_general_pull_pump_output(void);
void app_general_push_pump_output(bool in_status);
/*输配三通阀门输出状态*/
bool app_general_pull_three_vavle_output(void);
/*输配混水AI目标温度 */
int16_t app_general_pull_ai_dest_temp(void);
/*输配混水AI使能*/
bool app_general_pull_ai_enable_status(void);
void app_general_push_ai_enable_status(bool in_status);
/*输配防冻保护*/
uint8_t app_general_pull_mix_freeze_protect(void);
void app_general_push_mix_freeze_protect(uint8_t  in_stemp);
/*传感器错误*/
/*输配未绑定的阀门列表(风盘) */
uint16_t app_general_pull_unbind_list_fan(void);
void app_general_push_unbind_list_fan(uint16_t in_unbind);
/*输配未绑定的阀门列表(辐射)*/
uint16_t app_general_pull_unbind_list_warm(void);
void app_general_push_unbind_list_warm(uint16_t in_unbind);
/*重复绑定信息*/
void app_general_push_pad_repeat_bind_list(uint16_t in_list);
uint16_t app_general_pull_pad_repeat_bind_list(void);
/*防冻能需*/
bool app_pull_low_protect_reguest(void);

/*生活热水使能*/
int16_t app_general_pull_hotwater_enable(void);
void app_general_push_hotwater_enable(uint16_t reg_dat);
/*滤芯更换周期*/
void app_general_push_filter_time(int16_t in_time);
int16_t app_general_pull_filter_time(void);
/*滤芯使用时间*/
void app_general_push_filter_usetime(int16_t in_time);
int16_t app_general_pull_filter_usetime(void);
void app_general_push_filter_usetime_inside(int16_t in_time);
/*风阀互换*/
void app_general_push_wind_value(bool reg_dat);
bool app_general_pull_wind_value(void);


/*末端接口*/
timerClock_def* app_general_pull_pad_id_ocupy_time(uint8_t in_solidNum);
/*物理端口绑定信息*/
uint8_t  app_general_pull_pad_phy_port_bind_message(uint8_t in_solidNum);
/*末端id占用信息*/
void app_general_push_pad_id_use_message(uint8_t in_solidNum,bool in_status);
bool app_general_pull_pad_id_use_message(uint8_t in_solidNum);
/*末端时间戳*/
void app_general_push_pad_dp_stamp(uint8_t in_solidNum,uint8_t in_index,uint32_t in_stamp);
uint32_t app_general_pull_pad_dp_stamp(uint8_t in_solidNum,uint8_t in_index);

/*设备故障字*/
void app_general_push_devive_error_word(uint8_t in_solidNum,uint16_t in_error);
uint16_t app_general_pull_devive_error_word(uint8_t in_solidNum);

/*在线状态*/
void app_general_push_devive_online(uint8_t in_solidNum,bool in_status);
bool app_general_pull_devive_online(uint8_t in_solidNum);

/*设备类型*/
void app_general_push_devive_type(uint8_t in_solidNum,uint16_t in_type);
uint16_t app_general_pull_devive_type(uint8_t in_solidNum);

/*版本號*/
void app_general_push_pad_version(uint8_t in_solidNum,uint16_t in_type);
uint16_t app_general_pull_pad_version(uint8_t in_solidNum);
/*硬件标识*/
void app_general_push_pad_hardware_sign(uint8_t in_solidNum,uint16_t in_type);
uint16_t app_general_pull_pad_hardware_sign(uint8_t in_solidNum);
/*设备ID*/
void app_general_push_devive_id0(uint8_t in_solidNum,uint16_t in_id);
uint16_t app_general_pull_devive_id0(uint8_t in_solidNum);
void app_general_push_devive_id1(uint8_t in_solidNum,uint16_t in_id);
uint16_t app_general_pull_devive_id1(uint8_t in_solidNum);
void app_general_push_devive_id2(uint8_t in_solidNum,uint16_t in_id);
uint16_t app_general_pull_devive_id2(uint8_t in_solidNum);

/*开关机*/
void app_general_push_devive_power(uint8_t in_solidNum,uint8_t in_status);
bool app_general_pull_devive_power(uint8_t in_solidNum);

/*制冷设定温度*//*制热设定温度 */
void app_general_push_pad_set_cold_temp(uint8_t in_solidNum,int16_t in_set_temp);
void app_general_push_pad_set_heat_temp(uint8_t in_solidNum,int16_t in_set_temp);
int16_t app_general_pull_pad_set_cold_temp(uint8_t in_solidNum);
int16_t app_general_pull_pad_set_heat_temp(uint8_t in_solidNum);

/*露点温度*/
void app_general_push_pad_lew_drop_temp(uint8_t in_solidNum,int16_t in_temp);
int16_t app_general_pull_pad_lew_drop_temp(uint8_t in_solidNum);

/*冷热运行状态*/
void app_general_push_pad_cold_warm_status(uint8_t in_solidNum,uint8_t in_status);
uint8_t app_general_pull_pad_cold_warm_status(uint8_t in_solidNum);

/*防冻保护*/
void app_general_push_pad_freeze_protect(uint8_t in_solidNum,bool in_status);
bool app_general_pull_pad_freeze_protect(uint8_t in_solidNum);

/*防冻温度*/
void app_general_push_pad_freeze_temp(uint8_t in_solidNum,int16_t in_temp);
int16_t app_general_pull_pad_freeze_temp(uint8_t in_solidNum);

/*童锁功能*/
void app_general_push_pad_child_lock(uint8_t in_solidNum,bool in_status);
bool app_general_pull_pad_child_lock(uint8_t in_solidNum);

/*上电(关机)/(记忆)*/
void app_general_push_pad_onoff_memory(uint8_t in_solidNum,bool in_status);
bool app_general_pull_pad_onoff_memory(uint8_t in_solidNum);

/*制冷舒适温度*/
void app_general_push_pad_cold_comfortable_temp(uint8_t in_solidNum,int16_t in_temp);
int16_t app_general_pull_pad_cold_comfortable_temp(uint8_t in_solidNum);

/*制热舒适温度*/
void app_general_push_pad_heat_comfortable_temp(uint8_t in_solidNum,int16_t in_temp);
int16_t app_general_pull_pad_heat_comfortable_temp(uint8_t in_solidNum);

/*最高设定温度*/
void app_general_push_pad_set_high_temp(uint8_t in_solidNum,int16_t in_temp);
int16_t app_general_pull_pad_set_high_temp(uint8_t in_solidNum);

/*最低设定温度*/
void app_general_push_pad_set_low_temp(uint8_t in_solidNum,int16_t in_temp);
int16_t app_general_pull_pad_set_low_temp(uint8_t in_solidNum);

/*控温带宽*/
void app_general_push_pad_deadzone_temp(uint8_t in_solidNum,int16_t in_temp);
int16_t app_general_pull_pad_deadzone_temp(uint8_t in_solidNum);

/*露点带宽*/
void app_general_push_pad_deadzone_lewtemp(uint8_t in_solidNum,int16_t in_temp);
int16_t app_general_pull_pad_deadzone_lewtemp(uint8_t in_solidNum);

/*测量温度*/
void app_general_push_pad_measure_temp(uint8_t in_solidNum,int16_t in_temp);
int16_t app_general_pull_pad_measure_temp(uint8_t in_solidNum);

/*测量湿度*/
void app_general_push_pad_measure_hum(uint8_t in_solidNum,uint16_t in_temp);
uint16_t app_general_pull_pad_measure_hum(uint8_t in_solidNum);

/*辐射阀门需求*/
void app_general_push_pad_warm_need(uint8_t in_solidNum,uint16_t in_status);
uint16_t app_general_pull_pad_warm_need(uint8_t in_solidNum);

/*设定风速 */
void app_general_push_pad_set_fan_speed(uint8_t in_solidNum,uint8_t in_speded);
uint8_t app_general_pull_pad_set_fan_speed(uint8_t in_solidNum);

/*风机受控*/
void app_general_push_pad_fan_control(uint8_t in_solidNum,bool in_status);
bool app_general_pull_pad_fan_control(uint8_t in_solidNum);

/*低风量PWM值*/
void app_general_push_pad_set_pwm_low(uint8_t in_solidNum,uint16_t in_pwm);
uint16_t app_general_pull_pad_set_pwm_low(uint8_t in_solidNum);

/*中风量PWM值*/
void app_general_push_pad_set_pwm_mid(uint8_t in_solidNum,uint16_t in_pwm);
uint16_t app_general_pull_pad_set_pwm_mid(uint8_t in_solidNum);

/*高风量PWM值*/
void app_general_push_pad_set_pwm_high(uint8_t in_solidNum,uint16_t in_pwm);
uint16_t app_general_pull_pad_set_pwm_high(uint8_t in_solidNum);

/*AI制冷协同带宽*/
void app_general_push_pad_ai_cold_diff(uint8_t in_solidNum,int16_t in_diff);
int16_t app_general_pull_pad_ai_cold_diff(uint8_t in_solidNum);

/*AI制热协同带宽 */
void app_general_push_pad_ai_heat_diff(uint8_t in_solidNum,int16_t in_diff);
int16_t app_general_pull_pad_ai_heat_diff(uint8_t in_solidNum);
/*制冷协同使能 */
void app_general_push_pad_cold_colla_enable(uint8_t in_solidNum,bool in_status);
bool app_general_pull_pad_cold_colla_enable(uint8_t in_solidNum);
/*制热协同使能 */
void app_general_push_pad_warm_colla_enable(uint8_t in_solidNum,bool in_status);
bool app_general_pull_pad_warm_colla_enable(uint8_t in_solidNum);

/*风阀需求*/
void app_general_push_pad_fan_need(uint8_t in_solidNum,uint16_t in_status);
uint16_t app_general_pull_pad_fan_need(uint8_t in_solidNum);
/*风机输出状态*/
void app_general_push_pad_fan_out_speed(uint8_t in_solidNum,uint8_t in_speed);
uint8_t app_general_pull_pad_fan_out_speed(uint8_t in_solidNum);

/*风机转速*/
void app_general_push_pad_fan_speed_output(uint8_t in_solidNum,uint16_t in_speed);
uint16_t app_general_pull_pad_fan_speed_output(uint8_t in_solidNum);
/*末端数量*/
void app_general_push_pad_control_num(uint8_t in_solidNum,uint8_t in_num);
uint8_t app_general_pull_pad_control_num(uint8_t in_solidNum);
/*双末端模式选择*/
void app_general_push_pad_two_output_mode(uint8_t in_solidNum,uint8_t in_mode);
uint8_t app_general_pull_pad_two_output_mode(uint8_t in_solidNum);
/*绑定的阀门列表 (风盘)*/
void app_general_push_pad_bind_list_fan(uint8_t in_solidNum,uint16_t in_list);
uint16_t app_general_pull_pad_bind_list_fan(uint8_t in_solidNum);
/*绑定的阀门列表 (辐射)*/
void app_general_push_pad_bind_list_warm(uint8_t in_solidNum,uint16_t in_list);
uint16_t app_general_pull_pad_bind_list_warm(uint8_t in_solidNum);
/*校温*/
void app_general_push_pad_adjust_temp(uint8_t in_solidNum,int16_t in_temp);
int16_t app_general_pull_pad_adjust_temp(uint8_t in_solidNum);
/*制冷制热回水设定温度*/
int16_t app_general_pull_coolbackwater_set_temp(void);
int16_t app_general_pull_hotbackwater_set_temp(void);
void app_general_push_coolbackwater_set_temp(int16_t  in_set_temp);
void app_general_push_hotbackwater_set_temp(int16_t  in_set_temp);
/*校湿*/
void app_general_push_pad_adjust_hum(uint8_t in_solidNum,int16_t in_hum);
int16_t app_general_pull_pad_adjust_hum(uint8_t in_solidNum);

/*辐射类型选择*/
void app_general_push_pad_type_warm_choose(uint8_t in_solidNum,uint8_t in_mode);
uint8_t app_general_pull_pad_type_warm_choose(uint8_t in_solidNum);

/*房间面积*/
void app_general_push_pad_room_area(uint8_t in_solidNum,uint8_t in_mode);
uint8_t app_general_pull_pad_room_area(uint8_t in_solidNum);


/*绑定故障*/
void app_general_push_pad_bind_error(uint8_t in_solidNum,uint16_t in_error);
uint16_t app_general_pull_pad_bind_error(uint8_t in_solidNum);
/*露点保护状态*/
void app_general_push_pad_lew_dorp_temp_output(uint8_t in_solidNum,bool in_status);
bool app_general_pull_pad_lew_dorp_temp_output(uint8_t in_solidNum);
/*露点状态*/
void app_general_push_system_lew_temp_status(uint16_t in_status);
uint16_t app_general_pull_system_lew_temp_status(void);
/*末端输出状态*/
uint16_t app_general_pull_pad_output_status(void);
/*综合传感器故障*/
bool pull_integrated_sensor_error(void);
void app_general_push_error_word(uint16_t in_errorBit);
void app_general_clear_error_word(uint16_t in_errorBit);
uint16_t app_general_pull_error_word(void);
uint16_t GetRandomDelayTime(void);
void check_rebind_list(void);
/*系统能需*/
uint8_t app_pull_system_energy_need(void);
/*新风效率*/
void app_general_push_freshair_effciency(int16_t in_effciency);
int16_t app_general_pull_freshair_effciency(void);
/*485参数   地址 波特率  奇偶校验位*/
void app_general_push_adress485(uint8_t in_address);
void app_general_push_baudrate(uint16_t in_baudRate);
void app_general_push_checkbit(uint8_t in_check);
uint8_t app_general_pull_adress485(void);
uint16_t app_general_pull_baudrate(void);
uint8_t app_general_pull_checkbit(void);
/*远程受控模式*/
void app_general_push_remote_control(bool in_remote_control);
bool  app_general_pull_remote_control(void);
/*远程继电器*/
void app_general_push_remote_relay(uint8_t in_port,bool in_remote_control);
bool  app_general_pull_remote_relay(uint8_t in_port);
/*远程水泵*/
void app_general_push_remote_pump(bool in_remote_status);
bool  app_general_pull_remote_pump(void);
/*远程三通阀*/
void app_general_push_remote_threeVavle(bool in_remote_status);
bool  app_general_pull_remote_threeVavle(void);
/*远程旁通*/
void app_general_push_remote_bypass(bool in_remote_status);
bool  app_general_pull_remote_bypass(void);
/*远程三通阀开度*/
void app_general_push_remote_degree(uint8_t in_vavle);
uint8_t  app_general_pull_remote_degree(void);
/*调试使能*/
bool app_general_pull_debug_enable(void);
void app_general_push_debug_enable(bool in_status);
/*制冷无能需设定温度*/
void app_general_push_cold_no_need_set_temp(int16_t in_set_temp);
int16_t app_general_pull_cold_no_need_set_temp(void);
/*制冷风盘能需设定温度*/
void app_general_push_cold_fan_need_set_temp(int16_t in_set_temp);
int16_t app_general_pull_cold_fan_need_set_temp(void);
/*制冷辐射能需设定温度*/
void app_general_push_cold_warm_need_set_temp(int16_t in_set_temp);
int16_t app_general_pull_cold_warm_need_set_temp(void);
/*制冷露点配置温度*/
void app_general_push_config_lew_set_temp(int16_t in_set_temp);
int16_t app_general_pull_config_lew_set_temp(void);
/*制热无能需设定温度*/
void app_general_push_heat_no_need_set_temp(int16_t in_set_temp);
int16_t app_general_pull_heat_no_need_set_temp(void);
/*制热风盘能需设定温度*/
void app_general_push_heat_fan_need_set_temp(int16_t in_set_temp);
int16_t app_general_pull_heat_fan_need_set_temp(void);
/*制热辐射能需设定温度*/
void app_general_push_heat_warm_need_set_temp(int16_t in_set_temp);
int16_t app_general_pull_heat_warm_need_set_temp(void);
/*制热回风配置温度*/
void app_general_push_config_back_wind_set_temp(int16_t in_set_temp);
int16_t app_general_pull_config_back_wind_set_temp(void);
/*除湿设定配置*/
void app_general_push_config_hum_set(int16_t in_set_temp);
int16_t app_general_pull_config_hum_set(void);
/*制冷风温最大设定温度*/
void app_general_push_cold_wind_max_set_temp(int16_t in_set_temp);
int16_t app_general_pull_cold_wind_max_set_temp(void);
/*制热风温最小设定温度 */
void app_general_push_heat_wind_min_set_temp(int16_t in_set_temp);
int16_t app_general_pull_heat_wind_min_set_temp(void);
/*制热风温最大设定温度*/
void app_general_push_heat_wind_max_set_temp(int16_t in_set_temp);
int16_t app_general_pull_heat_wind_max_set_temp(void);
/*主控制策略*/
uint8_t app_general_pull_main_control_method(void);
void app_general_push_main_control_method(uint8_t in_method);
/*户外除湿状态*/
bool app_general_pull_indoor_dehum_status(void);
void app_general_push_indoor_dehum_status(bool in_status);
/*获取开机辐射末端最大露点温度*/
int16_t app_pull_max_low_temp(void);
/*露点状态上限(开启)带宽 */
void app_general_push_lew_status_open_status(int16_t in_set_temp);
int16_t app_general_pull_lew_status_open_status(void);
/*露点状态下限(关闭)带宽 */
void app_general_push_lew_status_close_status(int16_t in_set_temp);
int16_t app_general_pull_lew_status_close_status(void);
/*输配软件复位 */
void app_general_push_cc_reset(uint16_t in_code);
/*环控软件复位 */
void app_general_push_hc_reset(uint16_t in_code);
/*水机开关机*/
bool app_general_pull_water_machine_status(void);
void app_general_push_water_machine_status(bool in_status);
//面板版本号升级
uint16_t app_general_pull_version_pad_list(void);
bool app_general_pull_version_pad_flag(void);
void app_general_clear_version_pad_flag(void);
void app_general_clear_port_version(uint8_t in_port);
//风盘版本号升级
uint16_t app_general_pull_version_fan_list(void);
bool app_general_pull_version_fan_flag(void);
void app_general_clear_version_fan_flag(void);


/*除湿模块相关接口*/

/*末端id占用信息*/
void app_general_push_dhm_id_use_message(uint8_t in_port,bool in_status);
bool app_general_pull_dhm_id_use_message(uint8_t in_port);
/*公共占用端口*/
uint8_t app_general_pull_dhm_use_port(uint8_t in_port);
void app_general_push_dhm_use_port(uint8_t in_port,uint8_t in_com);

/*除湿模块时间戳*/
void app_general_push_dhm_dp_stamp(uint8_t in_solidNum,uint16_t in_index,uint32_t in_stamp);
uint32_t app_general_pull_dhm_dp_stamp(uint8_t in_solidNum,uint16_t in_index);
/*设定湿度*/
void app_general_push_dhm_aircod_humidity(uint8_t in_port,int16_t in_set_humidity);
int16_t app_general_pull_dhm_aircod_humidity(uint8_t in_port);
/*除湿需求*/
bool app_general_pull_dhm_dehum_request(uint8_t in_port);
void app_general_push_dhm_dehum_request(uint8_t in_port,bool in_status);
//ptc测量温度
int16_t app_general_pull_dhm_ptc_temp(uint8_t in_port);
void  app_general_push_dhm_ptc_temp(uint8_t in_port,int16_t in_temp);
/*设定风速*/
void app_general_push_dhm_fanSpeed(uint8_t in_port,NewAirLevelSet_Def in_speed);
NewAirLevelSet_Def app_general_pull_dhm_fanSpeed(uint8_t in_port);
//iec5测量温度
int16_t app_general_pull_dhm_iec5_temp(uint8_t in_port);
void  app_general_push_dhm_iec5_temp(uint8_t in_port,int16_t in_temp);
/*除湿输出状态*/
uint16_t app_general_pull_dhm_dm_output_status(uint8_t in_port);
void  app_general_push_dhm_dm_output_status(uint8_t in_port,uint16_t in_status);
/*新风PWM*/
uint8_t app_general_pull_dhm_new_air_pwm_low(uint8_t in_port);
uint8_t app_general_pull_dhm_new_air_pwm_mid(uint8_t in_port);
uint8_t app_general_pull_dhm_new_air_pwm_high(uint8_t in_port);
void app_general_push_dhm_new_air_pwm_low(uint8_t in_port,uint8_t in_pwm);
void app_general_push_dhm_new_air_pwm_mid(uint8_t in_port,uint8_t in_pwm);
void app_general_push_dhm_new_air_pwm_high(uint8_t in_port,uint8_t in_pwm);
/*回风风PWM*/
uint8_t app_general_pull_dhm_back_air_pwm_low(uint8_t in_port);
uint8_t app_general_pull_dhm_back_air_pwm_mid(uint8_t in_port);
uint8_t app_general_pull_dhm_back_air_pwm_high(uint8_t in_port);
void app_general_push_dhm_back_air_pwm_low(uint8_t in_port,uint8_t in_pwm);
void app_general_push_dhm_back_air_pwm_mid(uint8_t in_port,uint8_t in_pwm);
void app_general_push_dhm_back_air_pwm_high(uint8_t in_port,uint8_t in_pwm);
/*户外进风/氟盘前/氟盘后/回风/排风温湿度*/
void app_general_push_dhm_outdoor_temp(uint8_t in_port,int16_t in_temp);
int16_t app_general_pull_dhm_outdoor_temp(uint8_t in_port);
void app_general_push_dhm_outdoor_hum(uint8_t in_port,int16_t in_hum);
int16_t app_general_pull_dhm_outdoor_hum(uint8_t in_port);

int16_t app_general_pull_dhm_adjust_outdoor_hum(uint8_t in_port);
void app_general_push_dhm_adjust_outdoor_hum(uint8_t in_port,int16_t in_hum);
int16_t app_general_pull_dhm_adjust_outdoor_temp(uint8_t in_port);
void app_general_push_dhm_adjust_outdoor_temp(uint8_t in_port,int16_t in_temp);


void app_general_push_dhm_before_fu_temp(uint8_t in_port,int16_t in_temp);
int16_t app_general_pull_dhm_before_fu_temp(uint8_t in_port);
void app_general_push_dhm_before_fu_hum(uint8_t in_port,int16_t in_hum);
int16_t app_general_pull_dhm_before_fu_hum(uint8_t in_port);
int16_t app_general_pull_dhm_adjust_beforfu_hum(uint8_t in_port);
void app_general_push_dhm_adjust_beforfu_hum(uint8_t in_port,int16_t in_hum);
int16_t app_general_pull_dhm_adjust_beforfu_temp(uint8_t in_port);
void app_general_push_dhm_adjust_beforfu_temp(uint8_t in_port,int16_t in_temp);


void app_general_push_dhm_after_fu_temp(uint8_t in_port,int16_t in_temp);
int16_t app_general_pull_dhm_after_fu_temp(uint8_t in_port);
void app_general_push_dhm_after_fu_hum(uint8_t in_port,int16_t in_hum);
int16_t app_general_pull_dhm_after_fu_hum(uint8_t in_port);
int16_t app_general_pull_dhm_adjust_afterfu_hum(uint8_t in_port);
void app_general_push_dhm_adjust_afterfu_hum(uint8_t in_port,int16_t in_hum);
int16_t app_general_pull_dhm_adjust_afterfu_temp(uint8_t in_port);
void app_general_push_dhm_adjust_afterfu_temp(uint8_t in_port,int16_t in_temp);


void app_general_push_dhm_backair_temp(uint8_t in_port,int16_t in_temp);
int16_t app_general_pull_dhm_backair_temp(uint8_t in_port);
void app_general_push_dhm_backair_hum(uint8_t in_port,int16_t in_hum);
int16_t app_general_pull_dhm_backair_hum(uint8_t in_port);
void app_general_push_dhm_backair_co2(uint8_t in_port,int16_t in_set_co2);
int16_t app_general_pull_dhm_backair_co2(uint8_t in_port);
void app_general_push_dhm_backair_pm25(uint8_t in_port,int16_t in_set_pm25);
int16_t app_general_pull_dhm_backair_pm25(uint8_t in_port);
int16_t app_general_pull_dhm_adjust_backair_hum(uint8_t in_port);
void app_general_push_dhm_adjust_backair_hum(uint8_t in_port,int16_t in_hum);
int16_t app_general_pull_dhm_adjust_backair_temp(uint8_t in_port);
void app_general_push_dhm_adjust_backair_temp(uint8_t in_port,int16_t in_temp);
int16_t app_general_pull_dhm_adjust_backair_co2(uint8_t in_port);
int16_t app_general_pull_dhm_adjust_backair_pm25(uint8_t in_port);
void app_general_push_dhm_adjust_backair_co2(uint8_t in_port,int16_t in_co2);
void app_general_push_dhm_adjust_backair_pm25(uint8_t in_port,int16_t in_pm25);

void app_general_push_dhm_exhastair_temp(uint8_t in_port,int16_t in_temp);
int16_t app_general_pull_dhm_exhastair_temp(uint8_t in_port);
void app_general_push_dhm_exhastair_hum(uint8_t in_port,int16_t in_hum);
int16_t app_general_pull_dhm_exhastair_hum(uint8_t in_port);
void app_general_push_dhm_adjust_exhastair_hum(uint8_t in_port,int16_t in_hum);
int16_t app_general_pull_dhm_adjust_exhastair_hum(uint8_t in_port);
void app_general_push_dhm_adjust_exhastair_temp(uint8_t in_port,int16_t in_temp);
int16_t app_general_pull_dhm_adjust_exhastair_temp(uint8_t in_port);


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif