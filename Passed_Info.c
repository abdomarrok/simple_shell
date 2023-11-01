#include "shell.h"

/**
 * Init_Info - initializes Passed_Info_t struct
 * @Pinfo: struct address
 */
void Init_Info(Passed_Info_t *Pinfo)
{
	Pinfo->arg = NULL;
	Pinfo->argv = NULL;
	Pinfo->path = NULL;
	Pinfo->argc = 0;
}

/**
 * Set_info - initializes Passed_Info_t struct
 * @Pinfo: struct address
 * @argv: argument vector
 */
void Set_info(Passed_Info_t *Pinfo, char **argv)
{
	int i = 0;

	Pinfo->File_Name = argv[0];
	if (Pinfo->arg)
	{
		Pinfo->argv = _strtok(Pinfo->arg, " \t");
		if (!Pinfo->argv)
		{

			Pinfo->argv = malloc(sizeof(char *) * 2);
			if (Pinfo->argv)
			{
				Pinfo->argv[0] = _StrDublicate(Pinfo->arg);
				Pinfo->argv[1] = NULL;
			}
		}
		for (i = 0; Pinfo->argv && Pinfo->argv[i]; i++)
			;
		Pinfo->argc = i;

		Change_alias(Pinfo);
		Change_vars(Pinfo);
	}
}

/**
 * Free_Passed_info - frees Passed_Info_t struct fields
 * @Pinfo: struct address
 * @all: true if freeing all fields
 */
void Free_Passed_info(Passed_Info_t *Pinfo, int all)
{
	FreeStrofStr(Pinfo->argv);
	Pinfo->argv = NULL;
	Pinfo->path = NULL;
	if (all)
	{
		if (!Pinfo->Command_Buffer)
			free(Pinfo->arg);
		if (Pinfo->env)
			FreeNodes(&(Pinfo->env));
		if (Pinfo->history)
			FreeNodes(&(Pinfo->history));
		if (Pinfo->alias)
			FreeNodes(&(Pinfo->alias));
		FreeStrofStr(Pinfo->environ);
		Pinfo->environ = NULL;
		FreesPointer((void **)Pinfo->Command_Buffer);
		if (Pinfo->ReadFileInput > 2)
			close(Pinfo->ReadFileInput);
		_putchar(-1);
	}
}
