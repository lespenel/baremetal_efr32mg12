#ifndef NVIC_H
# define NVIC_H

#include <stdint.h>

typedef struct
{
	volatile uint32_t	ICTR;			/* Interrupt Controller Type Register, ICTR */

	uint32_t			reserved0[62];	/* RESERVED */
	volatile uint32_t	ISER[8];		/* Interrupt Set-Enable Registers */

	uint32_t			reserved1[24];	/* RESERVED */
	volatile uint32_t	ICER[8];		/* Interrupt Clear-Enable Registers */

	uint32_t			reserved2[24];	/* RESERVED */
	volatile uint32_t	ISPR[8];		/* Interrupt Set-Pending Registers */

	uint32_t			reserved3[24];	/* RESERVED */
	volatile uint32_t	ICPR[8];		/* Interrupt Clear-Pending Registers */

	uint32_t			reserved4[24];	/* RESERVED */
	volatile uint32_t	IABR[8];		/* Interrupt Active Bit Registers */

	uint32_t			reserved5[56];	/* RESERVED */
	volatile uint32_t	IPR[60];		/* Interrupt Priority Registers */

}	NVIC_Typedef;

#define NVIC	((NVIC_Typedef *)(0xE000E004UL))

void	NVIC_interupt_set_enable(uint32_t to_enable);

#define NVIC_IRQ_EMU		0
#define NVIC_IRQ_WDOG0		2
#define NVIC_IRQ_WDOG1		3
#define NVIC_IRQ_LDMA		9
#define NVIC_IRQ_GPIO_EVEN	10
#define NVIC_IRQ_TIMER0		11
#define NVIC_IRQ_USART0_RX	12
#define NVIC_IRQ_USART0_TX	13
#define NVIC_IRQ_ACMP0_1	14
#define NVIC_IRQ_ADC0		15
#define NVIC_IRQ_IADC0		16
#define NVIC_IRQ_I2C0		17
#define NVIC_IRQ_GPIO_ODD	18
#define NVIC_IRQ_TIMER1		19
#define NVIC_IRQ_USART1_RX	20
#define NVIC_IRQ_USART1_TX	21
#define NVIC_IRQ_LEUART0	22
#define NVIC_IRQ_PCNT0		23
#define NVIC_IRQ_CMU		24
#define NVIC_IRQ_MSC		25
#define NVIC_IRQ_CRYPTO0	26
#define NVIC_IRQ_LETIMER0	27
#define NVIC_IRQ_RTCC		30
#define NVIC_IRQ_CRYOTIMER	32
#define NVIC_IRQ_FPUEH		34
#define NVIC_IRQ_SMU		35
#define NVIC_IRQ_WTIMER0	36
#define NVIC_IRQ_WTIMER1	37
#define NVIC_IRQ_PCNT1		38
#define NVIC_IRQ_PCNT2		39
#define NVIC_IRQ_USART2_RX	40
#define NVIC_IRQ_USART2_TX	41
#define NVIC_IRQ_I2C1		42
#define NVIC_IRQ_USART3_RX	43
#define NVIC_IRQ_USART3_TX	44
#define NVIC_IRQ_VDAC0		45
#define NVIC_IRQ_CSEN		46
#define NVIC_IRQ_LESENSE	47
#define NVIC_IRQ_CRYPTO1	48
#define NVIC_IRQ_TRNG0		49

#endif
