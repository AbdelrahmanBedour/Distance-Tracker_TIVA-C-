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


/********************************* PROTOTYPES ********************************************/

void send_to_pc(char* latitude_string,char* longitude_string);

#endif /*UART_TO_PC_H_*/
