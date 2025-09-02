#include <stddef.h>

void *memset(void *s, int c, size_t n)
{
	while (n != 0)
	{
		--n;
		((unsigned char *)s)[n] = (unsigned char)c;
	}
	return (s);
}
