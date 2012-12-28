/*============================================================================*/
/*                                                                            */
/*  filename:       command.c                                                 */
/*  author:         Brian Detweiler (bdetweiler@gmail.com)                    */
/*                                                                            */
/*  description:                                                              */
/*  note:                                                                     */
/*============================================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include "command.h"

#define ARGNUM 10

void command_init(Command* c, const char* command_line)
{
    char* line = NULL;
    char* tok = NULL;
    char* sep = " ";

    c->arg_count = 0;
    c->arg_size = ARGNUM;
    c->program = NULL;

    if(command_line)
    {
        line = (char*)malloc(strlen(command_line) * sizeof(char*));
        strncpy(line, command_line, strlen(command_line));
        line[strlen(command_line)] = '\0';
    }

    c->args = (char**)malloc(ARGNUM * sizeof(char**));

    tok = strtok(line, sep);
  
    if(tok)
    {
        c->program = (char*)malloc(strlen(tok) * sizeof(char*));
        // First token is the program
        strncpy(c->program, tok, strlen(tok));
        (c->program)[strlen(tok)] = '\0';
    }

    while((tok = strtok(NULL, sep)))
    {

        static char* new_arg;

        new_arg = calloc(strlen(tok) * sizeof(char*), sizeof(char*));
        assert(new_arg);

        // If we have a ton of args (more than ARGNUM) resize the char**
        if(c->arg_count == c->arg_size - 1)
        {
            c->args = (char**)realloc(c->args, (c->arg_size + ARGNUM) * sizeof(char**));
            c->arg_size += ARGNUM;
        }

        // Adding to the arguments by upping the arg_count on each iteration

        strncpy(new_arg, tok, strlen(tok));
        new_arg[strlen(tok)] = '\0';

        (c->args)[c->arg_count] = new_arg;

        ++(c->arg_count);
    }

    // We have to terminate the arguments with a null pointer. 
    (c->args)[c->arg_count] = NULL;

    c->print = print_command;
    c->free_c = free_command;

}

void free_command(Command* c)
{
    unsigned int i = 0;
    if(c->program)
        free(c->program);


    // Free each line of the history file
    for(i = 0; i < c->arg_count; ++i)
    {
        if((c->args)[i])
        {
            free((c->args)[i]);
        }
    }

    c->arg_count = 0;


    if(c->args)
        free(c->args);
}


void print_command(Command* c)
{
    int i = 0;

    printf("program: %s\n", c->program);

    printf("args:\n");
    // copy data into tmp
    for(; i < c->arg_count; ++i)
    { 
        printf("%d:       %s\n", i, c->args[i]);
    }

    printf("\n");
}
