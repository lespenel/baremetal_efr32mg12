#include "console.h"

#include "interfaces/serial.h"

#include "util.h"

static void	handle_line(void);
static void	build_argc_argv(char *line, int *argc, char **argv);
static void	handle_backspace(void);
static void	handle_char(char c);

typedef struct s_console
{
	t_serial	*serial;
	char		cli_line[CONSOLE_MAX_LINE_SIZE];
	uint32_t	cli_line_len;
}	t_console;

static t_console	g_console;

void	console_init(t_serial *serial)
{
	g_console.serial = serial;
}

t_serial	*console_get_serial(void)
{
	return (g_console.serial);
}

void	console_putstr(const char *str)
{
	t_serial	*serial = console_get_serial();

	serial_putstr(serial, str);
}

void	console_putstr_crlf(const char *str)
{
	t_serial	*serial = console_get_serial();

	serial_putstr(serial, str);
	serial_putstr(serial, "\r\n");
}

void	console_task(void)
{
	char	c = 0;

	if (g_console.serial == NULL)
		return ;
	while (serial_getc(g_console.serial, &c))
	{
		if (bm_strchr(CONSOLE_EOL, c))
			handle_line();
		else if (c == 0x7F || c == '\b')
			handle_backspace();
		else
			handle_char(c);
	}
}

static void	handle_line(void)
{
	char	*argv[CONSOLE_MAX_ARG_COUNT];
	int		argc = 0;

	serial_putstr(g_console.serial, "\r\n");
	g_console.cli_line[g_console.cli_line_len] = '\0';
	build_argc_argv(g_console.cli_line, &argc, argv);
	cli_exec(argc, argv);
	g_console.cli_line_len = 0;
	serial_putstr(g_console.serial, CONSOLE_PROMPT);
}

static void	build_argc_argv(char *line, int *argc, char **argv)
{
	char	*tmp = NULL;
	char	*token = NULL;

	token = bm_strtok_r(line, CONSOLE_IFS, &tmp);
	while (token && *argc < CONSOLE_MAX_ARG_COUNT)
	{
		argv[*argc] = token;
		++(*argc);
		token = bm_strtok_r(NULL, CONSOLE_IFS, &tmp);
	}
}

static void	handle_backspace(void)
{
	if (g_console.cli_line_len)
	{
		g_console.cli_line_len -= 1;
		serial_putstr(g_console.serial, "\b\033[K");
	}
}

static void	handle_char(char c)
{
	if (g_console.cli_line_len >= CONSOLE_MAX_LINE_SIZE - 1)
		return ;
	g_console.cli_line[g_console.cli_line_len] = c;
	g_console.cli_line_len += 1;
	if (c < ' ' || c > '~')
		serial_putc(g_console.serial, '.');
	else
		serial_putc(g_console.serial, c);
}
