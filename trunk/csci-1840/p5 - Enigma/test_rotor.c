#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include"spindle.h"

#define R1 'P'
#define R2 'D'
#define R3 'T'

int main(void)
{
    Spindle spindle;
    char      tmp[80];
   
    Rotor     right;
    Rotor     middle;
    Rotor     left;

    Reflector ref;

    rotor_init(    &left,   1, R1);
    rotor_init(    &middle, 2, R2);
    rotor_init(    &right,  3, R3);
    reflector_init(&ref,    'B');
    spindle_init(  &spindle);

    spindle.addRotor(    &spindle, &right);
    spindle.addRotor(    &spindle, &middle);
    spindle.addRotor(    &spindle, &left);
    
    spindle.addReflector(&spindle, &ref);
  
    // Char to encrypt
    while((fgets(tmp, 80, stdin) != NULL))
    {;;;} // do nothing

    printf("encrypted message: %s\n", spindle.encrypt(&spindle, tmp));

#if 0 
    printf("%c %c %c\n", R1, R2, R3);
    printf("INPUT: %c\n\n", tmp);
    printf("rotorStep\n");
    right.step(&right);

    
    // right.sub(&right, 'G', 0);



    tmp = right.sub(    &right,  tmp);
    tmp = middle.sub(   &middle, tmp);
    tmp = left.sub(     &left,   tmp); 
   
    tmp = ref.sub(      &ref,    tmp);
    
    tmp = left.revSub(  &left,   tmp);
    tmp = middle.revSub(&middle, tmp);
    tmp = right.revSub( &right,  tmp);

    printf("\nAnswer is: %c\n\n", tmp);

/* 
    right.revSub(&right, 
                 middle.revSub(&middle, 
                               left.revSub(&left, 
                                           ref.sub(&ref, 
                                                   left.sub(&left, 
                                                            middle.sub(&middle, 
                                                                       right.sub(&right, 
                                                                                 'G', 
                                                                                 0), 
                                                                       right.offset), 
                                                            middle.offset))))));// , 
                                
                                                    
*/ 
                                                            //right.ringSetting), 
                                                                                        //middle.ringSetting)))))); 
                

#if 0 
    printf("rotorNum = %d\n", right.rotorNum);

    printf("alphaRing[0] = %c\n", right.alphaRing[0]);

    printf("alphaRingRev[0] = %c\n", right.alphaRingRev[0]);

    printf("offset = %d\n", right.offset);

    printf("ringSetting = %d\n", right.ringSetting);

    printf("stepControl = %c\n", right.stepControl);
    printf("findCharNum(G) = %d\n", right.lookup('G'));


    printf("rotorNum = %d\n", right.rotorNum);

    printf("alphaRing[0] = %c\n", right.alphaRing[0]);

    printf("alphaRingRev[0] = %c\n", right.alphaRingRev[0]);

    printf("offset = %d\n", right.offset);

    printf("ringSetting = %d\n", right.ringSetting);

    printf("stepControl = %c\n", right.stepControl);

    printf("rotorSub('G') = %c\n", right.sub(&right, 'G'));
    printf("rotorSub('C') = %c\n", middle.sub(&middle, 'C'));
    printf("rotorSub('D') = %c\n", left.sub(&left, 'D'));
    printf("reflectorSub('F') = %c\n", ref.sub(&ref, 'F'));
    printf("rotorRevSub('S') = %c\n", left.revSub(&left, 'S'));
    printf("rotorRevSub('S') = %c\n", middle.revSub(&middle, 'S'));
    printf("rotorRevSub('E') = %c\n", right.revSub(&right, 'E'));

    printf("rotorStep\n");
    right.step(&right);
/*
    printf("encode 'A' = %c\n", 
            right.revSub(&right, 
                middle.revSub(&middle, 
                    left.revSub(&left, 
                        ref.sub(&ref,
                            left.sub(&left, 
                                middle.sub(&middle, 
                                    right.sub(&right, 'A')))))))); 

*/
#endif
#endif
    
    return 0;
}
    
