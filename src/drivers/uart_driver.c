#include "cmu.h"
#include "config.h"
#include "usart.h"
#include "gpio.h"
#include "gpio_driver.h"
#include "uart_driver.h"
#include <stdint.h>

static void	set_baud_rate(USART_TypeDef *UART, uint32_t baud_rate);
static void	enable_vcom(void);

// RM p.553
/* typedef struct
{
	USART_TypeDef	*UART;
	uint32_t		baud_rate;
	uint8_t			tx_pin;
	uint8_t			tx_port;
	uint8_t			tx_loc;
	uint8_t			rx_pin;
	uint8_t			rx_port;
	uint8_t			rx_loc;
	uint8_t			vcom_enable;

}	USART_Config_TypeDef;
*/
void	init_uart(UART_Config_TypeDef *cfg)
{
	CMU->HFPERCLKEN0 |= (1 << CMU_HFPERCLKEN0_USART3_SHIFT); // enable clock

	enable_gpio_port(cfg->tx_port, cfg->tx_pin, gpio_mode_PUSHPULL);
	enable_gpio_port(cfg->rx_port, cfg->rx_pin, gpio_mode_INPUT);

	// The USART operates in asynchronous mode when SYNC in USARTn_CTRL is cleared to 0	
	cfg->UART->CTRL &= ~USART_CTRL_SYNC;
	cfg->UART->CTRL &= ~USART_CTRL_LOOPBK;

	// The number of data bits in a frame is set by DATABITS in USARTn_FRAME
	cfg->UART->FRAME = (USART_FRAME_DATABITS_EIGHT << USART_FRAME_DATABITS_SHIFT);
	// and the number of stop-bits is set by STOPBITS in USARTn_FRAME
	cfg->UART->FRAME |= (USART_FRAME_STOPBITS_ONE << USART_FRAME_STOPBITS_SHIFT);
	// Whether or not a parity bit should be included, and even or odd is defined by PARITY
	cfg->UART->FRAME |= (0 << 8);


	set_baud_rate(cfg->UART, USART_DESIRED_BAUD_RATE);
	if (cfg->vcom_enable)
		enable_vcom();


	cfg->UART->ROUTELOC0 = (cfg->tx_loc << 8) | (cfg->rx_loc << 0);
	cfg->UART->ROUTEPEN = USART_ROUTEPEN_TXPEN;
	
	cfg->UART->CMD = USART_CMD_TXEN; // Enable TX
}

static void	set_baud_rate(USART_TypeDef *UART, uint32_t baud_rate)
{
	// The USART has a fractional clock divider to allow the USART clock to be controlled
	// more accurately than what is possible with a stand

	// When operating in asynchronous mode, the baud rate (bit-rate) is 
	// br = fHFPERCLK/(oversample x (1 + USARTn_CLKDIV/256))
	UART->CLKDIV = 256 * (HFX_FREQ / (16 * baud_rate) - 1);
}

static void	enable_vcom(void)
{
	// Enable VCOM
	enable_gpio_port(GPIO_PORTA, 5, gpio_mode_PUSHPULL);
	GPIO->P[GPIO_PORTA].DOUT |= (1 << 5);
}

void	uart_putchar(USART_TypeDef *UART, unsigned char c)
{
	UART->TXDATA = (uint32_t)c;

	// Wait until the Transmission is complete
	while ((UART->STATUS & USART_STATUS_TXC) == 0);
}

void	uart_putstring(USART_TypeDef *UART, char *str)
{
	while (*str != '\0')
	{
		uart_putchar(UART, *str);
		++str;
	}
}
