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
		s++; /
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

/**
 * PrintErr - prints an error message
 * @Pinfo: the parameter & return Pinfo struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void PrintErr(Passed_Info_t *Pinfo, char *estr)
{
	_PutsErr(Pinfo->File_Name);
	_PutsErr(": ");
	PrintDecimal(Pinfo->Line_Count, STDERR_FILENO);
	_PutsErr(": ");
	_PutsErr(Pinfo->argv[0]);
	_PutsErr(": ");
	_PutsErr(estr);
}

/**
 * PrintDecimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int PrintDecimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _PutCharsErr;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * ConvertNum - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @Flags: argument Flags
 *
 * Return: string
 */
char *ConvertNum(long int num, int base, int Flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(Flags & ConvUnsigned) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = Flags & ConvLower ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * DeleteComment - function Changes first instance of '#' with '\0'
 * @Buffer: address of the string to modify
 *
 * Return: Always 0;
 */
void DeleteComment(char *Buffer)
{
	int i;

	for (i = 0; Buffer[i] != '\0'; i++)
		if (Buffer[i] == '#' && (!i || Buffer[i - 1] == ' '))
		{
			Buffer[i] = '\0';
			break;
		}
}
