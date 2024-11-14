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
#include "bsp_adc.h"
#include "bsp_led.h"
#include "lora.h"
#include "bsp_tim.h"
#include "task_ctrl.h"
#include "bsp_24cxx.h" 
#include "task_com.h"

uint8_t test=0;
uint8_t test_buf[15]={0};
uint8_t test_data=0x11;


uint32_t preTb1s=0;
uint8_t channelStatus[6]={0};
uint8_t fireChannel[6]={0};
uint8_t flagFire=0;

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
    bsp_InitAdc();
    bsp_usartInit();
    LoraInit();
    Bsp_tim4_Init();
    while (1)
    {
        if(preTb1s!=TimerGet1s())
        {
            preTb1s=TimerGet1s();
            ChannelDetect();
            LedRefresh(channelStatus);
        }
        ChannelFire(TimerGet1ms(),&flagFire,fireChannel);
        TaskCom();
        
        switch(test)
        {
            case 1:
                memset(test_buf,test_data,15);
                loraSendData(test_buf,15);
                break;
            case 2:
                memset(test_buf,test_data,15);
                AT24CXX_Write(10,test_buf,15);
                break;
            case 3:
                memset(test_buf,0,15);
                AT24CXX_Read(10,test_buf,15);
                break;
            default:
                break;
        }
        test=0;
    }
}




