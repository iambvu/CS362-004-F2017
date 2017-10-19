#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>

#define FUNCTION "initializeGame"

int main() {
  int success = 0;
  int testsFailed = 0, totalTests = 0;
  int numPlayers = 2;
  int seed = 1000;
  int i, j;
  int player1 = 0;
  int player2 = 1;
  int estateCount = 0, copperCount = 0;
  int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, great_hall};
  
  struct gameState G;

  initializeGame(numPlayers, kingdomCards, seed, &G);

  printf("----------------- Testing Function: %s ----------------\n", FUNCTION);

  printf("DESCRIPTION: Game is initialized correct number of cards for each card\n\n");

  // at initial start deck should contain 10 cards (7 coppers, 3 estates)
  totalTests++;
  printf("Expected deck size at start of game: 10, Actual deck size: %d >>> ", G.deckCount[player2]);
  if (G.deckCount[player2] == 10) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  // check there are 7 coppers and 3 estates
  for (j = 0; j < G.deckCount[player2]; j++) {
    if (G.deck[player2][j] == estate) {
      estateCount++;
    } else if (G.deck[player2][j] == copper) {
      copperCount++;
    }
  }

  totalTests++;
  printf("Expected estate card count at start of game: 3, Actual estate card count: %d >>> ", estateCount);
  if (estateCount == 3) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  totalTests++;
  printf("Expected copper card count at start of game: 7, Actual copper card count: %d >>> ", copperCount);
  if (copperCount == 7) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  // 10 curses
  totalTests++;
  printf("Expected curse card count in supply at start of game: 10, Actual curse card count: %d >>> ", G.supplyCount[curse]);
  if (G.supplyCount[curse] == 10) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  // 24 victories
  totalTests++;
  printf("Expected estate card count in supply at start of game: 8, Actual estate card count: %d\n", G.supplyCount[estate]);
  printf("Expected duchy card count in supply at start of game: 8, Actual duchy card count: %d\n", G.supplyCount[duchy]);
  printf("Expected province card count in supply at start of game: 8, Actual province card count: %d\n", G.supplyCount[province]);

  int totalVictoryCards = G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province];
  printf("Expected total victory card count at start of game: 24, Actual victory card count: %d >>> ", totalVictoryCards);
  if (totalVictoryCards == 24) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  // treasures
  totalTests++;
  printf("Expected total copper card count in supply at start of game: 46, Actual copper card count: %d >>> ", G.supplyCount[copper]);
  if (G.supplyCount[copper] == 46) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  totalTests++;
  printf("Expected total silver card count in supply at start of game: 40, Actual silver card count: %d >>> ", G.supplyCount[silver]);
  if (G.supplyCount[silver] == 40) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  assert(G.supplyCount[gold] == 30);
  totalTests++;
  printf("Expected total gold card count in supply at start of game: 30, Actual gold card count: %d >>> ", G.supplyCount[gold]);
  if (G.supplyCount[gold] == 30) {
    printf("TEST PASSED\n");
  } else {
    printf("TEST FAILED\n");
    success = 1;
    testsFailed++;
  }

  // assert kingdom cards have correct card counts
  totalTests++;
  int badKingdomCount = 0;
  for (i = 0; i < 10; i++) {
    // printf("kingdom card: %d and supplyCount: %d\n", kingdomCards[i], G.supplyCount[i]);
    switch(kingdomCards[i]) {
      case adventurer:
        printf("Expected total adventurer card count in supply at start of game: 10, Actual adventurer card count: %d\n", G.supplyCount[adventurer]);
        if (G.supplyCount[adventurer] != 10) {
          success = 1;
          badKingdomCount = 1;
        }
        break;
      case embargo:
        printf("Expected total embargo card count in supply at start of game: 10, Actual embargo card count: %d\n", G.supplyCount[embargo]);
        if (G.supplyCount[embargo] != 10) {
          success = 1;
          badKingdomCount = 1;
        }
        break;
      case village:
        printf("Expected total village card count in supply at start of game: 10, Actual village card count: %d\n", G.supplyCount[village]);
        if (G.supplyCount[village] != 10) {
          success = 1;
          badKingdomCount = 1;
        }
        break;
      case minion:
        printf("Expected total minion card count in supply at start of game: 10, Actual minion card count: %d\n", G.supplyCount[minion]);
        if (G.supplyCount[minion] != 10) {
          success = 1;
          badKingdomCount = 1;
        }
        break;
      case mine:
        printf("Expected total mine card count in supply at start of game: 10, Actual mine card count: %d\n", G.supplyCount[mine]);
        if (G.supplyCount[mine] != 10) {
          success = 1;
          badKingdomCount = 1;
        }
        break;
      case cutpurse:
        printf("Expected total cutpurse card count in supply at start of game: 10, Actual cutpurse card count: %d\n", G.supplyCount[cutpurse]);
        if (G.supplyCount[cutpurse] != 10) {
          success = 1;
          badKingdomCount = 1;
        }
        break;
      case sea_hag:
        printf("Expected total sea_hag card count in supply at start of game: 10, Actual sea_hag card count: %d\n", G.supplyCount[sea_hag]);
        if (G.supplyCount[sea_hag] != 10) {
          success = 1;
          badKingdomCount = 1;
        }
        break;
      case tribute:
        printf("Expected total tribute card count in supply at start of game: 10, Actual tribute card count: %d\n", G.supplyCount[tribute]);
        if (G.supplyCount[tribute] != 10) {
          success = 1;
          badKingdomCount = 1;
        }
        break;
      case smithy:
        printf("Expected total smithy card count in supply at start of game: 10, Actual smithy card count: %d\n", G.supplyCount[smithy]);
        if (G.supplyCount[smithy] != 10) {
          success = 1;
          badKingdomCount = 1;
        }
        break;
      case great_hall:
        printf("Expected total great_hall card count in supply at start of game: 8, Actual great_hall card count: %d\n", G.supplyCount[great_hall]);
        if (G.supplyCount[great_hall] != 8) {
          success = 1;
          badKingdomCount = 1;
        }
        break;
    }
  }

  if (badKingdomCount == 1) {
    success = 1;
    testsFailed++;
  } else {
    printf("Kingdom cards have correct count of cards for the game >>> TEST PASSED\n");
  }

  // at start of game both hand and discard should be empty
  printf("Expected total hand count in supply at start of game: 0, Actual hand count: %d\n", G.handCount[player2]);
  printf("Expected total discard count in supply at start of game: 0, Actual discard count: %d\n", G.discardCount[player2]);
  if (G.handCount[player2] == 0 && G.discardCount[player2] == 0) {
    printf("Actual hand count and discard count are empty at start of game >>> TEST PASSED\n");
  } else {
    printf("Actual hand count and discard count not empty at start of game >>> TEST FAILED\n");
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