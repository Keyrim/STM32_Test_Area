/*
 * orientation.c
 *
 *  Created on: Dec 6, 2020
 *      Author: Théo
 */


#include "orientation.h"

#define ORIENTATION_ALPHA 0.998f

static bool_e first_use = TRUE ;

//Kalman settings
static arm_matrix_instance_f32 A ;
static arm_matrix_instance_f32 B ;
static arm_matrix_instance_f32 C ;
static arm_matrix_instance_f32 R ;
static arm_matrix_instance_f32 Q ;
static arm_matrix_instance_f32 P ;

#define X_SIZE 2
#define U_SIZE 1
#define Z_SIZE 2

static float A_array[] = {0.9973, 0.009991, -0.5445, 0.9973};
static float B_array[] = {0, 0};
static float C_array[] = {1, 0, 0 ,1};
static float R_array[] = {0.1, 0, 0, 0.1};
static float Q_array[] = {0.2, 0, 0, 0.2};
static float P_array[] = {20, 0, 0, 20};
static float * u_ptr[U_SIZE];
static float * z_ptr[Z_SIZE];

static float x[] = {50, 0};




static float absolu(float x);
static float acc_correction(float x);
static float angle_180(float x);


static float angle_180(float x){
	if(x > 180)
		x -= 360;
	else if( x < -180)
		x += 360 ;
	return x ;
}

static float absolu(float x){
	if( x > 0)
		return x ;
	else
		return -x ;
}
static float acc_correction(float x){
	x = ( x > 0) ? 180 - x : -180 -x ;
	return x ;
}

void ORIENTATION_Init(orientation_t * orientation, gyro_t * gyro, acc_t * acc, int32_t frequency){
	//Kalman's matricies init
	arm_mat_init_f32(&A, X_SIZE, X_SIZE, A_array);
	arm_mat_init_f32(&B, X_SIZE, U_SIZE, B_array);
	arm_mat_init_f32(&C, Z_SIZE, X_SIZE, C_array);
	arm_mat_init_f32(&R, Z_SIZE, Z_SIZE, R_array);
	arm_mat_init_f32(&Q, X_SIZE, X_SIZE, Q_array);
	arm_mat_init_f32(&P, X_SIZE, X_SIZE, P_array);

	z_ptr[0] = &orientation->acc_angles[ORIENTATION_PITCH] ;
	z_ptr[1] = &gyro->filtered[ORIENTATION_PITCH];




	//Link data structures
	orientation->acc = acc ;
	orientation->gyro = gyro ;
	orientation->angular_velocity = gyro->filtered ;

	//Configure our frequency
	orientation->frequency = frequency ;
	orientation->periode = (float)1 / (float)frequency ;

	orientation->alpha = ORIENTATION_ALPHA ;

	//Init our values to zero
	for(int x = 0; x < 3; x++)
	{
		orientation->angular_position[x] = 0 ;
		orientation->angular_velocity[x] = 0 ;
	}

}

void ORIENTATION_Update(orientation_t * orientation){
	//Just to make the code shorter
	acc_t * acc = orientation->acc ;
	gyro_t * gyro = orientation->gyro ;

	//Guess our angular position using the accelerometer

	//Total acceleration
	float acc_total = acc->filtered[ORIENTATION_ROLL] * acc->filtered[ORIENTATION_ROLL] ;
	acc_total += acc->filtered[ORIENTATION_PITCH] * acc->filtered[ORIENTATION_PITCH] ;
	acc_total += acc->filtered[ORIENTATION_YAW] * acc->filtered[ORIENTATION_YAW] ;
	acc_total = sqrtf(acc_total);

	if(acc_total)	//To avoid /0
	{
		if(absolu(acc->filtered[ORIENTATION_YAW]) < acc_total)	//To avoid asin x with x greater than 1
			orientation->acc_angles[ORIENTATION_PITCH] = asinf(acc->filtered[ORIENTATION_YAW] / acc_total) * 57.32f;
//		if(absolu(acc->filtered[ORIENTATION_PITCH]) < acc_total) 	//To avoid asin x with x greater than 1
//			orientation->acc_angles[ORIENTATION_YAW] = -asinf(acc->filtered[ORIENTATION_PITCH] / acc_total) * 57.32f;
		if(acc->filtered[ORIENTATION_ROLL] < 0)
		{
//			orientation->acc_angles[ORIENTATION_YAW] = acc_correction(orientation->acc_angles[ORIENTATION_YAW]);
			orientation->acc_angles[ORIENTATION_PITCH] = acc_correction(orientation->acc_angles[ORIENTATION_PITCH]);
		}
	}

	//If it's our first use, we dont use the gyro
	if(first_use)
	{
//		orientation->angular_position[ORIENTATION_ROLL] = orientation->acc_angles[ORIENTATION_ROLL] ;
		orientation->angular_position[ORIENTATION_PITCH] = orientation->acc_angles[ORIENTATION_PITCH] ;
//		orientation->angular_position[ORIENTATION_YAW] = 0 ;
		first_use = FALSE ;
	}
	else
	{
		//Angular distance according to our angular velocities
//		float dx = gyro->filtered[ORIENTATION_ROLL] * orientation->periode ;
		float dy = gyro->filtered[ORIENTATION_PITCH] * orientation->periode ;
//		float dz = gyro->filtered[ORIENTATION_YAW] * orientation->periode ;

//		orientation->angular_position[ORIENTATION_ROLL] += dx ;
		orientation->angular_position[ORIENTATION_PITCH] += dy ;
//		orientation->angular_position[ORIENTATION_YAW] += dz ;

		//On prend en compte le transfert d'angle lors d'une rotation sur l'axe YAW (non pertinent avec le projet actuel)
//		float sin_dz = sinf(0.01745329251f * dz);
//		orientation->angular_position[ORIENTATION_ROLL] += sin_dz * orientation->angular_position[ORIENTATION_PITCH] ;
//		orientation->angular_position[ORIENTATION_PITCH] -= sin_dz * orientation->angular_position[ORIENTATION_ROLL] ;


//		orientation->angular_position[ORIENTATION_ROLL] = angle_180(orientation->angular_position[ORIENTATION_ROLL]);
		orientation->angular_position[ORIENTATION_PITCH] = angle_180(orientation->angular_position[ORIENTATION_PITCH]);

//		orientation->angular_position[ORIENTATION_ROLL] = orientation->alpha * orientation->angular_position[ORIENTATION_ROLL] + (1.0f - orientation->alpha) * orientation->acc_angles[ORIENTATION_ROLL];
		orientation->angular_position[ORIENTATION_PITCH] = orientation->alpha * orientation->angular_position[ORIENTATION_PITCH] + (1.0f - orientation->alpha) * orientation->acc_angles[ORIENTATION_PITCH];



	}
}






















