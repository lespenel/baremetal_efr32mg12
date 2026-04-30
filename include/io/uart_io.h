#ifndef UART_IO_H
# define UART_IO_H

#include <stddef.h>

#include "usart_reg.h"

void	uart_putchar(USART_TypeDef *UART, unsigned char c);
void	uart_putstring(USART_TypeDef *UART, char *str);
void	uart_putstring_crlf(USART_TypeDef *UART, char *str);
void	uart_print_reg(USART_TypeDef *UART, uint32_t reg);
void	uart_print_uint(USART_TypeDef *UART, uint32_t nb);

size_t	uart_readline(USART_TypeDef *uart, char *buff, size_t size);
size_t	uart_read(USART_TypeDef *uart, char *buff, size_t size);

#endif
