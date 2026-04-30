#ifndef USART_DRIVER_H
# define USART_DRIVER_H

#include <stddef.h>

#include "usart_reg.h"

typedef struct
{
	USART_TypeDef	*USART;
	uint32_t		baud_rate;
	uint8_t			tx_pin;
	uint8_t			tx_port;
	uint8_t			tx_loc;
	uint8_t			rx_pin;
	uint8_t			rx_port;
	uint8_t			rx_loc;
	uint8_t			vcom_enable;

}	t_usart_config;


#define USART_BUFFER_SIZE		1024
#define USART_RX_IFS			"\n\r"

typedef struct s_uart_rx
{
	volatile char		buffer[USART_BUFFER_SIZE];
	volatile uint16_t	len;
	volatile uint16_t	head;
	volatile uint16_t	tail;
	volatile int32_t	ifs;
}	t_uart_rx;

#include "lib/ringbuf.h"

typedef struct s_usart
{
	USART_TypeDef	*USART;
	t_ringbuf		ringbuf;
}	t_usart;

void	uart_init(t_usart *usart, const t_usart_config *cfg);

void	uart_putchar(USART_TypeDef *UART, unsigned char c);
char	uart_getchar(USART_TypeDef *UART);

t_uart_rx	*get_uart_rx(USART_TypeDef *uart);
size_t		uart_read(USART_TypeDef *uart, char *buff, size_t size);
int8_t		uart_buffchr(USART_TypeDef *uart, char c);

char		uart_rx_consume(t_uart_rx *rx);
void		uart_rx_insert(t_uart_rx *rx, char c);
t_uart_rx	*get_uart_rx(USART_TypeDef *uart);

#endif
