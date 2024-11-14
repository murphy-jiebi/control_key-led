#ifndef _LORA_H
#define _LORA_H


#include "main.h"


typedef enum
{
    AIR_SPEED_2400     =0x02,
    AIR_SPEED_4800     =0x03,
    AIR_SPEED_9600     =0x04,
    AIR_SPEED_19200    =0x05,  
}airSpeed_enum;

typedef enum
{
    COM_MODE_BD         =0x00,
    COM_MODE_P2P        =0x01,
}comMode_enum;

typedef enum
{
    WAKE_TIME_250MS      =0x00,
    WAKE_TIME_500MS      =0x01,
    WAKE_TIME_750MS      =0x02,
    WAKE_TIME_1000MS     =0x03,
    WAKE_TIME_1250MS     =0x04,
    WAKE_TIME_1500MS     =0x05,
    WAKE_TIME_1750MS     =0x06,
    WAKE_TIME_2000MS     =0x07,
}wakeTime_enum;

typedef enum
{
    TX_POWER_30DB        =0x00,
    TX_POWER_27DB        =0x01,
    TX_POWER_24DB        =0x02,
    TX_POWER_21DB        =0x03,
}txPower_enum;

#define default_loraParam {0x0000,AIR_SPEED_2400,0x17,COM_MODE_BD,WAKE_TIME_250MS,TX_POWER_30DB}

typedef struct
{
    uint16_t addr;
    uint8_t airSpeed;
    uint8_t channel;
    uint8_t comMode;
    uint8_t wakeTime;
    uint8_t txPower;
}loraParam_typedef;

void LoraInit(void);

void loraSendData(uint8_t *buf,uint8_t len);

#endif

