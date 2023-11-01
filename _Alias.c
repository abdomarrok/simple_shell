#include "shell.h"
/**
 * _Alias - mimics the alias builtin (man alias)
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _Alias(Passed_Info_t *Pinfo)
{
	int i = 0;
	char *p = NULL;
	MyListString *node = NULL;

	if (Pinfo->argc == 1)
	{
		node = Pinfo->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; Pinfo->argv[i]; i++)
	{
		p = _LocateChar(Pinfo->argv[i], '=');
		if (p)
			set_alias(Pinfo, Pinfo->argv[i]);
		else
			print_alias(getNodeStartWith(Pinfo->alias, Pinfo->argv[i], '='));
	}

	return (0);
}
