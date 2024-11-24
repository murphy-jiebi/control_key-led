#include "bsp_can.h"


CAN_HandleTypeDef hcan;
CAN_TxHeaderTypeDef txheader;
uint32_t txMailbox;

can_data_typedef canRx;

void bsp_can_Init(void)
{
    CAN_FilterTypeDef sFilterConfig;
    
    hcan.Instance = CAN1;
    hcan.Init.Prescaler = 9;
    hcan.Init.Mode = CAN_MODE_NORMAL;
    hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
    hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
    hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
    hcan.Init.TimeTriggeredMode = DISABLE;
    hcan.Init.AutoBusOff = DISABLE;
    hcan.Init.AutoWakeUp = DISABLE;
    hcan.Init.AutoRetransmission = ENABLE;
    hcan.Init.ReceiveFifoLocked = DISABLE;
    hcan.Init.TransmitFifoPriority = DISABLE;
    if (HAL_CAN_Init(&hcan) != HAL_OK)
    {
        Error_Handler();
    }
    
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;
    if(HAL_CAN_ConfigFilter(&hcan,&sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    
    
    
    if(HAL_CAN_Start(&hcan) != HAL_OK)
    {
        Error_Handler();
    }
    if(HAL_CAN_ActivateNotification(&hcan,CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }
    
}
void CAN_SendMsg(uint8_t *buf,uint8_t len)
{
    
    txheader.RTR = CAN_RTR_DATA;
    txheader.IDE = CAN_ID_STD;
    txheader.StdId = devID;
    txheader.TransmitGlobalTime = DISABLE;
    txheader.DLC =len;
    
    HAL_CAN_AddTxMessage(&hcan,&txheader,buf,&txMailbox);
    
    while(HAL_CAN_GetTxMailboxesFreeLevel(&hcan) != 3)
    {
        
    }
}

void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(hcan->Instance==CAN1)
    {
        /* Peripheral clock enable */
        __HAL_RCC_CAN1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**CAN GPIO Configuration
        PA11     ------> CAN_RX
        PA12     ------> CAN_TX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_11;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_12;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    }
}

/**
* @brief CAN MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hcan: CAN handle pointer
* @retval None
*/
void HAL_CAN_MspDeInit(CAN_HandleTypeDef* hcan)
{
    if(hcan->Instance==CAN1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_CAN1_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);
        HAL_NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
    }

}
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    HAL_CAN_IRQHandler(&hcan);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef CAN_rxheader;
    if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN_rxheader,canRx.buf) == HAL_OK)
    {
        if(CAN_rxheader.StdId == 0x01)
        {
            canRx.len = CAN_rxheader.DLC;
            canRx.flag = 1;
        }
        
//        CAN_SendMsg(canRx.buf,canRx.len);
    }
}



