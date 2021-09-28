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
#define MRegaddr_Restoragefac                            0x200F   //恢复出厂设置   3589
//-----------------------------------------------------------------------------
#define REG_ADDR_MASTER_ERROR_WORD                       0X2C00   //主机故障字
#define REG_ADDR_AIRCOD_ENERGY_NEED                      0X2C01   //旁通输出
#define REG_ADDR_SYSTEM_POWER                            0X2C02   //系统开关机
#define REG_ADDR_SYSTEM_RUN_MODE                         0X2C03   //系统运行模式
#define REG_ADDR_FAN_SET_HUM                             0X2C04   //通风制冷/除湿模式设定相对湿度
#define REG_ADDR_FAN_SET_SPEED                           0X2C05   //通风设定风速 
#define REG_ADDR_MASTER_SET_COLD_WATER_TEMP              0X2C0E  //主机制冷模式设定水温
#define REG_ADDR_MASTER_SET_HEAT_WATER_TEMP              0X2C0F  //主机制热模式设定水温
#define REG_ADDR_WATER_MACHINE_FRE                       0X2C21//水机压缩机频率
#define REG_ADDR_MASTER_SUPPLY_TEMP                      0X2C23//主机供水温度
#define REG_ADDR_YESTERDAY_POWER_USED                    0X2C2C//昨日能耗
#define REG_ADDR_TODAY_POWER_USED                        0X2C2D//今日能耗
#define REG_ADDR_SYSTEM_STATSU                           0X2C36//主机状态字
#define REG_ADDR_LEW_PROTECT_STATSU                      0X2C37//露点保护状态
#define REG_ADDR_PAD_OUTPUT_STATSU                       0X2C38//末端输出状态
#define REG_ADDR_FIIST_SUPPLY_WATER_TEMP                 0X2C3C//输配一次侧供水温度
#define REG_ADDR_FIIST_BACK_WATER_TEMP                   0X2C3D//输配一次侧回水温度
#define REG_ADDR_SET_MIXWATER_COLD_TEMP                  0X2C3E//混水制冷设定温度
#define REG_ADDR_SET_MIXWATER_HEAT_TEMP                  0X2C3F//混水制热设定温度
#define REG_ADDR_MIXWATER_BACKWATER_TEMP                 0X2C41//输配二次侧回水温度
#define REG_ADDR_MIXWATER_TEMP                           0X2C42//输配混水温度
#define REG_ADDR_OUTPUT_PUMP                             0X2C43//输配水泵状态
#define REG_ADDR_OUTPUT_THREE_VAVLE                      0X2C44//输配三通阀门输出状态
#define REG_ADDR_MIXWATER_LOW_TEMP_PROTECT               0X2C47//输配防冻保护
#define REG_ADRESS_MAIN_CONTROL_METHOD   			     0x2c5B//主控策略
#define REG_ADRESS_LEW_STATUS_OPEN_DIFF				     0x2c5C//露点状态上限(开启)
#define REG_ADRESS_LEW_STATUS_CLOSE_DIFF				 0x2c5D//露点状态下限(关闭)
#define REG_ADRESS_CC_RESET			                     0x2c5E//输配软件复位
#define REG_ADRESS_HC_RESET   			                 0x2c5F//环控软件复位
#define REG_ADRESS_DEBUG_ENABLE  						 0x2c60//调试使能
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
#define REG_ADRESS_CC_DEVICE_NUM                         0x2E00//输配数量
#define REG_ADRESS_CC_DEVICE_SEL                         0x2E01//当前输配片选
#define REG_ADRESS_CC_DEVICE_MASTER                      0x2E02//主站选择
#define REG_ADRESS_HARDWARESIGN                          0x2E03//输配中心硬件标识

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
/*除湿模块*/
#define REG_ADDR_DHM_START                               0X4000//除湿模块起始地址
#define REG_ADDR_DHM1_ONLINE_STATUS                      0X4000//在线状态
#define REG_ADDR_DHM1_DEVICE_TYPE                        0X4001//设备类型
#define REG_ADDR_DHM1_VERSION                            0X4002//版本号
#define REG_ADDR_DHM1_HARDSIGN                           0X4003//硬件标识
#define REG_ADDR_DHM1_POWER                              0X4004//除湿模块开关机
#define REG_ADDR_DHM1_RUN_STATUS                         0X4005//除湿模块运行状态
#define REG_ADDR_DHM1_SET_HUM                            0X4006//设定湿度 
#define REG_ADDR_DHM1_SET_FANSPEED                       0X4007//设定风速 
#define REG_ADDR_DHM1_RUN_FANSPEED                       0X4008//运行风速 
#define REG_ADDR_DHM1_SET_WARM_TEMP                      0X4009//设定制热目标温度 
#define REG_ADDR_DHM1_SET_CLOD_TEMP                      0X400A//设定制冷目标温度
#define REG_ADDR_DHM1_SET_BACK_HOT_TEMP                  0X400B//设定回热目标温度
#define REG_ADDR_DHM1_SYSTEM_TEMP                        0X400C//系统温度 
#define REG_ADDR_DHM1_SYSTEM_HUM                         0X400D//系统湿度
#define REG_ADDR_DHM1_IN_WIND_TEMP                       0X400E//进风温度
#define REG_ADDR_DHM1_IN_WIND_HUM                        0X400F //进风湿度
#define REG_ADDR_DHM1_OUT_WIND_TEMP                      0X4010//出风温度
#define REG_ADDR_DHM1_OUT_WIND_HUM                       0X4011// 出风湿度
#define REG_ADDR_DHM1_BACK_AIR_TEMP                      0X4012//室内温度
#define REG_ADDR_DHM1_BACK_AIR_HUM                       0X4013 //室内湿度
#define REG_ADDR_DHM1_BACK_AIR_CO2                       0X4014 //室内CO2
#define REG_ADDR_DHM1_BACK_AIR_PM25                      0X4015 //室内PM2.5
#define REG_ADDR_DHM1_RESEVER4_TEMP                      0X4016 //预留4温度
#define REG_ADDR_DHM1_RESEVER4_HUM                       0X4017 //预留4湿度
#define REG_ADDR_DHM1_RESEVER5_TEMP                      0X4018//预留5温度 
#define REG_ADDR_DHM1_RESEVER5_HUM                       0X4019//预留5湿度
#define REG_ADDR_DHM1_PTC_TEMP                           0X401A//PTC温度
#define REG_ADDR_DHM1_TEMP_DIFF                          0X401B//温度带宽 
#define REG_ADDR_DHM1_HUM_DIFF                           0X401C//湿度带宽
#define REG_ADDR_DHM1_PTC_PROTECT_DIFF                   0X401D//PTC保护带宽
#define REG_ADDR_DHM1_PTC_LIMIT_TEMP                     0X401E //PTC温度限制
#define REG_ADDR_DHM1_HOT_VAVLE_OUT                      0X401F//电热阀输出
#define REG_ADDR_DHM1_LIFT_PUMP_OUT                      0X4020// 提水泵输出
#define REG_ADDR_DHM1_PTC_OUT                            0X4021//PTC输出
#define REG_ADDR_DHM1_MAIN_OUT                           0X4022 //输配接口输出
#define REG_ADDR_DHM1_HOT_ASSIST                         0X4023 //辅助制热
#define REG_ADDR_DHM1_ADJUST_IN_WIND_TEMP                0X4024 //进风校准温度
#define REG_ADDR_DHM1_ADJUST_IN_WIND_HUM                 0X4025 //进风校准湿度
#define REG_ADDR_DHM1_ADJUST_OUT_WIND_TEMP               0X4026 //出风校准温度
#define REG_ADDR_DHM1_ADJUST_OUT_WIND_HUM                0X4027//出风校准湿度 
#define REG_ADDR_DHM1_ADJUST_BACK_WIND_TEMP              0X4028//室内校准温度
#define REG_ADDR_DHM1_ADJUST_BACK_WIND_HUM               0X4029//室内校准湿度
#define REG_ADDR_DHM1_ADJUST_BACK_WIND_CO2               0X402A//室内校准CO2 
#define REG_ADDR_DHM1_ADJUST_BACK_WIND_PM25              0X402B//室内校准PM2.5
#define REG_ADDR_DHM1_ADJUST_4_TEMP                      0X402C//校准4温度
#define REG_ADDR_DHM1_ADJUST_4_HUM                       0X402D //校准4湿度
#define REG_ADDR_DHM1_ADJUST_5_TEMP                      0X402E//校准5温度
#define REG_ADDR_DHM1_ADJUST_5_HUM                       0X402F// 校准5湿度
#define REG_ADDR_DHM1_DEVICE_ERROR                       0X4030//设备故障字
#define REG_ADDR_DHM1_DEVICE_RESET                       0X4031 //故障复位字
#define REG_ADDR_DHM1_NEW_AIR_LOW_PWM                    0X4032 //新风低风量PWM值
#define REG_ADDR_DHM1_NEW_AIR_MID_PWM                    0X4033 //新风中风量PWM值	
#define REG_ADDR_DHM1_NEW_AIR_HIGH_PWM                   0X4034 //新风高风量PWM值
#define REG_ADDR_DHM1_BACK_AIR_LOW_PWM                   0X4035 //回风低风量PWM值
#define REG_ADDR_DHM1_BACK_AIR_MID_PWM                   0X4036//回风中风量PWM值 
#define REG_ADDR_DHM1_BACK_AIR_HIGH_PWM                  0X4037//回风高风量PWM值	
#define REG_ADDR_DHM1_NET_CHANGE_PERIOD                  0X4038//粗效过滤网更换周期	
#define REG_ADDR_DHM1_NET_USED_TIME                      0X4039//粗效过滤网使用时间 
#define REG_ADDR_DHM1_FAN_DIR_CHANGE                     0X403A//风机互换功能
#define REG_ADDR_DHM1_IN_FAN_STATUS                      0X403B//进风风速状态值
#define REG_ADDR_DHM1_OUT_FAN_STATUS                     0X403C //出风风速状态值
#define REG_ADDR_DHM1_IN_FAN_PWM                         0X403D//进风电机PWM值
#define REG_ADDR_DHM1_IN_FAN_SPEED                       0X403E// 进风电机转速
#define REG_ADDR_DHM1_OUT_FAN_PWM                        0X403F//出风电机PWM值
#define REG_ADDR_DHM1_OUT_FAN_SPEED                      0X4040 //出风电机转速

#define REG_ADDR_DHM2_ONLINE_STATUS                      0x4100//在线状态
#define REG_ADDR_DHM2_DEVICE_TYPE                        0x4101//设备类型
#define REG_ADDR_DHM2_VERSION                            0x4102//版本号
#define REG_ADDR_DHM2_HARDSIGN                           0x4103//硬件标识
#define REG_ADDR_DHM2_POWER                              0x4104//除湿模块开关机
#define REG_ADDR_DHM2_RUN_STATUS                         0x4105//除湿模块运行状态
#define REG_ADDR_DHM2_SET_HUM                            0x4106//设定湿度 
#define REG_ADDR_DHM2_SET_FANSPEED                       0x4107//设定风速 
#define REG_ADDR_DHM2_RUN_FANSPEED                       0x4108//运行风速 
#define REG_ADDR_DHM2_SET_WARM_TEMP                      0x4109//设定制热目标温度 
#define REG_ADDR_DHM2_SET_CLOD_TEMP                      0x410A//设定制冷目标温度
#define REG_ADDR_DHM2_SET_BACK_HOT_TEMP                  0x410B//设定回热目标温度
#define REG_ADDR_DHM2_SYSTEM_TEMP                        0x410C//系统温度 
#define REG_ADDR_DHM2_SYSTEM_HUM                         0x410D//系统湿度
#define REG_ADDR_DHM2_IN_WIND_TEMP                       0x410E//进风温度
#define REG_ADDR_DHM2_IN_WIND_HUM                        0x410F //进风湿度
#define REG_ADDR_DHM2_OUT_WIND_TEMP                      0x4110//出风温度
#define REG_ADDR_DHM2_OUT_WIND_HUM                       0x4111// 出风湿度
#define REG_ADDR_DHM2_BACK_AIR_TEMP                      0x4112//室内温度
#define REG_ADDR_DHM2_BACK_AIR_HUM                       0x4113 //室内湿度
#define REG_ADDR_DHM2_BACK_AIR_CO2                       0x4114 //室内CO2
#define REG_ADDR_DHM2_BACK_AIR_PM25                      0x4115 //室内PM2.5
#define REG_ADDR_DHM2_RESEVER4_TEMP                      0x4116 //预留4温度
#define REG_ADDR_DHM2_RESEVER4_HUM                       0x4117 //预留4湿度
#define REG_ADDR_DHM2_RESEVER5_TEMP                      0x4118//预留5温度 
#define REG_ADDR_DHM2_RESEVER5_HUM                       0x4119//预留5湿度
#define REG_ADDR_DHM2_PTC_TEMP                           0x411A//PTC温度
#define REG_ADDR_DHM2_TEMP_DIFF                          0x411B//温度带宽 
#define REG_ADDR_DHM2_HUM_DIFF                           0x411C//湿度带宽
#define REG_ADDR_DHM2_PTC_PROTECT_DIFF                   0x411D//PTC保护带宽
#define REG_ADDR_DHM2_PTC_LIMIT_TEMP                     0x411E //PTC温度限制
#define REG_ADDR_DHM2_HOT_VAVLE_OUT                      0x411F//电热阀输出
#define REG_ADDR_DHM2_LIFT_PUMP_OUT                      0x4120// 提水泵输出
#define REG_ADDR_DHM2_PTC_OUT                            0x4121//PTC输出
#define REG_ADDR_DHM2_MAIN_OUT                           0x4122 //输配接口输出
#define REG_ADDR_DHM2_HOT_ASSIST                         0x4123 //辅助制热
#define REG_ADDR_DHM2_ADJUST_IN_WIND_TEMP                0x4124 //进风校准温度
#define REG_ADDR_DHM2_ADJUST_IN_WIND_HUM                 0x4125 //进风校准湿度
#define REG_ADDR_DHM2_ADJUST_OUT_WIND_TEMP               0x4126 //出风校准温度
#define REG_ADDR_DHM2_ADJUST_OUT_WIND_HUM                0x4127//出风校准湿度 
#define REG_ADDR_DHM2_ADJUST_BACK_WIND_TEMP              0x4128//室内校准温度
#define REG_ADDR_DHM2_ADJUST_BACK_WIND_HUM               0x4129//室内校准湿度
#define REG_ADDR_DHM2_ADJUST_BACK_WIND_CO2               0x412A//室内校准CO2 
#define REG_ADDR_DHM2_ADJUST_BACK_WIND_PM25              0x412B//室内校准PM2.5
#define REG_ADDR_DHM2_ADJUST_4_TEMP                      0x412C//校准4温度
#define REG_ADDR_DHM2_ADJUST_4_HUM                       0x412D //校准4湿度
#define REG_ADDR_DHM2_ADJUST_5_TEMP                      0x412E//校准5温度
#define REG_ADDR_DHM2_ADJUST_5_HUM                       0x412F// 校准5湿度
#define REG_ADDR_DHM2_DEVICE_ERROR                       0x4130//设备故障字
#define REG_ADDR_DHM2_DEVICE_RESET                       0x4131 //故障复位字
#define REG_ADDR_DHM2_NEW_AIR_LOW_PWM                    0x4132 //新风低风量PWM值
#define REG_ADDR_DHM2_NEW_AIR_MID_PWM                    0x4133 //新风中风量PWM值	
#define REG_ADDR_DHM2_NEW_AIR_HIGH_PWM                   0x4134 //新风高风量PWM值
#define REG_ADDR_DHM2_BACK_AIR_LOW_PWM                   0x4135 //回风低风量PWM值
#define REG_ADDR_DHM2_BACK_AIR_MID_PWM                   0x4136//回风中风量PWM值 
#define REG_ADDR_DHM2_BACK_AIR_HIGH_PWM                  0x4137//回风高风量PWM值	
#define REG_ADDR_DHM2_NET_CHANGE_PERIOD                  0x4138//粗效过滤网更换周期	
#define REG_ADDR_DHM2_NET_USED_TIME                      0x4139//粗效过滤网使用时间 
#define REG_ADDR_DHM2_FAN_DIR_CHANGE                     0x413A//风机互换功能
#define REG_ADDR_DHM2_IN_FAN_STATUS                      0x413B//进风风速状态值
#define REG_ADDR_DHM2_OUT_FAN_STATUS                     0x413C //出风风速状态值
#define REG_ADDR_DHM2_IN_FAN_PWM                         0x413D//进风电机PWM值
#define REG_ADDR_DHM2_IN_FAN_SPEED                       0x413E// 进风电机转速
#define REG_ADDR_DHM2_OUT_FAN_PWM                        0x413F//出风电机PWM值
#define REG_ADDR_DHM2_OUT_FAN_SPEED                      0x4140 //出风电机转速

#define DP_ADDR_WRITE_DEVICE_ID                           0X1000//写设备ID


#define DP_ADDR_START                                     0x0100

/*房间温控器DP点地址*/ 
#define DP_ADDR_PAD_POWER                                 0X00//开关机
#define DP_ADDR_PAD_SET_COLD_TEMP                         0X01//制冷设定温度
#define DP_ADDR_PAD_SET_HEAT_TEMP                         0X02//制热设定温度
#define DP_ADDR_PAD_CHILD_LOCK                            0X03//童锁
#define DP_ADDR_PAD_SET_FAN                               0X04//设定风速
#define DP_ADDR_PAD_TWO_CNONTROL_MODE                     0X05//双末端运行模式
#define DP_ADDR_PAD_BIND_MESSAGE                          0X06//末端绑定信息
#define DP_ADDR_PAD_STATUS_MESSAGE                        0X07//末端信息
#define DP_ADDR_PAD_MEASURE_MESSAGE                       0X08//末端测量信息
#define DP_ADDR_PAD_ADV_MESSAGE                           0X09//高级信息
#define DP_ADDR_PAD_SYSTEM_MESSAGE                        0X0A//系统信息
#define DP_ADDR_PAD_SYSTEM_RTC                            0X0B//系统RTC信息
#define DP_ADDR_PAD_DEVICE_TYPE                           0X0D//设备类型

/*除湿模块DP点地址*/
#define DP_ADDR_DHM_START                                0X0200
#define DP_ADDR_DHM_POWER                                0X0200//除湿模块开关机
#define DP_ADDR_DHM_RUN_MODE                             0X0201//运行模式
#define DP_ADDR_DHM_SET_HUM                              0X0202//设定湿度
#define DP_ADDR_DHM_SET_SPEED                            0X0203//设定风速
#define DP_ADDR_DHM_RUN_SPEED                            0X0204//运行风速
#define DP_ADDR_DHM_SET_HOT_TEMP                         0X0205//设定制热目标温度
#define DP_ADDR_DHM_SET_COLD_TEMP                        0X0206//设定制冷目标温度
#define DP_ADDR_DHM_SET_BACK_HOT_TEMP                    0X0207//设定回热目标温度
#define DP_ADDR_DHM_REVERSE1                             0X0208//预留
#define DP_ADDR_DHM_REVERSE2                             0X0209//预留
#define DP_ADDR_DHM_LIST_SYSTEM_RTC                      0X020A//系统RTC
#define DP_ADDR_DHM_LIST_MODULE_MESSAGE                  0X020B//除湿模块信息
#define DP_ADDR_DHM_LIST_MODULE_MEASURE                  0X020C//除湿模块测量数据
#define DP_ADDR_DHM_LIST_SYSTEM_TEMP_HUM                 0X020D//系统测量温湿度
#define DP_ADDR_DHM_LIST_TEMP_HUM_DIFF                   0X020E//除湿模块温湿度死区
#define DP_ADDR_DHM_LIST_OUT_STATUS                      0X020F//除湿模块输出状态
#define DP_ADDR_DHM_LIST_MODULE_CONFIG                   0X0210//除湿模块设置
#define DP_ADDR_DHM_LIST_MODULE_FUN                      0X0211//除湿模块功能字
#define DP_ADDR_DHM_LIST_IEC5_CONGIG                     0X0212//IEC5新风设置信息
#define DP_ADDR_DHM_LIS_IEC5_MESSAGE                     0X0213//IEC5新风风机信息

#define DEVICE_TYPE                                      0x8522
#define DEVICE_TYPE_HC                                   0x8521//环控
#define DEVICE_TYPE_CC                                   0x8522//输配
#define DEVICE_TYPE_FAN                                  0x9521//风盘
#define DEVICE_TYPE_ROMM                                 0x9522//面板
#define DEVICE_TYPE_DHM                                  0x9523//除湿模块
#define DEVICE_VERSION                                   0x2101
//-----------------------------------------------------------------------------
uint16_t app_modbus_read_reg_data(uint16_t reg_addr);
bool app_modebus_write_reg_data(uint16_t reg_addr,uint16_t reg_detailes);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif