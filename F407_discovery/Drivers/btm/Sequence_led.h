/*
 * sequence_led.h
 *
 *  Created on: 22 juin 2020
 *      Author: Th�o
 */

#ifndef LIB_PERSO_SEQUENCE_LED_H_
#define LIB_PERSO_SEQUENCE_LED_H_

#include "macro_types.h"
#include "stm32f405xx.h"

//Structure utilis� par les fonctions s�quence led
typedef struct{
	GPIO_TypeDef* gpio;
	uint16_t gpio_pin ;
	uint32_t periode ;
	int32_t sequence ;		//Sequences lues de gauche � droite
	int8_t compteur ;
	int8_t length_sequence ;
	uint32_t previous_time ;
	bool_e output_logic ;	//True si logique n�gative au niveau de la led
}sequence_led_t;

void LED_SEQUENCE_init(sequence_led_t * seq_led, GPIO_TypeDef* gpio, uint16_t gpio_pin, int32_t init_seq, uint32_t periode, int8_t length_sequence, bool_e output_logic);
void LED_SEQUENCE_set_sequence(sequence_led_t * seq_led, int32_t seq);
void LED_SEQUENCE_play(sequence_led_t * seq_led, uint32_t current_time_us);

#endif /* LIB_PERSO_SEQUENCE_LED_H_ */
