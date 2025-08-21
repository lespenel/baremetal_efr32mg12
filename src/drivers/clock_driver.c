#include "cmu.h"

/**
 * @brief Start the HFX oscillator and wait until it is ready
 */
void	init_hfxo(void)
{
	// Enable HFXCLK
	CMU->OSCENCMD = CMU_OSCENCMD_HFXOEN;

	while ((CMU->STATUS & CMU_STATUS_HFXORDY) == 0)
	{
		__asm__("nop");
	}
}

/**
 * @brief Start the LFX oscillator and wait until it is ready
 */
void	init_lfxo(void)
{
	// Enable LFXCLK
	CMU->OSCENCMD = CMU_OSCENCMD_LFXOEN;

	while ((CMU->STATUS & CMU_STATUS_LFXORDY) == 0)
	{
		__asm__("nop");
	}
}

/**
 * @brief Calibrate the HFXO using LFXO as reference
 * @note the LFXO must be enabled and running before calling this function
 * @param HFCycles 
 * @return The number of ticks counted by the HFXO during calibration
 */
uint32_t	calibrate_hfxo(uint32_t HFCycles)
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
