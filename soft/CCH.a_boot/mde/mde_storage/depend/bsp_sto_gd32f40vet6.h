//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "gd32f4xx.h"
#include "..\..\mde_w25q64\mde_w25q64.h"
#include "..\..\mde_watchDog\mde_watchDog.h"
#include "..\..\..\pbc\pbc_dataConvert\pbc_dataConvert.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//flash map gd32f407vet6
//512k flash
//0x0800 0000 -- 0x0807 FFFF
//boot
//0x0800 0000 -- 0x0800 3FFF     16k     
//user.app 运行区
//0x0800 4000 -- 0x0803 FFFF     240k  
//user.upgrade 升级区
//0x10000 -- 0x4bFFF             240k   
//reserve                    
//0x0804 0000 -- 0x0807 FFFF     256k
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define user_app_start_addr      0x08004000
#define user_app_inf_addr        0x0803FFE0
#define user_upgrade_start_addr  0x10000
#define user_upgrade_inf_addr    0x4BfE0
#define page_unit_size           2048
#define information_size         32
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef void (*pFunction)(void);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//程序跳转到应用区
//-----------------------------------------------------------------------------
#define KR_KEY_Reload    ((uint16_t)0xAAAA)
//-----------------------------------------------------------------------------
void bsp_jump_to_user_app(void)
{
    pFunction Jump_To_Application;
    
    #ifdef NDEBUG
   // mde_IWDG_FeedDog();
    #endif
    //IWDG->KR = KR_KEY_Reload;
      
    __disable_interrupt();  
    /* Jump to user application */
    if((*(uint32_t*)(0x8000000)&0x2FFE0000)==0x20000000)//判断栈顶指针是否合法
    {
        Jump_To_Application = (pFunction)(*(__IO uint32_t*)(user_app_start_addr + 4));
        /* Initialize user application's Stack Pointer */
        __set_MSP(*(__IO uint32_t*) user_app_start_addr);
        Jump_To_Application(); 
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//32byte的信息数据
//-----------------------------------------------------------------------------
void bsp_read_information_user_app(sdt_int8u* out_pInf)
{
    sdt_int8u *pAddr;
    sdt_int8u i;
    pAddr = (sdt_int8u*)user_app_inf_addr;
    for(i = 0;i < information_size;i++)
    {
        *out_pInf = *pAddr;
        pAddr ++;
        out_pInf ++;
    }
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_read_information_user_upgrade(sdt_int8u* out_pInf)
{
    SPI_FLASH_BufferRead(out_pInf,user_upgrade_inf_addr,information_size);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//读取flash的数据流
//-----------------------------------------------------------------------------
void bsp_read_4bytes_user_app(sdt_int32u in_offset_addr,sdt_int8u* out_pData)
{
    sdt_int8u* pAddr;
    sdt_int8u i;
    
    #ifdef NDEBUG
    mde_IWDG_FeedDog();  //大数据传输，避免watchdog timeout
    #endif
    
    if((user_app_start_addr + in_offset_addr) > user_app_inf_addr)//地址保护
    {
        return;
    }
    pAddr = (sdt_int8u*)(user_app_start_addr + in_offset_addr);
    for(i = 0;i < 4;i++)
    {
        *out_pData = *pAddr;
        out_pData++;
        pAddr++;
    }

}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_read_4bytes_user_upgrade(sdt_int32u in_offset_addr,sdt_int8u* out_pData)
{  
    #ifdef NDEBUG
    mde_IWDG_FeedDog();  //大数据传输，避免watchdog timeout
    #endif
    
    if((user_upgrade_start_addr + in_offset_addr) > user_upgrade_inf_addr)//地址保护
    {
        return;
    }
    SPI_FLASH_BufferRead(out_pData,(user_upgrade_start_addr + in_offset_addr),4);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void CheckWriteProtectionBits(void)
{ 
  /*  if((FLASH_GetWriteProtectionOptionByte()&(~0xE0000003))==(~0xE0000003))
    {
    }
    else
    {
        FLASH_Unlock();
        FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
        FLASH_EraseOptionBytes(); 
        FLASH_EnableWriteProtection(FLASH_WRProt_Pages0to1|FLASH_WRProt_Pages2to3);
        FLASH_Lock();
        NVIC_SystemReset();
    }*/
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_transfer_user_upgrade_to_app(sdt_int32u in_codesize)
{
 //   sdt_int32u falsh_addr;
 //   volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
    volatile fmc_state_enum FLASHStatus = FMC_BUSY;
    #ifdef NDEBUG
    mde_IWDG_FeedDog();
    #endif
    
    if((user_app_start_addr + in_codesize) > user_app_inf_addr)//地址保护
    {
        return;
    }
    
    #ifdef NDEBUG
    #else
    //test
  //  sdt_int32u test_addr;
   // sdt_int32u test_reg;
  //  test_addr = user_app_inf_addr - 4; 
   // test_reg = *(sdt_int32u*)test_addr + 1;
    //    
    #endif

    CheckWriteProtectionBits();
    fmc_unlock();
    fmc_flag_clear(FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_WPERR | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR);
    /*擦除240K*/
    FLASHStatus = fmc_sector_erase(CTL_SECTOR_NUMBER_1);
    if(FMC_READY == FLASHStatus)
    {
        FLASHStatus = fmc_sector_erase(CTL_SECTOR_NUMBER_2);
        if(FMC_READY == FLASHStatus)
        {
            FLASHStatus = fmc_sector_erase(CTL_SECTOR_NUMBER_3);
            {
                if(FMC_READY == FLASHStatus)
                {
                    FLASHStatus = fmc_sector_erase(CTL_SECTOR_NUMBER_4);
                    if(FMC_READY == FLASHStatus)
                    {
                        FLASHStatus = fmc_sector_erase(CTL_SECTOR_NUMBER_5);
                    }
                }
            }
        }
    }
    
    #ifdef NDEBUG
    #else
    //    
    #endif
    
    
    sdt_int32u app_falsh_addr;
    sdt_int32u upgrade_falsh_addr;
    sdt_int32u words_32bits;
    sdt_int32u i;

    app_falsh_addr = user_app_inf_addr;
    upgrade_falsh_addr = user_upgrade_inf_addr;
    sdt_int8u buff[4];
    static sdt_int32u value;
    words_32bits = 8;         //32bytes information
    for(i=0;i<words_32bits;i++)
    {
        #ifdef NDEBUG
        mde_IWDG_FeedDog();
        #endif
        SPI_FLASH_BufferRead(buff,upgrade_falsh_addr,4);
        value = pbc_arrayToInt32u_smallEndian(buff);
        fmc_word_program(app_falsh_addr,value);
        app_falsh_addr += 4;
        upgrade_falsh_addr += 4;
    }
    
    app_falsh_addr = user_app_start_addr;
    upgrade_falsh_addr = user_upgrade_start_addr;
    words_32bits = in_codesize/4;   //program data

    for(i=0;i<words_32bits;i++)
    {
        #ifdef NDEBUG
        mde_IWDG_FeedDog();
        #endif
        SPI_FLASH_BufferRead(buff,upgrade_falsh_addr,4);
        value = pbc_arrayToInt32u_smallEndian(buff);
        fmc_word_program(app_falsh_addr,value);
        app_falsh_addr += 4;
        upgrade_falsh_addr += 4;
    }
    //扇区0-扇区7共512K  16+16+16+16+64+128+128+128
    ob_unlock();
    ob_write_protection_enable(OB_WP_0|OB_WP_1|OB_WP_2|OB_WP_3|OB_WP_4|OB_WP_5|OB_WP_6 | OB_WP_7);
    ob_start();
    ob_lock();
    fmc_lock();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++