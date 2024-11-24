#include "protocol.h"

#define FRAME_DATA_HEAD             0xAA
#define FRAME_DATA_CMD_DETECT       0x51
#define FRAME_DATA_CMD_FIRE         0x52
    
#define FRAME_OFFSET_HEAD           0x00
#define FRAME_OFFSET_LEN            0x01
#define FRAME_OFFSET_GROUP          0x02
#define FRAME_OFFSET_DEV            0x03
#define FRAME_OFFSET_CMD            0x04
#define FRAME_OFFSET_DATA           0x05
#define FRAME_OFFSET_CRC            0x0B

const uint8_t groupSN=1;
const uint8_t devSN=1;

extern uint8_t channelStatus[];
extern uint8_t fireChannel[];
extern uint8_t flagFire;

uint8_t Get_CrcXOR(uint8_t *_ucpBuf, uint16_t _usLen)
{
	uint16_t i;
	uint8_t  Temp_Crc = 0x00;	
	for(i = 0; i < _usLen; i++)
	{
		Temp_Crc ^= *_ucpBuf++;
	}
	return Temp_Crc;
}

uint8_t ProtocolParse(uint8_t *mess,uint8_t len)
{

    if(mess[FRAME_OFFSET_HEAD]!=0xAA)
    {
        return 0;
    }
    if(mess[2]!= 0x55)
    {
        return 0;
    }
    channelStatus[0]=(mess[2]>>0)&0x03;
    channelStatus[1]=(mess[2]>>2)&0x03;
    channelStatus[2]=(mess[2]>>4)&0x03;
    channelStatus[3]=(mess[2]>>6)&0x03;
    
    channelStatus[4]=(mess[3]>>0)&0x03;
    channelStatus[5]=(mess[3]>>2)&0x03;
    channelStatus[6]=(mess[3]>>4)&0x03;
    channelStatus[7]=(mess[3]>>6)&0x03;
    
    channelStatus[8]=(mess[4]>>0)&0x03;
    channelStatus[9]=(mess[4]>>2)&0x03;
    channelStatus[10]=(mess[4]>>4)&0x03;
    channelStatus[11]=(mess[4]>>6)&0x03;
    
    channelStatus[12]=(mess[5]>>0)&0x03;
    channelStatus[13]=(mess[5]>>2)&0x03;

    return 1;
}

uint8_t ProtocolPackage(uint8_t *buf,uint8_t cmd)
{
    buf[0]=0xAA;
    buf[1]=0x55;
    buf[2]=cmd;
    buf[3]=cmd;
    buf[4]=cmd;
    buf[5]=cmd;
    buf[6]=cmd;
    buf[7]=Get_CrcXOR(buf,7);
    
    return 8;
}

