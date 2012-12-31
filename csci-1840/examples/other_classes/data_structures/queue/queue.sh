#!/bin/sh
# This is a shell archive (produced by GNU sharutils 4.2.1).
# To extract the files from this archive, save it to some FILE, remove
# everything before the `!/bin/sh' line above, then type `sh FILE'.
#
# Made on 2005-09-08 17:12 CDT by <jclark@phoenix.unomaha.edu>.
# Source directory was `/home/jclark/class_code/fall05/C_class/queue'.
#
# Existing files will *not* be overwritten unless `-c' is specified.
#
# This shar contains:
# length mode       name
# ------ ---------- ------------------------------------------
#    255 -rw------- Makefile
#    511 -rw------- foo.cpp
#    456 -rw------- main.c
#   1494 -rw------- queue.c
#    289 -rw------- queue.h
#
save_IFS="${IFS}"
IFS="${IFS}:"
gettext_dir=FAILED
locale_dir=FAILED
first_param="$1"
for dir in $PATH
do
 if test "$gettext_dir" = FAILED && test -f $dir/gettext \
    && ($dir/gettext --version >/dev/null 2>&1)
 then
   set `$dir/gettext --version 2>&1`
   if test "$3" = GNU
   then
     gettext_dir=$dir
   fi
 fi
 if test "$locale_dir" = FAILED && test -f $dir/shar \
    && ($dir/shar --print-text-domain-dir >/dev/null 2>&1)
 then
   locale_dir=`$dir/shar --print-text-domain-dir`
 fi
done
IFS="$save_IFS"
if test "$locale_dir" = FAILED || test "$gettext_dir" = FAILED
then
 echo=echo
else
 TEXTDOMAINDIR=$locale_dir
 export TEXTDOMAINDIR
 TEXTDOMAIN=sharutils
 export TEXTDOMAIN
 echo="$gettext_dir/gettext -s"
fi
if touch -am -t 200112312359.59 $$.touch >/dev/null 2>&1 && test ! -f 200112312359.59 -a -f $$.touch; then
 shar_touch='touch -am -t $1$2$3$4$5$6.$7 "$8"'
elif touch -am 123123592001.59 $$.touch >/dev/null 2>&1 && test ! -f 123123592001.59 -a ! -f 123123592001.5 -a -f $$.touch; then
 shar_touch='touch -am $3$4$5$6$1$2.$7 "$8"'
elif touch -am 1231235901 $$.touch >/dev/null 2>&1 && test ! -f 1231235901 -a -f $$.touch; then
 shar_touch='touch -am $3$4$5$6$2 "$8"'
else
 shar_touch=:
 echo
 $echo 'WARNING: not restoring timestamps.  Consider getting and'
 $echo "installing GNU \`touch', distributed in GNU File Utilities..."
 echo
fi
rm -f 200112312359.59 123123592001.59 123123592001.5 1231235901 $$.touch
#
if mkdir _sh20928; then
 $echo 'x -' 'creating lock directory'
else
 $echo 'failed to create lock directory'
 exit 1
fi
# ============= Makefile ==============
if test -f 'Makefile' && test "$first_param" != -c; then
 $echo 'x -' SKIPPING 'Makefile' '(file already exists)'
else
 $echo 'x -' extracting 'Makefile' '(text)'
 sed 's/^X//' << 'SHAR_EOF' > 'Makefile' &&
X
TARGETS=queue
X
CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall
X
all: $(TARGETS)
clean:
X       rm -f *.o $(TARGETS)
X
# to use the implicit linking the root of the target
# MUST match the first dependancy
X
queue: queue.o main.o
main.o: main.c queue.h
queue.o: queue.c queue.h
SHAR_EOF
 (set 20 05 09 08 16 54 38 'Makefile'; eval "$shar_touch") &&
 chmod 0600 'Makefile' ||
 $echo 'restore of' 'Makefile' 'failed'
 if ( md5sum --help 2>&1 | grep 'sage: md5sum \[' ) >/dev/null 2>&1 \
 && ( md5sum --version 2>&1 | grep -v 'textutils 1.12' ) >/dev/null; then
   md5sum -c << SHAR_EOF >/dev/null 2>&1 \
   || $echo 'Makefile:' 'MD5 check failed'
f1158b39a6156ff284db42f9048e6c8f  Makefile
SHAR_EOF
 else
   shar_count="`LC_ALL= LC_CTYPE= LANG= wc -c < 'Makefile'`"
   test 255 -eq "$shar_count" ||
   $echo 'Makefile:' 'original size' '255,' 'current size' "$shar_count!"
 fi
fi
# ============= foo.cpp ==============
if test -f 'foo.cpp' && test "$first_param" != -c; then
 $echo 'x -' SKIPPING 'foo.cpp' '(file already exists)'
else
 $echo 'x -' extracting 'foo.cpp' '(text)'
 sed 's/^X//' << 'SHAR_EOF' > 'foo.cpp' &&
X
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
#include"queue.h"
X
int main()
{
X    Queue q;
X    int i;
X
X    init_queue( &q );
X
X    for ( i = 0 ; i < 10 ; ++i )
X        enqueue( &q, i );
X
X    for ( i = 0 ; i < 5 ; ++i )
X        printf ( "%d ", dequeue( &q ) );
X    printf ( "\n");
X
X    for ( i = 0 ; i < 20 ; ++i )
X        enqueue( &q, i + 10 );
X
X    while ( !queue_empty( &q ) )
X        printf ( "%d ", dequeue( &q ) );
X    printf ( "\n");
X
X
X    free_queue( &q );
X
X    return 0;
X
}
SHAR_EOF
 (set 20 05 09 08 17 06 21 'foo.cpp'; eval "$shar_touch") &&
 chmod 0600 'foo.cpp' ||
 $echo 'restore of' 'foo.cpp' 'failed'
 if ( md5sum --help 2>&1 | grep 'sage: md5sum \[' ) >/dev/null 2>&1 \
 && ( md5sum --version 2>&1 | grep -v 'textutils 1.12' ) >/dev/null; then
   md5sum -c << SHAR_EOF >/dev/null 2>&1 \
   || $echo 'foo.cpp:' 'MD5 check failed'
0ae937f1663d5e514af918303bf5c310  foo.cpp
SHAR_EOF
 else
   shar_count="`LC_ALL= LC_CTYPE= LANG= wc -c < 'foo.cpp'`"
   test 511 -eq "$shar_count" ||
   $echo 'foo.cpp:' 'original size' '511,' 'current size' "$shar_count!"
 fi
fi
# ============= main.c ==============
if test -f 'main.c' && test "$first_param" != -c; then
 $echo 'x -' SKIPPING 'main.c' '(file already exists)'
else
 $echo 'x -' extracting 'main.c' '(text)'
 sed 's/^X//' << 'SHAR_EOF' > 'main.c' &&
X
#include<stdio.h>
#include"queue.h"
X
X
int main()
{
X    Queue q;
X    int i;
X
X    init_queue( &q );
X
X    for ( i = 0 ; i < 10 ; ++i )
X        enqueue( &q, i );
X
X    for ( i = 0 ; i < 5 ; ++i )
X        printf ( "%d ", dequeue( &q ) );
X    printf ( "\n");
X
X    for ( i = 0 ; i < 20 ; ++i )
X        enqueue( &q, i + 10 );
X
X    while ( !queue_empty( &q ) )
X        printf ( "%d ", dequeue( &q ) );
X    printf ( "\n");
X
X
X    free_queue( &q );
X
X    return 0;
}
X
X
SHAR_EOF
 (set 20 05 09 08 16 57 32 'main.c'; eval "$shar_touch") &&
 chmod 0600 'main.c' ||
 $echo 'restore of' 'main.c' 'failed'
 if ( md5sum --help 2>&1 | grep 'sage: md5sum \[' ) >/dev/null 2>&1 \
 && ( md5sum --version 2>&1 | grep -v 'textutils 1.12' ) >/dev/null; then
   md5sum -c << SHAR_EOF >/dev/null 2>&1 \
   || $echo 'main.c:' 'MD5 check failed'
f2631fe872d82aa8178f78cf9130c4e2  main.c
SHAR_EOF
 else
   shar_count="`LC_ALL= LC_CTYPE= LANG= wc -c < 'main.c'`"
   test 456 -eq "$shar_count" ||
   $echo 'main.c:' 'original size' '456,' 'current size' "$shar_count!"
 fi
fi
# ============= queue.c ==============
if test -f 'queue.c' && test "$first_param" != -c; then
 $echo 'x -' SKIPPING 'queue.c' '(file already exists)'
else
 $echo 'x -' extracting 'queue.c' '(text)'
 sed 's/^X//' << 'SHAR_EOF' > 'queue.c' &&
X
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
X
#include"queue.h"
X
X
void init_queue ( Queue * q )
{
X    q->size = QNUM;
X    q->arr = ( int * ) malloc ( sizeof ( int ) * q->size );
X    q->front = 0;
X    q->back = 0;
X    q->count = 0;
}
X
void free_queue ( Queue * q )
{
X    free( q->arr );
}
X
int queue_empty ( Queue * q )
{
X    return ( q->count <= 0 );
}
X
X
void enqueue ( Queue * q, const int foo )
{
X    if ( q->count >= q->size )    /* if full */
X    {
X        int nsize = q->size + QNUM;
X        int * narr = ( int * ) malloc ( sizeof ( int ) * nsize );
X
#if 0
X        int i;
X        for ( i = 0 ; i < q->size ; ++i )
X            narr[i] = q->arr[ ( q->front + i ) % q->size ];
#else
X        /* copy from the front of arr, to the 0 index in narr */
X        memcpy( narr, q->arr + q->front,
X                ( q->size - q->front ) * sizeof ( int ) );
X        /* copy the front elements from arr in the rest of narr */
X        memcpy( narr + ( q->size - q->front ) , q->arr,
X                q->front * sizeof ( int ));
#endif
X        free ( q->arr );
X        q->arr = narr;
X        q->size = nsize;
X        q->front = 0;
X        q->back = q->count;
X    }
X    q->arr[ (q->back)++ ] = foo;
X    q->back %= q->size;
X    ++(q->count);
}
X
int dequeue ( Queue * q )
{
X    int rval;
X    if ( queue_empty( q ) )
X    {
X        fprintf ( stderr, "dequeue error!\n" );
X        exit( 1 );
X    }
X    rval = q->arr[ (q->front)++ ];
X    q->front %= q->size;
X    --(q->count);
X    return rval;
}
X
X
X
X
X
SHAR_EOF
 (set 20 05 09 08 16 50 38 'queue.c'; eval "$shar_touch") &&
 chmod 0600 'queue.c' ||
 $echo 'restore of' 'queue.c' 'failed'
 if ( md5sum --help 2>&1 | grep 'sage: md5sum \[' ) >/dev/null 2>&1 \
 && ( md5sum --version 2>&1 | grep -v 'textutils 1.12' ) >/dev/null; then
   md5sum -c << SHAR_EOF >/dev/null 2>&1 \
   || $echo 'queue.c:' 'MD5 check failed'
8fb3986af2cb027d34534e9064efa5ca  queue.c
SHAR_EOF
 else
   shar_count="`LC_ALL= LC_CTYPE= LANG= wc -c < 'queue.c'`"
   test 1494 -eq "$shar_count" ||
   $echo 'queue.c:' 'original size' '1494,' 'current size' "$shar_count!"
 fi
fi
# ============= queue.h ==============
if test -f 'queue.h' && test "$first_param" != -c; then
 $echo 'x -' SKIPPING 'queue.h' '(file already exists)'
else
 $echo 'x -' extracting 'queue.h' '(text)'
 sed 's/^X//' << 'SHAR_EOF' > 'queue.h' &&
X
extern "C"
{
typedef struct queue
{
X    int size;
X    int * arr;
X    int front;
X    int back;
X    int count;
} Queue ;
X
void init_queue ( Queue * );
void free_queue ( Queue * );
int queue_empty ( Queue * );
void enqueue ( Queue *, const int );
int dequeue ( Queue * );
X
#define QNUM 10
}
SHAR_EOF
 (set 20 05 09 08 17 07 30 'queue.h'; eval "$shar_touch") &&
 chmod 0600 'queue.h' ||
 $echo 'restore of' 'queue.h' 'failed'
 if ( md5sum --help 2>&1 | grep 'sage: md5sum \[' ) >/dev/null 2>&1 \
 && ( md5sum --version 2>&1 | grep -v 'textutils 1.12' ) >/dev/null; then
   md5sum -c << SHAR_EOF >/dev/null 2>&1 \
   || $echo 'queue.h:' 'MD5 check failed'
6fc4432afcbd4249972c07d79d660217  queue.h
SHAR_EOF
 else
   shar_count="`LC_ALL= LC_CTYPE= LANG= wc -c < 'queue.h'`"
   test 289 -eq "$shar_count" ||
   $echo 'queue.h:' 'original size' '289,' 'current size' "$shar_count!"
 fi
fi
rm -fr _sh20928
exit 0
