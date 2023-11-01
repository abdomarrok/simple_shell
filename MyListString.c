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
MyListString *ajouterNode_end(MyListString **head,
const char *string, int number)
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
