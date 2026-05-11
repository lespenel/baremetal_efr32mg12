#include "interfaces/serial.h"

int	serial_putc(t_serial *serial, char c)
{
	return (serial->putc(serial->backend, c));
}

int	serial_getc(t_serial *serial, char *out)
{
	return (serial->getc(serial->backend, out));
}

int	serial_putstr(t_serial *serial, const char *s)
{
	while (*s)
		serial_putc(serial, *s++);
	return (0);
}
