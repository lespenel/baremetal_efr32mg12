#include "console.h"

int	clear(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	console_putstr("\033c");

	return (0);
}
