#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
  int success = 0;
  int testsFailed = 0, totalTests = 0;
  int numPlayers = 2;
  int seed = 1000;
  int thisPlayer = 0;
  int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
  int kingdomCards[10] = { smithy, adventurer, village, mine, minion, steward, treasure_map, council_room, feast, gardens };
  char name1[32];
  char name2[32];

  struct gameState G, testG;

  initializeGame(numPlayers, kingdomCards, seed, &G);

  printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

  printf("TEST: +3 cards\n");

  memcpy(&testG, &G, sizeof(struct gameState));

  totalTests++;
  printf("Actual hand count: %d, expected: %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
  printf("Actual deck count: %d, expected: %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
  if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] && testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]) {
    printf("Hand and deck have expected count >>> TEST PASSED\n");
  }
  else {
    printf("Hand and deck do not have expected count >>> TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, bonus);

  printf("Checking hand and deck count after playing smithy card...\n");

  totalTests++;
  int newCards = 3;

  printf("Actual hand count: %d, expected: %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - 1); // discard smithy card just played
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

  if (success == 0) {
    printf("\n >>>>> SUCCESS: %d/%d tests passed %s <<<<<\n\n", totalTests - testsFailed, totalTests, TESTCARD);
  }
  else {
    printf("\n >>>>> FAILURE: %d/%d tests failed %s <<<<<\n\n", testsFailed, totalTests, TESTCARD);
  }


  return 0;
}