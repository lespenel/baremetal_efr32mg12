#include "cmu.h"
#include "config.h"
#include "gpio.h"
#include "usart_reg.h"

#include "drivers/gpio_driver.h"
#include "drivers/usart_driver.h"

static inline uint32_t	get_usart_clock_shift(USART_TypeDef *uart);
static void	set_baud_rate(USART_TypeDef *UART, uint32_t baud_rate);
static void	enable_vcom(void);

#include "lib/ringbuf.h"

/**
 * @brief Configure and Enable the specified USART in asynchronous mode
 *	specified in 'cfg'
 *
 * @param cfg Configuration struct containing the USARTn
 */
void	usart_init(t_usart *usart, const t_usart_config *cfg)
{
	usart->USART = cfg->USART;
	ringbuf_init(&usart->ringbuf);

	CMU->HFPERCLKEN0 |= (1 << get_usart_clock_shift(usart->USART)); // enable clock

	enable_gpio_port(cfg->tx_port, cfg->tx_pin, gpio_mode_PUSHPULL);
	enable_gpio_port(cfg->rx_port, cfg->rx_pin, gpio_mode_INPUT);

	// The USART operates in asynchronous mode when SYNC in USARTn_CTRL is cleared to 0	
	usart->USART->CTRL &= ~USART_CTRL_SYNC;
	usart->USART->CTRL &= ~USART_CTRL_LOOPBK;

	// The number of data bits in a frame is set by DATABITS in USARTn_FRAME
	// and the number of stop-bits is set by STOPBITS in USARTn_FRAME
	// Whether or not a parity bit should be included, and even or odd is defined by PARITY
	usart->USART->FRAME = USART_FRAME_DATABITS_EIGHT
					| USART_FRAME_STOPBITS_ONE
					| (0 << 8);

	set_baud_rate(usart->USART, USART_DESIRED_BAUD_RATE);
	if (cfg->vcom_enable)
		enable_vcom();

	usart->USART->ROUTELOC0 = (cfg->tx_loc << 8) | (cfg->rx_loc << 0);
	usart->USART->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;
	
	usart->USART->CMD = USART_CMD_TXEN | USART_CMD_RXEN; // Enable TX
}

/**
 * @brief send the char 'c' via the given USART
 */
void	usart_putc_poll(t_usart *usart, unsigned char c)
{
	usart->USART->TXDATA = (uint32_t)c;

	// Wait until the Transmission is complete
	while ((usart->USART->STATUS & USART_STATUS_TXC) == 0);
}

char	usart_gtc_poll(t_usart *usart)
{
	while ((usart->USART->STATUS & USART_STATUS_RXDATAV) == 0);
	char c = usart->USART->RXDATA & 0xFFUL;

	return (c);
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
 * @brief set the given baud_rate to the given USART (oversampling x16)
 */
static void	set_baud_rate(USART_TypeDef *USART, uint32_t baud_rate)
{
	// br = fHFPERCLK/(oversample x (1 + USARTn_CLKDIV/256))
	USART->CLKDIV = 256 * (HFX_FREQ / (16 * baud_rate) - 1);
}

static void	enable_vcom(void)
{
	enable_gpio_port(GPIO_PORTA, 5, gpio_mode_PUSHPULL);
	GPIO->P[GPIO_PORTA].DOUT |= (1 << 5);
}
