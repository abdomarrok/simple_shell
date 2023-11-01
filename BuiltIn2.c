#include "shell.h"

/**
 * _History - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _History(Passed_Info_t *Pinfo)
{
    Print_List(Pinfo->history);
    return (0);
}

/**
 * unset_alias - sets alias to string
 * @Pinfo: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(Passed_Info_t *Pinfo, char *str)
{
    char *p, c;
    int ret;

    p = _LocateChar(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = SupprimeNodeAt(&(Pinfo->alias),
                         getNodeIndexAt(Pinfo->alias, getNodeStartWith(Pinfo->alias, str, -1)));
    *p = c;
    return (ret);
}
