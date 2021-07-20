//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//name: 应用task
//-----------------------------------------------------------------------------
uint16_t app_modbus_read_reg_data(uint16_t reg_addr,uint8_t in_src)
{
    uint16_t reg_detailes = 0;
    uint8_t virtualPort = PAD_NO_PHY_BIND;
	if((reg_addr >= 0x3A01) && (reg_addr <= (0x3A01+ARICOD_READ_ONLY_REG_NUM)))
    {
        APP_pull_aricod_message((reg_addr-0x3a01+1),&reg_detailes);
    }
    else if((reg_addr >= 0x3b01) && (reg_addr <= (0x3b01+ARICOD_READ_WRITE_REG_NUM)))
    {
        APP_pull_aricod_message((reg_addr-0x3b01+5001),&reg_detailes);
    }
    else if((reg_addr == MRegaddr_SlaveStatusW) || (reg_addr == MRegaddr_RequestNumber))
    {
        //app_updataBackup_readRegister(reg_addr,&reg_detailes);
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
			case MRegaddr_TEST_SYN_STATUS:
			{
				//reg_detailes = test_pull_syn_status();
				break;
			}
			case REG_ADDR_MASTER_ERROR_WORD:
			{//系统主机故障字
				reg_detailes = app_general_pull_master_error_word();
				break;
			}
			case REG_ADDR_AIRCOD_ENERGY_NEED:
			{//环控能需
				reg_detailes = app_general_pull_anergy_need();
				break;
			}
			case REG_ADDR_SYSTEM_POWER:
			{
				reg_detailes = app_general_pull_power_status();
				break;
			}
			case REG_ADDR_SYSTEM_RUN_MODE:
			{
				reg_detailes = app_general_pull_aircod_mode();
				break;
			}
			case REG_ADDR_FAN_SET_HUM:
			{
				reg_detailes = app_general_pull_aircod_humidity();
				break;
			}
			case REG_ADDR_FAN_SET_SPEED:
			{
				reg_detailes = app_general_pull_aircod_fanSpeed();
				break;
			}
			case REG_ADDR_SET_COLD_TEMP:
			{
				reg_detailes = app_general_pull_aircod_cold_temp();
				break;
			}
			case REG_ADDR_SET_HEAT_TEMP:
			{
				reg_detailes = app_general_pull_aircod_heat_temp();
				break;
			}
			case REG_ADDR_NEW_AIR_LOW_PWM:
			{
				reg_detailes = app_general_pull_new_air_pwm_low();
				break;
			}
			case REG_ADDR_NEW_AIR_MID_PWM:
			{
				reg_detailes = app_general_pull_new_air_pwm_mid();
				break;
			}
			case REG_ADDR_NEW_AIR_HIGH_PWM:
			{
				reg_detailes = app_general_pull_new_air_pwm_high();
				break;
			}
			case REG_ADDR_BACK_AIR_LOW_PWM:
			{
				reg_detailes = app_general_pull_back_air_pwm_low();
				break;
			}
			case REG_ADDR_BACK_AIR_MID_PWM:
			{
				reg_detailes = app_general_pull_back_air_pwm_mid();
				break;
			}
			case REG_ADDR_BACK_AIR_HIGH_PWM:
			{
				reg_detailes = app_general_pull_back_air_pwm_high();
				break;
			}
			case REG_ADDR_MASTER_SET_COLD_WATER_TEMP:
			{
				reg_detailes = app_general_pull_set_cold_water_temp();
				break;
			}
			case REG_ADDR_MASTER_SET_HEAT_WATER_TEMP:
			{
				reg_detailes = app_general_pull_set_heat_water_temp();
				break;
			}
			case REG_ADDR_MASTER_SET_LIVING_WATER_TEMP:
			{
				reg_detailes = app_general_pull_set_living_water_temp();
				break;
			}
			case REG_ADDR_MASTER_OUTDOOR_IN_FAN_TEMP:
			{
				reg_detailes = app_general_pull_outdoor_temp();
				break;
			}
			case REG_ADDR_MASTER_OUTDOOR_IN_FAN_HUM:
			{
				reg_detailes = app_general_pull_outdoor_hum();
				break;
			}
			case REG_ADDR_BEFORE_FU_TEMP:
			{
				reg_detailes = app_general_pull_before_fu_temp();
				break;
			}
			case REG_ADDR_BEFORE_FU_HUM:
			{
				reg_detailes = app_general_pull_before_fu_hum();
				break;
			}
			case REG_ADDR_AFTER_FU_TEMP:
			{
				reg_detailes = app_general_pull_after_fu_temp();
				break;
			}
			case REG_ADDR_AFTER_FU_HUM:
			{
				reg_detailes = app_general_pull_after_fu_hum();
				break;
			}
			case REG_ADDR_BACK_AIR_TEMP:
			{
				reg_detailes = app_general_pull_backair_temp();
				break;
			}
			case REG_ADDR_BACK_AIR_HUM:
			{
				reg_detailes = app_general_pull_backair_hum();
				break;
			}
			case REG_ADDR_EXHAST_AIR_TEMP:
			{
				reg_detailes = app_general_pull_exhastair_temp();
				break;
			}
			case REG_ADDR_EXHAST_AIR_HUM:
			{
				reg_detailes = app_general_pull_exhastair_hum();
				break;
			}
			case REG_ADDR_BACK_AIR_CO2:
			{
				reg_detailes = app_general_pull_backair_co2();
				break;
			}
			case REG_ADDR_BACK_AIR_PM25:
			{
				reg_detailes = app_general_pull_backair_pm25();
				break;
			}
			case REG_ADDR_DEADZONE_FAN_HUM:
			{
				reg_detailes = app_general_pull_aircod_setHum_deadZone();
				break;
			}
			case REG_ADDR_DEADZONE_FAN_TEMP:
			{
				reg_detailes = app_general_pull_aircod_setTemp_deadZone();
				break;
			}
			case REG_ADDR_NEW_AIR_SPEED:
			{
				reg_detailes = app_general_pull_aircod_newair_speed();
				break;
			}
			case REG_ADDR_BACK_AIR_SPEED:
			{
				reg_detailes = app_general_pull_aircod_backair_speed();
				break;
			}
			case REG_ADDR_WATER_MACHINE_FRE:
			{
				reg_detailes = app_general_pull_water_machine_fre();
				break;
			}
			case REG_ADDR_FU_MACHINE_FRE:
			{
				reg_detailes = app_general_pull_fu_machine_fre();
				break;
			}
			case REG_ADDR_MASTER_SUPPLY_TEMP:
			{
				reg_detailes = app_general_pull_master_supply_temp();
				break;
			}
			case REG_ADDR_MASTER_LIVING_TEMP:
			{
				reg_detailes = app_general_pull_master_living_temp();
				break;
			}
			case REG_ADDR_MASTER_OUTDOOR_TEMP:
			{
				//reg_detailes = app_general_pull_master_outdoor_temp();
				break;
			}
			case REG_ADDR_ADJUST_OUTDOORAIR_HUM:
			{
				reg_detailes = app_general_pull_adjust_outdoor_hum();
				break;
			}
			case REG_ADDR_ADJUST_OUTDOORAIR_TEMP:
			{
				reg_detailes = app_general_pull_adjust_outdoor_temp();
				break;
			}
			case REG_ADDR_ADJUST_OUTDOORAIR_CO2:
			{
				reg_detailes = app_general_pull_adjust_outdoor_co2();
				break;
			}
			case REG_ADDR_ADJUST_OUTDOORAIR_PM25:
			{
				reg_detailes = app_general_pull_adjust_outdoor_pm25();
				break;
			}
			case REG_ADDR_ADJUST_BEFORFU_HUM:
			{
				reg_detailes = app_general_pull_adjust_beforfu_hum();
				break;
			}
			case REG_ADDR_ADJUST_BEFORFU_TEMP:
			{
				reg_detailes = app_general_pull_adjust_beforfu_temp();
				break;
			}
			case REG_ADDR_ADJUST_BEFORFU_CO2:
			{
				reg_detailes = app_general_pull_adjust_beforfu_co2();
				break;
			}
			case REG_ADDR_ADJUST_BEFORFU_PM25:
			{
				reg_detailes = app_general_pull_adjust_beforfu_pm25();
				break;
			}
			case REG_ADDR_ADJUST_AFTERFU_HUM:
			{
				reg_detailes = app_general_pull_adjust_afterfu_hum();
				break;
			}
			case REG_ADDR_ADJUST_AFTERFU_TEMP:
			{
				reg_detailes = app_general_pull_adjust_afterfu_temp();
				break;
			}
			case REG_ADDR_ADJUST_AFTERFU_CO2:
			{
				reg_detailes = app_general_pull_adjust_afterfu_co2();
				break;
			}
			case REG_ADDR_ADJUST_AFTERFU_PM25:
			{
				reg_detailes = app_general_pull_adjust_afterfu_pm25();
				break;
			}       
            case REG_ADDR_SYSTEM_STATSU:
			{
				reg_detailes = app_general_pull_system_status_word();
				break;
			}
			case REG_ADDR_LEW_PROTECT_STATSU:
			{
				reg_detailes = app_general_pull_system_lew_temp_status();
				break;
			}
			case REG_ADDR_PAD_OUTPUT_STATSU:
			{
				reg_detailes = app_general_pull_pad_output_status();
				break;
			}
			case REG_ADDR_ADJUST_BACKAIR_HUM:
			{
				reg_detailes = app_general_pull_adjust_backair_hum();
				break;
			}
			case REG_ADDR_ADJUST_BACKAIR_TEMP:
			{
				reg_detailes = app_general_pull_adjust_backair_temp();
				break;
			}
			case REG_ADDR_ADJUST_BACKAIR_CO2:
			{
				reg_detailes = app_general_pull_adjust_backair_co2();
				break;
			}
			case REG_ADDR_ADJUST_BACKAIR_PM25:
			{
				reg_detailes = app_general_pull_adjust_backair_pm25();
				break;
			}
			case REG_ADDR_ADJUST_EXHASTAIR_HUM:
			{
				reg_detailes = app_general_pull_adjust_exhastair_hum();
				break;
			}
			case REG_ADDR_ADJUST_EXHASTAIR_TEMP:
			{
				reg_detailes = app_general_pull_adjust_exhastair_temp();
				break;
			}
			case REG_ADDR_ADJUST_EXHASTAIR_CO2:
			{
				reg_detailes = app_pull_first_in_water_temp();
				break;
			}
			case REG_ADDR_ADJUST_EXHASTAIR_PM25:
			{
				reg_detailes = app_pull_first_back_water_temp();
				break;
			}
			case REG_ADDR_SET_MIXWATER_COLD_TEMP:
			{
				reg_detailes = app_general_pull_set_mixwater_cold_temp();
				break;
			}
			case REG_ADDR_SET_MIXWATER_HEAT_TEMP:
			{
				reg_detailes = app_general_pull_set_mixwater_heat_temp();
				break;
			}
			case REG_ADDR_MIXWATER_INWATER_TEMP:
			{
				//reg_detailes = app_pull_in_water_temp();
				break;
			}
			case REG_ADDR_MIXWATER_BACKWATER_TEMP:
			{
				reg_detailes = app_pull_back_water_temp();
				break;
			}
			case REG_ADDR_MIXWATER_TEMP:
			{
				reg_detailes = app_pull_mix_water_temp();
				break;
			}
			case REG_ADDR_OUTPUT_PUMP:
			{
				reg_detailes = app_general_pull_pump_output();
				break;
			}
			case REG_ADDR_OUTPUT_THREE_VAVLE:
			{
				reg_detailes = app_general_pull_three_vavle_output();
				break;
			}
			case REG_ADDR_MIXWATER_AI_DEST_TEMP:
			{
				reg_detailes = app_general_pull_ai_dest_temp();
				break;
			}
			case REG_ADDR_MIXWATER_AI_ENABLE:
			{
				reg_detailes = app_general_pull_ai_enable_status();
				break;
			}
			case REG_ADDR_MIXWATER_LOW_TEMP_PROTECT:
			{
				reg_detailes = app_general_pull_mix_freeze_protect();
				break;
			}
			case REG_ADDR_COLD_NO_NEED_SET_TEMP_CONFIG:
            {//制冷无能需出水温度配置
                reg_detailes = app_general_pull_cold_no_need_set_temp();
                break;
            }
            case REG_ADDR_COLD_FAN_NEED_SET_TEMP_CONFIG:
            {//制冷风盘能需出水温度配置
                reg_detailes = app_general_pull_cold_fan_need_set_temp();
                break;
            }
            case REG_ADDR_COLD_WARM_NEED_SET_TEMP_CONFIG:
            {//制冷辐射能需出水温度配置
                reg_detailes = app_general_pull_cold_warm_need_set_temp();
                break;
            }
            case REG_ADDR_LEW_TEMP_COMPARE_CONFIG:
            {//制冷露点比较温度配置
                reg_detailes = app_general_pull_config_lew_set_temp();
                break;
            }
            case REG_ADRESS_HEAT_NO_NEED_SET_TEMP_CONFIG:
            {//制热无能需出水温度配置
                reg_detailes = app_general_pull_heat_no_need_set_temp();
                break;
            }
            case REG_ADRESS_HEAT_FAN_NEED_SET_TEMP_CONFIG:
            {//制热风盘能需出水温度配置
                reg_detailes = app_general_pull_heat_fan_need_set_temp();
                break;
            }
            case REG_ADRESS_HEAT_WARM_NEED_SET_TEMP_CONFIG:
            {//制热辐射能需出水温度配置
                reg_detailes = app_general_pull_heat_warm_need_set_temp();
                break;
            }
            case REG_ADRESS_HEAT_BACKWATER_COMPARE_CONFIG:
            {//制热回风比较温度配置
                reg_detailes = app_general_pull_config_back_wind_set_temp();
                break;
            }
            case REG_ADRESS_DEHUM_FIX_CONFIG:
            {//除湿固定湿度配置
                reg_detailes = app_general_pull_config_hum_set();
                break;
            }
            case REG_ADRESS_COLD_WIND_MAX_COLD_SET:
            {//制冷氟盘最大设定温度
                reg_detailes = app_general_pull_cold_wind_max_set_temp();
                break;
            }
            case REG_ADRESS_HEAT_WIND_MIN_COLD_SET:
            {//制热氟盘最小设定温度
                reg_detailes = app_general_pull_heat_wind_min_set_temp();
                break;
            }
            case REG_ADRESS_HEAT_WIND_MAX_COLD_SET:
            {//制热氟盘最大设定温度
                reg_detailes = app_general_pull_heat_wind_max_set_temp();
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
            case REG_ADRESS_WATER_MACHINE_CONTROL:
            {//水机控制
                reg_detailes = app_general_pull_water_machine_status();
                break;
            }
			case REG_ADRESS_NEW_TREND_EFFCIENCY:
			{
				reg_detailes = app_general_pull_freshair_effciency();
				break;
			}
            case REG_ADRESS_WIND_VALUE: //风阀切换
            {
                reg_detailes = app_general_pull_wind_value();
				break;
            }			
			case REG_ADRESS_HOTWATER_ENABLE: //热水使能
            {
                reg_detailes = app_general_pull_hotwater_enable();
				break;
            }		
			case REG_ADRESS_COOL_BACKWATER_SETTEMP: 
            {//制冷回水设置温度
                reg_detailes = app_general_pull_coolbackwater_set_temp();
				break;
            }	
            case REG_ADRESS_FILTER_TIME:
            {//滤芯更换周期
                reg_detailes = app_general_pull_filter_time();
				break;
            }	
			case REG_ADRESS_HOT_BACKWATER_SETTEMP: 
            {//制热回水设置温度
                reg_detailes = app_general_pull_hotbackwater_set_temp();
				break;
            }	
            case REG_ADRESS_FILTER_USERTIME:
            {//滤芯使用时间
                reg_detailes = app_general_pull_filter_usetime();
				break;
            }	 			
            case REG_ADRESS_DEBUG_ENABLE:
            {//调试使能
                reg_detailes = app_general_pull_debug_enable();
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
			case REG_ADDR_PAD12_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD12_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD12_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD12_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD12_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD12_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD12_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD12_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD12_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD12_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD12_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD12_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD12_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD12_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD12_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD12_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD12_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD12_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD12_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD12_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD12_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD12_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD12_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD12_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD12_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD12_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD12_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD12_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD12_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD12_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD12_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD12_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD12_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD12_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD12_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD12_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD12_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD12_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD12_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD12_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD12_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD12_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD12_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD12_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD12_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD12_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
	        
						case REG_ADDR_PAD13_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD13_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD13_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD13_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD13_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD13_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD13_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD13_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD13_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD13_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD13_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD13_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD13_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD13_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD13_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD13_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD13_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD13_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD13_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD13_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD13_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD13_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD13_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD13_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD13_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD13_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD13_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD13_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD13_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD13_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD13_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD13_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD13_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD13_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD13_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD13_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD13_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD13_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD13_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD13_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD13_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD13_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD13_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD13_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD13_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD13_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}

						case REG_ADDR_PAD14_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD14_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD14_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD14_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD14_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD14_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD14_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD14_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD14_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD14_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD14_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD14_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD14_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD14_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD14_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD14_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD14_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD14_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD14_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD14_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD14_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD14_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD14_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD14_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD14_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD14_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD14_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD14_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD14_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD14_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD14_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD14_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD14_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD14_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD14_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD14_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD14_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD14_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD14_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD14_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD14_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD14_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD14_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD14_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD14_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD14_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}

						case REG_ADDR_PAD15_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD15_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD15_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD15_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD15_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD15_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD15_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD15_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD15_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD15_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD15_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD15_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD15_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD15_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD15_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD15_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD15_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD15_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD15_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD15_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD15_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD15_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD15_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD15_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD15_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD15_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD15_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD15_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD15_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD15_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD15_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD15_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD15_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD15_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD15_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD15_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD15_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD15_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD15_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD15_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD15_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD15_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD15_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD15_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD15_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD15_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}

						case REG_ADDR_PAD16_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD16_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD16_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD16_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD16_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD16_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD16_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD16_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD16_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD16_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD16_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD16_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD16_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD16_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD16_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD16_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD16_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD16_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD16_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD16_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD16_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD16_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD16_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD16_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD16_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD16_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD16_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD16_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD16_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD16_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD16_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD16_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD16_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD16_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD16_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD16_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD16_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD16_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD16_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD16_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD16_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD16_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD16_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD16_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD16_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD16_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
						case REG_ADDR_PAD17_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD17_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD17_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD17_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD17_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD17_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD17_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD17_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD17_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD17_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD17_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD17_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD17_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD17_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD17_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD17_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD17_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD17_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD17_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD17_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD17_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD17_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD17_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD17_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD17_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD17_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD17_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD17_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD17_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD17_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD17_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD17_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD17_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD17_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD17_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD17_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD17_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD17_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD17_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD17_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD17_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD17_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD17_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD17_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD17_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD17_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
						case REG_ADDR_PAD18_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD18_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD18_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD18_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD18_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD18_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD18_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD18_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD18_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD18_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD18_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD18_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD18_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD18_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD18_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD18_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD18_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD18_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD18_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD18_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD18_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD18_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD18_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD18_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD18_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD18_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD18_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD18_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD18_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD18_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD18_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD18_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD18_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD18_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD18_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD18_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD18_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD18_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD18_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD18_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD18_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD18_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD18_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD18_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD18_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD18_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}

						case REG_ADDR_PAD19_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD19_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD19_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD19_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD19_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD19_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD19_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD19_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD19_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD19_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD19_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD19_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD19_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD19_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD19_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD19_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD19_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD19_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD19_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD19_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD19_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD19_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD19_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD19_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD19_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD19_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD19_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD19_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD19_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD19_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD19_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD19_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD19_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD19_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD19_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD19_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD19_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD19_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD19_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD19_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD19_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD19_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD19_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD19_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD19_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD19_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}

						case REG_ADDR_PAD20_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD20_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD20_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD20_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD20_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD20_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD20_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD20_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD20_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD20_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD20_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD20_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD20_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD20_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD20_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD20_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD20_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD20_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD20_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD20_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD20_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD20_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD20_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD20_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD20_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD20_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD20_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD20_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD20_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD20_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD20_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD20_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD20_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD20_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD20_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD20_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD20_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD20_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD20_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD20_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD20_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD20_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD20_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD20_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD20_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD20_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}

						case REG_ADDR_PAD21_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD21_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD21_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD21_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD21_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD21_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD21_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD21_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD21_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD21_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD21_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD21_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD21_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD21_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD21_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD21_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD21_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD21_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD21_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD21_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD21_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD21_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD21_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD21_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD21_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD21_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD21_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD21_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD21_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD21_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD21_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD21_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD21_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD21_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD21_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD21_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD21_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD21_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD21_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD21_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD21_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD21_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD21_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD21_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD21_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD21_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}

						case REG_ADDR_PAD22_ERROR_WORD:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_error_word(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD22_ONLINE_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_online(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD22_DEVICE_TYPE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_type(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD22_DEVICE_ID0:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id0(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD22_DEVICE_ID1:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id1(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD22_DEVICE_ID2:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_devive_id2(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD22_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{//有绑定信息
					reg_detailes = app_general_pull_devive_power(virtualPort);
				}
				break;
			}
			case REG_ADDR_PAD22_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_cold_temp(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD22_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_heat_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD22_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_drop_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD22_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_warm_status(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD22_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_protect(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD22_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_freeze_temp(virtualPort);
				}           
				break;
			}    
			case REG_ADDR_PAD22_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_child_lock(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD22_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_onoff_memory(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD22_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD22_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_heat_comfortable_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD22_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_high_temp(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD22_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_low_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD22_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD22_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_deadzone_lewtemp(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD22_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_measure_temp(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD22_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					 reg_detailes = app_general_pull_pad_measure_hum(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD22_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_need(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD22_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_fan_speed(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD22_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_control(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD22_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_low(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD22_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_mid(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD22_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_set_pwm_high(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD22_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_cold_diff(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD22_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_ai_heat_diff(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD22_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_cold_colla_enable(virtualPort);
				}          
				break;
			}
			case REG_ADDR_PAD22_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_warm_colla_enable(virtualPort);
				}      
				break;
			}
			case REG_ADDR_PAD22_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_need(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD22_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_out_speed(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD22_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_fan_speed_output(virtualPort);
				}            
				break;
			}
			case REG_ADDR_PAD22_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_control_num(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD22_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_two_output_mode(virtualPort);
				}           
				break;
			}
			case REG_ADDR_PAD22_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_fan(virtualPort);
				}         
				break;
			}
			case REG_ADDR_PAD22_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_bind_list_warm(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD22_WARM_TYPE:
			{/*辐射类型选择*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_type_warm_choose(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD22_ROOM_AREA:
			{/*房间面积*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_room_area(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD22_LEW_TEMP_STATUS:
			{/*露点保护状态*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_lew_dorp_temp_output(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD22_ADJUST_TEMP:
			{/*校温*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_temp(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD22_ADJUST_HUM:
			{/*校湿*/
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADDR_PAD22_VERSION:
			{/*版本号*/
				virtualPort = app_general_pull_pad_version((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					reg_detailes = app_general_pull_pad_adjust_hum(virtualPort);
				}        
				break;
			}
			case REG_ADRESS_REMOTE_CONTROL:
			{
				reg_detailes = app_general_pull_remote_control();
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY1:
			{
				reg_detailes = app_general_pull_remote_relay(0);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY2:
			{
				reg_detailes = app_general_pull_remote_relay(1);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY3:
			{
				reg_detailes = app_general_pull_remote_relay(2);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY4:
			{
				reg_detailes = app_general_pull_remote_relay(3);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY5:
			{
				reg_detailes = app_general_pull_remote_relay(4);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY6:
			{
				reg_detailes = app_general_pull_remote_relay(5);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY7:
			{
				reg_detailes = app_general_pull_remote_relay(6);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY8:
			{
				reg_detailes = app_general_pull_remote_relay(7);
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

bool app_modebus_write_reg_data(uint16_t reg_addr,uint16_t reg_detailes,uint8_t in_src)
{
    uint8_t virtualPort = PAD_NO_PHY_BIND;
	if((reg_addr >= MRegaddr_StrUpdateWord) && (reg_addr <= MRegaddr_Message63))
    {
        //app_updataBackup_writeRegister(reg_addr,reg_detailes);
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
			case REG_ADDR_MASTER_ERROR_WORD:
			{
			  //  app_general_push_master_error_word(reg_detailes);
				break;
			}
			case REG_ADDR_AIRCOD_ENERGY_NEED:
			{
				app_general_push_anergy_need(reg_detailes);
				break;
			}
			case REG_ADDR_SYSTEM_POWER:
			{
				app_general_push_power_status(reg_detailes);
				break;
			}
			case REG_ADDR_SYSTEM_RUN_MODE:
			{
				app_general_push_aircod_mode((AirRunMode_Def)reg_detailes);
				break;
			}
			case REG_ADDR_FAN_SET_HUM:
			{
				app_general_push_aircod_humidity(reg_detailes);
				break;
			}
			case REG_ADDR_FAN_SET_SPEED:
			{
				app_general_push_aircod_fanSpeed((NewAirLevelSet_Def)reg_detailes);
				break;
			}
			case REG_ADDR_SET_COLD_TEMP:
			{
				app_general_push_aircod_cold_temp(reg_detailes);
				break;
			}
			case REG_ADDR_SET_HEAT_TEMP:
			{
				app_general_push_aircod_heat_temp(reg_detailes);
				break;
			}
			case REG_ADDR_NEW_AIR_LOW_PWM:
			{
				app_general_push_new_air_pwm_low(reg_detailes);
				break;
			}
			case REG_ADDR_NEW_AIR_MID_PWM:
			{
				app_general_push_new_air_pwm_mid(reg_detailes);
				break;
			}
			case REG_ADDR_NEW_AIR_HIGH_PWM:
			{
				app_general_push_new_air_pwm_high(reg_detailes);
				break;
			}
			case REG_ADDR_BACK_AIR_LOW_PWM:
			{
				app_general_push_back_air_pwm_low(reg_detailes);
				break;
			}
			case REG_ADDR_BACK_AIR_MID_PWM:
			{
				app_general_push_back_air_pwm_mid(reg_detailes);
				break;
			}
			case REG_ADDR_BACK_AIR_HIGH_PWM:
			{
				app_general_push_back_air_pwm_high(reg_detailes);
				break;
			}
			case REG_ADDR_MASTER_SET_COLD_WATER_TEMP:
			{
				app_general_push_set_cold_water_temp(reg_detailes);
				break;
			}
			case REG_ADDR_MASTER_SET_HEAT_WATER_TEMP:
			{
				app_general_push_set_heat_water_temp(reg_detailes);
				break;
			}
			case REG_ADDR_MASTER_SET_LIVING_WATER_TEMP:
			{
				app_general_push_set_living_water_temp(reg_detailes);
				break;
			}
			case REG_ADDR_MASTER_OUTDOOR_IN_FAN_TEMP:
			{
			  //  app_general_push_outdoor_temp(reg_detailes);
				break;
			}
			case REG_ADDR_MASTER_OUTDOOR_IN_FAN_HUM:
			{
			  //  app_general_push_outdoor_hum(reg_detailes);
				break;
			}
			case REG_ADDR_BEFORE_FU_TEMP:
			{
			   // app_general_push_before_fu_temp(reg_detailes);
				break;
			}
			case REG_ADDR_BEFORE_FU_HUM:
			{
			   // app_general_push_before_fu_hum(reg_detailes);
				break;
			}
			case REG_ADDR_AFTER_FU_TEMP:
			{
			  //  app_general_push_after_fu_temp(reg_detailes);
				break;
			}
			case REG_ADDR_AFTER_FU_HUM:
			{
			  //  app_general_push_after_fu_hum(reg_detailes);
				break;
			}
			case REG_ADDR_BACK_AIR_TEMP:
			{
			 //   app_general_push_backair_temp(reg_detailes);
				break;
			}
			case REG_ADDR_BACK_AIR_HUM:
			{
			  //  app_general_push_backair_hum(reg_detailes);
				break;
			}
			case REG_ADDR_EXHAST_AIR_TEMP:
			{
			  //  app_general_push_exhastair_temp(reg_detailes);
				break;
			}
			case REG_ADDR_EXHAST_AIR_HUM:
			{
			  //  app_general_push_exhastair_hum(reg_detailes);
				break;
			}
			case REG_ADDR_BACK_AIR_CO2:
			{
			   // app_general_push_backair_co2(reg_detailes);
				break;
			}
			case REG_ADDR_BACK_AIR_PM25:
			{
			  //  app_general_push_backair_pm25(reg_detailes);
				break;
			}
			case REG_ADDR_DEADZONE_FAN_HUM:
			{
				//app_general_push_aircod_setHum_deadZone(reg_detailes);
				break;
			}
			case REG_ADDR_DEADZONE_FAN_TEMP:
			{
			   // app_general_push_aircod_setTemp_deadZone(reg_detailes);
				break;
			}
			case REG_ADDR_NEW_AIR_SPEED:
			{
			   // app_general_push_aircod_newair_speed(reg_detailes);
				break;
			}
			case REG_ADDR_BACK_AIR_SPEED:
			{
			  //  app_general_push_aircod_backair_speed(reg_detailes);
				break;
			}
			case REG_ADDR_WATER_MACHINE_FRE:
			{
			 //   app_general_push_water_machine_fre(reg_detailes);
				break;
			}
			case REG_ADDR_FU_MACHINE_FRE:
			{
			  //  app_general_push_fu_machine_fre(reg_detailes);
				break;
			}
			case REG_ADDR_MASTER_SUPPLY_TEMP:
			{
				app_general_push_master_supply_temp(reg_detailes);
				break;
			}
			case REG_ADDR_MASTER_LIVING_TEMP:
			{
				app_general_push_master_living_temp(reg_detailes);
				break;
			}
			case REG_ADDR_MASTER_OUTDOOR_TEMP:
			{
			    app_general_push_system_reset_word(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_OUTDOORAIR_HUM:
			{
				app_general_push_adjust_outdoor_hum(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_OUTDOORAIR_TEMP:
			{
				app_general_push_adjust_outdoor_temp(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_OUTDOORAIR_CO2:
			{
				app_general_push_adjust_outdoor_co2(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_OUTDOORAIR_PM25:
			{
				app_general_push_adjust_outdoor_pm25(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_BEFORFU_HUM:
			{
				app_general_push_adjust_beforfu_hum(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_BEFORFU_TEMP:
			{
				app_general_push_adjust_beforfu_temp(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_BEFORFU_CO2:
			{
				app_general_push_adjust_beforfu_co2(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_BEFORFU_PM25:
			{
				app_general_push_adjust_beforfu_pm25(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_AFTERFU_HUM:
			{
				app_general_push_adjust_afterfu_hum(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_AFTERFU_TEMP:
			{
				app_general_push_adjust_afterfu_temp(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_AFTERFU_CO2:
			{
				app_general_push_adjust_afterfu_co2(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_AFTERFU_PM25:
			{
				app_general_push_adjust_afterfu_pm25(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_BACKAIR_HUM:
			{
				app_general_push_adjust_backair_hum(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_BACKAIR_TEMP:
			{
				app_general_push_adjust_backair_temp(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_BACKAIR_CO2:
			{
				app_general_push_adjust_backair_co2(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_BACKAIR_PM25:
			{
				app_general_push_adjust_backair_pm25(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_EXHASTAIR_HUM:
			{
				app_general_push_adjust_exhastair_hum(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_EXHASTAIR_TEMP:
			{
				app_general_push_adjust_exhastair_temp(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_EXHASTAIR_CO2:
			{
				//app_general_push_adjust_exhastair_co2(reg_detailes);
				break;
			}
			case REG_ADDR_ADJUST_EXHASTAIR_PM25:
			{
				//app_general_push_adjust_exhastair_pm25(reg_detailes);
				break;
			}
			case REG_ADDR_SET_MIXWATER_COLD_TEMP:
			{
				app_general_push_set_mixwater_cold_temp(reg_detailes);
				break;
			}
			case REG_ADDR_SET_MIXWATER_HEAT_TEMP:
			{
				app_general_push_set_mixwater_heat_temp(reg_detailes);
				break;
			}
			case REG_ADDR_MIXWATER_INWATER_TEMP:
			{
			  //  reg_detailes = 0;
				break;
			}
			case REG_ADDR_MIXWATER_BACKWATER_TEMP:
			{
			 //   reg_detailes = 0;
				break;
			}
			case REG_ADDR_MIXWATER_TEMP:
			{
			 //   reg_detailes = 0;
				break;
			}
			case REG_ADDR_OUTPUT_PUMP:
			{
			   // reg_detailes = 0;
				break;
			}
			case REG_ADDR_OUTPUT_THREE_VAVLE:
			{
			   // reg_detailes = 0;
				break;
			}
			case REG_ADDR_MIXWATER_AI_DEST_TEMP:
			{
			   // reg_detailes = 0;
				break;
			}
			case REG_ADDR_MIXWATER_AI_ENABLE:
			{
				app_general_push_ai_enable_status(reg_detailes);
				break;
			}
			case REG_ADDR_MIXWATER_LOW_TEMP_PROTECT:
			{
				app_general_push_mix_freeze_protect(reg_detailes);
				break;
			}
			case REG_ADRESS_WIND_VALUE: //风阀切换
            {
                app_general_push_wind_value(reg_detailes);
                break;
            }                           
			case REG_ADRESS_HOTWATER_ENABLE://热水使能
            {
				app_general_push_hotwater_enable(reg_detailes);
				break;
            }
			case REG_ADRESS_COOL_BACKWATER_SETTEMP: 
            {
                app_general_push_coolbackwater_set_temp(reg_detailes);
                break;
            }    
            case REG_ADRESS_FILTER_TIME:
            {
				app_general_push_filter_time(reg_detailes);
				break;
            }
            case REG_ADRESS_HOT_BACKWATER_SETTEMP: 
            {
                app_general_push_hotbackwater_set_temp(reg_detailes);
                break;
            }
            case REG_ADRESS_FILTER_USERTIME:
            {
				app_general_push_filter_usetime(reg_detailes);
				break;   
            }
			 case REG_ADDR_COLD_NO_NEED_SET_TEMP_CONFIG:
            {//制冷无能需出水温度配置
                app_general_push_cold_no_need_set_temp(reg_detailes);
                break;
            }
            case REG_ADDR_COLD_FAN_NEED_SET_TEMP_CONFIG:
            {//制冷风盘能需出水温度配置
                app_general_push_cold_fan_need_set_temp(reg_detailes);
                break;
            }
            case REG_ADDR_COLD_WARM_NEED_SET_TEMP_CONFIG:
            {//制冷辐射能需出水温度配置
                app_general_push_cold_warm_need_set_temp(reg_detailes);
                break;
            }
            case REG_ADDR_LEW_TEMP_COMPARE_CONFIG:
            {//制冷露点比较温度配置
                app_general_push_config_lew_set_temp(reg_detailes);
                break;
            }
            case REG_ADRESS_HEAT_NO_NEED_SET_TEMP_CONFIG:
            {//制热无能需出水温度配置
                app_general_push_heat_no_need_set_temp(reg_detailes);
                break;
            }
            case REG_ADRESS_HEAT_FAN_NEED_SET_TEMP_CONFIG:
            {//制热风盘能需出水温度配置
                app_general_push_heat_fan_need_set_temp(reg_detailes);
                break;
            }
            case REG_ADRESS_HEAT_WARM_NEED_SET_TEMP_CONFIG:
            {//制热辐射能需出水温度配置
                app_general_push_heat_warm_need_set_temp(reg_detailes);
                break;
            }
            case REG_ADRESS_HEAT_BACKWATER_COMPARE_CONFIG:
            {//制热回风比较温度配置
                app_general_push_config_back_wind_set_temp(reg_detailes);
                break;
            }
            case REG_ADRESS_DEHUM_FIX_CONFIG:
            {//除湿固定湿度配置
                app_general_push_config_hum_set(reg_detailes);
                break;
            }
            case REG_ADRESS_COLD_WIND_MAX_COLD_SET:
            {//制冷氟盘最大设定温度
                app_general_push_cold_wind_max_set_temp(reg_detailes);
                break;
            }
            case REG_ADRESS_HEAT_WIND_MIN_COLD_SET:
            {//制热氟盘最小设定温度
                app_general_push_heat_wind_min_set_temp(reg_detailes);
                break;
            }
            case REG_ADRESS_HEAT_WIND_MAX_COLD_SET:
            {//制热氟盘最大设定温度
                app_general_push_heat_wind_max_set_temp(reg_detailes);
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
            case REG_ADRESS_WATER_MACHINE_CONTROL:
            {//水机控制
                app_general_push_water_machine_status(reg_detailes);
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
			case REG_ADDR_PAD1_ERROR_WORD:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_error_word(virtualPort,reg_detailes);
	//            }           
				break;
			}
			case REG_ADDR_PAD1_ONLINE_STATUS:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_online(virtualPort,reg_detailes);
	//            }       
				break;
			}
			case REG_ADDR_PAD1_DEVICE_TYPE:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_type(virtualPort,reg_detailes);
	//            }    
				break;
			}
			case REG_ADDR_PAD1_DEVICE_ID0:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id0(virtualPort,reg_detailes);
	//            }       
				break;
			}
			case REG_ADDR_PAD1_DEVICE_ID1:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id1(virtualPort,reg_detailes);
	//            }         
				break;
			}
			case REG_ADDR_PAD1_DEVICE_ID2:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id2(virtualPort,reg_detailes);
	//            }      
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
			case REG_ADDR_PAD1_COLD_WARM_STATUS:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
	//            }        
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
			case REG_ADDR_PAD1_MEASURE_TEMP:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_temp(virtualPort,reg_detailes);
	//            }      
				break;
			}
			case REG_ADDR_PAD1_MEASURE_HUM:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_hum(virtualPort,reg_detailes);
	//            }     
				break;
			}
			case REG_ADDR_PAD1_WARM_NEED:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_warm_need(virtualPort,reg_detailes);
	//            } 
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
			case REG_ADDR_PAD1_FAN_VAVLE_NEED:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_need(virtualPort,reg_detailes);
	//            }         
				break;
			}
			case REG_ADDR_PAD1_FAN_OUTPUT_LEVEL:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
	//            }          
				break;
			}
			case REG_ADDR_PAD1_FAN_SPEED:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
	//            }           
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
	//        case REG_ADDR_PAD2_ERROR_WORD:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_error_word(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
	//        case REG_ADDR_PAD2_ONLINE_STATUS:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_online(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD2_DEVICE_TYPE:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_type(virtualPort,reg_detailes);
	//            }    
	//            break;
	//        }
	//        case REG_ADDR_PAD2_DEVICE_ID0:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id0(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD2_DEVICE_ID1:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id1(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD2_DEVICE_ID2:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id2(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
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
			case REG_ADDR_PAD2_COLD_WARM_STATUS:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
	//            }        
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
			case REG_ADDR_PAD2_MEASURE_TEMP:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_temp(virtualPort,reg_detailes);
	//            }      
				break;
			}
			case REG_ADDR_PAD2_MEASURE_HUM:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_hum(virtualPort,reg_detailes);
	//            }     
				break;
			}
			case REG_ADDR_PAD2_WARM_NEED:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_warm_need(virtualPort,reg_detailes);
	//            } 
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
			case REG_ADDR_PAD2_FAN_VAVLE_NEED:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_need(virtualPort,reg_detailes);
	//            }         
				break;
			}
			case REG_ADDR_PAD2_FAN_OUTPUT_LEVEL:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
	//            }          
				break;
			}
			case REG_ADDR_PAD2_FAN_SPEED:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
	//            }           
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
			case REG_ADDR_PAD2_BIND_FAN:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
	//            }          
				break;
			}
			case REG_ADDR_PAD2_BIND_WARM:
			{
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
	//            }          
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
	//        case REG_ADDR_PAD3_ERROR_WORD:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_error_word(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
	//        case REG_ADDR_PAD3_ONLINE_STATUS:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_online(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD3_DEVICE_TYPE:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_type(virtualPort,reg_detailes);
	//            }    
	//            break;
	//        }
	//        case REG_ADDR_PAD3_DEVICE_ID0:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id0(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD3_DEVICE_ID1:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id1(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD3_DEVICE_ID2:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id2(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
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
	//        case REG_ADDR_PAD3_MEASURE_TEMP:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_temp(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
	//        case REG_ADDR_PAD3_MEASURE_HUM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_hum(virtualPort,reg_detailes);
	//            }     
	//            break;
	//        }
	//        case REG_ADDR_PAD3_WARM_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_warm_need(virtualPort,reg_detailes);
	//            } 
	//            break;
	//        }
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
	//        case REG_ADDR_PAD3_FAN_VAVLE_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_need(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD3_FAN_OUTPUT_LEVEL:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD3_FAN_SPEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
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
	//        case REG_ADDR_PAD3_BIND_FAN:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD3_BIND_WARM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
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
	//        case REG_ADDR_PAD4_ERROR_WORD:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_error_word(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
	//        case REG_ADDR_PAD4_ONLINE_STATUS:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_online(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD4_DEVICE_TYPE:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_type(virtualPort,reg_detailes);
	//            }    
	//            break;
	//        }
	//        case REG_ADDR_PAD4_DEVICE_ID0:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id0(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD4_DEVICE_ID1:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id1(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD4_DEVICE_ID2:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id2(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
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
	//        case REG_ADDR_PAD4_MEASURE_TEMP:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_temp(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
	//        case REG_ADDR_PAD4_MEASURE_HUM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_hum(virtualPort,reg_detailes);
	//            }     
	//            break;
	//        }
	//        case REG_ADDR_PAD4_WARM_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_warm_need(virtualPort,reg_detailes);
	//            } 
	//            break;
	//        }
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
	//        case REG_ADDR_PAD4_FAN_VAVLE_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_need(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD4_FAN_OUTPUT_LEVEL:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD4_FAN_SPEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
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
	//        case REG_ADDR_PAD4_BIND_FAN:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD4_BIND_WARM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
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
	//        case REG_ADDR_PAD5_ERROR_WORD:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_error_word(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
	//        case REG_ADDR_PAD5_ONLINE_STATUS:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_online(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD5_DEVICE_TYPE:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_type(virtualPort,reg_detailes);
	//            }    
	//            break;
	//        }
	//        case REG_ADDR_PAD5_DEVICE_ID0:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id0(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD5_DEVICE_ID1:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id1(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD5_DEVICE_ID2:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id2(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
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
	//        case REG_ADDR_PAD5_MEASURE_TEMP:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_temp(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
	//        case REG_ADDR_PAD5_MEASURE_HUM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_hum(virtualPort,reg_detailes);
	//            }     
	//            break;
	//        }
	//        case REG_ADDR_PAD5_WARM_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_warm_need(virtualPort,reg_detailes);
	//            } 
	//            break;
	//        }
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
	//        case REG_ADDR_PAD5_FAN_VAVLE_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_need(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD5_FAN_OUTPUT_LEVEL:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD5_FAN_SPEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
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
	//        case REG_ADDR_PAD5_BIND_FAN:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD5_BIND_WARM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
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
	//        case REG_ADDR_PAD6_ERROR_WORD:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_error_word(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
	//        case REG_ADDR_PAD6_ONLINE_STATUS:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_online(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD6_DEVICE_TYPE:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_type(virtualPort,reg_detailes);
	//            }    
	//            break;
	//        }
	//        case REG_ADDR_PAD6_DEVICE_ID0:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id0(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD6_DEVICE_ID1:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id1(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD6_DEVICE_ID2:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id2(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
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
	//        case REG_ADDR_PAD6_MEASURE_TEMP:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_temp(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
	//        case REG_ADDR_PAD6_MEASURE_HUM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_hum(virtualPort,reg_detailes);
	//            }     
	//            break;
	//        }
	//        case REG_ADDR_PAD6_WARM_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_warm_need(virtualPort,reg_detailes);
	//            } 
	//            break;
	//        }
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
	//        case REG_ADDR_PAD6_FAN_VAVLE_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_need(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD6_FAN_OUTPUT_LEVEL:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD6_FAN_SPEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
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
	//        case REG_ADDR_PAD6_BIND_FAN:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD6_BIND_WARM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
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
	//        case REG_ADDR_PAD7_ERROR_WORD:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_error_word(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
	//        case REG_ADDR_PAD7_ONLINE_STATUS:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_online(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD7_DEVICE_TYPE:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_type(virtualPort,reg_detailes);
	//            }    
	//            break;
	//        }
	//        case REG_ADDR_PAD7_DEVICE_ID0:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id0(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD7_DEVICE_ID1:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id1(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD7_DEVICE_ID2:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id2(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
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
	//        case REG_ADDR_PAD7_MEASURE_TEMP:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_temp(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
	//        case REG_ADDR_PAD7_MEASURE_HUM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_hum(virtualPort,reg_detailes);
	//            }     
	//            break;
	//        }
	//        case REG_ADDR_PAD7_WARM_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_warm_need(virtualPort,reg_detailes);
	//            } 
	//            break;
	//        }
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
	//        case REG_ADDR_PAD7_FAN_VAVLE_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_need(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD7_FAN_OUTPUT_LEVEL:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD7_FAN_SPEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
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
	//        case REG_ADDR_PAD7_BIND_FAN:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD7_BIND_WARM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
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

	//        case REG_ADDR_PAD8_ERROR_WORD:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_error_word(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
	//        case REG_ADDR_PAD8_ONLINE_STATUS:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_online(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD8_DEVICE_TYPE:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_type(virtualPort,reg_detailes);
	//            }    
	//            break;
	//        }
	//        case REG_ADDR_PAD8_DEVICE_ID0:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id0(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD8_DEVICE_ID1:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id1(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD8_DEVICE_ID2:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id2(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
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
	//        case REG_ADDR_PAD8_MEASURE_TEMP:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_temp(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
	//        case REG_ADDR_PAD8_MEASURE_HUM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_hum(virtualPort,reg_detailes);
	//            }     
	//            break;
	//        }
	//        case REG_ADDR_PAD8_WARM_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_warm_need(virtualPort,reg_detailes);
	//            } 
	//            break;
	//        }
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
	//        case REG_ADDR_PAD8_FAN_VAVLE_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_need(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD8_FAN_OUTPUT_LEVEL:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD8_FAN_SPEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
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
	//        case REG_ADDR_PAD8_BIND_FAN:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD8_BIND_WARM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
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
	//        case REG_ADDR_PAD9_ERROR_WORD:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_error_word(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
	//        case REG_ADDR_PAD9_ONLINE_STATUS:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_online(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD9_DEVICE_TYPE:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_type(virtualPort,reg_detailes);
	//            }    
	//            break;
	//        }
	//        case REG_ADDR_PAD9_DEVICE_ID0:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id0(virtualPort,reg_detailes);
	//            }       
	//            break;
	//        }
	//        case REG_ADDR_PAD9_DEVICE_ID1:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id1(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD9_DEVICE_ID2:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_devive_id2(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
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
	//        case REG_ADDR_PAD9_MEASURE_TEMP:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_temp(virtualPort,reg_detailes);
	//            }      
	//            break;
	//        }
	//        case REG_ADDR_PAD9_MEASURE_HUM:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_measure_hum(virtualPort,reg_detailes);
	//            }     
	//            break;
	//        }
	//        case REG_ADDR_PAD9_WARM_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_warm_need(virtualPort,reg_detailes);
	//            } 
	//            break;
	//        }
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
	//        case REG_ADDR_PAD9_FAN_VAVLE_NEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_need(virtualPort,reg_detailes);
	//            }         
	//            break;
	//        }
	//        case REG_ADDR_PAD9_FAN_OUTPUT_LEVEL:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
	//            }          
	//            break;
	//        }
	//        case REG_ADDR_PAD9_FAN_SPEED:
	//        {
	//            virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
	//            if(virtualPort != PAD_NO_PHY_BIND)
	//            {
	//                app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
	//            }           
	//            break;
	//        }
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
            
			case REG_ADDR_PAD12_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD12_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD12_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD12_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD12_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD12_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD12_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD12_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD12_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD12_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD12_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD12_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD12_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD12_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD12_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD12_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD12_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD12_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD12_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD12_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD12_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD12_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD12_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD12_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD12_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD12_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD12_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD12_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD12_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD12_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD12_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD12_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD12_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD12_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD12_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD12_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD12_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD12_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD12_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}

						case REG_ADDR_PAD13_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD13_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD13_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD13_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD13_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD13_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD13_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD13_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD13_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD13_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD13_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD13_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD13_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD13_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD13_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD13_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD13_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD13_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD13_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD13_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD13_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD13_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD13_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD13_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD13_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD13_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD13_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD13_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD13_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD13_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD13_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD13_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD13_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD13_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD13_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD13_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD13_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD13_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD13_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}

						case REG_ADDR_PAD14_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD14_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD14_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD14_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD14_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD14_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD14_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD14_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD14_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD14_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD14_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD14_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD14_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD14_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD14_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD14_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD14_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD14_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD14_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD14_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD14_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD14_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD14_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD14_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD14_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD14_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD14_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD14_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD14_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD14_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD14_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD14_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD14_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD14_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD14_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD14_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD14_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD14_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD14_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}

						case REG_ADDR_PAD15_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD15_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD15_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD15_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD15_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD15_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD15_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD15_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD15_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD15_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD15_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD15_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD15_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD15_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD15_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD15_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD15_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD15_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD15_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD15_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD15_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD15_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD15_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD15_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD15_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD15_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD15_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD15_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD15_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD15_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD15_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD15_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD15_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD15_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD15_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD15_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD15_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD15_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD15_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}

						case REG_ADDR_PAD16_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD16_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD16_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD16_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD16_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD16_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD16_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD16_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD16_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD16_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD16_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD16_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD16_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD16_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD16_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD16_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD16_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD16_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD16_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD16_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD16_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD16_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD16_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD16_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD16_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD16_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD16_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD16_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD16_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD16_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD16_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD16_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD16_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD16_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD16_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD16_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD16_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD16_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD16_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}

						case REG_ADDR_PAD17_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD17_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD17_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD17_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD17_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD17_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD17_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD17_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD17_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD17_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD17_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD17_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD17_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD17_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD17_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD17_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD17_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD17_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD17_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD17_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD17_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD17_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD17_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD17_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD17_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD17_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD17_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD17_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD17_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD17_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD17_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD17_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD17_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD17_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD17_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD17_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD17_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD17_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD17_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}

						case REG_ADDR_PAD18_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD18_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD18_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD18_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD18_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD18_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD18_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD18_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD18_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD18_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD18_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD18_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD18_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD18_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD18_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD18_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD18_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD18_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD18_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD18_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD18_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD18_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD18_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD18_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD18_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD18_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD18_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD18_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD18_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD18_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD18_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD18_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD18_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD18_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD18_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD18_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD18_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD18_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD18_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}

						case REG_ADDR_PAD19_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD19_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD19_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD19_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD19_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD19_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD19_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD19_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD19_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD19_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD19_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD19_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD19_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD19_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD19_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD19_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD19_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD19_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD19_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD19_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD19_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD19_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD19_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD19_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD19_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD19_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD19_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD19_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD19_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD19_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD19_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD19_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD19_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD19_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD19_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD19_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD19_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD19_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD19_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}

						case REG_ADDR_PAD20_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD20_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD20_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD20_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD20_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD20_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD20_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD20_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD20_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD20_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD20_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD20_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD20_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD20_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD20_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD20_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD20_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD20_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD20_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD20_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD20_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD20_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD20_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD20_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD20_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD20_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD20_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD20_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD20_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD20_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD20_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD20_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD20_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD20_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD20_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD20_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD20_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD20_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD20_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}

						case REG_ADDR_PAD21_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD21_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD21_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD21_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD21_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD21_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD21_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD21_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD21_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD21_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD21_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD21_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD21_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD21_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD21_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD21_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD21_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD21_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD21_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD21_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD21_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD21_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD21_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD21_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD21_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD21_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD21_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD21_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD21_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD21_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD21_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD21_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD21_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD21_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD21_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD21_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD21_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD21_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD21_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}

						case REG_ADDR_PAD22_POWER:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_devive_power(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD22_SET_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_cold_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD22_SET_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_heat_temp(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD22_LEW_DORP_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_drop_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD22_COLD_WARM_STATUS:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_warm_status(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD22_FREEZE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD22_FREEZE_PROTECT:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_freeze_protect(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD22_CHILD_LOCK:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_child_lock(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD22_POWER_MEMORY:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_onoff_memory(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD22_COMFORTABLE_COLD_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_comfortable_temp(virtualPort,reg_detailes);
				}        
				break;
			}
			case REG_ADDR_PAD22_COMFORTABLE_HEAT_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_heat_comfortable_temp(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD22_SET_HIGH_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_high_temp(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD22_SET_LOW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_low_temp(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD22_DEADZONE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_temp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD22_DEADZONE_LEW_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_deadzone_lewtemp(virtualPort,reg_detailes);
				}       
				break;
			}
			case REG_ADDR_PAD22_MEASURE_TEMP:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_temp(virtualPort,reg_detailes);
				}      
				break;
			}
			case REG_ADDR_PAD22_MEASURE_HUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_measure_hum(virtualPort,reg_detailes);
				}     
				break;
			}
			case REG_ADDR_PAD22_WARM_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_need(virtualPort,reg_detailes);
				} 
				break;
			}
			case REG_ADDR_PAD22_SET_FANSPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_fan_speed(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD22_CONTROL_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_control(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD22_PWM_LOW_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_low(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD22_PWM_MID_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_mid(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD22_PWM_HIGH_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_set_pwm_high(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD22_AI_COLD_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_cold_diff(virtualPort,reg_detailes);
				}    
				break;
			}
			case REG_ADDR_PAD22_AI_HEAT_COLLA_DEADZONE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_ai_heat_diff(virtualPort,reg_detailes);
				}            
				break;
			}
			case REG_ADDR_PAD22_AI_COLD_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_cold_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD22_AI_HEAT_COLLA_ENABLE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_warm_colla_enable(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD22_FAN_VAVLE_NEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_need(virtualPort,reg_detailes);
				}         
				break;
			}
			case REG_ADDR_PAD22_FAN_OUTPUT_LEVEL:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_out_speed(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD22_FAN_SPEED:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_fan_speed_output(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD22_CONTROL_OUTPUT_NUM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_control_num(virtualPort,reg_detailes);
				}           
				break;
			}
			case REG_ADDR_PAD22_TWO_CHOOSE_MODE:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_two_output_mode(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD22_BIND_FAN:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_fan(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD22_BIND_WARM:
			{
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_bind_list_warm(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD22_WARM_TYPE:
			{//辐射类型
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_type_warm_choose(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD22_ROOM_AREA:
			{//房间面积
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_room_area(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD22_LEW_TEMP_STATUS:
			{//露点状态
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_lew_dorp_temp_output(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD22_ADJUST_TEMP:
			{//校温
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_temp(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADDR_PAD22_ADJUST_HUM:
			{//校湿
				virtualPort = app_general_pull_pad_phy_port_bind_message((reg_addr-REG_ADDR_PAD_START)/256);
				if(virtualPort != PAD_NO_PHY_BIND)
				{
					app_general_push_pad_adjust_hum(virtualPort,reg_detailes);
				}          
				break;
			}
			case REG_ADRESS_REMOTE_CONTROL:
			{
				app_general_push_remote_control(reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY1:
			{
				app_general_push_remote_relay(0,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY2:
			{
				app_general_push_remote_relay(1,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY3:
			{
				app_general_push_remote_relay(2,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY4:
			{
				app_general_push_remote_relay(3,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY5:
			{
				app_general_push_remote_relay(4,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY6:
			{
				app_general_push_remote_relay(5,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY7:
			{
				app_general_push_remote_relay(6,reg_detailes);
				break;
			}	
			case REG_ADRESS_REMOTE_RELAY8:
			{
				app_general_push_remote_relay(7,reg_detailes);
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