 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 *******************************************************************************/

#include "lcd.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void LCD_init(void)
{


        volatile unsigned long delay;
        SYSCTL_REGCGC2_REG  |= (1<<LCD_CTRL_PORT_NUM) | (1<<LCD_DATA_PORT_NUM) ; /* enable DATA & CTRL clock */
        delay = SYSCTL_REGCGC2_REG ; /* delay till the clock activated */

        *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT_BASE + PORT_ANALOG_MODE_SEL_REG_OFFSET) &= ~((1<<E) | (1<<RS) | (1<<RW)) ; /* Disable analog  */
        *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT_BASE + PORT_CTL_REG_OFFSET) &= ~((1<<E) | (1<<RS) | (1<<RW)); /* Normal GPIO */
        *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT_BASE + PORT_ALT_FUNC_REG_OFFSET) &= ~((0x0000000F<<(E*4)) | (0x0000000F<<(RS*4)) | (0x0000000F<<(RW*4)) ); /* NO ALT function */
        *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT_BASE + PORT_DIGITAL_ENABLE_REG_OFFSET) |= ((1<<E) | (1<<RS) | (1<<RW)); /* Enable the digital */
        *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT_BASE + PORT_PULL_UP_REG_OFFSET)  &= ~((1<<E) | (1<<RS) | (1<<RW)); /* No PullUp resis */
        *(volatile uint32 *)((volatile uint8 *)LCD_CTRL_PORT_BASE + PORT_PULL_DOWN_REG_OFFSET)  &= ~((1<<E) | (1<<RS) | (1<<RW)); /* No PullDown resis */
	LCD_CTRL_PORT_DIR |= ( (1<<E) | (1<<RS) | (1<<RW) ); /* Configure the control pins(E,RS,RW) as output pins */

	#if (DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_ANALOG_MODE_SEL_REG_OFFSET) &= ~(0xF0) /* Disable analog  */
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_CTL_REG_OFFSET) &= ~(0xF0); /* Normal GPIO */
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_ALT_FUNC_REG_OFFSET) &= ~(0xFFFF0000); /* NO ALT function */
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_DIGITAL_ENABLE_REG_OFFSET) |= (0xF0); /* Enable the digital */
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_PULL_UP_REG_OFFSET)  &= ~(0xF0); /* No PullUp resis */
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_PULL_DOWN_REG_OFFSET)  &= ~(0xF0); /* No PullDown resis */
			LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
		#else
			*(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_ANALOG_MODE_SEL_REG_OFFSET) &= ~(0x0F) /* Disable analog  */
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_CTL_REG_OFFSET) &= ~(0x0F); /* Normal GPIO */
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_ALT_FUNC_REG_OFFSET) &= ~(0x0000FFFF); /* NO ALT function */
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_DIGITAL_ENABLE_REG_OFFSET) |= (0x0F); /* Enable the digital */
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_PULL_UP_REG_OFFSET)  &= ~(0x0F); /* No PullUp resis */
                        *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_PULL_DOWN_REG_OFFSET)  &= ~(0x0F); /* No PullDown resis */
                        LCD_DATA_PORT_DIR |= 0x0F; /* Configure the lowest 4 bits of the data port as output pins */
		#endif
		LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
	#elif (DATA_BITS_MODE == 8)
                *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_ANALOG_MODE_SEL_REG_OFFSET) &= ~(0xFF); /* Disable analog  */
                *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_CTL_REG_OFFSET) &= ~(0xFF); /* Normal GPIO */
                *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_ALT_FUNC_REG_OFFSET) &= ~(0xFFFFFFFF); /* NO ALT function */
                *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_DIGITAL_ENABLE_REG_OFFSET) |= (0xFF); /* Enable the digital */
                *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_PULL_UP_REG_OFFSET)  &= ~(0xFF); /* No PullUp resis */
                *(volatile uint32 *)((volatile uint8 *)LCD_DATA_PORT_BASE + PORT_PULL_DOWN_REG_OFFSET)  &= ~(0xFF); /* No PullDown resis */
		LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	#endif

	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}



void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	Delay_MS(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	Delay_MS(1); /* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
#endif

	Delay_MS(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	Delay_MS(1); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	Delay_MS(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif

	Delay_MS(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	Delay_MS(1); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = command; /* out the required command to the data bus D0 --> D7 */
	Delay_MS(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	Delay_MS(1); /* delay for processing Th = 13ns */
#endif
}

void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,RS); /* Data Mode RS=1 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	Delay_MS(1); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	Delay_MS(1); /* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
#endif

	Delay_MS(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	Delay_MS(1); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	Delay_MS(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
#endif

	Delay_MS(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	Delay_MS(1); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = data; /* out the required command to the data bus D0 --> D7 */
	Delay_MS(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	Delay_MS(1); /* delay for processing Th = 13ns */
#endif
}
