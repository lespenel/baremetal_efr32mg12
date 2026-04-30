#include <stddef.h>
#include <stdint.h>

#include "bsp/leds.h"
#include "config.h"

#include "io/uart_io.h"
#include "scheduler.h"
#include "timer.h"

void	prompt_task(void)
{
	char buff[1024] = {0};
	size_t	ret = uart_readline(USART0, buff, 1024);

	if (ret != 0)
	{
		if (buff[0])
			uart_putstring_crlf(USART0, buff);
		uart_putstring(USART0, CLI_PROMPT);
	}
}

void	led_task(void)
{
	// led0_toggle();
	// led1_toggle();
}

#define TASKS_NB 2

t_task	tasks[TASKS_NB] = {
	{prompt_task, 0, 0},
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
