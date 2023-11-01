#include "shell.h"
/**
 * StrStartWith - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *StrStartWith(const char *haystack, const char *needle)
{
    while (*needle)
        if (*needle++ != *haystack++)
            return (NULL);
    return ((char *)haystack);
}

/**
 * _StrConcatinate - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_StrConcatinate(char *destination, char *source)
{
    char *res = destination;

    while (*destination)
        destination++;
    while (*source)
        *destination++ = *source++;
    *destination = *source;
    return (res);
}
