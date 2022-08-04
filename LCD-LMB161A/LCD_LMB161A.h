/*******************************************************************************
* Title                 :   LCD_LMB161A   
* Filename              :   LCD_LMB161A.h
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
#ifndef _LCD_CHAR_DRIVER_H
#define _LCD_CHAR_DRIVER_H

/*******************************************************************************
* Includes
*******************************************************************************/
#include "stm32f1xx_hal.h"

/*******************************************************************************
* Macros
*******************************************************************************/
#define LCD_PORT        GPIOA
#define RS_PORT         GPIOA          
#define RS_PIN          GPIO_PIN_4
#define RW_PORT         GPIOA
#define RW_PIN          GPIO_PIN_5    
#define EN_PORT         GPIOA
#define EN_PIN          GPIO_PIN_6
#define BL_PORT         GPIOA
#define BL_PIN          GPIO_PIN_7

#define D4_PORT         GPIOA
#define D4_PIN          GPIO_PIN_0
#define D5_PORT         GPIOA
#define D5_PIN          GPIO_PIN_1
#define D6_PORT         GPIOA
#define D6_PIN          GPIO_PIN_2
#define D7_PORT         GPIOA
#define D7_PIN          GPIO_PIN_3

#define RS_CLEAR        PIN_LOW(RS_PORT, RS_PIN)        /*For COMMAND*/
#define RS_SET          PIN_HIGH(RS_PORT, RS_PIN)       /*For DATA*/

#define RW_CLEAR        PIN_LOW(RW_PORT, RW_PIN)        /*For Writing*/
#define RW_SET          PIN_HIGH(RW_PORT, RW_PIN)       /*For Reading*/

#define EN_CLEAR        PIN_LOW(EN_PORT, EN_PIN)      
#define EN_SET          PIN_HIGH(EN_PORT, EN_PIN)

#define _clear		      	0x01	//<! clear LCD Display and return cursor to position 0
#define _return_home	  	0x02	//<! return shifted display to original position and cursor to position 0
#define _lentry_mode	  	0x06	//<! shift cursor from left to right when read/writing operations
#define _rentry_mode	  	0x04	//<! shift cursor from right to left when read/writing operations
#define _display_on	    	0x0F
#define _display_off	  	0x0B
#define _cursor_off     	0x0C
#define _cursor_on      	0x0D
#define _cursor_lshift		0x10
#define _cursor_rshift		0x14
#define _display_lshift		0x18
#define _display_rshift		0x1C
#define _function_set	  	0x28	//<! set interface data length to 4-bit

/*******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct{
  uint8_t X;
  uint8_t Y;
}LCD_Cursor_Position_s;

/*******************************************************************************
* Functions Prototyping
*******************************************************************************/

/*To Send Commands To LCD*/
void LCD_Send_Command(uint8_t cmd);

/*To Send A character to LCD*/
void LCD_Send_Char(char chr);

/*To Send string to LCD*/
void LCD_Send_String(char *str);

/*To Send integer to LCD*/
void LCD_Send_Integer(int number);

/*To go to a specific position on LCD*/
void LCD_GoTo_XY(uint8_t x, uint8_t y);

/*4-Bit Mode Initialization*/
void LCD_Init_4Bits(void);

/*To remove a character*/
void LCD_Remove_Char(void);

/*To clear the entire LCD*/
void LCD_Clear_All(void);

/*To clear the first row only*/
void LCD_Clear_1st_Row(void);

/*To clear the second row only*/
void LCD_Clear_2nd_Row(void);

/*To return lcdX*/
uint8_t LCD_X(void);

/*To return lcdY*/
uint8_t LCD_Y(void);

void HAL_Delay_us(uint16_t microSeconds);

//void LCD_Buttons_Buzzer(void);

#endif //_LCD_CHAR_DRIVER_H