#ifndef CONSOLE_H
# define CONSOLE_H

#include <stdint.h>

#include "interfaces/serial.h"

#define CONSOLE_PROMPT	"EFR32MG12> "
#define CONSOLE_EOL		"\r\n"
#define CONSOLE_IFS		" \t\n\r"

#define CONSOLE_MAX_LINE_SIZE	1024
#define CONSOLE_MAX_ARG_COUNT	32
#define CONSOLE_MAX_ARG_SIZE	32

typedef enum e_cmd_type
{
	ECHO,
	HELP,
	INSPECT,
	I,
	SEND,
	UNKNOWN
}	t_cmd_type;

typedef int	(*t_cmd)(int argc, char **argv);

typedef struct s_cmd_map
{
	char		*name;
	t_cmd		func;
}	t_cmd_map;

void	console_init(t_serial *serial);

t_serial	*console_get_serial(void);

void	console_task(void);
int		cli_exec(int argc, char **argv);

void	console_putstr_crlf(const char *str);
void	console_putstr(const char *str);

int	inspect(int argc, char **argv);
int	help(int argc, char **argv);
int	echo(int argc, char **argv);
int	send(int argc, char **argv);

#endif
