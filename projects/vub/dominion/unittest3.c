#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>

#define FUNCTION "fullDeckCount"

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

  printf("DESCRIPTION: Return correct count of full deck (hand, deck, discard)\n\n");

  // at initialize one player should have total 7 full deck count
  // 7 in deck, discard and hand are empty
  totalTests++;
  printf("Expected full deck count to be 7, 7 in deck, while both discard and hand are empty >>> ");
  if (fullDeckCount(player2, 0, &G) == 7) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  // buy a card which goes into discard pile
  G.coins = money;
  if (G.coins >= 8) {
    buyCard(province, &G);
  }
  else if (G.coins >= 6) {
    buyCard(gold, &G);
  }

  totalTests++;
  printf("Expected full deck count to be 8, 7 in deck, 1 discard and hand is empty >>> ");
  if (fullDeckCount(player2, 0, &G) == 8) {
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