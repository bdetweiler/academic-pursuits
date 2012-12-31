/* war.h
 * Header file for war.c
 * Contains all definitions and prototpyes for war.c
 */

// Standard stuff
#include<stdio.h>
#include<stdlib.h>

// For random number generation
#include<time.h>

// Check memory allocation
#include<assert.h>

// String manipulation
#include<string.h>

// Include our queue
#include"queue.h"

// Number of cards in a deck
#define NUM_CARDS 52
#define COL_WIDTH 80

/*
 * In order to get the card name from the number
 *
 * printf( "%s of %s", card[ number % 13 ], suit[ number / 13 ] );
 * printf( "%s of %s", CARD( number), SUIT( number ) );
 */
#define CARD(x) (card[ (x) % 13 ])
#define SUIT(x) (suit[ (x) / 13 ])
#define STR(x) CARD(x)

// prototypes
void setDeck(int*);      //initializes index array 0-51
void shuffleCards(int*); //shuffles values of index array
