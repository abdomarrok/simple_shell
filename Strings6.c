#include "shell.h"

/**
 **_StrNCopy - copies a string
 *@destination: the destination string to be copied to
 *@source: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_StrNCopy(char *destination, char *source, int n)
{
	int i, j;
	char *s = destination;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (s);
}
