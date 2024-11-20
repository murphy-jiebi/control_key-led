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
  //GPIOB8,B9��ʼ������
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
*	�� �� ��: EE_Start
*	����˵��: CPU����EE���������ź�
*	��    ��:  ��
*	�� �� ֵ: ��
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
*	�� �� ��: void EE_Stop(void)
*	����˵��: CPU����EE����ֹͣ�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
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
*	�� �� ��: EE_SendByte
*	����˵��: CPU��EE�����豸����8bit����
*	��    ��:  _ucByte �� �ȴ����͵��ֽ�
*	�� �� ֵ: ��
**********************************************************************************************************/
void I2C_Send_Byte(uint8_t ch,uint8_t _ucByte)
{
	uint8_t i;
    if(ch>=IIC_CH_SIZE)
    {
        return;
    }
	/* �ȷ����ֽڵĸ�λbit7 */
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
			 IIC_SDA_H(ch); // �ͷ�����
		}
		_ucByte <<= 1;	/* ����һ��bit */
		EE_delay();
	}
}

/**********************************************************************************************************
*	�� �� ��: EE_ReadByte
*	����˵��: CPU��EE�����豸��ȡ8bit����
*	��    ��:  ��
*	�� �� ֵ: ����������
**********************************************************************************************************/
uint8_t I2C_Read_Byte(uint8_t ch)
{
	uint8_t i;
	uint8_t value;

	/* ������1��bitΪ���ݵ�bit7 */
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
*	�� �� ��: EE_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    ��:  ��
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
**********************************************************************************************************/
uint8_t I2C_Wait_Ack(uint8_t ch)
{
	uint8_t re;

	IIC_SDA_H(ch);	/* CPU�ͷ�SDA���� */
	EE_delay();
	IIC_SCL_H(ch);	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	EE_delay();
	if (IIC_SDA_READ(ch))	/* CPU��ȡSDA����״̬ */
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
*	�� �� ��: EE_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void I2C_Ack(uint8_t ch)
{
    
	IIC_SDA_L(ch);	/* CPU����SDA = 0 */
	EE_delay();
	
	IIC_SCL_H(ch);	/* CPU����1��ʱ�� */
	EE_delay();
	IIC_SCL_L(ch);
	EE_delay();
	IIC_SDA_H(ch);	/* CPU�ͷ�SDA���� */
}

/**********************************************************************************************************
*	�� �� ��: EE_NAck
*	����˵��: CPU����1��NACK�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
**********************************************************************************************************/
void I2C_NAck(uint8_t ch)
{
	IIC_SDA_H(ch);	/* CPU����SDA = 1 */
	EE_delay();
	IIC_SCL_H(ch);	/* CPU����1��ʱ�� */
	EE_delay();
	IIC_SCL_L(ch);
	EE_delay();
}

































