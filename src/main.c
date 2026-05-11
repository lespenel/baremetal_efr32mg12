#include "bsp/board.h"
#include "bsp/leds.h"

#include "console.h"

#include "scheduler.h"

static void	app_init(void);

int main(void)
{
	board_init();

	app_init();

	led1_toggle();
	while (1)
	{
		scheduler_run();
	}
	return (0);
}

static void	app_init(void)
{
	console_init(board_get_serial0());
}
