
#include "stm32f1xx_hal.h"
#include "stdint.h"
#include "stdbool.h"

#define ST_Matriz_WriteRow(ST_Val) GPIOA->BSRR |= (((~(uint32_t)ST_Val) & 0x7F) <<  1) << 16 \
																						|  ((uint32_t)ST_Val <<  1)
#define ST_Matriz_WriteCol(ST_Val) GPIOB->BSRR |= (((~(uint32_t)ST_Val) & 0x1F) << 11) << 16 \
																						|  ((uint32_t)ST_Val << 11)																						


void ST_Matriz_PrintfMatriz(const bool matriz[7][5]);
void ST_Matriz_Printf(uint8_t *matriz);
void ST_Matriz_PrintfIT(void);
void ST_Matriz_WriteM(uint8_t st_value, uint8_t st_pos);