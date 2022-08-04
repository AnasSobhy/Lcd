/*******************************************************************************
* Title                 :   LCD_LMB161A   
* Filename              :   LCD_LMB161A.c
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
#include "main.h"
#include "LCD_LMB161A.h"

#include <stdio.h>
#include <string.h>
/* Private variables ---------------------------------------------------------*/
static LCD_Cursor_Position_s LCD_Cursor_Current_Position = {1,1};

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim1;
/*******************************************************************************
* Functions definitions
*******************************************************************************/

/******************************************************************************
* Function : PIN_LOW(GPIOx, GPIO_Pin);
* 
* Description:
*
* This function is used to out 0 volt on selected pin
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void PIN_LOW (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
}

/******************************************************************************
* Function : PIN_High(GPIOx, GPIO_Pin);
* 
* Description:
*
* This function is used to out 3.3 volt on selected pin
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void PIN_HIGH (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
}

/******************************************************************************
* Function : PIN_High(GPIOx, GPIO_Pin);
* 
* Description:
*
* This function is used to send enable pulse to lcd
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
static void LCD_En_Pulse(void)
{
  EN_SET;
  HAL_Delay_us(50);
  EN_CLEAR;
}

/*******************************************************************************
* Function : LCD_Send_Command(cmd);
* 
* Description:
*
* This function is used to send commands to LCd
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Send_Command(uint8_t cmd)
{
  RS_CLEAR;     //for Instruction mode
    	
  //At First send the 4-high bits
  LCD_PORT->ODR = ((LCD_PORT->ODR)&0xFFF0)|(cmd>>4);
  LCD_En_Pulse();
  
  HAL_Delay_us(200);
  
  //Then the 4-low bits
  LCD_PORT->ODR = ((LCD_PORT->ODR)&0xFFF0)|(cmd&0x0F);
  LCD_En_Pulse();
  
  HAL_Delay_us(200);
  
  RS_SET;       //for Data mode
}

/*******************************************************************************
* Function : LCD_Send_Char(chr);
* 
* Description:
*
* This function is used to send a character to LCd
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Send_Char(char chr)
{
  LCD_GoTo_XY(LCD_Cursor_Current_Position.X, LCD_Cursor_Current_Position.Y);
  
  //At First send the 4-high bits
  LCD_PORT->ODR = ((LCD_PORT->ODR)&0xFFF0)|(chr>>4);
  LCD_En_Pulse();
    
  HAL_Delay_us(200);
  
  //Then the 4-low bits
  LCD_PORT->ODR = ((LCD_PORT->ODR)&0xFFF0)|(chr&0x0F);
  LCD_En_Pulse();
  
  
  (LCD_Cursor_Current_Position.Y)++;
  
  if(LCD_Cursor_Current_Position.Y > 16)
  {
    switch(LCD_Cursor_Current_Position.X)
    {
    case 1:
      LCD_Cursor_Current_Position.X = 2;
      LCD_Cursor_Current_Position.Y = 1;
      break;
    case 2:
      LCD_Cursor_Current_Position.X = 1;
      LCD_Cursor_Current_Position.Y = 1;
      break;
    default:
      break;
    }
  }
  else
  {
    ///
  }
}

/*******************************************************************************
* Function : LCD_Send_String(str);
* 
* Description:
*
* This function is used to send a string to LCd
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Send_String(char *str)
{
  while((*str) != '\0')
  {
    LCD_Send_Char(*str);
    ++str;
  }
}

/*******************************************************************************
* Function : LCD_Send_Integer(number);
* 
* Description:
*
* This function is used to send a string to LCd
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Send_Integer(int number)
{
  char arr[7];
  memset(arr, 0, 7);
  sprintf(arr,"%d", number);
  
  LCD_Send_String(arr);
}

/*******************************************************************************
* Function : LCD_GoTo_XY(x, y);
* 
* Description:
*
* This function is used to go to a specific position on LCD
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_GoTo_XY(uint8_t x, uint8_t y)
{
	LCD_Cursor_Current_Position.X = x;
	LCD_Cursor_Current_Position.Y = y;
	if(LCD_Cursor_Current_Position.X>=1 && LCD_Cursor_Current_Position.X<=2 
       && LCD_Cursor_Current_Position.Y>=1 && LCD_Cursor_Current_Position.Y <=16)
	{
          switch(LCD_Cursor_Current_Position.X)
          {
            case 1:
              LCD_Send_Command(LCD_Cursor_Current_Position.Y+127); /** 127 = 0x80 - 1, refer to the first position on LCD **/
              break;
            case 2:
              LCD_Send_Command(LCD_Cursor_Current_Position.Y+191); /** 192 refers to the first position in second row on LCD **/
              break;
            default:
              break;
          }
	}
}

/*******************************************************************************
* Function : LCD_Init_4Bits();
* 
* Description:
*
* This function is used to initialize the LCD
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Init_4Bits(void)
{
    RW_CLEAR;     //alwayes write operations
    
    //See Data sheet page14
	
    HAL_Delay(30);  
    
    LCD_Send_Command(_return_home);
    HAL_Delay_us(500);
    
    LCD_Send_Command(_function_set);
    HAL_Delay_us(500); 
    
    LCD_Send_Command(_display_on);
    HAL_Delay_us(500);
        
    LCD_Send_Command(_clear);
    HAL_Delay(2);
    
    LCD_Send_Command(_lentry_mode);	
    HAL_Delay(3);
    
    LCD_Send_Command(_cursor_off);
    HAL_Delay(2);
}

/*******************************************************************************
* Function : LCD_Init_4Bits();
* 
* Description:
*
* This function is used to remove the last character
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Remove_Char(void)
{
  (LCD_Cursor_Current_Position.Y)--;
  LCD_GoTo_XY(LCD_Cursor_Current_Position.X, LCD_Cursor_Current_Position.Y);
  LCD_Send_Char(' ');
  (LCD_Cursor_Current_Position.Y)--;
  LCD_GoTo_XY(LCD_Cursor_Current_Position.X, LCD_Cursor_Current_Position.Y);
}

/*******************************************************************************
* Function : LCD_Clear_All();
* 
* Description:
*
* This function is used to clear the entire display
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Clear_All(void)
{
  LCD_Send_Command(_clear);
  HAL_Delay(2);
  LCD_GoTo_XY(1, 1);
}

/*******************************************************************************
* Function : LCD_Clear_1st_Row();
* 
* Description:
*
* This function is used to clear the first row 
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Clear_1st_Row(void)
{
  char space[] = "                ";
  LCD_GoTo_XY(1, 1);
  LCD_Send_String(space);
  LCD_GoTo_XY(1, 1);
}

/*******************************************************************************
* Function : LCD_Clear_2nd_Row();
* 
* Description:
*
* This function is used to clear the second row 
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
void LCD_Clear_2nd_Row(void)
{
  char space[] = "                ";
  LCD_GoTo_XY(2, 1);
  LCD_Send_String(space);
  LCD_GoTo_XY(2, 1);
}


/*******************************************************************************
* Function : LCD_X();
* 
* Description:
*
* This function is used to return the cursor row position
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
uint8_t LCD_X(void)
{
  return LCD_Cursor_Current_Position.X;
}

/*******************************************************************************
* Function : LCD_Y();
* 
* Description:
*
* This function is used to return the cursor column position
*
* PRE-CONDITION: Hardware initialization
*
* POST-CONDITION: None
*
* @return void
*
*******************************************************************************/
uint8_t LCD_Y(void)
{
  return LCD_Cursor_Current_Position.Y;
}

void HAL_Delay_us(uint16_t microSeconds)
{
  __HAL_TIM_SET_COUNTER(&htim1,0);  
  while (__HAL_TIM_GET_COUNTER(&htim1) < microSeconds)
  {
    //
  }
}

/*void LCD_Buttons_Buzzer(void)
{
  HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_SET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(Buzz_GPIO_Port, Buzz_Pin, GPIO_PIN_RESET);
}*/