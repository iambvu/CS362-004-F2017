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

#define TESTCARD "adventurer"

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

  printf("TEST: +2 treasure cards\n");

  printf("RANDOM TESTS.\n");

  srand(time(NULL));

  int n, i;

  for (n = 0; n < 250; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(rand() % 256);
    }

    // numPlayers = floor(rand() % 4);

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
    // G.deckCount[thisPlayer + 1] = floor(rand() % MAX_DECK);
    // G.discardCount[thisPlayer + 1] = floor(rand() % MAX_DECK);
    // G.handCount[thisPlayer + 1] = floor(rand() % MAX_HAND);

    // set player hands
    // for (i = 0; i < 5; i++) {
    //   G.hand[thisPlayer][i] = floor(rand() % 26);
    //   G.hand[thisPlayer + 1][i] = floor(rand() % 26);
    // }

    G.whoseTurn = thisPlayer;

    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, bonus);

    printf("Checking hand and deck count after playing adventurer card...\n");

    totalTests++;
    int newCards = 2;   // two new treasure cards are added to hand after playing adventurer card
              // any none treasure cards drawn are discarded
    printf("Actual hand count: %d, expected: %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - 1); // discard adventurer card just played
    printf("Actual deck count: %d, expected: %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - ((testG.discardCount[thisPlayer] + newCards) - G.discardCount[thisPlayer]));
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - 1 &&
      G.deckCount[thisPlayer] - ((testG.discardCount[thisPlayer] + newCards) - G.discardCount[thisPlayer])) {
      printf("Hand and deck have expected count >>> TEST PASSED\n");
    }
    else {
      printf("Hand and deck do not have expected count >>> TEST FAILED\n");
      success = 1;
      testsFailed++;
    }

    printf("Checking top two cards in hand are treasure cards after playing adventurer card...\n");

    totalTests++;
    int card1 = testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1];
    int card2 = testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2];
    cardNumToName(card1, name1);
    cardNumToName(card2, name2);

    printf("Actual first new card in hand: %s\n", name1);
    printf("Actual second new card in hand: %s\n", name2);
    if ((card1 == copper || card1 == silver || card1 == gold) && (card2 == copper || card2 == silver || card2 == gold)) {
      printf("Top two cards in hand are treasure cards >>> TEST PASSED\n");
    }
    else {
      printf("Top two cards in hand are not treasure cards >>> TEST FAILED\n");
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