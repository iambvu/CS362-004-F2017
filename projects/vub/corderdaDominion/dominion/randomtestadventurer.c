// Testing adventurer: cardEffectAdventurer(struct gameState *state, int currentPlayer, int handPos, int i)
// 	Reveal cards from your deck until you reveal 2 Treasure cards. Put those Treasure cards into your hand
	// and discard the other revealed cards.

// compile, run, and log by calling "make randomttestadventurer.out"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TESTING adventurer
#define KINGDOM_SIZE 10
#define VERBOSE 1
#define ASSERTION 1


int main () {

	srand(time(0));

	// Initialize game state and associated variables
	struct gameState opState, testState;
	int seed;
	int playerNum = 2; //number of players
	int coins; /* Use as you see fit! */
	int whoseTurn;
	int handCount;
	int deckCount;
	int discardCount;
	int playedCardCount;
	int numAdventurers[playerNum];
	memset(numAdventurers, 0, playerNum*sizeof(int));
	int kingdom[KINGDOM_SIZE] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
	int adventurerPos;
	int i,j;

	// keep generating random tests until the abort trap is set or
		// 100 test suite instances have been performed.
	for (j = 0; j < 100; ++j) {

		// Initialize a random new game
		seed = rand();
		printf("Now starting test suite with random seed %d ...\n", seed);
		initializeGame(playerNum, kingdom, seed, &opState);

		// Game simulation implementation modeled after the playdom and UML
		// Card test implementation adapted in part from example of steward test file
		while (!isGameOver(&opState)) {

			// reset local variables
			coins = 0;
			adventurerPos = -1;

			// Find the position of a adventurer card
			for (i = 0; i < numHandCards(&opState); i++) {
				if (handCard(i, &opState) == copper)
					coins++;
				else if (handCard(i, &opState) == silver)
					coins += 2;
				else if (handCard(i, &opState) == gold)
					coins += 3;
				else if (handCard(i, &opState) == adventurer)
					adventurerPos = i;
			}

			// Make a copy of the gameState
			memcpy(&testState, &opState, sizeof(struct gameState));

			whoseTurn = testState.whoseTurn;

			printf("Hand start conditions - player %d\n", whoseTurn+1);
			printf("\t\t\topState\ttestState\n");
			printf("handCount:\t\t%d\t%d\n", opState.handCount[whoseTurn], testState.handCount[whoseTurn]);
			// printf("deckCount:\t\t%d\t%d\n", opState.deckCount[whoseTurn], testState.deckCount[whoseTurn]);
			// printf("discardCount:\t\t%d\t%d\n", opState.discardCount[whoseTurn], testState.discardCount[whoseTurn]);
			printf("playedCardCount:\t%d\t%d\n", opState.playedCardCount, testState.playedCardCount);
			// printf("numActions:\t\t%d\t%d\n", opState.numActions, testState.numActions);

			// Call the function to test
			// if adventurer is in the hand
			if (adventurerPos != -1) {
				
				// play the adventurer card in the testState
				playCard(adventurerPos, -1, -1, -1, &testState);
				
				// 	Reveal cards from your deck until you reveal 2 Treasure cards. Put those Treasure cards into your hand
					// and discard the other revealed cards.

				// the net gamestate delta should be...
				// handCount += 2
				handCount = opState.handCount[whoseTurn] + 2;
				// deckCount = previous deckcount - (discardCount + 2)
				deckCount = (opState.deckCount[whoseTurn] - (testState.discardCount[whoseTurn] + 2));
				// discardCount = previous discardCount + (previous deckCount - deckCount)
				discardCount = (opState.discardCount[whoseTurn] + (opState.deckCount[whoseTurn] - testState.deckCount[whoseTurn]));
				// playedCardCount++
				playedCardCount = (opState.playedCardCount + 1);

				printf("adventurer played from position %d\n", adventurerPos);

				if (VERBOSE==1) {
					printf("Post adventurer card play conditions - player %d\n", whoseTurn+1);
					printf("\t\t\topState\ttestState\n");
					printf("handCount:\t\t%d\t%d\n", handCount, testState.handCount[whoseTurn]);
					printf("deckCount:\t\t%d\t%d\n", deckCount, testState.deckCount[whoseTurn]);
					printf("discardCount:\t\t%d\t%d\n", discardCount, testState.discardCount[whoseTurn]);
					printf("playedCardCount:\t%d\t%d\n", playedCardCount, testState.playedCardCount);
				}
				
				// Assert that all variables are equal to the ideal state
				if (ASSERTION==1) {
					assert(handCount==testState.handCount[whoseTurn]);
					assert(deckCount==testState.deckCount[whoseTurn]);
					assert(discardCount==testState.discardCount[whoseTurn]);
					assert(playedCardCount==testState.playedCardCount);
				}
			}

			// play all coin cards and increment local coins variables
			coins = 0;
			i=0;
			while(i<numHandCards(&opState)){
				if (handCard(i, &opState) == copper){
					playCard(i, -1, -1, -1, &opState);
					coins++;
				} else if (handCard(i, &opState) == silver){
					playCard(i, -1, -1, -1, &opState);
					coins += 2;
				} else if (handCard(i, &opState) == gold){
					playCard(i, -1, -1, -1, &opState);
					coins += 3;
				}
				i++;
			}

			// if possible buy a province, gold, silver, or adventurer
			if (coins >= 8) {
			printf("1: bought province\n");
			buyCard(province, &opState);
			}
			else if ((coins >= 6) && (numAdventurers[whoseTurn] < 2)) {
			printf("1: bought adventurer\n");
			buyCard(adventurer, &opState);
			numAdventurers[whoseTurn]++;
			}else if (coins >= 6){
			printf("1: bought gold\n");
			buyCard(gold, &opState);
			}
			else if (coins >= 3){
			printf("1: bought silver\n");
			buyCard(silver, &opState);
			}

			printf("end turn\n");
			endTurn(&opState);
		} // end of While

		printf("Testing complete.\n");
	}
}


