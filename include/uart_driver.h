#ifndef UART_DRIVER_H
# define UART_DRIVER_H

#include "usart.h"

typedef struct
{
	USART_TypeDef	*UART;
	uint32_t		baud_rate;
	uint8_t			tx_pin;
	uint8_t			tx_port;
	uint8_t			tx_loc;
	uint8_t			rx_pin;
	uint8_t			rx_port;
	uint8_t			rx_loc;
	uint8_t			vcom_enable;

}	UART_Config_TypeDef;

void	init_uart(UART_Config_TypeDef *cfg);
void	uart_putchar(USART_TypeDef *UART, unsigned char c);
void	uart_putstring(USART_TypeDef *UART, char *str);

#endif
