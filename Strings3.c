#include "shell.h"

/**
 * _StrCopy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *_StrCopy(char *destination, char *source)
{
    int i = 0;

    if (destination == source || source == 0)
        return (destination);
    while (source[i])
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = 0;
    return (destination);
}

/**
 * _StrDublicate - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_StrDublicate(const char *string)
{
    int length = 0;
    char *res;

    if (string == NULL)
        return (NULL);
    while (*string++)
        length++;
    res = malloc(sizeof(char) * (length + 1));
    if (!res)
        return (NULL);
    for (length++; length--;)
        res[length] = *--string;
    return (res);
}
