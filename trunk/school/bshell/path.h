/*============================================================================*/
/*                                                                            */
/*  filename:       path.h                                                    */
/*  author:         Brian Detweiler (bdetweiler@gmail.com)                    */
/*                                                                            */
/*  description:                                                              */
/*  note:                                                                     */
/*============================================================================*/

typedef struct path
{
    // malloc
    char**  paths;
    char*   cwd;
    char*   home;

    // Keep track of the number of paths so we can walk the pointer
    unsigned int path_count;
    unsigned int size;

    // Given a program and a Path*, return the canonical path to that file
    char* (*get_canonical_path)(struct path*, const char*);
    char* (*get_canonical_pathf)(struct path*, const char*, const char*);

    char* (*remove_filename)(struct path*, char*, const char*);
    const char* (*get_filename)(const char*); 

    // Search a directory for a file
    // Returns true if it exists in the directory
    unsigned int (*file_exist)(struct path*, const char*);
    unsigned int (*file_executable)(struct path*, const char*);
    const char* (*search)(struct path*, const char*);
    const char* (*search_exec)(struct path*, const char*);
    
    void (*print)(struct path*);
    void (*free_p)(struct path*);
}Path;

void  path_init(Path*, const char*, const char*, const char*);

char* get_cpath(Path*, const char*);
char* get_cpathf(Path*, const char*, const char*);
unsigned int exist(Path*, const char*);
unsigned int executable(Path*, const char*);
void  print_path(Path*);
void  free_path(Path*);
const char* search_for_file(Path*, const char*);
const char* search_for_executable_file(Path*, const char*);
const char* get_filename_from_path(const char*);
char* remove_filename_from_path(Path*, char*, const char*);
