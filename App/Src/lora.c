#include "lora.h"
#include "bsp_gpio.h"
#include "delay.h"


extern UART_HandleTypeDef huart2;

uint8_t loraSendBuf[64]={0};

loraParam_typedef loraParam=
{
    .addr=0x0000,
    .airSpeed=AIR_SPEED_2400,
    .channel=0x17,
    .comMode=COM_MODE_BD,
    .wakeTime=WAKE_TIME_250MS,
    .txPower=TX_POWER_30DB,
};

void loraSendData(uint8_t *buf,uint8_t len)
{
    HAL_UART_Transmit(&huart2,buf,len,1000);
}
void LoraWriteParam(loraParam_typedef *para,uint8_t store)
{
    loraSendBuf[0]=store?0xC0:0xC2;
    loraSendBuf[1]=para->addr>>8;
    loraSendBuf[2]=para->addr&0xFF;
    loraSendBuf[3]=para->addr&0xFF;
    loraSendBuf[4]=(0x03<<3)|(para->airSpeed&0x07);  //9600 8N1
    loraSendBuf[5]=para->channel;
    loraSendBuf[5]=(para->comMode<<7)|(1<<6)|(para->wakeTime<<3)|(1<<2)|(para->txPower&0x03); 
    loraSendData(loraSendBuf,6);
}
void LoraReadVerInfo(void)
{
    memset(loraSendBuf,0xC3,3);
    loraSendData(loraSendBuf,3);
}

void LoraReadParam(void)
{
    memset(loraSendBuf,0xC1,3);
    loraSendData(loraSendBuf,3);
}


void LoraInit(void)
{
    LORA_PWR_EN;
    LORA_MO_H;
    LORA_M1_H;
    LoraWriteParam(&loraParam,0);
    
    delay_ms(1);
    LORA_MO_L;
    LORA_M1_L;
    
}



