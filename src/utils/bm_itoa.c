#include "util.h"
#include <stdint.h>

void	bm_itoa(char buff[], int size, uint32_t nb)
{
	while (size)
	{
		--size;
		buff[size] = (nb % 10) + '0';
		nb = nb / 10;
	}
}
