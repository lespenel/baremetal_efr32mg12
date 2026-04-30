#include "console.h"

int	echo(int argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
	{
		if (i > 1)
			console_putstr(" ");
		console_putstr(argv[i]);
	}
	console_putstr_crlf("");
	return (0);
}
