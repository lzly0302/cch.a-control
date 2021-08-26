#ifndef app_modbus_register_H
#define app_modbus_register_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//----------------------------------------------------------------------------
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MRegaddr_FactoryParameter                        0x1500   //恢复出厂设置,0x2591安全字
//-----------------------------------------------------------------------------
#define MRegaddr_SNWriteCtlHi                            0x1600   //控制字
#define MRegaddr_SNWriteCtlLo                            0x1601
#define MRegaddr_CiphersVerCtl                           0x1602   //密文版本控制   
#define MRegaddr_AllowWrSTxtD                            0x1603   //允许写入标志 0xFFFF允许写入
#define MRegaddr_STxtEncodeType                          0x1604   //编码类型
#define MRegaddr_STxtBytesLength                         0x1605   //标识字节长度
#define MRegaddr_STxtDetailsStart                        0x1606   //标识内容开始地址
#define STXTDETAILSREGAMOUNT                             64       //标识最大支持128byte
//-----------------------------------------------------------------------------URL
#define MRegaddr_URLBytesLength                          0x1700
#define MRegaddr_URLDetailsStart                         0x1701   //URL开始地址
#define URLDETAILSAOUNT                                  254
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define MRegaddr_StrUpdateWord                           0x1800
#define MRegaddr_UpdateVersion                           0x1801
#define MRegaddr_MessageTnumber                          0x1802
#define MRegaddr_CheckSumHI                              0x1805
#define MRegaddr_CheckSumLo                              0x1806                                    
#define MRegaddr_SlaveStatusW                            0x1810
#define MRegaddr_RequestNumber                           0x1811
#define MRegaddr_HardwareTypeHi                          0x1812
#define MRegaddr_HardwareTypeLo                          0x1813                                     
#define MRegaddr_MessageNumber                           0x187F  //129 register
#define MRegaddr_Message0                                0x1880
#define MRegaddr_Message63                               0x18BF
#define MRegaddr_STM32F103R8T6WRPRHi                     0x1900   //加密字
#define MRegaddr_STM32F103R8T6WRPRLo                     0x1901
#define MRegaddr_STM32F103R8T6OBRHi                      0x1902   //状态字
#define MRegaddr_STM32F103R8T6OBRLo                      0x1903
#define MRegaddr_EraseWRPR                               0x1904   //擦除加密字
//-----------------------------------------------------------------------------
#define MRegaddr_ProductType                             0x2000   //产品类型
#define MRegaddr_SoftVersion                             0x2001   //软件版本
#define MRegaddr_SecondAndWeek                           0x2002   //时钟 秒-星期
#define MRegaddr_HourAndMinute                           0x2003   //时钟 小时-分钟
#define MRegaddr_MonthAndDay                             0x2004   //时钟 月-天
#define MRegaddr_Year                                    0x2005   //时钟 年
#define MRegaddr_SalveAddr                               0x2006   //从机地址
#define MRegaddr_SalveBaudrate                           0x2007   //从机波特率 2400 4800 9600
#define MRegaddr_SalveParityBit                          0x2008   //从机奇偶校验位
#define MRegaddr_Restoragefac                            0x200F   //
#define MRegaddr_TEST_SYN_STATUS                         0x2010   //
//-----------------------------------------------------------------------------
#define REG_ADDR_MASTER_ERROR_WORD                       0X2C00   //主机故障字
#define REG_ADDR_AIRCOD_ENERGY_NEED                      0X2C01   //环控能需
#define REG_ADDR_SYSTEM_POWER                            0X2C02   //系统开关机
#define REG_ADDR_SYSTEM_RUN_MODE                         0X2C03   //系统运行模式
#define REG_ADDR_FAN_SET_HUM                             0X2C04   //通风制冷/除湿模式设定相对湿度
#define REG_ADDR_FAN_SET_SPEED                           0X2C05   //通风设定风速 
#define REG_ADDR_SET_COLD_TEMP                           0X2C06   //通风制冷设定温度
#define REG_ADDR_SET_HEAT_TEMP                           0X2C07   //通风制热设定温度
#define REG_ADDR_NEW_AIR_LOW_PWM                         0X2C08   //新风低风量PWM值
#define REG_ADDR_NEW_AIR_MID_PWM                         0X2C09   //新风中风量PWM值
#define REG_ADDR_NEW_AIR_HIGH_PWM                        0X2C0A   // 新风高风量PWM值
#define REG_ADDR_BACK_AIR_LOW_PWM                        0X2C0B  //回风低风量PWM值
#define REG_ADDR_BACK_AIR_MID_PWM                        0X2C0C   //回风中风量PWM值
#define REG_ADDR_BACK_AIR_HIGH_PWM                       0X2C0D  //回风高风量PWM值
#define REG_ADDR_MASTER_SET_COLD_WATER_TEMP              0X2C0E  //主机制冷模式设定水温
#define REG_ADDR_MASTER_SET_HEAT_WATER_TEMP              0X2C0F  //主机制热模式设定水温
#define REG_ADDR_MASTER_SET_LIVING_WATER_TEMP            0X2C10  //主机生活热水设定水温
#define REG_ADDR_MASTER_OUTDOOR_IN_FAN_TEMP              0X2C11//户外进风口温度T0R(进风温度)
#define REG_ADDR_MASTER_OUTDOOR_IN_FAN_HUM               0X2C12//
#define REG_ADDR_BEFORE_FU_TEMP                          0X2C13//
#define REG_ADDR_BEFORE_FU_HUM                           0X2C14//
#define REG_ADDR_AFTER_FU_TEMP                           0X2C15//
#define REG_ADDR_AFTER_FU_HUM                            0X2C16//
#define REG_ADDR_BACK_AIR_TEMP                           0X2C17//
#define REG_ADDR_BACK_AIR_HUM                            0X2C18//
#define REG_ADDR_EXHAST_AIR_TEMP                         0X2C19//
#define REG_ADDR_EXHAST_AIR_HUM                          0X2C1A//
#define REG_ADDR_BACK_AIR_CO2                            0X2C1B//
#define REG_ADDR_BACK_AIR_PM25                           0X2C1C//
#define REG_ADDR_DEADZONE_FAN_HUM                        0X2C1D//
#define REG_ADDR_DEADZONE_FAN_TEMP                       0X2C1E//
#define REG_ADDR_NEW_AIR_SPEED                           0X2C1F//
#define REG_ADDR_BACK_AIR_SPEED                          0X2C20//
#define REG_ADDR_WATER_MACHINE_FRE                       0X2C21//
#define REG_ADDR_FU_MACHINE_FRE                          0X2C22//
#define REG_ADDR_MASTER_SUPPLY_TEMP                      0X2C23//
#define REG_ADDR_MASTER_LIVING_TEMP                      0X2C24//
#define REG_ADDR_MASTER_OUTDOOR_TEMP                     0X2C25//
#define REG_ADDR_ADJUST_BACKAIR_HUM                      0X2C26//回风
#define REG_ADDR_ADJUST_BACKAIR_TEMP                     0X2C27
#define REG_ADDR_ADJUST_BACKAIR_CO2                      0X2C28
#define REG_ADDR_ADJUST_BACKAIR_PM25                     0X2C29
#define REG_ADDR_ADJUST_OUTDOORAIR_HUM                   0X2C2A//
#define REG_ADDR_ADJUST_OUTDOORAIR_TEMP                  0X2C2B//
#define REG_ADDR_ADJUST_OUTDOORAIR_CO2                   0X2C2C//
#define REG_ADDR_ADJUST_OUTDOORAIR_PM25                  0X2C2D//
#define REG_ADDR_ADJUST_BEFORFU_HUM                      0X2C2E//
#define REG_ADDR_ADJUST_BEFORFU_TEMP                     0X2C2F//
#define REG_ADDR_ADJUST_BEFORFU_CO2                      0X2C30//
#define REG_ADDR_ADJUST_BEFORFU_PM25                     0X2C31//
#define REG_ADDR_ADJUST_AFTERFU_HUM                      0X2C32//
#define REG_ADDR_ADJUST_AFTERFU_TEMP                     0X2C33//
#define REG_ADDR_ADJUST_AFTERFU_CO2                      0X2C34//
#define REG_ADDR_ADJUST_AFTERFU_PM25                     0X2C35//
#define REG_ADDR_SYSTEM_STATSU                           0X2C36//主机状态字
#define REG_ADDR_LEW_PROTECT_STATSU                      0X2C37//露点保护状态
#define REG_ADDR_PAD_OUTPUT_STATSU                       0X2C38//末端输出状态

#define REG_ADDR_ADJUST_EXHASTAIR_HUM                    0X2C3A//
#define REG_ADDR_ADJUST_EXHASTAIR_TEMP                   0X2C3B//
#define REG_ADDR_ADJUST_EXHASTAIR_CO2                    0X2C3C//输配一次侧供水温度
#define REG_ADDR_ADJUST_EXHASTAIR_PM25                   0X2C3D//输配一次侧回水温度
#define REG_ADDR_SET_MIXWATER_COLD_TEMP                  0X2C3E//
#define REG_ADDR_SET_MIXWATER_HEAT_TEMP                  0X2C3F//
#define REG_ADDR_MIXWATER_INWATER_TEMP                   0X2C40//预留
#define REG_ADDR_MIXWATER_BACKWATER_TEMP                 0X2C41//输配二次侧回水温度
#define REG_ADDR_MIXWATER_TEMP                           0X2C42//输配混水温度
#define REG_ADDR_OUTPUT_PUMP                             0X2C43//输配水泵状态
#define REG_ADDR_OUTPUT_THREE_VAVLE                      0X2C44//输配三通阀门输出状态
#define REG_ADDR_MIXWATER_AI_DEST_TEMP                   0X2C45//
#define REG_ADDR_MIXWATER_AI_ENABLE                      0X2C46//
#define REG_ADDR_MIXWATER_LOW_TEMP_PROTECT               0X2C47//输配防冻保护
#define REG_ADDR_COLD_NO_NEED_SET_TEMP_CONFIG            0X2C48//制冷无能需出水温度配置
#define REG_ADDR_COLD_FAN_NEED_SET_TEMP_CONFIG           0X2C49//制冷风盘能需出水温度配置
#define REG_ADDR_COLD_WARM_NEED_SET_TEMP_CONFIG          0X2C4a//制冷辐射能需出水温度配置
#define REG_ADDR_LEW_TEMP_COMPARE_CONFIG                 0X2C4b//制冷露点比较温度配置
#define REG_ADRESS_NEW_TREND_EFFCIENCY			         0x2c4c//新风效率newwind efficiency
#define REG_ADRESS_WIND_VALUE				             0x2c4d//风阀切换
#define REG_ADRESS_HOTWATER_ENABLE			             0x2c4e//热水使能开关
#define REG_ADRESS_COOL_BACKWATER_SETTEMP		         0x2c4f//制冷回水设置温度
#define REG_ADRESS_FILTER_TIME				             0x2c50//滤芯更换周期
#define REG_ADRESS_HOT_BACKWATER_SETTEMP		         0x2c51//制热回水设置温度
#define REG_ADRESS_FILTER_USERTIME						 0x2c52//滤芯使用时间
#define REG_ADRESS_HEAT_NO_NEED_SET_TEMP_CONFIG		     0x2c53//制热无能需出水温度配置
#define REG_ADRESS_HEAT_FAN_NEED_SET_TEMP_CONFIG	     0x2c54//制热风盘能需出水温度配置
#define REG_ADRESS_HEAT_WARM_NEED_SET_TEMP_CONFIG		 0x2c55//制热辐射能需出水温度配置
#define REG_ADRESS_HEAT_BACKWATER_COMPARE_CONFIG	     0x2c56//制热回风比较温度配置
#define REG_ADRESS_DEHUM_FIX_CONFIG					     0x2c57//除湿固定湿度配置
#define REG_ADRESS_COLD_WIND_MAX_COLD_SET				 0x2c58//制冷氟盘最大设定温度
#define REG_ADRESS_HEAT_WIND_MIN_COLD_SET				 0x2c59//制热氟盘最小设定温度
#define REG_ADRESS_HEAT_WIND_MAX_COLD_SET			     0x2c5a//制热氟盘最大设定温度
#define REG_ADRESS_MAIN_CONTROL_METHOD   			     0x2c5B//主控策略
#define REG_ADRESS_LEW_STATUS_OPEN_DIFF				     0x2c5C//露点状态上限(开启)
#define REG_ADRESS_LEW_STATUS_CLOSE_DIFF				 0x2c5D//露点状态下限(关闭)
#define REG_ADRESS_CC_RESET			                     0x2c5E//输配软件复位
#define REG_ADRESS_HC_RESET   			                 0x2c5F//环控软件复位
#define REG_ADRESS_DEBUG_ENABLE  						 0x2c60//调试使能
#define REG_ADRESS_WATER_MACHINE_CONTROL  			     0x2c61//水机控制

#define REG_ADRESS_REMOTE_CONTROL				 	     0x2D00//远程控制
#define REG_ADRESS_REMOTE_RELAY1				 	     0x2D01//远程继电器1
#define REG_ADRESS_REMOTE_RELAY2				 	     0x2D02//远程继电器2
#define REG_ADRESS_REMOTE_RELAY3				 	     0x2D03//远程继电器3
#define REG_ADRESS_REMOTE_RELAY4				 	     0x2D04//远程继电器4
#define REG_ADRESS_REMOTE_RELAY5				 	     0x2D05//远程继电器5
#define REG_ADRESS_REMOTE_RELAY6				 	     0x2D06//远程继电器6
#define REG_ADRESS_REMOTE_RELAY7				 	     0x2D07//远程继电器7
#define REG_ADRESS_REMOTE_RELAY8				 	     0x2D08//远程继电器8
#define REG_ADRESS_REMOTE_RELAY9				 	     0x2D09//远程继电器9
#define REG_ADRESS_REMOTE_RELAY10				 	     0x2D0A//远程继电器10
#define REG_ADRESS_REMOTE_RELAY11				 	     0x2D0B//远程继电器11
#define REG_ADRESS_REMOTE_PUMP				 	         0x2D0C//远程水泵
#define REG_ADRESS_REMOTE_THREEVAVLE				 	 0x2D0D//远程三通阀
#define REG_ADRESS_REMOTE_VAVLEDUTY				 	     0x2D0E//远程三通阀开度
#define REG_ADRESS_REMOTE_BY_PASS				 	     0x2D0F//远程旁通

#define REG_ADDR_PAD_START                               0X3000//
#define REG_ADDR_PAD1_ERROR_WORD                         0X3000//
#define REG_ADDR_PAD1_ONLINE_STATUS                      0X3001//
#define REG_ADDR_PAD1_DEVICE_TYPE                        0X3002//
#define REG_ADDR_PAD1_DEVICE_ID0                         0X3003//
#define REG_ADDR_PAD1_DEVICE_ID1                         0X3004//
#define REG_ADDR_PAD1_DEVICE_ID2                         0X3005//
#define REG_ADDR_PAD1_POWER                              0X3006//
#define REG_ADDR_PAD1_SET_COLD_TEMP                      0X3007//
#define REG_ADDR_PAD1_SET_HEAT_TEMP                      0X3008//
#define REG_ADDR_PAD1_LEW_DORP_TEMP                      0X3009//露点温度
#define REG_ADDR_PAD1_COLD_WARM_STATUS                   0X300A//冷热运行状态
#define REG_ADDR_PAD1_FREEZE_PROTECT                     0X300B//防冻保护
#define REG_ADDR_PAD1_FREEZE_TEMP                        0X300C//
#define REG_ADDR_PAD1_CHILD_LOCK                         0X300D//
#define REG_ADDR_PAD1_POWER_MEMORY                       0X300E//
#define REG_ADDR_PAD1_COMFORTABLE_COLD_TEMP              0X300F//
#define REG_ADDR_PAD1_COMFORTABLE_HEAT_TEMP              0X3010//
#define REG_ADDR_PAD1_SET_HIGH_TEMP                      0X3011//
#define REG_ADDR_PAD1_SET_LOW_TEMP                       0X3012//
#define REG_ADDR_PAD1_DEADZONE_TEMP                      0X3013//
#define REG_ADDR_PAD1_DEADZONE_LEW_TEMP                  0X3014//
#define REG_ADDR_PAD1_MEASURE_TEMP                       0X3015//
#define REG_ADDR_PAD1_MEASURE_HUM                        0X3016//
#define REG_ADDR_PAD1_WARM_NEED                          0X3017//
#define REG_ADDR_PAD1_SET_FANSPEED                       0X3018//设定风速 
#define REG_ADDR_PAD1_CONTROL_FAN                        0X3019//风机受控
#define REG_ADDR_PAD1_PWM_LOW_FAN                        0X301A//
#define REG_ADDR_PAD1_PWM_MID_FAN                        0X301B//
#define REG_ADDR_PAD1_PWM_HIGH_FAN                       0X301C//
#define REG_ADDR_PAD1_AI_COLD_COLLA_DEADZONE             0X301D//
#define REG_ADDR_PAD1_AI_HEAT_COLLA_DEADZONE             0X301E//
#define REG_ADDR_PAD1_AI_COLD_COLLA_ENABLE               0X301F//制冷协同使能
#define REG_ADDR_PAD1_AI_HEAT_COLLA_ENABLE               0X3020//制热协同使能
#define REG_ADDR_PAD1_FAN_VAVLE_NEED                     0X3021//风阀需求
#define REG_ADDR_PAD1_FAN_OUTPUT_LEVEL                   0X3022//风机输出状态
#define REG_ADDR_PAD1_FAN_SPEED                          0X3023//EC风机转速
#define REG_ADDR_PAD1_CONTROL_OUTPUT_NUM                 0X3024//末端数量
#define REG_ADDR_PAD1_TWO_CHOOSE_MODE                    0X3025//双末端模式选择
#define REG_ADDR_PAD1_BIND_FAN                           0X3026//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD1_BIND_WARM                          0X3027//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD1_WARM_TYPE                          0X3028//辐射类型
#define REG_ADDR_PAD1_ROOM_AREA                          0X3029//房间面积
#define REG_ADDR_PAD1_LEW_TEMP_STATUS                    0X302A//露点状态
#define REG_ADDR_PAD1_ADJUST_TEMP                        0X302B//校温
#define REG_ADDR_PAD1_ADJUST_HUM                         0X302C//校湿
#define REG_ADDR_PAD1_VERSION                            0X302D//版本号

#define REG_ADDR_PAD2_ERROR_WORD                         0X3100//
#define REG_ADDR_PAD2_ONLINE_STATUS                      0X3101//
#define REG_ADDR_PAD2_DEVICE_TYPE                        0X3102//
#define REG_ADDR_PAD2_DEVICE_ID0                         0X3103//
#define REG_ADDR_PAD2_DEVICE_ID1                         0X3104//
#define REG_ADDR_PAD2_DEVICE_ID2                         0X3105//
#define REG_ADDR_PAD2_POWER                              0X3106//
#define REG_ADDR_PAD2_SET_COLD_TEMP                      0X3107//
#define REG_ADDR_PAD2_SET_HEAT_TEMP                      0X3108//
#define REG_ADDR_PAD2_LEW_DORP_TEMP                      0X3109//露点温度
#define REG_ADDR_PAD2_COLD_WARM_STATUS                   0X310A//冷热运行状态
#define REG_ADDR_PAD2_FREEZE_PROTECT                     0X310B//防冻保护
#define REG_ADDR_PAD2_FREEZE_TEMP                        0X310C//
#define REG_ADDR_PAD2_CHILD_LOCK                         0X310D//
#define REG_ADDR_PAD2_POWER_MEMORY                       0X310E//
#define REG_ADDR_PAD2_COMFORTABLE_COLD_TEMP              0X310F//
#define REG_ADDR_PAD2_COMFORTABLE_HEAT_TEMP              0X3110//
#define REG_ADDR_PAD2_SET_HIGH_TEMP                      0X3111//
#define REG_ADDR_PAD2_SET_LOW_TEMP                       0X3112//
#define REG_ADDR_PAD2_DEADZONE_TEMP                      0X3113//
#define REG_ADDR_PAD2_DEADZONE_LEW_TEMP                  0X3114//
#define REG_ADDR_PAD2_MEASURE_TEMP                       0X3115//
#define REG_ADDR_PAD2_MEASURE_HUM                        0X3116//
#define REG_ADDR_PAD2_WARM_NEED                          0X3117//
#define REG_ADDR_PAD2_SET_FANSPEED                       0X3118//设定风速 
#define REG_ADDR_PAD2_CONTROL_FAN                        0X3119//风机受控
#define REG_ADDR_PAD2_PWM_LOW_FAN                        0X311A//
#define REG_ADDR_PAD2_PWM_MID_FAN                        0X311B//
#define REG_ADDR_PAD2_PWM_HIGH_FAN                       0X311C//
#define REG_ADDR_PAD2_AI_COLD_COLLA_DEADZONE             0X311D//
#define REG_ADDR_PAD2_AI_HEAT_COLLA_DEADZONE             0X311E//
#define REG_ADDR_PAD2_AI_COLD_COLLA_ENABLE               0X311F//制冷协同使能
#define REG_ADDR_PAD2_AI_HEAT_COLLA_ENABLE               0X3120//制热协同使能
#define REG_ADDR_PAD2_FAN_VAVLE_NEED                     0X3121//风阀需求
#define REG_ADDR_PAD2_FAN_OUTPUT_LEVEL                   0X3122//风机输出状态
#define REG_ADDR_PAD2_FAN_SPEED                          0X3123//EC风机转速
#define REG_ADDR_PAD2_CONTROL_OUTPUT_NUM                 0X3124//末端数量
#define REG_ADDR_PAD2_TWO_CHOOSE_MODE                    0X3125//双末端模式选择
#define REG_ADDR_PAD2_BIND_FAN                           0X3126//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD2_BIND_WARM                          0X3127//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD2_WARM_TYPE                          0X3128//辐射类型
#define REG_ADDR_PAD2_ROOM_AREA                          0X3129//房间面积
#define REG_ADDR_PAD2_LEW_TEMP_STATUS                    0X312A//露点状态
#define REG_ADDR_PAD2_ADJUST_TEMP                        0X312B//校温
#define REG_ADDR_PAD2_ADJUST_HUM                         0X312C//校湿
#define REG_ADDR_PAD2_VERSION                            0X312D//版本号


#define REG_ADDR_PAD3_ERROR_WORD                         0X3200//
#define REG_ADDR_PAD3_ONLINE_STATUS                      0X3201//
#define REG_ADDR_PAD3_DEVICE_TYPE                        0X3202//
#define REG_ADDR_PAD3_DEVICE_ID0                         0X3203//
#define REG_ADDR_PAD3_DEVICE_ID1                         0X3204//
#define REG_ADDR_PAD3_DEVICE_ID2                         0X3205//
#define REG_ADDR_PAD3_POWER                              0X3206//
#define REG_ADDR_PAD3_SET_COLD_TEMP                      0X3207//
#define REG_ADDR_PAD3_SET_HEAT_TEMP                      0X3208//
#define REG_ADDR_PAD3_LEW_DORP_TEMP                      0X3209//露点温度
#define REG_ADDR_PAD3_COLD_WARM_STATUS                   0X320A//冷热运行状态
#define REG_ADDR_PAD3_FREEZE_PROTECT                     0X320B//防冻保护
#define REG_ADDR_PAD3_FREEZE_TEMP                        0X320C//
#define REG_ADDR_PAD3_CHILD_LOCK                         0X320D//
#define REG_ADDR_PAD3_POWER_MEMORY                       0X320E//
#define REG_ADDR_PAD3_COMFORTABLE_COLD_TEMP              0X320F//
#define REG_ADDR_PAD3_COMFORTABLE_HEAT_TEMP              0X3210//
#define REG_ADDR_PAD3_SET_HIGH_TEMP                      0X3211//
#define REG_ADDR_PAD3_SET_LOW_TEMP                       0X3212//
#define REG_ADDR_PAD3_DEADZONE_TEMP                      0X3213//
#define REG_ADDR_PAD3_DEADZONE_LEW_TEMP                  0X3214//
#define REG_ADDR_PAD3_MEASURE_TEMP                       0X3215//
#define REG_ADDR_PAD3_MEASURE_HUM                        0X3216//
#define REG_ADDR_PAD3_WARM_NEED                          0X3217//
#define REG_ADDR_PAD3_SET_FANSPEED                       0X3218//设定风速 
#define REG_ADDR_PAD3_CONTROL_FAN                        0X3219//风机受控
#define REG_ADDR_PAD3_PWM_LOW_FAN                        0X321A//
#define REG_ADDR_PAD3_PWM_MID_FAN                        0X321B//
#define REG_ADDR_PAD3_PWM_HIGH_FAN                       0X321C//
#define REG_ADDR_PAD3_AI_COLD_COLLA_DEADZONE             0X321D//
#define REG_ADDR_PAD3_AI_HEAT_COLLA_DEADZONE             0X321E//
#define REG_ADDR_PAD3_AI_COLD_COLLA_ENABLE               0X321F//制冷协同使能
#define REG_ADDR_PAD3_AI_HEAT_COLLA_ENABLE               0X3220//制热协同使能
#define REG_ADDR_PAD3_FAN_VAVLE_NEED                     0X3221//风阀需求
#define REG_ADDR_PAD3_FAN_OUTPUT_LEVEL                   0X3222//风机输出状态
#define REG_ADDR_PAD3_FAN_SPEED                          0X3223//EC风机转速
#define REG_ADDR_PAD3_CONTROL_OUTPUT_NUM                 0X3224//末端数量
#define REG_ADDR_PAD3_TWO_CHOOSE_MODE                    0X3225//双末端模式选择
#define REG_ADDR_PAD3_BIND_FAN                           0X3226//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD3_BIND_WARM                          0X3227//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD3_WARM_TYPE                          0X3228//辐射类型
#define REG_ADDR_PAD3_ROOM_AREA                          0X3229//房间面积
#define REG_ADDR_PAD3_LEW_TEMP_STATUS                    0X322A//露点状态
#define REG_ADDR_PAD3_ADJUST_TEMP                        0X322B//校温
#define REG_ADDR_PAD3_ADJUST_HUM                         0X322C//校湿
#define REG_ADDR_PAD3_VERSION                            0X322D//版本号

#define REG_ADDR_PAD4_ERROR_WORD                         0X3300//
#define REG_ADDR_PAD4_ONLINE_STATUS                      0X3301//
#define REG_ADDR_PAD4_DEVICE_TYPE                        0X3302//
#define REG_ADDR_PAD4_DEVICE_ID0                         0X3303//
#define REG_ADDR_PAD4_DEVICE_ID1                         0X3304//
#define REG_ADDR_PAD4_DEVICE_ID2                         0X3305//
#define REG_ADDR_PAD4_POWER                              0X3306//
#define REG_ADDR_PAD4_SET_COLD_TEMP                      0X3307//
#define REG_ADDR_PAD4_SET_HEAT_TEMP                      0X3308//
#define REG_ADDR_PAD4_LEW_DORP_TEMP                      0X3309//露点温度
#define REG_ADDR_PAD4_COLD_WARM_STATUS                   0X330A//冷热运行状态
#define REG_ADDR_PAD4_FREEZE_PROTECT                     0X330B//防冻保护
#define REG_ADDR_PAD4_FREEZE_TEMP                        0X330C//
#define REG_ADDR_PAD4_CHILD_LOCK                         0X330D//
#define REG_ADDR_PAD4_POWER_MEMORY                       0X330E//
#define REG_ADDR_PAD4_COMFORTABLE_COLD_TEMP              0X330F//
#define REG_ADDR_PAD4_COMFORTABLE_HEAT_TEMP              0X3310//
#define REG_ADDR_PAD4_SET_HIGH_TEMP                      0X3311//
#define REG_ADDR_PAD4_SET_LOW_TEMP                       0X3312//
#define REG_ADDR_PAD4_DEADZONE_TEMP                      0X3313//
#define REG_ADDR_PAD4_DEADZONE_LEW_TEMP                  0X3314//
#define REG_ADDR_PAD4_MEASURE_TEMP                       0X3315//
#define REG_ADDR_PAD4_MEASURE_HUM                        0X3316//
#define REG_ADDR_PAD4_WARM_NEED                          0X3317//
#define REG_ADDR_PAD4_SET_FANSPEED                       0X3318//设定风速 
#define REG_ADDR_PAD4_CONTROL_FAN                        0X3319//风机受控
#define REG_ADDR_PAD4_PWM_LOW_FAN                        0X331A//
#define REG_ADDR_PAD4_PWM_MID_FAN                        0X331B//
#define REG_ADDR_PAD4_PWM_HIGH_FAN                       0X331C//
#define REG_ADDR_PAD4_AI_COLD_COLLA_DEADZONE             0X331D//
#define REG_ADDR_PAD4_AI_HEAT_COLLA_DEADZONE             0X331E//
#define REG_ADDR_PAD4_AI_COLD_COLLA_ENABLE               0X331F//制冷协同使能
#define REG_ADDR_PAD4_AI_HEAT_COLLA_ENABLE               0X3320//制热协同使能
#define REG_ADDR_PAD4_FAN_VAVLE_NEED                     0X3321//风阀需求
#define REG_ADDR_PAD4_FAN_OUTPUT_LEVEL                   0X3322//风机输出状态
#define REG_ADDR_PAD4_FAN_SPEED                          0X3323//EC风机转速
#define REG_ADDR_PAD4_CONTROL_OUTPUT_NUM                 0X3324//末端数量
#define REG_ADDR_PAD4_TWO_CHOOSE_MODE                    0X3325//双末端模式选择
#define REG_ADDR_PAD4_BIND_FAN                           0X3326//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD4_BIND_WARM                          0X3327//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD4_WARM_TYPE                          0X3328//辐射类型
#define REG_ADDR_PAD4_ROOM_AREA                          0X3329//房间面积
#define REG_ADDR_PAD4_LEW_TEMP_STATUS                    0X332A//露点状态
#define REG_ADDR_PAD4_ADJUST_TEMP                        0X332B//校温
#define REG_ADDR_PAD4_ADJUST_HUM                         0X332C//校湿
#define REG_ADDR_PAD4_VERSION                            0X332D//版本号

#define REG_ADDR_PAD5_ERROR_WORD                         0X3400//
#define REG_ADDR_PAD5_ONLINE_STATUS                      0X3401//
#define REG_ADDR_PAD5_DEVICE_TYPE                        0X3402//
#define REG_ADDR_PAD5_DEVICE_ID0                         0X3403//
#define REG_ADDR_PAD5_DEVICE_ID1                         0X3404//
#define REG_ADDR_PAD5_DEVICE_ID2                         0X3405//
#define REG_ADDR_PAD5_POWER                              0X3406//
#define REG_ADDR_PAD5_SET_COLD_TEMP                      0X3407//
#define REG_ADDR_PAD5_SET_HEAT_TEMP                      0X3408//
#define REG_ADDR_PAD5_LEW_DORP_TEMP                      0X3409//露点温度
#define REG_ADDR_PAD5_COLD_WARM_STATUS                   0X340A//冷热运行状态
#define REG_ADDR_PAD5_FREEZE_PROTECT                     0X340B//防冻保护
#define REG_ADDR_PAD5_FREEZE_TEMP                        0X340C//
#define REG_ADDR_PAD5_CHILD_LOCK                         0X340D//
#define REG_ADDR_PAD5_POWER_MEMORY                       0X340E//
#define REG_ADDR_PAD5_COMFORTABLE_COLD_TEMP              0X340F//
#define REG_ADDR_PAD5_COMFORTABLE_HEAT_TEMP              0X3410//
#define REG_ADDR_PAD5_SET_HIGH_TEMP                      0X3411//
#define REG_ADDR_PAD5_SET_LOW_TEMP                       0X3412//
#define REG_ADDR_PAD5_DEADZONE_TEMP                      0X3413//
#define REG_ADDR_PAD5_DEADZONE_LEW_TEMP                  0X3414//
#define REG_ADDR_PAD5_MEASURE_TEMP                       0X3415//
#define REG_ADDR_PAD5_MEASURE_HUM                        0X3416//
#define REG_ADDR_PAD5_WARM_NEED                          0X3417//
#define REG_ADDR_PAD5_SET_FANSPEED                       0X3418//设定风速 
#define REG_ADDR_PAD5_CONTROL_FAN                        0X3419//风机受控
#define REG_ADDR_PAD5_PWM_LOW_FAN                        0X341A//
#define REG_ADDR_PAD5_PWM_MID_FAN                        0X341B//
#define REG_ADDR_PAD5_PWM_HIGH_FAN                       0X341C//
#define REG_ADDR_PAD5_AI_COLD_COLLA_DEADZONE             0X341D//
#define REG_ADDR_PAD5_AI_HEAT_COLLA_DEADZONE             0X341E//
#define REG_ADDR_PAD5_AI_COLD_COLLA_ENABLE               0X341F//制冷协同使能
#define REG_ADDR_PAD5_AI_HEAT_COLLA_ENABLE               0X3420//制热协同使能
#define REG_ADDR_PAD5_FAN_VAVLE_NEED                     0X3421//风阀需求
#define REG_ADDR_PAD5_FAN_OUTPUT_LEVEL                   0X3422//风机输出状态
#define REG_ADDR_PAD5_FAN_SPEED                          0X3423//EC风机转速
#define REG_ADDR_PAD5_CONTROL_OUTPUT_NUM                 0X3424//末端数量
#define REG_ADDR_PAD5_TWO_CHOOSE_MODE                    0X3425//双末端模式选择
#define REG_ADDR_PAD5_BIND_FAN                           0X3426//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD5_BIND_WARM                          0X3427//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD5_WARM_TYPE                          0X3428//辐射类型
#define REG_ADDR_PAD5_ROOM_AREA                          0X3429//房间面积
#define REG_ADDR_PAD5_LEW_TEMP_STATUS                    0X342A//露点状态
#define REG_ADDR_PAD5_ADJUST_TEMP                        0X342B//校温
#define REG_ADDR_PAD5_ADJUST_HUM                         0X342C//校湿
#define REG_ADDR_PAD5_VERSION                            0X342D//版本号

#define REG_ADDR_PAD6_ERROR_WORD                         0X3500//
#define REG_ADDR_PAD6_ONLINE_STATUS                      0X3501//
#define REG_ADDR_PAD6_DEVICE_TYPE                        0X3502//
#define REG_ADDR_PAD6_DEVICE_ID0                         0X3503//
#define REG_ADDR_PAD6_DEVICE_ID1                         0X3504//
#define REG_ADDR_PAD6_DEVICE_ID2                         0X3505//
#define REG_ADDR_PAD6_POWER                              0X3506//
#define REG_ADDR_PAD6_SET_COLD_TEMP                      0X3507//
#define REG_ADDR_PAD6_SET_HEAT_TEMP                      0X3508//
#define REG_ADDR_PAD6_LEW_DORP_TEMP                      0X3509//露点温度
#define REG_ADDR_PAD6_COLD_WARM_STATUS                   0X350A//冷热运行状态
#define REG_ADDR_PAD6_FREEZE_PROTECT                     0X350B//防冻保护
#define REG_ADDR_PAD6_FREEZE_TEMP                        0X350C//
#define REG_ADDR_PAD6_CHILD_LOCK                         0X350D//
#define REG_ADDR_PAD6_POWER_MEMORY                       0X350E//
#define REG_ADDR_PAD6_COMFORTABLE_COLD_TEMP              0X350F//
#define REG_ADDR_PAD6_COMFORTABLE_HEAT_TEMP              0X3510//
#define REG_ADDR_PAD6_SET_HIGH_TEMP                      0X3511//
#define REG_ADDR_PAD6_SET_LOW_TEMP                       0X3512//
#define REG_ADDR_PAD6_DEADZONE_TEMP                      0X3513//
#define REG_ADDR_PAD6_DEADZONE_LEW_TEMP                  0X3514//
#define REG_ADDR_PAD6_MEASURE_TEMP                       0X3515//
#define REG_ADDR_PAD6_MEASURE_HUM                        0X3516//
#define REG_ADDR_PAD6_WARM_NEED                          0X3517//
#define REG_ADDR_PAD6_SET_FANSPEED                       0X3518//设定风速 
#define REG_ADDR_PAD6_CONTROL_FAN                        0X3519//风机受控
#define REG_ADDR_PAD6_PWM_LOW_FAN                        0X351A//
#define REG_ADDR_PAD6_PWM_MID_FAN                        0X351B//
#define REG_ADDR_PAD6_PWM_HIGH_FAN                       0X351C//
#define REG_ADDR_PAD6_AI_COLD_COLLA_DEADZONE             0X351D//
#define REG_ADDR_PAD6_AI_HEAT_COLLA_DEADZONE             0X351E//
#define REG_ADDR_PAD6_AI_COLD_COLLA_ENABLE               0X351F//制冷协同使能
#define REG_ADDR_PAD6_AI_HEAT_COLLA_ENABLE               0X3520//制热协同使能
#define REG_ADDR_PAD6_FAN_VAVLE_NEED                     0X3521//风阀需求
#define REG_ADDR_PAD6_FAN_OUTPUT_LEVEL                   0X3522//风机输出状态
#define REG_ADDR_PAD6_FAN_SPEED                          0X3523//EC风机转速
#define REG_ADDR_PAD6_CONTROL_OUTPUT_NUM                 0X3524//末端数量
#define REG_ADDR_PAD6_TWO_CHOOSE_MODE                    0X3525//双末端模式选择
#define REG_ADDR_PAD6_BIND_FAN                           0X3526//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD6_BIND_WARM                          0X3527//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD6_WARM_TYPE                          0X3528//辐射类型
#define REG_ADDR_PAD6_ROOM_AREA                          0X3529//房间面积
#define REG_ADDR_PAD6_LEW_TEMP_STATUS                    0X352A//露点状态
#define REG_ADDR_PAD6_ADJUST_TEMP                        0X352B//校温
#define REG_ADDR_PAD6_ADJUST_HUM                         0X352C//校湿
#define REG_ADDR_PAD6_VERSION                            0X352D//版本号

#define REG_ADDR_PAD7_ERROR_WORD                         0X3600//
#define REG_ADDR_PAD7_ONLINE_STATUS                      0X3601//
#define REG_ADDR_PAD7_DEVICE_TYPE                        0X3602//
#define REG_ADDR_PAD7_DEVICE_ID0                         0X3603//
#define REG_ADDR_PAD7_DEVICE_ID1                         0X3604//
#define REG_ADDR_PAD7_DEVICE_ID2                         0X3605//
#define REG_ADDR_PAD7_POWER                              0X3606//
#define REG_ADDR_PAD7_SET_COLD_TEMP                      0X3607//
#define REG_ADDR_PAD7_SET_HEAT_TEMP                      0X3608//
#define REG_ADDR_PAD7_LEW_DORP_TEMP                      0X3609//露点温度
#define REG_ADDR_PAD7_COLD_WARM_STATUS                   0X360A//冷热运行状态
#define REG_ADDR_PAD7_FREEZE_PROTECT                     0X360B//防冻保护
#define REG_ADDR_PAD7_FREEZE_TEMP                        0X360C//
#define REG_ADDR_PAD7_CHILD_LOCK                         0X360D//
#define REG_ADDR_PAD7_POWER_MEMORY                       0X360E//
#define REG_ADDR_PAD7_COMFORTABLE_COLD_TEMP              0X360F//
#define REG_ADDR_PAD7_COMFORTABLE_HEAT_TEMP              0X3610//
#define REG_ADDR_PAD7_SET_HIGH_TEMP                      0X3611//
#define REG_ADDR_PAD7_SET_LOW_TEMP                       0X3612//
#define REG_ADDR_PAD7_DEADZONE_TEMP                      0X3613//
#define REG_ADDR_PAD7_DEADZONE_LEW_TEMP                  0X3614//
#define REG_ADDR_PAD7_MEASURE_TEMP                       0X3615//
#define REG_ADDR_PAD7_MEASURE_HUM                        0X3616//
#define REG_ADDR_PAD7_WARM_NEED                          0X3617//
#define REG_ADDR_PAD7_SET_FANSPEED                       0X3618//设定风速 
#define REG_ADDR_PAD7_CONTROL_FAN                        0X3619//风机受控
#define REG_ADDR_PAD7_PWM_LOW_FAN                        0X361A//
#define REG_ADDR_PAD7_PWM_MID_FAN                        0X361B//
#define REG_ADDR_PAD7_PWM_HIGH_FAN                       0X361C//
#define REG_ADDR_PAD7_AI_COLD_COLLA_DEADZONE             0X361D//
#define REG_ADDR_PAD7_AI_HEAT_COLLA_DEADZONE             0X361E//
#define REG_ADDR_PAD7_AI_COLD_COLLA_ENABLE               0X361F//制冷协同使能
#define REG_ADDR_PAD7_AI_HEAT_COLLA_ENABLE               0X3620//制热协同使能
#define REG_ADDR_PAD7_FAN_VAVLE_NEED                     0X3621//风阀需求
#define REG_ADDR_PAD7_FAN_OUTPUT_LEVEL                   0X3622//风机输出状态
#define REG_ADDR_PAD7_FAN_SPEED                          0X3623//EC风机转速
#define REG_ADDR_PAD7_CONTROL_OUTPUT_NUM                 0X3624//末端数量
#define REG_ADDR_PAD7_TWO_CHOOSE_MODE                    0X3625//双末端模式选择
#define REG_ADDR_PAD7_BIND_FAN                           0X3626//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD7_BIND_WARM                          0X3627//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD7_WARM_TYPE                          0X3628//辐射类型
#define REG_ADDR_PAD7_ROOM_AREA                          0X3629//房间面积
#define REG_ADDR_PAD7_LEW_TEMP_STATUS                    0X362A//露点状态
#define REG_ADDR_PAD7_ADJUST_TEMP                        0X362B//校温
#define REG_ADDR_PAD7_ADJUST_HUM                         0X362C//校湿
#define REG_ADDR_PAD7_VERSION                            0X362D//版本号

#define REG_ADDR_PAD8_ERROR_WORD                         0X3700//
#define REG_ADDR_PAD8_ONLINE_STATUS                      0X3701//
#define REG_ADDR_PAD8_DEVICE_TYPE                        0X3702//
#define REG_ADDR_PAD8_DEVICE_ID0                         0X3703//
#define REG_ADDR_PAD8_DEVICE_ID1                         0X3704//
#define REG_ADDR_PAD8_DEVICE_ID2                         0X3705//
#define REG_ADDR_PAD8_POWER                              0X3706//
#define REG_ADDR_PAD8_SET_COLD_TEMP                      0X3707//
#define REG_ADDR_PAD8_SET_HEAT_TEMP                      0X3708//
#define REG_ADDR_PAD8_LEW_DORP_TEMP                      0X3709//露点温度
#define REG_ADDR_PAD8_COLD_WARM_STATUS                   0X370A//冷热运行状态
#define REG_ADDR_PAD8_FREEZE_PROTECT                     0X370B//防冻保护
#define REG_ADDR_PAD8_FREEZE_TEMP                        0X370C//
#define REG_ADDR_PAD8_CHILD_LOCK                         0X370D//
#define REG_ADDR_PAD8_POWER_MEMORY                       0X370E//
#define REG_ADDR_PAD8_COMFORTABLE_COLD_TEMP              0X370F//
#define REG_ADDR_PAD8_COMFORTABLE_HEAT_TEMP              0X3710//
#define REG_ADDR_PAD8_SET_HIGH_TEMP                      0X3711//
#define REG_ADDR_PAD8_SET_LOW_TEMP                       0X3712//
#define REG_ADDR_PAD8_DEADZONE_TEMP                      0X3713//
#define REG_ADDR_PAD8_DEADZONE_LEW_TEMP                  0X3714//
#define REG_ADDR_PAD8_MEASURE_TEMP                       0X3715//
#define REG_ADDR_PAD8_MEASURE_HUM                        0X3716//
#define REG_ADDR_PAD8_WARM_NEED                          0X3717//
#define REG_ADDR_PAD8_SET_FANSPEED                       0X3718//设定风速 
#define REG_ADDR_PAD8_CONTROL_FAN                        0X3719//风机受控
#define REG_ADDR_PAD8_PWM_LOW_FAN                        0X371A//
#define REG_ADDR_PAD8_PWM_MID_FAN                        0X371B//
#define REG_ADDR_PAD8_PWM_HIGH_FAN                       0X371C//
#define REG_ADDR_PAD8_AI_COLD_COLLA_DEADZONE             0X371D//
#define REG_ADDR_PAD8_AI_HEAT_COLLA_DEADZONE             0X371E//
#define REG_ADDR_PAD8_AI_COLD_COLLA_ENABLE               0X371F//制冷协同使能
#define REG_ADDR_PAD8_AI_HEAT_COLLA_ENABLE               0X3720//制热协同使能
#define REG_ADDR_PAD8_FAN_VAVLE_NEED                     0X3721//风阀需求
#define REG_ADDR_PAD8_FAN_OUTPUT_LEVEL                   0X3722//风机输出状态
#define REG_ADDR_PAD8_FAN_SPEED                          0X3723//EC风机转速
#define REG_ADDR_PAD8_CONTROL_OUTPUT_NUM                 0X3724//末端数量
#define REG_ADDR_PAD8_TWO_CHOOSE_MODE                    0X3725//双末端模式选择
#define REG_ADDR_PAD8_BIND_FAN                           0X3726//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD8_BIND_WARM                          0X3727//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD8_WARM_TYPE                          0X3728//辐射类型
#define REG_ADDR_PAD8_ROOM_AREA                          0X3729//房间面积
#define REG_ADDR_PAD8_LEW_TEMP_STATUS                    0X372A//露点状态
#define REG_ADDR_PAD8_ADJUST_TEMP                        0X372B//校温
#define REG_ADDR_PAD8_ADJUST_HUM                         0X372C//校湿
#define REG_ADDR_PAD8_VERSION                            0X372D//版本号

#define REG_ADDR_PAD9_ERROR_WORD                         0X3800//
#define REG_ADDR_PAD9_ONLINE_STATUS                      0X3801//
#define REG_ADDR_PAD9_DEVICE_TYPE                        0X3802//
#define REG_ADDR_PAD9_DEVICE_ID0                         0X3803//
#define REG_ADDR_PAD9_DEVICE_ID1                         0X3804//
#define REG_ADDR_PAD9_DEVICE_ID2                         0X3805//
#define REG_ADDR_PAD9_POWER                              0X3806//
#define REG_ADDR_PAD9_SET_COLD_TEMP                      0X3807//
#define REG_ADDR_PAD9_SET_HEAT_TEMP                      0X3808//
#define REG_ADDR_PAD9_LEW_DORP_TEMP                      0X3809//露点温度
#define REG_ADDR_PAD9_COLD_WARM_STATUS                   0X380A//冷热运行状态
#define REG_ADDR_PAD9_FREEZE_PROTECT                     0X380B//防冻保护
#define REG_ADDR_PAD9_FREEZE_TEMP                        0X380C//
#define REG_ADDR_PAD9_CHILD_LOCK                         0X380D//
#define REG_ADDR_PAD9_POWER_MEMORY                       0X380E//
#define REG_ADDR_PAD9_COMFORTABLE_COLD_TEMP              0X380F//
#define REG_ADDR_PAD9_COMFORTABLE_HEAT_TEMP              0X3810//
#define REG_ADDR_PAD9_SET_HIGH_TEMP                      0X3811//
#define REG_ADDR_PAD9_SET_LOW_TEMP                       0X3812//
#define REG_ADDR_PAD9_DEADZONE_TEMP                      0X3813//
#define REG_ADDR_PAD9_DEADZONE_LEW_TEMP                  0X3814//
#define REG_ADDR_PAD9_MEASURE_TEMP                       0X3815//
#define REG_ADDR_PAD9_MEASURE_HUM                        0X3816//
#define REG_ADDR_PAD9_WARM_NEED                          0X3817//
#define REG_ADDR_PAD9_SET_FANSPEED                       0X3818//设定风速 
#define REG_ADDR_PAD9_CONTROL_FAN                        0X3819//风机受控
#define REG_ADDR_PAD9_PWM_LOW_FAN                        0X381A//
#define REG_ADDR_PAD9_PWM_MID_FAN                        0X381B//
#define REG_ADDR_PAD9_PWM_HIGH_FAN                       0X381C//
#define REG_ADDR_PAD9_AI_COLD_COLLA_DEADZONE             0X381D//
#define REG_ADDR_PAD9_AI_HEAT_COLLA_DEADZONE             0X381E//
#define REG_ADDR_PAD9_AI_COLD_COLLA_ENABLE               0X381F//制冷协同使能
#define REG_ADDR_PAD9_AI_HEAT_COLLA_ENABLE               0X3820//制热协同使能
#define REG_ADDR_PAD9_FAN_VAVLE_NEED                     0X3821//风阀需求
#define REG_ADDR_PAD9_FAN_OUTPUT_LEVEL                   0X3822//风机输出状态
#define REG_ADDR_PAD9_FAN_SPEED                          0X3823//EC风机转速
#define REG_ADDR_PAD9_CONTROL_OUTPUT_NUM                 0X3824//末端数量
#define REG_ADDR_PAD9_TWO_CHOOSE_MODE                    0X3825//双末端模式选择
#define REG_ADDR_PAD9_BIND_FAN                           0X3826//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD9_BIND_WARM                          0X3827//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD9_WARM_TYPE                          0X3828//辐射类型
#define REG_ADDR_PAD9_ROOM_AREA                          0X3829//房间面积
#define REG_ADDR_PAD9_LEW_TEMP_STATUS                    0X382A//露点状态
#define REG_ADDR_PAD9_ADJUST_TEMP                        0X382B//校温
#define REG_ADDR_PAD9_ADJUST_HUM                         0X382C//校湿
#define REG_ADDR_PAD9_VERSION                            0X382D//版本号

#define REG_ADDR_PAD10_ERROR_WORD                         0X3900//
#define REG_ADDR_PAD10_ONLINE_STATUS                      0X3901//
#define REG_ADDR_PAD10_DEVICE_TYPE                        0X3902//
#define REG_ADDR_PAD10_DEVICE_ID0                         0X3903//
#define REG_ADDR_PAD10_DEVICE_ID1                         0X3904//
#define REG_ADDR_PAD10_DEVICE_ID2                         0X3905//
#define REG_ADDR_PAD10_POWER                              0X3906//
#define REG_ADDR_PAD10_SET_COLD_TEMP                      0X3907//
#define REG_ADDR_PAD10_SET_HEAT_TEMP                      0X3908//
#define REG_ADDR_PAD10_LEW_DORP_TEMP                      0X3909//露点温度
#define REG_ADDR_PAD10_COLD_WARM_STATUS                   0X390A//冷热运行状态
#define REG_ADDR_PAD10_FREEZE_PROTECT                     0X390B//防冻保护
#define REG_ADDR_PAD10_FREEZE_TEMP                        0X390C//
#define REG_ADDR_PAD10_CHILD_LOCK                         0X390D//
#define REG_ADDR_PAD10_POWER_MEMORY                       0X390E//
#define REG_ADDR_PAD10_COMFORTABLE_COLD_TEMP              0X390F//
#define REG_ADDR_PAD10_COMFORTABLE_HEAT_TEMP              0X3910//
#define REG_ADDR_PAD10_SET_HIGH_TEMP                      0X3911//
#define REG_ADDR_PAD10_SET_LOW_TEMP                       0X3912//
#define REG_ADDR_PAD10_DEADZONE_TEMP                      0X3913//
#define REG_ADDR_PAD10_DEADZONE_LEW_TEMP                  0X3914//
#define REG_ADDR_PAD10_MEASURE_TEMP                       0X3915//
#define REG_ADDR_PAD10_MEASURE_HUM                        0X3916//
#define REG_ADDR_PAD10_WARM_NEED                          0X3917//
#define REG_ADDR_PAD10_SET_FANSPEED                       0X3918//设定风速 
#define REG_ADDR_PAD10_CONTROL_FAN                        0X3919//风机受控
#define REG_ADDR_PAD10_PWM_LOW_FAN                        0X391A//
#define REG_ADDR_PAD10_PWM_MID_FAN                        0X391B//
#define REG_ADDR_PAD10_PWM_HIGH_FAN                       0X391C//
#define REG_ADDR_PAD10_AI_COLD_COLLA_DEADZONE             0X391D//
#define REG_ADDR_PAD10_AI_HEAT_COLLA_DEADZONE             0X391E//
#define REG_ADDR_PAD10_AI_COLD_COLLA_ENABLE               0X391F//制冷协同使能
#define REG_ADDR_PAD10_AI_HEAT_COLLA_ENABLE               0X3920//制热协同使能
#define REG_ADDR_PAD10_FAN_VAVLE_NEED                     0X3921//风阀需求
#define REG_ADDR_PAD10_FAN_OUTPUT_LEVEL                   0X3922//风机输出状态
#define REG_ADDR_PAD10_FAN_SPEED                          0X3923//EC风机转速
#define REG_ADDR_PAD10_CONTROL_OUTPUT_NUM                 0X3924//末端数量
#define REG_ADDR_PAD10_TWO_CHOOSE_MODE                    0X3925//双末端模式选择
#define REG_ADDR_PAD10_BIND_FAN                           0X3926//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD10_BIND_WARM                          0X3927//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD10_WARM_TYPE                          0X3928//辐射类型
#define REG_ADDR_PAD10_ROOM_AREA                          0X3929//房间面积
#define REG_ADDR_PAD10_LEW_TEMP_STATUS                    0X392A//露点状态
#define REG_ADDR_PAD10_ADJUST_TEMP                        0X392B//校温
#define REG_ADDR_PAD10_ADJUST_HUM                         0X392C//校湿
#define REG_ADDR_PAD10_VERSION                            0X392D//版本号

#define REG_ADDR_PAD11_ERROR_WORD                         0X3A00//
#define REG_ADDR_PAD11_ONLINE_STATUS                      0X3A01//
#define REG_ADDR_PAD11_DEVICE_TYPE                        0X3A02//
#define REG_ADDR_PAD11_DEVICE_ID0                         0X3A03//
#define REG_ADDR_PAD11_DEVICE_ID1                         0X3A04//
#define REG_ADDR_PAD11_DEVICE_ID2                         0X3A05//
#define REG_ADDR_PAD11_POWER                              0X3A06//
#define REG_ADDR_PAD11_SET_COLD_TEMP                      0X3A07//
#define REG_ADDR_PAD11_SET_HEAT_TEMP                      0X3A08//
#define REG_ADDR_PAD11_LEW_DORP_TEMP                      0X3A09//露点温度
#define REG_ADDR_PAD11_COLD_WARM_STATUS                   0X3A0A//冷热运行状态
#define REG_ADDR_PAD11_FREEZE_PROTECT                     0X3A0B//防冻保护
#define REG_ADDR_PAD11_FREEZE_TEMP                        0X3A0C//
#define REG_ADDR_PAD11_CHILD_LOCK                         0X3A0D//
#define REG_ADDR_PAD11_POWER_MEMORY                       0X3A0E//
#define REG_ADDR_PAD11_COMFORTABLE_COLD_TEMP              0X3A0F//
#define REG_ADDR_PAD11_COMFORTABLE_HEAT_TEMP              0X3A10//
#define REG_ADDR_PAD11_SET_HIGH_TEMP                      0X3A11//
#define REG_ADDR_PAD11_SET_LOW_TEMP                       0X3A12//
#define REG_ADDR_PAD11_DEADZONE_TEMP                      0X3A13//
#define REG_ADDR_PAD11_DEADZONE_LEW_TEMP                  0X3A14//
#define REG_ADDR_PAD11_MEASURE_TEMP                       0X3A15//
#define REG_ADDR_PAD11_MEASURE_HUM                        0X3A16//
#define REG_ADDR_PAD11_WARM_NEED                          0X3A17//
#define REG_ADDR_PAD11_SET_FANSPEED                       0X3A18//设定风速 
#define REG_ADDR_PAD11_CONTROL_FAN                        0X3A19//风机受控
#define REG_ADDR_PAD11_PWM_LOW_FAN                        0X3A1A//
#define REG_ADDR_PAD11_PWM_MID_FAN                        0X3A1B//
#define REG_ADDR_PAD11_PWM_HIGH_FAN                       0X3A1C//
#define REG_ADDR_PAD11_AI_COLD_COLLA_DEADZONE             0X3A1D//
#define REG_ADDR_PAD11_AI_HEAT_COLLA_DEADZONE             0X3A1E//
#define REG_ADDR_PAD11_AI_COLD_COLLA_ENABLE               0X3A1F//制冷协同使能
#define REG_ADDR_PAD11_AI_HEAT_COLLA_ENABLE               0X3A20//制热协同使能
#define REG_ADDR_PAD11_FAN_VAVLE_NEED                     0X3A21//风阀需求
#define REG_ADDR_PAD11_FAN_OUTPUT_LEVEL                   0X3A22//风机输出状态
#define REG_ADDR_PAD11_FAN_SPEED                          0X3A23//EC风机转速
#define REG_ADDR_PAD11_CONTROL_OUTPUT_NUM                 0X3A24//末端数量
#define REG_ADDR_PAD11_TWO_CHOOSE_MODE                    0X3A25//双末端模式选择
#define REG_ADDR_PAD11_BIND_FAN                           0X3A26//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD11_BIND_WARM                          0X3A27//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD11_WARM_TYPE                          0X3A28//辐射类型
#define REG_ADDR_PAD11_ROOM_AREA                          0X3A29//房间面积
#define REG_ADDR_PAD11_LEW_TEMP_STATUS                    0X3A2A//露点状态
#define REG_ADDR_PAD11_ADJUST_TEMP                        0X3A2B//校温
#define REG_ADDR_PAD11_ADJUST_HUM                         0X3A2C//校湿
#define REG_ADDR_PAD11_VERSION                            0X3A2D//版本号

#define REG_ADDR_PAD12_ERROR_WORD                         0X3B00//
#define REG_ADDR_PAD12_ONLINE_STATUS                      0X3B01//
#define REG_ADDR_PAD12_DEVICE_TYPE                        0X3B02//
#define REG_ADDR_PAD12_DEVICE_ID0                         0X3B03//
#define REG_ADDR_PAD12_DEVICE_ID1                         0X3B04//
#define REG_ADDR_PAD12_DEVICE_ID2                         0X3B05//
#define REG_ADDR_PAD12_POWER                              0X3B06//
#define REG_ADDR_PAD12_SET_COLD_TEMP                      0X3B07//
#define REG_ADDR_PAD12_SET_HEAT_TEMP                      0X3B08//
#define REG_ADDR_PAD12_LEW_DORP_TEMP                      0X3B09//露点温度
#define REG_ADDR_PAD12_COLD_WARM_STATUS                   0X3B0A//冷热运行状态
#define REG_ADDR_PAD12_FREEZE_PROTECT                     0X3B0B//防冻保护
#define REG_ADDR_PAD12_FREEZE_TEMP                        0X3B0C//
#define REG_ADDR_PAD12_CHILD_LOCK                         0X3B0D//
#define REG_ADDR_PAD12_POWER_MEMORY                       0X3B0E//
#define REG_ADDR_PAD12_COMFORTABLE_COLD_TEMP              0X3B0F//
#define REG_ADDR_PAD12_COMFORTABLE_HEAT_TEMP              0X3B10//
#define REG_ADDR_PAD12_SET_HIGH_TEMP                      0X3B11//
#define REG_ADDR_PAD12_SET_LOW_TEMP                       0X3B12//
#define REG_ADDR_PAD12_DEADZONE_TEMP                      0X3B13//
#define REG_ADDR_PAD12_DEADZONE_LEW_TEMP                  0X3B14//
#define REG_ADDR_PAD12_MEASURE_TEMP                       0X3B15//
#define REG_ADDR_PAD12_MEASURE_HUM                        0X3B16//
#define REG_ADDR_PAD12_WARM_NEED                          0X3B17//
#define REG_ADDR_PAD12_SET_FANSPEED                       0X3B18//设定风速 
#define REG_ADDR_PAD12_CONTROL_FAN                        0X3B19//风机受控
#define REG_ADDR_PAD12_PWM_LOW_FAN                        0X3B1A//
#define REG_ADDR_PAD12_PWM_MID_FAN                        0X3B1B//
#define REG_ADDR_PAD12_PWM_HIGH_FAN                       0X3B1C//
#define REG_ADDR_PAD12_AI_COLD_COLLA_DEADZONE             0X3B1D//
#define REG_ADDR_PAD12_AI_HEAT_COLLA_DEADZONE             0X3B1E//
#define REG_ADDR_PAD12_AI_COLD_COLLA_ENABLE               0X3B1F//制冷协同使能
#define REG_ADDR_PAD12_AI_HEAT_COLLA_ENABLE               0X3B20//制热协同使能
#define REG_ADDR_PAD12_FAN_VAVLE_NEED                     0X3B21//风阀需求
#define REG_ADDR_PAD12_FAN_OUTPUT_LEVEL                   0X3B22//风机输出状态
#define REG_ADDR_PAD12_FAN_SPEED                          0X3B23//EC风机转速
#define REG_ADDR_PAD12_CONTROL_OUTPUT_NUM                 0X3B24//末端数量
#define REG_ADDR_PAD12_TWO_CHOOSE_MODE                    0X3B25//双末端模式选择
#define REG_ADDR_PAD12_BIND_FAN                           0X3B26//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD12_BIND_WARM                          0X3B27//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD12_WARM_TYPE                          0X3B28//辐射类型
#define REG_ADDR_PAD12_ROOM_AREA                          0X3B29//房间面积
#define REG_ADDR_PAD12_LEW_TEMP_STATUS                    0X3B2A//露点状态
#define REG_ADDR_PAD12_ADJUST_TEMP                        0X3B2B//校温
#define REG_ADDR_PAD12_ADJUST_HUM                         0X3B2C//校湿
#define REG_ADDR_PAD12_VERSION                            0X3B2D//版本号

#define REG_ADDR_PAD13_ERROR_WORD                         0X3C00//
#define REG_ADDR_PAD13_ONLINE_STATUS                      0X3C01//
#define REG_ADDR_PAD13_DEVICE_TYPE                        0X3C02//
#define REG_ADDR_PAD13_DEVICE_ID0                         0X3C03//
#define REG_ADDR_PAD13_DEVICE_ID1                         0X3C04//
#define REG_ADDR_PAD13_DEVICE_ID2                         0X3C05//
#define REG_ADDR_PAD13_POWER                              0X3C06//
#define REG_ADDR_PAD13_SET_COLD_TEMP                      0X3C07//
#define REG_ADDR_PAD13_SET_HEAT_TEMP                      0X3C08//
#define REG_ADDR_PAD13_LEW_DORP_TEMP                      0X3C09//露点温度
#define REG_ADDR_PAD13_COLD_WARM_STATUS                   0X3C0A//冷热运行状态
#define REG_ADDR_PAD13_FREEZE_PROTECT                     0X3C0B//防冻保护
#define REG_ADDR_PAD13_FREEZE_TEMP                        0X3C0C//
#define REG_ADDR_PAD13_CHILD_LOCK                         0X3C0D//
#define REG_ADDR_PAD13_POWER_MEMORY                       0X3C0E//
#define REG_ADDR_PAD13_COMFORTABLE_COLD_TEMP              0X3C0F//
#define REG_ADDR_PAD13_COMFORTABLE_HEAT_TEMP              0X3C10//
#define REG_ADDR_PAD13_SET_HIGH_TEMP                      0X3C11//
#define REG_ADDR_PAD13_SET_LOW_TEMP                       0X3C12//
#define REG_ADDR_PAD13_DEADZONE_TEMP                      0X3C13//
#define REG_ADDR_PAD13_DEADZONE_LEW_TEMP                  0X3C14//
#define REG_ADDR_PAD13_MEASURE_TEMP                       0X3C15//
#define REG_ADDR_PAD13_MEASURE_HUM                        0X3C16//
#define REG_ADDR_PAD13_WARM_NEED                          0X3C17//
#define REG_ADDR_PAD13_SET_FANSPEED                       0X3C18//设定风速 
#define REG_ADDR_PAD13_CONTROL_FAN                        0X3C19//风机受控
#define REG_ADDR_PAD13_PWM_LOW_FAN                        0X3C1A//
#define REG_ADDR_PAD13_PWM_MID_FAN                        0X3C1B//
#define REG_ADDR_PAD13_PWM_HIGH_FAN                       0X3C1C//
#define REG_ADDR_PAD13_AI_COLD_COLLA_DEADZONE             0X3C1D//
#define REG_ADDR_PAD13_AI_HEAT_COLLA_DEADZONE             0X3C1E//
#define REG_ADDR_PAD13_AI_COLD_COLLA_ENABLE               0X3C1F//制冷协同使能
#define REG_ADDR_PAD13_AI_HEAT_COLLA_ENABLE               0X3C20//制热协同使能
#define REG_ADDR_PAD13_FAN_VAVLE_NEED                     0X3C21//风阀需求
#define REG_ADDR_PAD13_FAN_OUTPUT_LEVEL                   0X3C22//风机输出状态
#define REG_ADDR_PAD13_FAN_SPEED                          0X3C23//EC风机转速
#define REG_ADDR_PAD13_CONTROL_OUTPUT_NUM                 0X3C24//末端数量
#define REG_ADDR_PAD13_TWO_CHOOSE_MODE                    0X3C25//双末端模式选择
#define REG_ADDR_PAD13_BIND_FAN                           0X3C26//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD13_BIND_WARM                          0X3C27//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD13_WARM_TYPE                          0X3C28//辐射类型
#define REG_ADDR_PAD13_ROOM_AREA                          0X3C29//房间面积
#define REG_ADDR_PAD13_LEW_TEMP_STATUS                    0X3C2A//露点状态
#define REG_ADDR_PAD13_ADJUST_TEMP                        0X3C2B//校温
#define REG_ADDR_PAD13_ADJUST_HUM                         0X3C2C//校湿
#define REG_ADDR_PAD13_VERSION                            0X3C2D//版本号

#define REG_ADDR_PAD14_ERROR_WORD                         0X3D00//
#define REG_ADDR_PAD14_ONLINE_STATUS                      0X3D01//
#define REG_ADDR_PAD14_DEVICE_TYPE                        0X3D02//
#define REG_ADDR_PAD14_DEVICE_ID0                         0X3D03//
#define REG_ADDR_PAD14_DEVICE_ID1                         0X3D04//
#define REG_ADDR_PAD14_DEVICE_ID2                         0X3D05//
#define REG_ADDR_PAD14_POWER                              0X3D06//
#define REG_ADDR_PAD14_SET_COLD_TEMP                      0X3D07//
#define REG_ADDR_PAD14_SET_HEAT_TEMP                      0X3D08//
#define REG_ADDR_PAD14_LEW_DORP_TEMP                      0X3D09//露点温度
#define REG_ADDR_PAD14_COLD_WARM_STATUS                   0X3D0A//冷热运行状态
#define REG_ADDR_PAD14_FREEZE_PROTECT                     0X3D0B//防冻保护
#define REG_ADDR_PAD14_FREEZE_TEMP                        0X3D0C//
#define REG_ADDR_PAD14_CHILD_LOCK                         0X3D0D//
#define REG_ADDR_PAD14_POWER_MEMORY                       0X3D0E//
#define REG_ADDR_PAD14_COMFORTABLE_COLD_TEMP              0X3D0F//
#define REG_ADDR_PAD14_COMFORTABLE_HEAT_TEMP              0X3D10//
#define REG_ADDR_PAD14_SET_HIGH_TEMP                      0X3D11//
#define REG_ADDR_PAD14_SET_LOW_TEMP                       0X3D12//
#define REG_ADDR_PAD14_DEADZONE_TEMP                      0X3D13//
#define REG_ADDR_PAD14_DEADZONE_LEW_TEMP                  0X3D14//
#define REG_ADDR_PAD14_MEASURE_TEMP                       0X3D15//
#define REG_ADDR_PAD14_MEASURE_HUM                        0X3D16//
#define REG_ADDR_PAD14_WARM_NEED                          0X3D17//
#define REG_ADDR_PAD14_SET_FANSPEED                       0X3D18//设定风速 
#define REG_ADDR_PAD14_CONTROL_FAN                        0X3D19//风机受控
#define REG_ADDR_PAD14_PWM_LOW_FAN                        0X3D1A//
#define REG_ADDR_PAD14_PWM_MID_FAN                        0X3D1B//
#define REG_ADDR_PAD14_PWM_HIGH_FAN                       0X3D1C//
#define REG_ADDR_PAD14_AI_COLD_COLLA_DEADZONE             0X3D1D//
#define REG_ADDR_PAD14_AI_HEAT_COLLA_DEADZONE             0X3D1E//
#define REG_ADDR_PAD14_AI_COLD_COLLA_ENABLE               0X3D1F//制冷协同使能
#define REG_ADDR_PAD14_AI_HEAT_COLLA_ENABLE               0X3D20//制热协同使能
#define REG_ADDR_PAD14_FAN_VAVLE_NEED                     0X3D21//风阀需求
#define REG_ADDR_PAD14_FAN_OUTPUT_LEVEL                   0X3D22//风机输出状态
#define REG_ADDR_PAD14_FAN_SPEED                          0X3D23//EC风机转速
#define REG_ADDR_PAD14_CONTROL_OUTPUT_NUM                 0X3D24//末端数量
#define REG_ADDR_PAD14_TWO_CHOOSE_MODE                    0X3D25//双末端模式选择
#define REG_ADDR_PAD14_BIND_FAN                           0X3D26//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD14_BIND_WARM                          0X3D27//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD14_WARM_TYPE                          0X3D28//辐射类型
#define REG_ADDR_PAD14_ROOM_AREA                          0X3D29//房间面积
#define REG_ADDR_PAD14_LEW_TEMP_STATUS                    0X3D2A//露点状态
#define REG_ADDR_PAD14_ADJUST_TEMP                        0X3D2B//校温
#define REG_ADDR_PAD14_ADJUST_HUM                         0X3D2C//校湿
#define REG_ADDR_PAD14_VERSION                            0X3D2D//版本号

#define REG_ADDR_PAD15_ERROR_WORD                         0X3E00//
#define REG_ADDR_PAD15_ONLINE_STATUS                      0X3E01//
#define REG_ADDR_PAD15_DEVICE_TYPE                        0X3E02//
#define REG_ADDR_PAD15_DEVICE_ID0                         0X3E03//
#define REG_ADDR_PAD15_DEVICE_ID1                         0X3E04//
#define REG_ADDR_PAD15_DEVICE_ID2                         0X3E05//
#define REG_ADDR_PAD15_POWER                              0X3E06//
#define REG_ADDR_PAD15_SET_COLD_TEMP                      0X3E07//
#define REG_ADDR_PAD15_SET_HEAT_TEMP                      0X3E08//
#define REG_ADDR_PAD15_LEW_DORP_TEMP                      0X3E09//露点温度
#define REG_ADDR_PAD15_COLD_WARM_STATUS                   0X3E0A//冷热运行状态
#define REG_ADDR_PAD15_FREEZE_PROTECT                     0X3E0B//防冻保护
#define REG_ADDR_PAD15_FREEZE_TEMP                        0X3E0C//
#define REG_ADDR_PAD15_CHILD_LOCK                         0X3E0D//
#define REG_ADDR_PAD15_POWER_MEMORY                       0X3E0E//
#define REG_ADDR_PAD15_COMFORTABLE_COLD_TEMP              0X3E0F//
#define REG_ADDR_PAD15_COMFORTABLE_HEAT_TEMP              0X3E10//
#define REG_ADDR_PAD15_SET_HIGH_TEMP                      0X3E11//
#define REG_ADDR_PAD15_SET_LOW_TEMP                       0X3E12//
#define REG_ADDR_PAD15_DEADZONE_TEMP                      0X3E13//
#define REG_ADDR_PAD15_DEADZONE_LEW_TEMP                  0X3E14//
#define REG_ADDR_PAD15_MEASURE_TEMP                       0X3E15//
#define REG_ADDR_PAD15_MEASURE_HUM                        0X3E16//
#define REG_ADDR_PAD15_WARM_NEED                          0X3E17//
#define REG_ADDR_PAD15_SET_FANSPEED                       0X3E18//设定风速 
#define REG_ADDR_PAD15_CONTROL_FAN                        0X3E19//风机受控
#define REG_ADDR_PAD15_PWM_LOW_FAN                        0X3E1A//
#define REG_ADDR_PAD15_PWM_MID_FAN                        0X3E1B//
#define REG_ADDR_PAD15_PWM_HIGH_FAN                       0X3E1C//
#define REG_ADDR_PAD15_AI_COLD_COLLA_DEADZONE             0X3E1D//
#define REG_ADDR_PAD15_AI_HEAT_COLLA_DEADZONE             0X3E1E//
#define REG_ADDR_PAD15_AI_COLD_COLLA_ENABLE               0X3E1F//制冷协同使能
#define REG_ADDR_PAD15_AI_HEAT_COLLA_ENABLE               0X3E20//制热协同使能
#define REG_ADDR_PAD15_FAN_VAVLE_NEED                     0X3E21//风阀需求
#define REG_ADDR_PAD15_FAN_OUTPUT_LEVEL                   0X3E22//风机输出状态
#define REG_ADDR_PAD15_FAN_SPEED                          0X3E23//EC风机转速
#define REG_ADDR_PAD15_CONTROL_OUTPUT_NUM                 0X3E24//末端数量
#define REG_ADDR_PAD15_TWO_CHOOSE_MODE                    0X3E25//双末端模式选择
#define REG_ADDR_PAD15_BIND_FAN                           0X3E26//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD15_BIND_WARM                          0X3E27//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD15_WARM_TYPE                          0X3E28//辐射类型
#define REG_ADDR_PAD15_ROOM_AREA                          0X3E29//房间面积
#define REG_ADDR_PAD15_LEW_TEMP_STATUS                    0X3E2A//露点状态
#define REG_ADDR_PAD15_ADJUST_TEMP                        0X3E2B//校温
#define REG_ADDR_PAD15_ADJUST_HUM                         0X3E2C//校湿
#define REG_ADDR_PAD15_VERSION                            0X3E2D//版本号

#define REG_ADDR_PAD16_ERROR_WORD                         0X3F00//
#define REG_ADDR_PAD16_ONLINE_STATUS                      0X3F01//
#define REG_ADDR_PAD16_DEVICE_TYPE                        0X3F02//
#define REG_ADDR_PAD16_DEVICE_ID0                         0X3F03//
#define REG_ADDR_PAD16_DEVICE_ID1                         0X3F04//
#define REG_ADDR_PAD16_DEVICE_ID2                         0X3F05//
#define REG_ADDR_PAD16_POWER                              0X3F06//
#define REG_ADDR_PAD16_SET_COLD_TEMP                      0X3F07//
#define REG_ADDR_PAD16_SET_HEAT_TEMP                      0X3F08//
#define REG_ADDR_PAD16_LEW_DORP_TEMP                      0X3F09//露点温度
#define REG_ADDR_PAD16_COLD_WARM_STATUS                   0X3F0A//冷热运行状态
#define REG_ADDR_PAD16_FREEZE_PROTECT                     0X3F0B//防冻保护
#define REG_ADDR_PAD16_FREEZE_TEMP                        0X3F0C//
#define REG_ADDR_PAD16_CHILD_LOCK                         0X3F0D//
#define REG_ADDR_PAD16_POWER_MEMORY                       0X3F0E//
#define REG_ADDR_PAD16_COMFORTABLE_COLD_TEMP              0X3F0F//
#define REG_ADDR_PAD16_COMFORTABLE_HEAT_TEMP              0X3F10//
#define REG_ADDR_PAD16_SET_HIGH_TEMP                      0X3F11//
#define REG_ADDR_PAD16_SET_LOW_TEMP                       0X3F12//
#define REG_ADDR_PAD16_DEADZONE_TEMP                      0X3F13//
#define REG_ADDR_PAD16_DEADZONE_LEW_TEMP                  0X3F14//
#define REG_ADDR_PAD16_MEASURE_TEMP                       0X3F15//
#define REG_ADDR_PAD16_MEASURE_HUM                        0X3F16//
#define REG_ADDR_PAD16_WARM_NEED                          0X3F17//
#define REG_ADDR_PAD16_SET_FANSPEED                       0X3F18//设定风速 
#define REG_ADDR_PAD16_CONTROL_FAN                        0X3F19//风机受控
#define REG_ADDR_PAD16_PWM_LOW_FAN                        0X3F1A//
#define REG_ADDR_PAD16_PWM_MID_FAN                        0X3F1B//
#define REG_ADDR_PAD16_PWM_HIGH_FAN                       0X3F1C//
#define REG_ADDR_PAD16_AI_COLD_COLLA_DEADZONE             0X3F1D//
#define REG_ADDR_PAD16_AI_HEAT_COLLA_DEADZONE             0X3F1E//
#define REG_ADDR_PAD16_AI_COLD_COLLA_ENABLE               0X3F1F//制冷协同使能
#define REG_ADDR_PAD16_AI_HEAT_COLLA_ENABLE               0X3F20//制热协同使能
#define REG_ADDR_PAD16_FAN_VAVLE_NEED                     0X3F21//风阀需求
#define REG_ADDR_PAD16_FAN_OUTPUT_LEVEL                   0X3F22//风机输出状态
#define REG_ADDR_PAD16_FAN_SPEED                          0X3F23//EC风机转速
#define REG_ADDR_PAD16_CONTROL_OUTPUT_NUM                 0X3F24//末端数量
#define REG_ADDR_PAD16_TWO_CHOOSE_MODE                    0X3F25//双末端模式选择
#define REG_ADDR_PAD16_BIND_FAN                           0X3F26//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD16_BIND_WARM                          0X3F27//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD16_WARM_TYPE                          0X3F28//辐射类型
#define REG_ADDR_PAD16_ROOM_AREA                          0X3F29//房间面积
#define REG_ADDR_PAD16_LEW_TEMP_STATUS                    0X3F2A//露点状态
#define REG_ADDR_PAD16_ADJUST_TEMP                        0X3F2B//校温
#define REG_ADDR_PAD16_ADJUST_HUM                         0X3F2C//校湿
#define REG_ADDR_PAD16_VERSION                            0X3F2D//版本号

#define REG_ADDR_PAD17_ERROR_WORD                         0X4000//
#define REG_ADDR_PAD17_ONLINE_STATUS                      0X4001//
#define REG_ADDR_PAD17_DEVICE_TYPE                        0X4002//
#define REG_ADDR_PAD17_DEVICE_ID0                         0X4003//
#define REG_ADDR_PAD17_DEVICE_ID1                         0X4004//
#define REG_ADDR_PAD17_DEVICE_ID2                         0X4005//
#define REG_ADDR_PAD17_POWER                              0X4006//
#define REG_ADDR_PAD17_SET_COLD_TEMP                      0X4007//
#define REG_ADDR_PAD17_SET_HEAT_TEMP                      0X4008//
#define REG_ADDR_PAD17_LEW_DORP_TEMP                      0X4009//露点温度
#define REG_ADDR_PAD17_COLD_WARM_STATUS                   0X400A//冷热运行状态
#define REG_ADDR_PAD17_FREEZE_PROTECT                     0X400B//防冻保护
#define REG_ADDR_PAD17_FREEZE_TEMP                        0X400C//
#define REG_ADDR_PAD17_CHILD_LOCK                         0X400D//
#define REG_ADDR_PAD17_POWER_MEMORY                       0X400E//
#define REG_ADDR_PAD17_COMFORTABLE_COLD_TEMP              0X400F//
#define REG_ADDR_PAD17_COMFORTABLE_HEAT_TEMP              0X4010//
#define REG_ADDR_PAD17_SET_HIGH_TEMP                      0X4011//
#define REG_ADDR_PAD17_SET_LOW_TEMP                       0X4012//
#define REG_ADDR_PAD17_DEADZONE_TEMP                      0X4013//
#define REG_ADDR_PAD17_DEADZONE_LEW_TEMP                  0X4014//
#define REG_ADDR_PAD17_MEASURE_TEMP                       0X4015//
#define REG_ADDR_PAD17_MEASURE_HUM                        0X4016//
#define REG_ADDR_PAD17_WARM_NEED                          0X4017//
#define REG_ADDR_PAD17_SET_FANSPEED                       0X4018//设定风速 
#define REG_ADDR_PAD17_CONTROL_FAN                        0X4019//风机受控
#define REG_ADDR_PAD17_PWM_LOW_FAN                        0X401A//
#define REG_ADDR_PAD17_PWM_MID_FAN                        0X401B//
#define REG_ADDR_PAD17_PWM_HIGH_FAN                       0X401C//
#define REG_ADDR_PAD17_AI_COLD_COLLA_DEADZONE             0X401D//
#define REG_ADDR_PAD17_AI_HEAT_COLLA_DEADZONE             0X401E//
#define REG_ADDR_PAD17_AI_COLD_COLLA_ENABLE               0X401F//制冷协同使能
#define REG_ADDR_PAD17_AI_HEAT_COLLA_ENABLE               0X4020//制热协同使能
#define REG_ADDR_PAD17_FAN_VAVLE_NEED                     0X4021//风阀需求
#define REG_ADDR_PAD17_FAN_OUTPUT_LEVEL                   0X4022//风机输出状态
#define REG_ADDR_PAD17_FAN_SPEED                          0X4023//EC风机转速
#define REG_ADDR_PAD17_CONTROL_OUTPUT_NUM                 0X4024//末端数量
#define REG_ADDR_PAD17_TWO_CHOOSE_MODE                    0X4025//双末端模式选择
#define REG_ADDR_PAD17_BIND_FAN                           0X4026//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD17_BIND_WARM                          0X4027//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD17_WARM_TYPE                          0X4028//辐射类型
#define REG_ADDR_PAD17_ROOM_AREA                          0X4029//房间面积
#define REG_ADDR_PAD17_LEW_TEMP_STATUS                    0X402A//露点状态
#define REG_ADDR_PAD17_ADJUST_TEMP                        0X402B//校温
#define REG_ADDR_PAD17_ADJUST_HUM                         0X402C//校湿
#define REG_ADDR_PAD17_VERSION                            0X402D//版本号

#define REG_ADDR_PAD18_ERROR_WORD                         0X4100//
#define REG_ADDR_PAD18_ONLINE_STATUS                      0X4101//
#define REG_ADDR_PAD18_DEVICE_TYPE                        0X4102//
#define REG_ADDR_PAD18_DEVICE_ID0                         0X4103//
#define REG_ADDR_PAD18_DEVICE_ID1                         0X4104//
#define REG_ADDR_PAD18_DEVICE_ID2                         0X4105//
#define REG_ADDR_PAD18_POWER                              0X4106//
#define REG_ADDR_PAD18_SET_COLD_TEMP                      0X4107//
#define REG_ADDR_PAD18_SET_HEAT_TEMP                      0X4108//
#define REG_ADDR_PAD18_LEW_DORP_TEMP                      0X4109//露点温度
#define REG_ADDR_PAD18_COLD_WARM_STATUS                   0X410A//冷热运行状态
#define REG_ADDR_PAD18_FREEZE_PROTECT                     0X410B//防冻保护
#define REG_ADDR_PAD18_FREEZE_TEMP                        0X410C//
#define REG_ADDR_PAD18_CHILD_LOCK                         0X410D//
#define REG_ADDR_PAD18_POWER_MEMORY                       0X410E//
#define REG_ADDR_PAD18_COMFORTABLE_COLD_TEMP              0X410F//
#define REG_ADDR_PAD18_COMFORTABLE_HEAT_TEMP              0X4110//
#define REG_ADDR_PAD18_SET_HIGH_TEMP                      0X4111//
#define REG_ADDR_PAD18_SET_LOW_TEMP                       0X4112//
#define REG_ADDR_PAD18_DEADZONE_TEMP                      0X4113//
#define REG_ADDR_PAD18_DEADZONE_LEW_TEMP                  0X4114//
#define REG_ADDR_PAD18_MEASURE_TEMP                       0X4115//
#define REG_ADDR_PAD18_MEASURE_HUM                        0X4116//
#define REG_ADDR_PAD18_WARM_NEED                          0X4117//
#define REG_ADDR_PAD18_SET_FANSPEED                       0X4118//设定风速 
#define REG_ADDR_PAD18_CONTROL_FAN                        0X4119//风机受控
#define REG_ADDR_PAD18_PWM_LOW_FAN                        0X411A//
#define REG_ADDR_PAD18_PWM_MID_FAN                        0X411B//
#define REG_ADDR_PAD18_PWM_HIGH_FAN                       0X411C//
#define REG_ADDR_PAD18_AI_COLD_COLLA_DEADZONE             0X411D//
#define REG_ADDR_PAD18_AI_HEAT_COLLA_DEADZONE             0X411E//
#define REG_ADDR_PAD18_AI_COLD_COLLA_ENABLE               0X411F//制冷协同使能
#define REG_ADDR_PAD18_AI_HEAT_COLLA_ENABLE               0X4120//制热协同使能
#define REG_ADDR_PAD18_FAN_VAVLE_NEED                     0X4121//风阀需求
#define REG_ADDR_PAD18_FAN_OUTPUT_LEVEL                   0X4122//风机输出状态
#define REG_ADDR_PAD18_FAN_SPEED                          0X4123//EC风机转速
#define REG_ADDR_PAD18_CONTROL_OUTPUT_NUM                 0X4124//末端数量
#define REG_ADDR_PAD18_TWO_CHOOSE_MODE                    0X4125//双末端模式选择
#define REG_ADDR_PAD18_BIND_FAN                           0X4126//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD18_BIND_WARM                          0X4127//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD18_WARM_TYPE                          0X4128//辐射类型
#define REG_ADDR_PAD18_ROOM_AREA                          0X4129//房间面积
#define REG_ADDR_PAD18_LEW_TEMP_STATUS                    0X412A//露点状态
#define REG_ADDR_PAD18_ADJUST_TEMP                        0X412B//校温
#define REG_ADDR_PAD18_ADJUST_HUM                         0X412C//校湿
#define REG_ADDR_PAD18_VERSION                            0X412D//版本号

#define REG_ADDR_PAD19_ERROR_WORD                         0X4200//
#define REG_ADDR_PAD19_ONLINE_STATUS                      0X4201//
#define REG_ADDR_PAD19_DEVICE_TYPE                        0X4202//
#define REG_ADDR_PAD19_DEVICE_ID0                         0X4203//
#define REG_ADDR_PAD19_DEVICE_ID1                         0X4204//
#define REG_ADDR_PAD19_DEVICE_ID2                         0X4205//
#define REG_ADDR_PAD19_POWER                              0X4206//
#define REG_ADDR_PAD19_SET_COLD_TEMP                      0X4207//
#define REG_ADDR_PAD19_SET_HEAT_TEMP                      0X4208//
#define REG_ADDR_PAD19_LEW_DORP_TEMP                      0X4209//露点温度
#define REG_ADDR_PAD19_COLD_WARM_STATUS                   0X420A//冷热运行状态
#define REG_ADDR_PAD19_FREEZE_PROTECT                     0X420B//防冻保护
#define REG_ADDR_PAD19_FREEZE_TEMP                        0X420C//
#define REG_ADDR_PAD19_CHILD_LOCK                         0X420D//
#define REG_ADDR_PAD19_POWER_MEMORY                       0X420E//
#define REG_ADDR_PAD19_COMFORTABLE_COLD_TEMP              0X420F//
#define REG_ADDR_PAD19_COMFORTABLE_HEAT_TEMP              0X4210//
#define REG_ADDR_PAD19_SET_HIGH_TEMP                      0X4211//
#define REG_ADDR_PAD19_SET_LOW_TEMP                       0X4212//
#define REG_ADDR_PAD19_DEADZONE_TEMP                      0X4213//
#define REG_ADDR_PAD19_DEADZONE_LEW_TEMP                  0X4214//
#define REG_ADDR_PAD19_MEASURE_TEMP                       0X4215//
#define REG_ADDR_PAD19_MEASURE_HUM                        0X4216//
#define REG_ADDR_PAD19_WARM_NEED                          0X4217//
#define REG_ADDR_PAD19_SET_FANSPEED                       0X4218//设定风速 
#define REG_ADDR_PAD19_CONTROL_FAN                        0X4219//风机受控
#define REG_ADDR_PAD19_PWM_LOW_FAN                        0X421A//
#define REG_ADDR_PAD19_PWM_MID_FAN                        0X421B//
#define REG_ADDR_PAD19_PWM_HIGH_FAN                       0X421C//
#define REG_ADDR_PAD19_AI_COLD_COLLA_DEADZONE             0X421D//
#define REG_ADDR_PAD19_AI_HEAT_COLLA_DEADZONE             0X421E//
#define REG_ADDR_PAD19_AI_COLD_COLLA_ENABLE               0X421F//制冷协同使能
#define REG_ADDR_PAD19_AI_HEAT_COLLA_ENABLE               0X4220//制热协同使能
#define REG_ADDR_PAD19_FAN_VAVLE_NEED                     0X4221//风阀需求
#define REG_ADDR_PAD19_FAN_OUTPUT_LEVEL                   0X4222//风机输出状态
#define REG_ADDR_PAD19_FAN_SPEED                          0X4223//EC风机转速
#define REG_ADDR_PAD19_CONTROL_OUTPUT_NUM                 0X4224//末端数量
#define REG_ADDR_PAD19_TWO_CHOOSE_MODE                    0X4225//双末端模式选择
#define REG_ADDR_PAD19_BIND_FAN                           0X4226//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD19_BIND_WARM                          0X4227//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD19_WARM_TYPE                          0X4228//辐射类型
#define REG_ADDR_PAD19_ROOM_AREA                          0X4229//房间面积
#define REG_ADDR_PAD19_LEW_TEMP_STATUS                    0X422A//露点状态
#define REG_ADDR_PAD19_ADJUST_TEMP                        0X422B//校温
#define REG_ADDR_PAD19_ADJUST_HUM                         0X422C//校湿
#define REG_ADDR_PAD19_VERSION                            0X422D//版本号

#define REG_ADDR_PAD20_ERROR_WORD                         0X4300//
#define REG_ADDR_PAD20_ONLINE_STATUS                      0X4301//
#define REG_ADDR_PAD20_DEVICE_TYPE                        0X4302//
#define REG_ADDR_PAD20_DEVICE_ID0                         0X4303//
#define REG_ADDR_PAD20_DEVICE_ID1                         0X4304//
#define REG_ADDR_PAD20_DEVICE_ID2                         0X4305//
#define REG_ADDR_PAD20_POWER                              0X4306//
#define REG_ADDR_PAD20_SET_COLD_TEMP                      0X4307//
#define REG_ADDR_PAD20_SET_HEAT_TEMP                      0X4308//
#define REG_ADDR_PAD20_LEW_DORP_TEMP                      0X4309//露点温度
#define REG_ADDR_PAD20_COLD_WARM_STATUS                   0X430A//冷热运行状态
#define REG_ADDR_PAD20_FREEZE_PROTECT                     0X430B//防冻保护
#define REG_ADDR_PAD20_FREEZE_TEMP                        0X430C//
#define REG_ADDR_PAD20_CHILD_LOCK                         0X430D//
#define REG_ADDR_PAD20_POWER_MEMORY                       0X430E//
#define REG_ADDR_PAD20_COMFORTABLE_COLD_TEMP              0X430F//
#define REG_ADDR_PAD20_COMFORTABLE_HEAT_TEMP              0X4310//
#define REG_ADDR_PAD20_SET_HIGH_TEMP                      0X4311//
#define REG_ADDR_PAD20_SET_LOW_TEMP                       0X4312//
#define REG_ADDR_PAD20_DEADZONE_TEMP                      0X4313//
#define REG_ADDR_PAD20_DEADZONE_LEW_TEMP                  0X4314//
#define REG_ADDR_PAD20_MEASURE_TEMP                       0X4315//
#define REG_ADDR_PAD20_MEASURE_HUM                        0X4316//
#define REG_ADDR_PAD20_WARM_NEED                          0X4317//
#define REG_ADDR_PAD20_SET_FANSPEED                       0X4318//设定风速 
#define REG_ADDR_PAD20_CONTROL_FAN                        0X4319//风机受控
#define REG_ADDR_PAD20_PWM_LOW_FAN                        0X431A//
#define REG_ADDR_PAD20_PWM_MID_FAN                        0X431B//
#define REG_ADDR_PAD20_PWM_HIGH_FAN                       0X431C//
#define REG_ADDR_PAD20_AI_COLD_COLLA_DEADZONE             0X431D//
#define REG_ADDR_PAD20_AI_HEAT_COLLA_DEADZONE             0X431E//
#define REG_ADDR_PAD20_AI_COLD_COLLA_ENABLE               0X431F//制冷协同使能
#define REG_ADDR_PAD20_AI_HEAT_COLLA_ENABLE               0X4320//制热协同使能
#define REG_ADDR_PAD20_FAN_VAVLE_NEED                     0X4321//风阀需求
#define REG_ADDR_PAD20_FAN_OUTPUT_LEVEL                   0X4322//风机输出状态
#define REG_ADDR_PAD20_FAN_SPEED                          0X4323//EC风机转速
#define REG_ADDR_PAD20_CONTROL_OUTPUT_NUM                 0X4324//末端数量
#define REG_ADDR_PAD20_TWO_CHOOSE_MODE                    0X4325//双末端模式选择
#define REG_ADDR_PAD20_BIND_FAN                           0X4326//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD20_BIND_WARM                          0X4327//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD20_WARM_TYPE                          0X4328//辐射类型
#define REG_ADDR_PAD20_ROOM_AREA                          0X4329//房间面积
#define REG_ADDR_PAD20_LEW_TEMP_STATUS                    0X432A//露点状态
#define REG_ADDR_PAD20_ADJUST_TEMP                        0X432B//校温
#define REG_ADDR_PAD20_ADJUST_HUM                         0X432C//校湿
#define REG_ADDR_PAD20_VERSION                            0X432D//版本号

#define REG_ADDR_PAD21_ERROR_WORD                         0X4400//
#define REG_ADDR_PAD21_ONLINE_STATUS                      0X4401//
#define REG_ADDR_PAD21_DEVICE_TYPE                        0X4402//
#define REG_ADDR_PAD21_DEVICE_ID0                         0X4403//
#define REG_ADDR_PAD21_DEVICE_ID1                         0X4404//
#define REG_ADDR_PAD21_DEVICE_ID2                         0X4405//
#define REG_ADDR_PAD21_POWER                              0X4406//
#define REG_ADDR_PAD21_SET_COLD_TEMP                      0X4407//
#define REG_ADDR_PAD21_SET_HEAT_TEMP                      0X4408//
#define REG_ADDR_PAD21_LEW_DORP_TEMP                      0X4409//露点温度
#define REG_ADDR_PAD21_COLD_WARM_STATUS                   0X440A//冷热运行状态
#define REG_ADDR_PAD21_FREEZE_PROTECT                     0X440B//防冻保护
#define REG_ADDR_PAD21_FREEZE_TEMP                        0X440C//
#define REG_ADDR_PAD21_CHILD_LOCK                         0X440D//
#define REG_ADDR_PAD21_POWER_MEMORY                       0X440E//
#define REG_ADDR_PAD21_COMFORTABLE_COLD_TEMP              0X440F//
#define REG_ADDR_PAD21_COMFORTABLE_HEAT_TEMP              0X4410//
#define REG_ADDR_PAD21_SET_HIGH_TEMP                      0X4411//
#define REG_ADDR_PAD21_SET_LOW_TEMP                       0X4412//
#define REG_ADDR_PAD21_DEADZONE_TEMP                      0X4413//
#define REG_ADDR_PAD21_DEADZONE_LEW_TEMP                  0X4414//
#define REG_ADDR_PAD21_MEASURE_TEMP                       0X4415//
#define REG_ADDR_PAD21_MEASURE_HUM                        0X4416//
#define REG_ADDR_PAD21_WARM_NEED                          0X4417//
#define REG_ADDR_PAD21_SET_FANSPEED                       0X4418//设定风速 
#define REG_ADDR_PAD21_CONTROL_FAN                        0X4419//风机受控
#define REG_ADDR_PAD21_PWM_LOW_FAN                        0X441A//
#define REG_ADDR_PAD21_PWM_MID_FAN                        0X441B//
#define REG_ADDR_PAD21_PWM_HIGH_FAN                       0X441C//
#define REG_ADDR_PAD21_AI_COLD_COLLA_DEADZONE             0X441D//
#define REG_ADDR_PAD21_AI_HEAT_COLLA_DEADZONE             0X441E//
#define REG_ADDR_PAD21_AI_COLD_COLLA_ENABLE               0X441F//制冷协同使能
#define REG_ADDR_PAD21_AI_HEAT_COLLA_ENABLE               0X4420//制热协同使能
#define REG_ADDR_PAD21_FAN_VAVLE_NEED                     0X4421//风阀需求
#define REG_ADDR_PAD21_FAN_OUTPUT_LEVEL                   0X4422//风机输出状态
#define REG_ADDR_PAD21_FAN_SPEED                          0X4423//EC风机转速
#define REG_ADDR_PAD21_CONTROL_OUTPUT_NUM                 0X4424//末端数量
#define REG_ADDR_PAD21_TWO_CHOOSE_MODE                    0X4425//双末端模式选择
#define REG_ADDR_PAD21_BIND_FAN                           0X4426//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD21_BIND_WARM                          0X4427//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD21_WARM_TYPE                          0X4428//辐射类型
#define REG_ADDR_PAD21_ROOM_AREA                          0X4429//房间面积
#define REG_ADDR_PAD21_LEW_TEMP_STATUS                    0X442A//露点状态
#define REG_ADDR_PAD21_ADJUST_TEMP                        0X442B//校温
#define REG_ADDR_PAD21_ADJUST_HUM                         0X442C//校湿
#define REG_ADDR_PAD21_VERSION                            0X442D//版本号

#define REG_ADDR_PAD22_ERROR_WORD                         0X4500//
#define REG_ADDR_PAD22_ONLINE_STATUS                      0X4501//
#define REG_ADDR_PAD22_DEVICE_TYPE                        0X4502//
#define REG_ADDR_PAD22_DEVICE_ID0                         0X4503//
#define REG_ADDR_PAD22_DEVICE_ID1                         0X4504//
#define REG_ADDR_PAD22_DEVICE_ID2                         0X4505//
#define REG_ADDR_PAD22_POWER                              0X4506//
#define REG_ADDR_PAD22_SET_COLD_TEMP                      0X4507//
#define REG_ADDR_PAD22_SET_HEAT_TEMP                      0X4508//
#define REG_ADDR_PAD22_LEW_DORP_TEMP                      0X4509//露点温度
#define REG_ADDR_PAD22_COLD_WARM_STATUS                   0X450A//冷热运行状态
#define REG_ADDR_PAD22_FREEZE_PROTECT                     0X450B//防冻保护
#define REG_ADDR_PAD22_FREEZE_TEMP                        0X450C//
#define REG_ADDR_PAD22_CHILD_LOCK                         0X450D//
#define REG_ADDR_PAD22_POWER_MEMORY                       0X450E//
#define REG_ADDR_PAD22_COMFORTABLE_COLD_TEMP              0X450F//
#define REG_ADDR_PAD22_COMFORTABLE_HEAT_TEMP              0X4510//
#define REG_ADDR_PAD22_SET_HIGH_TEMP                      0X4511//
#define REG_ADDR_PAD22_SET_LOW_TEMP                       0X4512//
#define REG_ADDR_PAD22_DEADZONE_TEMP                      0X4513//
#define REG_ADDR_PAD22_DEADZONE_LEW_TEMP                  0X4514//
#define REG_ADDR_PAD22_MEASURE_TEMP                       0X4515//
#define REG_ADDR_PAD22_MEASURE_HUM                        0X4516//
#define REG_ADDR_PAD22_WARM_NEED                          0X4517//
#define REG_ADDR_PAD22_SET_FANSPEED                       0X4518//设定风速 
#define REG_ADDR_PAD22_CONTROL_FAN                        0X4519//风机受控
#define REG_ADDR_PAD22_PWM_LOW_FAN                        0X451A//
#define REG_ADDR_PAD22_PWM_MID_FAN                        0X451B//
#define REG_ADDR_PAD22_PWM_HIGH_FAN                       0X451C//
#define REG_ADDR_PAD22_AI_COLD_COLLA_DEADZONE             0X451D//
#define REG_ADDR_PAD22_AI_HEAT_COLLA_DEADZONE             0X451E//
#define REG_ADDR_PAD22_AI_COLD_COLLA_ENABLE               0X451F//制冷协同使能
#define REG_ADDR_PAD22_AI_HEAT_COLLA_ENABLE               0X4520//制热协同使能
#define REG_ADDR_PAD22_FAN_VAVLE_NEED                     0X4521//风阀需求
#define REG_ADDR_PAD22_FAN_OUTPUT_LEVEL                   0X4522//风机输出状态
#define REG_ADDR_PAD22_FAN_SPEED                          0X4523//EC风机转速
#define REG_ADDR_PAD22_CONTROL_OUTPUT_NUM                 0X4524//末端数量
#define REG_ADDR_PAD22_TWO_CHOOSE_MODE                    0X4525//双末端模式选择
#define REG_ADDR_PAD22_BIND_FAN                           0X4526//绑定的阀门列表 (风盘)
#define REG_ADDR_PAD22_BIND_WARM                          0X4527//绑定的阀门列表 (辐射)
#define REG_ADDR_PAD22_WARM_TYPE                          0X4528//辐射类型
#define REG_ADDR_PAD22_ROOM_AREA                          0X4529//房间面积
#define REG_ADDR_PAD22_LEW_TEMP_STATUS                    0X452A//露点状态
#define REG_ADDR_PAD22_ADJUST_TEMP                        0X452B//校温
#define REG_ADDR_PAD22_ADJUST_HUM                         0X452C//校湿
#define REG_ADDR_PAD22_VERSION                            0X452D//版本号

#define DP_ADDR_PAD_POWER                                 0X00
#define DP_ADDR_PAD_SET_COLD_TEMP                         0X01
#define DP_ADDR_PAD_SET_HEAT_TEMP                         0X02
#define DP_ADDR_PAD_CHILD_LOCK                            0X03
#define DP_ADDR_PAD_SET_FAN                               0X04
#define DP_ADDR_PAD_TWO_CNONTROL_MODE                     0X05
#define DP_ADDR_PAD_BIND_MESSAGE                          0X06
#define DP_ADDR_PAD_STATUS_MESSAGE                        0X07
#define DP_ADDR_PAD_MEASURE_MESSAGE                       0X08
#define DP_ADDR_PAD_ADV_MESSAGE                           0X09
#define DP_ADDR_PAD_SYSTEM_MESSAGE                        0X0A
#define DP_ADDR_PAD_SYSTEM_RTC                            0X0B
#define DP_ADDR_PAD_DEVICE_TYPE                           0X0D

#define DP_ADDR_START                                    0X0100
#define DP_ADDR_SYSTEM_POWER                             0X0100
#define DP_ADDR_SYSTEM_RUN_MODE                          0X0101
#define DP_ADDR_SYSTEM_WIND_SET_CLOD_TEMP                0X0102
#define DP_ADDR_SYSTEM_WIND_SET_HEAT_TEMP                0X0103
#define DP_ADDR_SYSTEM_WIND_SET_HUM                      0X0104
#define DP_ADDR_SYSTEM_WIND_SET_SPEED                    0X0105
#define DP_ADDR_SYSTEM_WATER_SET_CLOD_TEMP               0X0106
#define DP_ADDR_SYSTEM_WATER_SET_HEAT_TEMP               0X0107
#define DP_ADDR_SYSTEM_WATER_SET_LIVING_TEMP             0X0108
#define DP_ADDR_SYSTEM_MIXWATER_SET_CLOD_TEMP            0X0109
#define DP_ADDR_SYSTEM_MIXWATER_SET_HEAT_TEMP            0X010A
#define DP_ADDR_SYSTEM_MIXWATER_AI_ENABLE                0X010B
#define DP_ADDR_SYSTEM_MIXWATER_LOW_TEMP_PROTECT         0X010C
#define DP_ADDR_SYSTEM_MIXWATER_AI_DEST_TEMP             0X010D
#define DP_ADDR_SYSTEM_LIS_NEW_AIR_PWM                   0X010E
#define DP_ADDR_SYSTEM_LIS_BACK_AIR_PWM                  0X010F
#define DP_ADDR_SYSTEM_LIS_OUTDOOR_WEATHER               0X0110
#define DP_ADDR_SYSTEM_LIS_BEFORE_FU_WEATHER             0X0111
#define DP_ADDR_SYSTEM_LIS_AFTER_FU_WEATHER              0X0112
#define DP_ADDR_SYSTEM_LIS_BACK_AIR_WEATHER              0X0113
#define DP_ADDR_SYSTEM_LIS_EXHAST_AIR_WEATHER            0X0114
#define DP_ADDR_SYSTEM_LIS_DEAD_ZONE                     0X0115
#define DP_ADDR_SYSTEM_LIS_OUT_VALVE                     0X0116
#define DP_ADDR_SYSTEM_LIS_OUT_STATUS                    0X0117
#define DP_ADDR_SYSTEM_LIS_MIXWATER_OUT                  0X0118
#define DP_ADDR_SYSTEM_LIS_MAIN_MACHINE_TEMP             0X0119
#define DP_ADDR_SYSTEM_LIS_MIXWATER_TEMP                 0X011A
#define DP_ADDR_SYSTEM_LIS_RTC                           0X011B
#define DP_ADDR_SYSTEM_LIS_485_PAREMETER                 0X011C
#define DP_ADDR_SYSTEM_AIRCOD_READ_ONLY_PAREMETER        0X011D
#define DP_ADDR_SYSTEM_AIRCOD_READ_WRITE_PAREMETER       0X011E
#define DP_ADDR_SYSTEM_AIRCOD_COLD_BACK_WATER            0X011F
#define DP_ADDR_SYSTEM_AIRCOD_WARM_BACK_WATER            0X0120
#define DP_ADDR_WRITE_DEVICE_ID                          0X1000

#define DP_ADDR_DHM_START                                0X0200


#define DEVICE_TYPE                                      0x8522
#define DEVICE_TYPE_HC                                   0x8521//环控
#define DEVICE_TYPE_CC                                   0x8522//输配
#define DEVICE_TYPE_FAN                                  0x9521//风盘
#define DEVICE_TYPE_ROMM                                 0x9522//面板
#define DEVICE_TYPE_DHM                                  0x9523//除湿模块
#define SOURCE_OUTSIDE                                   0x0001
#define SOURCE_INSIDE                                    0x0002
#define DEVICE_VERSION                                   0x2103

//-----------------------------------------------------------------------------
uint16_t app_modbus_read_reg_data(uint16_t reg_addr,uint8_t in_src);
bool app_modebus_write_reg_data(uint16_t reg_addr,uint16_t reg_detailes,uint8_t in_src);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif