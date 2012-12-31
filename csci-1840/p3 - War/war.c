/* war.c
 * by Brian Detweiler
 * A simulation of the cardgame war. 'Nuff said.
 */

#include"war.h"

/* Here are the #defines from war.h
 * ----
 * #define NUM_CARDS 52
 * #define COL_WIDTH 80
 * #define CARD(x) (card[ (x) % 13 ])
 * #define SUIT(x) (suit[ (x) / 13 ])
 * #define STR(x) CARD(x)
 */


// void setDeck(int* indexArray )
// initializes indexArray to 0-51
// input:   an array of NUM_CARDS integers
// output:  the array filled in with the index as the value
// returns: nothing
//
void setDeck(int* indexArray)
{
    // loop counter 
    int i;          
    for (i = 0; i < NUM_CARDS; i++)
    {
        indexArray[i] = i;
    }
}

// void shuffleCards( int * indexArray )
// uses rand() to switch elements for shuffling
// input:   an array of NUM_CARDS integers, that has been initialized
// output:  a shuffled array of NUM_CARDS integers
// returns: nothing
//
void shuffleCards(int* indexArray)
{
    //holds value to be switched
    int temp;
    //holds index to random element
    int randElem;
    // loop counter
    int i;

    // seed the random number generator
    srand(time(NULL));
    for(i = 0; i < NUM_CARDS; i++)
    {
        //picks random num for index
        randElem             = rand() % NUM_CARDS;
        //holds value of curr position for switch
        temp                 = indexArray[i];  
        //switches rand elem to curr
        indexArray[i]        = indexArray[randElem]; 
        //switch curr elem to rand
        indexArray[randElem] = temp;
    }
} // shuffleCards

int main(void)
{
    /* ===================================================================
     * These arrays are just the card names.  The actual cards are just ints
     * from 0 - 51, which are set in the setDeck call, shuffleCards then
     * mixes up the numbers.
     * =================================================================== 
     */ 
    //holds names of cards
    static const char *card[] =
    {
        "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
        "Nine", "Ten", "Jack", "Queen", "King", "Ace"
    };
    //holds suits of cards
    static const char *suit[] =
    {
        "Diamonds", "Clubs", "Hearts", "Spades"
    };

    // for loop int
    int   i       = 0;
    // The two card values
    int   card1   = 0;
    int   card2   = 0;
    // Keep track of hands played
    int   count   = 0;
    // Keep count of ties
    int   tie     = 0;
    // The string to tell the status of the match
    char  cardStr[COL_WIDTH + 1];
    
    int* indexArray;
    indexArray    = malloc(sizeof(int)  * NUM_CARDS);
    assert(indexArray);

    char* hand1;
    hand1         = malloc(sizeof(char) * NUM_CARDS);
    assert(hand1);

    char* hand2;
    hand2         = malloc(sizeof(char) * NUM_CARDS);
    assert(hand2);

    char* score;
    score         = malloc(sizeof(char) * NUM_CARDS);
    assert(score);


    // Each player's hand
    Queue player1;
    Queue player2;

    // Initialize the deck
    setDeck(indexArray);
    shuffleCards(indexArray);

    // Initialize the player's hands
    init_queue(&player1);
    init_queue(&player2);

    // Deal the cards

    // player 1
    for(i = 0; i <= 25; ++i)
        enqueue(&player1, indexArray[i]); 
    // player 2
    for(i = 26; i <= 51; ++i)
        enqueue(&player2, indexArray[i]);

    // Header
    printf("Let them eat war!\n\n");
    printf("%20s - %-20s %20s - %-20s\n", "Player 1's card", "Player 2's card ", 
           "Player 1's count", "Player 2's count"); 

    // Begin game
    while(!queue_empty(&player1) && !queue_empty(&player2))
    {
        // If we got here, we can safely increment the counter
        ++count;

        // Each player grabs a card from their queue
        card1 = dequeue(&player1);
        card2 = dequeue(&player2);

        // Build the string
#if 0
#endif
        sprintf(hand1, "%s of %s", card[ card1 % 13 ], suit[ card1 / 13 ]);
        sprintf(hand2, "%s of %s", card[ card2 % 13 ], suit[ card2 / 13 ]);
        
        // If player 1's hand is larger
        if((card1 % 13) > (card2 % 13))
        {
            // Player 1 takes the cards, starting with his
            enqueue(&player1, card1);
            enqueue(&player1, card2);
            // Continue building string
            sprintf(score, "%20d - %-20d", player1.count, player2.count);
            sprintf(cardStr, "%20s > %-20s %20s\n", hand1, hand2, score);

        }
        // If player 2's hand is larger
        else if((card1 % 13) < (card2 % 13))
        {
            // Player 2 takes the cards, starting with his
            enqueue(&player2, card2);
            enqueue(&player2, card1);
            // Continue building string
            sprintf(score, "%20d - %-20d", player1.count, player2.count);
            sprintf(cardStr, "%20s < %-20s %-20s\n", hand1, hand2, score);
        }
        // Cards are equal
        else 
        {
            // Toss the cards out

            // Continue building string
            sprintf(score, "%20d - %-20d", player1.count, player2.count);
            sprintf(cardStr, "%20s = %-20s %-20s\n", hand1, hand2, score);
            // Increment tie
            ++tie;
        }
        // Print the string we just built.
        printf("%s", cardStr);
            
    } // end while(!queue_empty(&player1) && !queue_empty(&player2))

    if(queue_empty(&player1))
    {
        printf("\nPlayer 2 wins!\n");
    }
    else if(queue_empty(&player2))
    {
        printf("\nPlayer 1 wins!\n");
    }
    else
    {
        // we've got issues. Exit gracefully.
        fprintf(stderr, "There was an error\n");
        exit(EXIT_FAILURE);
    }

    // Print the final status
    printf("It took %d hands and there were %d ties.\n\n", count, tie);

    // free the queues and malloc'd variables
    free_queue(&player1);
    free_queue(&player2);
    free(indexArray);
    free(hand1);
    free(hand2);
    free(score);
    return 0;
}
