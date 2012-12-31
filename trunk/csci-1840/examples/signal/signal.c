#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

// defines are in : /usr/include/bits/signum.h
// to kill this suspend and do "kill -9"

void func ( int x )
{
   printf ( "got sigint!\n" );
   raise( SIGUSR1 );
}

void foo ( int x )
{
   printf ( "got user 1!\n" );
}

void bar ( int x )
{
   printf ( "alarm!\n" );
   alarm(1);
}

int main()
{
   signal ( SIGINT, func );
   signal ( SIGUSR1, foo );
   signal ( SIGALRM, bar );

   alarm(2);

   while(1)
       ;
   return 0;
}

