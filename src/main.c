#include "cmu.h"
#include "gpio.h"
#include "nvic.h"
#include "timer.h"

#include "drivers/clock_driver.h"
#include "drivers/dcdc_driver.h"

#include "io/led_io.h"
#include "io/uart_io.h"

void timer0_init(void)
{
	// Reset timer
	TIMER0->CMD = 0;
	TIMER0->CNT = 0;

	// Set PRESC (DIV 1024)
	TIMER0->CTRL &= ~(0xF << 24);
	TIMER0->CTRL |= (10 << 24);

	TIMER0->TOP = 0xFFFF;
	// Start
	TIMER0->CMD = 1;
}

int main(void)
{
	DCDCInit();
	init_hfxo();
	init_lfxo();

	// set HFXTAL as the HFCLK
	CMU->HFCLKSEL = CMU_HFCLKSEL_HFXO;
	
	CMU->HFBUSCLKEN0 |= (1 << CMU_HFBUSCLKEN0_GPIO_SHIFT);		// enable GPIO CLK
	CMU->HFPERCLKEN0 |= (1 << CMU_HFPERCLKEN0_TIMER0_SHIFT);	// enable TIMER0 clock

	leds_init();
	config_usart3();
	config_usart0();
	timer0_init();

	// set the overflow flag for timer0 interupt
	// TIMER0->IEN = TIMER_IEN_OF;

	// Enable TIMER0 interupt in the NVIC
	// NVIC->ISER[0] = (1UL << 11);
	uint32_t	start = TIMER0->CNT;
	int tx = 0;
	while (1)
	{
		uint32_t elapsed = TIMER0->CNT - start;
		if (elapsed < (TIMER0->TOP / 2))
		{
			leds_set(1, 0);
			if (tx == 0)
			{
				uart_putstring(USART3, "Salut tout le monde \r\n");
				uart_print_reg(USART3, GPIO->P[GPIO_PORTF].MODEL);
				tx = 1;
			}
		}
		else
		{
			leds_set(0, 1);
			if (tx == 1)
			{
				uart_putstring(USART0, "Je parle dans le vcom \r\n");
				tx = 0;
			}
		}
	}
	return (0);
}
