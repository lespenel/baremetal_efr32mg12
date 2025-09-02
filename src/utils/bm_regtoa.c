#include <stdint.h>

void	bm_regtoa(char buff[], int size, uint32_t reg)
{
	while (size)
	{
		--size;
		if (reg & (1UL << size))
			buff[size] = '1';
		else
			buff[size] = '0';
	}
}
