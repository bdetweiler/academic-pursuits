#include<stdio.h>
#include<stdlib.h>

#include "path.h"

void status(Path*);

int main(int argc, char** argv, char** envp)
{
    Path path;
    printf("PATH: %s\n", getenv("PATH"));
    printf("PWD: %s\n", getenv("PWD"));
    printf("HOME: %s\n", getenv("HOME"));
    path_init(&path, getenv("PATH"), getenv("PWD"), getenv("HOME"));

    status(&path);

    printf("canonical path of 'ls': %s\n", path.get_canonical_path(&path, "ls"));

    printf("canonical path of '../../../../../.././ls': %s\n", path.get_canonical_path(&path, "../../../../../.././ls"));

    printf("get_canonical_path '/usr/bin/ls': %s\n", path.get_canonical_path(&path, "/usr/bin/ls"));
    printf("get_canonical_path '~/src/': %s\n", path.get_canonical_path(&path, "~/src/"));
    printf("get_canonical_path '~/../': %s\n", path.get_canonical_path(&path, "~/../"));
    printf("get_canonical_path '~/./../../.././': %s\n", path.get_canonical_path(&path, "~/./../../.././"));
    printf("get_canonical_path '~': %s\n", path.get_canonical_path(&path, "~"));

    printf("\n\n\n");
    printf("get_canonical_pathf '../../' and 'ls': %s\n", path.get_canonical_pathf(&path, "../../", "ls"));

    printf("get_canonical_pathf '/usr/bin/' and 'ls': %s\n", path.get_canonical_pathf(&path, "/usr/bin/", "ls"));
    printf("get_canonical_pathf '/usr/bin/../../usr/bin' and 'who': %s\n", path.get_canonical_pathf(&path, "/usr/bin/../../usr/bin", "who"));
    printf("get_canonical_pathf '~' and 'who': %s\n", path.get_canonical_pathf(&path, "~", "who"));

    printf("file_exists(/bin/ls) = %d\n", path.file_exist(&path, "/bin/ls"));
    printf("file_executable(/bin/ls) = %d\n", path.file_executable(&path, "/bin/ls"));

    printf("file_exists(stack.c) = %d\n", path.file_exist(&path, "stack.c"));
    printf("file_executable(stack.c) = %d\n", path.file_executable(&path, "stack.c"));
    
    printf("file_exists(nonexistantfile) = %d\n", path.file_exist(&path, "nonexistantfile"));
    printf("file_executable(nonexistantfile) = %d\n", path.file_executable(&path, "nonexistantfile"));

    printf("file_exists(~/.bash_history) = %d\n", path.file_exist(&path, "~/.bash_history"));
    printf("file_executable(~/.bash_history) = %d\n", path.file_executable(&path, "~/.bash_history"));

    printf("file_exists(~/src/../.xinitrc) = %d\n", path.file_exist(&path, "~/src/../.xinitrc"));
    printf("file_executable(~/src/../.xinitrc) = %d\n", path.file_executable(&path, "~/src/../.xinitrc"));


    printf("search(who) = %s\n", path.search(&path, "who"));
    printf("search(ls) = %s\n", path.search(&path, "ls"));
    printf("search(banner) = %s\n", path.search(&path, "banner"));
    printf("search(.bash_history) = %s\n", path.search(&path, ".bash_history"));
    printf("search(blah) = %s\n", path.search(&path, "blah"));
    printf("search(~/src/c/Operating Systems/bshell/bshell) = %s\n", path.search(&path, "~/src/c/Operating Systems/bshell/bshell"));

    printf("search_exec(who) = %s\n", path.search_exec(&path, "who"));
    printf("search_exec(ls) = %s\n", path.search_exec(&path, "ls"));
    printf("search_exec(banner) = %s\n", path.search_exec(&path, "banner"));
    printf("search_exec(blah) = %s\n", path.search_exec(&path, "blah"));
    printf("search_exec(~/src/c/Operating Systems/bshell/bshell) = %s\n", path.search_exec(&path, "~/src/c/Operating Systems/bshell/bshell"));


    path.free_p(&path);

    return 0;
}

void status(Path* p)
{
    int i = 0;

    for(i = 0; i < p->path_count; ++i)
        printf("path: %s\n", *(p->paths + (i * sizeof(char**))));

    printf("cwd: %s\n", p->cwd);
    printf("home: %s\n", p->home);

}
