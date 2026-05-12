#include "debug_server.h"

char	*toto = "salut tout le monde";
char	*leo = "je suis leo";
int		count = 42;
int		voltage = -78452;


void	debug_server_init(t_debug_server *server, t_transport *transport)
{
	server->transport = transport;
	server->var_count = 0;
	server->rx_len = 0;

	debug_server_register_var("toto", toto, STRING);
	debug_server_register_var("leo", leo, STRING);
	debug_server_register_var("count", &count, INT);
	debug_server_register_var("voltage", &voltage, INT);
}
