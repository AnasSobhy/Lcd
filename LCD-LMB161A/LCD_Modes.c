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
#include "LCD_Modes.h"
#include "LCD_LMB161A.h"
#include "CAN_GlobalFunctions.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
/* Private variables ---------------------------------------------------------*/
LCD_MODE_LEVEL_e lcdModeLevelSelect = LEVEL1_MODE;

volatile uint8_t insideLevelLcdFlag = 1;

/* External variables --------------------------------------------------------*/
extern volatile uint16_t gServerSecondsCounter;

extern volatile uint8_t editIndicator;

extern Currents_t measuredCurrent;
extern Voltages_t measuredVoltage;
extern Powers_t   measuredPower;
extern Energies_t measuredEnergy;
extern Harmonics_t measuredHarmonics;

extern char temperatureValue[4];
extern char unitID[5];
extern char ctValue[5];
extern char timeInterval[3];
extern char setPiont[3];
extern char simOperator[10];
extern uint8_t passwordValue;
extern char clockValue[6];
extern char signalValue[3];
extern uint8_t energyResetFlag;

extern volatile MODE_t MODE;
/*******************************************************************************
* Functions definitions
*******************************************************************************/

/******************************************************************************
* Function : LCD_Screen_1();
* 
* Description:
*
* This function is used to ///
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Screen_1(void)
{
	char message[17];
	switch(lcdModeLevelSelect)
	{
	case LEVEL1_MODE:
		if(insideLevelLcdFlag == 1) //to do somthing only one time
		{
			insideLevelLcdFlag = 2;
			gServerSecondsCounter = 0;
			//LCD_Buttons_Buzzer();
			LCD_Clear_All();
			LCD_GoTo_XY(1, 1);
			LCD_Send_String(" EdgeTechnology New_Aumento V0.0");
		}
		else if(insideLevelLcdFlag == 2 && gServerSecondsCounter > 1)
		{
			gServerSecondsCounter = 0;
			
			CAN_Get_Value_upon_on_Identifier(UNIT_ID_REQUEST_IDENTIFIER);
			CAN_Get_Value_upon_on_Identifier(CLOCK_REQUEST_IDENTIFIER);
			CAN_Get_Value_upon_on_Identifier(SIGNAL_REQUEST_IDENTIFIER);
			
			LCD_Clear_All();

			LCD_GoTo_XY(1, 1);
			LCD_Send_String("ID    CLK   Sign");
			
			sprintf(message, "%0.4s  %0.5s %0.2s", unitID, clockValue, signalValue); 
			LCD_GoTo_XY(2, 1);
			LCD_Send_String(message);
		}
		else
		{
			//
		}
		break;
//	case LEVEL2_MODE:
//		break;
//	case LEVEL3_MODE:
//		break;
	default:
		break;
	}
}

/******************************************************************************
* Function : LCD_Screen_2();
* 
* Description:
*
* This function is used to ///
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Screen_2(void)
{
	char message[33];
	
	switch(lcdModeLevelSelect)
	{
	case LEVEL1_MODE:
		if(insideLevelLcdFlag == 1) //To do somthing once 
		{
			insideLevelLcdFlag = 0;
			gServerSecondsCounter = 0;

			//LCD_Buttons_Buzzer();
			
			LCD_Send_Command(_cursor_off);
			HAL_Delay(1);
			LCD_Clear_All();
			
			LCD_GoTo_XY(1, 1);
			LCD_Send_String("1.0 Metering");

			//
		}
		else
		{
			//
		}
		break;
////////////////////////////// Inside Level 2 of Mode2 /////////////////////////			
	case LEVEL2_MODE:
		switch(MODE.secondLevel)
		{
		case METERING_LEV2_VOLTAGE:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				CAN_Get_Value_upon_on_Identifier(VOLTAGE_REQUEST_IDENTIFIER);
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("1.1 Voltage");

				//
			}
			else
			{
				//
			}
			break;
		case METERING_LEV2_CURRENT:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				CAN_Get_Value_upon_on_Identifier(CURRENT_REQUEST_IDENTIFIER);
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("1.2 Current");

				//
			}
			else
			{
				//
			}
			break;
		case METERING_LEV2_POWER:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				CAN_Get_Value_upon_on_Identifier(POWER_REQUEST_IDENTIFIER);
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("1.3 Power");

				//
			}
			else
			{
				//
			}
			break;
		case METERING_LEV2_ENERGY:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				CAN_Get_Value_upon_on_Identifier(ENERGY_REQUEST_IDENTIFIER);
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("1.4 Energy");

				//
			}
			else
			{
				//
			}
			break;
		case METERING_LEV2_HARMONICS:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;
				
				//LCD_Buttons_Buzzer();
				
				CAN_Get_Value_upon_on_Identifier(HARMONICS_REQUEST_IDENTIFIER);
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("1.5 Harmonics");

				//
			}
			else
			{
				//
			}
			break;
		case METERING_LEV2_TEMPERATURE:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;


				//LCD_Buttons_Buzzer();
				
				CAN_Get_Value_upon_on_Identifier(TEMPERATURE_REQUEST_IDENTIFIER);
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("1.6 Temperature");

				//
			}
			else
			{
				//
			}
			break;
		default:
			break;
		}
		break;
////////////////////////////// Inside Level 3 of Mode2 /////////////////////////		
	case LEVEL3_MODE:
		switch(MODE.secondLevel)
		{
		case METERING_LEV2_VOLTAGE:
			if(insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(VOLTAGE_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				
				LCD_Clear_All();
				LCD_GoTo_XY(1, 1);
				
				switch(MODE.thirdLevel)
				{
				case 1:
					sprintf(message,"V1:%.7s", measuredVoltage.phase1);
					LCD_Send_String(message);
					
					LCD_GoTo_XY(2, 1);
					sprintf(message,"V2:%.7s", measuredVoltage.phase2);
					LCD_Send_String(message);
					break;
				case 2:
					sprintf(message,"V3:%.7s", measuredVoltage.phase3);
					LCD_Send_String(message);
					break;
				default:
					break;
				}
					
				//
			}
			else
			{
				//
			}
			break;
		case METERING_LEV2_CURRENT:
			if(insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(CURRENT_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				
				LCD_Clear_All();
				LCD_GoTo_XY(1, 1);
				
				switch(MODE.thirdLevel)
				{
				case 1:
					sprintf(message,"I1:%.7s", measuredCurrent.phase1);
					LCD_Send_String(message);
					
					LCD_GoTo_XY(2, 1);
					sprintf(message,"I2:%.7s", measuredCurrent.phase2);
					LCD_Send_String(message);
					break;
				case 2:
					sprintf(message,"I3:%.7s", measuredCurrent.phase3);
					LCD_Send_String(message);
					
					LCD_GoTo_XY(2, 1);
					sprintf(message,"In:%.7s", measuredCurrent.neutral);
					LCD_Send_String(message);
					break;
				default:
					break;
				}
					
				//
			}
			else
			{
				//
			}
			break;
		case METERING_LEV2_POWER:
			if(insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(POWER_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				
				LCD_Clear_All();
				LCD_GoTo_XY(1, 1);
				
				switch(MODE.thirdLevel)
				{
				case 1:
					sprintf(message,"P1:%.10s", measuredPower.phase1);
					LCD_Send_String(message);
					
					LCD_GoTo_XY(2, 1);
					sprintf(message,"P2:%.10s", measuredPower.phase2);
					LCD_Send_String(message);
					break;
				case 2:
					sprintf(message,"P3:%.10s", measuredPower.phase3);
					LCD_Send_String(message);
					break;
				default:
					break;
				}
					
				//
			}
			else
			{
				//
			}
			break;
		case METERING_LEV2_ENERGY:
			if(insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(ENERGY_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				sprintf(message,"kWH:%.10s", measuredEnergy.active);
				LCD_Send_String(message);
				
				LCD_GoTo_XY(2, 1);
				sprintf(message,"kVAR:%.10s", measuredEnergy.reactive);											 
				LCD_Send_String(message);

				//
			}
			else
			{
				//
			}
			break;
		case METERING_LEV2_HARMONICS:
			if(insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;
				
				CAN_Get_Value_upon_on_Identifier(HARMONICS_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				
				LCD_Clear_All();
				LCD_GoTo_XY(1, 1);
				
				switch(MODE.thirdLevel)
				{
				case 1:
					sprintf(message,"THDv1:%.2s", measuredHarmonics.Vphase1);
					strcat(message, "%");
					LCD_Send_String(message);
					
					LCD_GoTo_XY(2, 1);
					sprintf(message,"THDv2:%.2s", measuredHarmonics.Vphase2);
					strcat(message, "%");
					LCD_Send_String(message);
					break;
				case 2:
					sprintf(message,"THDv3:%.2s", measuredHarmonics.Vphase3);
					strcat(message, "%");
					LCD_Send_String(message);
					break;
				case 3:
					sprintf(message,"THDi1:%.2s", measuredHarmonics.Iphase1);
					strcat(message, "%");
					LCD_Send_String(message);
					
					LCD_GoTo_XY(2, 1);
					sprintf(message,"THDi2:%.2s", measuredHarmonics.Iphase2);
					strcat(message, "%");
					LCD_Send_String(message);
					break;
				case 4:
					sprintf(message,"THDi3:%.2s", measuredHarmonics.Iphase3);
					strcat(message, "%");
					LCD_Send_String(message);
					break;
				default:
					break;
				}
					
				//
			}
			else
			{
				//
			}
			break;
		case METERING_LEV2_TEMPERATURE:
			if(insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(TEMPERATURE_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				sprintf(message,"Temperature:%.3s", temperatureValue);
																 
				LCD_Send_String(message);

				//
			}
			else
			{
				//
			}
		default:
			break;
		}
		break;
	default:
		break;
	}
}

/******************************************************************************
* Function : LCD_Screen_3();
* 
* Description:
*
* This function is used to ///
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Screen_3(void) //Settings Mode
{	
	switch(lcdModeLevelSelect)
	{
	case LEVEL1_MODE:
		if(insideLevelLcdFlag == 1) //To do somthing once 
		{
			insideLevelLcdFlag = 0;
			gServerSecondsCounter = 0;

			//LCD_Buttons_Buzzer();
			
			LCD_Send_Command(_cursor_off);
			HAL_Delay(1);
			LCD_Clear_All();
			
			LCD_GoTo_XY(1, 1);
			LCD_Send_String("2.0 Settings");
			
			//
		}
		else
		{
			//
		}
		break;
////////////////////////////// Inside Level 2 of Mode3 /////////////////////////	
	case LEVEL2_MODE:
		switch(MODE.secondLevel)
		{
		case SETTINGS_LEV2_UNIT_ID:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("2.1 Unit ID.");

				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_CT_RATIO:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("2.2 CT Ratio");

				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_SYNCH_TIME:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("2.3 Synch. Time");

				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_SET_POINT:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("2.4 Set Point");

				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_OPERATOR:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("2.5 Operator");

				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_PASSWORD:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("2.6 Password");

				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_ENERGY_RST:
			if(insideLevelLcdFlag == 1) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("2.7 Energy Reset");

				//
			}
			else
			{
				//
			}
			break;
		default:
			break;
		}
		break;
////////////////////////////// Inside Level 3 of Mode3 /////////////////////////	
	case LEVEL3_MODE:
		switch(MODE.secondLevel)
		{
		case SETTINGS_LEV2_UNIT_ID:
			if((insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) && editIndicator) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(UNIT_ID_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				
				LCD_Clear_All();
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("Unit ID:");
				LCD_Send_String(unitID);
				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_CT_RATIO:
			if((insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) && editIndicator) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(CT_RATIO_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				
				LCD_Clear_All();

				LCD_GoTo_XY(1, 1);
				LCD_Send_String("CT Ratio:");
				LCD_Send_String(ctValue);
				LCD_Send_String("/5");
				
				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_SYNCH_TIME:
			if((insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) && editIndicator) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(TIME_INTERVAL_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("Synch. Time:");
							
				LCD_GoTo_XY(2, 1);
				LCD_Send_String(timeInterval);
				LCD_Send_String(" minutes");
				
			
				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_SET_POINT:
			if((insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) && editIndicator) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(SET_POINT_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("Set Piont:");
				LCD_Send_String(setPiont);
				
				
				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_OPERATOR:
			if((insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) && editIndicator) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(SIM_OPERATOR_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("SIM Operator:");
				
				LCD_GoTo_XY(2, 1);
				LCD_Send_String(simOperator);
				
				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_PASSWORD:
			if((insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) && editIndicator) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				CAN_Get_Value_upon_on_Identifier(PASSWORD_REQUEST_IDENTIFIER);

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("Password:");
				
				LCD_Send_Char(passwordValue+'0');
				
				//
			}
			else
			{
				//
			}
			break;
		case SETTINGS_LEV2_ENERGY_RST:
			if((insideLevelLcdFlag == 1 || gServerSecondsCounter > 1) && editIndicator) //To do somthing once 
			{
				insideLevelLcdFlag = 0;
				gServerSecondsCounter = 0;

				//LCD_Buttons_Buzzer();
				
				LCD_Send_Command(_cursor_off);
				HAL_Delay(1);
				LCD_Clear_All();
				
				LCD_GoTo_XY(1, 1);
				LCD_Send_String("ENERGY RESET?");
				
				LCD_GoTo_XY(2, 1);
				LCD_Send_String("NO");
				energyResetFlag = 0;
				
				//
			}
			else
			{
				//
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

/******************************************************************************
* Function : LCD_Screen_4();
* 
* Description:
*
* This function is used to ///
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Screen_4(void)
{
	switch(lcdModeLevelSelect)
	{
	case LEVEL1_MODE:
		if(insideLevelLcdFlag == 1) //To do somthing once 
		{
			insideLevelLcdFlag = 0;
			gServerSecondsCounter = 0;

			//LCD_Buttons_Buzzer();
			
			LCD_Send_Command(_cursor_off);
			HAL_Delay(1);
			LCD_Clear_All();
			
			LCD_GoTo_XY(1, 1);
			LCD_Send_String("3.0 Calibration");

			//
		}
		else
		{
			//
		}
		break;
////////////////////////////// Inside Level 2 of Mode2 /////////////////////////			
	case LEVEL2_MODE:
		if(insideLevelLcdFlag == 1) //To do somthing once 
		{
			insideLevelLcdFlag = 0;
			gServerSecondsCounter = 0;

			//LCD_Buttons_Buzzer();
			
			LCD_Send_Command(_cursor_off);
			HAL_Delay(1);
			LCD_Clear_All();
			
			LCD_GoTo_XY(1, 1);
			LCD_Send_String("OK   to start.");
			LCD_GoTo_XY(2, 1);
			LCD_Send_String("BACK to return.");

			//
		}
		else
		{
			//
		}
		break;
////////////////////////////// Inside Level 3 of Mode2 /////////////////////////		
	case LEVEL3_MODE:
		if(insideLevelLcdFlag == 1) //To do somthing once 
		{
			insideLevelLcdFlag = 2;
			gServerSecondsCounter = 0;

			//CAN_Get_Value_upon_on_Identifier(VOLTAGE_REQUEST_IDENTIFIER); will do calibration flag

			//LCD_Buttons_Buzzer();
			
			LCD_Send_Command(_cursor_off);
			HAL_Delay(1);
			
			LCD_Clear_All();
			LCD_GoTo_XY(1, 1);
			
			LCD_Send_String(" PLEASE WAIT !");
			
		}
		else if(insideLevelLcdFlag == 2 && gServerSecondsCounter > 5 && gServerSecondsCounter < 10)
		{
			gServerSecondsCounter = 10;
			
			//CAN_Get_Value_upon_on_Identifier(VOLTAGE_REQUEST_IDENTIFIER); will do calibration flag
			
			LCD_Clear_All();
			LCD_GoTo_XY(1, 1);
			LCD_Send_String(" THE GREATNESS");
			LCD_GoTo_XY(2, 1);
			LCD_Send_String(" IS BEING COOKED");
		}
		else if(insideLevelLcdFlag == 2 && gServerSecondsCounter > 15)
		{
			gServerSecondsCounter = 0;
			
			//CAN_Get_Value_upon_on_Identifier(VOLTAGE_REQUEST_IDENTIFIER); will do calibration flag
			
			LCD_Clear_All();
			LCD_GoTo_XY(1, 1);
			LCD_Send_String("  BE PATIENT !");
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
