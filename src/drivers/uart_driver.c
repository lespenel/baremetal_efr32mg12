#include "cmu.h"
#include "config.h"
#include "gpio.h"
#include "usart_reg.h"

#include "drivers/gpio_driver.h"
#include "drivers/uart_driver.h"

static inline uint32_t	get_usart_clock_shift(USART_TypeDef *uart);
static void	set_baud_rate(USART_TypeDef *UART, uint32_t baud_rate);
static void	enable_vcom(void);

static t_uart_rx	uart0_rx = {{0}, 0, 0, 0, -1};
static t_uart_rx	uart1_rx = {{0}, 0, 0, 0, -1};
static t_uart_rx	uart2_rx = {{0}, 0, 0, 0, -1};
static t_uart_rx	uart3_rx = {{0}, 0, 0, 0, -1};

/**
 * @brief Configure and Enable the specified USART in asynchronous mode
 *	specified in 'cfg'
 *
 * @param cfg Configuration struct containing the USARTn
 */
void	uart_init(UART_Config_TypeDef *cfg)
{
	CMU->HFPERCLKEN0 |= (1 << get_usart_clock_shift(cfg->UART)); // enable clock

	enable_gpio_port(cfg->tx_port, cfg->tx_pin, gpio_mode_PUSHPULL);
	enable_gpio_port(cfg->rx_port, cfg->rx_pin, gpio_mode_INPUT);

	// The USART operates in asynchronous mode when SYNC in USARTn_CTRL is cleared to 0	
	cfg->UART->CTRL &= ~USART_CTRL_SYNC;
	cfg->UART->CTRL &= ~USART_CTRL_LOOPBK;

	// The number of data bits in a frame is set by DATABITS in USARTn_FRAME
	// and the number of stop-bits is set by STOPBITS in USARTn_FRAME
	// Whether or not a parity bit should be included, and even or odd is defined by PARITY
	cfg->UART->FRAME = USART_FRAME_DATABITS_EIGHT
					| USART_FRAME_STOPBITS_ONE
					| (0 << 8);

	set_baud_rate(cfg->UART, USART_DESIRED_BAUD_RATE);
	if (cfg->vcom_enable)
		enable_vcom();

	cfg->UART->ROUTELOC0 = (cfg->tx_loc << 8) | (cfg->rx_loc << 0);
	cfg->UART->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;
	
	cfg->UART->CMD = USART_CMD_TXEN | USART_CMD_RXEN; // Enable TX
}

/**
 * @brief send the char 'c' via the given UART
 */
void	uart_putchar(USART_TypeDef *UART, unsigned char c)
{
	UART->TXDATA = (uint32_t)c;

	// Wait until the Transmission is complete
	while ((UART->STATUS & USART_STATUS_TXC) == 0);
}

char	uart_getchar(USART_TypeDef *UART)
{
	while ((UART->STATUS & USART_STATUS_RXDATAV) == 0);
	char c = UART->RXDATA & 0xFFUL;

	uart_putchar(UART, c);
	return (c);
}

char	uart_rx_consume(t_uart_rx *rx)
{
	char	c;

	if (rx->len == 0)
		return ('\0');
	c = rx->buffer[rx->tail];
	rx->tail = (rx->tail + 1) % UART_BUFFER_SIZE;
	--rx->len;
	return (c);
}

void	uart_rx_insert(t_uart_rx *rx, char c)
{
	rx->buffer[rx->head] = c;
	rx->head = (rx->head + 1) % UART_BUFFER_SIZE;

	if (rx->len < UART_BUFFER_SIZE)
		++rx->len;
	else
		rx->tail = (rx->tail + 1) % UART_BUFFER_SIZE;
}

t_uart_rx	*get_uart_rx(USART_TypeDef *uart)
{
	if (uart == USART0)
		return (&uart0_rx);
	if (uart == USART1)
		return (&uart1_rx);
	if (uart == USART2)
		return (&uart2_rx);
	return (&uart3_rx);
}

static inline uint32_t	get_usart_clock_shift(USART_TypeDef *uart)
{
	if (uart == USART0)
		return (CMU_HFPERCLKEN0_USART0_SHIFT);
	if (uart == USART1)
		return (CMU_HFPERCLKEN0_USART1_SHIFT);
	if (uart == USART2)
		return (CMU_HFPERCLKEN0_USART2_SHIFT);
	if (uart == USART3)
		return (CMU_HFPERCLKEN0_USART3_SHIFT);
	return (0);
}

/**
 * @brief set the given baud_rate to the given UART (oversampling x16)
 */
static void	set_baud_rate(USART_TypeDef *UART, uint32_t baud_rate)
{
	// br = fHFPERCLK/(oversample x (1 + USARTn_CLKDIV/256))
	UART->CLKDIV = 256 * (HFX_FREQ / (16 * baud_rate) - 1);
}

static void	enable_vcom(void)
{
	enable_gpio_port(GPIO_PORTA, 5, gpio_mode_PUSHPULL);
	GPIO->P[GPIO_PORTA].DOUT |= (1 << 5);
}
