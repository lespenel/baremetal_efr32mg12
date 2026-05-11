#include "bsp/serial_usart.h"

static int	serial_usart_putc(void *ctx, char c);
static int	serial_usart_getc(void *ctx, char *out);
static int	usarte_read(t_usart *usart, char *out);

void	serial_from_usart(t_serial *serial, t_usart *usart)
{
	serial->backend = usart;
	serial->putc = serial_usart_putc;
	serial->getc = serial_usart_getc;
}

static int	serial_usart_putc(void *ctx, char c)
{
	usart_putc_poll((t_usart *)ctx, c);
	return (1);
}

static int	serial_usart_getc(void *ctx, char *out)
{
	return (usarte_read((t_usart *)ctx, out));
}

static int	usarte_read(t_usart *usart, char *out)
{
	return(ringbuf_consume(&usart->ringbuf, out));
}
