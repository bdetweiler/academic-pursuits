#include<iostream.h>
#include<string>

char *soundex (char []);

int main(void)
{

    char mainword[40] = {};
    cout << "Please enter ten (10) words." << endl;
    cout << endl;

    // input words to check.
    for(int i = 1; i <=10; i++)
    {
        cout << "Please enter word number " << i << ": " << flush;
        cin >> mainword;
        cout << "The soundex code for " << mainword << " is "
             << soundex(mainword) << '.' << endl;
        cout << "THIS FUNCTION HAS RUN " << i << " TIMES" << endl;
        cout << "THE WORD IS " << mainword << "." << endl;
    }

    return 0;
}
// input:   A char []
// output:  None
// return:  A char *
char *soundex (char mainword[])
{
    char word[40];
    char temp[40];
    char code[40];
    strcpy(word, mainword);
    static char realcode[6];
    strcpy(realcode, "Z0000");
    if ((word[0] == 'a') || (word[0] == 'b') || (word[0] == 'c') ||
        (word[0] == 'd') || (word[0] == 'e') || (word[0] == 'f') ||
        (word[0] == 'f') || (word[0] == 'g') || (word[0] == 'h') ||
        (word[0] == 'i') || (word[0] == 'j') || (word[0] == 'k') ||
        (word[0] == 'l') || (word[0] == 'm') || (word[0] == 'n') ||
        (word[0] == 'o') || (word[0] == 'p') || (word[0] == 'q') ||
        (word[0] == 'r') || (word[0] == 's') || (word[0] == 't') ||
        (word[0] == 'u') || (word[0] == 'v') || (word[0] == 'w') ||
        (word[0] == 'x') || (word[0] == 'y') || (word[0] == 'z'))
    {
        //code[0] = word[0];
    char code[40] = {};

        int b = 1;
        for (int a = 1; (word[a] != '\0') || (code[b] != '\0'); ++a)
        {

                if ((word[a] == 'b') || (word[a] == 'p') ||

                    (word[a] == 'f') || (word[a] == 'v'))
                {
                    code[b] = '1';
                    ++b;
                }
                else if ((word[a] == 'c') || (word[a] == 's') ||
                    (word[a] == 'k') || (word[a] == 'g') ||
                    (word[a] == 'j') || (word[a] == 'q') ||
                    (word[a] == 'x') || (word[a] == 'z'))
                {
                    code[b] = '2';
                    ++b;
                }

                else if ((word[a] == 'd') || (word[a] == 't'))
                {
                    code[b] = '3';
                    ++b;
                }

                else if (word[a] == 'l')
                {
                    code[b] = '4';
                    ++b;
                }

                else if ((word[a] == 'm') || (word[a] == 'n'))
                {
                    code[b] = '5';
                    ++b;
                }

                else if (word[a] == 'r')
                {
                    code[b] = '6';
                    ++b;
                }
                else
                {
                    code[b] = '-';
                    ++b;
                }
            }

            // Remove the doubles
            int g = 1;
            for (int f = 0; f <= 39; ++f)
            {
                if (code[f] == code[++f])
                {
                    code[f] = '-';
                }

                }
            }
            // Remove the Zeros

            for (int e = 0; e <= 39; ++e)
            {
                if ((code[e] == '1') || (code[e] == '2') ||
                    (code[e] == '3') || (code[e] == '4') ||
                    (code[e] == '5') || (code[e] == '6'))
                {
                    temp[g] = code[e];
                    ++g;
                }
            }
            int q = 1;
            for (int f = 0; f <= 5; ++f)
            {
                realcode[q] = temp[f];
                q++
            }
    }
    return realcode;
}


