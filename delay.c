#include "delay.h"

void Delay_MS(uint16 n)
{

  SysTick_Start(n);
  
  /* wait until thew COUNT flag = 1 which mean SysTick Timer reaches ZERO value */
  while(!(SYSTICK_CTRL_REG & (1<<16))); 
  
  SysTick_Stop();    
}
