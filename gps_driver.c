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

void gps_receive_data(double* latitude_double,double* longitude_double) //returns lat and long as doubles in degrees for calculations.
{
	char lat[20];
	char lon[20];
	int lat_size=0;
	int lon_size=0;

	char *endp,*endp2;

	char gpgll[] = {'G','P','G','L','L'};
	while(1)
	{
		char temp = UART1_recieveByte();
		if (temp == '$')
		{
			int right_string_flag=1;
			int i;
			for(i = 0; i < 5 ; i++)
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
					lat_size++;
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
					lon_size++;
					i++;
					temp = UART1_recieveByte();
				}
				break;
			}
		}
	}

	*latitude_double = strtod(lat, &endp);
	*longitude_double = strtod(lon, &endp2);

	convert_to_degrees(latitude_double,longitude_double);

	char latitude_string_degrees[10];
	char longitude_string_degrees[10];

	snprintf(latitude_string_degrees, 10, "%f", *latitude_double);
	snprintf(longitude_string_degrees, 10, "%f", *longitude_double);

	send_to_pc(latitude_string_degrees,longitude_string_degrees);


}

void convert_to_degrees(double* latitude,double* longitude)
{
	int degrees;
	double minutes,seconds;

	/*latitude conversion*/
	degrees = (int)(*latitude/100);
	minutes = *latitude - (double)(degrees*100);
	seconds = minutes/60;
	*latitude = degrees + seconds;

	/*longitude conversion*/
	degrees = (int)(*longitude/100);
	minutes = *longitude - (double)(degrees*100);
	seconds = minutes/60;
	*longitude = degrees + seconds;

}