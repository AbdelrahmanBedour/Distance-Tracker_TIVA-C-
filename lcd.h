 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"
#include "common_macros.h"
#include "tm4c123gh6pm_registers.h"
#include "delay.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* LCD HW Pins */
#define RS
#define RW
#define E

#define LCD_CTRL_PORT
#define LCD_CTRL_PORT_DIR

#define LCD_DATA_PORT
#define LCD_DATA_PORT_DIR


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);

#endif /* LCD_H_ */
