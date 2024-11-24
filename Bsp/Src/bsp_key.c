#include "bsp_key.h"
#include "bsp_gpio.h"
#include "bsp_tim.h"
#include "delay.h"

key_fifo_typedef key_fifo;

void KeyPush(uint8_t val)
{
    key_fifo.buf[key_fifo.write]=val;
    if(++key_fifo.write>KEY_FIFO_MAX-1)
    {
        key_fifo.write=0;
    }
}

uint8_t KeyPop(void)
{
    uint8_t val=0;
    if(key_fifo.read==key_fifo.write)
    {
        return 0;
    }
    val=key_fifo.buf[key_fifo.read];
    if(++key_fifo.read>KEY_FIFO_MAX-1)
    {
        key_fifo.read=0;
    }
    return val;
}

uint8_t KeyScan(void)
{
    uint8_t i=0;
	for(i=0;i<14;i++)
    {
        if(HAL_GPIO_ReadPin(key_gpio[i].key_port,key_gpio[i].key_pin) == GPIO_PIN_RESET)
        {
            delay_ms(10);
            if(HAL_GPIO_ReadPin(key_gpio[i].key_port,key_gpio[i].key_pin) == GPIO_PIN_RESET)
            {
                return i+1;
            }
        }      
    }
	return 0;
}




