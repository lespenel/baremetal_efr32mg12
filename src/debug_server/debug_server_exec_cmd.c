#include "debug_server.h"
#include "util.h"

static void	unknown_command(char *cmd);

// typedef enum e_cmd_type
// {
// 	INSPECT,
// }	t_cmd_type;
//
typedef struct s_cmd_map
{
	char	*key;
	int		(*func)(t_debug_server *s, int argc, char **argv);
}	t_cmd_map;

int	inspect(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	return (0);
}

int	debug_server_exec_cmd(t_debug_server *server, int argc, char **argv)
{
	const t_cmd_map	cmd_map[] = {
		{"inspect", debug_server_inspect},
	};

	(void)server;
	if (argc == 0)
		return (0);

	const int map_size = sizeof(cmd_map) / sizeof(t_cmd_map);
	for (int j = 0; j < map_size; ++j)
	{
		if (bm_strcmp(cmd_map[j].key, argv[0]) == 0)
			return (cmd_map[j].func(server, argc, argv));
	}
	unknown_command(argv[0]);
	return (-1);
}

static void	unknown_command(char *cmd)
{
	(void)cmd;
	// console_putstr("Unknown command: ");
	// console_putstr_crlf(cmd);
}
