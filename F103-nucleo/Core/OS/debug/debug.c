/*
 * debug.c
 *
 *  Created on: Nov 21, 2020
 *      Author: Théo
 */



#include "debug.h"
#include "retarget.h"

extern UART_HandleTypeDef huart2 ;

void DEBUG_init(void){
	RetargetInit(&huart2);
}

