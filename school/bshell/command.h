/*============================================================================*/
/*                                                                            */
/*  filename:       command.c                                                 */
/*  author:         Brian Detweiler (bdetweiler@gmail.com)                    */
/*                                                                            */
/*  description:                                                              */
/*  note:                                                                     */
/*============================================================================*/

typedef struct command
{
    // malloc
    char*   program;
    char**  args;

    unsigned int arg_size;
    unsigned int arg_count;

    // "Class Methods" (if we actually had objects)
    void (*free_c)(struct command*);
    void (*print)(struct command*);

}Command;

// Starts off our history struct
void command_init(Command*, const char*);
void free_command(Command*);
void print_command(Command*);
