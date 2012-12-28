/*============================================================================*/
/*                                                                            */
/*  filename:       path.c                                                    */
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
#include<dirent.h>

#include "stack.h"
#include "path.h"

#define PATHSIZE 10

void path_init(Path* p, const char* paths, const char* current_working_directory, const char* home_dir)
{
    // Seperator for PATH env var
    char* sep = ":";
    // tokens for PATH env var
    char* cur_dir = NULL;
    long unsigned int paths_len = 0;
    long unsigned int current_working_directory_len = 0;
    long unsigned int home_dir_len = 0;

    if(paths)
        paths_len = strlen(paths);

    if(current_working_directory)
        current_working_directory_len = strlen(current_working_directory);

    if(home_dir)
        home_dir_len = strlen(home_dir);

    // Since paths, current_working_directory, and home_dir are const, we'll copy it to a temporary ones
    char* tmp_paths = (char*)malloc(paths_len * sizeof(char*));
    p->cwd = (char*)malloc(current_working_directory_len * sizeof(char*));
    p->home = (char*)malloc(home_dir_len * sizeof(char*));

    unsigned int i = 0;

    p->path_count = 0;
    p->size = PATHSIZE;
    p->paths = (char**)malloc(p->size * sizeof(char**));
    p->paths[0] = NULL;


    // "Class methods" - these are "air quotes"
    p->get_canonical_path = get_cpath;
    p->get_canonical_pathf = get_cpathf;
    p->search = search_for_file;
    p->search_exec = search_for_executable_file;
    p->print = print_path;
    p->free_p = free_path;
    p->file_exist = exist;
    p->file_executable = executable;
    p->remove_filename = remove_filename_from_path;
    p->get_filename = get_filename_from_path;


    // This is how we should be getting it, but if it came with the PATH= part, 
    // we can strip that out
    if(paths[0] == '/')
    {
        strncpy(tmp_paths, paths, paths_len);
        tmp_paths[paths_len] = '\0';
    }
    else if(paths[0] == 'P' &&
            paths[1] == 'A' &&
            paths[2] == 'T' &&
            paths[3] == 'H' &&
            paths[4] == '=')
    {
        for(i = 5; i < paths_len; ++i)
            tmp_paths[i - 5] = paths[i];
    }

    // current working directory (PWD)
    if(current_working_directory[0] == '/')
    {
        strncpy(p->cwd, current_working_directory, current_working_directory_len);
        p->cwd[current_working_directory_len] = '\0';
    }
    else if(current_working_directory[0] == 'P' &&
            current_working_directory[1] == 'W' &&
            current_working_directory[2] == 'D' &&
            current_working_directory[3] == '=')
    {
        for(i = 4; i < current_working_directory_len; ++i)
            p->cwd[i - 4] = current_working_directory[i];

        // p->cwd[i - 4] == '\0';
    }
    
    // Home dir
    if(home_dir[0] == '/')
    {
        strncpy(p->home, home_dir, home_dir_len);
        (p->home)[home_dir_len] = '\0';
    }
    else if(home_dir[0] == 'H' &&
            home_dir[1] == 'O' &&
            home_dir[2] == 'M' &&
            home_dir[3] == 'E' &&
            home_dir[4] == '=')
    {
        for(i = 5; i < home_dir_len; ++i)
            p->home[i - 5] = home_dir[i];

        // p->home[i - 5] == '\0';
    }




    for(cur_dir = strtok(tmp_paths, sep); cur_dir; cur_dir = strtok(NULL, sep))
    {
        ++(p->path_count);

        // Allocate a pointer to a string
        if(p->path_count >= p->size)
        {
            p->paths = (char**)realloc(p->paths, ((p->size + PATHSIZE) * sizeof(char**)));
            p->size += PATHSIZE;
        }

        // Allocate space for the string
        *(p->paths + ((p->path_count - 1) * sizeof(char**))) = (char*)malloc(strlen(cur_dir) * sizeof(char*));

        // Copy the string into the string pointer location
        strncpy(*(p->paths + (p->path_count - 1) * sizeof(char**)), cur_dir, strlen(cur_dir));

        (*(p->paths + ((p->path_count - 1) * sizeof(char**))))[strlen(cur_dir)] = '\0';
    }

    free(tmp_paths);
}

char* get_cpath(Path* p, const char* path)
{
    char* sep = "/";
    char* tok = NULL;
    char* tmp_home = NULL;
    char* tmp_cwd = NULL;
    Stack stack;
    static char* tmp_path = NULL;
    unsigned int i = 0;
    long unsigned int path_len = 0;
    long unsigned int cwd_len = 0;
    long unsigned int home_len = 0;

    if(path)
        path_len = strlen(path);
    if(p->cwd)
        cwd_len = strlen(p->cwd);
    if(p->home)
        home_len = strlen(p->home);

    // XXX: FREE ME
    tmp_path = (char*)malloc(path_len + cwd_len + home_len * sizeof(char*));

    tmp_home = (char*)malloc(home_len * sizeof(char*));
    tmp_cwd = (char*)malloc(cwd_len * sizeof(char*));

    strncpy(tmp_path, path, path_len);
    tmp_path[path_len] = '\0';

    strncpy(tmp_home, p->home, home_len);
    tmp_home[home_len] = '\0';

    strncpy(tmp_cwd, p->cwd, cwd_len);
    tmp_cwd[cwd_len] = '\0';

    init_stack(&stack);


    // not null && ROOT
    if(tmp_path && tmp_path[0] == '/')
    {
        for(tok = strtok(tmp_path, sep); tok; tok = strtok(NULL, sep))
        {
            if(strlen(tok) == 2 && 
               tok[0] == '.' &&
               tok[1] == '.' &&
               stack.top > 0)
            {
                stack.pop(&stack);
            } 
            else if(strlen(tok) == 2 && 
               tok[0] == '.' &&
               tok[1] == '.' &&
               stack.top == 0)
            {
                tmp_path[0] = '/';
                tmp_path[1] = '\0';
            } 
            else if(strlen(tok) == 1 &&
                    tok[0] == '.')
            {
                ;;;
            }
            else
            {
                stack.push(&stack, tok);
            }
        }
    }
    // Otherwise we're starting at home
    else if(tmp_path && tmp_path[0] == '~')
    {
        // Push HOME on stack
        for(tok = strtok(tmp_home, sep); tok; tok = strtok(NULL, sep))
        {
            if(strlen(tok) == 2 && 
               tok[0] == '.' &&
               tok[1] == '.' &&
               stack.top > 0)
            {
                stack.pop(&stack);
            } 
            else if(strlen(tok) == 2 && 
               tok[0] == '.' &&
               tok[1] == '.' &&
               stack.top == 0)
            {
                tmp_path[0] = '/';
                tmp_path[1] = '\0';
            } 
            else if(strlen(tok) == 1 &&
                    tok[0] == '.')
            {
                ;;;
            }
            else
            {
                stack.push(&stack, tok);
            }
        }

        for(tok = strtok(tmp_path, sep); tok; tok = strtok(NULL, sep))
        {
            // If it's "home" ignore it, we've already pushed HOME
            if(tok[0] == '~')
            {
                continue;
            }
            else if(strlen(tok) == 2 && 
               tok[0] == '.' &&
               tok[1] == '.' &&
               stack.top > 0)
            {
                stack.pop(&stack);
            } 
            // If we've backed too far out, we're already at root
            else if(strlen(tok) == 2 && 
               tok[0] == '.' &&
               tok[1] == '.' &&
               stack.top == 0)
            {
                tmp_path[0] = '/';
                tmp_path[1] = '\0';
            } 
            else if(strlen(tok) == 1 &&
                    tok[0] == '.')
            {
                ;;;
            }
            else
            {
                stack.push(&stack, tok);
            }
        }
    }
    // Else, we're starting with CWD
    else 
    {
        // Push CWD on stack
        for(tok = strtok(tmp_cwd, sep); tok; tok = strtok(NULL, sep))
        {
            if(strlen(tok) == 2 && 
               tok[0] == '.' &&
               tok[1] == '.' &&
               stack.top > 0)
            {
                stack.pop(&stack);
            } 
            else if(strlen(tok) == 2 && 
               tok[0] == '.' &&
               tok[1] == '.' &&
               stack.top == 0)
            {
                tmp_path[0] = '/';
                tmp_path[1] = '\0';
            } 
            else if(strlen(tok) == 1 &&
                    tok[0] == '.')
            {
                ;;;
            }
            else
            {
                stack.push(&stack, tok);
            }
        }

        // Now find the path relative to the current directory
        for(tok = strtok(tmp_path, sep); tok; tok = strtok(NULL, sep))
        {
            if(strlen(tok) == 2 && 
               tok[0] == '.' &&
               tok[1] == '.' &&
               stack.top > 0)
            {
                stack.pop(&stack);
            } 
            else if(strlen(tok) == 2 && 
               tok[0] == '.' &&
               tok[1] == '.' &&
               stack.top == 0)
            {
                tmp_path[0] = '/';
                tmp_path[1] = '\0';
            } 
            else if(strlen(tok) == 1 &&
                    tok[0] == '.')
            {
                ;;;
            }
            else
            {
                stack.push(&stack, tok);
            }

        } 

    }

    if(stack.top == 0)
        tmp_path[i++] = '/';

    // Start our finished path at root
    while(stack.top > 0)
    {
        unsigned int j = 0;
        tmp_path[i++] = '/';
        for(; j < strlen(stack.peek_bottom(&stack)); ++j)
            tmp_path[i++] = stack.peek_bottom(&stack)[j];

        stack.pop_bottom(&stack);
    }

    tmp_path[i] = '\0';

    if(tmp_home)
        free(tmp_home);
    if(tmp_cwd)
        free(tmp_cwd);

    free_stack(&stack);

    return tmp_path;
}

/** 
 * get_cpathf
 * 
 * @param Path* p The "this" Path object
 * @param const char* dir The directory 
 * @param const char* file The file 
 */
char* get_cpathf(Path* p, const char* dir, const char* file)
{
    static char* fullpath = NULL;
    int slash_bit = 1;
    int i = 0;
    int j = 0;
    long unsigned int dir_len = 0;
    long unsigned int file_len = 0;
    long unsigned int cwd_len = 0;
    long unsigned int home_len = 0;

    if(dir)
        dir_len = strlen(dir);
    if(file) 
        file_len = strlen(file);
    if(p->cwd) 
        cwd_len = strlen(p->cwd);
    if(p->home)
        home_len = strlen(p->home);

    // XXX: NEED TO FREE THIS TOO
    fullpath = (char*)malloc((dir_len + cwd_len + home_len + file_len) * sizeof(char*));

    i = strlen(get_cpath(p, dir));

    strncpy(fullpath, get_cpath(p, dir), i);

    // If there wasn't a slash in the path, add one
    // XXX: Maybe we shouldn't allow this, but we will for now
    if(fullpath[i] != '/')
    {
        // "/home/bdetweiler/src" = "/home/bdetweiler/src/"
        fullpath[i++] = '/';
    }
    else
    {
        --slash_bit;
    }

    // "/home/bdetweiler/src/" = "/home/bdetweiler/src/a.out"
    for(j = 0; j < file_len + slash_bit; ++j, ++i)
    {
        fullpath[i] = file[j];
    }

    // "/home/bdetweiler/src/a.out" = "/home/bdetweiler/src/a.out\0"
    fullpath[i] = '\0';

    return fullpath;
}

const char* get_filename_from_path(const char* fullpath)
{
    int i = 0;
    int j = 0;
    static char* filename = NULL;
    long unsigned int fullpath_len = 0;

    if(fullpath)
        fullpath_len = strlen(fullpath);

    // XXX: FREE ME!!!
    filename = (char*)malloc(fullpath_len * sizeof(char*));

    // Work from the back of the string to the front
    for(i = fullpath_len; i >= 0; --i)
    {
        if(i == 0)
            break;

        if(fullpath[i] == '/')
        {
            // move forward one, and we're done
            ++i;
            break;
        }
    }

    for(; i < fullpath_len; ++i)
    {
        filename[j++] = fullpath[i];
    }

    filename[j] = '\0';
    // i is now at the start of the filename
    // filename = &(fullpath[i]);
    return filename;
}


/**
 * remove_filename_from_path
 *
 * @param char* new_fullpath 
 * @param const char* new_fullpath 
 *
 * @return char*
 *
 * notes: I hate the way I did this, but after evaluating all my options,
 *        I actually hated all of them. So I just picked one. This one. Sorry.
 */
char* remove_filename_from_path(Path* p, char* new_fullpath, const char* fullpath)
{
    int i = 0;
    DIR* dir = NULL;
    char* tmp_fullpath = NULL;
    long unsigned int fullpath_len = 0;
    long unsigned int home_len = 0;
    long unsigned int cwd_len = 0;
    long unsigned int new_fullpath_len = 0;
    long unsigned int tmp_fullpath_len = 0;


    if(fullpath)
        fullpath_len = strlen(fullpath);
    if(p->cwd)
        cwd_len = strlen(p->cwd);
    if(p->home)
        home_len = strlen(p->home);

    tmp_fullpath = get_cpath(p, fullpath);

    if(tmp_fullpath)
        tmp_fullpath_len = strlen(tmp_fullpath);

    // XXX: MUST FREE AFTER USE
    new_fullpath = (char*)calloc((tmp_fullpath_len) * sizeof(char*), sizeof(char*));
    strncpy(new_fullpath, tmp_fullpath, tmp_fullpath_len);
    new_fullpath[tmp_fullpath_len] = '\0';


    if(new_fullpath)
        new_fullpath_len = strlen(new_fullpath);



    // If there is no file tacked on
    // e.g. /usr/local/bin
    if((dir = opendir(new_fullpath)))
    {
        closedir(dir);
    }
    // Else if there is a file tacked on
    // e.g. /usr/bin/ls
    else
    {
        // Work from the back of the string to the front
        for(i = new_fullpath_len; i >= 0; --i)
        {

            if(new_fullpath[i] == '/')
            {
                new_fullpath[i] = '\0';
                break;
            }
        }
        // Check to see if our newly created "directory"
        // actually is a directory
        if(new_fullpath && (dir = opendir(new_fullpath)))
        {
            closedir(dir);
        }
        else
        {
            new_fullpath = NULL;
        }
    }
    // i is now at the start of the filename
    return new_fullpath;
}

// Search through the paths and see if the file exists in each one
// Returns the full path on success, NULL on failure. 
const char* search_for_file(Path* p, const char* file)
{
    int i = 0;
    static char* full_path = NULL;

    for(; i < p->path_count; ++i)
    {
        full_path = NULL;
        char* new_path = p->get_canonical_pathf(p, *(p->paths + (i * sizeof(char**)) ), file);

        if(exist(p, new_path))
        {
            full_path = new_path;
            break;
        }

    }

    return full_path;
}

const char* search_for_executable_file(Path* p, const char* file)
{
    int i = 0;
    static char* full_path = NULL;

    for(; i < p->path_count; ++i)
    {
        full_path = NULL;
        char* new_path = p->get_canonical_pathf(p, p->paths[i * sizeof(char**)], file);

        if(executable(p, new_path))
        {
            full_path = new_path;
            break;
        }

    }

    return full_path;
}

unsigned int exist(Path* p, const char* fullpath)
{
    FILE* file;
    char* tmp_fullpath = NULL;
    unsigned int rval = 0;


    // If it's NULL
    if(!fullpath)
        rval = 0;
    else
    {
        // Set a temporary path
        tmp_fullpath = (char*)malloc(strlen(fullpath) * sizeof(char*));
        // Copy the path to the tmp path
        strncpy(tmp_fullpath, fullpath, strlen(fullpath));
        tmp_fullpath[strlen(fullpath)] = '\0';

        rval = 1;
    }

    if(rval && (file = fopen(get_cpathf(p, 
                                        remove_filename_from_path(p, tmp_fullpath, fullpath), 
                                        get_filename_from_path(fullpath)),
                                        
                             "r")))
    {
        fclose(file);
        rval = 1;
    }
    else
        rval = 0;

    return rval;
}

unsigned int executable(Path* p, const char* fullpath)
{
    char* tmp_fullpath = NULL;
    unsigned int rval = 0;

    // If it's NULL
    if(!fullpath)
        rval = 0;
    else
    {
        tmp_fullpath = (char*)malloc(strlen(fullpath) * sizeof(char*));
        strncpy(tmp_fullpath, fullpath, strlen(fullpath));
        tmp_fullpath[strlen(fullpath)] = '\0';

        rval = 1;
    }

    if(rval && (access(get_cpathf(p, 
                                  remove_filename_from_path(p, tmp_fullpath, fullpath), 
                                  get_filename_from_path(fullpath)),
                             X_OK) != -1))
    {
        rval = 1;
    }
    else
        rval = 0;

    return rval;
}

void print_path(Path* p)
{
    unsigned int i = 0;
    printf("PATHS: \n");
    // Free each line of the path
    for(i = 0; i < p->path_count; ++i)
    {
        printf("%s\n", p->paths[i * sizeof(char**)]);
    }
}

void free_path(Path* p)
{
    unsigned int i = 0;

    // Free each line of the path
    for(i = 0; i < p->path_count; ++i)
        if(p->paths[i * sizeof(char**)])
            free(p->paths[i * sizeof(char**)]);
            

    if(p->paths)
        free(p->paths);

    if(p->cwd)
        free(p->cwd);

    if(p->home)
        free(p->home);
}
