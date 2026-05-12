#include "interfaces/transport.h"
#include "util.h"
#include "debug_server.h"
#include <stdint.h>

#include "bsp/leds.h"
int	get_var_content(void *var, t_var_type type)
{
	led0_toggle();
	if (type == STRING)
	{
		char *str = var;

		transport_send(debug_server_get()->transport, str, bm_strlen(str));
		transport_send(debug_server_get()->transport, "\r\n", 1);
		return (0);
	}
	if (type == INT)
	{
		int	*nb = var;
		char buf[42];

		char *ret = bm_itoa(buf, 42, *nb);

		transport_send(debug_server_get()->transport, ret, 42  - (ret - buf));
		transport_send(debug_server_get()->transport, "\r\n", 1);
		return (0);
	}
	return (-1);
}

int	get_var(char *var_name)
{
	t_debug_server *server = debug_server_get();

	for (uint32_t i = 0; i < server->var_count; ++i)
	{
		if (bm_strcmp(server->vars[i].name, var_name) == 0)
		{
			return (get_var_content(server->vars[i].var, server->vars[i].type));
		}
	}
	transport_send(debug_server_get()->transport, "Error: var not found", 21);
	return (-1);
}

int	debug_server_inspect(t_debug_server	*s, int argc, char **argv)
{
	(void)s;
	if (argc != 2)
	{
		// console_putstr_crlf("Wrong number of args");
		return (-1);
	}

	return (get_var(argv[1]));
}
