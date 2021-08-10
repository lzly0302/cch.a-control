#ifndef pbc_dataConvert_H
#define pbc_dataConvert_H
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef snail_data_types
    #include ".\depend\snail_data_types.h"
#endif
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//名称: 16位数据转换成字符串
//功能:
//入口: 
//      in_data  ---16位的shu
//      out_string  字符串指针
//
//出口: 

//-------------------------------------------------------------------------------------------------
void pbc_int16u_to_string_convert(sdt_int16u in_data,sdt_string* out_string);
//-------------------------------------------------------------------------------------------------
void pbc_string_append(sdt_string* in_pAppend,sdt_string* out_string);
//-------------------------------------------------------------------------------------------------
sdt_int16u pbc_arrayToInt16u_bigEndian(sdt_int8u* in_data);
//-------------------------------------------------------------------------------------------------
sdt_int32u pbc_arrayToInt32u_bigEndian(sdt_int8u* in_data);
//-------------------------------------------------------------------------------------------------
void pbc_int16uToArray_bigEndian(sdt_int16u in_data,sdt_int8u* out_array);
//-------------------------------------------------------------------------------------------------
void pbc_int32uToArray_bigEndian(sdt_int32u in_data,sdt_int8u* out_array);
sdt_int8u pbc_string_to_int16u(sdt_int8u *in_char);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#endif