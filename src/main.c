#include "board.h"
#include "bsp/leds.h"

#include "scheduler.h"

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
