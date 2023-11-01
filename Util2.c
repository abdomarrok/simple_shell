#include "shell.h"

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
	unsigned long int n = num;

	if (!(Flags & ConvUnsigned) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = Flags & ConvLower ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do{
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
