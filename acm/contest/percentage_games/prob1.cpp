#include <iostream>
using namespace std;

int main()
{
    int p, n;
    int cases = 0;
    cin >> p >> n;
    while( !((p==0)&&(n==0)) )
    {
        cases++;
        cout << "Case " << cases << ": p = " << p << ", n = " << n << endl;

        int numer = p;
        int den = 1;

        if( p == 0 )
        {
            den = 1;
            for( int i = 0; i < n; ++i )
            {
                cout << "    " << numer+(i*numer) << " games out of " << den+(i*den) << endl;
            }
        }
        else
        {
            cout << "here" << endl;
            int counter = 0;
            for( int i = 1; i <100; ++i )
            {
                for( int j = 1; j < 100; ++j )
                {
                    cout << j << " " << i << endl;
                    float hundred = 100;
                    float pdec = static_cast<float>(p) / hundred;
                    cout << "pdec: " << pdec << endl;
                    float prob = (static_cast<float>(j) / static_cast<float>(i)) ;
                    cout << "prob: " << prob << endl;
                    if( prob == pdec )
                    {
                        numer = j;
                        den = i;
                        cout << "    " << numer << " games out of " << den << endl;
                        counter++;
                        if( counter == n )
                        {
                            j = i = 1000;
                        }
                    }
                }

            }
        }
        cin >> p >> n;
        cout << "got: " << p << " " << n << endl;
    }
    return 0;
}
