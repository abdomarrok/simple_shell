#include "shell.h"

/**
 * Is_Chain - test if current char in buffer is a chain delimeter
 * @Pinfo: the parameter struct
 * @Buffer: the char Buffer
 * @p: address of current position in Buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int Is_Chain(Passed_Info_t *Pinfo, char *Buffer, size_t *p)
{
	size_t j = *p;

	if (Buffer[j] == '|' && Buffer[j + 1] == '|')
	{
		Buffer[j] = 0;
		j++;
		Pinfo->Command_Buffer_Type = Command_Or;
	}
	else if (Buffer[j] == '&' && Buffer[j + 1] == '&')
	{
		Buffer[j] = 0;
		j++;
		Pinfo->Command_Buffer_Type = Command_And;
	}
	else if (Buffer[j] == ';') /* found end of this command */
	{
		Buffer[j] = 0; /* Change semicolon with null */
		Pinfo->Command_Buffer_Type = Command_Chain;
	}
	else
		return (0);
	*p = j;
	return (1);
}
