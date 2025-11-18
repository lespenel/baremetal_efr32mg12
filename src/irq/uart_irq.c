#include <stddef.h>

#include "drivers/uart_driver.h"
#include "util.h"

void USART3_RX_IRQHandler(void)
{
	char		c = USART3->RXDATA & 0xFFUL;
	t_uart_rx	*rx = get_uart_rx(USART3);

	if (rx->ifs != -1)
		return ;
	// set the flag if an input separator is found
	if (bm_strchr(UART_RX_IFS, c))
		rx->ifs = rx->head;

	uart_rx_insert(rx, c);

	USART3->IFC |= (1UL << 2);

	uart_putchar(USART3, c);
}
