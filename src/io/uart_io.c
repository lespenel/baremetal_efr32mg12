#include "config.h"
#include "drivers/gpio_driver.h"
#include "drivers/uart_driver.h"
#include "gpio.h"
#include "util.h"
#include <stddef.h>
#include "io/uart_io.h"

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

ssize_t	read(int fd, void *buff, size_t count)
{
	(void)fd;
	size_t	i = 0;
	while (i < count)
	{
		((char *)buff)[i] = uart_getchar(USART0);
		++i;
	}
	return (count);
}

int bm_strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] && s1[i] != s2[i] && i < n - 1)
		++i;
	return (s1[i] - s2[i]);
}

char *bm_strstr(char *big, char *litle)
{
	size_t len = bm_strlen(litle);

	while (*big)
	{
		if (bm_strncmp(big, litle, len) == 0)
			return (big);
		++big;
	}
	return (0);
}

void	uart_getline(USART_TypeDef *uart, char *buff, size_t size)
{
	uart_putstring(uart, CLI_PROMPT);

	char c = 0;
	for (uint64_t i = 0; i < size; ++i)
	{
		c = uart_getchar(uart);
		if (c)
			buff[i] = c;
		if (c == 0 || bm_strstr(buff, "\r\n") || bm_strstr(buff, "\n"))
			return;
		c = 0;
	}
}

void	config_usart0(void)
{
	UART_Config_TypeDef	usart3_config;

	memset(&usart3_config, 0, sizeof(UART_Config_TypeDef));

	usart3_config.tx_pin = 0;
	usart3_config.rx_pin = 1;
	usart3_config.vcom_enable = 1;
	usart3_config.baud_rate = USART_DESIRED_BAUD_RATE;
	usart3_config.tx_loc = 0;
	usart3_config.rx_loc = 0;
	usart3_config.UART = USART0;
	usart3_config.tx_port = GPIO_PORTA;
	usart3_config.rx_port = GPIO_PORTA;
	uart_init(&usart3_config);
}

void	config_usart3(void)
{
	UART_Config_TypeDef	usart3_config;

	memset(&usart3_config, 0, sizeof(UART_Config_TypeDef));

	usart3_config.tx_pin = 6;
	usart3_config.rx_pin = 7;
	usart3_config.vcom_enable = 0;
	usart3_config.baud_rate = USART_DESIRED_BAUD_RATE;
	usart3_config.tx_loc = 10;
	usart3_config.rx_loc = 10;
	usart3_config.UART = USART3;
	usart3_config.tx_port = GPIO_PORTB;
	usart3_config.rx_port = GPIO_PORTB;
	uart_init(&usart3_config);
}
