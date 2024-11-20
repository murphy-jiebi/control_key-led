#include "bsp_iic.h"
#include "delay.h"

#define IIC_CH_SIZE         2

#define IIC_SDA_H(ch)       HAL_GPIO_WritePin(iic_gpio[ch].iic_sda_port,iic_gpio[ch].iic_sda_pin,GPIO_PIN_SET)
#define IIC_SDA_L(ch)       HAL_GPIO_WritePin(iic_gpio[ch].iic_sda_port,iic_gpio[ch].iic_sda_pin,GPIO_PIN_RESET)

#define IIC_SCL_H(ch)       HAL_GPIO_WritePin(iic_gpio[ch].iic_scl_port,iic_gpio[ch].iic_scl_pin,GPIO_PIN_SET)
#define IIC_SCL_L(ch)       HAL_GPIO_WritePin(iic_gpio[ch].iic_scl_port,iic_gpio[ch].iic_scl_pin,GPIO_PIN_RESET)

#define IIC_SDA_READ(ch)    HAL_GPIO_ReadPin(iic_gpio[ch].iic_sda_port,iic_gpio[ch].iic_sda_pin)


IIC_gpio_typedef  iic_gpio[2]=
{
    {GPIOB,GPIO_PIN_6,GPIOB,GPIO_PIN_7},
    {GPIOB,GPIO_PIN_10,GPIOB,GPIO_PIN_11},
};

void bsp_IIC_Init(void)
{			
  //GPIOB8,B9初始化设置
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    
    for(uint8_t i=0;i<IIC_CH_SIZE;i++)
    {
        GPIO_InitStruct.Pin = iic_gpio[i].iic_scl_pin;
        HAL_GPIO_Init(iic_gpio[i].iic_scl_port, &GPIO_InitStruct);
        
        
        GPIO_InitStruct.Pin = iic_gpio[i].iic_sda_pin;
        HAL_GPIO_Init(iic_gpio[i].iic_sda_port, &GPIO_InitStruct);
        
        IIC_SCL_H(i);
        
        IIC_SDA_H(i);
    }
}

void EE_delay(void)
{
	uint8_t i;
	for (i = 0; i < 50; i++);
}
/**********************************************************************************************************
*	函 数 名: EE_Start
*	功能说明: CPU发起EE总线启动信号
*	形    参:  无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Start(uint8_t ch)
{
    if(ch>=IIC_CH_SIZE)
    {
        return;
    }
    IIC_SDA_H(ch);
    IIC_SCL_H(ch);
    EE_delay();
    
    IIC_SDA_L(ch);
    EE_delay();
    
    IIC_SCL_L(ch);
    EE_delay();
}
/*********************************************************************************************************
*	函 数 名: void EE_Stop(void)
*	功能说明: CPU发起EE总线停止信号
*	形    参:  无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Stop(uint8_t ch)
{
    if(ch>=IIC_CH_SIZE)
    {
        return;
    }
    IIC_SDA_L(ch);
    IIC_SCL_H(ch);
    
    EE_delay();
    IIC_SDA_H(ch);
    EE_delay();
}

/**********************************************************************************************************
*	函 数 名: EE_SendByte
*	功能说明: CPU向EE总线设备发送8bit数据
*	形    参:  _ucByte ： 等待发送的字节
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Send_Byte(uint8_t ch,uint8_t _ucByte)
{
	uint8_t i;
    if(ch>=IIC_CH_SIZE)
    {
        return;
    }
	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++)
	{
		if (_ucByte & 0x80)
		{
			IIC_SDA_H(ch);
		}
		else
		{
			IIC_SDA_L(ch);
		}
		EE_delay();
		IIC_SCL_H(ch);
		EE_delay();
		IIC_SCL_L(ch);
		if (i == 7)
		{
			 IIC_SDA_H(ch); // 释放总线
		}
		_ucByte <<= 1;	/* 左移一个bit */
		EE_delay();
	}
}

/**********************************************************************************************************
*	函 数 名: EE_ReadByte
*	功能说明: CPU从EE总线设备读取8bit数据
*	形    参:  无
*	返 回 值: 读到的数据
**********************************************************************************************************/
uint8_t I2C_Read_Byte(uint8_t ch)
{
	uint8_t i;
	uint8_t value;

	/* 读到第1个bit为数据的bit7 */
	value = 0;
	for (i = 0; i < 8; i++)
	{
		value <<= 1;
		IIC_SCL_H(ch);
		EE_delay();
		if (IIC_SDA_READ(ch))
		{
			value++;
		}
		IIC_SCL_L(ch);
		EE_delay();
	}
	return value;
}

/**********************************************************************************************************
*	函 数 名: EE_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参:  无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
**********************************************************************************************************/
uint8_t I2C_Wait_Ack(uint8_t ch)
{
	uint8_t re;

	IIC_SDA_H(ch);	/* CPU释放SDA总线 */
	EE_delay();
	IIC_SCL_H(ch);	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	EE_delay();
	if (IIC_SDA_READ(ch))	/* CPU读取SDA口线状态 */
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	IIC_SCL_L(ch);
	EE_delay();
	return re;
}

/**********************************************************************************************************
*	函 数 名: EE_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参:  无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_Ack(uint8_t ch)
{
    
	IIC_SDA_L(ch);	/* CPU驱动SDA = 0 */
	EE_delay();
	
	IIC_SCL_H(ch);	/* CPU产生1个时钟 */
	EE_delay();
	IIC_SCL_L(ch);
	EE_delay();
	IIC_SDA_H(ch);	/* CPU释放SDA总线 */
}

/**********************************************************************************************************
*	函 数 名: EE_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参:  无
*	返 回 值: 无
**********************************************************************************************************/
void I2C_NAck(uint8_t ch)
{
	IIC_SDA_H(ch);	/* CPU驱动SDA = 1 */
	EE_delay();
	IIC_SCL_H(ch);	/* CPU产生1个时钟 */
	EE_delay();
	IIC_SCL_L(ch);
	EE_delay();
}

































