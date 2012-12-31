/*
 * socket_shared
 * main.c
 * By Brian Detweiler
 *
 * This is a simple server program that demonstrates the
 * use of sockets. It takes in input over a tcp connection
 * and formats the input to make it suitable for an Enigma
 * machine to encrypt.
 */


#include<time.h>
#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

#include"socket.h"

char* parse(const char*);

int main(int argc, char** argv)
{
    int flag = 1;
    TCP_Server s;
    if(argc < 2)
    {
        printf("Usage: %s [port]\n\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    server_init(&s, atoi(argv[1]));

    s.sopen(&s);
    s.sbind(&s);
    s.slisten(&s);
    while(1)
    {
        s.saccept(&s);
        while(flag)
        {
            s.sread(&s);
            if(strlen(s.buf) > 0 && strncasecmp("quit\r\n", s.buf, BUFSIZ - 1) != 0)
            {
                strncpy(s.buf, parse(s.buf), BUFSIZ -1);
                s.swrite(&s);
            }
            else
            {
                flag = 0;
            }
        }
        flag = 1;

        s.sclose(&s, s.sd2);
    }
    // ToDo: catch close signal
    s.sclose(&s, s.sd);
    
    return 0;
}

/*
 * parse()
 * --
 * Input:   const char*
 * Output:  None
 * Return   char*
 * Notes:   This takes care of all the parsing
 *          stuff. First, we uppercase everything,
 *          then, we put in our Xs and stuff, and
 *          finally, we put in the spacing.
 */
char* parse(const char* buf)
{
    // i is for buf, and it increments normally
    int         i    = 0;
    // j is for tmp, and it may double increment
    int         j    = 0;

    // This is a two step process. So we have two buffers.
    char        tmp[BUFSIZ];
    static char tmp2[BUFSIZ];
    
    // Clear both buffers. 
    memset(tmp2, 0, BUFSIZ);
    memset(tmp,  0, BUFSIZ);
    while(buf[i] != '\0')
    {
        // Step 1a: TO UPPERCASE
        if(isalpha(buf[i]))
            tmp[j] = toupper(buf[i]);
        // Step 1b: Throw in Xs and shit
        else
        {
            /*
             * Note: This method isn't pretty, but it is
             * consistant and it works. And if it ain't broke,
             * I ain't fixin' shit.
             */
            switch(buf[i])
            {
                case '0':
                    tmp[j]   = 'Z';
                    tmp[++j] = 'E';
                    tmp[++j] = 'R';
                    tmp[++j] = 'O';
                    break;
                case '1':
                    tmp[j]   = 'O';
                    tmp[++j] = 'N';
                    tmp[++j] = 'E';
                    break;
                case '2':
                    tmp[j]   = 'T';
                    tmp[++j] = 'W';
                    tmp[++j] = 'O';
                    break;
                case '3':
                    tmp[j]   = 'T';
                    tmp[++j] = 'H';
                    tmp[++j] = 'R';
                    tmp[++j] = 'E';
                    tmp[++j] = 'E';
                    break;
                case '4':
                    tmp[j]   = 'F';
                    tmp[++j] = 'O';
                    tmp[++j] = 'U';
                    tmp[++j] = 'R';
                    break;
                case '5':
                    tmp[j]   = 'F';
                    tmp[++j] = 'I';
                    tmp[++j] = 'V';
                    tmp[++j] = 'E';
                    break;
                case '6':
                    tmp[j]   = 'S';
                    tmp[++j] = 'I';
                    tmp[++j] = 'X';
                    break;
                case '7':
                    tmp[j]   = 'S';
                    tmp[++j] = 'E';
                    tmp[++j] = 'V';
                    tmp[++j] = 'E';
                    tmp[++j] = 'N';
                    break;
               case '8':
                    tmp[j]   = 'E';
                    tmp[++j] = 'I';
                    tmp[++j] = 'G';
                    tmp[++j] = 'H';
                    tmp[++j] = 'T';
                    break;
               case '9':
                    tmp[j]   = 'N';
                    tmp[++j] = 'I';
                    tmp[++j] = 'N';
                    tmp[++j] = 'E';
                    break;
                // '\r'
                case 13:
                    tmp[j]   = 'X';
                    break;
                // '\n'
                case 10:
                    ++j;
                    break;
                // Space
                case 32: 
                // Period
                case 46:
                    tmp[j]   = 'X';
                    break;
                // Colon
                case 58:
                    tmp[j]   = 'X';
                    tmp[++j] = 'X';
                    break;
                // Question Mark
                case 63:
                    tmp[j]   = 'U';
                    tmp[++j] = 'D';
                    break;
                // Comma
                case 44:
                    tmp[j]   = 'Y';
                    break;
                // Forward Slash
                case 47:
                // Backward Slash
                case 92:
                // Dash
                case 45:
                // Underscore
                case 95:
                    tmp[j]   = 'Y';
                    tmp[++j] = 'Y';
                    break;
                // Left Paren 
                case 40:
                // Right Parens
                case 41:
                    tmp[j]   = 'K';
                    tmp[++j] = 'K';
                    break;
                default:
                    tmp[j]   = buf[i];
            } // End Switch
        } // End else
        ++i;
        ++j;
    }
    // Get the null in there
    tmp[j] = buf[i];
  
    // Reset counters 
    i = 0;
    j = 0; 

    // Step 2: Spacing!
    while(tmp[i] != '\0')
    {
        if(i > 0 && (i % 50) == 0)
        {
            tmp2[j]   = '\r';
            tmp2[++j] = '\n';
            tmp2[++j] = tmp[i];
        }
        else if(i > 0 && (i % 5) == 0)
        {
            tmp2[j]   = ' ';
            tmp2[++j] = tmp[i];
        }
        else
        {
            tmp2[j]   = tmp[i];
        }
        ++i;
        ++j;
    }
    tmp2[j]   = '\r';
    tmp2[++j] = '\n';
    tmp2[++j] = '\0';
    return tmp2;
    /* Robotic Chuck Norris owes you NOTHING!" */
}



