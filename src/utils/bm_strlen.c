#include <stddef.h>

/**
 * @brief Return the len of a given string
 *
 * @return Length of the string
 */
size_t	bm_strlen(const char *str)
{
	size_t	len = 0;

	while (str[len] != '\0')
		++len;
	return (len);
}
