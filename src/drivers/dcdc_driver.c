#include "emu.h"

/**
 * @brief Set the PWRCFG to DCDC and enable DCDC in lownoise mode
 */
void DCDCInit(void)
{
	// set DCDC to be the main alim (mandatory for high frequency)
	EMU->PWRCFG = EMU_PWRCFG_DCDCTODVDD;

	// set DCDC in lownoise mode (mandatory otherwise the DCDC is set in bypass)
	EMU->DCDCCTRL = EMU_DCDCCTRL_DCDCMODE_LOWNOISE;
}
