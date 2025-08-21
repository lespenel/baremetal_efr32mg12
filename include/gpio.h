#ifndef GPIO_H
# define GPIO_H

#include <stdint.h>

#define GPIO_BASE (0x4000A000UL)

//General Purpose Input/Output (p.1116)
typedef struct
{
	volatile uint32_t	CTRL;			/* Port Control Register */
	volatile uint32_t	MODEL;			/* Port Pin Mode Low Register */
	volatile uint32_t	MODEH;			/* Port Pin Mode High Registe */
	volatile uint32_t	DOUT;			/* Port Data Out Register */

	uint32_t			RESERVED0[2U];
	volatile uint32_t	DOUTTGL;		/* Port Data Out Toggle Register */
	volatile uint32_t	DIN;			/* Port Data in Register */
	volatile uint32_t	PINLOCKN;		/* Port Unlocked Pins Register */

	uint32_t			RESERVED1[1U];
	volatile uint32_t	OVTDIS;			/* Over Voltage Disable for All Modes */

	uint32_t			RESERVED2[1U];
}	GPIO_PORT_TypeDef;

typedef struct
{
	GPIO_PORT_TypeDef	P[12U];
	volatile uint32_t	EXTIPSELL;		/* External Interrupt Port Select Low Register */
	volatile uint32_t	EXTIPSELH;		/* External Interrupt Port Select High Register */
	volatile uint32_t	EXTIPINSELL;	/* External Interrupt Pin Select Low Register */
	volatile uint32_t	EXTIPINSELH;	/* External Interrupt Pin Select High Register */
	volatile uint32_t	EXTIRISE;		/* External Interrupt Rising Edge Trigger Reg */
	volatile uint32_t	EXTIFALL;		/* External Interrupt Falling Edge Trigger Reg */
	volatile uint32_t	EXTILEVEL;		/* External Interrupt Level Register */
	volatile uint32_t	IF;				/* Interrupt Flag Register */
	volatile uint32_t	IFS;			/* Interrupt Flag Set Register */
	volatile uint32_t	IFC;			/* Interrupt Flag Clear Register */
	volatile uint32_t	IEN;			/* Interrupt Enable Register */
	volatile uint32_t	EM4WUEN;		/* EM4 Wake Up Enable Register */

	uint32_t			RESERVED0[4U];
	volatile uint32_t	ROUTEPEN;		/* I/O Routing Pin Enable Register */
	volatile uint32_t	ROUTELOC0;		/* I/O Routing Location Register */
	volatile uint32_t	ROUTELOC1;		/* I/O Routing Location Register 1 */
	
	uint32_t			RESERVED1[1U];
	volatile uint32_t	INSENSE;		/* Input Sense Register */
	volatile uint32_t	LOCK;			/* Configuration Lock Register */

}	GPIO_TypeDef;

#define GPIO	((GPIO_TypeDef *) GPIO_BASE)

#define GPIO_PORTA	0
#define GPIO_PORTB	1
#define GPIO_PORTC	2
#define GPIO_PORTD	3
#define GPIO_PORTE	4
#define GPIO_PORTF	5
#define GPIO_PORTG	6
#define GPIO_PORTH	7
#define GPIO_PORTI	8
#define GPIO_PORTJ	9
#define GPIO_PORTK	10
#define GPIO_PORTL	11

#endif
