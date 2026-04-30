#include <stddef.h>

#include "drivers/usart_driver.h"
#include "util.h"

/**
 * @brief Send a Null terminated string via UART
 */
void	uart_putstring(USART_TypeDef *UART, char *str)
{
	while (*str != '\0')
	{
		uart_putchar(UART, *str);
		++str;
	}
}

/**
 * @brief Send a Null terminated string and a "\r\n" via UART
 */
void	uart_putstring_crlf(USART_TypeDef *UART, char *str)
{
	uart_putstring(UART, str);
	uart_putstring(UART, "\r\n");
}

/**
 * @brief Display the binary value of a 32 bits register via UART
 */
void	uart_print_reg(USART_TypeDef *UART, uint32_t reg)
{
	int		size = 33;
	char	buff[size];
	int		i = 0;

	memset(buff, 0, size);

	bm_regtoa(buff, size - 1, reg);
	uart_putstring(UART, "|");
	while (buff[i] != 0)
	{
		uart_putchar(UART, buff[i]);
		++i;
		if (i % 4 == 0 )
			uart_putstring(UART, "|");
	}
	uart_putstring(UART, "\r\n");
}

/**
 * @brief Display an unsigned int via UART
 */
void	uart_print_uint(USART_TypeDef *UART, uint32_t nb)
{
	int		size = 33;
	char	buff[size];
	int		to_skip = 0;

	memset(buff, 0, size);

	bm_itoa(buff, size - 1, nb);
	while (buff[to_skip] == 0)
		++to_skip;
	uart_putstring_crlf(UART, buff + to_skip);
}

/**
 * @brief extracts one complete line from the UART RX ring buffer.
 * It reads characters until an input-separator (IFS) is encountered,
 * stores them in buff, null-terminates the string, 
 * and consumes any trailing IFS characters. 
 *
 * If a line was received but contains no characters (e.g., user pressed Enter),
 * the function returns 1. 
 * If no line is available, it returns 0. 
 * Otherwise, it returns the number of characters read
 *
 * @param uart uart to read the data from
 * @param buff buffer to store the readed line
 * @param size size of the input buffer
 *
 * @return 0 if no line is availabe,
 *		   1 if an empty line was received,
 *		   or the number of characters read.
 */
size_t	uart_readline(USART_TypeDef *uart, char *buff, size_t size)
{
	t_uart_rx	*rx = get_uart_rx(uart);
	size_t		i = 0;
	size_t		ifs_consumed = 0;

	if (rx->ifs == -1)
		return (0);
	while (rx->len != 0 && i < size - 1 &&
		bm_strchr(USART_RX_IFS, rx->buffer[rx->tail]) == NULL)
	{
		buff[i] = uart_rx_consume(rx);
		++i;
	}
	buff[i] = '\0';
	while (rx->len && bm_strchr(USART_RX_IFS, rx->buffer[rx->tail]))
	{
		uart_rx_consume(rx);
		ifs_consumed = 1;
	}
	rx->ifs = -1;
	if (i == 0 && ifs_consumed)
		return (1);
	return (i);
}

size_t	uart_read(USART_TypeDef *uart, char *buff, size_t size)
{
	t_uart_rx	*rx = get_uart_rx(uart);
	size_t		i = 0;

	while (rx->len != 0 && i < size)
	{
		buff[i] = rx->buffer[rx->tail];
		rx->tail = (rx->tail + 1) % USART_BUFFER_SIZE;
		--rx->len;
		++i;
	}
	return (i);
}
