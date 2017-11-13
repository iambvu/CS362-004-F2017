
// 1- Write unit tests for four functions (not card implementations, and not cardEffect)
// in dominion.c “the refactored code you created for assignment-2”. Check these tests in
// as unittest1.c,unittest2.c, unittest3.c, and unittest4.c. At least two of these
// functions should be more than 5 lines of code. (20 points)

// Testing updateCoins(): int updateCoins(int player, struct gameState *state, int bonus)
// 	Returns 0 on successfully updating the coins for a player, given a gameState and bonus

// unittest2: unittest2.c dominion.o rngs.o
// 	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define KINGDOM_SIZE 10
#define VERBOSE 0


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
    int bonusMax = 10;
	int seed = 1000;
	int i, j, bonus;

	int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

	// For a number of possibilities
	for (i = 0; i < playerNum; ++i){
		for (j = 0; j <= 5; ++j){
			for (bonus = 0; bonus <= bonusMax; ++bonus){

				// Clear the gamestate
				memset(&state, 0, sizeof(struct gameState));
				// Initialize a 'new' game
				initializeGame(playerNum, kingdom, seed, &state);

				// Assign the current number of cards in the hand
				state.handCount[i] = j;

				// To keep things simple and avoid creating a random unit test generator,
				// Assign Copper as each card in the hand
				memcpy(state.hand[i], coppers, sizeof(int) * j);
				// Call the function to test
				updateCoins(i, &state, bonus);
				if (VERBOSE==1)
					printf("Coins: %d, expected: %d\n", state.coins, j * 1 + bonus);
				// Assert that the function's return value matches the correct result
				assert(state.coins == (j * 1) + bonus);

				// Assign Silver as each card in the hand
				memcpy(state.hand[i], silvers, sizeof(int) * j);
				// Call the function to test
				updateCoins(i, &state, bonus);
				if (VERBOSE==1)
					printf("Coins: %d, expected: %d\n", state.coins, j * 2 + bonus);
				// Assert that the function's return value matches the correct result
				assert(state.coins == (j * 2) + bonus);

				// Assign Gold as each card in the hand
				memcpy(state.hand[i], golds, sizeof(int) * j);
				// Call the function to test
				updateCoins(i, &state, bonus);
				if (VERBOSE==1)
					printf("Coins: %d, expected: %d\n", state.coins, j * 3 + bonus);
				// Assert that the function's return value matches the correct result
				assert(state.coins == (j * 3) + bonus);


			}
		}
	}

	printf("Testing complete.\n");

	return 0;

}




