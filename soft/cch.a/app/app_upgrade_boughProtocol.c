//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//负责Bough Easy Upgrade Protocol的报文处理,任务。
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\APP_Cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define BGPTCL_EasyUpagrde         0xD002  //简易固件升级协议
#define BGPTCL_debug               0xDFFF  //
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define BGEUCMD_QuerySalveStatus   0x01
#define BGEUCMD_EnterBoot          0x02
#define BGEUCMD_StrUpgrade_map     0x03
#define BGEUCMD_ResumeUpgrade_map  0x04
#define BGEUCMD_TransferFile       0x05

#define BGEUCMD_ErrorReport        0xFE
//-------------------------------------------------------------------------------------------------
#define BGEUERR_NoneError          0x00
#define BGEUERR_Length             0x01
#define BGEUERR_Version            0x02
#define BGEUERR_Command            0x03
#define BGEUERR_FileMapCheckSum    0x04
#define BGEUERR_FileCheckSum       0x05
#define BGEUERR_BlockNumber        0x06
#define BGEUERR_Fireware           0x07
#define BGEUERR_Other              0xFE
//--------------------------------------------------------------------------------------------------
#define BGEUSTS_None               0x00
#define BGEUSTS_NotInBoot          0x01
#define BGEUSTS_Boot               0x10
//#define BGEUSTS_QueryFileMap       0x11
#define BGEUSTS_QueryFile          0x12
#define BGEUSTS_UpgradeFinish      0x1F
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define THE_VER      0x01
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
    ugd_esay_staue_idle         = 0x00,
    ugd_esay_staue_wait_ms      = 0x01,
    ugd_esay_staue_start_answer = 0x02,
    ugd_esay_staue_cpl_answer   = 0x03,
    ugd_esay_staue_backoff      = 0x04,
    ugd_esay_staue_backoffing   = 0x05,
}ugd_esay_staues_def;
//------------------------------------------------------------------------------
static ugd_esay_staues_def ugd_esay_staues;
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct
{
   sdt_int8u  src_addr[6];
   sdt_int8u  dst_addr[6];
   sdt_int8u  answer_length;
   sdt_int8u  answer_payload[6];
}answer_oper_def;
//------------------------------------------------------------------------------
static answer_oper_def  answer_oper;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//名称: Bough 错误应答
//功能: 
//入口: 
//      _Out_pPayload       应答内容,          ---->>
//      _In_ErrCode          错误号            <<----
//出口: 应答的数据长度,
//------------------------------------------------------------------------------
void Bough_AnswerErrorReport(sdt_int8u _In_ErrCode)
{
    answer_oper.answer_payload[0] = THE_VER;              //Version
    answer_oper.answer_payload[1] = BGEUCMD_ErrorReport;  //Command
    answer_oper.answer_payload[2] = BGEUSTS_None;         //Status
    answer_oper.answer_payload[3] = _In_ErrCode;          //Error Code
    answer_oper.answer_length = 4;
}
sdt_int16u random_backoff_time(void)
{
    return 2000;
   // return(pull_mde_one_random_data());
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//名称: Bough 简易升级报文协议处理函数
//功能: 
//入口: 
//      _In_pReceiveData     接收到的数据指针,         <<----
//     _In_TheAddr           本机链路地址              <<----
//      _Out_pTransmitData   应答数据指针,             ---->>
//      _Out_DevEnterBoot    进入Boot,sdt_true --需要进入   ---->>
//出口: 是否有应答数据,sdt_true--有应答数据
//-------------------------------------------------------------------------------------------------
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//简易升级任务
//------------------------------------------------------------------------------
void app_upgrade_easy_task(void)
{
    mde_upgrade_files_task();
    macro_createTimer(timer_backoff,timerType_millisecond,0);
    ugd_esay_staues_def rd_ugd_esay_staues;
    
    
    pbc_timerClockRun_task(&timer_backoff);

    do
    {
        rd_ugd_esay_staues = ugd_esay_staues;
        switch(ugd_esay_staues)
        {
            case ugd_esay_staue_idle:
            {
                ugd_esay_staues = ugd_esay_staue_wait_ms;
                break;
            }
            case ugd_esay_staue_wait_ms:
            {
                break;
            }
            case ugd_esay_staue_start_answer:
            {
                if(pull_bough_link_is_busy(1))
                {
                    ugd_esay_staues = ugd_esay_staue_backoff;
                }
                else
                {
                  
                    bgk_comm_buff_def* p_tx_bgk_buff;
                    
                    p_tx_bgk_buff = pull_bough_message_pBuff(1);
                    p_tx_bgk_buff->LinkSrcAddr[0] = answer_oper.src_addr[0];
                    p_tx_bgk_buff->LinkSrcAddr[1] = answer_oper.src_addr[1];
                    p_tx_bgk_buff->LinkSrcAddr[2] = answer_oper.src_addr[2];
                    p_tx_bgk_buff->LinkSrcAddr[3] = answer_oper.src_addr[3];
                    p_tx_bgk_buff->LinkSrcAddr[4] = answer_oper.src_addr[4];
                    p_tx_bgk_buff->LinkSrcAddr[5] = answer_oper.src_addr[5];
                    
                    p_tx_bgk_buff->LinkDstAddr[0] = answer_oper.dst_addr[0];
                    p_tx_bgk_buff->LinkDstAddr[1] = answer_oper.dst_addr[1];
                    p_tx_bgk_buff->LinkDstAddr[2] = answer_oper.dst_addr[2];
                    p_tx_bgk_buff->LinkDstAddr[3] = answer_oper.dst_addr[3];
                    p_tx_bgk_buff->LinkDstAddr[4] = answer_oper.dst_addr[4];
                    p_tx_bgk_buff->LinkDstAddr[5] = answer_oper.dst_addr[5];     
                    p_tx_bgk_buff->ProcotolType = BGPTCL_EasyUpagrde;
                    p_tx_bgk_buff->PayloadLength = answer_oper.answer_length;
                    
                    sdt_int8u i;
                    for(i = 0;i<answer_oper.answer_length;i++)
                    {
                        p_tx_bgk_buff->Payload[i] = answer_oper.answer_payload[i];
                    }
                    push_active_one_message_transmit(1,sdt_false);
                    ugd_esay_staues = ugd_esay_staue_cpl_answer;
                }
                break;
            }
            case ugd_esay_staue_cpl_answer:
            {
                bgk_trans_mon_def rd_monitor;
                rd_monitor = pull_bough_transmit_monitor(1);
                if(bgk_trans_mon_conflict == rd_monitor)
                {
                    ugd_esay_staues = ugd_esay_staue_backoff;
                }
                else if(bgk_trans_mon_complete == rd_monitor)
                {
                    ugd_esay_staues = ugd_esay_staue_wait_ms;
                }
                else if(bgk_trans_mon_error == rd_monitor)
                {
                    ugd_esay_staues = ugd_esay_staue_wait_ms;
                }
                break;
            }
            case ugd_esay_staue_backoff:
            {
              //  pbc_reload_timerClock(&timer_backoff,random_backoff_time());//随机避退时间
                ugd_esay_staues = ugd_esay_staue_backoffing;
                break;
            }
            case ugd_esay_staue_backoffing:
            {
                if(pbc_pull_timerIsCompleted(&timer_backoff))
                {
                    ugd_esay_staues = ugd_esay_staue_start_answer;
                }
                break;
            }
            default:
            {
                ugd_esay_staues = ugd_esay_staue_idle;
                break;
            }
        }
    }while(rd_ugd_esay_staues != ugd_esay_staues);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Bough_EasyUpgrade_Protocol(bgk_comm_buff_def* _In_pReceiveData,sdt_int8u* _In_TheAddr)
{         

    if(((0xFF == _In_pReceiveData->LinkDstAddr[0])&&\
        (0xFF == _In_pReceiveData->LinkDstAddr[1])&&\
        (0xFF == _In_pReceiveData->LinkDstAddr[2])&&\
        (0xFF == _In_pReceiveData->LinkDstAddr[3])&&\
        (0xFF == _In_pReceiveData->LinkDstAddr[4])&&\
        (0xFF == _In_pReceiveData->LinkDstAddr[5]))||\
       ((_In_TheAddr[0] == _In_pReceiveData->LinkDstAddr[0])&&\
        (_In_TheAddr[1] == _In_pReceiveData->LinkDstAddr[1])&&\
        (_In_TheAddr[2] == _In_pReceiveData->LinkDstAddr[2])&&\
        (_In_TheAddr[3] == _In_pReceiveData->LinkDstAddr[3])&&\
        (_In_TheAddr[4] == _In_pReceiveData->LinkDstAddr[4])&&\
        (_In_TheAddr[5] == _In_pReceiveData->LinkDstAddr[5])))
    {

        answer_oper.dst_addr[0] = _In_pReceiveData->LinkSrcAddr[0];
        answer_oper.dst_addr[1] = _In_pReceiveData->LinkSrcAddr[1];
        answer_oper.dst_addr[2] = _In_pReceiveData->LinkSrcAddr[2];
        answer_oper.dst_addr[3] = _In_pReceiveData->LinkSrcAddr[3];
        answer_oper.dst_addr[4] = _In_pReceiveData->LinkSrcAddr[4];
        answer_oper.dst_addr[5] = _In_pReceiveData->LinkSrcAddr[5];
        
        answer_oper.src_addr[0] = _In_TheAddr[0];
        answer_oper.src_addr[1] = _In_TheAddr[1];
        answer_oper.src_addr[2] = _In_TheAddr[2];
        answer_oper.src_addr[3] = _In_TheAddr[3];
        answer_oper.src_addr[4] = _In_TheAddr[4];
        answer_oper.src_addr[5] = _In_TheAddr[5];
        
        if(0 == _In_pReceiveData->PayloadLength)
        {
            Bough_AnswerErrorReport(BGEUERR_Length);
        }
        else
        {
            if(THE_VER == _In_pReceiveData->Payload[0])  //Command
            {
                switch(_In_pReceiveData->Payload[1])
                {
                    case BGEUCMD_QuerySalveStatus://Query Boot Status
                    {
                        if(4 == _In_pReceiveData->PayloadLength)
                        {
                            answer_oper.answer_payload[0] = THE_VER;                           //Version
                            answer_oper.answer_payload[1] = (BGEUCMD_QuerySalveStatus | 0x80); //Command
                            answer_oper.answer_payload[2] = BGEUSTS_Boot;                      //Status
                            answer_oper.answer_payload[3] = BGEUERR_NoneError;                 //Error Code
                            answer_oper.answer_length = 4;                               
                        }
                        else
                        {
                            Bough_AnswerErrorReport(BGEUERR_Length);
                        }
                        break;
                    }
                    case BGEUCMD_EnterBoot:
                    {
                        if(4 == _In_pReceiveData->PayloadLength)
                        {
                            answer_oper.answer_payload[0] = THE_VER;                           //Version
                            answer_oper.answer_payload[1] = (BGEUCMD_EnterBoot | 0x80);        //Command
                            answer_oper.answer_payload[2] = BGEUSTS_Boot;     //Status
                            answer_oper.answer_payload[3] = BGEUERR_NoneError;                 //Error Code
                            answer_oper.answer_length = 4;                          
                        }
                        else
                        {
                            Bough_AnswerErrorReport(BGEUERR_Length);
                        }
                        
                        break;
                    }
                    case BGEUCMD_StrUpgrade_map://重传命令
                    {
                        
                        if((128+6) == _In_pReceiveData->PayloadLength)
                        {
                            sdt_int8u err;
                            err = mde_push_fileMap(&_In_pReceiveData->Payload[6],sdt_false);
                            if(err)
                            {
                                Bough_AnswerErrorReport(err);
                            }
                            else
                            {
                                answer_oper.answer_payload[0] = THE_VER;                                //Version
                                answer_oper.answer_payload[1] = (BGEUCMD_StrUpgrade_map | 0x80);  //Command
                                answer_oper.answer_payload[2] = BGEUSTS_QueryFile;                   //Status,请求FileMap
                                answer_oper.answer_payload[3] = BGEUERR_NoneError;                                     //Error Code
                                
                                sdt_int16u next_block_number;
                                mde_pull_upgrade_next_block(&next_block_number);
                                pbc_int16uToArray_bigEndian(next_block_number,&answer_oper.answer_payload[4]);
                                answer_oper.answer_length = 6;                                   
                            }
                        }
                        else
                        {
                            Bough_AnswerErrorReport(BGEUERR_Length);
                        }
                        break;
                    }
                    case BGEUCMD_ResumeUpgrade_map://续传命令
                    {
                      
                        if((128+6) == _In_pReceiveData->PayloadLength)
                        {
                            sdt_int8u err;
                            err = mde_push_fileMap(&_In_pReceiveData->Payload[6],sdt_true);
                            if(err)
                            {
                                Bough_AnswerErrorReport(err);
                            }
                            else
                            {
                                answer_oper.answer_payload[0] = THE_VER;                              //Version
                                answer_oper.answer_payload[1] = (BGEUCMD_ResumeUpgrade_map | 0x80);        //Command
                                answer_oper.answer_payload[2] = BGEUSTS_QueryFile;                  //Status,请求FileMap
                                answer_oper.answer_payload[3] = BGEUERR_NoneError;                    //Error Code
                                
                                sdt_int16u next_block_number;
                                mde_pull_upgrade_next_block(&next_block_number);
                                pbc_int16uToArray_bigEndian(next_block_number,&answer_oper.answer_payload[4]);
                                answer_oper.answer_length = 6;                                     
                            }
                        }
                        else
                        {
                            Bough_AnswerErrorReport(BGEUERR_Length);
                        }
                        break;
                    }
                    case BGEUCMD_TransferFile://接收到File内容
                    {
                        if((128+6) == _In_pReceiveData->PayloadLength)
                        {
                            sdt_int8u ErrorCode = BGEUERR_NoneError;

                            ErrorCode = mde_push_files_one_block(pbc_arrayToInt16u_bigEndian(&_In_pReceiveData->Payload[4]),&_In_pReceiveData->Payload[6]);  //处理接收报文
                            
                            sdt_bool completed;
                            sdt_int16u next_block_number;
                            
                            completed = mde_pull_upgrade_next_block(&next_block_number);
                            if(ErrorCode)
                            {
                                Bough_AnswerErrorReport(ErrorCode);
                            }
                            else if(completed)
                            {
                                answer_oper.answer_payload[0] = THE_VER;                              //Version
                                answer_oper.answer_payload[1] = (BGEUCMD_TransferFile | 0x80);         //Command
                                answer_oper.answer_payload[2] = BGEUSTS_UpgradeFinish;                 //Status,UpgradeFinish
                                answer_oper.answer_payload[3] = BGEUERR_NoneError;                     //Error Code
                                answer_oper.answer_payload[4] = 0;
                                answer_oper.answer_payload[5] = 0;
                                answer_oper.answer_length = 6;   
                            }
                            else
                            {
                                answer_oper.answer_payload[0] = THE_VER;                           //Version
                                answer_oper.answer_payload[1] = (BGEUCMD_TransferFile | 0x80);     //Command
                                answer_oper.answer_payload[2] = BGEUSTS_QueryFile;                 //Status,请求File
                                answer_oper.answer_payload[3] = BGEUERR_NoneError;                 //Error Is not
                                pbc_int16uToArray_bigEndian(next_block_number,&answer_oper.answer_payload[4]);
                                answer_oper.answer_length = 6;    
                            }
                        }
                        else
                        {
                            Bough_AnswerErrorReport(BGEUERR_Length);
                        }
                        break;
                    }
                    default:
                    {
                        Bough_AnswerErrorReport(BGEUCMD_ErrorReport);
                        break;
                    }
                }
            }
            else
            {
                Bough_AnswerErrorReport(BGEUERR_Version);
            }          
        }
        ugd_esay_staues = ugd_esay_staue_start_answer;
        app_upgrade_easy_task();  //运行一次任务,有发送数据,占领link
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//升级接收文件状态

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//名称: 获取设备是否运行在Boot状态
//功能: 
//入口: 
//      
//出口: sdt_true--Boot状态
//-------------------------------------------------------------------------------------------------
sdt_int8u Pull_TheDeviceUpgradeStatus(void)
{
    sdt_int8u TheUdeStatus = BGEUSTS_Boot;
    /*
    switch(UPL_RevFileStatus)
    {
        case UPL_Idle:
        {
            break;
        }
        case UPL_RevFileMap:
        {
            TheUdeStatus = BGEUSTS_QueryFileMap;
            break;
        }
        case UPL_RevFileData:
        {
            TheUdeStatus = BGEUSTS_QueryFile;
            break;
        }
        case UPL_RevFinish:
        {
            TheUdeStatus = BGEUSTS_UpgradeFinish;
            break;
        }
        default:
        {
            break;
        }
    }*/
    return(TheUdeStatus);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//重传处理
//-------------------------------------------------------------------------------------------------
void RestartUpgrade_Process(void)
{

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//续传处理
//-------------------------------------------------------------------------------------------------
void ResumeUpgrade_Process(void)
{

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//主站任務
typedef enum
{
    ugdsm_idle               = 0x00,
    ugdsm_query              = 0x01,
    ugdsm_query_amswer       = 0x02,
    ugdsm_entryBoot          = 0x03,
    ugdsm_entryBoot_answer   = 0x04,
    ugdsm_restart            = 0x05,
    ugdsm_restart_answer     = 0x06,
    ugdsm_resume             = 0x07,
    ugdsm_resume_answer      = 0x08,
    ugdsm_transFlies         = 0x09,
    ugdsm_transFlies_answer  = 0x0A,
    ugdsm_check_pad_list     = 0x0B,
    ugdsm_check_fan_list     = 0x0C,
}upgrade_stateMachine_def;
#define easy_upgrade_version         0x01
//-----------------------------------------------------------------------------
#define easy_upgradeCmd_query        0x01
#define easy_upgradeCmd_entryBoot    0x02
#define easy_upgradeCmd_restart      0x03
#define easy_upgradeCmd_resume       0x04
#define easy_upgradeCmd_transFiles   0x05
#define easy_upgradeCmd_errReport    0x06
//-----------------------------------------------------------------------------
#define easy_upgradeSte_noValid      0x00
#define easy_upgradeSte_noBoot       0x01
#define easy_upgradeSte_Boot         0x10
#define easy_upgradeSte_transFiles   0x12
#define easy_upgradeSte_completed    0x1F
bgk_comm_buff_def* pReceive_date;
bool  haveDataFlag = false;
static upgrade_stateMachine_def upgrade_stateMachine = ugdsm_idle;
//主动升级任务
void app_bough_update_master_task(void)
{
    macro_createTimer(timer_transmit,timerType_millisecond,0);
    macro_createTimer(timer_answerTimeout,timerType_millisecond,0);
//-----------------------------------------------------------------------------
    bgk_comm_buff_def *transmit_data;
    static uint16_t padList = 0;//
    linkDeviceList_t* logList;
    uint8_t *local_addr;
    uint8_t i = 0;
    static uint8_t padPort = 0;//面板端口
    static uint16_t device_quety_fileNumber;
//-----------------------------------------------------------------------------
    pbc_timerClockRun_task(&timer_transmit);
    pbc_timerClockRun_task(&timer_answerTimeout);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
    switch(upgrade_stateMachine)
    {
        case ugdsm_idle:
        {
            if(mde_upgrade_pull_pad_status())
            {
                upgrade_stateMachine = ugdsm_check_pad_list;
            }          
            break;
        }
        case ugdsm_check_pad_list:
        {
            if(padList)
            {

            }
            else
            {
                logList = app_link_log_pull_device_list(SYSTEM_PAD);
                for(i = 0; i < MAX_DEVICE_NUM;i++)
                {
                    if(logList[i].onlineFlag)
                    {
                        if(logList[i].deviceType == DEVICE_TYPE_ROMM)
                        {
                            padList |= (0x01<<i);
                        }
                    }
                }      
            }
            if(padList)
            {
                upgrade_stateMachine = ugdsm_query;
            }
            else
            {
                upgrade_stateMachine = ugdsm_idle;
            }
            break;
        }
        case ugdsm_query:
        {
            if(pbc_pull_timerIsCompleted(&timer_transmit))
            {
                pbc_reload_timerClock(&timer_transmit,2000);
                for(i = 0;i < MAX_DEVICE_NUM;i++)
                {
                    if(padList & (0x01<<i))
                    {                        
                        padPort = i;
                        break;
                    }
                }
                transmit_data = pull_bough_message_pBuff(SYSTEM_PAD);
                logList = app_link_log_pull_device_list(SYSTEM_PAD);
                transmit_data->LinkDstAddr[0] = logList[padPort].DeviceID[0];
                transmit_data->LinkDstAddr[1] = logList[padPort].DeviceID[1];
                transmit_data->LinkDstAddr[2] = logList[padPort].DeviceID[2];
                transmit_data->LinkDstAddr[3] = logList[padPort].DeviceID[3];
                transmit_data->LinkDstAddr[4] = logList[padPort].DeviceID[4];
                transmit_data->LinkDstAddr[5] = logList[padPort].DeviceID[5];
                local_addr = app_pull_local_id();
                transmit_data->LinkSrcAddr[0] = local_addr[0];
                transmit_data->LinkSrcAddr[1] = local_addr[1];
                transmit_data->LinkSrcAddr[2] = local_addr[2];
                transmit_data->LinkSrcAddr[3] = local_addr[3];
                transmit_data->LinkSrcAddr[4] = local_addr[4];
                transmit_data->LinkSrcAddr[5] = local_addr[5];
                transmit_data->ProcotolType = 0xD002;
                transmit_data->PayloadLength = 4;
                transmit_data->Payload[0] = easy_upgrade_version;
                transmit_data->Payload[1] = easy_upgradeCmd_query;
                transmit_data->Payload[2] = 0x00;
                transmit_data->Payload[3] = 0x00;
                push_active_one_message_transmit(SYSTEM_PAD,false);
                upgrade_stateMachine = ugdsm_query_amswer;
                pbc_reload_timerClock(&timer_answerTimeout,1500);
            }
            break;
        }
        case ugdsm_query_amswer:
        {
            if(pbc_pull_timerIsCompleted(&timer_answerTimeout))
            {
                upgrade_stateMachine = ugdsm_query;
            }
            if(haveDataFlag)
            {
                haveDataFlag = false;
                if((pReceive_date->ProcotolType == 0xD002) && (pReceive_date->Payload[0] == easy_upgrade_version) &&\
                  (pReceive_date->Payload[1] == (easy_upgradeCmd_query|0x80)))
                {
                    if(pReceive_date->Payload[2] == easy_upgradeSte_Boot)
                    {
                       // if(app_pull_resumeOrRestart())
                       // {
                      //      upgrade_stateMachine = ugdsm_resume;
                      //  }
                      //  else
                      //  {
                            upgrade_stateMachine = ugdsm_restart;
                       // }
                    }
                    else if(pReceive_date->Payload[2] == easy_upgradeSte_Boot)
                    {
                        upgrade_stateMachine = ugdsm_entryBoot;
                    }
                }
            }
            break;
        }
        case ugdsm_entryBoot:
        {
            break;
        }
        case ugdsm_entryBoot_answer:
        {
           // pReceive_date = bsp_receive_message_event(&have_message);
            break;
        }
        case ugdsm_restart:
        {
            transmit_data = pull_bough_message_pBuff(SYSTEM_PAD);
            logList = app_link_log_pull_device_list(SYSTEM_PAD);
            transmit_data->LinkDstAddr[0] = logList[padPort].DeviceID[0];
            transmit_data->LinkDstAddr[1] = logList[padPort].DeviceID[1];
            transmit_data->LinkDstAddr[2] = logList[padPort].DeviceID[2];
            transmit_data->LinkDstAddr[3] = logList[padPort].DeviceID[3];
            transmit_data->LinkDstAddr[4] = logList[padPort].DeviceID[4];
            transmit_data->LinkDstAddr[5] = logList[padPort].DeviceID[5];
            local_addr = app_pull_local_id();
            transmit_data->LinkSrcAddr[0] = local_addr[0];
            transmit_data->LinkSrcAddr[1] = local_addr[1];
            transmit_data->LinkSrcAddr[2] = local_addr[2];
            transmit_data->LinkSrcAddr[3] = local_addr[3];
            transmit_data->LinkSrcAddr[4] = local_addr[4];
            transmit_data->LinkSrcAddr[5] = local_addr[5];
            transmit_data->ProcotolType = 0xD002;
            transmit_data->PayloadLength = 128+6;
            transmit_data->Payload[0] = easy_upgrade_version;
            transmit_data->Payload[1] = easy_upgradeCmd_restart;
            transmit_data->Payload[2] = 0x00;
            transmit_data->Payload[3] = 0x00;
            transmit_data->Payload[4] = 0x00;
            transmit_data->Payload[5] = 0x00;

           /* sdt_int8u i;
            for(i = 0;i < 128;i ++)
            {
                transmit_data.Payload[6+i] = (sdt_int8u)pRdData[i];
            }*/
            SPI_FLASH_BufferRead(&transmit_data->Payload[6+i],PAD_UPDATA_TUF_ADDRESS,128);
            push_active_one_message_transmit(SYSTEM_PAD,false);
            upgrade_stateMachine = ugdsm_restart_answer;
            pbc_reload_timerClock(&timer_answerTimeout,1500);

            break;
        }
        case ugdsm_restart_answer:
        {
            if(haveDataFlag)
            {
                haveDataFlag = false;
                if((easy_upgradeCmd_restart | 0x80) == pReceive_date->Payload[1])
                {
                    device_quety_fileNumber = pReceive_date->Payload[4];
                    device_quety_fileNumber = device_quety_fileNumber<<8;
                    device_quety_fileNumber |= pReceive_date->Payload[5];
                    upgrade_stateMachine = ugdsm_transFlies;
                }
            }

            break;
        }
        case ugdsm_resume:
        {
            break;
        }
        case ugdsm_resume_answer:
        {
           // pReceive_date = bsp_receive_message_event(&have_message);
            break;
        }
        case ugdsm_transFlies:
        {
            transmit_data = pull_bough_message_pBuff(SYSTEM_PAD);
            logList = app_link_log_pull_device_list(SYSTEM_PAD);
            transmit_data->LinkDstAddr[0] = logList[padPort].DeviceID[0];
            transmit_data->LinkDstAddr[1] = logList[padPort].DeviceID[1];
            transmit_data->LinkDstAddr[2] = logList[padPort].DeviceID[2];
            transmit_data->LinkDstAddr[3] = logList[padPort].DeviceID[3];
            transmit_data->LinkDstAddr[4] = logList[padPort].DeviceID[4];
            transmit_data->LinkDstAddr[5] = logList[padPort].DeviceID[5];
            local_addr = app_pull_local_id();
            transmit_data->LinkSrcAddr[0] = local_addr[0];
            transmit_data->LinkSrcAddr[1] = local_addr[1];
            transmit_data->LinkSrcAddr[2] = local_addr[2];
            transmit_data->LinkSrcAddr[3] = local_addr[3];
            transmit_data->LinkSrcAddr[4] = local_addr[4];
            transmit_data->LinkSrcAddr[5] = local_addr[5];
            transmit_data->ProcotolType = 0xD002;
            transmit_data->PayloadLength = 128+6;
            transmit_data->Payload[0] = easy_upgrade_version;
            transmit_data->Payload[1] = easy_upgradeCmd_transFiles;
            transmit_data->Payload[2] = 0x00;
            transmit_data->Payload[3] = 0x00;
            transmit_data->Payload[4] = device_quety_fileNumber >> 8;
            transmit_data->Payload[5] = device_quety_fileNumber;

            /*sdt_int8u i;
            for(i = 0;i < 128;i ++)
            {
                transmit_data.Payload[6+i] = (sdt_int8u)pRdData[device_quety_fileNumber*128+i];
            }*/
            SPI_FLASH_BufferRead(&transmit_data->Payload[6+i],PAD_UPDATA_TUF_ADDRESS+device_quety_fileNumber*128,128);
            push_active_one_message_transmit(SYSTEM_PAD,false);
            upgrade_stateMachine = ugdsm_transFlies_answer;
            pbc_reload_timerClock(&timer_answerTimeout,1500);
            break;
        }
        case ugdsm_transFlies_answer:
        {
            if(haveDataFlag)
            {
                haveDataFlag = false;
                if((easy_upgradeCmd_transFiles | 0x80) == pReceive_date->Payload[1])
                {
                    if(easy_upgradeSte_completed == pReceive_date->Payload[2])
                    {//升级完成
                        padList &= (~(0x01<<padPort));
                        if(padList)
                        {
                            upgrade_stateMachine = ugdsm_check_pad_list;
                        }
                        else
                        {
                            upgrade_stateMachine = ugdsm_idle;
                            mde_upgrade_clear_pad_status();
                        }                   
                    }
                    else
                    {
                        device_quety_fileNumber = pReceive_date->Payload[4];
                        device_quety_fileNumber = device_quety_fileNumber<<8;
                        device_quety_fileNumber |= pReceive_date->Payload[5];
                        upgrade_stateMachine = ugdsm_transFlies;
                    }
                }
            }
            if(pbc_pull_timerIsCompleted(&timer_answerTimeout))
            {
                upgrade_stateMachine = ugdsm_transFlies;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

//------------------------------------------------------------------------------
void app_bough_update_master_receive_protocol(bgk_comm_buff_def* in_pReceive_date)
{
    haveDataFlag = true;
    pReceive_date = in_pReceive_date;
    app_bough_update_master_task();
}
//------------------------------------------------------------------------------

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++