#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define R_Buffer_Size 1024
#define W_Buffer_Size 1024

/* the command chaining */
#define Command_Norm 0
#define Command_Or 1
#define Command_And 2
#define Command_Chain 3

/* for ConvertNum() */
#define ConvLower 1
#define ConvUnsigned 2

/* 1 if using system getline() */
#define UseTheGetLine 0
#define UseTheStrTok 0

#define History_File ".simple_shell_history"
#define History_Max 4096

extern char **environ;

/**
 * struct ListStrings - singly linked list
 * @number: the number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct ListStrings
{
	int number;
	char *string;
	struct ListStrings *next;
} MyListString;

/**
 *struct Passed_Info - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@Line_Count: the error count
 *@Error_Number: the error code for exit()s
 *@LineCount_Flag: if on count this line of input
 *@File_Name: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@Env_Status: on if environ was changed
 *@status: the return status of the last exec'd command
 *@Command_Buffer: address of pointer to Command_Buffer, on if chaining
 *@Command_Buffer_Type: CMD_type ||, &&, ;
 *@ReadFileInput: the fileD from which to read line input
 *@History_File_count: the history line number count
 */
typedef struct Passed_Info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int Line_Count;
	int Error_Number;
	int LineCount_Flag;
	char *File_Name;
	MyListString *env;
	MyListString *history;
	MyListString *alias;
	char **environ;
	int Env_Status;
	int status;

	char **Command_Buffer;
	int Command_Buffer_Type;
	int ReadFileInput;
	int History_File_count;
} Passed_Info_t;

#define Info_Initialization                                                     \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 *struct Built_In - contains a Built_In string and related function
 *@type: the Built_In command flag
 *@func: the function
 */
typedef struct Built_In
{
	char *type;
	int (*func)(Passed_Info_t *);
} Built_In_table;

int main_shell_loop(Passed_Info_t *, char **);
int Find_Built_In(Passed_Info_t *);
void Find_Command(Passed_Info_t *);
void Fork_Command(Passed_Info_t *);

int Is_Command(Passed_Info_t *, char *);
char *DuplicateChars(char *, int, int);
char *Find_Command_Path(Passed_Info_t *, char *, char *);

void _PutsErr(char *);
int _PutCharsErr(char);
int _PutFileDescriptor(char ch, int fileD);
int _PutsFileDescriptorSring(char *str, int fileD);

int _StrLen(char *);
int _StrCompare(char *, char *);
char *StrStartWith(const char *, const char *);
char *_StrConcatinate(char *, char *);

char *_StrCopy(char *, char *);
char *_StrDublicate(const char *);
void _puts(char *);
int _putchar(char);

char *_StrNCopy(char *, char *, int);
char *_StrNConcatinate(char *, char *, int);
char *_LocateChar(char *, char);

char **_strtok(char *, char *);
char **_strtok2(char *, char);

char *_MemorySet(char *, char, unsigned int);
void FreeStrofStr(char **);
void *_realloc(void *, unsigned int, unsigned int);

int FreesPointer(void **);

int Is_InterActiveMode(Passed_Info_t *);
int Is_Delim(char, char *);
int Is_Alphabet(int);
int _atoi(char *);

int Str_to_Int(char *);
void PrintErr(Passed_Info_t *, char *);
int PrintDecimal(int, int);
char *ConvertNum(long int, int, int);
void DeleteComment(char *);

int builtin_exit(Passed_Info_t *);
int _cd(Passed_Info_t *);
int _Help(Passed_Info_t *);

int _History(Passed_Info_t *);
int set_alias(Passed_Info_t *Pinfo, char *string);
int Remove_alias(Passed_Info_t *Pinfo, char *string);
int print_alias(MyListString *node);
int _Alias(Passed_Info_t *);

ssize_t Get_in(Passed_Info_t *);
int _getline(Passed_Info_t *, char **, size_t *);
void HandleSignal(int);

void Init_Info(Passed_Info_t *);
void Set_info(Passed_Info_t *, char **);
void Free_Passed_info(Passed_Info_t *, int);

char *_Get_Env(Passed_Info_t *, const char *);
int _env(Passed_Info_t *);
int _Set_Env(Passed_Info_t *);
int RemoveEnvVar(Passed_Info_t *);
int Populate_Envs(Passed_Info_t *);

char **Get_Environ(Passed_Info_t *);
int RemoveEnvVarByName(Passed_Info_t *, char *);
int _Set_Or_Edit_Env(Passed_Info_t *, char *, char *);

char *Get_Hist_File(Passed_Info_t *Pinfo);
int Set_Hist_File(Passed_Info_t *Pinfo);
int Get_Hist_file(Passed_Info_t *Pinfo);
int Add_Hist_File_List(Passed_Info_t *info, char *buf, int linecount);
int Edit_Hist_Num(Passed_Info_t *Pinfo);

MyListString *ajouterNode(MyListString **, const char *, int);
MyListString *ajouterNode_end(MyListString **, const char *, int);
size_t PrintStrs(const MyListString *);
int SupprimeNodeAt(MyListString **, unsigned int);
void FreeNodes(MyListString **);

size_t List_Length(const MyListString *);
char **List_to_Str(MyListString *);
size_t Print_List(const MyListString *);
MyListString *getNodeStartWith(MyListString *, char *, char);
ssize_t getNodeIndexAt(MyListString *, MyListString *);

int Is_Chain(Passed_Info_t *, char *, size_t *);
void Check_Hist_Chain(Passed_Info_t *, char *, size_t *, size_t, size_t);
int Change_alias(Passed_Info_t *);
int Change_vars(Passed_Info_t *);
int Change_string(char **, char *);

#endif
