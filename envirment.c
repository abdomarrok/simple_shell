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
 * @var: the string env var property
 */
int RemoveEnvVarByName(Passed_Info_t *Pinfo, char *var)
{
	MyListString *node = Pinfo->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = StrStartWith(node->string, var);
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
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _Set_Or_Edit_Env(Passed_Info_t *Pinfo, char *var, char *value)
{
	char *buf = NULL;
	MyListString *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_StrLen(var) + _StrLen(value) + 2);
	if (!buf)
		return (1);
	_StrCopy(buf, var);
	_StrConcatinate(buf, "=");
	_StrConcatinate(buf, value);
	node = Pinfo->env;
	while (node)
	{
		p = StrStartWith(node->string, var);
		if (p && *p == '=')
		{
			free(node->string);
			node->string = buf;
			Pinfo->Env_Status = 1;
			return (0);
		}
		node = node->next;
	}
	ajouterNode_end(&(Pinfo->env), buf, 0);
	free(buf);
	Pinfo->Env_Status = 1;
	return (0);
}
