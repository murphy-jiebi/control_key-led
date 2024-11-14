#include "bsp_gpio.h"


void bsp_InitGpio(void)
{
    //GPIOB8,B9初始化设置
	GPIO_InitTypeDef GPIO_InitStruct = {0};	
	__HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    
 /********************************输出********************************************************/   
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  
    GPIO_InitStruct.Pin = LED1_SDB_PIN;
	HAL_GPIO_Init(LED1_SDB_PORT, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = LED2_SDB_PIN;
	HAL_GPIO_Init(LED2_SDB_PORT, &GPIO_InitStruct);
/********************************输入********************************************************/
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    
    GPIO_InitStruct.Pin = KEY11_PIN;
	HAL_GPIO_Init(KEY11_PORT, &GPIO_InitStruct);
    
    LED1_RST_DIS;
    LED2_RST_DIS;

}

