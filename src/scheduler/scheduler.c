#include <stddef.h>
#include <stdint.h>

#include "bsp/leds.h"
#include "config.h"

#include "scheduler.h"
#include "timer.h"

#include "console.h"

void	led_task(void)
{
	led0_toggle();
	led1_toggle();
}

#define TASKS_NB 2

t_task	tasks[TASKS_NB] = {
	{console_task, 0, 0},
	{led_task, 1000, 0},
};

void	scheduler_run(void)
{
	uint32_t	time = timer0_get_overflow_count();

	for (uint32_t i = 0; i < TASKS_NB; ++i)
	{
		if (time - tasks[i].last_run >= tasks[i].interval)
		{
			tasks[i].callback();
			tasks[i].last_run = time;
		}
	}
	return ;
}
