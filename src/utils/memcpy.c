#include <stddef.h>

void	*memcpy(void *dest, const void *src, size_t n)
{
	while (n != 0)
	{
		--n;
		((unsigned char*)dest)[n] = ((unsigned char *)src)[n];
	}
	return (dest);
}
