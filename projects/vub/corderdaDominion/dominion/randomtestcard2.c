// Testing smithy: cardEffectSmithy(struct gameState *state, int currentPlayer, int handPos, int i)
	// The player draws 3 cards and is itself discarded

// compile, run, and log by calling "make randomtestcard2.out"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TESTING smithy
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
	int numSmithies[playerNum];
	memset(numSmithies, 0, playerNum*sizeof(int)); // dynamically initalize
	int smithyPos;
	int kingdom[KINGDOM_SIZE] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy};
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
			smithyPos = -1;

			// Find the position of a smithy card
			for (i = 0; i < numHandCards(&opState); i++) {
				if (handCard(i, &opState) == copper)
					coins++;
				else if (handCard(i, &opState) == silver)
					coins += 2;
				else if (handCard(i, &opState) == gold)
					coins += 3;
				else if (handCard(i, &opState) == smithy)
					smithyPos = i;
			}

			// Make a copy of the gameState
			memcpy(&testState, &opState, sizeof(struct gameState));

			whoseTurn = testState.whoseTurn;

			printf("Hand start conditions - player %d\n", whoseTurn+1);
			printf("\t\t\topState\ttestState\n");
			printf("handCount:\t\t%d\t%d\n", opState.handCount[whoseTurn], testState.handCount[whoseTurn]);
			printf("deckCount:\t\t%d\t%d\n", opState.deckCount[whoseTurn], testState.deckCount[whoseTurn]);
			printf("discardCount:\t\t%d\t%d\n", opState.discardCount[whoseTurn], testState.discardCount[whoseTurn]);
			printf("playedCardCount:\t%d\t%d\n", opState.playedCardCount, testState.playedCardCount);

			// Call the function to test
			// if smithy is in the hand
			if (smithyPos != -1) {
				
				// play the smithy card in the testState
				playCard(smithyPos, -1, -1, -1, &testState);
				
				// Perform the expected operation in the testState
				// [Draws 3 cards: for(i=0;i<5;i++) drawCard(currentPlayer,state)]
				// [Discards the smithy card]

				// the net gamestate delta should be...
				// handCount += 2;
				handCount = (opState.handCount[whoseTurn] + 2);
				// deckCount -= 3;
				deckCount = (opState.deckCount[whoseTurn] - 3);
				// discardCount ++;
				discardCount = (opState.discardCount[whoseTurn] +1);
				// playedCardCount++;
				playedCardCount = (opState.playedCardCount + 1);

				printf("smithy played from position %d\n", smithyPos);

				if (VERBOSE==1) {
					printf("Post smithy card play conditions - player %d\n", whoseTurn+1);
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

			// if possible buy a province, gold, silver, or smithy
			if (coins >= 8) {
				printf("bought province\n");
				buyCard(province, &opState);
			} else if (coins >= 6) {
				printf("bought gold\n");
				buyCard(gold, &opState);
			} else if ((coins >= 4) && (numSmithies[whoseTurn] < 2)) {
				printf("bought smithy\n");
				buyCard(smithy, &opState);
				numSmithies[whoseTurn]++;
			} else if (coins >= 3) {
				printf("bought silver\n");
				buyCard(silver, &opState);
			}

			printf("end turn\n");
			endTurn(&opState);
		} // end of While

		printf("Testing complete.\n");
	}
}


