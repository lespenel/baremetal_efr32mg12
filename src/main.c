#include "bsp/board.h"
#include "bsp/leds.h"

#include "debug_server.h"
#include "interfaces/transport.h"

static t_debug_server	g_debug_server;
static t_transport		g_transport_serial;

t_debug_server	*debug_server_get(void)
{
	return (&g_debug_server);
}

static void	app_init(void);

int main(void)
{
	board_init();

	app_init();

	while (1)
	{
		debug_server_poll(&g_debug_server);
	}
	return (0);
}

static void	app_init(void)
{
	transport_serial_init(&g_transport_serial, board_get_serial0());
	debug_server_init(&g_debug_server, &g_transport_serial);
}
