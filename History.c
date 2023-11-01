#include "shell.h"

/**
 * Get_Hist_File - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *Get_Hist_File(Passed_Info_t *info)
{
	char *buf, *dir;

	dir = _Get_Env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_StrLen(dir) + _StrLen(History_File) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_StrCopy(buf, dir);
	_StrConcatinate(buf, "/");
	_StrConcatinate(buf, History_File);
	return (buf);
}

/**
 * Set_Hist_File - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int Set_Hist_File(Passed_Info_t *info)
{
	ssize_t fd;
	char *filename = Get_Hist_File(info);
	MyListString *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_PutsFileDescriptorSring(node->string, fd);
		_PutFileDescriptor('\n', fd);
	}
	_PutFileDescriptor(-1, fd);
	close(fd);
	return (1);
}

/**
 * Get_Hist_file - reads history from file
 * @info: the parameter struct
 *
 * Return: History_File_count on success, 0 otherwise
 */
int Get_Hist_file(Passed_Info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = Get_Hist_File(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			Add_Hist_File_List(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		Add_Hist_File_List(info, buf + last, linecount++);
	free(buf);
	info->History_File_count = linecount;
	while (info->History_File_count-- >= History_Max)
		SupprimeNodeAt(&(info->history), 0);
	Edit_Hist_Num(info);
	return (info->History_File_count);
}

/**
 * Add_Hist_File_List - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, History_File_count
 *
 * Return: Always 0
 */
int Add_Hist_File_List(Passed_Info_t *info, char *buf, int linecount)
{
	MyListString *node = NULL;

	if (info->history)
		node = info->history;
	ajouterNode_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * Edit_Hist_Num - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new History_File_count
 */
int Edit_Hist_Num(Passed_Info_t *info)
{
	MyListString *node = info->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}
	return (info->History_File_count = i);
}
