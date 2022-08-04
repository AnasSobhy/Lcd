/*******************************************************************************
* Title                 :   CAN_GlobalFunctions   
* Filename              :   CAN_GlobalFunctions.c
* Author                :   Edge Technology
* Origin Date           :   15/07/2020
* Version               :   1.0.0
* Compiler              :   IAR compiler
* Target                :   STM32F103c8
* Notes                 :   None
*******************************************************************************/
/******************************************************************************
* Includes
*******************************************************************************/
#include "CAN_GlobalFunctions.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>


/* Private variables ---------------------------------------------------------*/
static CAN_TxHeaderTypeDef TX_Header;
static uint8_t LCD_CAN_stdID = LCD_CAN_ID; 
char gCAN_RxMessageFixed[CAN_RxMessageLength];

Currents_t measuredCurrent;
Voltages_t measuredVoltage;
Powers_t   measuredPower;
Energies_t measuredEnergy;
Harmonics_t measuredHarmonics;
char temperatureValue[4];

char unitID[5];
char ctValue[5];
char timeInterval[3];
char setPiont[3];
char simOperator[10] = "Automaic";
uint8_t passwordValue = 0;
uint8_t energyResetFlag = 0;

char clockValue[6];
char signalValue[3];
/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan;

/* Functions Definitions -----------------------------------------------------*/
/*******************************************************************************
* Function : Handle_CAN_Recieved_Messages();
* 
* Description:
*
* This function is used to handel CAN Recieved Messages
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Handle_CAN_Recieved_Data_Messages(void)
{  
	char* valuePTRStart = NULL;
	
	switch(gCAN_RxMessageFixed[0])
	{
	case 'i':	//refer to iD
		strcpy(unitID, strchr(gCAN_RxMessageFixed, ':')+1);
		break;
	case 'C':	//refer to CT
		strcpy(ctValue, strchr(gCAN_RxMessageFixed, ':')+1);
		break;
	case 't':	//refer to timeInterval
		strcpy(timeInterval, strchr(gCAN_RxMessageFixed, ':')+1);
		break;
	case 'O':  //refer to sim Operator
		strcpy(simOperator, strchr(gCAN_RxMessageFixed, ':')+1);
		switch(simOperator[0])
		{
			case 'w': //Small W (0x77)
				strcpy(simOperator, "we");				
				break;
			case 'V':
				strcpy(simOperator, "Vodafone");
				break;
			case 'E':
				strcpy(simOperator, "Etisalat");
				break;
			case 'O':
				strcpy(simOperator, "Orange");
				break;
			default:
				strcpy(simOperator, "Automatic");
				break;
		}
		break;
	case 's':  //refer to set Point (small s)
		strcpy(setPiont, strchr(gCAN_RxMessageFixed, ':')+1);
		break;
	case 'c':  //refer to clock
		strcpy(clockValue, strchr(gCAN_RxMessageFixed, ':')+1);
		break;
	case 'S':  //refer to Signal (capital S)
		strcpy(signalValue, strchr(gCAN_RxMessageFixed, ':')+1);
		break;
	case 'p':  //refer to password (small p)
		passwordValue = *(strchr(gCAN_RxMessageFixed, ':')+1) - '0';
		break;
	case 'V':	//refer to voltages
		valuePTRStart = strchr(gCAN_RxMessageFixed, ':')+1;
		memcpy(measuredVoltage.phase1, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);

		valuePTRStart = strchr(valuePTRStart, ':')+1;
		memcpy(measuredVoltage.phase2, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);

		valuePTRStart = strchr(valuePTRStart, ':')+1;
		strcpy(measuredVoltage.phase3, valuePTRStart);
		break;
	case 'I': //refer to currents
		valuePTRStart = strchr(gCAN_RxMessageFixed, ':')+1;
		memcpy(measuredCurrent.phase1, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);

		valuePTRStart = strchr(valuePTRStart, ':')+1;
		memcpy(measuredCurrent.phase2, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);

		valuePTRStart = strchr(valuePTRStart, ':')+1;
		memcpy(measuredCurrent.phase3, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);
		
		valuePTRStart = strchr(valuePTRStart, ':')+1;
		strcpy(measuredCurrent.neutral, valuePTRStart);
		break;
	case 'P': //refer to Power
		valuePTRStart = strchr(gCAN_RxMessageFixed, ':')+1;
		memcpy(measuredPower.phase1, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);

		valuePTRStart = strchr(valuePTRStart, ':')+1;
		memcpy(measuredPower.phase2, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);

		valuePTRStart = strchr(valuePTRStart, ':')+1;
		strcpy(measuredPower.phase3, valuePTRStart);
		break;
	case 'E': //refer to Energy
		valuePTRStart = strchr(gCAN_RxMessageFixed, ':')+1;
		memcpy(measuredEnergy.active, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);

		valuePTRStart = strchr(valuePTRStart, ':')+1;
		strcpy(measuredEnergy.reactive, valuePTRStart);
		break;
	case 'T':	//refer to Temperature
		strcpy(temperatureValue, strchr(gCAN_RxMessageFixed, ':')+1);
		break;
	case 'H': //refer to harmonics
		valuePTRStart = strchr(gCAN_RxMessageFixed, ':')+1;
		memcpy(measuredHarmonics.Vphase1, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);

		valuePTRStart = strchr(valuePTRStart, ':')+1;
		memcpy(measuredHarmonics.Vphase2, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);

		valuePTRStart = strchr(valuePTRStart, ':')+1;
		memcpy(measuredHarmonics.Vphase3, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);
		
		valuePTRStart = strchr(valuePTRStart, ':')+1;
		memcpy(measuredHarmonics.Iphase1, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);

		valuePTRStart = strchr(valuePTRStart, ':')+1;
		memcpy(measuredHarmonics.Iphase2, valuePTRStart, strchr(valuePTRStart, ':')-valuePTRStart);
		
		valuePTRStart = strchr(valuePTRStart, ':')+1;
		strcpy(measuredHarmonics.Iphase3, valuePTRStart);
		break;
	default:
		break;
	}
}

/*******************************************************************************
* Function : HAL_CAN_MyTxMessage();
* 
* Description:
*
* This function is used to send a character
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void HAL_CAN_MyTxMessage(char newMessage[], int n)
{
  //configure TX_Header structure
  TX_Header.DLC = 8; 
  TX_Header.IDE = CAN_ID_STD;
  TX_Header.RTR = CAN_RTR_DATA;
  TX_Header.StdId = (uint32_t)LCD_CAN_stdID;
  
  char message[CAN_RxMessageLength] = {0};
  strcpy(message, newMessage);
    
  switch(strlen(message) % 8)
  {
  case 1:
    strcat(message, "$$$$$$$");
    break;
  case 2:
    strcat(message, "$$$$$$");
    break;
  case 3:
    strcat(message, "$$$$$");
    break;
  case 4:
    strcat(message, "$$$$");
    break;    
  case 5:
    strcat(message, "$$$");
    break;    
  case 6:
    strcat(message, "$$");
    break;
  case 7:
    strcat(message, "$");
    break;
  default:
    strcat(message, "$$$$$$$$");
    break;
  }
  
  uint8_t loopCounter = strlen(message) / 8;
  uint32_t TxMailbox = 0;
  
  char CANTxBuffer[9] = {0};
  uint8_t i = 0;
  for(i=0; i<loopCounter; i++)
  { 
     sprintf(CANTxBuffer,"%.8s", message+(i*8));
     
     HAL_CAN_AddTxMessage(&hcan, &TX_Header, (uint8_t*)CANTxBuffer, &TxMailbox);
     
     while(HAL_CAN_IsTxMessagePending(&hcan, TxMailbox))
     {
       //
     }
  }
}

/*******************************************************************************
* Function : HAL_CAN_MyRxMessage();
* 
* Description:
*
* This function is used to recieve a character
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void HAL_CAN_MyRxMessage(void)
{
	HAL_CAN_DeactivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

	CAN_RxHeaderTypeDef RX_Header;

	static char lCAN_RxMessage[CAN_RxMessageLength] = {0};
	char CANRxBuffer[9] = {0};

	HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &RX_Header, (uint8_t*)CANRxBuffer);

	char *pChar = strchr(CANRxBuffer, '$');
	if(*pChar == '$')
	{
		memset(pChar, 0, strlen(pChar)); 
		strcat(lCAN_RxMessage, CANRxBuffer);
		strcpy(gCAN_RxMessageFixed, lCAN_RxMessage);
		memset(lCAN_RxMessage, 0, CAN_RxMessageLength);

		//Handle Recieved data 
		Handle_CAN_Recieved_Data_Messages();
	}
	else
	{
		strcat(lCAN_RxMessage, CANRxBuffer);
	}

	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

/*******************************************************************************
* Function : CAN_Get_Value_upon_on_Identifier();
* 
* Description:
*
* This function is used to recieve a character
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void CAN_Get_Value_upon_on_Identifier(uint32_t stdID)
{
	TX_Header.DLC = 8;
	TX_Header.IDE = CAN_ID_STD;
	TX_Header.RTR = CAN_RTR_REMOTE;
  	TX_Header.StdId = (uint32_t)stdID;
	 
	uint32_t TxMailbox;
	HAL_CAN_AddTxMessage(&hcan, &TX_Header, (uint8_t*)0, &TxMailbox);
     
    while(HAL_CAN_IsTxMessagePending(&hcan, TxMailbox))
	{
		//
	}
}
