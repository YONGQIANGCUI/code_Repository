#ifndef __API_MISC_H
#define __API_MISC_H

/***Include***/
#include "stm32f1xx_hal.h"
#include "string.h"
#include "stdlib.h"
#define MIN(x, y)                       ((x > y) ? y : x)
#define MAX(x, y)                       ((x > y) ? x : y)

#define API_PACK_UINT8(p_buf,data)                                             \
        do{                                                                        \
            (p_buf)[0] = (uint8_t)(data);                                      \
        }while(0)
/*
下面宏定义作用:
低字节在前，高字节在后
				*/
#define API_PACK_UINT16_B(p_buf, data)                                         \
    do{                                                                        \
        (p_buf)[1] = (uint8_t)(data >>  0);                                      \
        (p_buf)[0] = (uint8_t)(data >>  8);                                     \
    }while(0)

#define API_PACK_UINT16_L(p_buf, data)                                         \
    do{                                                                        \
        p_buf[0] = (uint8_t)(data >>  0);                                      \
        p_buf[1] = (uint8_t)(data >>  8);                                      \
    }while(0)

#define API_PACK_UINT32_B(p_buf, data)                                         \
    do{                                                                        \
        p_buf[3] = (uint8_t)(data >>  0);                                      \
        p_buf[2] = (uint8_t)(data >>  8);                                      \
        p_buf[1] = (uint8_t)(data >> 16);                                      \
        p_buf[0] = (uint8_t)(data >> 24);                                      \
    }while(0)

#define API_PACK_UINT32_L(p_buf, data)                                         \
    do{                                                                        \
        p_buf[0] = (uint8_t)(data >>  0);                                      \
        p_buf[1] = (uint8_t)(data >>  8);                                      \
        p_buf[2] = (uint8_t)(data >> 16);                                      \
        p_buf[3] = (uint8_t)(data >> 24);                                      \
    }while(0)

#define API_UNPACK_UINT16_B(p_buf)  ((uint16_t)((((uint8_t*)p_buf)[1] <<   0)  \
                                    |           (((uint8_t*)p_buf)[0] <<  8)))

#define API_UNPACK_UINT16_L(p_buf)  ((uint16_t)((((uint8_t*)p_buf)[0] << 0)    \
                                    |           (((uint8_t*)p_buf)[1] <<  8)))

#define API_UNPACK_UINT32_B(p_buf)  ((uint32_t)((((uint8_t*)p_buf)[3] <<  0)   \
                                    |           (((uint8_t*)p_buf)[2] <<  8)   \
                                    |           (((uint8_t*)p_buf)[1] << 16)   \
                                    |           (((uint8_t*)p_buf)[0] << 24)))

#define API_UNPACK_UINT32_L(p_buf)  ((uint32_t)((((uint8_t*)p_buf)[0] <<  0)   \
                                    |           (((uint8_t*)p_buf)[1] <<  8)   \
                                    |           (((uint8_t*)p_buf)[2] << 16)   \
                                    |           (((uint8_t*)p_buf)[3] << 24)))



#ifndef __OPEN_TIMER_MAC
#define __OPEN_TIMER_MAC

#define OPEN_TIMER(tmName, tmVal)	(tmName) = (tmVal);
#define CLOSE_TIMER(tmName)		(tmName) = 0;
#define TIMER_TRIG(tmName)		(1 == (tmName))
#define TIMER_EXECUTE(tmName)		{if(1 < (tmName)) (tmName)--;}
#define TIMER_JUDGE(tmName)      ( 1<(tmName))
#define TIMER_CLOSED(tmName)    (0 == (tmName))
#endif
#ifndef __NULL
#define __NULL 0
#define NULL 0
#endif

#ifndef __BOOL
#define __BOOL
typedef unsigned int BOOL;
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
extern uint32_t api_dec2bcd(uint32_t dec);
extern uint32_t api_bcd2dec(uint32_t bcd);
extern uint8_t xor_check_sum(uint8_t *start_byte,uint16_t length);
extern uint8_t api_byte_dec2bcd(uint8_t dec);
extern uint8_t api_byte_bcd2dec(uint8_t bcd);
extern char * GetField(char *sTheStr, char *sDelimiter, int16_t iWhichField, char *sResultStr);
extern uint16_t crc16bitbybit(uint8_t *ptr, uint16_t len);
extern unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen);

#endif
