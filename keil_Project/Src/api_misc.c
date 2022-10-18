#include "api_misc.h"

static const long int c_dec_pow_table[] =
    {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};


uint32_t api_dec2bcd(uint32_t dec)
{
	int bcd = 0;
	if(dec < c_dec_pow_table[8])
	{
		uint32_t remain = 0;
		int carry = 0;
		for(remain = dec; remain != 0; remain /= 10)
		{
			bcd |= (remain % 10) << carry;
			carry += 4;
		}
	}
	else
	{
		bcd = -1;
	}
	return bcd;
}

/**
*@brief     BCD 码转换为相应的 10 进制数
*@param     bcd:    BCD 码，格式为每 4bit 值范围 [0, 9]
*@retval    dec:    转换后的 10 进制数
*@note      如果 BCD 码格式错误则返回错误值 -1
*           0x12345678  =>  12345678
**/
uint32_t api_bcd2dec(uint32_t bcd)
{
    int dec = 0;
    uint32_t remain = 0;
    int carry = 0;

    for(remain = bcd; remain != 0; remain >>= 4)
    {
        uint8_t tmpval = remain & 0xF;

        if(tmpval < 10)
        {
            dec += tmpval * c_dec_pow_table[carry++];
        }
        else
        {
            dec = -1;
            break;
        }
    }

    return dec;
}

uint8_t xor_check_sum(uint8_t *start_byte,uint16_t length)
{
	uint8_t i = 0;
	uint8_t fcs = 0;
	for(i=0;i<length;i++)
	{
		fcs^= (*(start_byte + i));//except frame head
	}
	return fcs;
}
uint8_t api_byte_dec2bcd(uint8_t dec)
{
	return ((dec / 10) << 4) + (dec % 10);
}
uint8_t api_byte_bcd2dec(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

/*******************************************************************************
*	GetField
*		类型	:	void
*		返回值	:	返回指定域值  保存在sResultStr，失败时返回空字符
*		??	:	
*					char		*sTheStr			带界定符的字符串
*					char		*sDelimiter			界定符
*					int16			iWhichField			指定返回的域号，域号由1开始
*					char		*sResultStr			指定返回的域值
*

*******************************************************************************/
char * GetField(char *sTheStr, char *sDelimiter, int16_t iWhichField, char *sResultStr)
{
	char *sFind;
	char *sFind2;
	int16_t argCount;

	if(!sTheStr)
		return NULL;
	
	
	sFind=sTheStr;
	
	argCount = 1;
	while(argCount++ < iWhichField)
	{
		sFind=strstr(sFind,sDelimiter);
		if(sFind==NULL)
		{
			sResultStr[0]=0;
			return sResultStr;
		}
		sFind+=strlen(sDelimiter);
	}
	
	sFind2=strstr(sFind,sDelimiter);
	
	if(sFind2==NULL)
	{
		strcpy(sResultStr,sFind);
	}
	else
	{
		memcpy(sResultStr,sFind,sFind2-sFind);
		sResultStr[sFind2-sFind]=0;
	}
	
	return sResultStr;
}

// 非查表方式计算CRC16	
uint16_t crc16bitbybit(uint8_t *ptr, uint16_t len)
{
	uint8_t i = 0;
	uint8_t j= 0;
	uint16_t crc = 0xffff;
	uint16_t g_crc16_polynom = 0xA001;
	
	if (len == 0) 
	{
		len = 1;
	}
	for(j = 0;j < len;j++) 
	{
		crc ^= (*ptr);
		for (i = 0; i<8; i++)
		{
		
			crc >>= 1;
			if (crc & 0x0001) 
			{
				crc ^= g_crc16_polynom;
			}
		}
		ptr++;
	}
	return(crc);
}
 void InvertUint8(unsigned char *DesBuf, unsigned char *SrcBuf)
{
	int i;
	unsigned char temp = 0;
	for(i = 0; i < 8; i++)
	{
		if(SrcBuf[0] & (1 << i))
		{
			temp |= 1<<(7-i);
		}
	}
	 DesBuf[0] = temp;
}
void InvertUint16(unsigned short *DesBuf, unsigned short *SrcBuf)  
{  
	int i;  
	unsigned short temp = 0;    
	for(i = 0; i < 16; i++)  
	{  
		if(SrcBuf[0] & (1 << i))
		{          
			temp |= 1<<(15 - i);  
		}
	}  
	DesBuf[0] = temp;  
}
unsigned short CRC16_MODBUS(unsigned char *puchMsg, unsigned int usDataLen)  
{  
	unsigned short wCRCin = 0xFFFF;  
	unsigned short wCPoly = 0x8005;  
	unsigned char wChar = 0;  
	 while (usDataLen--)     
	{  
		wChar = *(puchMsg++);  
		InvertUint8(&wChar, &wChar);  
		wCRCin ^= (wChar << 8); 
		 for(int i = 0; i < 8; i++)  
		{  
			if(wCRCin & 0x8000) 
			{
				wCRCin = (wCRCin << 1) ^ wCPoly;  
			}
			else  
			{
				wCRCin = wCRCin << 1; 
			}            
		}  
	}  
	InvertUint16(&wCRCin, &wCRCin);  
	return (wCRCin) ;  
}




