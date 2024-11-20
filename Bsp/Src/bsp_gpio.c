#include "bsp_gpio.h"

key_gpio_typedef key_gpio[14]=
{
	{KEY11_PORT,KEY11_PIN},
	{KEY12_PORT,KEY12_PIN},
	{KEY13_PORT,KEY13_PIN},
	{KEY14_PORT,KEY14_PIN},
	{KEY15_PORT,KEY15_PIN},
	{KEY16_PORT,KEY16_PIN},
	{KEY17_PORT,KEY17_PIN},
	
	{KEY21_PORT,KEY21_PIN},
	{KEY22_PORT,KEY22_PIN},
	{KEY23_PORT,KEY23_PIN},
	{KEY24_PORT,KEY24_PIN},
	{KEY25_PORT,KEY25_PIN},
	{KEY26_PORT,KEY26_PIN},
	{KEY27_PORT,KEY27_PIN},
};
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
    GPIO_InitStruct.Pull = GPIO_PULLUP;
	for(uint8_t i=0;i<14;i++)
	{
		GPIO_InitStruct.Pin = key_gpio[i].key_pin;
		HAL_GPIO_Init(key_gpio[i].key_port, &GPIO_InitStruct);
	}
    
    LED1_RST_DIS;
    LED2_RST_DIS;

}

