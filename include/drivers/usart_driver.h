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

#include "lib/ringbuf.h"

typedef struct s_usart
{
	USART_TypeDef	*USART;
	t_ringbuf		ringbuf;
}	t_usart;

void	usart_init(t_usart *usart, const t_usart_config *cfg);

void	usart_putc_poll(t_usart *usart, unsigned char c);
char	usart_gtc_poll(t_usart *usart);

size_t		uart_read(USART_TypeDef *uart, char *buff, size_t size);
int8_t		uart_buffchr(USART_TypeDef *uart, char c);

#endif
