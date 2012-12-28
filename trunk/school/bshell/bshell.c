#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

// Keyboard event handler
#include "kbhit.h"
// Keeps a history of all typed in commands, much like Bash
#include "history.h"
// Used to conveniently store typed in commands to be ran
#include "command.h"
// Used to get canonical paths
#include "path.h"
// Used by path for easy figurin' out of canonical paths
#include "stack.h"

#define _CTRL_C_        3
#define _BACKSPACE_     127
#define _RETURN_        10
#define _ESC_           27 

#define _MAX_COMMANDS_  5
#define _BUFSIZE_       1025

#define PROMPT "\n$ "

void run(Path*, Command*, Command*, Command*, Command*, Command*, char**);

int main(int argc, char** argv, char** envp)
{
    unsigned int key = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int len = 0;
    char buf[_BUFSIZE_];
    char* tok = NULL;
    char* tok0 = NULL;
    char* tok1 = NULL;
    char* tok2 = NULL;
    char* tok3 = NULL;
    char* tok4 = NULL;
    char* sep = "|";

    /* Read into a structure
     * Manipulate structure while program is running
     * Write out the structure when we are done.
     */
    char* bshell_history = ".bshell_history";
    char* path_from_envp = NULL;
    char* cwd = NULL;
    char* home = NULL;


    Path path;
    History history;

    // NULL-terminated command pointer
    // We allow up to 5 commands
    //Command* commands;
    //commands = (Command*)malloc(_MAX_COMMANDS_ * sizeof(Command*));
  

    Command command0;
    Command command1;
    Command command2;
    Command command3;
    Command command4;


    history_init(&history, bshell_history);

    // Set our buffers to nulls
    memset(&buf, '\0', 1024);

    // Environment variables
    path_from_envp = getenv("PATH");
    home = getenv("HOME");
    cwd = getenv("PWD");


    path_init(&path, path_from_envp, cwd, home);

    // Initialize keyboard for key capture
    init_keyboard();

    write(1, PROMPT, strlen(PROMPT));

    do
    {

        // Wait for user to press a key
        key = readch();

        if(key == _CTRL_C_)
        {
            write(1, PROMPT, strlen(PROMPT));

            // Erase whatever was in the buffer
            memset(&buf, '\0', 1024);
            i = 0;

            history.current_line = NULL;
            history.current_line_pos = history.line_count;
        }
        // Detect UP or DOWN arrows for history
        // If escape
        else if(key == _ESC_)
        {
            // Read another character
            key = readch();

            // If that character is '['
            if(key == '[')
            {
                // Read another character
                key = readch();

                // If that character is 'A'
                if(key == 'A')
                {
                    len = strlen(buf);
                    for(j = 0; j < len; ++j)
                    {
                        write(1, "\b", 1);
                        write(1, " ", 1);

                        // Move the cursor back one space to where we wanted it
                        write(1, "\b", 1);
                        buf[--i] = '\0';
                    }

                    history.prev(&history);

                    strncpy(buf, history.current_line, strlen(history.current_line)); 

                    if(history.current_line && buf[strlen(history.current_line) - 1] == '\n')
                        buf[strlen(history.current_line) - 1] = '\0';
                    write(1, &buf, strlen(buf));

                    i = strlen(buf);
                }
                // If that character is 'B'
                else if(key == 'B')
                {
                    len = strlen(buf);
                    for(j = 0; j < len; ++j)
                    {
                        write(1, "\b", 1);
                        write(1, " ", 1);

                        // Move the cursor back one space to where we wanted it
                        write(1, "\b", 1);
                        buf[--i] = '\0';
                    }

                    history.next(&history);

                    // If there's any more lines of history to go through, copy that into buf.
                    if(history.current_line_pos < history.line_count)
                        strncpy(buf, history.current_line, strlen(history.current_line)); 
                    // Else, we're at the end
                    else
                        memset(&buf, '\0', 1024);

                    if(history.current_line && buf[strlen(history.current_line) - 1] == '\n')
                        buf[strlen(history.current_line) - 1] = '\0';

                    write(1, &buf, strlen(buf));

                    i = strlen(buf);
                }
            }
        }
        // Backspace was pressed.
        else if(key == _BACKSPACE_)
        {
            if(i > 0)
            {
                buf[--i] = '\0';
                // Move the cursor back one space
                write(1, "\b", 1);

                /* Replace the character at this position 
                 * with a space to give the illusion of erasing it
                 * This also advances the cursor back to the original
                 * position
                 */
                write(1, " ", 1);

                // Move the cursor back one space to where we wanted it
                write(1, "\b", 1);
            }
        }
        // Pressed return - Perform the action
        else if(key == _RETURN_)
        {
            /* Modifies input by replacing '|' with '\0', and returning an array of pointers to the actual pieces
             * eg. l  s  -  a  l  |     g  r  e  p  t  e  s  t     |     m  o  r  e \0
             *     0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22
             * 
             * Replace '|' with '\0':
             *     l  s  -  a  l  \0    g  r  e  p  t  e  s  t    \0     m  o  r  e \0
             *
             * The return array now becomes this:
             * [input + 0][input + 6][input + 17]
             */
  
            write(1, "\n", 1);

            // fwrite(buf, 1, sizeof(buf), bshell_history);
            // putc('\n', bshell_history);

            buf[i] = '\n';
            buf[i + 1] = '\0';

            // If there was data, add it to history
            if(buf[0] != '\n')
                history.add_line(&history, buf);

            buf[i] = '\0';

            // Write the what we currently have for history
            history.write_h(&history);


            history.current_line = NULL;
            history.current_line_pos = history.line_count;
           
            // Need to parse out the commands

            // Parse out any pipes and create our "commands"
            j = 0;
            for(tok = strtok(buf, sep); tok; tok = strtok(NULL, sep))
            {
                switch(j)
                {
                    case 0:
                        tok0 = tok;
                        break;
                    case 1:
                        tok1 = tok;
                        break;
                    case 2:
                        tok2 = tok;
                        break;
                    case 3:
                        tok3 = tok;
                        break;
                    case 4:
                        tok4 = tok;
                        break;
                    default:
                        break;
                }

                if(j > 4)
                    break;

                ++j;
            }

            command_init(&command0, tok0);
            command_init(&command1, tok1);
            command_init(&command2, tok2);
            command_init(&command3, tok3);
            command_init(&command4, tok4);

            // There is at least one command
            //commands[0] = command0;
            //commands[1] = command1;
            //commands[2] = command2;
            //commands[3] = command3;
            //commands[4] = command4;
            run(&path, 
                &command0,
                &command1,
                &command2,
                &command3,
                &command4, 
                envp);

            // write(1, "\nbshell > ", 10);
            memset(&buf, '\0', 1024);
            i = 0;

            command0.free_c(&command0);

            write(1, PROMPT, strlen(PROMPT));
        }
        // The user is still typing
        else
        {
            if(i < 1024)
            {
                buf[i] = (char)key;
                ++i;
                write(1, &key, 1);
            }
            else
            {
                printf("Your string must be less than _BUFSIZE_ characters long.\n");
                return 1;
            }
        }
    }while(key != 4);

    write(1, "\n", 1);

    path.free_p(&path);

    history.free_h(&history);

    close_keyboard();


    return 0;
}


void run(Path*    path,
         Command* command0, 
         Command* command1, 
         Command* command2, 
         Command* command3, 
         Command* command4,
         char** envp)
{

    // Nothing to execute
    if(!command0->program)
        return;

    // If command1 is null, then there's just one command to run (no pipes)
    if(!command1->program)
    {
        /* Looks like this:
         * arg_v[0]     -> program
         * arg_v[1]     -> argument1
         * arg_v[2]     -> argument2
         * ...
         * arg_v[n]     -> argumentn
         * arg_v[n + 1] -> NULL
         */
        char* arg_v[command0->arg_count + 2];
		
        // waitpid's return value
        pid_t status;
        // child's exit status
        int child_status;

        // Our processes
        pid_t pid0;
            
        unsigned int i = 1;

        pid0 = fork();

        if(pid0 == -1)
        {
            printf("Fork failed\n");
            exit(1);
        }
        else if(pid0 == 0)
        {
            arg_v[0] = command1->program;
            
            for(i = 1; i <= command2->arg_count; ++i)
                arg_v[i] = (command2->args)[i - 1];

            // Have to NULL terminate
            arg_v[i] = (char*)0;

            // If it's executable, execute it!
            if(path->search_exec(path, command0->program))
                execve(path->search_exec(path, command0->program), arg_v, envp);
            else
                printf("bshell: %s: command not found\n", command0->program);

            perror("exec error\n");
            exit(2);
        }

        status = waitpid(pid0, &child_status, 0);
        if (status == -1) 
        {
            perror("waitpid");
            exit(4);
        }
    }
    else
    {
        /*
        int p0[2] = {-1, -1}; 

        close(0);
        dup(p0[0]);
        close(p0[1]);
        */
        printf("Pipe functionality goes here. But it's not done. :-(\n");
        // Pipe functionality here
    }
}
