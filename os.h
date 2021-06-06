 /******************************************************************************
 *
 * Module: Os
 *
 * File Name: Os.h
 *
 * Description: Header file for Os .
 *
 ******************************************************************************/

#ifndef OS_H_
#define OS_H_

/******************************* INCLUDES *********************************/

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
#include "std_types.h"
#include "tm4c123gh6pm_registers.h"
#include "app.h"
#include "uart.h"
#include "led.h"
#include "gps_driver.h"
#include "lcd.h"
#include "uart_to_pc.h"
#include "delay.h"


/***************************** FUNCTIONS ************************************/
/* Description: 
 * Function responsible for:
 * 1. Execute the Init Task
 * 2. Start the Program
 */
void Os_start(void);


void Os_Run(void);


#endif /* OS_H_ */
