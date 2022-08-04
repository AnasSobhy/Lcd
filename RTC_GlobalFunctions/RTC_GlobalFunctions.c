/*******************************************************************************
* Title                 :   RTC_GlobalFunctions   
* Filename              :   RTC_GlobalFunctions.c
* Author                :   Edge Technology
* Origin Date           :   07/07/2020
* Version               :   1.0.0
* Compiler              :   IAR compiler
* Target                :   STM32F103C8T6
* Notes                 :   None
*******************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#include "stm32f1xx_hal.h"
#include "stdint.h"

/* Private variables ---------------------------------------------------------*/
volatile uint16_t gServerSecondsCounter = 0;

/* External variables --------------------------------------------------------*/
extern RTC_HandleTypeDef hrtc;


//Real Time Clock callback function every Second

void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc)
{
  gServerSecondsCounter++;
}
