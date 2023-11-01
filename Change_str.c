#include "shell.h"
/**
 * Change_vars - Changes vars in the tokenized string
 * @Pinfo: the parameter struct
 *
 * Return: 1 if Changed, 0 otherwise
 */
int Change_vars(Passed_Info_t *Pinfo)
{
    int i = 0;
    MyListString *node;

    for (i = 0; Pinfo->argv[i]; i++)
    {
        if (Pinfo->argv[i][0] != '$' || !Pinfo->argv[i][1])
            continue;

        if (!_StrCompare(Pinfo->argv[i], "$?"))
        {
            Change_string(&(Pinfo->argv[i]),
                          _StrDublicate(ConvertNum(Pinfo->status, 10, 0)));
            continue;
        }
        if (!_StrCompare(Pinfo->argv[i], "$$"))
        {
            Change_string(&(Pinfo->argv[i]),
                          _StrDublicate(ConvertNum(getpid(), 10, 0)));
            continue;
        }
        node = getNodeStartWith(Pinfo->env, &Pinfo->argv[i][1], '=');
        if (node)
        {
            Change_string(&(Pinfo->argv[i]),
                          _StrDublicate(_LocateChar(node->string, '=') + 1));
            continue;
        }
        Change_string(&Pinfo->argv[i], _StrDublicate(""));
    }
    return (0);
}

/**
 * Change_string - Changes string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if Changed, 0 otherwise
 */
int Change_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}
