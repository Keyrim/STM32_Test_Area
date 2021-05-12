/*
 * mask_def.c
 *
 *  Created on: 17 sept. 2020
 *      Author: Theo
 */

#include "mask_def.h"



//Prototypes
// ----------------	GYRO ------------------------
static void mask_def_gyro_data_ready(Event_t * event);
static void mask_def_gyro_init_ok(Event_t * event);

// ----------------	ACC ------------------------
static void mask_def_acc_data_ready(Event_t * event);
static void mask_def_acc_init_ok(Event_t * event);

// ----------------	Orientation ------------------------
static void mask_def_orientation_update(Event_t * event);



void mask_def_events_init(Event_t * event){
	//Gyro mask def
	mask_def_gyro_init_ok(&event[EVENT_GYRO_INIT_OK]);
	mask_def_gyro_data_ready(&event[EVENT_GYRO_DATA_READY]);
	//Acc mask def
	mask_def_acc_init_ok(&event[EVENT_ACC_INIT_OK]);
	mask_def_acc_data_ready(&event[EVENT_ACC_DATA_READY]);
	//Orientation
	mask_def_orientation_update(&event[EVENT_ORIENTATION_UPDATE]);

}

// ----------------	GYRO ------------------------
static void mask_def_gyro_init_ok(Event_t * event){
	//Si le gyro est init et pas déjà en train de tourner
	MASK_set_flag(&event->mask_and[MASK_GYRO_INIT_OK], FLAG_GYRO_OK);
	MASK_set_flag(&event->mask_or[MASK_GYRO_INIT_OK], FLAG_GYRO_OK);
	MASK_set_flag(&event->mask_not[MASK_GYRO_INIT_OK], FLAG_GYRO_READING);
}

static void mask_def_gyro_data_ready(Event_t * event){
	//Si le gyro est init et pas déjà en train de tourner
	MASK_set_flag(&event->mask_and[MASK_GYRO_DATA_READY], FLAG_GYRO_OK);
	MASK_set_flag(&event->mask_or[MASK_GYRO_DATA_READY], FLAG_GYRO_DATA_READY);
}

// ----------------	ACC ------------------------

static void mask_def_acc_init_ok(Event_t * event){
	//Si le gyro est init et pas déjà en train de tourner
	MASK_set_flag(&event->mask_and[MASK_ACC_INIT_OK], FLAG_ACC_OK);
	MASK_set_flag(&event->mask_or[MASK_ACC_INIT_OK], FLAG_ACC_OK);
	MASK_set_flag(&event->mask_not[MASK_ACC_INIT_OK], FLAG_ACC_READING);
}

static void mask_def_acc_data_ready(Event_t * event){
	//Si le gyro est init et pas déjà en train de tourner
	MASK_set_flag(&event->mask_and[MASK_ACC_DATA_READY], FLAG_ACC_OK);
	MASK_set_flag(&event->mask_or[MASK_ACC_DATA_READY], FLAG_ACC_DATA_READY);
}

// ----------------	ORIENTATION ------------------------
static void mask_def_orientation_update(Event_t * event){
	//Si les données filtrées du gyro et de l'acc on go
	MASK_set_flag(&event->mask_and[MASK_ORIENTATION_UPDATE], FLAG_ACC_OK);
	MASK_set_flag(&event->mask_and[MASK_ORIENTATION_UPDATE], FLAG_GYRO_OK);
	MASK_set_flag(&event->mask_and[MASK_ORIENTATION_UPDATE], FLAG_GYRO_FILTERED_DATA_READY);
	MASK_set_flag(&event->mask_or[MASK_ORIENTATION_UPDATE], FLAG_ACC_FILTERED_DATA_READY);
}




