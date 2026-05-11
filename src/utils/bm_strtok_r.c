#include "util.h"

char	*bm_strtok_r(char *str, const char *delim, char **saveptr)
{
	size_t	i;

	if (str == NULL)
		str = *saveptr;
	if (str == NULL)
		return (NULL);
	while (*str && bm_strchr(delim, *str))
		++str;
	i = 0;
	while (str[i] && bm_strchr(delim, str[i]) == NULL)
		++i;
	if (*str == '\0')
	{
		*saveptr = NULL;
		return (NULL);
	}
	if (str[i])
	{
		str[i] = '\0';
		*saveptr = (str + i + 1);
	}
	else
		*saveptr = NULL;
	return (str);
}
