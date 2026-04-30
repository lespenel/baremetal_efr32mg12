#include "cmu.h"

#include "drivers/clock_driver.h"
#include "drivers/dcdc_driver.h"
#include "drivers/timer_driver.h"

#include "bsp/leds.h"

#include "io/uart_io.h"

#include "scheduler.h"

void	board_init(void)
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
}

int main(void)
{
	board_init();

	led1_toggle();
	while (1)
	{
		scheduler_run();
	}
	return (0);
}
