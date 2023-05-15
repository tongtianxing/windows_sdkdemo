

#pragma once




//一个位的设置、清除、获取宏   
#define   BIT_SET(var, bit) ((var) |= (1<<(bit)))
#define   BIT_CLEAR(var, bit) ((var) &= ~(1<<(bit)))
#define   BIT_GET(var, bit) (((var)>>(bit)) & 0x01)