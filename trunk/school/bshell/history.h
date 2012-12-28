/*============================================================================*/
/*                                                                            */
/*  filename:       history.h                                                 */
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

typedef struct history
{
    // malloc
    char** lines;
    char*  current_line;
    int    current_line_pos;
    char*  history_file_name;
    int    line_count;
    int    space_available;

    // "Class Methods" (if we actually had objects)
    void (*add_line)(struct history*, const char*);
    int  (*write_h)(struct history*);
    void (*print)(struct history*);
    void (*free_h)(struct history*);

    char* (*prev)(struct history*);
    char* (*next)(struct history*);

}History;

// Starts off our history struct
void history_init(History*, const char*);

// Adds a new line of history
void history_add_line(History*, const char*);
//void load_history_file(History*, FILE*);
int  write_history(History*);
void print_history(History*);
void free_history(History*);
char* get_prev_line(History*);
char* get_next_line(History*);
