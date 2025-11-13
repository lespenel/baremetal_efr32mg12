#include "drivers/gpio_driver.h"
#include "gpio.h"

#define LED0_PIN 4
#define LED1_PIN 5

void	leds_init(void)
{
	enable_gpio_port(GPIO_PORTF, LED0_PIN, gpio_mode_PUSHPULL);
	enable_gpio_port(GPIO_PORTF, LED1_PIN, gpio_mode_PUSHPULL);
}

void	leds_set(uint8_t led0, uint8_t led1)
{
	if (led0)
		GPIO->P[GPIO_PORTF].DOUT |= (1 << LED0_PIN);
	else
		GPIO->P[GPIO_PORTF].DOUT &= ~(1 << LED0_PIN);
	if (led1)
		GPIO->P[GPIO_PORTF].DOUT |= (1 << LED1_PIN);
	else
		GPIO->P[GPIO_PORTF].DOUT &= ~(1 << LED1_PIN);
}

void	led0_toggle(void)
{
	GPIO->P[GPIO_PORTF].DOUTTGL |= (1 << LED0_PIN);
}

void	led1_toggle(void)
{
	GPIO->P[GPIO_PORTF].DOUTTGL |= (1 << LED1_PIN);
}
