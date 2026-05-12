#ifndef DEBUG_SERVER_H
# define DEBUG_SERVER_H

#include "interfaces/transport.h"
#include <stdint.h>

typedef enum e_var_type
{
	INT,
	STRING,
	PTR,
}	t_var_type;

typedef struct	s_var_map
{
	char		*name;
	void		*var;
	t_var_type	type;
}	t_var_map;

#define DEBUG_VAR_COUNT_MAX	1024
#define DEBUG_SERVER_RX_MAX	1024

#define TRANSPORT_EOF		"\r\n"

typedef struct s_debug_server
{
	t_transport	*transport;
	char		rx_buf[DEBUG_SERVER_RX_MAX];
	uint32_t	rx_len;

	t_var_map	vars[DEBUG_VAR_COUNT_MAX];
	uint32_t	var_count;

}	t_debug_server;

void	debug_server_init(t_debug_server *server, t_transport *transport);
void	debug_server_poll(t_debug_server *client);

int	debug_server_exec_cmd(t_debug_server *server, int argc, char **argv);

t_debug_server	*debug_server_get(void);

int	debug_server_register_var(char *name, void *var, t_var_type type);

// cmds..
int	debug_server_inspect(t_debug_server	*s, int argc, char **argv);

#endif
