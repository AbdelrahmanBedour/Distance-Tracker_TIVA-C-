 /******************************************************************************
 *
 * Module: GPS
 *
 * File Name: gps_driver.h
 *
 * Description: driver to operate gps using uart protocol
 *
 *******************************************************************************/

#ifndef GPS_DRIVER_H_
#define GPS_DRIVER_H_

/*********************************** INCLUDES *******************************************/

#include <stdio.h>
#include <stdlib.h>
#include "tm4c123gh6pm_registers.h"
#include "std_types.h"
#include "common_macros.h"
#include "uart.h"
#include "uart_to_pc.h"

/********************************* DEFINITIONS ******************************************/

#define VCC_GND 0

#define CFG_COM0_PIN
#define CFG_COM1_PIN
#define CFG_GPS_PIN
#define GND_PIN (0x08) //PA3
#define VCC_PIN (0x04) //PA2


/********************************* PROTOTYPES ********************************************/
void gps_init(void);
void gps_receive_data(double* lat,double* lon);
void convert_to_degrees(double* latitude,double* longitude);

#endif /* GPS_DRIVER_H_*/
