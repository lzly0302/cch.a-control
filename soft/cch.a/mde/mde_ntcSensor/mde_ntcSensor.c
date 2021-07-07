//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include ".\mde_ntcSensor.h"
#include "..\..\pbc\pbc_sysTick\pbc_sysTick.h"
//------------------------------E N D-------------------------------------------
typedef enum
{
     NtcSen_Free              =0,     //空闲
     NtcSen_Start             =1,     //开始
     NtcSen_ChannelSelect     =2,     //通道选择
     NtcSen_Conversion        =3,     //转换
     NtcSen_MultipleSample    =4,     //多次采样
     NtcSen_Finished          =5,     //完成
     NtcSen_Error             =6,     //出错
}NtcSenRunStatus_Def;
//-----------------------------------------------------------------------------
typedef struct
{                        
    NtcSenRunStatus_Def  SensorRunStatus;       //传感器运行状态
    uint8_t  ReadCount;                           //读取计算
    uint16_t Adc12DRMT ;                          //16个数据累计值，Max 0xFFF0
    uint16_t Adc12Value;                          //12Bit的ADC值
    timerClock_def  timeOutDelay;
    timerClock_def  channelClockDelay;
    void(*SelectAdcChannel)(void);           //选择ADC的通道
}NtcSensorParameter_Def;


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***********************函数使用的内部变量*************************************
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//*********************3380_____-20℃-119℃*************************************
const uint16_t B3380_10k_Table[140]=
{    //10k 上拉电阻
3568,3546,3523,3499,3475,3449,3424,3397,3370,3342,    //-20~-11
3314,3285,3255,3225,3194,3162,3130,3098,3064,3031,    //-10~-1,递减表
2996,2962,2927,2891,2855,2818,2781,2744,2706,2669,    //0~9
2630,2592,2553,2515,2476,2437,2398,2359,2319,2280,    //10~19
2241,2202,2163,2125,2086,2048,2009,1971,1933,1896,    //20~29
1859,1822,1785,1749,1714,1678,1643,1607,1575,1541,    //30~39
1508,1475,1443,1411,1379,1349,1319,1289,1259,1231,    //40~49
1203,1175,1148,1122,1096,1070,1045,1021, 997, 973,    //50~59
 950, 927, 905, 883, 862, 842, 822, 802, 783, 764,    //60~69
 746, 728, 710, 693, 677, 661, 645, 629, 614, 599,    //70~79
 585, 571, 558, 544, 531, 518, 506, 495, 483, 471,    //80~89
 460, 449, 439, 428, 418, 409, 399, 389, 381, 372,    //90~99
 363, 354, 346, 339, 331, 323, 316, 308, 301, 295,    //100~109
 288, 282, 275, 269, 263, 257, 251, 246, 241, 236,    //110~119          
};

/*根据不同温度下的毫米汞高计算露点温度*/
const uint16_t temp_mmHg[60] = {
    458,493,530,570,610,654,702,752,805,861,//0-9
    921,985,1052,1123,1200,1279,1364,1454,1548,1648,//10-19
    1754,1866,1984,2108,2239,2377,2522,2675,2836,3006,//20-29
    3184,3371,3568,3775,3992,4220,4459,4710,4972,5248,//30-39
    5536,5838,6154,6485,6831,7192,7571,7965,8378,8809,//40-49
    9258,9728,10217,10727,11259,11814,12392,12993,13619,14271,//50-59
};
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//****************************露点温度计算******************************************
/*露点温度查表*/
int16_t mde_drop_temp_search_mmHg(uint16_t _In_Adc_AvgValue)
{
    const uint16_t *pResistorTable;
    uint16_t  table_high = 0, table_low = 0;
    int16_t  ret_tempera = 0;            //返回温度
    int16_t  remain = 0;                 //小数部分
    int16_t  DivRm;

    pResistorTable=(const uint16_t*)temp_mmHg;
    if(_In_Adc_AvgValue<pResistorTable[0])          //查表
    {
        ret_tempera = 0;
    }
    else if(_In_Adc_AvgValue>pResistorTable[59])
    {
       ret_tempera = 600;
    }
    else
    {
        while(ret_tempera<59)       
        {
            if(_In_Adc_AvgValue<=pResistorTable[ret_tempera])
            {
                break;
            }
            else
            {
                ret_tempera++;
            }
        }
        if(ret_tempera == 0)
        {
            remain = 0;
        }
        else
        {
            table_high = pResistorTable[ret_tempera];
            table_low  = pResistorTable[ret_tempera-1];
            remain     = (_In_Adc_AvgValue-table_low)*10/(table_high-table_low);
            DivRm      = ((_In_Adc_AvgValue-table_low)*10)%(table_high-table_low);
            if(DivRm>((table_high-table_low)/2))
            {
                remain=0;
            }
            else
            {
                remain=5; 
            }
        }
        ret_tempera = ret_tempera*10;
        ret_tempera-=remain;           //小数部分
    }
    return(ret_tempera);
} 

int16_t mde_pull_drop_temp(int16_t in_measureTemp,uint16_t in_measureHum)
{//计算露点温度
    int16_t dew_temp = 0;
    uint16_t mmHg = 0;
    uint16_t dewTemp = 0;
    if(in_measureTemp < 0)
    {
        in_measureTemp = 0;
    }
    if(in_measureTemp>= 590)
    {
        in_measureTemp = 590;
    }
    if((in_measureTemp %10)>5)
    {
        dew_temp = (in_measureTemp/10)+1;
    }
    else
    {
        dew_temp = (in_measureTemp/10);
    }
    
    mmHg = ((uint32_t)(temp_mmHg[dew_temp]*in_measureHum))/100;
    dewTemp = mde_drop_temp_search_mmHg(mmHg);
    return dewTemp;
} 

void NTCSensorTask(NtcSensorParameter_Def *Me)
{
    NtcSenRunStatus_Def  RunStausRead;
    uint16_t CalculateTemp;
    pbc_timerClockRun_task(&Me->channelClockDelay);
    pbc_timerClockRun_task(&Me->timeOutDelay);
    if(pbc_pull_timerIsCompleted(&Me->timeOutDelay))
    {
        Me->timeOutDelay.timClock = 500;
        Me->SensorRunStatus=NtcSen_Error;
    }
    do
    {
        RunStausRead=Me->SensorRunStatus;
        
        switch(Me->SensorRunStatus)
        {
            case NtcSen_Free:
            {
                break;
            }
            case NtcSen_Start:
            {
                Me->SelectAdcChannel();
                Me->timeOutDelay.timClock = 500;
                Me->channelClockDelay.timClock = 10;
                Me->SensorRunStatus=NtcSen_ChannelSelect;
                break;
            }
            case NtcSen_ChannelSelect:
            {
                if(0 == Me->channelClockDelay.timClock)
                {
                    Me->SensorRunStatus=NtcSen_Conversion;
                    BSP_ADC12_Start();
                }
                break;
            }
            case NtcSen_Conversion:
            {
                if(BSP_ADC1_SampleOnceFinish())
                {
                    BSP_ADC1_GetValue();  //
                    Me->ReadCount=0;
                    Me->Adc12DRMT=0; 
                    Me->SensorRunStatus=NtcSen_Conversion;
                    Me->SensorRunStatus=NtcSen_MultipleSample;
                    BSP_ADC12_Start();
                }
                break;
            }
            case NtcSen_MultipleSample:
            {
                 if(BSP_ADC1_SampleOnceFinish())
                {
                    Me->Adc12DRMT+=BSP_ADC1_GetValue();
                    Me->ReadCount++;
                    if(Me->ReadCount>15)  //16 Times Sample
                    {
                        Me->Adc12Value=Me->Adc12DRMT/16;
                        CalculateTemp=Me->Adc12DRMT%16;
                        if(CalculateTemp>7)         //小数处理方法
                        {
                            Me->Adc12Value++;
                        }
                        Me->SensorRunStatus=NtcSen_Finished;
                    }
                    else
                    {
                        BSP_ADC12_Start();
                    }
                }
                break;
            }
            case NtcSen_Finished:
            {
                break;
            }
            case NtcSen_Error:
            {
                break;
            }
            default:
            {
                break;
            }
        }
    }while(RunStausRead!=Me->SensorRunStatus);
}

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//*************************ADC对温度值查表**************************************
int16_t Mod_SearchNTCTable(SensorType_Def SenType,uint16_t _In_Adc_AvgValue)
{
    const uint16_t *pResistorTable;
    uint16_t  table_high = 0, table_low = 0;
    int16_t  ret_tempera = 0;            //返回温度
    int16_t  remain = 0;                 //小数部分
    int16_t  DivRm;

    if(B_3380_10K==SenType)
    {
        pResistorTable=(const uint16_t*)B3380_10k_Table;
    }
    else
    {
        while(1);
    }

    if(_In_Adc_AvgValue>pResistorTable[0])          //查表
    {
        _In_Adc_AvgValue=pResistorTable[0];
    }
    if(_In_Adc_AvgValue<pResistorTable[139])
    {
       _In_Adc_AvgValue = pResistorTable[139];
    }
    while(ret_tempera<139)       
    {
        if(_In_Adc_AvgValue>=pResistorTable[ret_tempera])
        {
            break;
        }
        else
        {
            ret_tempera++;
        }
    }
    if(ret_tempera == 0)
    {
        remain = 0;
    }
    else
    {
        table_high = pResistorTable[ret_tempera-1];
        table_low  = pResistorTable[ret_tempera];
        remain     = (_In_Adc_AvgValue-table_low)*10/(table_high-table_low);
        DivRm      = ((_In_Adc_AvgValue-table_low)*10)%(table_high-table_low);
        if(DivRm>((table_high-table_low)>>1))
        {
            remain+=1;
        }
    }
    ret_tempera = (ret_tempera-20)*10;
    ret_tempera-=remain;           //小数部分
    return(ret_tempera);
}
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include ".\sod_ntcSensor.h"
//****************************返回温度值****************************************
int16_t mde_NTCSensor_GetTemperature(uint8_t in_solidNum,SensorType_Def in_SenType,Resolution_Def in_Res_Degree)
{
    int16_t Temperature = 0;
    int16_t Temporary = 0;
    if(in_solidNum < max_solid)
    {
        if(((mde_sensor[in_solidNum].Adc12Value)>0x0fd2)||((mde_sensor[in_solidNum].Adc12Value)<0x0008))
        {
            return(SensorError);
        }
        else
        {
            Temperature=Mod_SearchNTCTable(in_SenType,mde_sensor[in_solidNum].Adc12Value);
        }

        if(Res01_Degree==in_Res_Degree)
        {
        }
        else if(Res05_Degree==in_Res_Degree)
        {
            Temporary=Temperature;
            while(1)
            {
                if(Temperature<0)
                {
                    if(Temporary>-5)
                    {
                        if(Temporary>-3)
                        {
                            Temperature=Temperature-Temporary;
                        }
                        else
                        {
                            Temperature=Temperature-(5+Temporary);
                        }
                        break;
                    }
                    else
                    {
                        Temporary+=5;
                    }
                }
                else
                {
                    if(Temporary<5)
                    {
                        if(Temporary<3)
                        {
                            Temperature=Temperature-Temporary;
                        }
                        else
                        {
                            Temperature=Temperature+(5-Temporary);
                        }
                        break;
                    }
                    else
                    {
                        Temporary-=5;
                    }
                }
            }
        }
        else if(Res10_Degree==in_Res_Degree)
        {
            Temporary=Temperature;
            while(1)
            {
                if(Temperature<0)
                {
                    if(Temporary>-10)
                    {
                        if(Temporary>-5)
                        {
                            Temperature=Temperature-Temporary;
                        }
                        else
                        {
                            Temperature=Temperature-(10+Temporary);
                        }
                        break;
                    }
                    else
                    {
                        Temporary+=10;
                    }
                }
                else
                {
                    if(Temporary<10)
                    {
                        if(Temporary<5)
                        {
                            Temperature=Temperature-Temporary;
                        }
                        else
                        {
                            Temperature=Temperature+(10-Temporary);
                        }
                        break;
                    }
                    else
                    {
                        Temporary-=10;
                    }
                }
            }
        }
        return(Temperature);
    }
    else
    {
        while(1);
    }
}
//------------------------------E N D-------------------------------------------
//****************************返回电压值****************************************
int16_t mde_NTCSensor_pull_feedback_degree(void)
{
    return 0;
}
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//****************************返回温度值****************************************
void mde_NTCSensor_ScanTask(void)
{
    static uint8_t  SensorChannel = 0;
    static bool cfged = false;
    uint8_t i = 0;
    if(cfged)
    {
        for(i = 0; i < max_solid;i++)
        {
            NTCSensorTask(&mde_sensor[i]);
        }
        if(NtcSen_Free==mde_sensor[SensorChannel].SensorRunStatus)
        {
            mde_sensor[SensorChannel].SensorRunStatus=NtcSen_Start;
        }
        else if(NtcSen_Finished==mde_sensor[SensorChannel].SensorRunStatus)
        {
            mde_sensor[SensorChannel].SensorRunStatus=NtcSen_Free;
            SensorChannel++;
            if(SensorChannel >= max_solid)
            {
                SensorChannel = 0;
            }
        }
        else if(NtcSen_Error==mde_sensor[SensorChannel].SensorRunStatus)
        {
            mde_sensor[SensorChannel].SensorRunStatus=NtcSen_Free;
            SensorChannel++;
            if(SensorChannel >= max_solid)
            {
                SensorChannel = 0;
            }
        }
    }
    else
    {
        cfged = true;
        mde_ntc_sensor_solid_cfg();
    }
    
    
}
//------------------------------E N D-------------------------------------------


//-----------------------MOD_NTC3380.c--END------------------------------------