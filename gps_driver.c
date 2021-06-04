#include "gps_driver.h"

void gps_init(void)
{
	UART1_init();

	#if VCC_GND == 1  /*Initalize PA3 & PA4 for VCC and GND in case they are not hard wired (Optional)*/
		GPIO_PORTA_AMSEL_REG &= !(VCC_PIN | GND_PIN);         /* Disable Analog on PA2 and PA3 */
		GPIO_PORTA_PCTL_REG  &= 0xFFFF00FF;   /* Clear PMCx bits for PA2 and PA3 to use it as GPIO pin */
		GPIO_PORTA_DIR_REG   |= (VCC_PIN | GND_PIN);         /* Configure PA2 and PA3 as output pin */
		GPIO_PORTA_AFSEL_REG &= !(VCC_PIN | GND_PIN);         /* Disable alternative function on PA2 and PA3 */
		GPIO_PORTA_DEN_REG   |= (VCC_PIN | GND_PIN);         /* Enable Digital I/O on PA2 and PA3 */
		GPIO_PORTA_DATA_REG  &= !(GND_PIN);         /* Clear bit 4 in Data regsiter to use as ground */
		GPIO_PORTA_DATA_REG  |= VCC_PIN;			/* Set bit 3 in Data regsiter to use as VCC*/
	#endif
}

void gps_receive_data(char* lat,char* lon) //latitude & longitude are arrays of char with at least 10 elements
{
	char gpgll[] = {'g','p','g','l','l'};
	while(1)
	{
		char temp = UART1_recieveByte();
		if (temp == '$')
		{
			int right_string_flag=1;
			int i;
			for(i
					= 0; i < 5 ; i++)
			{
				temp = UART1_recieveByte();
				if(temp != gpgll[i])
				{
					right_string_flag=0;
				}
			}

			if(right_string_flag == 1)
			{
				while(temp != ',') //wasting characters not related to latitude or longitude
				{
					temp = UART1_recieveByte();
				}

				//receiving latitude into lat array
				i=0;
				temp = UART1_recieveByte();
				while(temp != ',')
				{
					lat[i] = temp;
					i++;
					temp = UART1_recieveByte();
				}

				temp = UART1_recieveByte();

				while(temp != ',') //wasting characters not related to latitude or longitude
				{
					temp = UART1_recieveByte();
				}

				//receiving longitude into lon array
				i=0;
				temp = UART1_recieveByte();
				while(temp != ',')
				{
					lon[i] = temp;
					i++;
					temp = UART1_recieveByte();
				}
				break;
			}
		}
	}
}
