 /******************************************************************************
 *
 * Module: uart_to_pc
 *
 * File Name: uart_to_pc.h
 *
 * Description: module to send data to pc using the uart protocol
 *
 *******************************************************************************/

#ifndef UART_TO_PC_H_
#define UART_TO_PC_H_

/*********************************** INCLUDES *******************************************/

#include "tm4c123gh6pm_registers.h"
#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"
#include "common_macros.h"
#include "uart.h"

/************************************ DEFINITIONS ****************************************/

#define ARRAY_SIZE 300

/********************************* PROTOTYPES ********************************************/

void save_coordinates(double latitude,double longitude);
void send_to_pc(double latitude,double longitude);
void send_all_coordinates_to_pc(double* latitude,double* longitude);

/*********************************** EXTERN **********************************************/

extern double latitude_array[ARRAY_SIZE];
extern double longitude_array[ARRAY_SIZE];

#endif /*UART_TO_PC_H_*/
