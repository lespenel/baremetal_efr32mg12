#include "bsp/board.h"
#include "interfaces/serial.h"

//TODO: avoid hardcoded dest UARTE
int	inspect(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	serial_putstr(board_get_serial0(), "Bonjour je suis leo\r\n");
	return (0);
}
