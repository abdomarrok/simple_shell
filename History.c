#include "shell.h"

/**
 * Get_Hist_File - gets the history file
 * @Pinfo: parameter struct
 *
 * Return: allocated string containg history file
 */

char *Get_Hist_File(Passed_Info_t *Pinfo)
{
	char *Buffer, *dirctory;

	dirctory = _Get_Env(Pinfo, "HOME=");
	if (!dirctory)
		return (NULL);
	Buffer = malloc(sizeof(char) * (_StrLen(dirctory) + _StrLen(History_File) + 2));
	if (!Buffer)
		return (NULL);
	Buffer[0] = 0;
	_StrCopy(Buffer, dirctory);
	_StrConcatinate(Buffer, "/");
	_StrConcatinate(Buffer, History_File);
	return (Buffer);
}

/**
 * Set_Hist_File - creates a file, or appends to an existing file
 * @Pinfo: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int Set_Hist_File(Passed_Info_t *Pinfo)
{
	ssize_t fileD;
	char *filename = Get_Hist_File(Pinfo);
	MyListString *node = NULL;

	if (!filename)
		return (-1);

	fileD = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fileD == -1)
		return (-1);
	for (node = Pinfo->history; node; node = node->next)
	{
		_PutsFileDescriptorSring(node->string, fileD);
		_PutFileDescriptor('\n', fileD);
	}
	_PutFileDescriptor(-1, fileD);
	close(fileD);
	return (1);
}

/**
 * Get_Hist_file - reads history from file
 * @Pinfo: the parameter struct
 *
 * Return: History_File_count on success, 0 otherwise
 */
int Get_Hist_file(Passed_Info_t *Pinfo)
{
	int i, last = 0, linecount = 0;
	ssize_t fileD, rdlen, fsize = 0;
	struct stat st;
	char *Buffer = NULL, *filename = Get_Hist_File(Pinfo);

	if (!filename)
		return (0);

	fileD = open(filename, O_RDONLY);
	free(filename);
	if (fileD == -1)
		return (0);
	if (!fstat(fileD, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	Buffer = malloc(sizeof(char) * (fsize + 1));
	if (!Buffer)
		return (0);
	rdlen = read(fileD, Buffer, fsize);
	Buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(Buffer), 0);
	close(fileD);
	for (i = 0; i < fsize; i++)
		if (Buffer[i] == '\n')
		{
			Buffer[i] = 0;
			Add_Hist_File_List(Pinfo, Buffer + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		Add_Hist_File_List(Pinfo, Buffer + last, linecount++);
	free(Buffer);
	Pinfo->History_File_count = linecount;
	while (Pinfo->History_File_count-- >= History_Max)
		SupprimeNodeAt(&(Pinfo->history), 0);
	Edit_Hist_Num(Pinfo);
	return (Pinfo->History_File_count);
}

/**
 * Add_Hist_File_List - adds entry to a history linked list
 * @Pinfo: Structure containing potential arguments. Used to maintain
 * @Buffer: buffer
 * @linecount: the history linecount, History_File_count
 *
 * Return: Always 0
 */
int Add_Hist_File_List(Passed_Info_t *Pinfo, char *Buffer, int linecount)
{
	MyListString *node = NULL;

	if (Pinfo->history)
		node = Pinfo->history;
	ajouterNode_end(&node, Buffer, linecount);

	if (!Pinfo->history)
		Pinfo->history = node;
	return (0);
}

/**
 * Edit_Hist_Num - renumbers the history linked list after changes
 * @Pinfo: Structure containing potential arguments. Used to maintain
 *
 * Return: the new History_File_count
 */
int Edit_Hist_Num(Passed_Info_t *Pinfo)
{
	MyListString *node = Pinfo->history;
	int i = 0;

	while (node)
	{
		node->number = i++;
		node = node->next;
	}
	return (Pinfo->History_File_count = i);
}
