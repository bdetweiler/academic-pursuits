//  Enigma.C - Simple "Enigma" Machine Encrypt/Decrypt machine
//
//  Myke Predko - 98.02.10
//
//  This code runs a Simple (Three Wheel) version of the WW2 German
//   "Enigma" Machine with a brute force decryption algorthim to
//   demonstrate how fast data can be decrypted by a Pentium Class
//   PC.
//
// 

#include "stdio.h"		//  stdio.h In quotes so it will 
 					//   show up in html.


//  Define Message Strings Along with the Variable Messages
int i, j, k, n;

// Letter Positions:ABCDEFGHIJKLMNOPQRSTUVWXYZ

char Wheel_1[26] = "ZYXWVUTSRQPOMNLKJIHGFEDCBA";  //  Reverse Letters

char Wheel_2[26] = "BADCFEHGJILKNMPORQTSVUXWZY";  //  Translate Up 13

char Wheel_3[26] = "FGHIJABCDEPQRSTKLMNOXYZUVW";  //  Blocks of 5


char far * Msg    = "CANTHISBEDECODED";  //  Message to be encoded/
char far * Encode = "canthisbedecoded";  //   decoded.
     	                           //  "Encode" points to space for Msg


//  Define the Wheel Operations
char Encode1( char Input )
{                               //  Convert the Letter using "i"
  return Wheel_1[( i + Input - 'A' ) - (( i + Input - 'A' ) / 26 * 26 )];
}  //  End Encode1

char Encode2( char Input )
{                               //  Convert the Letter using "j"

  return Wheel_2[( j + Input - 'A' ) -
                                    (( j + Input - 'A' ) / 26 * 26 )];

}  //  End Encode2

char Encode3( char Input )
{                               //  Convert the Letter using "j"

  return Wheel_3[( k + Input - 'A' ) -
                                    (( k + Input - 'A' ) / 26 * 26 )];

}  //  End Encode3

char ReadDecode( Input )
{                               //  Figure out what the Character is
                                //   For Input, i and j

char retvalue;                  //  Character to be Returned
int  count;

  for ( count = 0; Wheel_3[ count ] != Input; count++ );

  if (( count = count - k ) < 0 )
    count += 26;                //  Get a Valid Character Position

  retvalue = count + 'A';       //  Convert to ASCII

  for ( count = 0; Wheel_2[ count ] != retvalue; count++ );

  if (( count = count - j ) < 0 )
    count += 26;

  retvalue = count + 'A';       //  Convert to ASCII

  for ( count = 0; Wheel_1[ count ] != retvalue; count++ );

  if (( count = count - i ) < 0 )
    count += 26;

  return count + 'A';

}  //  End ReadDecode

EnigmaInc()                     //  Rotate the Wheels
{

    if ( ++i > 25 ) {           //  Now, Rotate the Wheels
      i = 0;                    //  "i" is Rolling Over
      if ( ++j > 25 ) {
        j = 0;
        if ( ++k > 25 )
          k = 0;
      }  //  endif
    }  //  endif

}  //  End EnigmaInc


main()
{

int Wheel_1Start = 16;          //  Set the Initial Wheel Positions
int Wheel_2Start = 25;          //   As part of the Code
int Wheel_3Start = 17;

  i = Wheel_1Start;             //  Setup the Checking Parameters
  j = Wheel_2Start;
  k = Wheel_3Start;

  for ( n = 0; n < strlen( Msg ); n++ ) {
    Encode[ n ] = Encode3( Encode2( Encode1( Msg[ n ])));
    EnigmaInc();                //  Get the Encrypted Character
  }  //  endfor

  printf( "\"%s\" is encoded into \"%s\"\n", Msg, Encode );


//  "Encode" is loaded with the Encoded Message

  for ( i = 0; i < 26; i++ )    //  Now, Find "i", "j" and "k" to
    for ( j = 0; j < 26; j++ )  //   Decrypt
      for ( k = 0; k < 26; k++ ) {
        Wheel_1Start = i;         //  Save Starting Values for Looping
        Wheel_2Start = j;
        Wheel_3Start = k;
        for ( n = 0; ( n < strlen( Msg )) &&
                      ( Msg[ n ] == ReadDecode( Encode[ n ])); n++ ) {
          EnigmaInc();
        }  // endfor
        if ( n == strlen( Msg ))
          printf(
            "Decode Wheel Positions: 1 -> %i, 2 -> %i, and 3 -> %i\n",
                           Wheel_1Start, Wheel_2Start, Wheel_3Start );
      i = Wheel_1Start;         //  Restore the Wheel Values
      j = Wheel_2Start;
      k = Wheel_3Start;
    }  //  endfor

}  //  end Enigma
              
