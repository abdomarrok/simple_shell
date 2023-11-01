#include "shell.h"

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	Passed_Info_t info[] = {Info_Initialization};
	int fileD = 2;

	/*asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fileD)
		: "r"(fileD));*/
		fileD += 3;

	if (argc == 2)
	{
		fileD = open(argv[1], O_RDONLY);
		if (fileD == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_PutsErr(argv[0]);
				_PutsErr(": 0: Can't open ");
				_PutsErr(argv[1]);
				_PutCharsErr('\n');
				_PutCharsErr(-1);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->ReadFileInput = fileD;
	}
	Populate_Envs(info);
	Get_Hist_file(info);
	main_shell_loop(info, argv);
	return (EXIT_SUCCESS);
}
