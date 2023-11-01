#include "shell.h"

/**
 * Is_Command - determines if a file is an executable command
 * @Pinfo: the Pinfo struct
 * @command: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int Is_Command(Passed_Info_t *Pinfo, char *command)
{
	struct stat st;

	(void)Pinfo;
	if (!command || stat(command, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * DuplicateChars - duplicates characters
 * @commandstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *DuplicateChars(char *commandstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (commandstr[i] != ':')
			buf[k++] = commandstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * Find_Command_Path - finds this cmd in the PATH string
 * @Pinfo: the Pinfo struct
 * @commandstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *Find_Command_Path(Passed_Info_t *Pinfo, char *commandstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *command;

	if (!commandstr)
		return (NULL);
	if ((_StrLen(cmd) > 2) && StrStartWith(cmd, "./"))
	{
		if (Is_Command(Pinfo, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!commandstr[i] || commandstr[i] == ':')
		{
			command = DuplicateChars(commandstr, curr_pos, i);
			if (!*command)
				_StrConcatinate(command, cmd);
			else
			{
				_StrConcatinate(command, "/");
				_StrConcatinate(command, cmd);
			}
			if (Is_Command(Pinfo, command))
				return (command);
			if (!commandstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
