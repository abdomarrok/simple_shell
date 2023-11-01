#include "shell.h"
/**
 * _PutFileDescriptor - writes the character c to given fileD
 * @ch: The character to print
 * @fileD: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _PutFileDescriptor(char ch, int fileD)
{
    static int i;
    static char Buffer[W_Buffer_Size];

    if (ch == -1 || i >= W_Buffer_Size)
    {
        write(fileD, Buffer, i);
        i = 0;
    }
    if (ch != -1)
        Buffer[i++] = ch;
    return (1);
}

/**
 *_PutsFileDescriptorSring - prints an input string
 * @string: the string to be printed
 * @fileD: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _PutsFileDescriptorSring(char *string, int fileD)
{
    int i = 0;

    if (!string)
        return (0);
    while (*string)
    {
        i += _PutFileDescriptor(*string++, fileD);
    }
    return (i);
}
