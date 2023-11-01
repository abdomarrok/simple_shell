#include "shell.h"

/**
 * _env - prints the current environment
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _env(Passed_Info_t *Pinfo)
{
	PrintStrs(Pinfo->env);
	return (0);
}

/**
 * _Get_Env - gets the value of an environ variable
 * @Pinfo: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_Get_Env(Passed_Info_t *Pinfo, const char *name)
{
	MyListString *node = Pinfo->env;
	char *p;

	while (node)
	{
		p = StrStartWith(node->string, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _Set_Env - Initialize a new environment variable,
 *             or modify an existing one
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _Set_Env(Passed_Info_t *Pinfo)
{
	if (Pinfo->argc != 3)
	{
		_PutsErr("Incorrect number of arguements\n");
		return (1);
	}
	if (_Set_Or_Edit_Env(Pinfo, Pinfo->argv[1], Pinfo->argv[2]))
		return (0);
	return (1);
}
