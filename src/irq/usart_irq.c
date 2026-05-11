#include <stddef.h>

#include "bsp/board.h"
#include "drivers/usart_driver.h"
#include "lib/ringbuf.h"

void	usart_rx_irq_handler(t_usart *usart)
{
	char	c = usart->USART->RXDATA & 0xFFUL;

	ringbuf_insert(&usart->ringbuf, c);
}

// void	usart_rx_irq_handler(USART_TypeDef *USART)
// {
// 	char		c = USART->RXDATA & 0xFFUL;
// 	t_uart_rx	*rx = get_uart_rx(USART);
//
// 	if (rx->ifs != -1)
// 		return ;
// 	// set the flag if an input separator is found
// 	if (bm_strchr(USART_RX_IFS, c))
// 		rx->ifs = rx->head;
//
// 	uart_rx_insert(rx, c);
//
// 	USART->IFC |= (1UL << 2);
//
// 	uart_putchar(USART, c);
// }

void USART0_RX_IRQHandler(void)
{
	usart_rx_irq_handler(board_get_usart0());
}

// void USART1_RX_IRQHandler(void)
// {
// 	usart_rx_irq_handler(board_get_usart1());
// }
//
// void USART2_RX_IRQHandler(void)
// {
// 	usart_rx_irq_handler(board_get_usart2());
// }
//
// void USART3_RX_IRQHandler(void)
// {
// 	usart_rx_irq_handler(board_get_usart3());
// }
