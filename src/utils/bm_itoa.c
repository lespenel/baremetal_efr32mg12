#include <stdint.h>

#include "util.h"

char *bm_itoa(char *buff, int size, int nb)
{
	int n = nb;
	int	pos = 0;

	if (size <= 0)
		return (NULL);

	if (n >= 0)
	{
		n = -n;
		pos = 1;
	}
	buff[size] = '\0';
	while (size)
	{
		--size;
		buff[size] = -(n % 10) + '0';
		if (n > -10)
			break ;
		n /= 10;
	}
	if (size && !pos)
		buff[--size] = '-';
	return (buff + size);
}
