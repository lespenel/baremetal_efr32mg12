#include "console.h"
#include "util.h"

static void	unknown_command(char *cmd);

int	cli_exec(int argc, char **argv)
{
	const t_cmd_map	cmd_map[] = {{"echo", echo},
	{"help", help}, {"inspect", inspect}, {"i", inspect},
	{"send", send}};

	if (argc == 0)
		return (0);

	for (int j = 0; j < UNKNOWN; ++j)
	{
		if (bm_strcmp(cmd_map[j].name, argv[0]) == 0)
			return (cmd_map[j].func(argc, argv));
	}
	unknown_command(argv[0]);
	return (-1);
}

static void	unknown_command(char *cmd)
{
	console_putstr("Unknown command: ");
	console_putstr_crlf(cmd);
}
