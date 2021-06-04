 /******************************************************************************
 *
 * Module: led driver
 *
 * File Name: led.h
 *
 * Description: Header file for led driver
 *
 *******************************************************************************/
#ifndef LED_H_
#define LED_H_

#include "std_types.h"
#include "common_macros.h"
#include "port.h"




/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void Led_init(uint8 num);
void Led_on(uint8 num);
void Led_off(uint8 num);

#endif /* LED_H_ */