#include<iostream>
using namespace std;
#include<ctime>
#include"queue.h"

void printNewCar(const int &, const int &);
void printWashingCar(const int &, const int &, const int &, const int &); 
                    

int main()
{
    srand(time(0));

    static const int MAX_TIME_OPEN   = 23;  // Maximum time open: 23 hours
    static const int MAX_MINUTES_CAR = 59;  // This would be a very slow wash
    static const int MAX_PERCENTAGE  = 100; // Can't be more than 100%

    int  hoursOpen  = 0;                    // User defined time open
    int  minPerCar  = 0;                    // Minutes to wash one car
    int  percentage = 0;                    // Percentage of car arriving

    int  hour       = 0;                    // Iteration hours
    int  min        = 0;                    // Iteration minutes

    bool washing    = false;                // Currently washing car?
    int  washTime   = 0;                    // Total wash time
    int  numCars    = 0;                    // Total cars washed
    int  avgWait    = 0;                    // Average wait time
    
    Queue wash;                             // The car wash queue itself

    do
    {
        cout << "For how many hours is the car wash open? " << flush;
        cin >> hoursOpen;
    }while(hoursOpen > MAX_TIME_OPEN);

    do
    {
        cout << "\nHow many minutes does it take to wash a car? " << flush;
        cin >> minPerCar;
    }while(minPerCar > MAX_MINUTES_CAR);

    do
    {
        cout << "\nWhat is the chance of a car each mintue ( percentage )? " 
            << flush;
        cin >> percentage;
    }while(percentage > MAX_PERCENTAGE);

    cout << "\nThe Car Wash is OPEN!" << endl;

    for(hour = 0; (hour <= hoursOpen) || (!wash.empty()); ++hour)
    {
        if(hour == hoursOpen + 1)
        {
            /* Print this message once, the hour following closing time */
            cout << "No longer taking new cars." << endl;
            cout << "There are " << wash.length() << " cars left." << endl;
        }

        for(min = 0; min <= MAX_MINUTES_CAR; ++min) // 0 - 59 minutes
        {
            if(((rand() % 100) <= percentage) && (hour <= hoursOpen)) 
            {
                /* A new car has arrived; Record the time in minutes */
                wash.enqueue((hour * 60) + min); 
                /* Print that we got a car */
                printNewCar(hour, min); 
            }
            if(washing)
            {
                ++washTime;
                if(washTime >= minPerCar)
                {
                    washing = false;                // Reset the counter;
                }
                    
            }
            if(!washing && !wash.empty()) 
            {
                /*try to get a car from the queue and start washing it*/
                int currentCar = wash.dequeue(); 

                ++numCars;

                /* Subtract the current time from the stored time */
                currentCar = ((hour * 60) + min) - currentCar;
                int waitHour = currentCar / 60;
                int waitMin  = currentCar % 60;

                avgWait += currentCar;

                //cout << " CURRENT ================ " << currentCar << endl;
                //cout << "WAIT HOUR = " << waitHour << " WAIT MIN = " << waitMin << endl;
                //cout << " hour = " << hour << " Minute = " << min << endl;
                printWashingCar(hour, min, waitHour, waitMin);
                washing  = true;
                washTime = 0;
            }
        } 
    }
    cout << "The Car Wash is closed."  << endl;
    cout << "Cars washed: " << numCars << endl;
    cout << "Average wait time: " << static_cast<float>(avgWait) / numCars << endl;
    return 0;
}

void printNewCar(const int &hour, const int &min)
{
    cout << "New car at ";
    if(hour > 0)
    { 
        cout << hour;
        cout << (hour == 1 ? " hour and " : " hours and ");
    }
    cout << min;
    cout << (min == 1 ? " minute." : " minutes.") << endl;
}
void printWashingCar(const int &startHour, const int &startMin, 
                     const int &waitHour, const int &waitMin)
{
    cout << "At ";
    if(startHour > 0)
    { 
        cout << startHour;
        cout << (startHour == 1 ? " hour and " : " hours and ");
    }
    cout << startMin;
    cout << (startMin == 1 ? " minute " : " minutes ");
    cout << "started washing car that waited ";
    if(waitHour > 0)
    {
        cout << waitHour;
        cout << (startHour == 1 ? " hour and " : " hours and ");
    }
    cout << waitMin;
    cout << (waitMin == 1 ? " minute." : " minutes.") << endl;
}
