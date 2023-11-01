#include "shell.h"

/**
 * main_shell_loop - main shell loop
 * @Pinfo: the parameter & return Pinfo struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main_shell_loop(Passed_Info_t *Pinfo, char **av)
{
	ssize_t r = 0;
	int BuiltinR = 0;

	while (r != -1 && BuiltinR != -2)
	{
		Init_Info(Pinfo);
		if (Is_InterActiveMode(Pinfo))
			_puts("$ ");
		_PutCharsErr(-1);
		r = Get_in(Pinfo);
		if (r != -1)
		{
			Set_info(Pinfo, av);
			BuiltinR = Find_Built_In(Pinfo);
			if (BuiltinR == -1)
				Find_Command(Pinfo);
		}
		else if (Is_InterActiveMode(Pinfo))
			_putchar('\n');
		Free_Passed_info(Pinfo, 0);
	}
	Set_Hist_File(Pinfo);
	Free_Passed_info(Pinfo, 1);
	if (!Is_InterActiveMode(Pinfo) && Pinfo->status)
		exit(Pinfo->status);
	if (BuiltinR == -2)
	{
		if (Pinfo->Error_Number == -1)
			exit(Pinfo->status);
		exit(Pinfo->Error_Number);
	}
	return (BuiltinR);
}

/**
 * Find_Built_In - finds a builtin command
 * @Pinfo: the parameter & return Pinfo struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int Find_Built_In(Passed_Info_t *Pinfo)
{
	int i, BuiltinR = -1;
	Built_In_table builtintbl[] = {
		{"exit", builtin_exit},
		{"env", _env},
		{"help", _Help},
		{"history", _History},
		{"setenv", _Set_Env},
		{"unsetenv", RemoveEnvVar},
		{"cd", _cd},
		{"alias", _Alias},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
		if (_StrCompare(Pinfo->argv[0], builtintbl[i].type) == 0)
		{
			Pinfo->Line_Count++;
			BuiltinR = builtintbl[i].func(Pinfo);
			break;
		}
	return (BuiltinR);
}

/**
 * Find_Command - finds a command in PATH
 * @Pinfo: the parameter & return Pinfo struct
 *
 * Return: void
 */
void Find_Command(Passed_Info_t *Pinfo)
{
	char *path = NULL;
	int i, k;

	Pinfo->path = Pinfo->argv[0];
	if (Pinfo->LineCount_Flag == 1)
	{
		Pinfo->Line_Count++;
		Pinfo->LineCount_Flag = 0;
	}
	for (i = 0, k = 0; Pinfo->arg[i]; i++)
		if (!Is_Delim(Pinfo->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = Find_Command_Path(Pinfo, _Get_Env(Pinfo, "PATH="), Pinfo->argv[0]);
	if (path)
	{
		Pinfo->path = path;
		Fork_Command(Pinfo);
	}
	else
	{
		if ((Is_InterActiveMode(Pinfo) || _Get_Env(Pinfo, "PATH=") || Pinfo->argv[0][0] == '/') && Is_Command(Pinfo, Pinfo->argv[0]))
			Fork_Command(Pinfo);
		else if (*(Pinfo->arg) != '\n')
		{
			Pinfo->status = 127;
			PrintErr(Pinfo, "not found\n");
		}
	}
}

/**
 * Fork_Command - forks a an exec thread to run cmd
 * @Pinfo: the parameter & return Pinfo struct
 *
 * Return: void
 */
void Fork_Command(Passed_Info_t *Pinfo)
{
	pid_t c_pid;

	c_pid = fork();
	if (c_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (c_pid == 0)
	{
		if (execve(Pinfo->path, Pinfo->argv, Get_Environ(Pinfo)) == -1)
		{
			Free_Passed_info(Pinfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		
	}
	else
	{
		wait(&(Pinfo->status));
		if (WIFEXITED(Pinfo->status))
		{
			Pinfo->status = WEXITSTATUS(Pinfo->status);
			if (Pinfo->status == 126)
				PrintErr(Pinfo, "Permission denied\n");
		}
	}
}
