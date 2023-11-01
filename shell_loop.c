#include "shell.h"

/**
 * Find_Command - finds a command in PATH
 * @Pinfo: the parameter & return Pinfo struct
 *
 * Return: void
 */
void Find_Command(Passed_Info_t *Pinfo)
{
	char *path = NULL;
	int i, k;

	Pinfo->path = Pinfo->argv[0];
	if (Pinfo->LineCount_Flag == 1)
	{
		Pinfo->Line_Count++;
		Pinfo->LineCount_Flag = 0;
	}
	for (i = 0, k = 0; Pinfo->arg[i]; i++)
		if (!Is_Delim(Pinfo->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = Find_Command_Path(Pinfo, _Get_Env(Pinfo, "PATH="), Pinfo->argv[0]);
	if (path)
	{
		Pinfo->path = path;
		Fork_Command(Pinfo);
	}
	else
if ((Is_InterActiveMode(Pinfo) || _Get_Env(Pinfo, "PATH=") || Pinfo->argv[0][0] == '/') &&
Is_Command(Pinfo, Pinfo->argv[0])) {
Fork_Command(Pinfo);
} 
else 
if (*(Pinfo->arg) != '\n') 
{
Pinfo->status = 127;
PrintErr(Pinfo, "not found\n");
}
}

/**
 * Fork_Command - forks a an exec thread to run cmd
 * @Pinfo: the parameter & return Pinfo struct
 *
 * Return: void
 */
void Fork_Command(Passed_Info_t *Pinfo)
{
	pid_t c_pid;

	c_pid = fork();
	if (c_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (c_pid == 0)
	{
		if (execve(Pinfo->path, Pinfo->argv, Get_Environ(Pinfo)) == -1)
		{
			Free_Passed_info(Pinfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		}
	else
	{
		wait(&(Pinfo->status));
		if (WIFEXITED(Pinfo->status))
		{
			Pinfo->status = WEXITSTATUS(Pinfo->status);
			if (Pinfo->status == 126)
				PrintErr(Pinfo, "Permission denied\n");
		}
	}
}
