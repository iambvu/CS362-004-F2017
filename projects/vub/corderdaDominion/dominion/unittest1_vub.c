#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>

#define FUNCTION "isGameOver"

int main() {
  int success = 0;
  int testsFailed = 0, totalTests = 0;
  int numPlayers = 2;
  int seed = 1000;
  int i, j = 0;
  int kingdomCards[10] = {smithy, adventurer, village, mine, minion, steward, treasure_map, baron, feast, gardens};
  
  struct gameState G;

  initializeGame(numPlayers, kingdomCards, seed, &G);

  printf("----------------- Testing Function: %s ----------------\n", FUNCTION);

  printf("DESCRIPTION: Game state is dependent on cards in province and supply piles\n\n");

  // at start of game so game state should not be "game over"
  totalTests++;
  if (isGameOver(&G) == 0) {
    printf("Expected game state at start of game: 0, Actual game state: %d >>> TEST PASSED\n", isGameOver(&G));
  } else {
    printf("Expected game state at start of game: 0, Actual game state: %d >>> TEST FAILED\n", isGameOver(&G));
    success = 1;
    testsFailed++;
  }

  int provincePile = G.supplyCount[province];

  totalTests++;
  printf("Province pile size: %d so game is not over >>> ", G.supplyCount[province]);
  if (isGameOver(&G) == 0) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  G.supplyCount[province] = 0;

  totalTests++;
  printf("Province pile size: %d so game is over >>> ", G.supplyCount[province]);
  if (isGameOver(&G) == 1) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  G.supplyCount[province] = provincePile;
  
  for (i = 0; i < 25; i++) {
    if(G.supplyCount[i] != 0) {
      j++;
    }
  }

  totalTests++;
  if (j >= 22) {
    printf("Supply piles not empty: %d so game is not over >>> ", j);
    if (isGameOver(&G) == 0) {
      printf("TEST PASSED\n");
    } else {
      printf("TEST FAILED\n");
      success = 1;
      testsFailed++;
    }
  }

  j = 0;
  
  for (i = 0; i < 3; i++) {
    G.supplyCount[i] = 0; // empty the piles
    j++;
  }

  totalTests++;
  if (j <= 3) {
    printf("Supply piles emptied: %d so game is over >>> ", j);
    if (isGameOver(&G) == 1) {
      printf("TEST PASSED\n");
    } else {
      printf("TEST FAILED\n");
      success = 1;
      testsFailed++;
    }
  }

  if (success == 0) {
    printf("\n >>>>> SUCCESS: %d/%d tests passed %s <<<<<\n\n", totalTests - testsFailed, totalTests, FUNCTION);
  } else {
    printf("\n >>>>> FAILURE: %d/%d tests failed %s <<<<<\n\n", testsFailed, totalTests, FUNCTION);
  }

  return 0;
}