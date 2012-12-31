#include<stdio.h>
#include<stdlib.h>
// fork
#include <sys/types.h>
#include <unistd.h>
// wait
#include <sys/wait.h>


int main( int argc, char * argv[], char * envp [] )
{
   printf ( "before fork\n" );
   pid_t pid = fork();
   int status;
   char * cmd[] = { "ls", "-lF", "/tmp", NULL };
   char * env[] = { NULL };

   if ( pid == -1 )
   {
       printf ( "this is bad\n" );
       exit( 1 );
   }
   if ( pid == 0 )
   {
       printf ( "I am the child\n" );
       sleep(1);   /* just to show waitpid works */
       execve( "/bin/ls", cmd, env );
   }
   else
   {
       printf ( "my child pid is %d\n", pid );
       waitpid(pid, &status, 0 );
       printf ( "the child is done\n" );
   }

   return 0;
}
