#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define g -9.8
int main(void)
{
 
    // Big mass
    float M = 0.0;
    // Little mass
    float m = 0.0;
    // Acceleration
    float a = 0.0;
    // Force
    float F = 0.0;
    // Normal force
    float N = 0.0;
    // Coefficient of friction
    float u = 0.0;

   
    printf("Enter M: ");
    scanf("%f", &M);
    printf("\nEnter m: ");
    scanf("%f", &m);
    printf("\nEnter a: ");
    scanf("%f", &a);

    // Get the Force
    F = (M * (g)) - (M + m) * a;
    // Get the Normal Force
    N = (M * (g));
    // Get the coefficient of friction
    u = F/N;
    printf("Friction is: %f\n", u);
    
    return 0;
}
