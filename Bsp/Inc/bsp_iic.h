#ifndef __MYIIC_H
#define __MYIIC_H 

#include "main.h" 	
#include "delay.h"

#define IIC_PORT                GPIOB
#define IIC_PIN                 GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_10|GPIO_PIN_11


#define IIC_SCL_PORT            GPIOB
#define IIC_SCL_PIN             GPIO_PIN_6

#define IIC_SDA_PORT            GPIOB
#define IIC_SDA_PIN             GPIO_PIN_7


#define I2C_SCL_H			 	(I2C_SCL_PORT->BSRR = I2C_SCL_PIN)
#define I2C_SCL_L	            (I2C_SCL_PORT->BRR = I2C_SCL_PIN)

#define I2C_SDA_H				(I2C_SDA_PORT->BSRR = I2C_SDA_PIN)
#define I2C_SDA_L				(I2C_SDA_PORT->BRR = I2C_SDA_PIN)

#define READ_I2C_SDA   			((I2C_SDA_PORT->IDR & I2C_SDA_PIN) != 0)	/* 读SDA口线状态 */

#define EE_SDA_HIGH()		    I2C_SDA_H
#define	EE_SDA_LOW()		    I2C_SDA_L
#define	EE_SCL_HIGH()		    I2C_SCL_H
#define	EE_SCL_LOW()		    I2C_SCL_L
#define	EE_SDA_READ()		    READ_I2C_SDA

typedef struct
{
    GPIO_TypeDef *iic_scl_port;
    uint32_t        iic_scl_pin;
    GPIO_TypeDef *iic_sda_port;
    uint32_t        iic_sda_pin;
}IIC_gpio_typedef;

//I2C所有操作函数
void I2C_Init(void);                //初始化I2C的IO口				 
void I2C_Start(uint8_t ch);				//发送I2C开始信号
void I2C_Stop(uint8_t ch);	  			//发送I2C停止信号

void I2C_Send_Byte(uint8_t ch,u8 txd);			//I2C发送一个字节
u8 I2C_Read_Byte(uint8_t ch);//I2C读取一个字节
u8 I2C_Wait_Ack(uint8_t ch); 				//I2C等待ACK信号
void I2C_Ack(uint8_t ch);					//I2C发送ACK信号
void I2C_NAck(uint8_t ch);				//I2C不发送ACK信号


void EE_delay(void);



#endif
















