#include "util.h"

int bm_strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] && s1[i] != s2[i] && i < n - 1)
		++i;
	return (s1[i] - s2[i]);
}

char *bm_strstr(char *big, char *litle)
{
	size_t len = bm_strlen(litle);

	while (*big)
	{
		if (bm_strncmp(big, litle, len) == 0)
			return (big);
		++big;
	}
	return (0);
}

void	*memcpy(void *dest, const void *src, size_t n)
{
	while (n != 0)
	{
		--n;
		((unsigned char*)dest)[n] = ((unsigned char *)src)[n];
	}
	return (dest);
}
