

#pragma once




//һ��λ�����á��������ȡ��   
#define   BIT_SET(var, bit) ((var) |= (1<<(bit)))
#define   BIT_CLEAR(var, bit) ((var) &= ~(1<<(bit)))
#define   BIT_GET(var, bit) (((var)>>(bit)) & 0x01)