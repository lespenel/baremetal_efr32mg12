#ifndef CMU_H
# define CMU_H

#include <stdint.h>

#define CMU_BASE (0x400E4000UL)

//Clock Management Unit (p.327)
typedef struct
{
	volatile uint32_t	CTRL;					/* CMU Control Register */

	uint32_t			RESERVED0[3U];			/* Reserved */
	volatile uint32_t	HFRCOCTRL;				/* HFRCO Control Register */

	uint32_t			RESERVED1[1U];			/* Reserved */
	volatile uint32_t	AUXHFRCOCTRL;			/* AUXHFRCO Control Register */

	uint32_t			RESERVED2[1U];			/* Reserved */
	volatile uint32_t	LFRCOCTRL;				/* LFRCOCTRL Control Register */
	volatile uint32_t	HFXOCTRL;				/* HFXOCTRL Control Register */

	uint32_t			RESERVED3[1U];			/* Reserved */
	volatile uint32_t	HFXOSTARTUPCTRL;		/* HFXO Startup Control */
	volatile uint32_t	HFXOSTEADYSTATECTRL;	/* HFXO Steady State Control */
	volatile uint32_t	HFXOTIMEOUTCTRL;		/* HFXO Timeout Control */
	volatile uint32_t	LFXOCTRL;				/* LFXO Control Register */
	// 15 * uint32_t addr
	
	uint32_t			RESERVED4[5U];			/* Reserved */
	volatile uint32_t	CALCTRL;				/* Calibration Control Register */
	volatile uint32_t	CALCNT;					/* Calibration Counter Register */

	uint32_t			RESERVED5[2U];			/* Reserved */
	volatile uint32_t	OSCENCMD;				/* Oscillator Enable/Disable Command */
	volatile uint32_t	CMD;					/* Command Register */

	uint32_t			RESERVED6[2U];			/* Reserved */
	volatile uint32_t	DBGCLKSEL;				/* Debug Trace Clock Select */
	volatile uint32_t	HFCLKSEL;				/* HFCLK Select Command Register */

	// 15 * uint32_t addr
	uint32_t			RESERVED7[2U];			/* Reserved */
	volatile uint32_t	LFACLKSEL;				/* Low Frequency CLK A Select Register */
	volatile uint32_t	LFBCLKSEL;				/* Low Frequency CLK B Select Register */
	volatile uint32_t	LFECLKSEL;				/* Low Frequency CLK E Select Register */

	uint32_t			RESERVED8[1U];			/* Reserved */
	volatile uint32_t	STATUS;					/* Status Register */
	volatile uint32_t	HFCLKSTATUS;			/* HFCLK Status Register */

	uint32_t			RESERVED9[1U];			/* Reserved */
	volatile uint32_t	HFXOTRIMSTATUS;			/* HFXO Trim Status Register */
	volatile uint32_t	IF;						/* Interupt Flag Register */
	volatile uint32_t	IFS;					/* Interupt Flag Set Register */
	volatile uint32_t	IFC;					/* Interupt Flag Clear Register */
	volatile uint32_t	IEN;					/* Interupt Enable Register */
	volatile uint32_t	HFBUSCLKEN0;			/* HF Bus Clock Enable Register 0 */

	// 15 * uint32_t addr
	uint32_t			RESERVED10[3U];			/* Reserved */
	volatile uint32_t	HFPERCLKEN0;			/* HF Peripheral Clock Enable Register 0 */

	uint32_t			RESERVED11[2U];			/* Reserved */
	volatile uint32_t	HFRADIOALTCLKEN0;		/* HF Alt Radio Peripheral clk Enable 0 */

	uint32_t			RESERVED12[4U];			/* Reserved */
	volatile uint32_t	LFACLKEN0;				/* Low Frequency A Clock Enable 0 Async */

	uint32_t			RESERVED13[1U];			/* Reserved */
	volatile uint32_t	LFBCLKEN0;				/* Low Frequency B Clock Enable 0 Async */

	uint32_t			RESERVED14[1U];			/* Reserved */
	volatile uint32_t	LFECLKEN0;				/* Low Frequency E Clock Enable 0 Async */

	uint32_t			RESERVED15[3U];			/* Reserved */
	volatile uint32_t	HFPRESC;				/* High Frequency Clock Prescaler */

	uint32_t			RESERVED16[1U];			/* Reserved */
	volatile uint32_t	HFCOREPRESC;			/* High Frequency Core Clock Prescaler */
	volatile uint32_t	HFPERPRESC;				/* HF Peripheral Clock Prescaler */
	volatile uint32_t	HFRADIOPRESC;			/* HF Radio Peripheral Clock Prescaler */
	volatile uint32_t	HFEXPPRESC;				/* HF Export Clock Prescaler */

	uint32_t			RESERVED17[2U];			/* Reserved */
	volatile uint32_t	LFAPRESC0;				/* Low Frequency A Prescaler 0 Async*/

	uint32_t			RESERVED18[1U];			/* Reserved */
	volatile uint32_t	LFBPRESC0;				/* Low Frequency B Prescaler 0 Async*/

	uint32_t			RESERVED19[1U];			/* Reserved */
	volatile uint32_t	LFEPRESC0;				/* Low Frequency E Prescaler 0 Async*/

	uint32_t			RESERVED20[1U];			/* Reserved */
	volatile uint32_t	HFRADIOALTPRESC;		/* HF Alt Radio Peripheral clk Prescaler */

	uint32_t			RESERVED21[1U];			/* Reserved */
	volatile uint32_t	SYNCBUSY;				/* Synchronization Busy Register */
	volatile uint32_t	FREEZE;					/* Freeze Register */

	uint32_t			RESERVED22[2U];			/* Reserved */
	volatile uint32_t	PCNTCTRL;				/* PCNT Control Register */

	uint32_t			RESERVED23[2U];			/* Reserved */
	volatile uint32_t	ADCCTRL;				/* ADC Control Register */

	uint32_t			RESERVED24[4U];			/* Reserved */
	volatile uint32_t	ROUTEPEN;				/* I/O Routing Pin Enable Register */
	volatile uint32_t	ROUTELOC0;				/* I/O Routing Location Register */
	volatile uint32_t	ROUTELOC1;				/* I/O Routing Location Register */
	uint32_t			RESERVED25[1U];			/* Reserved */
	volatile uint32_t	LOCK;					/* Configuration Lock Register */
}	CMU_TypeDef;

#define CMU ((CMU_TypeDef *) CMU_BASE)

#define CMU_HFCLKSEL_HFRCO		1
#define CMU_HFCLKSEL_HFXO		2
#define CMU_HFCLKSEL_LFRCO		3
#define CMU_HFCLKSEL_LFXO		4
#define CMU_HFCLKSEL_HFRCODIV2	5
#define CMU_HFCLKSEL_CLKIN0		7

#define CMU_OSCENCMD_LFXOEN		(1UL << 8)
#define CMU_OSCENCMD_HFXOEN		(1UL << 2)

#define CMU_STATUS_HFXORDY		(1UL << 3)
#define CMU_STATUS_LFXORDY		(1UL << 9)
#define CMU_STATUS_CALRDY		(1UL << 16)

#define CMU_CMD_CALSTART		(1UL << 0)

#define CMU_CALCTRL_UPSEL_LFXO	(1UL << 0)

#endif
