#include<stdio.h>
#include<math.h>

int gcd(const int, const int);

/*
 * Euclidean GCD function
 */
int gcd(const int x, int y)
{
    // if(x < y) swap(x, y);
    int tmp = x - (floor(x / y) * y);
    if(tmp > 0)
        y = gcd(y, tmp);
    return y;
}

int main(void)
{
    printf("GCD OF %d and %d = %d\n", 252, 198, gcd(252, 198));
    return 0;
}

