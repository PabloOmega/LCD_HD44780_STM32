
#include "stdint.h"
#include "string.h"
#include "ctype.h"
/*Depende del compilador y la arquitectura*/
#include "stm32f1xx_hal.h"

/*PINES */
#define ST_LCD_RS GPIO_PIN_3
#define ST_LCD_RW GPIO_PIN_4
#define ST_LCD_EN GPIO_PIN_5
#define ST_LCD_D4 GPIO_PIN_6
#define ST_LCD_D5 GPIO_PIN_7
#define ST_LCD_D6 GPIO_PIN_8
#define ST_LCD_D7 GPIO_PIN_9

/* Input Output*/
#define ST_LCD_Input()  GPIOB->CRL |= 0x44000000; GPIOB->CRH |= 0x44 //Revisar
#define ST_LCD_Output() GPIOB->CRL |= 0x22000000; GPIOB->CRH |= 0x22

#define ST_LCD_PORT GPIOB

#define ST_LCD_HIGH 16
#define ST_LCD_LOW  0
#define ST_LCD_FPOS GPIO_BSRR_BS6_Pos

#define ST_LCD_WriteCmd(ST_Val) GPIOB->BSRR |= (((~(uint32_t)ST_Val) & 0xF) << ST_LCD_FPOS) << ST_LCD_HIGH \
																						|  ((uint32_t)ST_Val << ST_LCD_FPOS)
#define ST_LCD_Data(cmd)    ST_LCD_RSSet();   ST_LCD_Write(cmd); ST_LCD_xpos++
#define ST_LCD_Config(cmd)	ST_LCD_RSReset(); ST_LCD_Write(cmd); if(cmd == 1 || cmd == 2 || cmd == 3) HAL_Delay(2);

#define ST_LCD_RSSet()    GPIOB->BSRR |= ST_LCD_RS 
#define ST_LCD_RSReset()  GPIOB->BSRR |= ST_LCD_RS << ST_LCD_HIGH   
#define ST_LCD_RWSet()    GPIOB->BSRR |= ST_LCD_RW
#define ST_LCD_RWReset()  GPIOB->BSRR |= ST_LCD_RW << ST_LCD_HIGH
#define ST_LCD_ENSet()    GPIOB->BSRR |= ST_LCD_EN
#define ST_LCD_ENReset()  GPIOB->BSRR |= ST_LCD_EN << ST_LCD_HIGH

/*Mascaras*/

#define ST_LCD_EntrySetMsk   (uint8_t)0x04
#define ST_LCD_DisContMsk    (uint8_t)0x08
#define ST_LCD_CurShiftMsk   (uint8_t)0x10
#define ST_LCD_FuncSetMsk    (uint8_t)0x20
#define ST_LCD_SetCGRAMMsk	 (uint8_t)0x40
#define ST_LCD_SetDDRAMMsk   (uint8_t)0x80

/*Comandos*/

#define ST_LCD_ClearDisplay  0x01
#define ST_LCD_ReturnHome    0x02
#define ST_LCD_ID_Inc				 0x02 | ST_LCD_EntrySetMsk
#define ST_LCD_ID_Dec				 0x00 | ST_LCD_EntrySetMsk
#define ST_LCD_SH_On				 0x01
#define ST_LCD_SH_Off				 0x00
#define ST_LCD_Dis_On				 0x04 | ST_LCD_DisContMsk
#define ST_LCD_Dis_Off			 0x00 | ST_LCD_DisContMsk
#define ST_LCD_Cursor_On		 0x02
#define ST_LCD_Cursor_Off		 0x00
#define ST_LCD_Blink_On	   	 0x01
#define ST_LCD_Blink_Off		 0x00
#define ST_LCD_DisShift			 0x08 | ST_LCD_CurShiftMsk
#define ST_LCD_CursorMove		 0x00 | ST_LCD_CurShiftMsk
#define ST_LCD_ShiftRight		 0x04
#define ST_LCD_ShiftLeft		 0x00
#define ST_LCD_8bits				 0x10 | ST_LCD_FuncSetMsk
#define ST_LCD_4bits   			 0x00 | ST_LCD_FuncSetMsk
#define ST_LCD_2line 		     0x08
#define ST_LCD_1line	    	 0x00
#define ST_LCD_5x10points    0x04
#define ST_LCD_5x7points		 0x00

void ST_LCD_Delay(uint32_t delay_us);
void ST_LCD_Load(uint8_t st_cmd);
void ST_LCD_Write(uint8_t st_cmd);
void ST_LCD_Printf(const char *st_string);
void ST_LCD_Gotoxy(uint8_t st_x,uint8_t st_y);
void ST_LCD_WriteCGRAM(uint8_t *st_matriz, uint8_t st_address);
void ST_LCD_Init(void);