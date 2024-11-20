#ifndef _BSP_CAN_H
#define _BSP_CAN_H

#include "main.h"

typedef struct{
    uint8_t buf[16];
    uint8_t len;
    uint8_t flag;
}can_data_typedef;


extern CAN_HandleTypeDef hcan;
extern CAN_TxHeaderTypeDef txheader;

extern can_data_typedef canRx;

void CAN_SendMsg(uint8_t *buf,uint8_t len);

void bsp_can_Init(void);

#endif
