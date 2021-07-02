//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define   MODBUS_ADDR    0x01
typedef enum
{
    mm_aircod_idle                  = 0x0000      ,//空闲状态
    mm_aircod_transmit_read_only_inf              ,//读取只读信息
    mm_aircod_receive_read_only_inf               ,
    mm_aircod_tramsimt_read_write_inf             ,//读取写读信息
    mm_aircod_receive_read_write_inf              ,
    mm_aircod_tramsimt_set_mode                   ,//设置模式
    mm_aircod_receive_set_mode                    ,
    mm_aircod_tramsimt_power                      ,//开关机
    mm_aircod_receive_power                       ,
    mm_aircod_tramsimt_power_on                   ,//开机
    mm_aircod_receive_power_on                    ,
    mm_aircod_tramsimt_power_off                  ,//关机
    mm_aircod_receive_power_off                   ,
    mm_aircod_tramsimt_cold_set_water_temp        ,//制冷回水设置温度
    mm_aircod_receive_cold_set_water_temp         ,
    mm_aircod_tramsimt_heat_set_water_temp        ,//制热回水设置温度
    mm_aircod_receive_heat_set_water_temp         ,
    mm_aircod_tramsimt_indoor_fan_control_enable  ,//室内风机控制使能
    mm_aircod_receive_indoor_fan_control_enable   ,
	mm_aircod_tramsimt_cool_backair_settemp       ,//5007制冷回风设置温度
	mm_aircod_receive_cool_backair_settemp        ,
	mm_aircod_tramsimt_hot_backair_settemp        ,//5008制热回风设置温度
	mm_aircod_receive_hot_backair_settemp         ,
	mm_aircod_tramsimt_sethumidity		   		  ,//5009相对湿度
	mm_aircod_receive_sethumidity 				  ,
	mm_aircod_tramsimt_lifewater				  ,//5010生活热水
	mm_aircod_receive_lifewater				  	  ,
	mm_aircod_tramsimt_cool_outwater_settemp	  ,//5024制冷出水设置温度
	mm_aircod_receive_cool_outwater_settemp 	  ,
	mm_aircod_tramsimt_hot_outwater_settemp	      ,//5026制热出水设置温度
	mm_aircod_receive_hot_outwater_settemp 	  	  ,
	mm_aircod_tramsimt_two_way_value_state 	      ,//5042二通阀状态
	mm_aircod_receive_two_way_value_state		  ,
	mm_aircod_tramsimt_indoor_message  		      ,//5047室内信息
 	mm_aircod_receive_indoor_message 		      ,
    mm_aircod_tramsimt_fan_need_speed  		      ,//5062室内风机实际转速
 	mm_aircod_receive_fan_need_speed 		      , 
 	mm_aircod_tramsimt_hotwater_enable  		  ,//5004热水使能
 	mm_aircod_receive_hotwater_enable 		      , 
    mm_aircod_tramsimt_watermachine_power  		  ,//5074水机开关机
 	mm_aircod_receive_watermachine_power 		  ,  
}modbus_master_state_def;

static uint32_t updataWord = 0;

#define SET_MODE_BIT                    0X0001//5001 设置模式
#define SET_POWER_BIT                   0X0002//5003 开关机
#define SET_SUPPLY_COLD_BIT             0X0004//5025 1#制冷回水设置温度
#define SET_SUPPLY_WARM_BIT             0X0008//5027 1#制热回水设置温度 
#define SET_COLD_BACKWIND_SETTEMP_BIT   0X0010//5007 2#制冷回风设置温度
#define SET_HOT_BACKWIND_SETTEMP_BIT    0X0020//5008 2#制热回风设置温度  
#define SET_HUMIDITY_BIT  				0X0040//5009 2#相对湿度设置
#define SET_LIFE_HOTWATER_BIT   		0X0080//5010 2#生活热水设置温度 
#define SET_SUPPLY_COLD_BACKWATER_BIT   0X0100//5024 1#制冷出水设置温度 
#define SET_SUPPLY_HOT_BACKWATER_BIT    0X0200//5026 1#制热出水设置温度 
#define TWO_WAY_STATE_BIT   		    0X0400//5042 室内电动二通阀状态
#define INSIDE_BACKWIND_HUMIDITY_BIT    0X0800//5047室内回风湿度值   
#define HOTWATER_ENABLE_BIT     	    0X1000//5004热水使能
#define WATER_MACHINE_POWER_BIT   	    0X2000//5074水机开关机 
#define INSIDE_FAN_NEED_SPEED_BIT       0X8000//5062室内风机实际转速

modbus_master_state_def   aircod_status = mm_aircod_idle;
/*外机只读寄存器列表*/
uint16_t aircodMesBuff_1[ARICOD_READ_ONLY_REG_NUM]={
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //0-15
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//16-31
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //32-47
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //48-63
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //64-79
            0x0000,0x0000,0x0000,0x0000,                                                                                     //80-83
                            };
                            
/*外机读写寄存器列表*/
uint16_t aircodMesBuff_5001[ARICOD_READ_WRITE_REG_NUM]={
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //0-15
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//16-31
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000, //32-47
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,//48-63
            0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,                                                 //64-72                                                                         //48-52
                                };

bool APP_pull_aricod_message(uint16_t in_reg_add,uint16_t *out_reg_value)
{//获取临时缓存里的数据   对外接口
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
{//压入数据到临时缓存里   对外接口
    if((in_reg_add >= 5001) && (in_reg_add <= (5000+ARICOD_READ_WRITE_REG_NUM)))
    {    
        static bool            debug_disable = true;
        static AirRunMode_Def  airRunmode_backup = AIR_MODE_NONE;
        static bool       power_backup = false;
        static uint16_t   hotwater_enable_backup = 0;
        static int16_t    hotTemp_set_backup;          //制冷回风设定温度(控制回风温度)
	    static int16_t    coldTemp_set_backup;         //制热回风设定温度   
        static int16_t    humidity_set_backup;         //设定湿度 
        static int16_t    set_living_water_temp_backup; //主机生活热水设定水温
        static int16_t    set_cold_water_temp_backup;   //主机制冷模式出水设定水温
        static int16_t    set_heat_water_temp_backup;   //主机制热模式出水设定水温  
        static bool       water_machine_power;
        static int16_t    inwind_temp;        
        static int16_t    inwind_hum; 
        static int16_t    outwind_temp;  
        static int16_t    outwind_hum;   
        macro_createTimer(timer_debug,timerType_millisecond,0);//调试使能延时时间
        pbc_timerClockRun_task(&timer_debug);
        if(StoRunParameter.debug_enable)
        {    
            if(water_machine_power != app_general_pull_water_machine_status())
            {
                water_machine_power = app_general_pull_water_machine_status();
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }  
            if(inwind_temp != Pull_RSS1001H_Temperature(SENSOR_OUTDOOR))
            {
                inwind_temp = Pull_RSS1001H_Temperature(SENSOR_OUTDOOR);
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(inwind_hum != Pull_RSS1001H_Humidity(SENSOR_OUTDOOR))
            {
                inwind_hum = Pull_RSS1001H_Humidity(SENSOR_OUTDOOR);
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(outwind_temp != Pull_RSS1001H_Temperature(SENSOR_BACKAIR))
            {
                outwind_temp = Pull_RSS1001H_Temperature(SENSOR_BACKAIR);
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(outwind_hum != Pull_RSS1001H_Humidity(SENSOR_BACKAIR))
            {
                outwind_hum = Pull_RSS1001H_Humidity(SENSOR_BACKAIR);
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(airRunmode_backup != StoRunParameter.airRunmode)
            {
                airRunmode_backup = StoRunParameter.airRunmode;
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(power_backup != StoRunParameter.systemPower)
            {
                power_backup = StoRunParameter.systemPower;
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(hotwater_enable_backup != StoRunParameter.hotwater_enable)
            {
                hotwater_enable_backup = StoRunParameter.hotwater_enable;
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(hotTemp_set_backup != StoRunParameter.hotTemp_set)
            {
                hotTemp_set_backup = StoRunParameter.hotTemp_set;
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(coldTemp_set_backup != StoRunParameter.coldTemp_set)
            {
                coldTemp_set_backup = StoRunParameter.coldTemp_set;
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(humidity_set_backup != StoRunParameter.humidity_set)
            {
                humidity_set_backup = StoRunParameter.humidity_set;
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(set_living_water_temp_backup != StoRunParameter.set_living_water_temp)
            {
                set_living_water_temp_backup = StoRunParameter.set_living_water_temp;
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(set_cold_water_temp_backup != StoRunParameter.set_cold_water_temp)
            {
                set_cold_water_temp_backup = StoRunParameter.set_cold_water_temp;
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            if(set_heat_water_temp_backup != StoRunParameter.set_heat_water_temp)
            {
                set_heat_water_temp_backup = StoRunParameter.set_heat_water_temp;
                pbc_reload_timerClock(&timer_debug,15000);
                debug_disable = true;
            }
            
            if(pbc_pull_timerIsOnceTriggered(&timer_debug))
            {
                debug_disable = false;
            }
        }
        else
        {
            debug_disable = true;
        }       
        if(debug_disable)
        {
            if(aircodMesBuff_5001[(in_reg_add-5001)] != in_reg_value)
            {//数据不相等时压入          
                aircodMesBuff_5001[(in_reg_add-5001)] = in_reg_value;
                switch(in_reg_add)
                {
                    case DRIVE_BOARD_SET_MODE:
                    {//模式
                        updataWord |= SET_MODE_BIT;
                        break;
                    }
                    case DRIVE_BOARD_POWER_ON_OFF:
                    {//开关机
                        updataWord |= SET_POWER_BIT;
                        break;
                    }
                    case DRIVE_BOARD_COOL_SET_TEMP:
                    {//2#制冷回风设置温度 氟机
                        updataWord |= SET_COLD_BACKWIND_SETTEMP_BIT;
                        break;
                    }
                    case DRIVE_BOARD_HOT_SET_TEMP:
                    {//2#制热回风设置温度
                        updataWord |= SET_HOT_BACKWIND_SETTEMP_BIT;
                        break;
                    }
                    case DRIVE_BOARD_HUMIDITY_SET_TEMP:
                    {//2#相对湿度设置
                        updataWord |= SET_HUMIDITY_BIT;
                        break;
                    }
                    case DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP:
                    {//2#生活热水设置温度
                        updataWord |= SET_LIFE_HOTWATER_BIT;
                        break;
                    }
                    case DRIVE_BOARD_COOL_OUTWATER_SETTEMP:
                    {//1#制冷出水设置温度  水机
                        updataWord |= SET_SUPPLY_COLD_BACKWATER_BIT;
                        break;
                    }
                    case DRIVE_BOARD_COOL_BACKWATER_SETTEMP:
                    {//1#制冷回水设置温度
                        updataWord |= SET_SUPPLY_COLD_BIT;
                        break;
                    }
                    case DRIVE_BOARD_HOT_OUTWATER_SETTEMP:
                    {//1#制热出水设置温度 
                        updataWord |= SET_SUPPLY_HOT_BACKWATER_BIT;
                        break;
                    }
                    case DRIVE_BOARD_HOT_BACKWATER_SETTEMP:
                    {//1#制热回水设置温度
                        updataWord |= SET_SUPPLY_WARM_BIT;
                        break;
                    }
                    case DRIVE_BOARD_TWO_WAY_VALUE_STATE:
                    {//室内电动二通阀状态
                        updataWord |= TWO_WAY_STATE_BIT;
                        break;
                    }
                    case DRIVE_BOARD_BACKWIND_HUMIDITY:
                    {//室内回风湿度值
                        updataWord |= INSIDE_BACKWIND_HUMIDITY_BIT;
                        break;
                    }
                    case DRIVE_BOARD_INWIND_HUMIDITY:
                    {//室内回风湿度值
                        updataWord |= INSIDE_BACKWIND_HUMIDITY_BIT;
                        break;
                    }
                    case DRIVE_BOARD_INWIND_TEMP:
                    {//室内回风湿度值
                        updataWord |= INSIDE_BACKWIND_HUMIDITY_BIT;
                        break;
                    }
                    case DRIVE_BOARD_BACKWIND_TEMP:
                    {//室内回风湿度值
                        updataWord |= INSIDE_BACKWIND_HUMIDITY_BIT;
                        break;
                    }
                    case DRIVE_BOARD_FAN_FEEDBACK_SPEED:
                    {//室内风机实际转速
                        updataWord |= INSIDE_FAN_NEED_SPEED_BIT;
                        break;
                    }
                    case DRIVE_BOARD_HOTWATER_ENABLE:
                    {//热水使能
                        updataWord |= HOTWATER_ENABLE_BIT;
                        break;
                    }
                    case DRIVE_BOARD_WATER_MACHINE_POWER:
                    {//水机开关机
                        updataWord |= WATER_MACHINE_POWER_BIT;
                        break;
                    }             
                    default:
                    {
                        break;
                    }
                }
                return true;
            }
        }
    } 
    return false;
}

bool _push_aricod_message(uint16_t in_reg_add,uint16_t in_reg_value)
{//获取外机的数据
    if((in_reg_add >= 1) && (in_reg_add <= ARICOD_READ_ONLY_REG_NUM))
    {//获取外机只读寄存器的值
       aircodMesBuff_1[(in_reg_add-1)] = in_reg_value;
       return true;
    } 
    else if((in_reg_add >= 5001) && (in_reg_add <= (5000+ARICOD_READ_WRITE_REG_NUM)))
    {//获取外机读写寄存器的值
	   if(updataWord == 0)
	   {//没有写入数据时更新 跟外机的数据保持同步
			aircodMesBuff_5001[(in_reg_add-5001)] = in_reg_value;
            switch(in_reg_add)
            {
                case DRIVE_BOARD_SET_MODE:
                {//设置模式  //不更新模式  制冷制热模式下有热水或制冷制热两种状态
                    if(StoRunParameter.debug_enable)
                    {
                        app_general_push_aircod_mode((AirRunMode_Def)aircodMesBuff_5001[0]);
                    }           
                    break;
                }
                case DRIVE_BOARD_POWER_ON_OFF:
                {//开关机
                    uint8_t power = app_general_pull_power_status();
                    if(aircodMesBuff_5001[2] != power)
                    {//不更新开关机状态 否则外机开关机影响系统开关机
                       // app_general_push_power_status(aircodMesBuff_5001[2]);
                    }    
                    break;
                }
                case DRIVE_BOARD_HOT_OUTWATER_SETTEMP:
                {//制热出水
                    if(StoRunParameter.debug_enable)
                    {
                        app_general_push_set_heat_water_temp(aircodMesBuff_5001[25]);
                    }
                }
                case DRIVE_BOARD_HOT_BACKWATER_SETTEMP:
                {//制热回水
                    int16_t temp = app_general_pull_hotbackwater_set_temp();
                    if(aircodMesBuff_5001[26] != temp)
                    {
                        app_general_push_hotbackwater_set_temp(aircodMesBuff_5001[26]);
                    }  
                    break;
                }
                case DRIVE_BOARD_COOL_SET_TEMP://制冷回风
                {
                    if(StoRunParameter.debug_enable)
                    {
                        app_general_push_aircod_cold_temp(aircodMesBuff_5001[6]);
                    }             
                    break;
                }                    
                case DRIVE_BOARD_HOT_SET_TEMP://制热回风
                {
                    if(StoRunParameter.debug_enable)
                    {
                        app_general_push_aircod_heat_temp(aircodMesBuff_5001[7]);
                    }  
                    break;
                }                  
                case DRIVE_BOARD_HUMIDITY_SET_TEMP://相对湿度设置
                {
                    if(StoRunParameter.debug_enable)
                    {
                        app_general_push_aircod_humidity(aircodMesBuff_5001[8]/10);
                    }  
                    break;
                }                 
                case DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP://生活热水设置温度
                {
                    if(StoRunParameter.debug_enable)
                    {
                        app_general_push_set_living_water_temp(aircodMesBuff_5001[9]);
                    }                 
                    break;
                }                     
                case DRIVE_BOARD_COOL_OUTWATER_SETTEMP://制冷出水
                {
                    if(StoRunParameter.debug_enable)
                    {
                        app_general_push_water_machine_status(aircodMesBuff_5001[73]);
                    } 
                    break;
                }
                case DRIVE_BOARD_WATER_MACHINE_POWER://水机开关机
                {
                    if(StoRunParameter.debug_enable)
                    {
                        app_general_push_set_cold_water_temp(aircodMesBuff_5001[23]);
                    } 
                    break;
                }
                case DRIVE_BOARD_COOL_BACKWATER_SETTEMP://制冷回水
                {
                    app_general_push_coolbackwater_set_temp(aircodMesBuff_5001[24]);
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
    return false;
}
void App_push_aircod_buff(uint16_t RegAddr,uint8_t RegLength)
{
    uint16_t regDetails;
    while(RegLength)
    {
        if(mde_pull_mRtu_receiveReg(MASTER_COMP,RegAddr,&regDetails))
        {
            _push_aricod_message((RegAddr+1),regDetails);
        }	
		switch(RegAddr)
		{
			default:
			{              				
				break;
			}
		}
        RegAddr++;
        RegLength--;
    }
}

static void app_push_send_reg_aircod(uint16_t in_regAddr,uint8_t in_regLength)
{
    uint16_t regDetails;
    while(in_regLength)
    {
        APP_pull_aricod_message(in_regAddr,&regDetails);
        mde_push_mRtu_master_sendReg(MASTER_COMP,in_regAddr-1,regDetails);
        in_regAddr++;
        in_regLength--;
    }
}

void app_master_comp_task(void)
{
    mde_mRtu_master_task();
    macro_createTimer(ReadInterval,timerType_millisecond,1000);
	macro_createTimer(blinkDelay,timerType_millisecond,0);
    macro_createTimer(updata_delay,timerType_millisecond,0);
    pbc_timerClockRun_task(&ReadInterval);
	pbc_timerClockRun_task(&blinkDelay);
    pbc_timerClockRun_task(&updata_delay);
    uint16_t regDetails;
    uint16_t reg_addr;
    uint16_t reg_length;
	if(pbc_pull_timerIsCompleted(&blinkDelay))
	{
		mde_led_off(LED_2);
	}
    switch(aircod_status)
    {
        case mm_aircod_idle:
        {         
			if(updataWord)
			{
				pbc_reload_timerClock(&blinkDelay,5000);//闪动5s
				mde_led_blink(LED_2,5,5);
                if(pbc_pull_timerIsCompleted(&updata_delay))
                {
                    if(updataWord & SET_MODE_BIT)
                    {
                        aircod_status = mm_aircod_tramsimt_power_off;
                    }
                    else if(updataWord & SET_POWER_BIT)
                    {
                        aircod_status = mm_aircod_tramsimt_power;
                    }
                    else if(updataWord & SET_SUPPLY_COLD_BIT)
                    {
                        aircod_status = mm_aircod_tramsimt_cold_set_water_temp;
                    }
                    else if(updataWord & SET_SUPPLY_WARM_BIT)
                    {
                        aircod_status = mm_aircod_tramsimt_heat_set_water_temp;
                    }
                    else if(updataWord & SET_COLD_BACKWIND_SETTEMP_BIT)//5007
                    {
                        aircod_status = mm_aircod_tramsimt_cool_backair_settemp;
                    }
                    else if(updataWord & SET_HOT_BACKWIND_SETTEMP_BIT)//5008
                    {
                        aircod_status = mm_aircod_tramsimt_hot_backair_settemp;
                    }
                    else if(updataWord & SET_HUMIDITY_BIT)//5009
                    {
                        aircod_status = mm_aircod_tramsimt_sethumidity;
                    }
                    else if(updataWord & SET_LIFE_HOTWATER_BIT)//5010
                    {
                        aircod_status = mm_aircod_tramsimt_lifewater;
                    }
                    else if(updataWord & SET_SUPPLY_COLD_BACKWATER_BIT)//5024
                    {
                        aircod_status = mm_aircod_tramsimt_cool_outwater_settemp;
                    }
                    else if(updataWord & SET_SUPPLY_HOT_BACKWATER_BIT)//5026
                    {
                        aircod_status = mm_aircod_tramsimt_hot_outwater_settemp;
                    }
                    else if(updataWord & TWO_WAY_STATE_BIT)//5042
                    {
                        aircod_status = mm_aircod_tramsimt_two_way_value_state;
                    }
                    else if(updataWord & INSIDE_BACKWIND_HUMIDITY_BIT)//5047~5050 10指令写4个数据
                    {
                        aircod_status = mm_aircod_tramsimt_indoor_message;
                    }
                    else if(updataWord & INSIDE_FAN_NEED_SPEED_BIT)
                    {
                        aircod_status = mm_aircod_tramsimt_fan_need_speed;
                    }
					else if(updataWord & HOTWATER_ENABLE_BIT)
					{
						aircod_status = mm_aircod_tramsimt_hotwater_enable;
					}
                    else if(updataWord & WATER_MACHINE_POWER_BIT)
					{
						aircod_status = mm_aircod_tramsimt_watermachine_power;
					}
                }				
			}
			else
			{
				if(pbc_pull_timerIsCompleted(&ReadInterval))
				{
					pbc_reload_timerClock(&ReadInterval,3000);
					aircod_status = mm_aircod_transmit_read_only_inf;
				}
			}
            break;
        }
        case mm_aircod_transmit_read_only_inf:
        {//读取只读信息
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                mde_mRtu_master_cmd0x04_transmit(MASTER_COMP,MODBUS_ADDR,0x0000,ARICOD_READ_ONLY_REG_NUM);
                aircod_status = mm_aircod_receive_read_only_inf;
            }
            break;
        }
        case mm_aircod_receive_read_only_inf:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                aircod_status = mm_aircod_tramsimt_read_write_inf;
                pbc_reload_timerClock(&ReadInterval,1000);
                mde_pull_mRtu_register_add_len(MASTER_COMP,&reg_addr,&reg_length);
                App_push_aircod_buff((reg_addr),reg_length);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                aircod_status = mm_aircod_tramsimt_read_write_inf;
                pbc_reload_timerClock(&ReadInterval,300);
            }
            break;
        }
        case mm_aircod_tramsimt_read_write_inf:
        {//读取写读信息
            if(pbc_pull_timerIsCompleted(&ReadInterval))
            {
                if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
                {
                    mde_mRtu_master_cmd0x03_transmit(MASTER_COMP,MODBUS_ADDR,5000,ARICOD_READ_WRITE_REG_NUM);
                    aircod_status = mm_aircod_receive_read_write_inf;
                }
            }         
            break;
        }
        case mm_aircod_receive_read_write_inf:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                aircod_status = mm_aircod_idle;
                mde_pull_mRtu_register_add_len(MASTER_COMP,&reg_addr,&reg_length);
                App_push_aircod_buff((reg_addr),reg_length);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                aircod_status = mm_aircod_idle;
            }
            break;
        }
        case mm_aircod_tramsimt_power_off:
        {//设置模式-关机
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_POWER_ON_OFF-1),0x00);
                aircod_status = mm_aircod_receive_power_off;
            }
            break;
        }
        case mm_aircod_receive_power_off:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_MODE_BIT);
                aircod_status = mm_aircod_tramsimt_set_mode;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_MODE_BIT);
                aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            break;
        }
        case mm_aircod_tramsimt_set_mode:
        {//设置模式
            if(pbc_pull_timerIsCompleted(&updata_delay))
            {
                if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
                {
                    APP_pull_aricod_message(DRIVE_BOARD_SET_MODE,&regDetails);
                    mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_SET_MODE-1),regDetails);
                    aircod_status = mm_aircod_receive_set_mode;
                }
            }
            break;
        }
        case mm_aircod_receive_set_mode:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                aircod_status = mm_aircod_tramsimt_power_on;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            break;
        }
        case mm_aircod_tramsimt_power_on:
        {//设置模式-开机
            if(pbc_pull_timerIsCompleted(&updata_delay))
            {
                if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
                {
                    mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_POWER_ON_OFF-1),0x01);
                    aircod_status = mm_aircod_receive_power_on;
                }
            }      
            break;
        }
        case mm_aircod_receive_power_on:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            break;
        }
        case mm_aircod_tramsimt_power:
        {//开关机
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_POWER_ON_OFF,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_POWER_ON_OFF-1),regDetails);
                aircod_status = mm_aircod_receive_power;
            }
            break;
        }
        case mm_aircod_receive_power:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_POWER_BIT);
                aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_POWER_BIT);
                aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            break;
        }
        case mm_aircod_tramsimt_cold_set_water_temp:
        {//制冷回水设置温度
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_COOL_BACKWATER_SETTEMP,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_COOL_BACKWATER_SETTEMP-1),regDetails);
                aircod_status = mm_aircod_receive_cold_set_water_temp;
            }
            break;
        }
        case mm_aircod_receive_cold_set_water_temp:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_SUPPLY_COLD_BIT);
                aircod_status = mm_aircod_idle;
                 pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_SUPPLY_COLD_BIT);
                aircod_status = mm_aircod_idle;
                 pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            break;
        }
        case mm_aircod_tramsimt_heat_set_water_temp:
        {//制热回水设置温度
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_HOT_BACKWATER_SETTEMP,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_HOT_BACKWATER_SETTEMP-1),regDetails);
                aircod_status = mm_aircod_receive_heat_set_water_temp;
            }
            break;
        }
        case mm_aircod_receive_heat_set_water_temp:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_SUPPLY_WARM_BIT);
                aircod_status = mm_aircod_idle;
                 pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_SUPPLY_WARM_BIT);
                aircod_status = mm_aircod_idle;
                 pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            break;
        }
		case mm_aircod_tramsimt_cool_backair_settemp: //5007制冷回风设置温度
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_COOL_SET_TEMP,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_COOL_SET_TEMP-1),regDetails);
                aircod_status = mm_aircod_receive_cool_backair_settemp;
            }
			break;
        }         
		case mm_aircod_receive_cool_backair_settemp:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_COLD_BACKWIND_SETTEMP_BIT);
                aircod_status = mm_aircod_idle;
                 pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_COLD_BACKWIND_SETTEMP_BIT);
                aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
			break;
        }
		case mm_aircod_tramsimt_hot_backair_settemp:  //5008制热回风设置温度
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_HOT_SET_TEMP,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_HOT_SET_TEMP-1),regDetails);
                aircod_status = mm_aircod_receive_hot_backair_settemp;
            }
			break;
        }		
		case mm_aircod_receive_hot_backair_settemp: 
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_HOT_BACKWIND_SETTEMP_BIT);
                aircod_status = mm_aircod_idle;
                 pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_HOT_BACKWIND_SETTEMP_BIT);
                aircod_status = mm_aircod_idle;
                 pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
			break;
        }         
		case mm_aircod_tramsimt_sethumidity: //5009相对湿度
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_HUMIDITY_SET_TEMP,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_HUMIDITY_SET_TEMP-1),regDetails);
                aircod_status = mm_aircod_receive_sethumidity;
            }
			break;
        }			
		case mm_aircod_receive_sethumidity: 
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_HUMIDITY_BIT);
                aircod_status = mm_aircod_idle;
                 pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
            else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
            {
                updataWord &= (~SET_HUMIDITY_BIT);
                aircod_status = mm_aircod_idle;
                 pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
            }
			break;
        }	
		case mm_aircod_tramsimt_lifewater: //5010生活热水
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_LIFE_HOTWATER_SET_TEMP-1),regDetails);
                aircod_status = mm_aircod_receive_lifewater;
            }
			break;
        }			
		case mm_aircod_receive_lifewater:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~SET_LIFE_HOTWATER_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~SET_LIFE_HOTWATER_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			break;
        }	
		case mm_aircod_tramsimt_cool_outwater_settemp: //5024制冷出水设置温度
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_COOL_OUTWATER_SETTEMP,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_COOL_OUTWATER_SETTEMP-1),regDetails);
                aircod_status = mm_aircod_receive_cool_outwater_settemp;
            }
			break;
        }		
		case mm_aircod_receive_cool_outwater_settemp: 
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~SET_SUPPLY_COLD_BACKWATER_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~SET_SUPPLY_COLD_BACKWATER_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			break;
        }
		case mm_aircod_tramsimt_hot_outwater_settemp: //5026制热出水设置温度
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_HOT_OUTWATER_SETTEMP,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_HOT_OUTWATER_SETTEMP-1),regDetails);
                aircod_status = mm_aircod_receive_hot_outwater_settemp;
            }
			break;
        }			
		case mm_aircod_receive_hot_outwater_settemp: 
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~SET_SUPPLY_HOT_BACKWATER_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~SET_SUPPLY_HOT_BACKWATER_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			break;
        }
		case mm_aircod_tramsimt_two_way_value_state: //5042二通阀状态
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_TWO_WAY_VALUE_STATE,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_TWO_WAY_VALUE_STATE-1),regDetails);
                aircod_status = mm_aircod_receive_two_way_value_state;
            }
			break;
        }			
		case mm_aircod_receive_two_way_value_state:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~TWO_WAY_STATE_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~TWO_WAY_STATE_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			break;
        }		
		case mm_aircod_tramsimt_indoor_message: //5047室内信息
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_INDOOR_MESSAGE,&regDetails);
				
                mde_mRtu_master_cmd0x10_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_INDOOR_MESSAGE-1),4);
                app_push_send_reg_aircod(DRIVE_BOARD_INDOOR_MESSAGE,4);
                aircod_status = mm_aircod_receive_indoor_message;
            }
			break;
        }			
		case mm_aircod_receive_indoor_message: 
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~INSIDE_BACKWIND_HUMIDITY_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~INSIDE_BACKWIND_HUMIDITY_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			break;
        }			
        case mm_aircod_tramsimt_fan_need_speed: //5068室内风机实际转速
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_FAN_FEEDBACK_SPEED,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_FAN_FEEDBACK_SPEED-1),regDetails);
                aircod_status = mm_aircod_receive_fan_need_speed;
            }
			break;
        }		
		case mm_aircod_receive_fan_need_speed: 
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~INSIDE_FAN_NEED_SPEED_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~INSIDE_FAN_NEED_SPEED_BIT);
				aircod_status = mm_aircod_idle;
                pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			break;
        }		
		case mm_aircod_tramsimt_hotwater_enable://热水使能
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_HOTWATER_ENABLE,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_HOTWATER_ENABLE-1),regDetails);
                aircod_status = mm_aircod_receive_hotwater_enable;
            }
			break;
        }			
		case mm_aircod_receive_hotwater_enable:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~HOTWATER_ENABLE_BIT);
				aircod_status = mm_aircod_idle;
				pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~HOTWATER_ENABLE_BIT);
				aircod_status = mm_aircod_idle;
				pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			break;	
        }
        case mm_aircod_tramsimt_watermachine_power://水机开关机
        {
            if(mmRunS_idle == mde_mRtu_master_run_status(MASTER_COMP))
            {
                APP_pull_aricod_message(DRIVE_BOARD_WATER_MACHINE_POWER,&regDetails);
                mde_mRtu_master_cmd0x06_transmit(MASTER_COMP,MODBUS_ADDR,(DRIVE_BOARD_WATER_MACHINE_POWER-1),regDetails);
                aircod_status = mm_aircod_receive_watermachine_power;
            }
			break;
        }			
		case mm_aircod_receive_watermachine_power:
        {
            if(mRtuS_master_complete == mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~WATER_MACHINE_POWER_BIT);
				aircod_status = mm_aircod_idle;
				pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			else if((mRtuS_master_timeout | mRtuS_master_poterr) & mde_mRtu_master_reveive_status(MASTER_COMP))
			{
				updataWord &= (~WATER_MACHINE_POWER_BIT);
				aircod_status = mm_aircod_idle;
				pbc_reload_timerClock(&updata_delay,UPDATA_DELAY);
			}
			break;	
        } 		 		
        default:
        {
            break;
        }

    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
