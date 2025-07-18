#include <stdint.h>
#include "timer.h"

#define CMU_BASE			(0x400E4000UL) /* CMU base address  */

// BUS clock
#define HFBUSCLKEN0_OFFSET	(0x0B0UL)
#define HFBUSCLKEN0			(*(volatile uint32_t *)(CMU_BASE + HFBUSCLKEN0_OFFSET))

// Peripherals clock (bit 0 timer 0, bit 1 timer 1)
#define HFPERCLKEN0_OFFSET	(0x0C0UL)
#define HFPERCLKEN0			(*(volatile uint32_t *)(CMU_BASE + HFPERCLKEN0_OFFSET))

// base for GPIO
#define GPIO_BASE		(0x4000A000UL)
// step for each port go from a to l (0 to 11) so 0x210 / 11 = 0x30
#define GPIO_PORT_STEP	0x30 // 0x210 / 11

// first port F register
#define GPIO_PF_CTRL (GPIO_BASE + GPIO_PORT_STEP * 5)

//classic offset from 0 work see RM page.1116
#define GPIO_PA_MODEL_OFST		0x004
#define GPIO_PA_DOUT_OFST		0x00C
#define GPIO_PA_DOUTTGL_OFST	0x018

#define GPIO_PF_MODEL (*(volatile uint32_t *)(GPIO_PF_CTRL + GPIO_PA_MODEL_OFST))
#define GPIO_PF_DOUT (*(volatile uint32_t *)(GPIO_PF_CTRL + GPIO_PA_DOUT_OFST))
#define GPIO_PF_DOUTTGL (*(volatile uint32_t *)(GPIO_PF_CTRL + GPIO_PA_DOUTTGL_OFST))

#define LED0_PIN 4
#define LED1_PIN 5

void ft_sleep(uint32_t time)
{
	for (volatile uint32_t i = 0; i < time; ++i)
		__asm__("nop");
}

void init_leds(void)
{
	// bit 19:16 control the pin 4 (PF4 the LED0) CLEAR
	GPIO_PF_MODEL &= ~(0x0F << (4 * LED0_PIN));
	// set the value 4 to set it in push-pull
	GPIO_PF_MODEL |= (4 << (4 * LED0_PIN));
	// bit 23:20 control the pin 5 (PF4 the LED1) CLEAR
	GPIO_PF_MODEL &= ~(0x0F << (4 * LED1_PIN));
	// set the value 4 to set it in push-pull
	GPIO_PF_MODEL |= (4 << (4 * LED1_PIN));
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
	HFBUSCLKEN0 |= (1 << 3);	// set the bit 3 to enable GPIO CLK
	HFPERCLKEN0 |= (1 << 0);	// enable TIMER0 clock

	init_leds();
	timer0_init();

	while (!(TIMER0->STATUS & 1));
	while (1)
	{
		uint32_t ms = TIMER0->CNT / 1000;
		uint32_t mod = ms % 10;

		if (mod == 5)
		{
			GPIO_PF_DOUT |= (1 << LED0_PIN);
			GPIO_PF_DOUT &= ~(1 << LED1_PIN);
		}
		else if (mod == 0)
		{
			GPIO_PF_DOUT &= ~(1 << LED0_PIN);
			GPIO_PF_DOUT |= (1 << LED1_PIN);
		}
	}

	return (0);
}
