#ifndef SERIAL_H
# define SERIAL_H

typedef struct s_serial
{
	void	*backend;
	int		(*putc)(void *ctx, char c);
	int		(*getc)(void *ctx, char *out);
}	t_serial;

int	serial_putc(t_serial *serial, char c);
int	serial_getc(t_serial *serial, char *out);
int	serial_putstr(t_serial *serial, const char *s);

#endif
