#include "console.h"
#include "util.h"

typedef struct s_help
{
    const char* name;
    const char* desc;
}	t_help;

int	help(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	const t_help cmds[] = {
		{"clear", "Clear the tty"},
		{"echo", "Display a line of text"},
	};
	int max_len = 0;


	const int num_commands = sizeof(cmds) / sizeof(t_help);

	for (int i = 0; i < num_commands; ++i)
	{
		int tmp = bm_strlen(cmds[i].name);
		if (tmp > max_len)
			max_len = tmp;
	}

	console_putstr_crlf("Available commands: \r\n");
	for (int i = 0; i < num_commands; ++i)
	{
		console_putstr("  ");
		console_putstr(cmds[i].name);
		int len = max_len - bm_strlen(cmds[i].name) + 2;
		for (int i = 0; i < len; ++ i)
			console_putstr(" ");
		console_putstr_crlf(cmds[i].desc);
	}
	console_putstr_crlf("\r\nType '<command> --help' for more details.");

	return (0);
}
