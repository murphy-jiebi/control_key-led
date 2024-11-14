/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H



/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "string.h"

typedef enum
{
    CH_NO_CON        =0,
    CH_SELECT        =0x01,
    CH_CONNECT       =0x02,
    CH_FIRED         =0x03,
    CH_FAULT         =0x04,
}chStatus_enum_typedef;

typedef enum 
{
    LED_NONE        =0,
    LED_BLUE        =0x01,
    LED_GREEN       =0x02,
    LED_RED         =0x04,
    LED_YELLOW      =0x06,
   
}led_color_typedef;

extern uint8_t channelStatus[];
extern uint8_t fireChannel[];
extern uint8_t flagFire;


void Error_Handler(void);


#endif /* __MAIN_H */
