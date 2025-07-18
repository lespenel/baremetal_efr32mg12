#include <stdint.h>

#define EXT_IRQ_COUNT	51
#define TOTAL_INTERUPTS	(16 + EXT_IRQ_COUNT)

#define __STACK_SIZE    0x00000400
#define __HEAP_SIZE		0x00000C00

#define RAM_START		0x20000000
#define RAM_LENGTH		262144
#define RAM_END		((RAM_START) + (RAM_LENGTH))

#define STACK_START RAM_END

void Reset_Handler(void);
void Default_Handler(void);

/* Cortex-M Processor Exceptions */
void NMI_Handler(void)               __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void)         __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void)        __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler(void)          __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void)               __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void)           __attribute__ ((weak, alias("Default_Handler")));
void sl_app_properties(void)         __attribute__ ((weak, alias("Default_Handler")));

/* Part Specific Interrupts */

void EMU_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void FRC_PRI_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void WDOG0_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void WDOG1_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void FRC_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void MODEM_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void RAC_SEQ_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void RAC_RSM_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void BUFC_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void LDMA_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void GPIO_EVEN_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void TIMER0_IRQHandler(void)         __attribute__ ((weak, alias("Default_Handler")));
void USART0_RX_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void USART0_TX_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void ACMP0_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void ADC0_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void IDAC0_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void I2C0_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void GPIO_ODD_IRQHandler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIMER1_IRQHandler(void)         __attribute__ ((weak, alias("Default_Handler")));
void USART1_RX_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void USART1_TX_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void LEUART0_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void PCNT0_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void CMU_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void MSC_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void CRYPTO0_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void LETIMER0_IRQHandler(void)       __attribute__ ((weak, alias("Default_Handler")));
void AGC_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void PROTIMER_IRQHandler(void)       __attribute__ ((weak, alias("Default_Handler")));
void RTCC_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void SYNTH_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void CRYOTIMER_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void RFSENSE_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void FPUEH_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void SMU_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void WTIMER0_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void WTIMER1_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void PCNT1_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void PCNT2_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void USART2_RX_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void USART2_TX_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void USART3_RX_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void USART3_TX_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void VDAC0_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void CSEN_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void LESENSE_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void CRYPTO1_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void TRNG0_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));

// Vector table
// __attribute__ specify a specific section instead of .data
uint32_t vectors[] __attribute__ ((section(".isr_vector")))= {
	STACK_START,						/* Initial Stack Pointer */
	(uint32_t) &Reset_Handler,			/* Reset Handler */
	(uint32_t) &NMI_Handler,			/* NMI Handler */
	(uint32_t) &HardFault_Handler,		/* Hard Fault Handler */

	(uint32_t) &MemManage_Handler,		/* MPU Fault Handler */
	(uint32_t) &BusFault_Handler,		/* Bus Fault Handler */
	(uint32_t) &UsageFault_Handler,		/* Usage Fault Handler */

	(uint32_t) &Default_Handler,		/* Reserved */
	(uint32_t) &Default_Handler,		/* Reserved */
	(uint32_t) &Default_Handler,		/* Reserved */
	(uint32_t) &Default_Handler,		/* Reserved */

	(uint32_t) &SVC_Handler,			/* SVCall Handler */
	(uint32_t) &DebugMon_Handler,		/* Debug Monitor Handler */

	(uint32_t) &sl_app_properties,		/* Application properties*/
	(uint32_t) &PendSV_Handler,			/* PendSV Handler */
	(uint32_t) &SysTick_Handler,		/* SysTick Handler */

	(uint32_t) &EMU_IRQHandler,			/* 0 */
	(uint32_t) &FRC_PRI_IRQHandler,		/* 1 */
	(uint32_t) &WDOG0_IRQHandler,		/* 2 */
	(uint32_t) &WDOG1_IRQHandler,		/* 3 */
	(uint32_t) &FRC_IRQHandler,			/* 4 */
	(uint32_t) &MODEM_IRQHandler,		/* 5 */
	(uint32_t) &RAC_SEQ_IRQHandler,		/* 6 */
	(uint32_t) &RAC_RSM_IRQHandler,		/* 7 */
	(uint32_t) &BUFC_IRQHandler,		/* 8 */
	(uint32_t) &LDMA_IRQHandler,		/* 9 */
	(uint32_t) &GPIO_EVEN_IRQHandler,	/* 10 */
	(uint32_t) &TIMER0_IRQHandler,		/* 11 */
	(uint32_t) &USART0_RX_IRQHandler,	/* 12 */
	(uint32_t) &USART0_TX_IRQHandler,	/* 13 */
	(uint32_t) &ACMP0_IRQHandler,		/* 14 */
	(uint32_t) &ADC0_IRQHandler,		/* 15 */
	(uint32_t) &IDAC0_IRQHandler,		/* 16 */
	(uint32_t) &I2C0_IRQHandler,		/* 17 */
	(uint32_t) &GPIO_ODD_IRQHandler,	/* 18 */
	(uint32_t) &TIMER1_IRQHandler,		/* 19 */
	(uint32_t) &USART1_RX_IRQHandler,	/* 20 */
	(uint32_t) &USART1_TX_IRQHandler,	/* 21 */
	(uint32_t) &LEUART0_IRQHandler,		/* 22 */
	(uint32_t) &PCNT0_IRQHandler,		/* 23 */
	(uint32_t) &CMU_IRQHandler,			/* 24 */
	(uint32_t) &MSC_IRQHandler,			/* 25 */
	(uint32_t) &CRYPTO0_IRQHandler,		/* 26 */
	(uint32_t) &LETIMER0_IRQHandler,	/* 27 */
	(uint32_t) &AGC_IRQHandler,			/* 28 */
	(uint32_t) &PROTIMER_IRQHandler,	/* 29 */
	(uint32_t) &RTCC_IRQHandler,		/* 30 */
	(uint32_t) &SYNTH_IRQHandler,		/* 31 */
	(uint32_t) &CRYOTIMER_IRQHandler,	/* 32 */
	(uint32_t) &RFSENSE_IRQHandler,		/* 33 */
	(uint32_t) &FPUEH_IRQHandler,		/* 34 */
	(uint32_t) &SMU_IRQHandler,			/* 35 */
	(uint32_t) &WTIMER0_IRQHandler,		/* 36 */
	(uint32_t) &WTIMER1_IRQHandler,		/* 37 */
	(uint32_t) &PCNT1_IRQHandler,		/* 38 */
	(uint32_t) &PCNT2_IRQHandler,		/* 39 */
	(uint32_t) &USART2_RX_IRQHandler,	/* 40 */
	(uint32_t) &USART2_TX_IRQHandler,	/* 41 */
	(uint32_t) &I2C1_IRQHandler,		/* 42 */
	(uint32_t) &USART3_RX_IRQHandler,	/* 43 */
	(uint32_t) &USART3_TX_IRQHandler,	/* 44 */
	(uint32_t) &VDAC0_IRQHandler,		/* 45 */
	(uint32_t) &CSEN_IRQHandler,		/* 46 */
	(uint32_t) &LESENSE_IRQHandler,		/* 47 */
	(uint32_t) &CRYPTO1_IRQHandler,		/* 48 */
	(uint32_t) &TRNG0_IRQHandler,		/* 49 */
	(uint32_t) &Default_Handler,		/* 50 - Reserved */
};

void Copy_Table(void);
void Zero_Table(void);

extern int main(void);

void Reset_Handler(void)
{
	//	SystemInit();   /* CMSIS System Initialization */
		Copy_Table();	/* clear .data */
		Zero_Table();	/* clear .bss */
	//	__libc_init_array();
		main();

		while (1);
}

void Default_Handler(void) {
	while (1);
}

extern uint32_t	_la_data;
extern uint32_t	_sdata;
extern uint32_t	_edata;

extern uint32_t _etext;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Copy_Table(void)
{
	uint32_t	*src = &_etext;
	uint32_t	*dst = &_sdata;

	while (dst < &_edata)
	{
		*dst = *src;
		dst++;
		src++;
	}
}

void Zero_Table(void)
{
	uint32_t	*dst = &_sbss;

	while (dst < &_ebss)
	{
		*dst = 0;
		dst++;
	}
}
