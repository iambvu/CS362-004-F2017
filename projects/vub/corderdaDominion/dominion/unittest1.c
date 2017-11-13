
// 1- Write unit tests for four functions (not card implementations, and not cardEffect)
// in dominion.c “the refactored code you created for assignment-2”. Check these tests in
// as unittest1.c,unittest2.c, unittest3.c, and unittest4.c. At least two of these
// functions should be more than 5 lines of code. (20 points)

// Testing buyCard()

// unittest1: unittest1.c dominion.o rngs.o
// 	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define KINGDOM_SIZE 10
#define VERBOSE 1

int main () {

	// gameState definition
	// struct gameState {
	//   int numPlayers; //number of players
	//   int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
	//   int embargoTokens[treasure_map+1];
	//   int outpostPlayed;
	//   int outpostTurn;
	//   int whoseTurn;
	//   int phase;
	//   int numActions; /* Starts at 1 each turn */
	//   int coins; /* Use as you see fit! */
	//   int numBuys; /* Starts at 1 each turn */
	//   int hand[MAX_PLAYERS][MAX_HAND];
	//   int handCount[MAX_PLAYERS];
	//   int deck[MAX_PLAYERS][MAX_DECK];
	//   int deckCount[MAX_PLAYERS];
	//   int discard[MAX_PLAYERS][MAX_DECK];
	//   int discardCount[MAX_PLAYERS];
	//   int playedCards[MAX_DECK];
	//   int playedCardCount;
	// };

	// Initialize game state and associated variables
	struct gameState state;
	int playerNum = 2;
	int kingdom[KINGDOM_SIZE] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
	int seed = 1000;
	int i, j;

	// For a number of possibilities
	for (i = 0; i < playerNum; ++i){
		for (j = 0; j < KINGDOM_SIZE; ++j){

			// Construct a new variation of the gameState to test            
			// Clear the gamestate
            memset(&post, 0, sizeof(struct gameState));
			// Initialize a new game
            initializeGame(playerNum, kingdom, seed, &post);

            // Make a copy of the gameState
            memcpy(&pre, &post, sizeof(struct gameState));

			// Call the function to test

			// Perform the expected operations


			if (VERBOSE==1)
				printf("Coins: %d, expected: %d\n", state.coins, j * 1 + bonus);
			
			// Assert that the function's return value matches the correct result
			assert(result==expect);
			// Assert that the gameState is identical to the ideal.
			// assert(memcmp(&pre, &post, sizeof(struct gameState)));
		
		}

	}

	printf("Testing complete.\n");

	return 0;

}




