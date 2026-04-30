#include <stddef.h>

#include "drivers/uart_driver.h"
#include "usart_reg.h"
#include "util.h"

void	usart_rx_irq_handler(USART_TypeDef *USART)
{
	char		c = USART->RXDATA & 0xFFUL;
	t_uart_rx	*rx = get_uart_rx(USART);

	if (rx->ifs != -1)
		return ;
	// set the flag if an input separator is found
	if (bm_strchr(UART_RX_IFS, c))
		rx->ifs = rx->head;

	uart_rx_insert(rx, c);

	USART->IFC |= (1UL << 2);

	uart_putchar(USART, c);
}

void USART0_RX_IRQHandler(void)
{
	usart_rx_irq_handler(USART0);
}

void USART1_RX_IRQHandler(void)
{
	usart_rx_irq_handler(USART1);
}

void USART2_RX_IRQHandler(void)
{
	usart_rx_irq_handler(USART2);
}

void USART3_RX_IRQHandler(void)
{
	usart_rx_irq_handler(USART3);
}
