#ifndef CLOCK_DRIVER_H
# define CLOCK_DRIVER_H

#include <stdint.h>

void		init_hfxo(void);
uint32_t	calibrate_hfxo(uint32_t HFCycles);

void		init_lfxo(void);

#endif
