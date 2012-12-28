/*============================================================================*/
/*                                                                            */
/*  filename:       history.c                                                 */
/*  author:         Brian Detweiler (bdetweiler@gmail.com)                    */
/*                                                                            */
/*  description:    Loads a history file into a struct. Allows a user to move */
/*                  up and down through the history.                          */
/*                  Stores typed lines in a queue-like manner.                */
/*                  Writes the history out to the original file.              */
/*                                                                            */
/*  note:           The file is read into memory then closed for the duration */
/*                  of the program. It is then re-opened and written to at    */
/*                  the end.                                                  */
/*                                                                            */
/*============================================================================*/

#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include "history.h"
void history_init(History* h, const char* bshell_history)
{
    FILE* history_file;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    h->lines = (char**)malloc(100 * sizeof(char*));

    h->line_count = 0;

    h->space_available = 100;

    h->add_line = history_add_line;

    h->print = print_history;

    h->write_h = write_history;

    h->history_file_name = (char*)malloc(strlen(bshell_history) * sizeof(char));
    strncpy(h->history_file_name, bshell_history, strlen(bshell_history));


    h->free_h = free_history;

    if((history_file = fopen(h->history_file_name, "r")) != NULL)
    {
        while((read = getline(&line, &len, history_file)) != -1) 
            h->add_line(h, line);

        fclose(history_file);
    }

    if(line)
        free(line);

    h->current_line_pos = h->line_count;

    h->prev = get_prev_line;
    h->next = get_next_line;

    // close h->history_file_name

    // set position to last line which should be blank

}

void free_history(History* h)
{
    unsigned int i = 0;
    if(h->history_file_name)
        free(h->history_file_name);


    // Free each line of the history file
    for(i = 0; i < h->line_count; ++i)
        if(*(h->lines + i))
            free(*(h->lines + i));

    if(h->lines)
        free(h->lines);
}

void history_add_line(History* h, const char* line)
{

    static char* new_line;

    new_line = calloc(strlen(line) * sizeof(char*), sizeof(char*));

    assert(new_line);

    if(h->line_count == h->space_available)
    {
        // Grow array by 100
        h->space_available += 100;
        h->lines = (char**)realloc(h->lines, h->space_available * sizeof(char**));
    }

    strncpy(new_line, line, strlen(line));

    h->lines[h->line_count] = new_line;

    ++(h->line_count);
    ++(h->current_line_pos);

    h->current_line = *(h->lines + h->line_count);
}

// Gets the previous line of history
char* get_prev_line(History* h)
{
    if(h->current_line_pos > 0)
    {
        --(h->current_line_pos);
        h->current_line = (*(h->lines + h->current_line_pos));
    }

    return h->current_line;
}

// Gets the next line of history
char* get_next_line(History* h)
{
    if(h->current_line_pos < h->line_count - 1)
    {
        ++(h->current_line_pos);
        h->current_line = (*(h->lines + h->current_line_pos));
    }
    else
    {
        if(h->current_line_pos < h->line_count)
            ++(h->current_line_pos);

        h->current_line = NULL;
    }

    return h->current_line;
}

// Adds a new line of history
int write_history(History* h)
{
    FILE* history_file = NULL;
    int i = 0;
    int j = 0;
    int bytes = 0;

    if((history_file = fopen(h->history_file_name, "w")) != NULL)
        // Iterate over the lines of the history file
        for(i = 0; i < h->line_count; ++i)
            // Iterate over each character of the current line
            for(j = 0; j < strlen(*(h->lines + i)); ++j)
                bytes += putc((*(h->lines + i))[j], history_file);

    return bytes;
}

void print_history(History* h)
{

    int i = 0;

    // copy data into tmp
    printf("line count: %d\n", h->line_count);
    for(; i < h->line_count; ++i)
         printf("%d: %s", i, h->lines[i]);

}

