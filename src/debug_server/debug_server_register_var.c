#include "debug_server.h"

int	debug_server_register_var(char *name, void *var, t_var_type type)
{
	t_debug_server	*server = debug_server_get();

	if (server->var_count >= DEBUG_VAR_COUNT_MAX)
		return (-1);

	server->vars[server->var_count].name = name;
	server->vars[server->var_count].var = var;
	server->vars[server->var_count].type = type;

	server->var_count++;

	return (0);
}
