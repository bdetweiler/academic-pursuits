#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/time.h>

static struct itimerval timer;

void sigalarm( int signum )
{
   static char x [] = "|/-\\";
   static int n = 0;
   printf ( "\b%c", x[ n % 4 ] );
   fflush( stdout );
   if ( ++n == 80 )
   {
       // make the timer stop
       timer.it_interval.tv_sec = 0;
       timer.it_interval.tv_usec = 0;
       setitimer ( ITIMER_REAL, &timer, NULL );
   }
}

int main()
{
   signal( SIGALRM , sigalarm );

   timer.it_value.tv_sec = 1;
   timer.it_value.tv_usec = 0;

   timer.it_interval.tv_sec = 0;
   timer.it_interval.tv_usec = 250000;

   setitimer ( ITIMER_REAL, &timer, NULL );

   // until the timer is off
   while( timer.it_interval.tv_usec != 0 )
       ;

   printf ( "  ... all done\n" );

   return 0;
}

