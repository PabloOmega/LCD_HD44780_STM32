
#include "ST_LCD.h"

volatile uint8_t ST_LCD_xpos = 0;
volatile uint8_t ST_LCD_ypos = 0;

void ST_LCD_Init(void){
	ST_LCD_RSReset();
	ST_LCD_RWReset();
	ST_LCD_ENReset(); 
	ST_LCD_WriteCmd(0x0);
	HAL_Delay(15);
	ST_LCD_WriteCmd(0x3);
	ST_LCD_ENSet();
	HAL_Delay(5);
	ST_LCD_ENReset();
	ST_LCD_WriteCmd(0x3);
	ST_LCD_ENSet();
	HAL_Delay(2);
	ST_LCD_ENReset();
	ST_LCD_WriteCmd(0x3);
	ST_LCD_ENSet();
	HAL_Delay(2);
	ST_LCD_ENReset();
	ST_LCD_WriteCmd(0x2);
	ST_LCD_ENSet();
	HAL_Delay(2);
	ST_LCD_ENReset();
	HAL_Delay(2);
	ST_LCD_Config(ST_LCD_4bits | ST_LCD_2line | ST_LCD_5x10points);
	ST_LCD_Config(ST_LCD_DisContMsk);
	ST_LCD_Config(ST_LCD_ClearDisplay);
	ST_LCD_Config(ST_LCD_ID_Inc | ST_LCD_SH_Off);
	ST_LCD_Config(ST_LCD_Dis_On | ST_LCD_Cursor_On | ST_LCD_Blink_On);
}

void ST_LCD_Load(uint8_t st_cmd){
	ST_LCD_WriteCmd(st_cmd);
	ST_LCD_ENSet();
	ST_LCD_Delay(50);
	ST_LCD_ENReset();
}

void ST_LCD_Delay(uint32_t delay_us){
	delay_us *= 7;
	while(delay_us--);
}

void ST_LCD_Write(uint8_t st_cmd){
	ST_LCD_RWReset();
	ST_LCD_Load((st_cmd & 0xF0) >> 4);
	ST_LCD_Load(st_cmd & 0xF);
	ST_LCD_WriteCmd(0);
}

void ST_LCD_Printf(const char *st_string){
	do{
	//	if(iscntrl(*st_string)){
			switch(*st_string){
				case '\n': ST_LCD_ypos = ~ST_LCD_ypos & 1;
									 ST_LCD_Gotoxy(ST_LCD_xpos, ST_LCD_ypos); 
									 break;
				case '\r': ST_LCD_Gotoxy(0, ST_LCD_ypos); break;
				case '\b': ST_LCD_Gotoxy(ST_LCD_xpos - 1, ST_LCD_ypos); 
									 ST_LCD_Data(' ');
									 ST_LCD_Gotoxy(ST_LCD_xpos - 1, ST_LCD_ypos);
									 break;
				case  127: ST_LCD_Config(ST_LCD_ClearDisplay); break;
				default  : ST_LCD_Data(*st_string); break; 
			}
		//}
	}while(*++st_string != '\0');
}

void ST_LCD_Gotoxy(uint8_t st_x,uint8_t st_y){
	ST_LCD_xpos = st_x;
	ST_LCD_ypos = st_y;
	st_y = ST_LCD_SetDDRAMMsk | ((st_y * 0x40) + st_x);
	ST_LCD_Config(st_y);
}

void ST_LCD_WriteCGRAM(uint8_t *st_matriz, uint8_t st_address){
	st_address |= ST_LCD_SetCGRAMMsk;
	ST_LCD_Config(st_address);
	for(uint8_t st_cnt = 0;st_cnt < 8;st_cnt++){
		ST_LCD_RSSet();
		ST_LCD_Write(*st_matriz++);
	}
	ST_LCD_Gotoxy(ST_LCD_xpos,ST_LCD_ypos);
	ST_LCD_Data((st_address & 0x38) >> 3);
}