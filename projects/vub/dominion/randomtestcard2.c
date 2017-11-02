#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define TESTCARD "council_room"

int main() {
  int success = 0;
  int testsFailed = 0, totalTests = 0;
  int numPlayers = 2;
  int seed = 1000;
  int thisPlayer = 0;
  int handpos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
  int kingdomCards[10] = { smithy, adventurer, village, mine, minion, steward, treasure_map, council_room, feast, gardens };
  char name1[32];
  char name2[32];

  struct gameState G, testG;

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  printf("TEST: +4 cards, +1 buy, each other player draws 1 card\n");

  printf("RANDOM TESTS.\n");

  srand(time(NULL));

  int n, i;

  for (n = 0; n < 200000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(rand() % 256);
    }

    // numPlayers = floor(rand() % 5);

    initializeGame(numPlayers, kingdomCards, seed, &G);

    /*******
    * Randomize everything
    **/

    // set up game
    G.supplyCount[copper] = rand() % 60;
    G.supplyCount[silver] = rand() % 40;
    G.supplyCount[gold] = rand() % 30;

    // player 1
    G.deckCount[thisPlayer] = floor(rand() % MAX_DECK);
    G.discardCount[thisPlayer] = floor(rand() % MAX_DECK);
    G.handCount[thisPlayer] = floor(rand() % MAX_HAND);

    // player 2
    G.deckCount[thisPlayer + 1] = floor(rand() % MAX_DECK);
    G.discardCount[thisPlayer + 1] = floor(rand() % MAX_DECK);
    G.handCount[thisPlayer + 1] = floor(rand() % MAX_HAND);

    G.whoseTurn = thisPlayer;
    G.numBuys = floor(rand() % 500);

    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, bonus);

    printf("Checking hand and deck count after playing council_room card...\n");

    totalTests++;
    int newCards = 4;

    printf("Actual hand count: %d, expected: %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - 1); // discard village card just played
    printf("Actual deck count: %d, expected: %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - 1 &&
      testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards) {
      printf("Hand and deck have expected count >>> TEST PASSED\n");
    }
    else {
      printf("Hand and deck do not have expected count >>> TEST FAILED\n");
      success = 1;
      testsFailed++;
    }

    totalTests++;
    printf("Actual hand count: %d, expected: %d\n", testG.handCount[thisPlayer + 1], G.handCount[thisPlayer + 1] + 1);
    if (testG.handCount[thisPlayer + 1] == G.handCount[thisPlayer + 1] + 1) {
      printf("Hand has expected count >>> TEST PASSED\n");
    }
    else {
      printf("Hand does not have expected count >>> TEST FAILED\n");
      success = 1;
      testsFailed++;
    }

    printf("Checking player buy count after playing council_room card...\n");

    totalTests++;
    printf("Current player buy count: %d, expected: %d\n", testG.numBuys, G.numBuys + 1);
    if (testG.numBuys == G.numBuys + 1) {
      printf("Buy count has expected count >>> TEST PASSED\n");
    } else {
      printf("Buy count does not have expected count >>> TEST FAILED\n");
      success = 1;
      testsFailed++;
    }
  }

  if (success == 0) {
    printf("\n >>>>> SUCCESS: %d/%d tests passed %s <<<<<\n\n", totalTests - testsFailed, totalTests, TESTCARD);
  }
  else {
    printf("\n >>>>> FAILURE: %d/%d tests failed %s <<<<<\n\n", testsFailed, totalTests, TESTCARD);
  }

  return 0;
}