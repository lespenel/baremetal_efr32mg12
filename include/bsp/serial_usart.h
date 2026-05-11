#ifndef SERIAL_USART_H
# define SERIAL_USART_H

#include "interfaces/serial.h"
#include "drivers/usart_driver.h"

void	serial_from_usart(t_serial *serial, t_usart *usart);

# endif
