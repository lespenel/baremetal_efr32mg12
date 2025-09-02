#ifndef USART_H
# define USART_H

#include <stdint.h>

#define USART0_BASE (0x40010000UL)
#define USART1_BASE (0x40010400UL)
#define USART2_BASE (0x40010800UL)
#define USART3_BASE (0x40010C00UL)

// Universal Synchronous Asynchronous Receiver/Transmitte (p.549)
typedef struct
{
	volatile uint32_t	CTRL;			/* Control Register */
	volatile uint32_t	FRAME;			/* USART Frame Format Register */
	volatile uint32_t	TRIGCTRL;		/* USART Trigger Control Register */
	volatile uint32_t	CMD;			/* Command Register */
	volatile uint32_t	STATUS;			/* USART Status Register */
	volatile uint32_t	CLKDIV;			/* Clock Control Register */
	volatile uint32_t	RXDATAX;		/* RX Buffer Data Extended Register */
	volatile uint32_t	RXDATA;			/* RX Buffer Data Register */
	volatile uint32_t	RXDOUBLEX;		/* RX Buffer Double Data Extended Register */
	volatile uint32_t	RXDOUBLE;		/* RX FIFO Double Data Register */
	volatile uint32_t	RXDATAXP;		/* RX Buffer Data Extended Peek Register */
	volatile uint32_t	RXDOUBLEXP;		/* RX Buffer Double Data Extended Peek Register */
	volatile uint32_t	TXDATAX;		/* TX Buffer Data Extended Register */
	volatile uint32_t	TXDATA;			/* TX Buffer Data Register */
	volatile uint32_t	TXDOUBLEX;		/* TX Buffer Double Data Extended Register */
	volatile uint32_t	TXDOUBLE;		/* TX Buffer Double Data Register */
	volatile uint32_t	IF;				/* Interrupt Flag Register */
	volatile uint32_t	IFS;			/* Interrupt Flag Set Register */
	volatile uint32_t	IFC;			/* Interrupt Flag Clear Register */
	volatile uint32_t	IEN;			/* Interrupt Enable Register */
	volatile uint32_t	IRCTRL;			/* IrDA Control Register */
	uint32_t			RESERVED0[1U];
	volatile uint32_t	INPUT;			/* USART Input Register */
	volatile uint32_t	I2SCTRL;		/* I2S Control Register */
	volatile uint32_t	TIMING;			/* Timing Register */
	volatile uint32_t	CTRLX;			/* Control Register Extended */
	volatile uint32_t	TIMECMP0;		/* To Generate Interrupts and Various Delays */
	volatile uint32_t	TIMECMP1;		/* To Generate Interrupts and Various Delays */
	volatile uint32_t	TIMECMP2;		/* To Generate Interrupts and Various Delays */
	volatile uint32_t	ROUTEPEN;		/* I/O Routing Pin Enable Register */
	volatile uint32_t	ROUTELOC0;		/* I/O Routing Location Register */
	volatile uint32_t	ROUTELOC1;		/* I/O Routing Location Register */
	
}	USART_TypeDef;

#define USART0 ((USART_TypeDef *) USART0_BASE)
#define USART1 ((USART_TypeDef *) USART1_BASE)
#define USART2 ((USART_TypeDef *) USART2_BASE)
#define USART3 ((USART_TypeDef *) USART3_BASE)

//CTRL
#define USART_CTRL_SYNC			(1UL << 0)
#define USART_CTRL_LOOPBK		(1UL << 1)
#define USART_CTRL_TXINV		(1UL << 14)

#define USART_CTRL_MSBF_SHIFT		10
#define USART_CTRL_MSBF_LSB_FIRST	0UL
#define USART_CTRL_MSBF_MSB_FIRST	1UL

//STATUS
#define USART_STATUS_TXENS			(1UL << 1)
#define USART_STATUS_MASTER			(1UL << 2)
#define USART_STATUS_RXBLOCK		(1UL << 3)
#define USART_STATUS_TXTRI			(1UL << 4)
#define USART_STATUS_TXC			(1UL << 5)
#define USART_STATUS_TXBL			(1UL << 6)
#define USART_STATUS_RXDATAV		(1UL << 7)
#define USART_STATUS_RXFULL			(1UL << 8)
#define USART_STATUS_TXBDRIGHT		(1UL << 9)
#define USART_STATUS_TXBSRIGHT		(1UL << 10)
#define USART_STATUS_RXDATAVRIGHT	(1UL << 11)
#define USART_STATUS_RXFULLRIGHT	(1UL << 12)
#define USART_STATUS_TXIDLE			(1UL << 13)
#define USART_STATUS_TIMERRESTARTED	(1UL << 14)


//FRAME DATABIS
#define USART_FRAME_DATABITS_SHIFT		0
#define USART_FRAME_DATABITS_FOUR		1UL
#define USART_FRAME_DATABITS_FIVE		2UL
#define USART_FRAME_DATABITS_SIX		3UL
#define USART_FRAME_DATABITS_SEVEN		4UL
#define USART_FRAME_DATABITS_EIGHT		5UL
#define USART_FRAME_DATABITS_NINE		6UL
#define USART_FRAME_DATABITS_TEN		7UL
#define USART_FRAME_DATABITS_ELEVEN		8UL
#define USART_FRAME_DATABITS_TWELVE		9UL
#define USART_FRAME_DATABITS_THIRTEEN	10UL
#define USART_FRAME_DATABITS_FOURTEEN	11UL
#define USART_FRAME_DATABITS_FIFTEEN	12UL
#define USART_FRAME_DATABITS_SIXTEEN	13UL


//FRAME STOPBITS
#define USART_FRAME_STOPBITS_HALF			(0UL << 12)
#define USART_FRAME_STOPBITS_ONE			(1UL << 12)
#define USART_FRAME_STOPBITS_ONEANDHALF		(2UL << 12)
#define USART_FRAME_STOPBITS_TWO			(3UL << 12)


//CMD
#define USART_CMD_RXEN	(1 << 0)
#define USART_CMD_RXDIS (1 << 1)
#define USART_CMD_TXEN	(1 << 2)
#define USART_CMD_TXDIS (1 << 3)

//IF
#define USART_IF_TXC		(1 << 0)
#define USART_IF_TXBL		(1 << 1)
#define USART_IF_RXDATAV	(1 << 2)
#define USART_IF_RXFULL		(1 << 3)
#define USART_IF_RXOF		(1 << 4)
#define USART_IF_RXUF		(1 << 5)
#define USART_IF_TXOF		(1 << 6)
#define USART_IF_TXUF		(1 << 7)
#define USART_IF_PERR		(1 << 8)
#define USART_IF_FERR		(1 << 9)
#define USART_IF_MPAF		(1 << 10)
#define USART_IF_SSM		(1 << 11)
#define USART_IF_CCF		(1 << 12)
#define USART_IF_TXIDLE		(1 << 13)
#define USART_IF_TCMP0		(1 << 14)
#define USART_IF_TCMP1		(1 << 15)
#define USART_IF_TCMP2		(1 << 16)

//ROUTEPEN
#define USART_ROUTEPEN_RXPEN_SHIFT	0
#define USART_ROUTEPEN_TXPEN_SHIFT	1
#define USART_ROUTEPEN_CSPEN_SHIFT	2
#define USART_ROUTEPEN_CLKPEN_SHIFT 3
#define USART_ROUTEPEN_CTSPEN_SHIFT 4
#define USART_ROUTEPEN_RTSPEN_SHIFT 5

#define USART_ROUTEPEN_RXPEN   (1 << USART_ROUTEPEN_RXPEN_SHIFT)
#define USART_ROUTEPEN_TXPEN   (1 << USART_ROUTEPEN_TXPEN_SHIFT)
#define USART_ROUTEPEN_CSPEN   (1 << USART_ROUTEPEN_CSPEN_SHIFT)
#define USART_ROUTEPEN_CLKPEN  (1 << USART_ROUTEPEN_CLKPEN_SHIFT)
#define USART_ROUTEPEN_CTSPEN  (1 << USART_ROUTEPEN_CTSPEN_SHIFT)
#define USART_ROUTEPEN_RTSPEN  (1 << USART_ROUTEPEN_RTSPEN_SHIFT)

#endif
