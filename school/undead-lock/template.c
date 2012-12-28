/*********************************************/
/* Partial code for programming assignment 2 */
/*********************************************/
#include <stdio.h>
#include <fcntl.h>

main()
{
    int progs[10][25][2];	/* 10 procs, 25 insts/process, 2 ints/inst */
    int ninst[10];		/* number of instructions per proc */

    int np, nr;			/* number of procs, number of resources */
    int i, j;
    int caseno;			/* simulation number */

    for(caseno=1;;caseno++) {
	scanf("%d%d",&np,&nr);		/* read # procs, # resources */
	if (np == 0) exit(0);		/* quit if we're done */

	for (i=0;i<np;i++) {		/* read "program" for process i */
	    scanf("%d",&ninst[i]);	/* read # of "instructions" */
	    for (j=0;j<ninst[i];j++)	/* read the instructions */
		scanf("%d%d",
		    &progs[i][j][0],		/* type of instruction */
		    &progs[i][j][1]);		/* parameter */
	}

	/* Simulation takes place here */

	/*---------------------------------------------*/
	/* In this template, we just display the input */
	/* to verify it was read correctly.            */
	/*---------------------------------------------*/
	printf("Simulation case %d\n", caseno);
	printf("Number of processes = %d\n", np);
	printf("Number of resources = %d\n", nr);
	for (i=0;i<np;i++) {
	    printf("Process %d: ", i);
	    for (j=0;j<ninst[i];j++) printf("(%d,%d)  ",
		progs[i][j][0], progs[i][j][1]);
	    printf("\n");
	}
	printf("\n");
    }
}
