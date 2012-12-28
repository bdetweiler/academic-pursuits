#include<stdio.h>
#include<stdlib.h>

#include "history.h"

void status(History*);

int main(void)
{
    History history;
    
    history_init(&history, ".bash_history");

    printf("loaded .bash_history\n");

    history.print(&history);

    status(&history);

    printf("\nadd_line: ls -al\n");

    history.add_line(&history, "ls -al");

    status(&history);

    printf("\nprev:\n");
    history.prev(&history);

    printf("\nprev: %s\n", history.prev(&history));
    status(&history);

    printf("\nprev: %s\n", history.prev(&history));
    status(&history);

    printf("\nprev: %s\n", history.prev(&history));
    status(&history);

    printf("\nnext: %s\n", history.next(&history));
    status(&history);

    printf("\nnext: %s\n", history.next(&history));
    status(&history);

    printf("\nnext: %s\n", history.next(&history));
    status(&history);

    // Down too far
    printf("\nnext: %s\n", history.next(&history));
    status(&history);

    printf("\nnext: %s\n", history.next(&history));
    status(&history);

    for(; history.current_line_pos >= 0; --(history.current_line_pos));
        printf("\nprev: %s\n", history.prev(&history));

    status(&history);

    printf("\nprev: %s\n", history.prev(&history));
    status(&history);
    printf("\nprev: %s\n", history.prev(&history));
    status(&history);
    printf("\nprev: %s\n", history.prev(&history));
    status(&history);

    printf("\nnext: %s\n", history.next(&history));
    status(&history);
    printf("\nnext: %s\n", history.next(&history));
    status(&history);
    printf("\nnext: %s\n", history.next(&history));
    status(&history);
    printf("\nnext: %s\n", history.next(&history));
    status(&history);
    printf("\nnext: %s\n", history.next(&history));
    status(&history);
    printf("\nnext: %s\n", history.next(&history));
    status(&history);
    printf("\nnext: %s\n", history.next(&history));
    status(&history);



    history.free_h(&history);

    return 0;
}

void status(History* h)
{
    printf("\n<status>\n");
    printf("current_line: %s\n", h->current_line);
    printf("current_line_pos: %d\n", h->current_line_pos);
    printf("history_file_name: %s\n", h->history_file_name);
    printf("line_count: %d\n", h->line_count);
    printf("space_available: %d\n", h->space_available);
    printf("</status>\n");
}
