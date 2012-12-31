/* array_sort.c
 * by Brian Detweiler
 * This program takes a bunch of numbers,
 * organizes them, and spits out the
 * number of elements, the  mean,
 * the median, the max, and the min.
 */


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>

#define SIZE 20

void swap(int *, int *);
void quickSort(int *, int, int);
void getNumElements(const int*, int*);
void getMean(int*, float*, int*);
void getMedian(int*, int*, int*);

/* Used by quickSort() */
void swap(int *a, int *b)
{ 
      int tmp = 0;
      tmp  = *a; 
      *a   = *b; 
      *b   = tmp; 
}

/* Algorithm stolen ^h^h^h^h^h borrowed from 
 * http://en.wikipedia.org/wiki/Quicksort_implementations#C 
 */
void quickSort(int* arr, int beg, int end)
{
    if(end > beg + 1) 
    {
        int pivot = arr[beg]; 
        int l     = beg + 1; 
        int r     = end;
        while (l < r) 
        {
            if (arr[l] <= pivot) 
                l++;
            else 
                swap(&arr[l], &arr[--r]);
        }
        swap(&arr[--l], &arr[beg]);
        quickSort(arr, beg, l);
        quickSort(arr, r, end);
    }
}

/* This gets the number of elements in the array. It is
 * admittedly never used, but could be viewed as a safety 
 * feature, as well as a function for scalability.
 */
void getNumElements(const int* arr, int* numElements)
{
    int i = 0;

    for(i = 0; i <= sizeof(arr); ++i)
    {
        ++(*numElements);
    }
}

/* Average people suck! Or so implies those moderately witty 
 * bumper stickers. This function grabs the average of the
 * elements.
 */
void getMean(int* arr, float* mean, int* numElements)
{
    int i = 0;

    if(*numElements <= 0)
    {
        getNumElements(arr, numElements);
    }
    for(i = 0; i < *numElements; ++i)
    {
        *mean += arr[i];
    }
    /* mean = the grand total element data devided by the total number of elements */
    *mean = *mean / *numElements;
}
 
/* Here, we grab the median of all the elements. "B-B-But Brian,"
 * you stutter, "what will we do about an even number of elements, 
 * which yields two elements as a median?" 
 *
 * To which I reply, "Shut the fuck up." 
 *
 * But seriously, that is handled in main(), by printing the pointer
 * before this one in addition to this one. There, are you happy?
 */
void getMedian(int* arr, int* median, int* numElements)
{
    if(numElements <= 0)
    {
        getNumElements(arr, numElements);
    }
    /* In Main, do an if to see if numElements is even. Median will just be an index number.
     * If it is even, just print arr[median - 1] and arr[median]. Simple.
     */
    *median = (*numElements) / 2;
}

/* Main. It's the shit. */
int main(void)
{
    int   numElements = 0;
    int   median      = 0;
    float mean        = 0.0;
    int   i           = SIZE;

    int*  arr         = NULL;
  
    /* Innitialized to 4 bytes which is 1 int. No wasted space here. */
    arr =(int*) malloc((numElements + 1) * sizeof(int));
    /* Make sure arr was allocated ok */
    assert(arr);

    /* 
     * Note the ampersand before arr. At first this looks wrong, until
     * we realize that arr[] with the brackets is actually a derefrenced 
     * pointer. Therefore, we have to re-reference it. This comment is for
     * me, so that when I look back at this in a few years time, I can stop 
     * beating my head against the wall.
     */
    while(scanf("%d", &arr[numElements]) == 1)
    {
        /* 
         * We automatically increment the numElements counter, because
         * we are about to do just that.
         */
        ++numElements;
        /* 
         * Since we are going to add an element into our array, we should
         * give it another byte of memory. This way, we never have to worry
         * about giving it too much, or running out. Everybody's happy. Except
         * for my mother, who still thinks I should be an English major.
         *
         * FIXME: This is bad coding. realloc() is a computationally expensive 
         *        function doing this one byte at a time is a bad idea. 
         */
        arr = realloc(arr, sizeof(int) * (numElements + 1));
        /* 
         * Make sure arr was allocated ok 
         */
        assert(arr);
    }
#if 0
    /* Don't really need this anymore */
    getNumElements(arr, &numElements);
#endif

    quickSort(arr, 0, numElements);
    getMean(arr, &mean, &numElements);
    getMedian(arr, &median, &numElements);

    /* Print everything out nicely */
    for(i = 0; i < numElements; ++i)
        printf("%d ", arr[i]);

    printf("\n");
    printf("elements = %d\n", numElements);
    printf("mean = %.2f\n", mean);
    printf("max = %d\n", arr[numElements - 1]);
    printf("min = %d\n", arr[0]);

    if((numElements % 2) == 0)
        printf("median = %d %d\n", arr[median - 1], arr[median]);
    else
        printf("median = %d\n", arr[median]);

    /* If you love something, set it free. */
    free(arr);
    return 0;
}
