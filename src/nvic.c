#include "nvic.h"

void	NVIC_interupt_set_enable(uint32_t to_enable)
{
	if (to_enable < 32)
		NVIC->ISER[0] |= (1UL << (to_enable % 32));
	else if (to_enable < 64)
		NVIC->ISER[1] |= (1UL << (to_enable % 32));
	// Iser range from [0] to [7], but the last irq is 49
}
