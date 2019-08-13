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
#include <fonts.h>
#include "stm32f0xx_hal.h"
#include "stdlib.h"
#include <math.h>
#include <sh1106.h>
#include <string.h>
#include "main.h"

#define DATA(c)       do { HAL_GPIO_WritePin( DC_GPIO_Port, DC_Pin, GPIO_PIN_SET); \
                           ssd1306SendByte( c ); \
                         } while (0);
#define CMD(c)        do { HAL_GPIO_WritePin( DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET); \
                           ssd1306SendByte( c ); \
                         } while (0);




void SSD1306LibTest(void)
{
	int i,p,j,k=0,l=132,z,z1,z2,q;
	z=sizeof(font_midlayer);
	z1=sizeof(font_uplayer);
	z2=sizeof(font_downlayer);

	// buffers to copy
	uint8_t font_midlayera[z];
	uint8_t font_uplayera[z];
	uint8_t font_downlayera[z];

	// copying to duplicate buffers
	for(q=0;q<=z;q++)
	{
		font_midlayera[q]=font_midlayer[q];
	}

	for(q=0;q<=z1;q++)
		{
		font_uplayera[q]=font_uplayer[q];
		}

	for(q=0;q<=z2;q++)
		{
		font_downlayera[q]=font_downlayer[q];
		}
	    /* ---Test routine--- */
        /* take display buffer */
     ssd1306ClearScreen();
     for(p=0;p<280;p++)
        {
    // move font
	memmove(&font_midlayera[0], &font_midlayera[1], sizeof(font_midlayer)-1);
	memmove(&font_uplayera[0], &font_uplayera[1], sizeof(font_uplayer)-1);
	memmove(&font_downlayera[0], &font_downlayera[1], sizeof(font_downlayer)-1);

	// write on the display
	 for(j=0XB2;j<0XB5;)
	       {
	    	   switch (j)
	    	   {
	    	   case 0XB2:
	    	   {
	           for(i = k; i < l; i++)
	             {
	         	   CMD(j);
	               DATA(font_uplayera[i]);
	              }
	           j++;
	    	   }
	           break;
	           case 0XB3:
	    	   {
	             for(i = k; i < l; i++)
	              {
	         	    CMD(j);
	                DATA(font_midlayera[i]);
	              }
	           j++;
	    	   }
	           break;
	           case 0XB4:
	           {
	             for(i = k; i < l; i++)
	              {
	         	    CMD(j);
	                DATA(font_downlayera[i]);
	               }
	            }
	    	    j++;
	              }
	            }
	             HAL_Delay(15);
                }
 ssd1306Refresh();
 }



	


  
/************************** (C) COPYRIGHT STMicroelectronics ****************END OF FILE****/
