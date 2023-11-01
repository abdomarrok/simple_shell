#include "shell.h"

/**
 *_PutsErr - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _PutsErr(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_PutCharsErr(str[i]);
		i++;
	}
}

/**
 * _PutCharsErr - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _PutCharsErr(char c)
{
	static int i;
	static char buf[W_Buffer_Size];

	if (c == -1 || i >= W_Buffer_Size)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}
