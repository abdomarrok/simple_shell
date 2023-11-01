#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	Passed_Info_t info[] = {Info_Initialization};
	int fd = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_PutsErr(av[0]);
				_PutsErr(": 0: Can't open ");
				_PutsErr(av[1]);
				_PutCharsErr('\n');
				_PutCharsErr(-1);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->ReadFileInput = fd;
	}
	Populate_Envs(info);
	Get_Hist_file(info);
	main_shell_loop(info, av);
	return (EXIT_SUCCESS);
}
