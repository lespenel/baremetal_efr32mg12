#include "bsp/board.h"
#include "console.h"
#include "interfaces/serial.h"

//TODO FIX HARDCODED DEST
int	send(int argc, char **argv)
{
	if (argc != 2)
	{
		console_putstr_crlf("Wrong number of args");
		return (0);
	}
	serial_putstr(board_get_serial0(),argv[1]);
	return (0);
}
