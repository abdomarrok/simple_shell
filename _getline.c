#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @Pinfo: parameter struct
 * @Buffer: address of buffer
 * @length: address of length var
 *
 * Return: bytes read
 */
ssize_t input_buf(Passed_Info_t *Pinfo, char **Buffer, size_t *length)
{
	ssize_t r = 0;
	size_t length_p = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		free(*Buffer);
		*Buffer = NULL;
		signal(SIGINT, HandleSignal);
#if UseTheGetLine
		r = getline(Buffer, &length_p, stdin);
#else
		r = _getline(Pinfo, Buffer, &length_p);
#endif
		if (r > 0)
		{
			if ((*Buffer)[r - 1] == '\n')
			{
				(*Buffer)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			Pinfo->LineCount_Flag = 1;
			DeleteComment(*Buffer);
			Add_Hist_File_List(Pinfo, *Buffer, Pinfo->History_File_count++);
			{
				*length = r;
				Pinfo->Command_Buffer = Buffer;
			}
		}
	}
	return (r);
}

/**
 * Get_in - gets a line minus the newline
 * @Pinfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t Get_in(Passed_Info_t *Pinfo)
{
	static char *Buffer; /* the ';' command chain buffer */
	static size_t i, j, length;
	ssize_t r = 0;
	char **Buffer_p = &(Pinfo->arg), *p;

	_putchar(-1);
	r = input_buf(Pinfo, &Buffer, &length);
	if (r == -1) /* EOF */
		return (-1);
	if (length) /* we have commands left in the chain buffer */
	{
		j = i;			/* init new iterator to current Buffer position */
		p = Buffer + i; /* get pointer for return */

		Check_Hist_Chain(Pinfo, Buffer, &j, i, length);
		while (j < length) /* iterate to semicolon or end */
		{
			if (Is_Chain(Pinfo, Buffer, &j))
				break;
			j++;
		}

		i = j + 1;		 /* increment past nulled ';'' */
		if (i >= length) /* reached end of buffer? */
		{
			i = length = 0; /* reset position and length */
			Pinfo->Command_Buffer_Type = Command_Norm;
		}

		*Buffer_p = p;		 /* pass back pointer to current command position */
		return (_StrLen(p)); /* return length of current command */
	}

	*Buffer_p = Buffer; /* else not a chain, pass back buffer from _getline() */
	return (r);			/* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @Pinfo: parameter struct
 * @Buffer: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(Passed_Info_t *Pinfo, char *Buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(Pinfo->ReadFileInput, Buffer, R_Buffer_Size);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @Pinfo: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(Passed_Info_t *Pinfo, char **ptr, size_t *length)
{
	static char Buffer[R_Buffer_Size];
	static size_t i, length1;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == length1)
		i = length1 = 0;

	r = read_buf(Pinfo, Buffer, &length1);
	if (r == -1 || (r == 0 && length1 == 0))
		return (-1);

	c = _LocateChar(Buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - Buffer) : length1;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_StrNConcatinate(new_p, Buffer + i, k - i);
	else
		_StrNCopy(new_p, Buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * HandleSignal - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void HandleSignal(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(-1);
}
