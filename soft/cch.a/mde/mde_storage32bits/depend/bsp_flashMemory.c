//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef snail_data_types
    #include ".\snail_data_types.h"
#endif
//-----------------------------------------------------------------------------
#include "..\..\mde_w25q64\mde_w25q64.h"
#include "..\..\..\pbc\pbc_dataConvert\pbc_dataConvert.h"
#include "..\mde_storage32bits.h"
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//头两个扇区用于各种运行参数的存储
//0-4095        4K     
//4096-8191     4K     
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define FIRST_ADDR    0
#define SECOND_ADDR   0x1000
//-----------------------------------------------------------------------------
sdt_int32u bsp_passage_flash_memory_read(block_def in_block,sdt_int32u in_offset)
{  
    sdt_int32u  the_data;
    sdt_int8u   readBuff[4] = {0,0,0,0};
    if(block_first == in_block)
    {
        SPI_FLASH_BufferRead(readBuff,(FIRST_ADDR+(in_offset*4)),4);
        the_data = pbc_arrayToInt32u_bigEndian(readBuff);                    
    }
    else if(block_second == in_block)
    {
        SPI_FLASH_BufferRead(readBuff,(SECOND_ADDR+(in_offset*4)),4);
        the_data = pbc_arrayToInt32u_bigEndian(readBuff);        
    }
    else
    {
        SPI_FLASH_BufferRead(readBuff,FIRST_ADDR,4);
        the_data = pbc_arrayToInt32u_bigEndian(readBuff);    
    }
    return the_data;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_passage_flash_memory_write(block_def in_block,sdt_int32u in_offset,sdt_int32u in_data)
{
    sdt_int32u write_f_addr;
    sdt_int8u  writeBuff[4];
    if(block_first == in_block)
    {
        write_f_addr =(FIRST_ADDR+(in_offset*4));
    }
    else if(block_second == in_block)
    {
        write_f_addr =(SECOND_ADDR+(in_offset*4));
    }
    else
    {
        write_f_addr =FIRST_ADDR;
    }
    
    if(0 == in_offset)
    {
        SPI_FLASH_SectorErase(write_f_addr);
    }
    pbc_int32uToArray_bigEndian(in_data,writeBuff);
    SPI_FLASH_BufferWrite(writeBuff,write_f_addr,4);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void bsp_passage_flash_write_complete(void)
{
    
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++