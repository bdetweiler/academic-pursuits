/******************************************************************************
 * Filename: calc.cpp                                                         *
 * Author:   Brian Detweiler                                                  *
 * Notes:    Takes an input from stdin (which must be formatted in Postfix or *
 *           Reverse Polish Notation. Right now, it only does basic           *
 *           operators: ( + - * / ^ )                                         *
 * Examples: Input:  3 4 2 * 1 5 - 2 ^ / +                                    *
 *           Output: 3.5                                                      *
 *****************************************************************************/

#include<iostream>
using namespace std;

#include<cstring>
using std::strchr;

#include<cmath>
using std::pow;

#include"stack.h"

int main(void)
{
    /* Templated char stack */
    Stack<float> stack;

    /* Start with an opening paren */
    stack.push('(');

    char ch;
    /* Read in from cin until it fails (there are no characters left) */
    while(cin >> ch)  
    {
        /* If the character is a digit, putback() (act like
         * we never read it, and read it out in its entirety
         */
        if(isdigit(ch))
        {
            cin.putback(ch);
            float num;
            cin >> num;
            stack.push(num);
        }
        else if(strchr("*/+-^", ch)) // if it is an operator
        {
            /* While the operator on the top of the stack is of
             * equal or greater precedence, pop it. Then place
             * the operator on the top of the stack 
             */
            if(ch == '^')            
            {
                float num;
                float num2 = stack.pop();
                float num1 = stack.pop();
                num = static_cast<float>(pow(num1, num2));
                stack.push(num);
            }
            else if(ch == '*' || ch == '/')
            {
                float num;
                if(ch == '*')
                {
                    num = stack.pop() * stack.pop();
                }
                else
                {
                    float num2 = stack.pop();
                    num = stack.pop() / num2;
                }
                stack.push(num);
            }
            else if(ch == '+' || ch == '-')
            {
                float num;
                if(ch == '+')
                {
                    num = stack.pop() + stack.pop();
                }
                else
                {
                    float num2 = stack.pop();
                    num = stack.pop() - num2;
                }
                stack.push(num);
            }
        } // else if(strchr("*/+-^", ch))
        
    } // while(cin >> ch)

    /* Finish outputting the rest of the stack and 
     * discard the first left paren
     */
    while((!stack.empty()) && (stack.peek() != '('))
    {
        cout << stack.pop() << ' ' << endl;
    }

    return 0;
}

