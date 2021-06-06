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
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 8

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

/* LCD HW Pins */
#define RS                      5 /* PA5 */
#define RW                      6 /* PA6 */
#define E                       7 /* PA7 */

#define LCD_CTRL_PORT_BASE      GPIO_PORTA_BASE_ADDRESS 
#define LCD_CTRL_PORT           GPIO_PORTA_DATA_REG
#define LCD_CTRL_PORT_DIR       GPIO_PORTA_DIR_REG 
#define LCD_CTRL_PORT_NUM       0   

#define LCD_DATA_PORT_BASE      GPIO_PORTB_BASE_ADDRESS 
#define LCD_DATA_PORT           GPIO_PORTB_DATA_REG
#define LCD_DATA_PORT_DIR       GPIO_PORTB_DIR_REG 
#define LCD_DATA_PORT_NUM       1  

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80 

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_intgerToString(int data);

#endif /* LCD_H_ */
