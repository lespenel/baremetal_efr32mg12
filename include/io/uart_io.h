#ifndef UART_IO_H
# define UART_IO_H

#include "usart.h"
#include <stddef.h>

typedef int64_t		ssize_t;

void	uart_putchar(USART_TypeDef *UART, unsigned char c);
void	uart_putstring(USART_TypeDef *UART, char *str);
void	uart_putstring_crlf(USART_TypeDef *UART, char *str);
void	uart_print_reg(USART_TypeDef *UART, uint32_t reg);
void	uart_print_uint(USART_TypeDef *UART, uint32_t nb);

void	config_usart0(void);
void	config_usart3(void);

void	uart_getline(USART_TypeDef *uart, char *buff, size_t size);

#endif
