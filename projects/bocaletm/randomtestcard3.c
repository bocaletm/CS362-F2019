#include "randomtests.h"

/**************
 * UNIT TEST 5: TRIBUTE
 *************/
int testTribute(int counter) {
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;
  struct gameState* gamePtr = &G;

  //rand seed
  time_t seed = time(0); 
  printf("Begin Testing tributeEffect():\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

  //random 
  int param1 = rand() % 2;
  int param2 = param1 ^ 1;

  // verify that discard count is decreased
  gamePtr->discardCount[param1] = 1;
  gamePtr->deckCount[param1] = 0;
  tributeEffect(param2, param1, gamePtr);
  failed = assertMod(gamePtr->discardCount[param1],0);
  if (failed) {
    printf("decrementing discard count of next player failed\n");
  }

  // verify that deck count is decreased
  gamePtr->discardCount[param1] = 0;
  gamePtr->deckCount[param1] = 1;
  tributeEffect(param2, param1, gamePtr);
  failed = assertMod(gamePtr->deckCount[param1],0);
  if (failed) {
    printf("decrementing deck of next player failed\n");
  }

  // verify that discard moves to deck
  gamePtr->discardCount[param1] = 2;
  gamePtr->discard[param1][0] = mine;
  gamePtr->discard[param1][1] = estate;
  gamePtr->deckCount[param1] = 0;
  tributeEffect(param2, param1, gamePtr); 
  failed = assertMod(gamePtr->deckCount[param1],2);
  if (failed) {
    printf("failed to move discard to deck\n");
  }
  failed = assertMod(gamePtr->deck[1],estate);
  if (failed) {
    printf("failed to move discard to deck\n");
  }
  
  //check tribute revealed (duplicate card)
  clearHand(param1,gamePtr);
  gainCard(estate, gamePtr, 2, param1);
  gainCard(estate, gamePtr, 2, param1);
  gainCard(estate, gamePtr, 2, param1);
  gainCard(estate, gamePtr, 2, param1);
  gainCard(estate, gamePtr, 2, param1);
  tributeEffect(param2, param1, gamePtr); 
  failed = assertMod(gamePtr->playedCards[gamePtr->playedCardCount],estate);
  if (failed) {
    printf("failed to drop duplicate tribute card\n");
  }

  //check  for currency cards
  clearHand(param1,gamePtr);
  gainCard(copper, gamePtr, 2, param1);
  gainCard(silver, gamePtr, 2, param1);
  gainCard(gold, gamePtr, 2, param1);
  gainCard(copper, gamePtr, 2, param1);
  gainCard(silver, gamePtr, 2, param1);
  gainCard(gold, gamePtr, 2, param1);
  tributeEffect(param2, param1, gamePtr); 
  gamePtr->coins = 0;
  failed = assertMod(gamePtr->coins,2);
  if (failed) {
    printf("failed to pay tribute from currency card\n");
  }

  //check victory card result
  clearHand(param1,gamePtr);
  gainCard(estate, gamePtr, 2, param1);
  gainCard(estate, gamePtr, 2, param1);
  gainCard(estate, gamePtr, 2, param1);
  gainCard(estate, gamePtr, 2, param1);
  gainCard(estate, gamePtr, 2, param1);
  gamePtr->whoseTurn = param1;
  int player2Cards = numHandCards(gamePtr);
  gamePtr->whoseTurn = param2;
  tributeEffect(param2, param1, gamePtr); 
  gamePtr->whoseTurn = param1;
  failed = assertMod(numHandCards(gamePtr),(player2Cards + 2));
  if (failed) {
    printf("failed to draw cards as vicory tribute\n");
  }

  printf("Test completed!\n");

  return 0;
}

int main() {
  //rand seed
  time_t seed = time(0); 

  //seed rand
  srand(seed);

  int counter = 1000;
  while (counter > 0) {
    testTribute(counter);  
    counter--;
  }
}
