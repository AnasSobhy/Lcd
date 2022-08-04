/*******************************************************************************
* Title                 :   MeteringChip_ISRFunctions   
* Filename              :   MeteringChip_ISRFunctions.c
* Author                :   Edge Technology (Mahmoud Gamal)
* Origin Date           :   25/03/2020
* Version               :   1.0.0
* Compiler              :   IAR compiler
* Target                :   STM32F302xC
* Notes                 :   None
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include "main.h"
#include "CAN_GlobalFunctions.h"

/* Private variables ---------------------------------------------------------*/

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan;


/* CAN Message Reception ISR -------------------------------------------------*/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  HAL_CAN_MyRxMessage();
}

 // /* USER CODE BEGIN CAN_Init 2 */
  
  // //configure filter structure 
  // CAN_FilterTypeDef canFilter = {0};
  
  // canFilter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  // canFilter.FilterIdHigh = 0;
  // canFilter.FilterIdLow = 0;
  // canFilter.FilterMaskIdHigh = 0;
  // canFilter.FilterMaskIdLow = 0;
  // canFilter.FilterScale = CAN_FILTERSCALE_32BIT;
  // canFilter.FilterActivation = CAN_FILTER_ENABLE;
  // canFilter.FilterMode = CAN_FILTERMODE_IDMASK;
  // canFilter.FilterBank = 0;
  
  // if(HAL_CAN_ConfigFilter(&hcan, &canFilter) != HAL_OK)
  // {
    // Error_Handler();
  // }
  
  // if(HAL_CAN_Start(&hcan) != HAL_OK)
  // {
    // Error_Handler();
  // }
  
  // if(HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  // {
    // Error_Handler();
  // }
  
  // /* USER CODE END CAN_Init 2 */



