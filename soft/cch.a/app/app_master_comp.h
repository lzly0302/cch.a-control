#ifndef app_master_comp_H
#define app_master_comp_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define DRIVE_BOARD_CUTRENT_FU_FRE          2//氟机实际频率
#define DRIVE_BOARD_CUTRENT_WATER_FRE       28//水机实际频率
#define DRIVE_BOARD_TH7_TEMP                45//
#define DRIVE_BOARD_TH14_TEMP               15//
#define DRIVE_BOARD_SET_MODE           		5001//设置模式
#define DRIVE_BOARD_FORCE_SET_MODE          5002//
#define DRIVE_BOARD_POWER_ON_OFF          	5003//开关机
#define DRIVE_BOARD_HOTWATER_ENABLE         5004//热水使能
#define DRIVE_BOARD_COOL_SET_TEMP      		5007//2#制冷回风设置温度 
#define DRIVE_BOARD_HOT_SET_TEMP          	5008//2#制热回风设置温度
#define DRIVE_BOARD_HUMIDITY_SET_TEMP       5009//2#相对湿度设置
#define DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP  5010  //2#生活热水设置温度
#define DRIVE_BOARD_COOL_OUTWATER_SETTEMP   5024//1#制冷出水设置温度  
#define DRIVE_BOARD_COOL_BACKWATER_SETTEMP  5025//1#制冷回水设置温度
#define DRIVE_BOARD_HOT_OUTWATER_SETTEMP    5026//1#制热出水设置温度 
#define DRIVE_BOARD_HOT_BACKWATER_SETTEMP   5027//1#制热回水设置温度
#define DRIVE_BOARD_FAN_CONTROL_ENABLE		5040//室内风机控制使能
#define DRIVE_BOARD_FAN_SPEED        		5041//室内风机转速  
#define DRIVE_BOARD_TWO_WAY_VALUE_STATE		5069//室内电动二通阀状态
#define DRIVE_BOARD_INDOOR_MESSAGE		    5070//室内回风湿度值
#define DRIVE_BOARD_FAN_FEEDBACK_SPEED      5068//室内风机实际转速 
#define DRIVE_BOARD_BACKWIND_HUMIDITY       5070//室内回风湿度
#define DRIVE_BOARD_INWIND_HUMIDITY         5071//室内进风湿度
#define DRIVE_BOARD_INWIND_TEMP             5072//室内进风温度
#define DRIVE_BOARD_BACKWIND_TEMP           5073//室内回风温度
#define DRIVE_BOARD_WATER_MACHINE_POWER     5074//水机开关机

#define UPDATA_DELAY                        1000
//----------------------------------------------------------------------------
#define ARICOD_READ_ONLY_REG_NUM            84
#define ARICOD_READ_WRITE_REG_NUM           74
//-----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void app_master_comp_task(void);
bool APP_pull_aricod_message(uint16_t in_reg_add,uint16_t *out_reg_value);
bool APP_push_aricod_message(uint16_t in_reg_add,uint16_t in_reg_value);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif
