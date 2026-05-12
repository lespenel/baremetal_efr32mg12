#ifndef TRANSPORT_H
# define TRANSPORT_H

#include <stddef.h>
#include <stdint.h>

typedef struct s_transport
{
	void	*backend;
	void	(*send)(void *back, const char *data, uint32_t len);
	int		(*read)(void *back, char *data, uint32_t len);

}	t_transport;

void	transport_send(t_transport *tp, const char *data, uint32_t len);
int		transport_read(t_transport *tp, char *data, uint32_t len);

#include "serial.h"

void	transport_serial_init(t_transport *tp, t_serial *serial);

#endif
