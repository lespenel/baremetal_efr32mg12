#include "cmu.h"

#include "drivers/clock_driver.h"
#include "drivers/dcdc_driver.h"
#include "drivers/timer_driver.h"
#include "drivers/usart_driver.h"

#include "usart_reg.h"
#include "config.h"
#include "nvic.h"

#include "gpio.h"

#include "bsp/leds.h"

#include "util.h"

static void	config_usart0(void);
static void	config_usart3(void);

static	t_usart	g_usart0;
static	t_usart	g_usart3;

void	board_init(void)
{
	DCDCInit();
	init_hfxo();
	init_lfxo();

	// set HFXTAL as the HFCLK
	CMU->HFCLKSEL = CMU_HFCLKSEL_HFXO;
	
	// enable GPIO CLK
	CMU->HFBUSCLKEN0 |= (1 << CMU_HFBUSCLKEN0_GPIO_SHIFT);

	leds_init();
	config_usart3();
	config_usart0();

	timer0_init();
}


static void	config_usart0(void)
{
	t_usart_config	usart0_config;

	memset(&usart0_config, 0, sizeof(t_usart_config));

	usart0_config.tx_pin = 0;
	usart0_config.rx_pin = 1;
	usart0_config.vcom_enable = 1;
	usart0_config.baud_rate = USART_DESIRED_BAUD_RATE;
	usart0_config.tx_loc = 0;
	usart0_config.rx_loc = 0;
	usart0_config.USART = USART0;
	usart0_config.tx_port = GPIO_PORTA;
	usart0_config.rx_port = GPIO_PORTA;

	uart_init(&g_usart0, &usart0_config);
	NVIC_interupt_set_enable(NVIC_IRQ_USART0_RX);
	USART0->IEN |= (1UL << 2);
}

static void	config_usart3(void)
{
	t_usart_config	usart3_config;

	memset(&usart3_config, 0, sizeof(t_usart_config));

	usart3_config.tx_pin = 6;
	usart3_config.rx_pin = 7;
	usart3_config.vcom_enable = 0;
	usart3_config.baud_rate = USART_DESIRED_BAUD_RATE;
	usart3_config.tx_loc = 10;
	usart3_config.rx_loc = 10;
	usart3_config.USART = USART3;
	usart3_config.tx_port = GPIO_PORTB;
	usart3_config.rx_port = GPIO_PORTB;
	uart_init(&g_usart3, &usart3_config);
	NVIC_interupt_set_enable(NVIC_IRQ_USART3_RX);
	USART3->IEN |= (1UL << 2);
}
