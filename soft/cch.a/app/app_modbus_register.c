//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: 应用task
//-----------------------------------------------------------------------------
uint16_t app_modbus_read_reg_data(uint16_t reg_addr)
{
    uint16_t reg_detailes = 0;
	uint8_t comm_port = 0;
    uint8_t virtualPort = PAD_NO_PHY_BIND;
	if((reg_addr >= 1) && (reg_addr <= (ARICOD_READ_ONLY_REG_NUM)))
    {
        APP_pull_aricod_message(reg_addr,&reg_detailes);
    }
    else if((reg_addr >= 5001) && (reg_addr <= (5000+ARICOD_READ_WRITE_REG_NUM)))
    {
        APP_pull_aricod_message(reg_addr,&reg_detailes);
    }
    else if((reg_addr == MRegaddr_SlaveStatusW) || (reg_addr == MRegaddr_RequestNumber))
    {
        app_updataBackup_readRegister(reg_addr,&reg_detailes);
    }
	else 
	{
		switch(reg_addr)
		{
			case MRegaddr_ProductType:
			{
				reg_detailes = DEVICE_TYPE;
				break;
			}
			case MRegaddr_SoftVersion:
			{
				reg_detailes = DEVICE_VERSION;
				break;
			}
			case  MRegaddr_SecondAndWeek:
			{
				realTime_t* currentRtc;
				uint8_t buff[2];
				currentRtc = app_real_time_pull_rtc();
				buff[0] = currentRtc->second;
				buff[1] = currentRtc->week;
				reg_detailes = pbc_arrayToInt16u_bigEndian(&buff[0]);
				break;
			}
			case  MRegaddr_HourAndMinute:
			{
				realTime_t* currentRtc;
				uint8_t buff[2];
				currentRtc = app_real_time_pull_rtc();
				buff[0] = currentRtc->hour;
				buff[1] = currentRtc->minute;
				reg_detailes = pbc_arrayToInt16u_bigEndian(&buff[0]);
				break;
			}
			case  MRegaddr_MonthAndDay:
			{
				realTime_t* currentRtc;
				uint8_t buff[2];
				currentRtc = app_real_time_pull_rtc();
				buff[0] = currentRtc->month;
				buff[1] = currentRtc->day;
				reg_detailes = pbc_arrayToInt16u_bigEndian(&buff[0]);
				break;
			}
			case  MRegaddr_Year:
			{
				realTime_t* currentRtc;
				currentRtc = app_real_time_pull_rtc();          
				reg_detailes = (currentRtc->year + 2000);
				break;
			}
            case MRegaddr_SalveAddr: 
            {
                app_general_push_adress485(reg_detailes);
                break;
            }
            case MRegaddr_SalveBaudrate: 
            {
                app_general_push_baudrate(reg_detailes);
                break;
            }
            case MRegaddr_SalveParityBit: 
            {
                app_general_push_checkbit(reg_detailes);
                break;
            }        
			case REG_ADDR_MASTER_ERROR_WORD:
			{//系统主机故障字
				reg_detailes = app_general_pull_master_error_word();
				break;
			}
			case REG_ADDR_AIRCOD_ENERGY_NEED:
			{//旁通输出
				reg_detailes = app_general_pull_anergy_need();
				break;
			}
			case REG_ADDR_SYSTEM_POWER:
			{//系统开关机
				reg_detailes = app_general_pull_power_status();
				break;
			}
			case REG_ADDR_SYSTEM_RUN_MODE:
			{//系统运行模式
				reg_detailes = app_general_pull_aircod_mode();
				break;
			}
			case REG_ADDR_FAN_SET_HUM:
			{//通风制冷/除湿模式设定相对湿度
				reg_detailes = app_general_pull_aircod_humidity();
				break;
			}
			case REG_ADDR_FAN_SET_SPEED:
			{ //通风设定风速 
				reg_detailes = app_general_pull_aircod_fanSpeed();
				break;
			}
			case REG_ADDR_MASTER_SET_COLD_WATER_TEMP:
			{//主机制冷模式设定水温
				reg_detailes = app_general_pull_set_cold_water_temp();
				break;
			}
			case REG_ADDR_MASTER_SET_HEAT_WATER_TEMP:
			{//主机制热模式设定水温
				reg_detailes = app_general_pull_set_heat_water_temp();
				break;
			}
			case REG_ADDR_WATER_MACHINE_FRE:
			{//水机压缩机频率
				reg_detailes = app_general_pull_water_machine_fre();
				break;
			}
			case REG_ADDR_MASTER_SUPPLY_TEMP:
			{//主机供水温度
				reg_detailes = app_general_pull_master_supply_temp();
				break;
			}
			case REG_ADDR_YESTERDAY_POWER_USED:
			{//昨日能耗
				//reg_detailes = app_general_pull_adjust_outdoor_co2();
				break;
			}
			case REG_ADDR_TODAY_POWER_USED:
			{//今日能耗
				//reg_detailes = app_general_pull_adjust_outdoor_pm25();
				break;
			}
            case REG_ADDR_SYSTEM_STATSU:
			{//主机状态字
				reg_detailes = app_general_pull_system_status_word();
				break;
			}
			case REG_ADDR_LEW_PROTECT_STATSU:
			{//露点保护状态
				reg_detailes = app_general_pull_system_lew_temp_status();
				break;
			}
			case REG_ADDR_PAD_OUTPUT_STATSU:
			{//末端输出状态
				reg_detailes = app_general_pull_pad_output_status();
				break;
			}
			case REG_ADDR_FIIST_SUPPLY_WATER_TEMP:
			{//输配一次侧供水温度
				reg_detailes = app_pull_first_in_water_temp();
				break;
			}
			case REG_ADDR_FIIST_BACK_WATER_TEMP:
			{//输配一次侧回水温度
				reg_detailes = app_pull_first_back_water_temp();
				break;
			}
			case REG_ADDR_SET_MIXWATER_COLD_TEMP:
			{//混水制冷设定温度
				reg_detailes = app_general_pull_set_mixwater_cold_temp();
				break;
			}
			case REG_ADDR_SET_MIXWATER_HEAT_TEMP:
			{//混水制热设定温度
				reg_detailes = app_general_pull_set_mixwater_heat_temp();
				break;
			}
			case REG_ADDR_MIXWATER_BACKWATER_TEMP:
			{//输配二次侧回水温度
				reg_detailes = app_pull_back_water_temp();
				break;
			}
			case REG_ADDR_MIXWATER_TEMP:
			{//输配混水温度
				reg_detailes = app_pull_mix_water_temp();
				break;
			}
			case REG_ADDR_OUTPUT_PUMP:
			{//输配水泵状态
				reg_detailes = app_general_pull_pump_output();
				break;
			}
			case REG_ADDR_OUTPUT_THREE_VAVLE:
			{//输配三通阀门输出状态
				reg_detailes = app_general_pull_three_vavle_output();
				break;
			}
			case REG_ADDR_MIXWATER_LOW_TEMP_PROTECT:
			{//输配防冻保护
				reg_detailes = app_general_pull_mix_freeze_protect();
				break;
			}
            case REG_ADRESS_MAIN_CONTROL_METHOD:
            {//主控策略
                reg_detailes = app_general_pull_main_control_method();
                break;
            }
			case REG_ADRESS_LEW_STATUS_OPEN_DIFF:
            {//露点状态上限(开启)
                reg_detailes = app_general_pull_lew_status_open_status();
                break;
            }
			case REG_ADRESS_LEW_STATUS_CLOSE_DIFF:
            {//露点状态下限(关闭)
                reg_detailes = app_general_pull_lew_status_close_status();
                break;
            } 			
            case REG_ADRESS_DEBUG_ENABLE:
            {//调试使能
                reg_detailes = app_general_pull_debug_enable();
				break;
            }
			case REG_ADRESS_REMOTE_CONTROL:
			{//远程控制
				reg_detailes = app_general_pull_remote_control();
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY1:
			{//远程继电器1
				reg_detailes = app_general_pull_remote_relay(0);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY2:
			{//远程继电器2
				reg_detailes = app_general_pull_remote_relay(1);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY3:
			{//远程继电器3
				reg_detailes = app_general_pull_remote_relay(2);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY4:
			{//远程继电器4
				reg_detailes = app_general_pull_remote_relay(3);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY5:
			{//远程继电器5
				reg_detailes = app_general_pull_remote_relay(4);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY6:
			{//远程继电器6
				reg_detailes = app_general_pull_remote_relay(5);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY7:
			{//远程继电器7
				reg_detailes = app_general_pull_remote_relay(6);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY8:
			{//远程继电器8
				reg_detailes = app_general_pull_remote_relay(7);
				break;
			}
			case REG_ADRESS_REMOTE_RELAY9:
			{//远程继电器9
				reg_detailes = app_general_pull_remote_relay(8);
				break;
			}
			case REG_ADRESS_REMOTE_RELAY10:
			{
				reg_detailes = app_general_pull_remote_relay(9);
				break;
			}
			case REG_ADRESS_REMOTE_RELAY11:
			{
				reg_detailes = app_general_pull_remote_relay(10);
				break;
			}	
			case REG_ADRESS_REMOTE_PUMP:
			{//远程水泵
				reg_detailes = app_general_pull_remote_pump();
				break;
			}
			case REG_ADRESS_REMOTE_THREEVAVLE:
			{//远程三通阀
				reg_detailes = app_general_pull_remote_threeVavle();
				break;
			}
			case REG_ADRESS_REMOTE_VAVLEDUTY:
			{//远程三通阀开度
				reg_detailes = app_general_pull_remote_degree();
				break;
			}
			case REG_ADRESS_REMOTE_BY_PASS:
			{//远程旁通
				reg_detailes = app_general_pull_remote_bypass();
				break;
			}	
			case REG_ADRESS_CC_DEVICE_NUM:
			{//输配数量
				//reg_detailes = app_general_pull_remote_bypass();
				break;
			}	
			case REG_ADRESS_CC_DEVICE_SEL:
			{//当前输配片选
				//reg_detailes = app_general_pull_remote_bypass();
				break;
			}	
			case REG_ADRESS_CC_DEVICE_MASTER:
			{//主站选择
				//reg_detailes = app_general_pull_remote_bypass();
				break;
			}	 
			case REG_ADRESS_HARDWARESIGN:
			{//输配中心硬件标识
				reg_detailes = HARDWARE_AIO5;
				break;
			}
			case REG_ADDR_PAD1_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD1_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD1_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD1_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD1_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD1_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD1_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD1_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD1_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD1_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD1_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD1_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD1_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD1_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD1_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD1_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD1_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD1_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD1_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD1_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD1_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD1_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD1_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD1_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD1_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD1_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD1_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD1_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD1_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD1_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD1_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD1_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD1_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD1_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD1_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD1_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD1_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD1_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD1_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD1_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD1_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD1_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD1_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD1_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD1_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD1_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD2_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD2_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD2_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD2_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD2_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD2_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD2_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD2_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD2_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD2_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD2_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD2_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD2_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD2_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD2_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD2_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD2_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD2_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD2_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD2_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD2_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD2_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD2_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD2_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD2_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD2_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD2_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD2_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD2_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD2_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD2_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD2_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD2_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD2_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD2_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD2_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD3_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD3_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD3_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD3_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD3_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD3_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD3_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD3_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD3_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD3_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD3_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD3_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD3_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD3_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD3_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD3_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD3_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD3_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD3_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD3_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD3_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD3_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD3_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD3_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD3_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD3_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD3_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD3_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD3_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD3_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD3_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD3_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD3_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD3_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD3_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD3_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD4_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD4_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD4_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD4_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD4_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD4_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD4_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD4_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD4_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD4_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD4_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD4_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD4_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD4_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD4_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD4_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD4_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD4_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD4_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD4_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD4_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD4_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD4_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD4_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD4_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD4_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD4_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD4_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD4_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD4_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD4_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD4_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD4_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD4_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD4_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD4_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD5_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD5_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD5_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD5_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD5_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD5_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD5_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD5_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD5_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD5_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD5_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD5_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD5_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD5_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD5_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD5_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD5_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD5_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD5_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD5_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD5_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD5_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD5_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD5_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD5_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD5_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD5_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD5_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD5_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD5_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD5_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD5_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD5_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD5_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD5_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD5_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD6_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD6_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD6_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD6_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD6_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD6_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD6_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD6_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD6_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD6_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD6_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD6_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD6_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD6_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD6_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD6_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD6_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD6_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD6_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD6_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD6_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD6_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD6_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD6_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD6_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD6_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD6_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD6_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD6_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD6_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD6_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD6_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD6_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD6_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD6_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD6_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD7_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD7_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD7_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD7_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD7_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD7_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD7_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD7_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD7_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD7_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD7_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD7_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD7_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD7_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD7_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD7_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD7_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD7_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD7_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD7_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD7_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD7_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD7_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD7_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD7_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD7_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD7_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD7_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD7_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD7_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD7_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD7_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD7_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD7_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD7_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD7_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD8_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD8_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD8_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD8_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD8_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD8_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD8_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD8_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD8_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD8_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD8_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD8_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD8_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD8_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD8_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD8_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD8_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD8_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD8_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD8_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD8_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD8_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD8_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD8_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD8_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD8_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD8_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD8_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD8_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD8_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD8_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD8_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD8_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD8_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD8_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD8_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD9_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD9_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD9_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD9_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD9_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD9_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD9_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD9_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD9_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD9_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD9_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD9_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD9_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD9_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD9_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD9_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD9_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD9_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD9_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD9_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD9_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD9_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD9_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD9_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD9_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD9_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD9_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD9_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD9_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD9_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD9_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD9_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD9_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD9_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD9_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD9_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD10_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD10_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD10_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD10_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD10_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD10_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD10_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD10_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD10_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD10_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD10_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD10_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD10_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD10_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD10_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD10_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD10_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD10_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD10_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD10_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD10_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD10_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD10_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD10_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD10_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD10_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD10_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD10_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD10_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD10_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD10_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD10_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD10_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD10_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD10_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD10_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD11_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD11_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD11_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD11_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD11_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD11_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD11_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD11_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD11_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD11_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD11_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD11_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD11_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD11_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD11_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD11_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD11_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD11_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD11_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD11_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD11_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD11_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD11_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD11_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD11_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD11_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD11_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD11_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD11_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD11_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD11_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD11_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD11_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD11_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD11_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD11_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD11_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD11_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD11_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD11_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD11_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD11_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD11_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD11_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD11_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}	
			case REG_ADDR_PAD11_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}

			case REG_ADDR_DHM1_ONLINE_STATUS:
			{//在线状态			
				reg_detailes = app_general_pull_dhm_id_use_message((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_DEVICE_TYPE:
			{//设备类型
				comm_port = app_general_pull_dhm_use_port((reg_addr-REG_ADDR_DHM_START)/256);
				reg_detailes = app_general_pull_devive_type(comm_port);
				break;
			}
			case REG_ADDR_DHM1_VERSION:
			{//版本号
				comm_port = app_general_pull_dhm_use_port((reg_addr-REG_ADDR_DHM_START)/256);
				reg_detailes = app_general_pull_pad_version(comm_port);
				break;
			}
			case REG_ADDR_DHM1_HARDSIGN:
			{//硬件标识
				comm_port = app_general_pull_dhm_use_port((reg_addr-REG_ADDR_DHM_START)/256);
				reg_detailes = app_general_pull_pad_hardware_sign(comm_port);
				break;
			}
			case REG_ADDR_DHM1_POWER:
			{//除湿模块开关机
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_RUN_STATUS:
			{//除湿模块运行状态
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_SET_HUM:
			{//设定湿度
				reg_detailes = app_general_pull_dhm_aircod_humidity((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_SET_FANSPEED:
			{//设定风速
				reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}	
			case REG_ADDR_DHM1_RUN_FANSPEED:
			{//运行风速
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}		
			case REG_ADDR_DHM1_SET_WARM_TEMP:
			{//设定制热目标温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_SET_CLOD_TEMP:
			{//设定制冷目标温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_SET_BACK_HOT_TEMP:
			{//设定回热目标温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_SYSTEM_TEMP:
			{//系统温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_SYSTEM_HUM:
			{//系统湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_IN_WIND_TEMP:
			{//进风温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_IN_WIND_HUM:
			{//进风湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}	
			case REG_ADDR_DHM1_OUT_WIND_TEMP:
			{//出风温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_OUT_WIND_HUM:
			{//出风湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_BACK_AIR_TEMP:
			{//室内温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_BACK_AIR_HUM:
			{//室内湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_BACK_AIR_CO2:
			{//室内CO2
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_BACK_AIR_PM25:
			{//室内PM2.5
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_RESEVER4_TEMP:
			{//预留4温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_RESEVER4_HUM:
			{//预留4湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_RESEVER5_TEMP:
			{//预留5温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			} 
			case REG_ADDR_DHM1_RESEVER5_HUM:
			{//预留5湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_PTC_TEMP:
			{//PTC温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_TEMP_DIFF:
			{//温度带宽
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_HUM_DIFF:
			{//湿度带宽
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_PTC_PROTECT_DIFF:
			{//PTC保护带宽
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_PTC_LIMIT_TEMP:
			{//PTC温度限制
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_HOT_VAVLE_OUT:
			{//电热阀输出
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_LIFT_PUMP_OUT:
			{//提水泵输出
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_PTC_OUT:
			{//PTC输出
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_MAIN_OUT:
			{//输配接口输出
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_HOT_ASSIST:
			{//辅助制热
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_IN_WIND_TEMP:
			{//进风校准温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_IN_WIND_HUM:
			{//进风校准湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_OUT_WIND_TEMP:
			{//出风校准温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_OUT_WIND_HUM:
			{//出风校准湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_BACK_WIND_TEMP:
			{//室内校准温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			} 
			case REG_ADDR_DHM1_ADJUST_BACK_WIND_HUM:
			{//室内校准湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_BACK_WIND_CO2:
			{//室内校准CO2
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_BACK_WIND_PM25:
			{//室内校准PM2.5
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_4_TEMP:
			{//校准4温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_4_HUM:
			{//校准4湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_5_TEMP:
			{//校准5温度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_5_HUM:
			{//校准5湿度
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_DEVICE_ERROR:
			{//设备故障字
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_DEVICE_RESET:
			{//故障复位字
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_NEW_AIR_LOW_PWM:
			{//新风低风量PWM值
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_NEW_AIR_MID_PWM:
			{//新风中风量PWM值
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_NEW_AIR_HIGH_PWM:
			{//新风高风量PWM值
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_BACK_AIR_LOW_PWM:
			{//回风低风量PWM值
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_BACK_AIR_MID_PWM:
			{//回风中风量PWM值
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_BACK_AIR_HIGH_PWM:
			{//回风高风量PWM值
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_NET_CHANGE_PERIOD:
			{//粗效过滤网更换周期
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_NET_USED_TIME:
			{//粗效过滤网使用时间
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			} 
			case REG_ADDR_DHM1_FAN_DIR_CHANGE:
			{//风机互换功能
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_IN_FAN_STATUS:
			{//进风风速状态值
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_OUT_FAN_STATUS:
			{//出风风速状态值
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_IN_FAN_PWM:
			{//进风电机PWM值
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_IN_FAN_SPEED:
			{//进风电机转速
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_OUT_FAN_PWM:
			{//出风电机PWM值
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			case REG_ADDR_DHM1_OUT_FAN_SPEED:
			{//出风电机转速
				//reg_detailes = app_general_pull_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256);
				break;
			}
			default:
			{
				reg_detailes = 0;
				break;
			}
		}
	}
    
    return reg_detailes;
}

bool app_modebus_write_reg_data(uint16_t reg_addr,uint16_t reg_detailes)
{
    uint8_t virtualPort = PAD_NO_PHY_BIND;
	if((reg_addr >= MRegaddr_StrUpdateWord) && (reg_addr <= MRegaddr_Message63))
    {
        app_updataBackup_writeRegister(reg_addr,reg_detailes);
    }
	else
	{
		switch(reg_addr)
		{
			case  MRegaddr_SecondAndWeek:
			{
				realTime_t* currentRtc;
				currentRtc = app_real_time_pull_rtc();
				uint8_t buff[2];
				pbc_int16uToArray_bigEndian(reg_detailes,&buff[0]);
				currentRtc->second = buff[0];
				currentRtc->week = buff[1];
				app_push_once_save_write_rtc();
				break;
			}
			case  MRegaddr_HourAndMinute:
			{
				realTime_t* currentRtc;
				currentRtc = app_real_time_pull_rtc();
				uint8_t buff[2];
				pbc_int16uToArray_bigEndian(reg_detailes,&buff[0]);
				currentRtc->hour = buff[0];
				currentRtc->minute = buff[1];
				app_push_once_save_write_rtc();
				break;
			}
			case  MRegaddr_MonthAndDay:
			{
				realTime_t* currentRtc;
				currentRtc = app_real_time_pull_rtc();
				uint8_t buff[2];
				pbc_int16uToArray_bigEndian(reg_detailes,&buff[0]);
				currentRtc->month = buff[0];
				currentRtc->day = buff[1];
				app_push_once_save_write_rtc();
				break;
			}
			case  MRegaddr_Year:
			{
				realTime_t* currentRtc;
				currentRtc = app_real_time_pull_rtc();
				currentRtc->year = (reg_detailes-2000);
				app_push_once_save_write_rtc();
				break;
			}
		    case MRegaddr_SalveAddr: 
            {
                app_general_push_adress485(reg_detailes);
                break;
            }
            case MRegaddr_SalveBaudrate: 
            {
                app_general_push_baudrate(reg_detailes);
                break;
            }
            case MRegaddr_SalveParityBit: 
            {
                app_general_push_checkbit(reg_detailes);
                break;
            }        
			case MRegaddr_Restoragefac:
			{//恢复出厂设置
			  //  app_general_push_master_error_word(reg_detailes);
			  	if(reg_detailes == 0x3589)
				{
					RestoreFactoryStorage();
				}
				break;
			}
			case REG_ADDR_AIRCOD_ENERGY_NEED:
			{//旁通输出
				app_general_push_anergy_need(reg_detailes);
				break;
			}
			case REG_ADDR_SYSTEM_POWER:
			{//系统开关机
				app_general_push_power_status(reg_detailes);
				break;
			}
			case REG_ADDR_SYSTEM_RUN_MODE:
			{//系统运行模式
				app_general_push_aircod_mode((AirRunMode_Def)reg_detailes);
				break;
			}
			case REG_ADDR_FAN_SET_HUM:
			{//通风制冷/除湿模式设定相对湿度
				app_general_push_aircod_humidity(reg_detailes);
				break;
			}
			case REG_ADDR_FAN_SET_SPEED:
			{//通风设定风速 
				app_general_push_aircod_fanSpeed((NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_MASTER_SET_COLD_WATER_TEMP:
			{//主机制冷模式设定水温
				app_general_push_set_cold_water_temp(reg_detailes);
				break;
			}
			case REG_ADDR_MASTER_SET_HEAT_WATER_TEMP:
			{//主机制热模式设定水温
				app_general_push_set_heat_water_temp(reg_detailes);
				break;
			}
			case REG_ADDR_SET_MIXWATER_COLD_TEMP:
			{//混水制冷设定温度
				app_general_push_set_mixwater_cold_temp(reg_detailes);
				break;
			}
			case REG_ADDR_SET_MIXWATER_HEAT_TEMP:
			{//混水制热设定温度
				app_general_push_set_mixwater_heat_temp(reg_detailes);
				break;
			}
			case REG_ADDR_MIXWATER_LOW_TEMP_PROTECT:
			{//输配防冻保护
				app_general_push_mix_freeze_protect(reg_detailes);
				break;
			}
            case REG_ADRESS_MAIN_CONTROL_METHOD:
            {//主控策略
                app_general_push_main_control_method(reg_detailes);
                break;
            }
			case REG_ADRESS_LEW_STATUS_OPEN_DIFF:
            {//露点状态上限开启
                app_general_push_lew_status_open_status(reg_detailes);
                break;
            }
			case REG_ADRESS_LEW_STATUS_CLOSE_DIFF:
            {//露点状态下限关闭
                app_general_push_lew_status_close_status(reg_detailes);
                break;
            }
			case REG_ADRESS_CC_RESET:
            {//输配软件复位
                app_general_push_cc_reset(reg_detailes);
                break;
            }
			case REG_ADRESS_HC_RESET:
            {//环控软件复位
                app_general_push_hc_reset(reg_detailes);
                break;
            }
			case REG_ADRESS_DEBUG_ENABLE:
            {//调试使能
				app_general_push_debug_enable(reg_detailes);
				break;   
            }
			case REG_ADRESS_REMOTE_CONTROL:
			{//远程控制
				app_general_push_remote_control(reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY1:
			{//远程继电器1
				app_general_push_remote_relay(0,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY2:
			{//远程继电器2
				app_general_push_remote_relay(1,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY3:
			{//远程继电器3
				app_general_push_remote_relay(2,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY4:
			{//远程继电器4
				app_general_push_remote_relay(3,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY5:
			{//远程继电器5
				app_general_push_remote_relay(4,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY6:
			{//远程继电器6
				app_general_push_remote_relay(5,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY7:
			{//远程继电器7
				app_general_push_remote_relay(6,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY8:
			{//远程继电器8
				app_general_push_remote_relay(7,reg_detailes);
				break;
			}
			case REG_ADRESS_REMOTE_RELAY9:
			{//远程继电器9
				app_general_push_remote_relay(8,reg_detailes);
				break;
			}
			case REG_ADRESS_REMOTE_RELAY10:
			{//远程继电器10
				app_general_push_remote_relay(9,reg_detailes);
				break;
			}
			case REG_ADRESS_REMOTE_RELAY11:
			{//远程继电器11
				app_general_push_remote_relay(10,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_PUMP:
			{//远程水泵
				app_general_push_remote_pump(reg_detailes);
				break;
			}
			case REG_ADRESS_REMOTE_THREEVAVLE:
			{//远程三通阀
				app_general_push_remote_threeVavle(reg_detailes);
				break;
			}
			case REG_ADRESS_REMOTE_VAVLEDUTY:
			{
				app_general_push_remote_degree(reg_detailes);
				break;
			}
			case REG_ADRESS_REMOTE_BY_PASS:
			{//远程旁通
				app_general_push_remote_bypass(reg_detailes);
				break;
			}
			case REG_ADDR_PAD1_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD1_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD1_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD1_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD1_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD1_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD1_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD1_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD1_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD1_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD1_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD1_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD1_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD1_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD1_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD1_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD1_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD1_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD1_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD1_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD1_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD1_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD1_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD1_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD1_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD1_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD1_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD1_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD1_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD1_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD2_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD2_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD2_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD2_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD2_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD2_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD2_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD2_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD2_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD2_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD2_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD2_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD2_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD2_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD2_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD2_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD2_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD2_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD2_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD2_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD2_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD2_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD2_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD2_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD2_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD2_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD2_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD2_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD2_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD2_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD3_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD3_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD3_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD3_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD3_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD3_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD3_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD3_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD3_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD3_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD3_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD3_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD3_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD3_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD3_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD3_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD3_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD3_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD3_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD3_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD3_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD3_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD3_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD3_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD3_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD3_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD3_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD3_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD3_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD3_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD3_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD4_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD4_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD4_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD4_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD4_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD4_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD4_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD4_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD4_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD4_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD4_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD4_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD4_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD4_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD4_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD4_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD4_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD4_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD4_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD4_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD4_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD4_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD4_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD4_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD4_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD4_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD4_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD4_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD4_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD4_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD4_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD5_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD5_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD5_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD5_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD5_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD5_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD5_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD5_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD5_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD5_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD5_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD5_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD5_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD5_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD5_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD5_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD5_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD5_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD5_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD5_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD5_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD5_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD5_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD5_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD5_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD5_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD5_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD5_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD5_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD5_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD5_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD6_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD6_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD6_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD6_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD6_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD6_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD6_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD6_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD6_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD6_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD6_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD6_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD6_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD6_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD6_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD6_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD6_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD6_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD6_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD6_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD6_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD6_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD6_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD6_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD6_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD6_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD6_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD6_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD6_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD6_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD6_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD7_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD7_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD7_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD7_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD7_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD7_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD7_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD7_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD7_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD7_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD7_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD7_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD7_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD7_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD7_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD7_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD7_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD7_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD7_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD7_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD7_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD7_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD7_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD7_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD7_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD7_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD7_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD7_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD7_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD7_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD7_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD8_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD8_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD8_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD8_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD8_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD8_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD8_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD8_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD8_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD8_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD8_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD8_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD8_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD8_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD8_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD8_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD8_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD8_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD8_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD8_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD8_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD8_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD8_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD8_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD8_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD8_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD8_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD8_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD8_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD8_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD8_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD9_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD9_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD9_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD9_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD9_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD9_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD9_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD9_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD9_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD9_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD9_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD9_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD9_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD9_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD9_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD9_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD9_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD9_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD9_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD9_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD9_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD9_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD9_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD9_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD9_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD9_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD9_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD9_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD9_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD9_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD9_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD10_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD10_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD10_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD10_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD10_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD10_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD10_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD10_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD10_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD10_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD10_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD10_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD10_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD10_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD10_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD10_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD10_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD10_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD10_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD10_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD10_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD10_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD10_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD10_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD10_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD10_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD10_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD10_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD10_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD11_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD11_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD11_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD11_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD11_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD11_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD11_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD11_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD11_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD11_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD11_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD11_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD11_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD11_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD11_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD11_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD11_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD11_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD11_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD11_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD11_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD11_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD11_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD11_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD11_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD11_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD11_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD11_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD11_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			/*除湿模块*/

			case REG_ADDR_DHM1_POWER:
			{//除湿模块开关机
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_RUN_STATUS:
			{//除湿模块运行状态
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_SET_HUM:
			{//设定湿度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_SET_FANSPEED:
			{//设定风速
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}		
			case REG_ADDR_DHM1_SET_WARM_TEMP:
			{//设定制热目标温度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_SET_CLOD_TEMP:
			{//设定制冷目标温度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_SET_BACK_HOT_TEMP:
			{//设定回热目标温度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_SYSTEM_TEMP:
			{//系统温度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_SYSTEM_HUM:
			{//系统湿度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}		
			case REG_ADDR_DHM1_TEMP_DIFF:
			{//温度带宽
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_HUM_DIFF:
			{//湿度带宽
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_PTC_PROTECT_DIFF:
			{//PTC保护带宽
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_PTC_LIMIT_TEMP:
			{//PTC温度限制
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_HOT_ASSIST:
			{//辅助制热
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_IN_WIND_TEMP:
			{//进风校准温度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_IN_WIND_HUM:
			{//进风校准湿度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_OUT_WIND_TEMP:
			{//出风校准温度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_OUT_WIND_HUM:
			{//出风校准湿度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_BACK_WIND_TEMP:
			{//室内校准温度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			} 
			case REG_ADDR_DHM1_ADJUST_BACK_WIND_HUM:
			{//室内校准湿度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_BACK_WIND_CO2:
			{//室内校准CO2
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_BACK_WIND_PM25:
			{//室内校准PM2.5
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_4_TEMP:
			{//校准4温度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_4_HUM:
			{//校准4湿度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_5_TEMP:
			{//校准5温度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_ADJUST_5_HUM:
			{//校准5湿度
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_DEVICE_RESET:
			{//故障复位字
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_NEW_AIR_LOW_PWM:
			{//新风低风量PWM值
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_NEW_AIR_MID_PWM:
			{//新风中风量PWM值
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_NEW_AIR_HIGH_PWM:
			{//新风高风量PWM值
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_BACK_AIR_LOW_PWM:
			{//回风低风量PWM值
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_BACK_AIR_MID_PWM:
			{//回风中风量PWM值
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_BACK_AIR_HIGH_PWM:
			{//回风高风量PWM值
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_NET_CHANGE_PERIOD:
			{//粗效过滤网更换周期
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_DHM1_NET_USED_TIME:
			{//粗效过滤网使用时间
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			} 
			case REG_ADDR_DHM1_FAN_DIR_CHANGE:
			{//风机互换功能
				//app_general_push_dhm_fanSpeed((reg_addr-REG_ADDR_DHM_START)/256,(NewAirLevelSet_Def)reg_detailes);
				break;
			}
			default:
			{
				break;
			}
		}
	}
    return true;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++