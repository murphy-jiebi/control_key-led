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
    uint8_t temp_group=0;
    uint8_t temp_dev=0;
    uint8_t temp_cmd=0;
    if(mess[FRAME_OFFSET_HEAD]!=FRAME_DATA_HEAD)
    {
        return 0;
    }
    if(mess[FRAME_OFFSET_LEN]!=(len-1))
    {
        return 0;
    }
    if(mess[FRAME_OFFSET_GROUP]!=groupSN)
    {
       return 0; 
    }
    if(mess[FRAME_OFFSET_DEV]!=devSN)
    {
        return 0;
    }
    
    temp_group=mess[FRAME_OFFSET_GROUP];
    temp_dev=mess[FRAME_OFFSET_DEV];
    temp_cmd=mess[FRAME_OFFSET_CMD];
    
    switch(temp_cmd)
    {
        case FRAME_DATA_CMD_DETECT:
            
            break;
        case FRAME_DATA_CMD_FIRE:
            flagFire=1;
            memcpy(fireChannel,&mess[FRAME_OFFSET_DATA],6);
            break;
        default:
            break;
    }
    return temp_cmd;
}

uint8_t ProtocolPackage(uint8_t *buf,uint8_t cmd)
{
    uint8_t len=0;
    uint8_t i=0;
    buf[FRAME_OFFSET_HEAD]=FRAME_DATA_HEAD;
    buf[FRAME_OFFSET_LEN]=12;
    buf[FRAME_OFFSET_GROUP]=groupSN;
    buf[FRAME_OFFSET_DEV]=devSN;
    buf[FRAME_OFFSET_CMD]=cmd|0x80;
    switch(cmd)
    {
        case FRAME_DATA_CMD_DETECT:
            memcpy(&buf[FRAME_OFFSET_DATA],channelStatus,6);
            break;
        case FRAME_DATA_CMD_FIRE:
            for(i=0;i<6;i++)
            {
                buf[FRAME_OFFSET_DATA+i]=fireChannel[i]?0x03:channelStatus[i];
            }
        //    memcpy(&buf[FRAME_OFFSET_DATA],channelStatus,6);
            break;
        default:
            break;
    }
    buf[FRAME_OFFSET_CRC]=Get_CrcXOR(buf,11);
    
    return 12;
}

uint8_t ProtocolPackageFire(uint8_t *buf)
{
    uint8_t len=0;
    uint8_t i=0;
    buf[FRAME_OFFSET_HEAD]=FRAME_DATA_HEAD;
    buf[FRAME_OFFSET_LEN]=12;
    buf[FRAME_OFFSET_GROUP]=groupSN;
    buf[FRAME_OFFSET_DEV]=devSN;
    buf[FRAME_OFFSET_CMD]=FRAME_DATA_CMD_FIRE|0x80;
    
//    memcpy(&buf[FRAME_OFFSET_DATA],channelStatus,6);
    buf[FRAME_OFFSET_CRC]=Get_CrcXOR(buf,11);
    
    return 12;
}