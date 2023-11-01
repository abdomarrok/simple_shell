#include "shell.h"
/**
 * _cd - changes the current directory of the process
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _cd(Passed_Info_t *Pinfo)
{
	char *s, *dirctory, buffer[1024];
	int chdirctory_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!Pinfo->argv[1])
	{
		dirctory = _Get_Env(Pinfo, "HOME=");
		if (!dirctory)
			chdirctory_ret = chdir((dirctory = _Get_Env(Pinfo, "PWD=")) ? dirctory : "/");
		else
			chdirctory_ret = chdir(dirctory);
	}
	else if (_StrCompare(Pinfo->argv[1], "-") == 0)
	{
		if (!_Get_Env(Pinfo, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_Get_Env(Pinfo, "OLDPWD=")), _putchar('\n');
		chdirctory_ret = chdir((dirctory = _Get_Env(Pinfo, "OLDPWD=")) ? dirctory : "/");
	}
	else
		chdirctory_ret = chdir(Pinfo->argv[1]);
	if (chdirctory_ret == -1)
	{
		PrintErr(Pinfo, "can't cd to ");
		_PutsErr(Pinfo->argv[1]), _PutCharsErr('\n');
	}
	else
	{
		_Set_Or_Edit_Env(Pinfo, "OLDPWD", _Get_Env(Pinfo, "PWD="));
		_Set_Or_Edit_Env(Pinfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}