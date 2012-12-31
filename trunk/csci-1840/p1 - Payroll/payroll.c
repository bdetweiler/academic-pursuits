#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* By Brian Detweiler
 * Advanced Topics in C
 * CSCI 1840
 * Program Description: Read in a list of names, hours, and rates, then
 * print them out along with their entitled pay in an ordered format. 
 */
int main()
{
    /* Size of array to store the name */
    const int NAME_SIZE = 20;

    float     hours     = 0.0;
    float     rate      = 0.0;
    char      name[NAME_SIZE]; 
    /* Print header */
    printf("%-20s %-10s %-10s %-10s\n", "name", "hours", "rate", "pay");

    /* Take input from stdin */
    while(scanf("%f %f\n", &hours, &rate) != EOF && 
          fgets(name, sizeof(name), stdin))
    { 
        char *ptr = strchr(name, '\n');
        if(ptr)
            *ptr = '\0';
        /* It puts the lotion on its skin, */

        printf("%-20s %-10.2f %-10.2f %-10.2f\n", 
               name, hours, rate, (hours * rate));

        /* or else it gets the hose again. */
    }
    return 0;
}

