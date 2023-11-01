#include "shell.h"
/**
 * _PutFileDescriptor - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _PutFileDescriptor(char c, int fd)
{
    static int i;
    static char buf[W_Buffer_Size];

    if (c == -1 || i >= W_Buffer_Size)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != -1)
        buf[i++] = c;
    return (1);
}

/**
 *_PutsFileDescriptorSring - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _PutsFileDescriptorSring(char *str, int fd)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += _PutFileDescriptor(*str++, fd);
    }
    return (i);
}
