#include "shell.h"

/**
 * main_shell_loop - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main_shell_loop(Passed_Info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		Init_Info(info);
		if (Is_InterActiveMode(info))
			_puts("$ ");
		_PutCharsErr(-1);
		r = Get_in(info);
		if (r != -1)
		{
			Set_info(info, av);
			builtin_ret = Find_Built_In(info);
			if (builtin_ret == -1)
				Find_Command(info);
		}
		else if (Is_InterActiveMode(info))
			_putchar('\n');
		Free_Passed_info(info, 0);
	}
	Set_Hist_File(info);
	Free_Passed_info(info, 1);
	if (!Is_InterActiveMode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->Error_Number == -1)
			exit(info->status);
		exit(info->Error_Number);
	}
	return (builtin_ret);
}

/**
 * Find_Built_In - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int Find_Built_In(Passed_Info_t *info)
{
	int i, built_in_ret = -1;
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
		if (_StrCompare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->Line_Count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * Find_Command - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void Find_Command(Passed_Info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->LineCount_Flag == 1)
	{
		info->Line_Count++;
		info->LineCount_Flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!Is_Delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = Find_Command_Path(info, _Get_Env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		Fork_Command(info);
	}
	else
	{
		if ((Is_InterActiveMode(info) || _Get_Env(info, "PATH=") || info->argv[0][0] == '/') && Is_Command(info, info->argv[0]))
			Fork_Command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			PrintErr(info, "not found\n");
		}
	}
}

/**
 * Fork_Command - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void Fork_Command(Passed_Info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, Get_Environ(info)) == -1)
		{
			Free_Passed_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				PrintErr(info, "Permission denied\n");
		}
	}
}
