#include "delay.h"

void delay_us(u16 us)
{
	uint32_t delay=us*40;
	do{
		__NOP();
	}while(delay--);
}

void delay_ms(u16 ms)
{
//	while(ms--!=0)
//	{
//		delay_us(1000);
//	}
	uint32_t tickstart = HAL_GetTick();
	uint32_t wait = ms;

  /* Add a period to guaranty minimum wait */
	if (wait < HAL_MAX_DELAY)
	{
		wait += (uint32_t)uwTickFreq;
	}
	while ((HAL_GetTick() - tickstart) < wait)
	{
	}
}
void delay_s(u16 s)
{
	while(s--!=0)
	{
		delay_ms(1000);
	}
}

void delay_US(u16 us)
{
	u32 Delay = us * 16;
	do
	{
			__NOP();
	}
	while(Delay--);
}
void delay_MS(u16 ms)
{
	int i,j;
	for(i=1;i<ms;i++)
	{
		for(j=0;j<3200;j++);
	}
}
/************************ (C) COPYRIGHT murphy_jiebi*****END OF FILE****/

