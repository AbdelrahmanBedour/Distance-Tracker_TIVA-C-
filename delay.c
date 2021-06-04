#include "delay.h"

void Delay_MS(unsigned long long n)
{
    volatile unsigned long long i = 0;
    while(i++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}
