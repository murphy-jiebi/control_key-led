/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "bsp_sys.h"
#include "delay.h"
#include "bsp_usart.h"
#include "bsp_gpio.h"
#include "bsp_led.h"
#include "bsp_tim.h"
#include "bsp_24cxx.h" 
#include "task_com.h"
#include "bsp_can.h"
#include "bsp_key.h"
#include "protocol.h"

const uint8_t devID=0x02;



uint8_t test=0;
uint8_t test_buf[15]={0};
uint8_t test_data=0x11;


uint32_t preTb1s=0;
uint8_t channelStatus[14]={0};
uint8_t flagFire=0;
uint8_t key=0;
uint8_t canTxBuf[8]={0};
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    HAL_Init();
    SystemClock_Config();
    bsp_InitGpio();
    AT24CXX_Init();
    LedInit();
    bsp_usartInit();
    Bsp_tim4_Init();
    bsp_can_Init();
    memset(channelStatus,0x1,14);
    while (1)
    {
        if(preTb1s!=TimerGet1s())
        {
            preTb1s=TimerGet1s();
        }
        LedRefresh(channelStatus);
        key=KeyScan();
        if(key>0)
        {
            key=0;
            ProtocolPackage(canTxBuf,key);
            CAN_SendMsg(canTxBuf,8);
        }
        TaskCom();
        
        switch(test)
        {
            case 1:
                memset(test_buf,test_data,15);
//                loraSendData(test_buf,15);
                break;
            case 2:
                memset(test_buf,test_data,15);
                AT24CXX_Write(10,test_buf,15);
                break;
            case 3:
                memset(test_buf,0,15);
                AT24CXX_Read(10,test_buf,15);
                break;
            case 4:
                memset(test_buf,test_data,8);
                CAN_SendMsg(test_buf,8);
                break;
            default:
                break;
        }
        test=0;
    }
}




