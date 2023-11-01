#include "shell.h"

/**
 * List_Length - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t List_Length(const MyListString *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * List_to_Str - returns an array of strings of the list->string
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **List_to_Str(MyListString *head)
{
	MyListString *node = head;
	size_t i = List_Length(head), j;
	char **strs;
	char *string;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		string = malloc(_StrLen(node->string) + 1);
		if (!string)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		string = _StrCopy(string, node->string);
		strs[i] = string;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * Print_List - prints all elements of a MyListString linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t Print_List(const MyListString *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(ConvertNum(h->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->string ? h->string : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * getNodeStartWith - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
MyListString *getNodeStartWith(MyListString *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = StrStartWith(node->string, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNodeIndexAt - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getNodeIndexAt(MyListString *head, MyListString *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
