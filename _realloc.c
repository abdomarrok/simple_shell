#include "shell.h"
/**
 * _realloc - reallocates a block of memory
 * @pointer: pointer to previous malloc'ated block
 * @old: byte size of previous block
 * @new: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *pointer, unsigned int old, unsigned int new)
{
	char *p;

	if (!pointer)
		return (malloc(new));
	if (!new)
		return (free(pointer), NULL);
	if (new == old)
		return (pointer);

	p = malloc(new);
	if (!p)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		p[old] = ((char *)pointer)[old];
	free(pointer);
	return (p);
}
