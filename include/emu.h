#ifndef EMU_H
# define EMU_H

#include <stdint.h>

#define EMU_BASE (0x400E3000UL)

//Energy Management Unit (p.255)
typedef struct
{	
	volatile uint32_t	CTRL;			/* Memory System Control Register */
	volatile uint32_t	STATUS;			/* Status Register */
	volatile uint32_t	LOCK;			/* Configuration Lock Register */
	volatile uint32_t	RAM0CTRL;		/* Memory Control Register */
	volatile uint32_t	CMD;			/* Command Register */

	uint32_t			RESERVED0[1U];
	volatile uint32_t	EM4CTRL;		/* EM4 Control Register */
	volatile uint32_t	TEMPLIMITS;		/* Temperature Limits for interrupt Generation */
	volatile uint32_t	TEMP;			/* Value of Last Temperature Measurement */
	volatile uint32_t	IF;				/* Interrupt Flag Register */
	volatile uint32_t	IFS;			/* Interrupt Flag Set Register */
	volatile uint32_t	IFC;			/* Interrupt Flag Clear Register */
	volatile uint32_t	IEN;			/* Interrupt Enable Register */
	volatile uint32_t	PWRLOCK;		/* Regulator and Suplly Lock Register */
	volatile uint32_t	PWRCFG;			/* Power Configuration Register */
	volatile uint32_t	PWRCTRL;		/* Power Control Register */
	volatile uint32_t	DCDCCTRL;		/* DCDC Control */

	uint32_t			RESERVED1[2U];
	volatile uint32_t	DCDCMISCCTRL;	/* DCDC	Miscellaneous Control Register */
	volatile uint32_t	DCDCZDETCTRL;	/* DCDC	Power Train NFET Zero Current Detector */
	volatile uint32_t	DCDCCLIMCTRL;	/* DCDC	Power Train PFET Current Limiter Control */
	volatile uint32_t	DCDCLNCOMPCTRL;	/* DCDC	Low Noise Compensator Control Register */
	volatile uint32_t	DCDCLNVCTRL;	/* DCDC	Low Noise Voltage Register */
	
	uint32_t			RESERVED2[1U];
	volatile uint32_t	DCDCLPVCTRL;	/* DCDC	Low Power Voltage Register */

	uint32_t			RESERVED3[1U];
	volatile uint32_t	DCDCLPCTRL;		/* DCDC	Low Power Control Register */
	volatile uint32_t	DCDCLNFREQCTRL;	/* DCDC	Low Noise Controller Frequency Control */

	uint32_t			RESERVED4[1U];
	volatile uint32_t	DCDCSYNC;		/* DCDC	Read Status Register */
	
	uint32_t			RESERVED5[5U];
	volatile uint32_t	VMONAVDDCTRL;	/* VMON AVDD Channel Control */
	volatile uint32_t	VMONALTAVDDCTRL;/* Alternate VMON AVDD Channel Control */
	volatile uint32_t	VMONDVDDCTRL;	/* VMON DVDD Channel Control */
	volatile uint32_t	VMONIO0CTRL;	/* VMON IOVDD0 Channel Control */
	
	uint32_t			RESERVED6[5U];
	volatile uint32_t	RAM1CTRL;		/* Memory Control Register */
	volatile uint32_t	RAM2CTRL;		/* Memory Control Register */
	
	uint32_t			RESERVED7[12U];
	volatile uint32_t	DCDCLPEM01CFG;	/* Configuration Bits for Low Power Mode */
	
	uint32_t			RESERVED8[4U];
	volatile uint32_t	EM23PERMORETAINCMD;		/* Clears Corresponding Bits in EM23PERNORETAINSTATUS Unlocking Access to Peripheral  */
	volatile uint32_t	EM23PERNORETAINSTATUS;	/* Status Indicating If Peripherals Were Powered Down in EM23, Subse  */
	volatile uint32_t	EM23PERNORETAINCTRL;	/* When Set Corresponding Peripherals May Get Powered Down in EM23 */

}	EMU_TypeDef;

#define EMU ((EMU_TypeDef *) EMU_BASE)

#define EMU_DCDCCTRL_DCDCMODE_LOWNOISE	1UL

// PWRCFG
#define EMU_PWRCFG_UNCONFIGURED	0UL
#define EMU_PWRCFG_DCDCTODVDD	2UL

#endif
