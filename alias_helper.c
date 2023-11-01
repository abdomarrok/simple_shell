#include "shell.h"
/**
 * set_alias - sets alias to string
 * @Pinfo: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(Passed_Info_t *Pinfo, char *string)
{
char *p;
p = _LocateChar(string, '=');
if (!p)
return (1);
if (!*++p)
return (Remove_alias(Pinfo, string));
Remove_alias(Pinfo, string);
return (ajouterNode_end(&(Pinfo->alias), string, 0) == NULL);
}
/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(MyListString *node)
{
char *p = NULL, *a = NULL;
if (node)
    {
p = _LocateChar(node->string, '=');
for (a = node->string; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
 * Change_alias - Changes an aliases in the tokenized string
 * @Pinfo: the parameter struct
 *
 * Return: 1 if Changed, 0 otherwise
 */
int Change_alias(Passed_Info_t *Pinfo)
{
    int i;
    MyListString *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = getNodeStartWith(Pinfo->alias, Pinfo->argv[0], '=');
        if (!node)
            return (0);
        free(Pinfo->argv[0]);
        p = _LocateChar(node->string, '=');
        if (!p)
            return (0);
        p = _StrDublicate(p + 1);
        if (!p)
            return (0);
        Pinfo->argv[0] = p;
    }
    return (1);
}

/**
 * Remove_alias - sets alias to string
 * @Pinfo: parameter struct
 * @string: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int Remove_alias(Passed_Info_t *Pinfo, char *string)
{
    char *p, c;
    int res;

    p = _LocateChar(string, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    res = SupprimeNodeAt(&(Pinfo->alias),
                         getNodeIndexAt(Pinfo->alias, getNodeStartWith(Pinfo->alias, string, -1)));
    *p = c;
    return (res);
}