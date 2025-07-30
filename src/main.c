#include <stdint.h>

#include "cmu.h"
#include "timer.h"
#include "nvic.h"

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

// Need to be calibrated
#define FREQ_HFXO	38400000UL
#define FREQ_LFXO	32768UL

void sleep_ms(uint32_t time_MS)
{
	uint32_t wait_tick = time_MS * (FREQ_HFXO / 1000 / 1024);
	uint32_t start = TIMER0->CNT;
	uint32_t elapsed = TIMER0->CNT - start;

	while (elapsed < wait_tick)
	{
		elapsed = TIMER0->CNT - start;
	}
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

void init_hfxo(void)
{
	// Enable HFXCLK
	CMU->OSCENCMD = CMU_OSCENCMD_HFXOEN;

	while ((CMU->STATUS & CMU_STATUS_HFXORDY) == 0)
	{
		__asm__("nop");
	}
}

void init_lfxo(void)
{
	// Enable LFXCLK
	CMU->OSCENCMD = CMU_OSCENCMD_LFXOEN;

	while ((CMU->STATUS & CMU_STATUS_LFXORDY) == 0)
	{
		__asm__("nop");
	}
}

uint32_t calibrate_hfxo(uint32_t HFCycles)
{
	CMU->CALCTRL =  CMU_CALCTRL_UPSEL_LFXO;

	CMU->CALCNT	= HFCycles;

	CMU->CMD = CMU_CMD_CALSTART;

	while ((CMU->STATUS & CMU_STATUS_CALRDY) == 0UL)
	{
		__asm__("nop");
	}

	return (CMU->CALCNT);
}

int main(void)
{
	init_hfxo();
	init_lfxo();
	uint32_t hfx_freq = calibrate_hfxo(1000000);
	(void)hfx_freq;

	float d = 5;
	(void)d;

	// set HFXTAL as the HFCLK
	CMU->HFCLKSEL = CMU_HFCLKSEL_HFXO;
	
	CMU->HFBUSCLKEN0 |= (1 << 3);	// set the bit 3 to enable GPIO CLK
// Peripherals clock (bit 0 timer 0, bit 1 timer 1)
	CMU->HFPERCLKEN0 |= (1 << 0);	// enable TIMER0 clock

	init_leds();
	timer0_init();

	// set the overflow flag for timer0 interupt
	TIMER0->IEN = TIMER_IEN_OF;

	// Enable TIMER0 interupt in the NVIC
	NVIC->ISER[0] = (1UL << 11);
	//while (!(TIMER0->STATUS & 1));

	uint32_t	start = TIMER0->CNT;

	while (1)
	{
		uint32_t elapsed = TIMER0->CNT - start;
		if (elapsed < (TIMER0->TOP/2))
		{
			GPIO_PF_DOUT |= (1 << LED0_PIN);
			GPIO_PF_DOUT &= ~(1 << LED1_PIN);
		}
		else
		{
			GPIO_PF_DOUT &= ~(1 << LED0_PIN);
			GPIO_PF_DOUT |= (1 << LED1_PIN);
		}
	}

	return (0);
}
