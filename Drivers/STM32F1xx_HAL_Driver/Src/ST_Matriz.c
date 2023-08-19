
#include "ST_Matriz.h"
volatile uint8_t caracterM[] = {0x04, 0x0E, 0x1F, 0x0E, 0x04};	

void ST_Matriz_PrintfMatriz(const bool matriz[7][5]){
	uint8_t st_row[5] = {0, 0, 0, 0, 0}, st_cnt2 = 0, st_i;
	for(st_i = 1;st_i < 0x80;st_i <<= 1, st_cnt2++){
		for(uint8_t st_cnt = 0;st_cnt < 6;st_cnt++){
			if(matriz[st_cnt2][st_cnt]) st_row[st_cnt] |= st_i;
		}
	}		
	for(st_i = 1, st_cnt2 = 0;st_i < 0x20;st_i <<= 1, st_cnt2++){
		ST_Matriz_WriteCol(st_i);
		ST_Matriz_WriteRow(st_row[st_cnt2]);
		HAL_Delay(1);
	}
}

void ST_Matriz_Printf(uint8_t *matriz){	
	for(uint8_t st_i = 1;st_i < 0x20;st_i <<= 1, matriz++){
		ST_Matriz_WriteCol(st_i);
		ST_Matriz_WriteRow(*matriz);
		HAL_Delay(1);
	}
}

void ST_Matriz_PrintfIT(void){
	static volatile uint8_t st_i = 1;
	static volatile uint8_t *matriz = caracterM;
	if(st_i < 0x20){
		ST_Matriz_WriteCol(st_i);
		ST_Matriz_WriteRow(*matriz);
		st_i <<= 1;
		matriz++;
	}	
	else{
		st_i = 1;
		matriz = caracterM;
	}
}

void ST_Matriz_WriteM(uint8_t st_value, uint8_t st_pos){
	caracterM[st_pos] = st_value;
}