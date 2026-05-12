#ifndef UTIL_H
# define UTIL_H

#include <stddef.h>
#include <stdint.h>

size_t	bm_strlen(const char *str);
void	*memset(void *s, int c, size_t n);

char	 *bm_itoa(char *buff, int size, int nb);
void	bm_regtoa(char buff[], int size, uint32_t reg);
char	*bm_strchr(const char *s, char c);
int		bm_strcmp(const char *s1, const char *s2);
int		bm_strncmp(char *s1, char *s2, uint32_t n);
char	*bm_strtok_r(char *str, const char *delim, char **saveptr);

#endif
