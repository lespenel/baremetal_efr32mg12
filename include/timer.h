#ifndef TIMER_H
# define TIMER_H

#include <stdint.h>

#define TIMER0_BASE (0x40018000UL) /* TIMER1 base address */

typedef struct
{
	volatile uint32_t	CTRL;	/* CC Chanel Control Register */
	volatile uint32_t	CCV;	/* CC Chanel Value Register */
	volatile uint32_t	CCVP;	/* CC Chanel Value Peek Register */
	volatile uint32_t	CCVB;	/* CC Chanel Buffer Register */
}	TIMER_CC_TypeDef;


uint32_t	timer0_get_overflow_count(void);

// Register Map (p.697 of the RM)
typedef struct
{
	volatile uint32_t	CTRL;			/* Control Register */
	volatile uint32_t	CMD;			/* Command Register */
	volatile uint32_t	STATUS;			/* Status Register */
	volatile uint32_t	IF;				/* Interrupt Flag Register */
	volatile uint32_t	IFS;			/* Interrupt Flag Set Register */
	volatile uint32_t	IFC;			/* Interrupt Flag Clear Register */
	volatile uint32_t	IEN;			/* Interrupt Enable Register */
	volatile uint32_t	TOP;			/* Counter Top Value Register */
	volatile uint32_t	TOPB;			/* Counter Top Value Buffer Register */
	volatile uint32_t	CNT;			/* Counter Value Register */
	uint32_t			RESERVED0[1U];	/* reserved */
	volatile uint32_t	LOCK;			/* TIMER Configuration Lock Register */
	volatile uint32_t	ROUTEPEN;		/* I/O Routing Pin Enable Register */
	volatile uint32_t	ROUTELOC0;		/* I/O Routing Location Register */
	uint32_t			RESERVED1[1U];
	volatile uint32_t	ROUTELOC2;		/* I/O Routing Location Register */
	uint32_t			RESERVED2[8U];

	TIMER_CC_TypeDef	CC[4U];			/* Compare/Capture Channel */
	
	volatile uint32_t	DTCTRL;			/* DTI Control Register */
	volatile uint32_t	DTTIME;			/* DTI Time Control Register */
	volatile uint32_t	DTFC;			/* DTI Fault Configuration Register */
	volatile uint32_t	DTOGEN;			/* DTI Output Generatin Enable Register */
	volatile uint32_t	DTFAULT;		/* DTI Fault Register */
	volatile uint32_t	DTFAULTC;		/* DTI Fault Clear Register */
	volatile uint32_t	DTLOCK;			/* DTI Configuration Lock Register */
}	TIMER_TypeDef;

#define TIMER0 ((TIMER_TypeDef *) TIMER0_BASE)

#define TIMER_IEN_OF	(1UL << 0)

#endif
