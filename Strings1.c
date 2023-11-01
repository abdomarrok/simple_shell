#include "shell.h"

/**
 * _StrLen - returns the length of a string
 * @string: the string whose length to check
 *
 * Return: integer length of string
 */
int _StrLen(char *string)
{
	int i = 0;

	if (!string)
		return (0);

	while (*string++)
		i++;
	return (i);
}

/**
 * _StrCompare - performs lexicogarphic comparison of two strangs.
 * @string1: the first strang
 * @string2: the second strang
 *
 * Return: negative if string1 < string2, positive if string1 > string2, zero if string1 == string2
 */
int _StrCompare(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string1 != *string2)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}
