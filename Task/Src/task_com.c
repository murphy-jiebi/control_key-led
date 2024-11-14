#include "task_com.h"
#include "protocol.h"
#include "bsp_usart.h"


void TaskComLora(void)
{
    uint8_t res=0;
    uint8_t txbuf[15]={0};
    if(usart2.usRxFrame)
    {
        usart2.usRxFrame=0;
        res=ProtocolParse(usart2.pRxBuf,usart2.usRxCount);
        if(res)
        {
            res=ProtocolPackage(txbuf,res);
            HAL_UART_Transmit(&huart2,txbuf,res,1000);
        }
    }
}
void TaskComDebug(void)
{
    
    
}


void TaskCom(void)
{
    TaskComLora();
    
}
