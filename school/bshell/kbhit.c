#include "kbhit.h"
#include <termios.h>
#include <unistd.h>

static struct termios initial_settings, new_settings;
static char peek_character = (char)-1;

void init_keyboard()
{
    int i = 0;
    i = tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = (cc_t)1;
    new_settings.c_cc[VTIME] = (cc_t)0;
    i = tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
    int i = 0;
    i = tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit()
{
    unsigned char ch;
    ssize_t nread;
    int i = 0;

    if(peek_character != (char)-1) 
        return 1;
    new_settings.c_cc[VMIN] = (cc_t)0;
    i = tcsetattr(0, TCSANOW, &new_settings);
    nread = read(0, &ch, 1);
    new_settings.c_cc[VMIN] = (cc_t)1;
    i = tcsetattr(0, TCSANOW, &new_settings);
    if(nread == 1)
    {
        peek_character = (char)ch;
        return 1;
    }
    return 0;
}

int readch()
{
    char ch;
    ssize_t i = 0;

    if(peek_character != (char)-1)
    {
        ch = peek_character;
        peek_character = (char)-1;
        return (int)ch;
    }
    i = read(0,&ch,1);
    return (int)ch;
}
