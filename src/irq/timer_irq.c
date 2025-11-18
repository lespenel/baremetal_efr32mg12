#include "timer.h"

static uint32_t	overflow_count = 0;

void	TIMER0_IRQHandler(void)
{
	overflow_count++;
	// set to clear the OF Interrupt Flag
	TIMER0->IFC = 1;
	
}

uint32_t	timer0_get_overflow_count(void)
{
	return (overflow_count);
}
