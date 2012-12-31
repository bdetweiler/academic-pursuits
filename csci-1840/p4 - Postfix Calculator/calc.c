/******************************************************************************
 * Filename: calc.c                                                           *
 * Author:   Brian Detweiler                                                  *
 * Notes:    Takes an input from stdin (which must be formatted in Postfix or *
 *           Reverse Polish Notation. Right now, it only does basic           *
 *           operators: + - * / ^                                             *
 * Examples: Input:  3 4 2 * 1 5 - 2 ^ / +                                    *
 *           Output: 3.5                                                      *
 *****************************************************************************/


/* Included with stack.h
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<curses.h>
#include<ctype.h>
#include<math.h>
*/

#include"stack.h"

int main(void)
{
    // This will get the input
    char  ch;

    // This will hold the final calculation
    float numFinal = 0.0;

    // These will hold our temporary numbers
    float num1     = 0.0;
    float num2     = 0.0;
    
    // Char stack 
    Stack s;

    // Constructor for the stack
    stack_init(&s);

    // Read from stdin until it fails (there are no characters left)
    while((ch = getc(stdin)) != EOF)  
    {
        /* If the character is a digit, ungetc() (act like
         * we never read it, and read it out in its entirety
         */
        if(isdigit(ch))
        {
            numFinal = 0;

            // Put the character fish back into the stream
            ungetc(ch, stdin);

            /* Loop until we hit the end of the number. 
             * This is to handle multi-digit numbers.
             */
            while((ch = getc(stdin)) && isdigit(ch))
            {
                // Advance the decimal one place to the right
                numFinal *= 10;

                // Tack the number on to the end
                numFinal += (float)atoi(&ch);
            }
            // Push the final number onto the stack
            s.push(&s, numFinal);
        }
        // if it is an operator
        else if(strchr("*/+-^", ch))
        {
            /* While the operator on the top of the stack is of
             * equal or greater precedence, pop it. Then place
             * the operator on the top of the stack 
             */
            
            // Power
            if(ch == '^')            
            {
                // e.g. 2 3 ^ = (2 * 2 * 2) or 8
                num1     = s.pop(&s);
                num2     = s.pop(&s);
                numFinal = (float)(powf(num2, num1));
                s.push(&s, numFinal);
            }
            else if(ch == '*' || ch == '/')
            {
                // Multiply
                if(ch == '*')
                {
                    numFinal = s.pop(&s) * s.pop(&s);
                }
                // Divide
                else
                {
                    num1     = s.pop(&s);
                    
                    // Divide by Zero
                    if(num1 == 0)
                    {
                        fprintf(stderr, "Can't divide by zero\n");
                        exit(1);
                    }

                    // All is good. Divide the two.
                    numFinal = s.pop(&s) / num1;
                }

                // Push it on the stack
                s.push(&s, numFinal);
            }
            else if(ch == '+' || ch == '-')
            {
                // Add
                if(ch == '+')
                {
                    numFinal  = s.pop(&s) + s.pop(&s);
                }
                // Subtract
                else
                {
                    num1     = s.pop(&s);
                    numFinal = s.pop(&s) - num1;
                }

                // Push it on the stack
                s.push(&s, numFinal);
            }
        } // else if(strchr("*/+-^", ch))
    } // while((ch = getc(stdin)) != EOF)

    // Finish outputting the rest of the stack 
    while(s.empty(&s) == 0)
    {
        printf("%f \n", s.pop(&s));
    }

    // Destructor
    s.free(&s);

    return 0;
}
