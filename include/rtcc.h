#ifndef RTCC_H
# define RTCC_H

#include <stdint.h>

#define RTCC_BASE (0x40042000UL)

typedef struct
{
	volatile uint32_t	CTRL;	/* CC Channel Control Register */
	volatile uint32_t	CCV;	/* Capture/Compare Value Register */
	volatile uint32_t	TIME;	/* Capture/Compare Time Register */
	volatile uint32_t	DATE;	/* Capture/Compare Date Register */
}	RTCC_CC_TypeDef;

typedef struct
{
	volatile uint32_t	CTRL;		/* Controle Register */
	volatile uint32_t	PRECNT;		/* Pre Counter Value Register */
	volatile uint32_t	CNT;		/* Counter Value Register */
	volatile uint32_t	COMBCNT;	/* Combined Pre-Counter and Counter Value Register */
	volatile uint32_t	TIME;		/* Time of Day Register */
	volatile uint32_t	DATE;		/* Date Register */
	volatile uint32_t	IF;			/* RTCC Interrupt Flags */
	volatile uint32_t	IFS;		/* Interrupt Flag Set Register */
	volatile uint32_t	IFC;		/* Interrupt Flag Clear Register */
	volatile uint32_t	IEN;		/* Interrupt Enable Register */
	volatile uint32_t	STATUS;		/* Status Register */
	volatile uint32_t	CMD;		/* Command Register */
	volatile uint32_t	SYNCBUSY;	/* Synchronization Busy Register */
	volatile uint32_t	POWERDOWN;	/* Retention RAM Power-down Register */
	volatile uint32_t	LOCK;		/* Configuration Lock Register */
	volatile uint32_t	EM4WUEN;	/* Wake Up Enable */

	RTCC_CC_TypeDef		CC[3U];		/* CC Channels */
	
	uint32_t			RESERVED0[37U];	/* Reserver registers */

	volatile uint32_t	RET[32U];	/** RetentionReg */
}	RTCC_TypeDef;

#define RTCC ((RTCC_TypeDef *) RTCC_BASE)

#endif
