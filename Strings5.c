#include "shell.h"
/**
 **_StrNConcatinate - concatenates two strings
 *@destination: the first string
 *@source: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_StrNConcatinate(char *destination, char *source, int n)
{
    int i, j;
    char *s = destination;

    i = 0;
    j = 0;
    while (destination[i] != '\0')
        i++;
    while (source[j] != '\0' && j < n)
    {
        destination[i] = source[j];
        i++;
        j++;
    }
    if (j < n)
        destination[i] = '\0';
    return (s);
}

/**
 **_LocateChar - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_LocateChar(char *s, char c)
{
    do
    {
        if (*s == c)
            return (s);
    } while (*s++ != '\0');

    return (NULL);
}
