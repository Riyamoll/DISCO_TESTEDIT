/**
  ******************************************************************************
  * File Name          : ssd1306libtest.c
  * Description        : 
  ******************************************************************************
  *
  * COPYRIGHT(c) 
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "ssd1306.h"
#include "stdlib.h"
#include <math.h>
#include <string.h>
#include "font5x7.h"
#include "main.h"

#define DATA(c)       do { HAL_GPIO_WritePin( DC_GPIO_Port, DC_Pin, GPIO_PIN_SET); \
                           ssd1306SendByte( c ); \
                         } while (0);
#define CMD(c)        do { HAL_GPIO_WritePin( DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET); \
                           ssd1306SendByte( c ); \
                         } while (0);
	
void SSD1306LibTest(void)
{
	int i,p,j,k=0,l=132;

	/* ---Test routine--- */
    /* take display buffer */
    ssd1306ClearScreen();
for(p=0;p<132;p++)
{
	 for(j=0XB2;j<0XB5;j++)
	       {
	    	   switch (j)
	    	   {
	    	   case 0XB2:
	    	   {
	       for(i = k; i < l; i++)
	         {
	         	CMD(j);
	          DATA(font5x8[i]);
	         }
	    	   }
	break;
	    	   case 0XB3:
	    	   {
	         for(i = k; i < l; i++)
	         {
	         	 CMD(j);
	             DATA(font5x7[i]);
	          // HAL_Delay  (20);
	         }
	    	   }
	break;
	case 0XB4:
	    	       	   {
	            for(i = k; i < l; i++)
	            {
	         	   CMD(j);
	             DATA(font5x9[i]);
	            }
	   }
	  }
	 }
}


 HAL_Delay(10000);
      ssd1306Refresh();
    }



	




  
  
  
/************************** (C) COPYRIGHT STMicroelectronics ****************END OF FILE****/
