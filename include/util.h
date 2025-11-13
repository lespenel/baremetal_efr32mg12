#ifndef UTIL_H
# define UTIL_H

#include <stddef.h>
#include <stdint.h>

size_t	bm_strlen(char *str);
void	*memset(void *s, int c, size_t n);

void	bm_itoa(char buff[], int size, uint32_t nb);
void	bm_regtoa(char buff[], int size, uint32_t reg);

#endif
