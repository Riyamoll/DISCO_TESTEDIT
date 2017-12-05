/*
    @file     ssd1306.h
    @author   
    @date     
    @version  
    @section LICENSE
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __SSD1306_H__
#define __SSD1306_H__

#include "stm32f0xx_hal.h"
#include <math.h>


#define 	SSD1306_SPI SPI1

// Pin Definitions
#define 	SSD1306_DC_PORT							GPIOB     // Data/Command
#define 	SSD1306_DC_PIN							(12)
#define 	SSD1306_RST_PORT            GPIOB     // Reset
#define 	SSD1306_RST_PIN             (13)
#define 	SSD1306_CS_PORT             GPIOA     // Select
#define 	SSD1306_CS_PIN              (15)
#define 	SSD1306_SCLK_PORT           GPIOB     // Serial Clock
#define 	SSD1306_SCLK_PIN            (3)
#define 	SSD1306_SDAT_PORT           GPIOB     // Serial Data
#define 	SSD1306_SDAT_PIN            (5)

#define   BLACK     									0
#define   WHITE     									1
#define   INVERSE   									2

#define   MULTILAYER   								1
#define   LAYER0											1
#define   LAYER1											2

#define		SSD1306_LCDWIDTH         	132
#define		SSD1306_LCDHEIGHT          	64

// Commands
#define SSD1306_SETCONTRAST               0x81
#define SSD1306_DISPLAYALLON_RESUME       0xA4
#define SSD1306_DISPLAYALLON              0xA5
#define SSD1306_NORMALDISPLAY             0xA6
#define SSD1306_INVERTDISPLAY             0xA7
#define SSD1306_DISPLAYOFF                0xAE
#define SSD1306_DISPLAYON                 0xAF
#define SSD1306_SETDISPLAYOFFSET          0xD3
#define SSD1306_SETCOMPINS                0xDA
#define SSD1306_SETVCOMDETECT             0xDB
#define SSD1306_SETDISPLAYCLOCKDIV        0xD5
#define SSD1306_SETPRECHARGE              0xD9
#define SSD1306_SETMULTIPLEX              0xA8
#define SSD1306_SETLOWCOLUMN              0x02
#define SSD1306_SETHIGHCOLUMN             0x10
#define SSD1306_SETSTARTLINE              0x09
#define SSD1306_SETPAGEADDRESS            0xB0
#define SSD1306_MEMORYMODE                0x20
#define SSD1306_COMSCANINC                0xC0
#define SSD1306_COMSCANDEC                0xC8
#define SSD1306_SEGREMAP                  0xA0
#define SSD1306_CHARGEPUMP                0x8D
#define SSD1306_EXTERNALVCC               0x1
#define SSD1306_SWITCHCAPVCC              0x2
// macros
#define SSD1306MSDELAY(c)      HAL_Delay( c );
	

//
typedef struct {
	double x;
	double y;
}	SSD1306_pointTypeDef;

typedef struct {
	SSD1306_pointTypeDef * SSD1306_points_pointer;
	int SSD1306_points_number;
}	SSD1306_polyTypeDef;


// Initialisation/Config Prototypes
void    ssd1306SendByte(uint8_t);
void    ssd1306Init (uint8_t);
void    ssd1306Refresh ( void );
void    ssd1306TurnOn(void);
void    ssd1306TurnOff(void);
void ssd1306ClearScreen(void);
void    ssd1306ShiftFrameBuffer( uint16_t height, uint16_t direction);
void    ssd1306MixFrameBuffer(void);

#endif
