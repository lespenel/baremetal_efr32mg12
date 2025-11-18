#include "config.h"
#include "cmu.h"
#include "nvic.h"
#include "timer.h"

void timer0_init(void)
{
	// enable TIMER0 clock
	CMU->HFPERCLKEN0 |= (1 << CMU_HFPERCLKEN0_TIMER0_SHIFT);
	
	// Reset timer
	TIMER0->CMD = 0;
	TIMER0->CNT = 0;

	// Set PRESC (DIV 1024)
	TIMER0->CTRL &= ~(0xF << 24);
	TIMER0->CTRL |= (0 << 24);

	TIMER0->TOP = (HFX_FREQ / 1000) - 1;
	// Start
	TIMER0->CMD = 1;

	// set the overflow flag for timer0 interupt
	TIMER0->IEN = TIMER_IEN_OF;

	// Enable TIMER0 interupt in the NVIC RM p42
	NVIC->ISER[0] = (1UL << 11);
}
