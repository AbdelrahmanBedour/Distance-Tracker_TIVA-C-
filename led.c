 /******************************************************************************
 *
 * Module: led driver
 *
 * File Name: led.c
 *
 * Description: Source file for led driver
 *
 *******************************************************************************/

#include "led.h"

void Led_init(uint8 num)
{
  if (num < 1 || num > 3)
    return;
  
  const PinConfig ledConfig = {PORT_F, num, OUTPUT};
  Pin_init(&ledConfig);
}
void Led_on(uint8 num)
{
  if (num < 1 || num > 3)
  return;
    
  const PinConfig ledConfig = {PORT_F, num, OUTPUT};
  Pin_write(&ledConfig,HIGH);
}
void Led_off(uint8 num)
{
  if (num < 1 || num > 3)
  return;
  
  const PinConfig ledConfig = {PORT_F, num, OUTPUT};
  Pin_write(&ledConfig,LOW);
}
