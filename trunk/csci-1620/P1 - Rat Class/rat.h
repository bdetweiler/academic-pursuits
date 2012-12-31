// Brian Detweiler
// rat.h - definition for the Rat class

#ifndef RAT_H
#define RAT_H

class Rat
{
    private:
        int num;
        int den;
    public:
        Rat(void);
        void set(int = 0, int = 1); // Innitialize values

/*********** Assignment ****************/
        Rat operator  =  (const Rat &r);

/*********** Addition ******************/
        Rat operator  +  (const Rat&) const;          // Rat + Rat
        Rat operator  +  (const int) const;           // Rat + int

/*********** Subtraction ***************/
        Rat operator  -  (const Rat&) const;
        Rat operator  -  (const int) const;

/*********** Multiplication ************/
        Rat operator  *  (const Rat&) const;
        Rat operator  *  (const int) const;

/*********** Division ******************/
        Rat operator  /  (const Rat&) const;
        Rat operator  /  (const int) const;

/*********** Reciporocal ***************/
        Rat reciporocal(void) const;
        Rat inverse(void) const;

/*********** Increment *****************/
        Rat &operator ++ (void);                    // Pre-increment
        Rat operator  ++ (int);                     // Post-increment - HACK!

/*********** Decrement *****************/
        Rat &operator -- (void);                    // Pre-increment
        Rat operator  -- (int);                     // Post-increment - HACK!

/********** Comparisons ****************/
        bool operator == (const Rat&) const;
        bool operator != (const Rat&) const;
        bool operator <  (const Rat&) const;
        bool operator <= (const Rat&) const;
        bool operator >  (const Rat&) const;
        bool operator >= (const Rat&) const;

/********** Shortcuts ******************/
        Rat operator += (const Rat&);
        Rat operator -= (const Rat&);
        Rat operator *= (const Rat&);
        Rat operator /= (const Rat&);

        Rat operator += (const int&);
        Rat operator -= (const int&);
        Rat operator *= (const int&);
        Rat operator /= (const int&);

/********** Just for fun ***************/

        /*
         * %
         * %=
         * ^
         * 
         % (???) // may be fun to do this
        // Rat operator % (???) // may be fun to do this
        // Rat operator %= (???) // may be fun to do this
        // Rat operator %= (???) // may be fun to do this
        */
        friend ostream & operator << (ostream&, const Rat&);
        friend istream & operator >> (istream&, Rat&);
        //friend void operator >> (istream &, const Rat&);
};

/********** Int operator Rat ***********/
       
        Rat operator + (const int, const Rat &);  
        Rat operator - (const int, const Rat &);
        Rat operator * (const int, const Rat &);
        Rat operator / (const int, const Rat &);

#endif
