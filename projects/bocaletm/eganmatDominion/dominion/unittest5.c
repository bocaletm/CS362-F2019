#include "unittests.h"

/**************
 * UNIT TEST 5: TRIBUTE
 *************/
int testTribute() {
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;
  struct gameState* gamePtr = &G;

  //rand seed
  time_t seed = time(0); 
  printf("Begin Testing tributeCard():\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

  // verify that discard count is decreased
  gamePtr->discardCount[1] = 1;
  gamePtr->deckCount[1] = 0;
  tributeCard(0, 1, gamePtr);
  failed = assertMod(gamePtr->discardCount[1],0);
  if (failed) {
    printf("decrementing discard count of next player failed\n");
  }

  // verify that deck count is decreased
  gamePtr->discardCount[1] = 0;
  gamePtr->deckCount[1] = 1;
  tributeCard(0, 1, gamePtr);
  failed = assertMod(gamePtr->deckCount[1],0);
  if (failed) {
    printf("decrementing deck of next player failed\n");
  }

  // verify that discard moves to deck
  gamePtr->discardCount[1] = 2;
  gamePtr->discard[1][0] = mine;
  gamePtr->discard[1][1] = estate;
  gamePtr->deckCount[1] = 0;
  tributeCard(0, 1, gamePtr); 
  failed = assertMod(gamePtr->deckCount[1],2);
  if (failed) {
    printf("failed to move discard to deck\n");
  }
  failed = assertMod(gamePtr->deck[1],estate);
  if (failed) {
    printf("failed to move discard to deck\n");
  }
  
  //check tribute revealed (duplicate card)
  clearHand(1,gamePtr);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  tributeCard(0, 1, gamePtr); 
  failed = assertMod(gamePtr->playedCards[gamePtr->playedCardCount],estate);
  if (failed) {
    printf("failed to drop duplicate tribute card\n");
  }

  //check  for currency cards
  clearHand(1,gamePtr);
  gainCard(copper, gamePtr, 2, 1);
  gainCard(silver, gamePtr, 2, 1);
  gainCard(gold, gamePtr, 2, 1);
  gainCard(copper, gamePtr, 2, 1);
  gainCard(silver, gamePtr, 2, 1);
  gainCard(gold, gamePtr, 2, 1);
  tributeCard(0, 1, gamePtr); 
  gamePtr->coins = 0;
  failed = assertMod(gamePtr->coins,2);
  if (failed) {
    printf("failed to pay tribute from currency card\n");
  }

  //check victory card result
  clearHand(1,gamePtr);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  gamePtr->whoseTurn = 1;
  int player2Cards = numHandCards(gamePtr);
  gamePtr->whoseTurn = 0;
  tributeCard(0, 1, gamePtr); 
  gamePtr->whoseTurn = 1;
  failed = assertMod(numHandCards(gamePtr),(player2Cards + 2));
  if (failed) {
    printf("failed to draw cards as vicory tribute\n");
  }

  printf("Test completed!\n");

  return 0;
}

int main() {
  testTribute();  
}
