#include "shell.h"

/**
 * ajouterNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @string: str field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
MyListString *ajouterNode(MyListString **head, const char *string, int number)
{
	MyListString *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(MyListString));
	if (!new_head)
		return (NULL);
	_MemorySet((void *)new_head, 0, sizeof(MyListString));
	new_head->number = number;
	if (string)
	{
		new_head->string = _StrDublicate(string);
		if (!new_head->string)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * ajouterNode_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @string: string field of node
 * @number: node index used by history
 *
 * Return: size of list
 */
MyListString *ajouterNode_end(MyListString **head, const char *string, int number)
{
	MyListString *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(MyListString));
	if (!new_node)
		return (NULL);
	_MemorySet((void *)new_node, 0, sizeof(MyListString));
	new_node->number = number;
	if (string)
	{
		new_node->string = _StrDublicate(string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * PrintStrs - prints only the string element of a MyListString linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t PrintStrs(const MyListString *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->string ? h->string : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * SupprimeNodeAt - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int SupprimeNodeAt(MyListString **head, unsigned int index)
{
	MyListString *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->string);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->string);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * FreeNodes - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void FreeNodes(MyListString **head_ptr)
{
	MyListString *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->string);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

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
