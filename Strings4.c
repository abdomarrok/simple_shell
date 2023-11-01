#include "shell.h"
/**
 *_puts - prints an input string
 *@string: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		_putchar(string[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char Buffer[W_Buffer_Size];

	if (c == -1 || i >= W_Buffer_Size)
	{
		write(1, Buffer, i);
		i = 0;
	}
	if (c != -1)
		Buffer[i++] = c;
	return (1);
}
