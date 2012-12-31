#!/bin/sh
# This is a shell archive (produced by GNU sharutils 4.2.1).
# To extract the files from this archive, save it to some FILE, remove
# everything before the `!/bin/sh' line above, then type `sh FILE'.
#
# Made on 2005-09-28 14:54 CDT by <bdetweiler@phoenix.unomaha.edu>.
# Source directory was `/home/bdetweiler/csci1840/program4'.
#
# Existing files will *not* be overwritten unless `-c' is specified.
#
# This shar contains:
# length mode       name
# ------ ---------- ------------------------------------------
#     95 -rw-r--r-- calc.c
#    370 -rw-r--r-- main.c
#   2579 -rw-r--r-- stack.c
#    676 -rw-r--r-- stack.h
#    255 -rw-r--r-- Makefile
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
if mkdir _sh18463; then
  $echo 'x -' 'creating lock directory'
else
  $echo 'failed to create lock directory'
  exit 1
fi
# ============= calc.c ==============
if test -f 'calc.c' && test "$first_param" != -c; then
  $echo 'x -' SKIPPING 'calc.c' '(file already exists)'
else
  $echo 'x -' extracting 'calc.c' '(text)'
  sed 's/^X//' << 'SHAR_EOF' > 'calc.c' &&
#include<stdio.h>
#include<cstdlib.h>
X
#include"stack.h"
X
int main(int argc, char** argv)
{
}
X
SHAR_EOF
  (set 20 05 09 27 15 18 07 'calc.c'; eval "$shar_touch") &&
  chmod 0644 'calc.c' ||
  $echo 'restore of' 'calc.c' 'failed'
  if ( md5sum --help 2>&1 | grep 'sage: md5sum \[' ) >/dev/null 2>&1 \
  && ( md5sum --version 2>&1 | grep -v 'textutils 1.12' ) >/dev/null; then
    md5sum -c << SHAR_EOF >/dev/null 2>&1 \
    || $echo 'calc.c:' 'MD5 check failed'
82ed948e7d6c8f32cf409eacc765e6ec  calc.c
SHAR_EOF
  else
    shar_count="`LC_ALL= LC_CTYPE= LANG= wc -c < 'calc.c'`"
    test 95 -eq "$shar_count" ||
    $echo 'calc.c:' 'original size' '95,' 'current size' "$shar_count!"
  fi
fi
# ============= main.c ==============
if test -f 'main.c' && test "$first_param" != -c; then
  $echo 'x -' SKIPPING 'main.c' '(file already exists)'
else
  $echo 'x -' extracting 'main.c' '(text)'
  sed 's/^X//' << 'SHAR_EOF' > 'main.c' &&
#include<stdio.h>
#include<stdlib.h>
X
#include"stack.h"
X
int main(void)
{
X    float i = 0.0;
X    Stack s;
X    stack_init(&s);
X
X    for(i = 0.0; i <= 24; ++i)
X    {
X        printf("Push it! %f\n", i);
X        s.push(&s, i);
X        printf("PEEK A BOO! %f\n", s.peek(&s));
X    }
X
X    while(!s.empty(&s))
X    {
X        printf("%f\n", s.pop(&s));
X    }
X    
X    return 0;
}
SHAR_EOF
  (set 20 05 09 28 14 51 47 'main.c'; eval "$shar_touch") &&
  chmod 0644 'main.c' ||
  $echo 'restore of' 'main.c' 'failed'
  if ( md5sum --help 2>&1 | grep 'sage: md5sum \[' ) >/dev/null 2>&1 \
  && ( md5sum --version 2>&1 | grep -v 'textutils 1.12' ) >/dev/null; then
    md5sum -c << SHAR_EOF >/dev/null 2>&1 \
    || $echo 'main.c:' 'MD5 check failed'
0c6196e2730617b92be61f7117a22729  main.c
SHAR_EOF
  else
    shar_count="`LC_ALL= LC_CTYPE= LANG= wc -c < 'main.c'`"
    test 370 -eq "$shar_count" ||
    $echo 'main.c:' 'original size' '370,' 'current size' "$shar_count!"
  fi
fi
# ============= stack.c ==============
if test -f 'stack.c' && test "$first_param" != -c; then
  $echo 'x -' SKIPPING 'stack.c' '(file already exists)'
else
  $echo 'x -' extracting 'stack.c' '(text)'
  sed 's/^X//' << 'SHAR_EOF' > 'stack.c' &&
#include"stack.h"
X
/*
X 
#include<stdio.h>
#include<stdlib.h>
X
typedef struct stack
{
X    // function pointers 
X    void  (*free)(  struct stack * );
X    int   (*empty)( struct stack * );
X    int   (*full)(  struct stack * );
X    void  (*push)(  struct stack *, const float );
X    float (*pop)(   struct stack * );
X    float (*peek)(  struct stack * );
X
X    // data elements for storage
X    float* arr;
X    int    size;
X    int    top;
} Stack;
X
void  stack_init( Stack*);
void  stack_free( Stack*);
int   stack_empty(Stack*);
int   stack_full( Stack*);
void  stack_push( Stack*, const float);
float stack_pop(  Stack*);
float stack_peek( Stack*);
X
#define SNUM 5
*/
X
void stack_init(Stack* s)
{
X    s->size = SNUM;
X    s->arr  = malloc(sizeof(int) * s->size);
X    s->top  = 0;
X
X    // Function pointers:
X    s->free    = stack_free;
X    s->empty   = stack_empty;
X    s->full    = stack_full;
X    s->push    = stack_push;
X    s->pop     = stack_pop;
X    s->peek    = stack_peek;
}
X
void stack_free(Stack* s)
{
X    free(s->arr);
}
X
int stack_empty(Stack* s)
{
X    return(s->top <= 0);
}
X
int stack_full(Stack* s)
{
X    return(s->top >= s->size);
}
X
void stack_push(Stack* s, const float foo)
{
X    // If full
X    if(stack_full(s))    
X    {
X        int    nsize = s->size + SNUM;
X        float* narr  = malloc(sizeof(int) * nsize);
X
#if 0
X        int i;
X        for ( i = 0 ; i < q->size ; ++i )
X            narr[i] = q->arr[ ( q->front + i ) % q->size ];
#else
X        /* copy from the front of arr, to the 0 index in narr */
X        memcpy(narr, s->arr + s->top,
X                (s->size - s->top) * sizeof(int));
X        /* copy the front elements from arr in the rest of narr */
X        memcpy(narr + (s->size - s->top) , s->arr,
X                s->top * sizeof(int));
#endif
X        /* ToDo: Check this part. Not too sure, especially
X         * about the s->top part.
X         */
X        free(s->arr);
X        s->arr   = narr;
X        s->size  = nsize;
X        
X        // WTF???
X        // s->top   = s->count;
X    }
X    s->arr[(s->top)++] = foo;
X    ++(s->count);
}
X
float stack_pop(Stack* s)
{
X    int rval;
X    if(stack_empty(s))
X    {
X        fprintf(stderr, "pop error!\n" );
X        exit(EXIT_FAILURE);
X    }
X    rval = s->arr[--(s->top)];
X
X    // Why do we do this step?
X    s->top %= s->size;
X
X    --(s->count);
X    return rval;
}
X
float stack_peek(Stack* s)
{
X    int rval;
X
X    if(stack_empty(s))
X    {
X        fprintf(stderr, "pop error!\n" );
X        exit(EXIT_FAILURE);
X    }
X
X    rval = s->arr[(s->top) - 1];
X
X    // Why do we do this step?
X    return rval;
}
X
SHAR_EOF
  (set 20 05 09 28 14 52 38 'stack.c'; eval "$shar_touch") &&
  chmod 0644 'stack.c' ||
  $echo 'restore of' 'stack.c' 'failed'
  if ( md5sum --help 2>&1 | grep 'sage: md5sum \[' ) >/dev/null 2>&1 \
  && ( md5sum --version 2>&1 | grep -v 'textutils 1.12' ) >/dev/null; then
    md5sum -c << SHAR_EOF >/dev/null 2>&1 \
    || $echo 'stack.c:' 'MD5 check failed'
13809d1eacd601d836cc68251a0f9a65  stack.c
SHAR_EOF
  else
    shar_count="`LC_ALL= LC_CTYPE= LANG= wc -c < 'stack.c'`"
    test 2579 -eq "$shar_count" ||
    $echo 'stack.c:' 'original size' '2579,' 'current size' "$shar_count!"
  fi
fi
# ============= stack.h ==============
if test -f 'stack.h' && test "$first_param" != -c; then
  $echo 'x -' SKIPPING 'stack.h' '(file already exists)'
else
  $echo 'x -' extracting 'stack.h' '(text)'
  sed 's/^X//' << 'SHAR_EOF' > 'stack.h' &&
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
X
typedef struct stack
{
X    // function pointers 
X    void  (*free)(  struct stack * );
X    int   (*empty)( struct stack * );
X    int   (*full)(  struct stack * );
X    void  (*push)(  struct stack *, const float );
X    float (*pop)(   struct stack * );
X    float (*peek)(  struct stack * );
X
X    // data elements for storage
X    float* arr;
X    int    size;
X    int    top;
X    int    count;
} Stack;
X
void  stack_init( Stack*);
void  stack_free( Stack*);
int   stack_empty(Stack*);
int   stack_full( Stack*);
void  stack_push( Stack*, const float);
float stack_pop(  Stack*);
float stack_peek( Stack*);
X
#define SNUM 5
SHAR_EOF
  (set 20 05 09 28 14 24 30 'stack.h'; eval "$shar_touch") &&
  chmod 0644 'stack.h' ||
  $echo 'restore of' 'stack.h' 'failed'
  if ( md5sum --help 2>&1 | grep 'sage: md5sum \[' ) >/dev/null 2>&1 \
  && ( md5sum --version 2>&1 | grep -v 'textutils 1.12' ) >/dev/null; then
    md5sum -c << SHAR_EOF >/dev/null 2>&1 \
    || $echo 'stack.h:' 'MD5 check failed'
e185539e5c81e2f93b0d1e4394757e87  stack.h
SHAR_EOF
  else
    shar_count="`LC_ALL= LC_CTYPE= LANG= wc -c < 'stack.h'`"
    test 676 -eq "$shar_count" ||
    $echo 'stack.h:' 'original size' '676,' 'current size' "$shar_count!"
  fi
fi
# ============= Makefile ==============
if test -f 'Makefile' && test "$first_param" != -c; then
  $echo 'x -' SKIPPING 'Makefile' '(file already exists)'
else
  $echo 'x -' extracting 'Makefile' '(text)'
  sed 's/^X//' << 'SHAR_EOF' > 'Makefile' &&
TARGETS=main
X
CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall
X
all: $(TARGETS)
clean:
X	rm -f *.o $(TARGETS)
X
# to use the implicit linking the root of the target
# MUST match the first dependancy
X
X
main: stack.o main.o
stack.o: main.c stack.h 
stack.o: stack.c stack.h
SHAR_EOF
  (set 20 05 09 28 14 06 13 'Makefile'; eval "$shar_touch") &&
  chmod 0644 'Makefile' ||
  $echo 'restore of' 'Makefile' 'failed'
  if ( md5sum --help 2>&1 | grep 'sage: md5sum \[' ) >/dev/null 2>&1 \
  && ( md5sum --version 2>&1 | grep -v 'textutils 1.12' ) >/dev/null; then
    md5sum -c << SHAR_EOF >/dev/null 2>&1 \
    || $echo 'Makefile:' 'MD5 check failed'
9ee6fb9eb6f182fa99ee23b3313f2561  Makefile
SHAR_EOF
  else
    shar_count="`LC_ALL= LC_CTYPE= LANG= wc -c < 'Makefile'`"
    test 255 -eq "$shar_count" ||
    $echo 'Makefile:' 'original size' '255,' 'current size' "$shar_count!"
  fi
fi
rm -fr _sh18463
exit 0
