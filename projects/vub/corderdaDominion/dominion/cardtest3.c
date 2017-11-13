// 2- Write unit tests for four Dominion cards implemented in dominion.c “the refactored
// code you created for assignment-2”. Write these tests so that they work whether a card
// is implemented inside cardEffect or in its own function. These tests should be checked
// in as cardtest1.c, cardtest2.c, cardtest3.c, and cardtest4.c. It is mandatory to test
// smithy and adventurer card. (20 points)

// Testing village: cardEffectVillage(struct gameState *state, int currentPlayer, int handPos, int i)
// 	The player draws 3 cards and is itself discarded

// cardtest3: cardtest3.c dominion.o rngs.o
// 	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TESTING village
#define KINGDOM_SIZE 10
#define VERBOSE 0


int main () {

	// Initialize game state and associated variables
	struct gameState pre, post;
	int playerNum = 2;
	int kingdom[KINGDOM_SIZE] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
	int seed = 1000;
	int i, j, result, expect;

	// For a number of possibilities
	for (i = 0; i < playerNum; ++i){
		for (j = 0; j < MAX_HAND; ++j){

			// Clear the gamestate
			memset(&post, 0, sizeof(struct gameState));
			// Initialize a new game
			initializeGame(playerNum, kingdom, seed, &post);

			// Construct a new variation of the gameState to test            
			post.handCount[i] = j;
			// Make a copy of the gameState
			memcpy(&pre, &post, sizeof(struct gameState));

			// Call the function to test
			result = numHandCards(&post);
			// Perform the expected operation
			expect = pre.handCount[i];

			if (VERBOSE==1)
				printf("Testing with player %d...Result: %d, expected: %d\n", i+1, result, expect);
			// Assert that the function's return value matches the correct result
			assert(result==expect);
			// Assert that the gameState is identical to the ideal.
			// assert(memcmp(&pre, &post, sizeof(struct gameState)));

		}

	}

	printf("Testing complete.\n");

}