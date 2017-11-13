#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>

#define FUNCTION "buyCard"

int main() {
  int success = 0;
  int testsFailed = 0, totalTests = 0;
  int numPlayers = 2;
  int seed = 1000;
  int i, j;
  int player1 = 0;
  int player2 = 1;
  int money = 6;
  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, great_hall};
  
  struct gameState G;

  initializeGame(numPlayers, kingdomCards, seed, &G);

  printf("----------------- Testing Function: %s ----------------\n", FUNCTION);

  printf("DESCRIPTION: Card bought is properly placed into discard pile\n\n");

  G.whoseTurn = player2;
  G.coins = money;

  totalTests++;
  buyCard(gold, &G);
  printf("Bought gold treasure card\n");
  printf("Expected top of discard to be gold: 6, actual top of discard: %d >>> ", G.discard[G.whoseTurn][G.discardCount[G.whoseTurn - 1]]);
  if (G.discard[G.whoseTurn][G.discardCount[G.whoseTurn - 1]] == gold) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  if (success == 0) {
    printf("\n >>>>> SUCCESS: %d/%d tests passed %s <<<<<\n\n", totalTests - testsFailed, totalTests, FUNCTION);
  } else {
    printf("\n >>>>> FAILURE: %d/%d tests failed %s <<<<<\n\n", testsFailed, totalTests, FUNCTION);
  }

  return 0;
}