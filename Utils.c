#include "shell.h"

/**
 * Is_InterActiveMode - returns true if shell is Is_InterActiveMode mode
 * @Pinfo: struct address
 *
 * Return: 1 if Is_InterActiveMode mode, 0 otherwise
 */
int Is_InterActiveMode(Passed_Info_t *Pinfo)
{
	return (isatty(STDIN_FILENO) && Pinfo->ReadFileInput <= 2);
}

/**
 * Is_Delim - checks if character is a delimeter
 * @ch: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int Is_Delim(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 *Is_Alphabet - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int Is_Alphabet(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, Sign = 1, Flag = 0, OutPut;
	unsigned int res = 0;

	for (i = 0; s[i] != '\0' && Flag != 2; i++)
	{
		if (s[i] == '-')
			Sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			Flag = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (Flag == 1)
			Flag = 2;
	}

	if (Sign == -1)
		OutPut = -res;
	else
		OutPut = res;

	return (OutPut);
}

/**
 * Str_to_Int - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int Str_to_Int(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}
