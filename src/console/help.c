#include "console.h"

int	help(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	console_putstr_crlf("");
	console_putstr_crlf("   echo");

	return (0);
}
