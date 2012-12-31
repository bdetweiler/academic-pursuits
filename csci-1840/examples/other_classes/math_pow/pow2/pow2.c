#include<stdio.h>
#include<stdlib.h>

int main()
{
    int i;
    int j;
    int k;
    int l;
    int m;
    int n;
    int count = 0;

    for(i = 1; i <= 9; ++i)
    {
        for(j = 0; j <= 9; ++j)
        {
            if(j != i)
            {
                for(k = 0; k <= 9; ++k)
                {
                    if(k != j)
                    {
                        for(l = 0; l <= 9; ++l)
                        {
                            if(l != k)
                            {
                                for(m = 0; m <= 9; ++m)
                                {
                                    if(m != l)
                                    {
                                        for(n = 0; n <= 8; n += 2)
                                        {
                                            ++count;
                                            // printf("%d\n", count);
                                        } 
                                    }
                                    else
                                    {
                                        printf("%d%d%d%d%d\n", i, j, k, l, m);
                                    }
                                }
                            }
                            else
                            {
                                printf("%d%d%d%d\n", i, j, k, l);
                            }
                        }
                    }
                    else
                    {
                        printf("%d%d%d\n", i, j, k);
                    }
                        
                }
            }
            else
            {
                printf("%d%d\n", i, j);
            } 
        }
    }
    printf("%d\n", count);
    return 0;
}
