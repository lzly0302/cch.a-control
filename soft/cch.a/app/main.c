//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include ".\app_cfg.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main (void)
{
    #ifdef NDEBUG
    nvic_vector_table_set(NVIC_VECTTAB_FLASH,0x00004000);        //中断向量定位到Flash
    #else
    nvic_vector_table_set(NVIC_VECTTAB_FLASH,0x00000000);     
    #endif
     NVIC_SetPriority(SysTick_IRQn, 0x00U);
    __enable_interrupt();
    mde_IWDG_Configure();
    app_read_run_parameter();
    pbc_createTask_one(app_general_task,0);
//-----------------------------------------------------------------------------
    pbc_sysTickTaskProcess();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++