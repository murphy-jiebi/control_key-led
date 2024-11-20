#include "task_com.h"
#include "protocol.h"
#include "bsp_usart.h"
#include "bsp_can.h"

void TaskComDebug(void)
{
    
    
}

void TaskCAN(void)
{
    if(canRx.flag)
    {
        canRx.flag=0;
        
    }
}
void TaskCom(void)
{
    TaskCAN();
    
}
