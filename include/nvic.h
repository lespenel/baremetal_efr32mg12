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

#endif
