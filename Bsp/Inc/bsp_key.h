#ifndef _BSP_KEY_H
#define _BSP_KEY_H

#include "main.h"

#define KEY_FIFO_MAX    10

typedef struct{
    uint8_t buf[KEY_FIFO_MAX];
    uint8_t read;
    uint8_t write; 
}key_fifo_typedef;


void KeyPush(uint8_t val);
uint8_t KeyPop(void);

uint8_t KeyScan(void);


#endif
