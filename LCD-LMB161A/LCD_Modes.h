/*******************************************************************************
* Title                 :   LCD_Modes   
* Filename              :   LCD_Modes.h
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

#ifndef _LCD_MODES_H
#define _LCD_MODES_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include "stm32f1xx_hal.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


/*******************************************************************************
* Macros
*******************************************************************************/

/*******************************************************************************
* TYPEDEF
*******************************************************************************/

#define SCREEN_NUMBERS   		4

#define MODES_LEVELS_NUMBERS 	4
typedef enum{
	LEVEL1_MODE = 1,
	LEVEL2_MODE,
	LEVEL3_MODE,
	EDIT_LEVEL_MODE,
}LCD_MODE_LEVEL_e;


#define METERING_MODE				2
#define METERING_LEVEL2_TAPS_NUMBER 6
enum{
	METERING_LEV2_VOLTAGE = 1,
	METERING_LEV2_CURRENT,
	METERING_LEV2_POWER,
	METERING_LEV2_ENERGY,
	METERING_LEV2_HARMONICS,
	METERING_LEV2_TEMPERATURE,
};

#define VOLTAGE_TAPS_NUMBER		2
#define CURRENT_TAPS_NUMBER		2
#define POWER_TAPS_NUMBER		2
#define HARMONICS_TAPS_NUMBER	4

#define SETTING_MODE				3
#define SETTINGS_LEVEL2_TAPS_NUMBER 7
enum{
	SETTINGS_LEV2_UNIT_ID = 1,
	SETTINGS_LEV2_CT_RATIO,
	SETTINGS_LEV2_SYNCH_TIME,
	SETTINGS_LEV2_SET_POINT,
	SETTINGS_LEV2_OPERATOR,
	SETTINGS_LEV2_PASSWORD,
	SETTINGS_LEV2_ENERGY_RST
};

#define CALIBRATION_MODE				4
#define CALIBRATION_LEVEL2_TAPS_NUMBER 	1


typedef struct modes
{
	uint8_t firstLevel;
	uint8_t secondLevel;
	uint8_t thirdLevel;
}MODE_t;

/*******************************************************************************
* Functions Prototyping
*******************************************************************************/
void LCD_Screen_1(void);
void LCD_Screen_2(void);
void LCD_Screen_3(void);
void LCD_Screen_4(void);


#endif //_LCD_MODES_H