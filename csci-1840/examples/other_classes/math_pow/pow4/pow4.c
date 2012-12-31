/* Brian Detweiler
 * A program to solve the following problem:
 *
 * Let "T" be the lower left-hand corner of a checkerboard and let "B"
 * be the intersection of the 7th vertical line and the 8th horizontal line
 * counting from the lower left-hand corner. Suppose that you want to 
 * move from T to B and that all movement must be horizontal or 
 * vertical along the lines formed by the various squares on the 
 * checkerboard. Clearley, you can get from T to B along a path that has 
 * length "15" in terms of a unit equal to a side fo a small square. It
 * should also be clear that no shorter path exists. How many different 
 * paths have length 15?
 */

#include<stdlib.h>
#include<stdio.h>

/*                       B(7,8)
 * ----------------------B
 * |  |  |  |  |  |  |  |
 * ----------------------
 * |  |  |  |  |  |  |  |
 * ----------------------
 * |  |  |  |  |  |  |  |
 * ----------------------
 * |  |  |  |  |  |  |  |  9 Lines horizontally
 * ----------------------
 * |  |  |  |  |  |  |  |
 * ----------------------
 * |  |  |  |  |  |  |  |
 * ----------------------
 * |  |  |  |  |  |  |  |
 * ----------------------
 * |  |  |  |  |  |  |  |
 *T----------------------
  T(0,0)   
    8 lines vertically
 */ 

void move(int*, int, int);

/* This is a recursive function that will
 * advance T either up, or to the right, 
 * until it reaches point (7,8), and then
 * it increments the counter. It then retraces
 * its step until it finds another path to 
 * take, and repeats the process until all
 * paths are found. 
 */
void move(int* count, int up, int right)
{
    static int uLimit = 8;
    static int rLimit = 7;

    printf("-----------------------\n");
    /* Conditional to test whether or not we are
     * at B. This is true when both up and right
     * are at their respective limits.
     */
    printf("count = %d\n(right, up) = (%d, %d)\n", *count, right, up);
        
    if(right < rLimit)
        move(count, up, ++right);
    if(up < uLimit)
        move(count, ++up, right);
  
    /* This is getting incremented twice, so we will devide it by two
     * when we output it.
     */ 
    if(up == 8 && right == 7)
        ++(*count); 
}

int main()
{
    int up    = 0;
    int right = 0;
    int count = 0;
    
    move(&count, up, right);
    count /= 2;
    printf("count = %d\n", count);
    return 0;
}
