#include "shell.h"

/**
 * Init_Info - initializes Passed_Info_t struct
 * @info: struct address
 */
void Init_Info(Passed_Info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * Set_info - initializes Passed_Info_t struct
 * @info: struct address
 * @av: argument vector
 */
void Set_info(Passed_Info_t *info, char **av)
{
	int i = 0;

	info->File_Name = av[0];
	if (info->arg)
	{
		info->argv = _strtok(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _StrDublicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		Change_alias(info);
		Change_vars(info);
	}
}

/**
 * Free_Passed_info - frees Passed_Info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void Free_Passed_info(Passed_Info_t *info, int all)
{
	FreeStrofStr(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->Command_Buffer)
			free(info->arg);
		if (info->env)
			FreeNodes(&(info->env));
		if (info->history)
			FreeNodes(&(info->history));
		if (info->alias)
			FreeNodes(&(info->alias));
		FreeStrofStr(info->environ);
		info->environ = NULL;
		FreesPointer((void **)info->Command_Buffer);
		if (info->ReadFileInput > 2)
			close(info->ReadFileInput);
		_putchar(-1);
	}
}
