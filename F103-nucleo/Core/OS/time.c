/*
 * time.c
 *
 *  Created on: Nov 21, 2020
 *      Author: Théo
 */

#include "time.h"


uint32_t TIME_us(void)
{

	uint32_t t_us;
	static uint32_t previous_t_us = 0;
	__disable_irq();
	t_us = HAL_GetTick() * 1000 + 1000 - SysTick->VAL / 64;
	__enable_irq();

	//Parfois la hal_get_tick ne s ait pas encore fait incrémenter, donc si notre miros actuel  est plus petit qu'avant on ajoute 1000µs (soit la ms qui n a pas été incrémenté)
	if(previous_t_us >= t_us)
		t_us += 1000;
	previous_t_us = t_us ;

	return t_us;
}
