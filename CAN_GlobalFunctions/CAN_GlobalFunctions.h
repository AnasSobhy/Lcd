/****************************************************************************
* Title                 :   CAN_GlobalFunctions  
* Filename              :   CAN_GlobalFunctions.h
* Author                :   Edge Technology
* Version               :   1.0.0
* Compiler              :   IAR compiler
* Target                :   STM32F103c8
* Notes                 :   None
*
* THIS SOFTWARE IS PROVIDED BY TODO: COMPANY "AS IS" AND ANY EXPRESSED
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
*******************************************************************************/
#ifndef _CAN_GLOBAL_FUNCTIONS_H
#define _CAN_GLOBAL_FUNCTIONS_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include "stm32f1xx_hal.h"


/*******************************************************************************
* Macros
*******************************************************************************/    
#define CAN_RxMessageLength 60
#define LCD_CAN_ID          15 //It's just a random number :) 

#define UNIT_ID_REQUEST_IDENTIFIER			(uint32_t)1
#define CT_RATIO_REQUEST_IDENTIFIER			(uint32_t)2
#define TIME_INTERVAL_REQUEST_IDENTIFIER	(uint32_t)3
#define SIM_OPERATOR_REQUEST_IDENTIFIER		(uint32_t)4
#define SET_POINT_REQUEST_IDENTIFIER		(uint32_t)5
#define CLOCK_REQUEST_IDENTIFIER			(uint32_t)6
#define SIGNAL_REQUEST_IDENTIFIER			(uint32_t)7
#define PASSWORD_REQUEST_IDENTIFIER			(uint32_t)8


#define VOLTAGE_REQUEST_IDENTIFIER			(uint32_t)20
#define CURRENT_REQUEST_IDENTIFIER			(uint32_t)21
#define POWER_REQUEST_IDENTIFIER			(uint32_t)22
#define ENERGY_REQUEST_IDENTIFIER			(uint32_t)23
#define TEMPERATURE_REQUEST_IDENTIFIER		(uint32_t)24
#define HARMONICS_REQUEST_IDENTIFIER		(uint32_t)25




/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct{
	char phase1[8];
	char phase2[8];
	char phase3[8];
	char neutral[8];
}Currents_t;

typedef struct{
	char phase1[8];
	char phase2[8];
	char phase3[8];
}Voltages_t;

typedef struct{
	char phase1[11];
	char phase2[11];
	char phase3[11];
}Powers_t;

typedef struct{
	char active[11];
	char reactive[11];
}Energies_t;

typedef struct{
	char Vphase1[3];
	char Vphase2[3];
	char Vphase3[3];
	
	char Iphase1[3];
	char Iphase2[3];
	char Iphase3[3];
}Harmonics_t;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void HAL_CAN_MyTxMessage(char newMessage[], int n);
void HAL_CAN_MyRxMessage(void);

void CAN_Get_Value_upon_on_Identifier(uint32_t stdID);

#ifdef __cplusplus
} // extern "C"
#endif

#endif 

