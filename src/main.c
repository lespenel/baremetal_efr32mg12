#include <stdint.h>

#include "cmu.h"
#include "gpio.h"
#include "gpio_driver.h"
#include "config.h"
#include "nvic.h"
#include "timer.h"

#include "clock_driver.h"
#include "dcdc_driver.h"
#include "uart_driver.h"
#include "usart.h"

#define LED0_PIN 4
#define LED1_PIN 5

void init_leds(void)
{
	enable_gpio_port(GPIO_PORTF, LED0_PIN, gpio_mode_PUSHPULL);
	enable_gpio_port(GPIO_PORTF, LED1_PIN, gpio_mode_PUSHPULL);
	// bit 19:16 control the pin 4 (PF4 the LED0) CLEAR
	// GPIO->P[GPIO_PORTF].MODEL &= ~(0x0F << (4 * LED0_PIN));
	// set the value 4 to set it in push-pull
	// GPIO->P[GPIO_PORTF].MODEL |= (4 << (4 * LED0_PIN));
	// bit 23:20 control the pin 5 (PF4 the LED1) CLEAR
	// GPIO->P[GPIO_PORTF].MODEL &= ~(0x0F << (4 * LED1_PIN));
	// set the value 4 to set it in push-pull
	// GPIO->P[GPIO_PORTF].MODEL |= (4 << (4 * LED1_PIN));
}

void timer0_init(void)
{
	// Reset timer
	TIMER0->CMD = 0;
	TIMER0->CNT = 0;

	// Set PRESC (DIV 1024)
	TIMER0->CTRL &= ~(0xF << 24);
	TIMER0->CTRL |= (10 << 24);

	TIMER0->TOP = 0xFFFF;
	// Start
	TIMER0->CMD = 1;
}

int main(void)
{
	DCDCInit();
	init_hfxo();
	init_lfxo();

	// set HFXTAL as the HFCLK
	CMU->HFCLKSEL = CMU_HFCLKSEL_HFXO;
	
	CMU->HFBUSCLKEN0 |= (1 << CMU_HFBUSCLKEN0_GPIO_SHIFT);		// enable GPIO CLK
	CMU->HFPERCLKEN0 |= (1 << CMU_HFPERCLKEN0_TIMER0_SHIFT);	// enable TIMER0 clock

	init_leds();

	UART_Config_TypeDef	usart3_config;


	usart3_config.tx_pin = 6;
	usart3_config.rx_pin = 7;
	usart3_config.vcom_enable = 0;
	usart3_config.baud_rate = USART_DESIRED_BAUD_RATE;
	usart3_config.tx_loc = 10;
	usart3_config.rx_loc = 10;
	usart3_config.UART = USART3;
	usart3_config.tx_port = GPIO_PORTB;
	usart3_config.rx_port = GPIO_PORTB;
	init_uart(&usart3_config);
	timer0_init();

	// set the overflow flag for timer0 interupt
	// TIMER0->IEN = TIMER_IEN_OF;

	// Enable TIMER0 interupt in the NVIC
	// NVIC->ISER[0] = (1UL << 11);
	uint32_t	start = TIMER0->CNT;
	int tx = 0;
	while (1)
	{
		uint32_t elapsed = TIMER0->CNT - start;
		if (elapsed < (TIMER0->TOP / 2))
		{
			GPIO->P[GPIO_PORTF].DOUT |= (1 << LED0_PIN);
			GPIO->P[GPIO_PORTF].DOUT &= ~(1 << LED1_PIN);
			if (tx == 0)
			{
				uart_putstring(USART3, "Salut tout le monde \r\n");
				tx = 1;
			}
		}
		else
		{
			tx = 0;
			GPIO->P[GPIO_PORTF].DOUT &= ~(1 << LED0_PIN);
			GPIO->P[GPIO_PORTF].DOUT |= (1 << LED1_PIN);
		}
	}

	return (0);
}
