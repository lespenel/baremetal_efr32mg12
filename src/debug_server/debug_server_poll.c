#include "debug_server.h"
#include "interfaces/transport.h"
#include "util.h"

#define SERVER_IFS				"\t\n\r "
#define SERVER_MAX_ARG_COUNT	32

static void	build_argc_argv(char *line, int *argc, char **argv)
{
	char	*tmp = NULL;
	char	*token = NULL;

	token = bm_strtok_r(line, SERVER_IFS, &tmp);
	while (token != NULL && *argc < SERVER_MAX_ARG_COUNT)
	{
		argv[*argc] = token;
		++(*argc);
		token = bm_strtok_r(NULL, SERVER_IFS, &tmp);
	}
}
#include "bsp/leds.h"
static void debug_server_handle_response(t_debug_server *server)
{
	char	*argv[SERVER_MAX_ARG_COUNT];
	int		argc = 0;
	server->rx_buf[server->rx_len] = '\0';
	build_argc_argv(server->rx_buf, &argc, argv);
	if (argc != 0)
	{
		led1_toggle();
		debug_server_exec_cmd(server, argc, argv);
	}

	server->rx_len = 0;
}

static void	debug_server_feed_rx(t_debug_server *server, char *data, int len)
{
	for (int i = 0; i < len; ++i)
	{
		if (bm_strchr(TRANSPORT_EOF, data[i]))
			debug_server_handle_response(server);
		else if (server->rx_len < DEBUG_SERVER_RX_MAX - 1)
		{
			server->rx_buf[server->rx_len] = data[i];
			server->rx_len++;
		}
		else
		{
			server->rx_len = 0;
			transport_send(server->transport, "response too long", 18);
		}
	}
}

void	debug_server_poll(t_debug_server *server)
{
	char	tmp[64];
	int		n;

	n = transport_read(server->transport, tmp, 64 - 1);
	if (n > 0)
		debug_server_feed_rx(server, tmp, n);
}
