#ifndef _BSP_GPIO_H
#define _BSP_GPIO_H

#include "main.h" 	

typedef struct 
{
	GPIO_TypeDef *key_port;
	uint32_t		key_pin;
}key_gpio_typedef;

#define LED1_SDB_PORT        GPIOB
#define LED1_SDB_PIN         GPIO_PIN_4

#define LED2_SDB_PORT        GPIOB
#define LED2_SDB_PIN         GPIO_PIN_12

#define KEY11_PORT           GPIOA
#define KEY11_PIN            GPIO_PIN_1

#define KEY12_PORT           GPIOA
#define KEY12_PIN            GPIO_PIN_2

#define KEY13_PORT           GPIOA
#define KEY13_PIN            GPIO_PIN_3

#define KEY14_PORT           GPIOA
#define KEY14_PIN            GPIO_PIN_4

#define KEY15_PORT           GPIOA
#define KEY15_PIN            GPIO_PIN_5

#define KEY16_PORT           GPIOA
#define KEY16_PIN            GPIO_PIN_6

#define KEY17_PORT           GPIOA
#define KEY17_PIN            GPIO_PIN_7

#define KEY21_PORT           GPIOB
#define KEY21_PIN            GPIO_PIN_0

#define KEY22_PORT           GPIOB
#define KEY22_PIN            GPIO_PIN_1

#define KEY23_PORT           GPIOB
#define KEY23_PIN            GPIO_PIN_3

#define KEY24_PORT           GPIOB
#define KEY24_PIN            GPIO_PIN_5

#define KEY25_PORT           GPIOB
#define KEY25_PIN            GPIO_PIN_13

#define KEY26_PORT           GPIOB
#define KEY26_PIN            GPIO_PIN_14

#define KEY27_PORT           GPIOB
#define KEY27_PIN            GPIO_PIN_15

#define READ_KEY11_INT        ((KEY11_PORT->IDR & KEY11_PIN) != 0)
#define READ_KEY12_INT        ((KEY12_PORT->IDR & KEY12_PIN) != 0)
#define READ_KEY13_INT        ((KEY13_PORT->IDR & KEY13_PIN) != 0)
#define READ_KEY14_INT        ((KEY14_PORT->IDR & KEY14_PIN) != 0)
#define READ_KEY15_INT        ((KEY15_PORT->IDR & KEY15_PIN) != 0)
#define READ_KEY16_INT        ((KEY16_PORT->IDR & KEY16_PIN) != 0)
#define READ_KEY17_INT        ((KEY17_PORT->IDR & KEY17_PIN) != 0)

#define READ_KEY21_INT        ((KEY21_PORT->IDR & KEY21_PIN) != 0)
#define READ_KEY22_INT        ((KEY22_PORT->IDR & KEY22_PIN) != 0)
#define READ_KEY23_INT        ((KEY23_PORT->IDR & KEY23_PIN) != 0)
#define READ_KEY24_INT        ((KEY24_PORT->IDR & KEY24_PIN) != 0)
#define READ_KEY25_INT        ((KEY25_PORT->IDR & KEY25_PIN) != 0)
#define READ_KEY26_INT        ((KEY26_PORT->IDR & KEY26_PIN) != 0)
#define READ_KEY27_INT        ((KEY27_PORT->IDR & KEY27_PIN) != 0)
                                                     
#define LED1_RST_DIS          (LED1_SDB_PORT->BSRR = LED1_SDB_PIN)
#define LED1_RST_EN           (LED1_SDB_PORT->BRR = LED1_SDB_PIN)

#define LED2_RST_DIS          (LED2_SDB_PORT->BSRR = LED2_SDB_PIN)
#define LED2_RST_EN           (LED2_SDB_PORT->BRR = LED2_SDB_PIN)



void bsp_InitGpio(void);

#endif

