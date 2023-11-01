#include "shell.h"

/**
 * RemoveEnvVar - Remove an environment variable
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int RemoveEnvVar(Passed_Info_t *Pinfo)
{
	int i;

	if (Pinfo->argc == 1)
	{
		_PutsErr("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= Pinfo->argc; i++)
		RemoveEnvVarByName(Pinfo, Pinfo->argv[i]);

	return (0);
}

/**
 * Populate_Envs - populates env linked list
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int Populate_Envs(Passed_Info_t *Pinfo)
{
	MyListString *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		ajouterNode_end(&node, environ[i], 0);
	Pinfo->env = node;
	return (0);
}
/**
 * Get_Environ - returns the string array copy of our environ
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **Get_Environ(Passed_Info_t *Pinfo)
{
	if (!Pinfo->environ || Pinfo->Env_Status)
	{
		Pinfo->environ = List_to_Str(Pinfo->env);
		Pinfo->Env_Status = 0;
	}

	return (Pinfo->environ);
}

/**
 * RemoveEnvVarByName - Remove an environment variable
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @name: the string env var property
 */
int RemoveEnvVarByName(Passed_Info_t *Pinfo, char *name)
{
	MyListString *node = Pinfo->env;
	size_t i = 0;
	char *p;

	if (!node || !name)
		return (0);

	while (node)
	{
		p = StrStartWith(node->string, name);
		if (p && *p == '=')
		{
			Pinfo->Env_Status = SupprimeNodeAt(&(Pinfo->env), i);
			i = 0;
			node = Pinfo->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (Pinfo->Env_Status);
}

/**
 * _Set_Or_Edit_Env - Initialize a new environment variable,
 *             or modify an existing one
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @name: the string env name property
 * @value: the string env name value
 *  Return: Always 0
 */
int _Set_Or_Edit_Env(Passed_Info_t *Pinfo, char *name, char *value)
{
	char *Buffer = NULL;
	MyListString *node;
	char *p;

	if (!name || !value)
		return (0);

	Buffer = malloc(_StrLen(name) + _StrLen(value) + 2);
	if (!Buffer)
		return (1);
	_StrCopy(Buffer, name);
	_StrConcatinate(Buffer, "=");
	_StrConcatinate(Buffer, value);
	node = Pinfo->env;
	while (node)
	{
		p = StrStartWith(node->string, name);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = Buffer;
			Pinfo->Env_Status = 1;
			return (0);
		}
		node = node->next;
	}
	ajouterNode_end(&(Pinfo->env), Buffer, 0);
	free(Buffer);
	Pinfo->Env_Status = 1;
	return (0);
}
