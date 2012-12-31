#include <iostream>
#include <iomanip>
using namespace std;

typedef struct contour
{
    int * arr;
    int points;
    int minx;
    int miny;
    int maxx;
    int maxy;
    int *set;
    int tier;
}cont;

void display( cont *, int );
void disp_recur( cont *, int, int );

int main()
{
    cont * cont_arr; 
    cont_arr = new cont[100];

    int contour;
    cin >> contour;
    int num = 0;
    while( contour != 0 )
    {
        num++;
        int i = contour - 1;
        cin >> cont_arr[i].points; // get the number of points
        // make an array to keep track of it
        cont_arr[i].arr = new int[cont_arr[i].points * 2];

        // populate the array of points
        for( int j = 0; j < cont_arr[i].points * 2; ++j )
        {
            cin >> cont_arr[i].arr[j];
        }

        // find the smallest x
        cont_arr[i].minx = cont_arr[i].arr[0];
        for( int j = 2; j < cont_arr[i].points; j += 2 )
        {
            if( cont_arr[i].arr[j] < cont_arr[i].minx )
                cont_arr[i].minx = cont_arr[i].arr[j];
        }

        // find the smallest y
        cont_arr[i].miny = cont_arr[i].arr[1];
        for( int j = 3; j < cont_arr[i].points; j += 2 )
        {
            if( cont_arr[i].arr[j] < cont_arr[i].miny )
                cont_arr[i].miny = cont_arr[i].arr[j];
        }

        // find the largest x
        cont_arr[i].maxx = cont_arr[i].arr[0];
        for( int j = 2; j < cont_arr[i].points; j += 2 )
        {
            if( cont_arr[i].arr[j] > cont_arr[i].maxx )
                cont_arr[i].maxx = cont_arr[i].arr[j];
        }

        // find the largest y
        cont_arr[i].maxy = cont_arr[i].arr[1];
        for( int j = 3; j < cont_arr[i].points; j += 2 )
        {
            if( cont_arr[i].arr[j] > cont_arr[i].maxy )
                cont_arr[i].maxy = cont_arr[i].arr[j];
        }
        cont_arr[i].tier = 0;
    }

    for(int i = 0; i < num; ++i )
    {
        cont_arr[i].set = new int[num];
        for( int j = 0; j < num; ++j )
            cont_arr[i].set[j] = 0;
    }

    for(int i = 0;i < contour; ++i )
    {
        for( int j = 0; j < contour; ++j )
        {
            if( i != j ) // don't compare it to itself
            {
                // it j is inside of i
                if ( ( cont_arr[i].minx < cont_arr[j].minx )&&
                        (cont_arr[i].miny < cont_arr[j].miny ) && 
                        ( cont_arr[i].maxx > cont_arr[j].maxx ) &&
                        ( cont_arr[i].maxy > cont_arr[j].maxy ) )
                {
                    cont_arr[j].tier++;
                    cont_arr[i].set[j] = 1;
                }

            }
        }
    }

    delete [] cont_arr;
    return 0;
}


void display( cont * cont_arr, int num )
{
    for( int i = 0; i < num; ++i )
    {
        if ( cont_arr[i].tier == 1 )
        {
            //print itself
            cout << i << endl;
            //print its sub-tiers
            for( int j = 0; j < num; ++j )
            {
                if ( cont_arr[i].set[j] == 1)
                {
                    disp_recur( cont_arr, j, num );
                }
            }
        }
    }
}
void disp_recur( cont * cont_arr, int which, int num )
{
    // display the current one
    cout << setw( 2 * cont_arr[which].tier ) << which << endl;

    // display any that it contains
    for( int j = 0; j < num; ++j )
    {
        if ( cont_arr[which].set[j] == 1)
        {
            disp_recur( cont_arr, j, num );
        }
    }
}
