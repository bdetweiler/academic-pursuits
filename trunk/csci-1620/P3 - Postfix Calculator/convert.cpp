/******************************************************************************
 * Filename: convert.cpp                                                      *
 * Author:   Brian Detweiler                                                  *
 * Notes:    Takes an Infix number and converts it to Reverse Polish          *
 *           Notation.                                                        *
 * Examples: Input:  3+4*2/(1-5)^2                                            *
 *           Output: 3 4 2 * 1 5 - 2 ^ / +                                    *
 *****************************************************************************/ 

#include<iostream>
using namespace std;

#include<cstring>
using std::strchr;

#include"stack.h"

int main(void)
{
    Stack<char> stack;

    stack.push('(');

    char ch;
    while(cin >> ch)
    {
        if(isdigit(ch))
        {
            cin.putback(ch);
            int num;
            cin >> num;
            cout << ch << ' ';
        }
        else if(strchr("*/+-^", ch))
        {
            if(ch == '^')
            {
                while(stack.peek() == '^')
                {
                    cout << stack.pop() << ' ';
                }
                stack.push(ch);
            }
            else if(ch == '*' || ch == '/')
            {
                while(stack.peek() == '^' ||
                      stack.peek() == '*' ||
                      stack.peek() == '/')
                {
                    cout << stack.pop() << ' ';
                }
                stack.push(ch);
            }
            else if(ch == '+' || ch == '-')
            {
                while(stack.peek() == '^' ||
                      stack.peek() == '*' ||
                      stack.peek() == '/' ||
                      stack.peek() == '+' ||
                      stack.peek() == '-')
                {
                    cout << stack.pop() << ' ';
                }
                stack.push(ch);
            }
        } // else if(strchr("*/+-^", ch))
        
        else if(strchr("(", ch))
        {
            stack.push(ch);
        } 
        
        else if(strchr(")", ch))
        {
            while(stack.peek() != '(')
            {
                cout << stack.pop() << ' ';
            }
            stack.pop();
        }
    } // while(cin >> ch)

    while((!stack.empty()) && (stack.peek() != '('))
    {
        cout << stack.pop() << ' ';
    }

    return 0;
}

