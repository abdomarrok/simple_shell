#include "shell.h"

/**
 **_MemorySet - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_MemorySet(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * FreeStrofStr - frees a string of strings
 * @pointer: string of strings
 */
void FreeStrofStr(char **pointer)
{
	char **a = pointer;

	if (!pointer)
		return;
	while (*pointer)
		free(*pointer++);
	free(a);
}

/**
 * FreesPointer - frees a pointer and NULLs the address
 * @pointer: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int FreesPointer(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
