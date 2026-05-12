#ifndef BOARD_H
# define BOARD_H

#include "drivers/usart_driver.h"
#include "interfaces/serial.h"

void		board_init(void);

t_usart		*board_get_usart3(void);

t_serial	*board_get_serial0(void);

#endif
