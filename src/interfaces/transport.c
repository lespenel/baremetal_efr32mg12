#include "interfaces/serial.h"
#include "interfaces/transport.h"

void	transport_send(t_transport *tp, const char *data, uint32_t len)
{
	tp->send(tp->backend, data, len);
}

int	transport_read(t_transport *tp, char *out, uint32_t max_len)
{
	return (tp->read(tp->backend, out, max_len));
}

static void	transport_serial_send(void *back, const char *data, uint32_t len);
static int	transport_serial_read(void *back, char *out, uint32_t max_len);

void	transport_serial_init(t_transport *tp, t_serial *serial)
{
	tp->backend = serial;
	tp->read = transport_serial_read;
	tp->send = transport_serial_send;
}

static void	transport_serial_send(void *back, const char *data, uint32_t len)
{
	for (uint32_t i = 0; i < len; ++i)
	{
		serial_putc((t_serial *)back,  data [i]);
	}
}

static int	transport_serial_read(void *back, char *out, uint32_t max_len)
{
	uint32_t	i = 0;

	while(i < max_len && serial_getc((t_serial *)back, &out[i]))
		++i;
	return ((int)i);
}
