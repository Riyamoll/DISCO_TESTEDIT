/**
 *  \file ssd1306.c
 *  \brief Brief
 */

#include <fonts.h>
#include <sh1106.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

#define CMD(c)        do { HAL_GPIO_WritePin( DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET); \
                           ssd1306SendByte( c ); \
                         } while (0);
#define DATA(c)       do { HAL_GPIO_WritePin( DC_GPIO_Port, DC_Pin, GPIO_PIN_SET); \
                           ssd1306SendByte( c ); \
                         } while (0); 
#define swap(a, b)       { int16_t t = a; a = b; b = t; }
												 
extern SPI_HandleTypeDef hspi1;

static uint8_t    buffer[SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8];

#ifdef MULTILAYER  
static uint8_t    buffer_ol[SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8];
#endif    



/**
 *  \brief SPI write
 *  
 *  \param [in] byte Parameter_Description
 *  \return Return_Description
 *  
 *  \details Details
 *  
 *  \code
 *  \endcode
 */
inline void ssd1306SendByte(uint8_t byte)
{
	HAL_SPI_Transmit ( &hspi1,  (uint8_t *) &byte, 1, 1) ;
}

/**************************************************************************/
/**
 *  \brief Initializes the SSD1306 LCD display
 *  
 *  \param [in] vccstate Parameter_Description
 *  \return Return_Description
 *  
 *  \details Details
 */
void  ssd1306Init(uint8_t vccstate)
{
  HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET);
  HAL_Delay  (100);
  HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET);
  // Initialization sequence
  CMD(SSD1306_DISPLAYOFF);                    // 0xAE
  CMD(SSD1306_SETDISPLAYCLOCKDIV);            // 0xD5
  CMD(0x80);                                  // the suggested ratio 0x80
  CMD(SSD1306_SETMULTIPLEX);                  // 0xA8
  CMD(0x3F);
  CMD(SSD1306_SETDISPLAYOFFSET);              // 0xD3
  CMD(0x0);                                   // no offset
  CMD(SSD1306_SETSTARTLINE);            // line #0
  CMD(SSD1306_SETPAGEADDRESS);
  CMD(SSD1306_CHARGEPUMP);                    // 0x8D
  if (vccstate == SSD1306_EXTERNALVCC) 
  { CMD(0x10); }
  else 
  { CMD(0x14); }
  CMD(SSD1306_MEMORYMODE);                    // 0x20
  CMD(0x00);                                  // 0x0 act like ks0108
  CMD(SSD1306_SEGREMAP | 0x1);
  CMD(SSD1306_COMSCANDEC);
  CMD(SSD1306_SETCOMPINS);                    // 0xDA
  CMD(0x12);
  CMD(SSD1306_SETCONTRAST);                   // 0x81
  if (vccstate == SSD1306_EXTERNALVCC) 
  { CMD(0x9F); }
  else 
  { CMD(0xCF); }
  CMD(SSD1306_SETPRECHARGE);                  // 0xd9
  if (vccstate == SSD1306_EXTERNALVCC) 
  { CMD(0x22); }
  else 
  { CMD(0xF1); }
  CMD(SSD1306_SETVCOMDETECT);                 // 0xDB
  CMD(0x40);
  CMD(SSD1306_DISPLAYALLON_RESUME);           // 0xA4
  CMD(SSD1306_NORMALDISPLAY);                 // 0xA6
  HAL_Delay  (100);
  ssd1306TurnOn();
}

/**
 *  \brief Renders the contents of the pixel buffer on the LCD
 *  
 *  \return Return_Description
 *  
 *  \details Details
 */
void ssd1306Refresh(void) 
{
  CMD(SSD1306_SETLOWCOLUMN);  // low col = 0
  CMD(SSD1306_SETHIGHCOLUMN);  // high col = 0
  CMD(SSD1306_SETSTARTLINE);  // line #0

  HAL_GPIO_WritePin( DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);
  #ifdef MULTILAYER

  HAL_SPI_Transmit  ( &hspi1,  (uint8_t *) buffer_ol, sizeof(buffer), 200) ;
  #else
  HAL_SPI_Transmit  ( &hspi1,  (uint8_t *) buffer, sizeof(buffer), 200) ;
  #endif
}

/**
 *  \brief Enable the OLED panel
 *  
 *  \return Return_Description
 *  
 *  \details Details
 */
void ssd1306TurnOn(void)
{
    CMD(SSD1306_DISPLAYON);
}
/**
 *  \brief Disable the OLED panel
 *  
 *  \return Return_Description
 *  
 *  \details Details
 */
void ssd1306TurnOff(void)
{
    CMD(SSD1306_DISPLAYOFF);
}


/**
 *  \brief Clears the screen
 *
 *  \param [in] layer Parameter_Description
 *  \return Return_Description
 *
 *  \details Details
 */
void ssd1306ClearScreen()
{
	for( int j=0XB0;j<0XB8;j++)
	            	{
	            		CMD(j);
	            		for(int i = 00; i < 132; i++)
	            		{
	            			DATA(0X00);
	            		    		}
  }
}



