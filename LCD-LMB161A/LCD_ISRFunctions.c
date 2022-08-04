/*******************************************************************************
* Title                 :   LCD_Modes   
* Filename              :   LCD_Modes.c
* Author                :   Edge Technology
* Origin Date           :   07/07/2020
* Version               :   1.0.0
* Compiler              :   IAR compiler
* Target                :   STM32F103C8T6
* Notes                 :   None
*
* THIS SOFTWARE IS PROVIDED BY BENINGO ENGINEERING "AS IS" AND ANY EXPRESSED
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL BENINGO ENGINEERING OR ITS CONTRIBUTORS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
*  
*******************************************************************************/
/*************** SOURCE REVISION LOG *******************************************
*
*    Date    Version   Author         Description 
*  07/07/20   1.0.0   Mahmoud Gamal  Interface Edited.
*
*******************************************************************************/

/*******************************************************************************
* Includes
*******************************************************************************/
#include "stm32f1xx_hal.h"
#include "main.h"
#include "LCD_Modes.h"
#include "LCD_LMB161A.h"
#include "CAN_GlobalFunctions.h"

#include <string.h>
/* Private variables ---------------------------------------------------------*/
volatile MODE_t MODE = {1, 0, 0};
volatile uint8_t modeIndicator = 1;
volatile uint8_t pressIndicator = 1;
volatile uint8_t editIndicator = 1;

/* External variables --------------------------------------------------------*/
extern volatile uint8_t insideLevelLcdFlag;
extern LCD_MODE_LEVEL_e lcdModeLevelSelect;
extern TIM_HandleTypeDef htim2;

extern char unitID[5];
extern char ctValue[5];
extern char timeInterval[3];
extern char setPiont[3];
extern char simOperator[10];
extern uint8_t passwordValue;
extern uint8_t energyResetFlag;


/* Functions definitions ******************************************************/
/******************************************************************************
* Function : Update_Unit_ID();
* 
* Description:
*
* This function is used to send the new value of specific variable to the main board
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Update_UnitID_in_mainUnit(void)
{
	char message[7] = "i:";
	strcat(message, unitID);
	HAL_CAN_MyTxMessage(message, strlen(message));
}

/******************************************************************************
* Function : Update_CtRatio_in_mainUnit();
* 
* Description:
*
* This function is used to send the new value of specific variable to the main board
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Update_CtRatio_in_mainUnit(void)
{
	char message[7] = "C:"; //C capital
	strcat(message, ctValue);
	HAL_CAN_MyTxMessage(message, strlen(message));
}

/******************************************************************************
* Function : Update_TimeInterval_in_mainUnit();
* 
* Description:
*
* This function is used to send the new value of specific variable to the main board
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Update_TimeInterval_in_mainUnit(void)
{
	char message[7] = "t:";
	strcat(message, timeInterval);
	HAL_CAN_MyTxMessage(message, strlen(message));
}

/******************************************************************************
* Function : Update_SimOperator_in_mainUnit();
* 
* Description:
*
* This function is used to send the new value of specific variable to the main board
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Update_SimOperator_in_mainUnit(void)
{
	char message[15];
	sprintf(message, "O:%c", simOperator[0]);
	HAL_CAN_MyTxMessage(message, strlen(message));
}


/******************************************************************************
* Function : Update_SetPoint_in_mainUnit();
* 
* Description:
*
* This function is used to send the new value of specific variable to the main board
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Update_SetPoint_in_mainUnit(void)
{
	char message[7] = "s:";
	strcat(message, setPiont);
	HAL_CAN_MyTxMessage(message, strlen(message));
}


/******************************************************************************
* Function : Update_Password_in_mainUnit();
* 
* Description:
*
* This function is used to send the new value of specific variable to the main board
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Update_Password_in_mainUnit(void)
{
	char message[5]; //= "p:";
	sprintf(message, "p:%d",passwordValue);
	HAL_CAN_MyTxMessage(message, strlen(message));
}

/******************************************************************************
* Function : Update_EnergyResetFlag_in_mainUnit();
* 
* Description:
*
* This function is used to send the new value of specific variable to the main board
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Update_EnergyResetFlag_in_mainUnit(void)
{
	char message[4]= "r:1";
	HAL_CAN_MyTxMessage(message, strlen(message));
}

/*******************************************************************************
* Function : Editing_Variable_Pressing_UP();
* 
* Description:
*
* This function is used to handle the varibale when the user in editing mode
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Editing_Variable_Pressing_UP(void)
{
	uint8_t yPosition = LCD_Y();
	
	switch(MODE.secondLevel)
	{
	case SETTINGS_LEV2_UNIT_ID: //ID //9 is the ofset on the display
		unitID[yPosition-9] = (unitID[yPosition-9] >= '9') ? '9' : unitID[yPosition-9]+1;
		LCD_Send_Char(unitID[yPosition-9]);
		LCD_GoTo_XY(1, LCD_Y()-1);
		break;
	case SETTINGS_LEV2_CT_RATIO: //CT Ratio //10 is the ofset on the display
		ctValue[yPosition-10] = (ctValue[yPosition-10] >= '9') ? '9' : ctValue[yPosition-10]+1;
		LCD_Send_Char(ctValue[yPosition-10]);
		LCD_GoTo_XY(1, LCD_Y()-1);
		break;
	case SETTINGS_LEV2_SYNCH_TIME: //SynchTime //1 is the ofset on the display
		timeInterval[yPosition-1] = (timeInterval[yPosition-1] >= '9') ? '9' : timeInterval[yPosition-1]+1;
		LCD_Send_Char(timeInterval[yPosition-1]);
		LCD_GoTo_XY(2, LCD_Y()-1);
		break;
	case SETTINGS_LEV2_SET_POINT:
		setPiont[yPosition-11] = (setPiont[yPosition-11] >= '9') ? '9' : setPiont[yPosition-11]+1;
		LCD_Send_Char(setPiont[yPosition-11]);
		LCD_GoTo_XY(1, LCD_Y()-1);
		break;
	case SETTINGS_LEV2_OPERATOR: //Operator
		switch(simOperator[0])
		{
			case 'A':
				strcpy(simOperator, "Vodafone");
				break;
			case 'V':
				strcpy(simOperator, "Etisalat");
				break;
			case 'E':
				strcpy(simOperator, "Orange");
				break;
			case 'O':
				strcpy(simOperator, "we");
				break;
			default:
				strcpy(simOperator, "Automatic");
				break;
		}
		LCD_GoTo_XY(2, 1);
		LCD_Send_String("         ");
		LCD_GoTo_XY(2, 1);
		LCD_Send_String(simOperator);
		break;
	case SETTINGS_LEV2_PASSWORD:
		passwordValue = (passwordValue >= 9) ? 9 : passwordValue+1;
		LCD_Send_Char(passwordValue+'0');
		LCD_GoTo_XY(1, LCD_Y()-1);
		break;
	case SETTINGS_LEV2_ENERGY_RST:
		LCD_GoTo_XY(2, 1);
		LCD_Send_String("         ");
		LCD_GoTo_XY(2, 1);
		
		energyResetFlag ^= (1<<0);
		
		energyResetFlag == 1 ? LCD_Send_String("YES") : LCD_Send_String("NO");		
		
		LCD_GoTo_XY(2, LCD_Y());
		break;
	default:
		break;
	}
}

/******************************************************************************
* Function : Editing_Variable_Pressing_DOWN();
* 
* Description:
*
* This function is used to handle the varibale when the user in editing mode
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Editing_Variable_Pressing_DOWN(void)
{
	uint8_t yPosition = LCD_Y();
	
	switch(MODE.secondLevel)
	{
	case SETTINGS_LEV2_UNIT_ID: //ID //9 is the ofset on the display
		unitID[yPosition-9] = (unitID[yPosition-9] <= '0') ? '0' : unitID[yPosition-9]-1;
		LCD_Send_Char(unitID[yPosition-9]);
		LCD_GoTo_XY(1, LCD_Y()-1);
		break;
	case SETTINGS_LEV2_CT_RATIO: //CT Ratio //10 is the ofset on the display
		ctValue[yPosition-10] = (ctValue[yPosition-10] <= '0') ? '0' : ctValue[yPosition-10]-1;
		LCD_Send_Char(ctValue[yPosition-10]);
		LCD_GoTo_XY(1, LCD_Y()-1);
		break;
	case SETTINGS_LEV2_SYNCH_TIME: //SynchTime //1 is the ofset on the display
		timeInterval[yPosition-1] = (timeInterval[yPosition-1] <= '0') ? '0' : timeInterval[yPosition-1]-1;
		LCD_Send_Char(timeInterval[yPosition-1]);
		LCD_GoTo_XY(2, LCD_Y()-1);
		break;
	case SETTINGS_LEV2_SET_POINT:
		setPiont[yPosition-11] = (setPiont[yPosition-11] <= '0') ? '0' : setPiont[yPosition-11]-1;
		LCD_Send_Char(setPiont[yPosition-11]);
		LCD_GoTo_XY(1, LCD_Y()-1);
		break;
	case SETTINGS_LEV2_OPERATOR: //Operator
		switch(simOperator[0])
		{
			case 'A':
				strcpy(simOperator, "Vodafone");
				break;
			case 'V':
				strcpy(simOperator, "Etisalat");
				break;
			case 'E':
				strcpy(simOperator, "Orange");
				break;
			case 'O':
				strcpy(simOperator, "We");
				break;
			default:
				strcpy(simOperator, "Automatic");
				break;
		}
		LCD_GoTo_XY(2, 1);
		LCD_Send_String("         ");
		LCD_GoTo_XY(2, 1);
		LCD_Send_String(simOperator);
		break;
	case SETTINGS_LEV2_PASSWORD:
		passwordValue = (passwordValue <= 0) ? 0 : passwordValue-1;
		LCD_Send_Char(passwordValue+'0');
		LCD_GoTo_XY(1, LCD_Y()-1);
		break;
	case SETTINGS_LEV2_ENERGY_RST:
		LCD_GoTo_XY(2, 1);
		LCD_Send_String("         ");
		LCD_GoTo_XY(2, 1);
		
		energyResetFlag ^= (1<<0);
		
		energyResetFlag == 1 ? LCD_Send_String("YES") : LCD_Send_String("NO");		
		
		LCD_GoTo_XY(2, LCD_Y());
		break;
	default:
		break;
	}
}


/******************************************************************************
* Function : Button_UP_Handler();
* 
* Description:
*
* This function is used to handle the event when a user press the UP Button
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Button_UP_Handler(void)
{
	switch(lcdModeLevelSelect)
	{
	case LEVEL1_MODE:
		MODE.firstLevel++;
		MODE.secondLevel = 0;
		MODE.thirdLevel = 0;
		
		MODE.firstLevel = (MODE.firstLevel == SCREEN_NUMBERS) ? ((passwordValue==3) ? SCREEN_NUMBERS : 1) : (MODE.firstLevel > SCREEN_NUMBERS) ? 1 : MODE.firstLevel;
				
		break;
	case LEVEL2_MODE:
		MODE.secondLevel++;
		MODE.thirdLevel = 0;
		switch(MODE.firstLevel)
		{
		//case 1: do nothing
			//break;
		case METERING_MODE:
			MODE.secondLevel = (MODE.secondLevel > METERING_LEVEL2_TAPS_NUMBER) ? 1 : MODE.secondLevel;
			break;
		case SETTING_MODE:
			MODE.secondLevel = (MODE.secondLevel > SETTINGS_LEVEL2_TAPS_NUMBER) ? 1 : MODE.secondLevel; //mode 3 level 2 has 5 parameters
			break;
		case CALIBRATION_MODE: //Because the number of taps = 1
			MODE.secondLevel = 1;
			break;
		default:
			break;
		}
		break;
	case LEVEL3_MODE:
		MODE.thirdLevel++;
		switch(MODE.firstLevel)
		{
		//case 1: do nothing
			//break;
		case METERING_MODE:
			switch(MODE.secondLevel)
			{
			case METERING_LEV2_VOLTAGE:
			case METERING_LEV2_CURRENT:
			case METERING_LEV2_POWER:
				MODE.thirdLevel = (MODE.thirdLevel > VOLTAGE_TAPS_NUMBER) ? 1 : MODE.thirdLevel;
				break;
			case METERING_LEV2_HARMONICS:
				MODE.thirdLevel = (MODE.thirdLevel > HARMONICS_TAPS_NUMBER) ? 1 : MODE.thirdLevel;
				break;
			default:
				MODE.thirdLevel = 1;
				break;
			}
			break;
		case SETTING_MODE: //no taps in setting level 3 mode 
		case CALIBRATION_MODE: //no taps in callibration level 3 mode 
		default:
			MODE.thirdLevel = 1;
			break;
		}
		break;
	case EDIT_LEVEL_MODE:
		Editing_Variable_Pressing_UP();
		break;
	default:
		break;
	}
}

/******************************************************************************
* Function : Button_DOWN_Handler();
* 
* Description:
*
* This function is used to handle the event when a user press the DOWN Button
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Button_DOWN_Handler(void)
{
	switch(lcdModeLevelSelect)
	{
	case LEVEL1_MODE:
		MODE.firstLevel--;
		MODE.secondLevel = 0;
		MODE.thirdLevel = 0;
		
		MODE.firstLevel = (MODE.firstLevel < 1) ? ((passwordValue==3) ? SCREEN_NUMBERS : SCREEN_NUMBERS-1) : MODE.firstLevel;
		break;
	case LEVEL2_MODE:
		MODE.secondLevel--;
		MODE.thirdLevel = 0;
		switch(MODE.firstLevel)
		{
		//case 1: do nothing
			//break;
		case METERING_MODE:
			MODE.secondLevel = (MODE.secondLevel < 1) ? METERING_LEVEL2_TAPS_NUMBER : MODE.secondLevel;
			break;
		case SETTING_MODE:
			MODE.secondLevel = (MODE.secondLevel < 1) ? SETTINGS_LEVEL2_TAPS_NUMBER : MODE.secondLevel;
			break;
		case CALIBRATION_MODE: //Because the number of taps = 1
			MODE.secondLevel = 1;
			break;
		default:
			break;
		}
	case LEVEL3_MODE:
		MODE.thirdLevel--;
		switch(MODE.firstLevel)
		{
		//case 1: do nothing
			//break;
		case METERING_MODE:
			switch(MODE.secondLevel)
			{
			case METERING_LEV2_VOLTAGE:
			case METERING_LEV2_CURRENT:
			case METERING_LEV2_POWER:
				MODE.thirdLevel = (MODE.thirdLevel < 1) ? VOLTAGE_TAPS_NUMBER : MODE.thirdLevel;
				break;
			case METERING_LEV2_HARMONICS:
				MODE.thirdLevel = (MODE.thirdLevel < 1) ? HARMONICS_TAPS_NUMBER : MODE.thirdLevel;
				break;
			default:
				MODE.thirdLevel = 1;
				break;
			}
			break;
		case SETTING_MODE: //no taps in setting level 3 mode 
		case CALIBRATION_MODE: //no taps in callibration level 3 mode 
		default:
			MODE.thirdLevel = 1;
			break;
		}
		break;
	case EDIT_LEVEL_MODE:
		Editing_Variable_Pressing_DOWN();
		break;
	default:
		break;
	}
}


/*******************************************************************************
* Function : Button_PUSH_Handler();
* 
* Description:
*
* This function is used to handle the event when a user press the PUSH Button
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Button_PUSH_Handler(void)
{
	if(lcdModeLevelSelect == EDIT_LEVEL_MODE)
	{
		//save Value and send it to RTU
		switch(MODE.secondLevel)
		{
		case SETTINGS_LEV2_UNIT_ID: //ID
			Update_UnitID_in_mainUnit();
			break;
		case SETTINGS_LEV2_CT_RATIO:
			Update_CtRatio_in_mainUnit();
			break;
		case SETTINGS_LEV2_SYNCH_TIME: //SynchTime
			Update_TimeInterval_in_mainUnit();
			break;
		case SETTINGS_LEV2_SET_POINT:
			Update_SetPoint_in_mainUnit();
			break;
		case SETTINGS_LEV2_OPERATOR: //Operator
			Update_SimOperator_in_mainUnit();
			break;
		case SETTINGS_LEV2_PASSWORD: //Passowrd
			Update_Password_in_mainUnit();
			break;
		case SETTINGS_LEV2_ENERGY_RST: //Energy reset flag
			Update_EnergyResetFlag_in_mainUnit();
			break;
		default:
			break;
		}
		
		LCD_Send_Command(_cursor_off);
		lcdModeLevelSelect = LEVEL3_MODE;
		MODE.thirdLevel = 1;
		editIndicator = 1;
	}
	else
	{
		switch(++lcdModeLevelSelect)
		{
		case LEVEL1_MODE:
			MODE.secondLevel = 0;
			MODE.thirdLevel = 0;
			break;
		case LEVEL2_MODE:
			MODE.secondLevel = 1;
			MODE.thirdLevel = 0;
			break;
		case LEVEL3_MODE:
			MODE.thirdLevel = 1;
			break;
		default:
			if(MODE.firstLevel == SETTING_MODE) //Modes I can edit values inside
			{
				lcdModeLevelSelect = EDIT_LEVEL_MODE;
				editIndicator = 0; //to lock other activities in LCD
				
				//turn on curseor
				switch(MODE.secondLevel)
				{
				case SETTINGS_LEV2_UNIT_ID:
				case SETTINGS_LEV2_SET_POINT:
					LCD_GoTo_XY(LCD_X(), LCD_Y()-1);
					break;
				case SETTINGS_LEV2_CT_RATIO:
					LCD_GoTo_XY(LCD_X(), LCD_Y()-3);
					break;
				case SETTINGS_LEV2_SYNCH_TIME:
					LCD_GoTo_XY(LCD_X(), LCD_Y()-9);
					break;
				case SETTINGS_LEV2_PASSWORD:
					LCD_GoTo_XY(LCD_X(), LCD_Y()-1);
					break;
				case SETTINGS_LEV2_OPERATOR:
				case SETTINGS_LEV2_ENERGY_RST:
				default:
					break;
				}
				LCD_Send_Command(_cursor_on);
			}
			else
			{
				lcdModeLevelSelect = LEVEL3_MODE;
			}
			break;
		}
	}
}

/*******************************************************************************
* Function : Button_POP_Handler();
* 
* Description:
*
* This function is used to handle the event when a user press the POP Button
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Button_POP_Handler(void)
{
	if(lcdModeLevelSelect == EDIT_LEVEL_MODE)
	{
		//LCD_Send_Command(_cursor_off); (actually done in LCD_Modex() Function)
		lcdModeLevelSelect = LEVEL3_MODE;
		MODE.thirdLevel = 1;
		editIndicator =  1;
	}
	else
	{		
		switch(--lcdModeLevelSelect)
		{
		case LEVEL1_MODE:
			MODE.secondLevel = 0;
			MODE.thirdLevel = 0;
			break;
		case LEVEL2_MODE:
			MODE.thirdLevel = 0;
			break;
		case LEVEL3_MODE:
			break;
		default:
			lcdModeLevelSelect = LEVEL1_MODE;
			break;
		}
	}
}


/******************************************************************************
* Function : Button_RIGHT_Handler();
* 
* Description:
*
* This function is used to handle the event when a user press the RIGHT Button
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Button_RIGHT_Handler(void)
{
	uint8_t yPosition = LCD_Y();
	
	if((MODE.secondLevel!=SETTINGS_LEV2_OPERATOR) && (MODE.secondLevel!=SETTINGS_LEV2_PASSWORD)
	   && (MODE.secondLevel!=SETTINGS_LEV2_ENERGY_RST))
	{
		(yPosition < 16) ? (LCD_GoTo_XY(LCD_X(), yPosition+1)) : (LCD_X() == 1) ? LCD_GoTo_XY(2, 1) : LCD_GoTo_XY(1, 1);
		
		yPosition = LCD_Y();
		switch(MODE.secondLevel)
		{
		case SETTINGS_LEV2_UNIT_ID: //ID
			if((yPosition > 12) || (yPosition < 9)) {LCD_GoTo_XY(1, 9);} else{};
			break;
		case SETTINGS_LEV2_CT_RATIO: //CT RATIO 
			if((yPosition > 13) || (yPosition < 10)) {LCD_GoTo_XY(1, 10);} else{};
			break;
		case SETTINGS_LEV2_SYNCH_TIME: //SynchTime
			if((yPosition > 2) || (yPosition < 1)) {LCD_GoTo_XY(2, 1);} else{};
			break;
		case SETTINGS_LEV2_SET_POINT: 
			if ((yPosition > 12 || yPosition < 11)) {LCD_GoTo_XY(1, 11);} else{};
			break;
//		case SETTINGS_LEV2_OPERATOR: //Operator /*won't reach here*/
//		case SETTINGS_LEV2_PASSWORD: //Password /*won't reach here*/
		default:
			break;
		}
	}
}

/******************************************************************************
* Function : Button_LEFT_Handler();
* 
* Description:
*
* This function is used to handle the event when a user press the LEFT Button
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void Button_LEFT_Handler(void)
{
	uint8_t yPosition = LCD_Y();
	
	if((MODE.secondLevel!=SETTINGS_LEV2_OPERATOR) && (MODE.secondLevel!=SETTINGS_LEV2_PASSWORD)
	   && (MODE.secondLevel!=SETTINGS_LEV2_ENERGY_RST))
	{
		(yPosition > 1) ? (LCD_GoTo_XY(LCD_X(), yPosition-1)) : (LCD_X() == 1) ? LCD_GoTo_XY(2, 16) : LCD_GoTo_XY(1, 16);
		
		yPosition = LCD_Y();
		switch(MODE.secondLevel)
		{
		case SETTINGS_LEV2_UNIT_ID: //ID
			if((yPosition > 12) || (yPosition < 9)) {LCD_GoTo_XY(1, 12);} else{};
			break;
		case SETTINGS_LEV2_CT_RATIO: //CT RATIO 
			if((yPosition > 13) || (yPosition < 10)) {LCD_GoTo_XY(1, 13);} else{};
			break;
		case SETTINGS_LEV2_SYNCH_TIME: //SynchTime
			if((yPosition > 2) || (yPosition < 1)) {LCD_GoTo_XY(2, 2);} else{};
			break;
		case SETTINGS_LEV2_SET_POINT: 
			if ((yPosition > 12 || yPosition < 11)) {LCD_GoTo_XY(1, 12);} else{};
			break;
//		case SETTINGS_LEV2_OPERATOR: //Operator /*won't reach here*/
//		case SETTINGS_LEV2_PASSWORD: //Password /*won't reach here*/
		default:
			break;
		}

	}
}


/******************************************************************************
* Function : HAL_GPIO_EXTI_Callback();
* 
* Description:
*
* This function is used to Handle all LCD Pins
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(pressIndicator != 1)
		return;
	
	switch(GPIO_Pin)
	{
	case SW1_EXTI7_Pin: //Up
		HAL_TIM_Base_Start_IT(&htim2);
		pressIndicator = 0;
		modeIndicator = 1;
		insideLevelLcdFlag = 1;
		
		Button_UP_Handler();		

		break;
	case SW2_EXTI5_Pin: //Down
		HAL_TIM_Base_Start_IT(&htim2);
		pressIndicator = 0;
		modeIndicator = 1;
		insideLevelLcdFlag = 1;
				
		Button_DOWN_Handler();

		break;
	case SW3_EXTI6_Pin: //Left
		HAL_TIM_Base_Start_IT(&htim2);
		pressIndicator = 0;
		
		if(lcdModeLevelSelect == EDIT_LEVEL_MODE) {Button_LEFT_Handler();} else{}
		break;
	case SW4_EXTI4_Pin: //Right
		HAL_TIM_Base_Start_IT(&htim2);
		pressIndicator = 0;
		
		if(lcdModeLevelSelect == EDIT_LEVEL_MODE) {Button_RIGHT_Handler();} else{}
		break;
	case SW5_EXTI3_Pin: //POP
		if(MODE.firstLevel != 1)
		{
			HAL_TIM_Base_Start_IT(&htim2);
			pressIndicator = 0;
			modeIndicator = 1;
			insideLevelLcdFlag = 1;
			
			Button_POP_Handler();
		}
		else
		{
			//
		}
		break;
	case SW6_EXTI15_Pin: //PUSH 
		if(MODE.firstLevel != 1)
		{
			HAL_TIM_Base_Start_IT(&htim2);
			pressIndicator = 0;
			modeIndicator  = 1;
			insideLevelLcdFlag = 1;
			
			Button_PUSH_Handler();
		}
		else
		{
			//
		}
		break;
	default:
		break;
	}
}

/******************************************************************************
* Function : HAL_TIM_PeriodElapsedCallback();
* 
* Description:
*
* This function is used to Handle LCD pins clicks
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		static volatile uint8_t counter = 0;
		if(modeIndicator == 1)
		{
			insideLevelLcdFlag = 1;
			modeIndicator = 0;
		}
		else
		{
			//
		}
		
		if(++counter >= 100)
		{
			counter = 0;
			pressIndicator = 1;
			HAL_TIM_Base_Stop_IT(&htim2);
		}
		else
		{
			//
		}
	}
	else
	{
		//
	}
}
