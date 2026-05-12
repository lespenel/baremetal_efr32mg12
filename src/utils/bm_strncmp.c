#include "stdint.h"

int bm_strncmp(char *s1, char *s2, uint32_t n)
{
	uint32_t i = 0;

	while (s1[i] && s1[i] != s2[i] && i < n - 1)
		++i;
	return (s1[i] - s2[i]);
}
