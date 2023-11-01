#include "shell.h"
/**
 * Check_Hist_Chain - checks we should continue chaining based on last status
 * @Pinfo: the parameter struct
 * @Buffer: the char Buffer
 * @p: address of current position in Buffer
 * @i: starting position in Buffer
 * @length: length of Buffer
 *
 * Return: Void
 */
void Check_Hist_Chain(Passed_Info_t *Pinfo, char *Buffer, size_t *p,
size_t i, size_t length)
{
size_t j = *p;
if (Pinfo->Command_Buffer_Type == Command_And)
{
if (Pinfo->status)
{
Buffer[i] = 0;
j = length;
}
}
if (Pinfo->Command_Buffer_Type == Command_Or)
{
if (!Pinfo->status)
{
Buffer[i] = 0;
j = length;
}
}
*p = j;
}
