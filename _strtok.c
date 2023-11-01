#include "shell.h"

/**
 * _strtok - splits a string into words. Repeat delimiters are ignored
 * @string: the input string
 * @delim: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **_strtok(char *string, char *delim)
{
	int i, j, k, m, WordNums = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; string[i] != '\0'; i++)
if (!Is_Delim(string[i], delim) &&
(Is_Delim(string[i + 1], delim) || !string[i + 1]))
			WordNums++;

	if (WordNums == 0)
		return (NULL);
	s = malloc((1 + WordNums) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < WordNums; j++)
	{
		while (Is_Delim(string[i], delim))
			i++;
		k = 0;
		while (!Is_Delim(string[i + k], delim) && string[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
