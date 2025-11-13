#include "cmu.h"
#include "config.h"
#include "nvic.h"
#include "timer.h"

#include "drivers/clock_driver.h"
#include "drivers/dcdc_driver.h"

#include "io/led_io.h"
#include "io/uart_io.h"
#include "usart.h"
#include "scheduler.h"

void timer0_init(void)
{
	// enable TIMER0 clock
	CMU->HFPERCLKEN0 |= (1 << CMU_HFPERCLKEN0_TIMER0_SHIFT);
	
	// Reset timer
	TIMER0->CMD = 0;
	TIMER0->CNT = 0;

	// Set PRESC (DIV 1024)
	TIMER0->CTRL &= ~(0xF << 24);
	TIMER0->CTRL |= (10 << 24);

	TIMER0->TOP = (HFX_FREQ / 1024 / 1000) - 1;
	// Start
	TIMER0->CMD = 1;

	// set the overflow flag for timer0 interupt
	TIMER0->IEN = TIMER_IEN_OF;

	// Enable TIMER0 interupt in the NVIC RM p42
	NVIC->ISER[0] = (1UL << 11);
}

int main(void)
{
	DCDCInit();
	init_hfxo();
	init_lfxo();

	// set HFXTAL as the HFCLK
	CMU->HFCLKSEL = CMU_HFCLKSEL_HFXO;
	
	// enable GPIO CLK
	CMU->HFBUSCLKEN0 |= (1 << CMU_HFBUSCLKEN0_GPIO_SHIFT);

	leds_init();
	config_usart3();
	config_usart0();
	timer0_init();

	NVIC->ISER[0] = (1UL << 12);
	led1_toggle();

	while (1)
	{
		scheduler_run();
	}
	return (0);
}
