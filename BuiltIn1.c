#include "shell.h"

/**
 * builtin_exit - exits the shell
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int builtin_exit(Passed_Info_t *Pinfo)
{
	int CheckExit;

	if (Pinfo->argv[1]) /* If there is an exit arguement */
	{
		CheckExit = Str_to_Int(Pinfo->argv[1]);
		if (CheckExit == -1)
		{
			Pinfo->status = 2;
			PrintErr(Pinfo, "Illegal number: ");
			_PutsErr(Pinfo->argv[1]);
			_PutCharsErr('\n');
			return (1);
		}
		Pinfo->Error_Number = Str_to_Int(Pinfo->argv[1]);
		return (-2);
	}
	Pinfo->Error_Number = -1;
	return (-2);
}

/**
 * _Help - changes the current directory of the process
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _Help(Passed_Info_t *Pinfo)
{
	char **arg_Arr;

	arg_Arr = Pinfo->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_Arr); 
	return (0);
}
