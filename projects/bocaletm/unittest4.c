#include "unittests.h"

/**************
 * UNIT TEST 4: MINION
 *************/
int testMinion(){
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { minion, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;
  struct gameState* gamePtr = &G;

  //rand seed
  time_t seed = time(0); 
  printf("Begin Testing minionEffect():\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

  // verify that card is discarded
  clearHand(0,gamePtr);
  gainCard(mine, gamePtr, 2, 0);
  minionEffect(0, 1, 0, 0, gamePtr);
  failed = assertMod(hasCard(0,gamePtr,mine),1);
  if (failed) {
    printf("card was not discarded\n");
  }

  //verify that coins increased
  int oldCoins = gamePtr->coins; 
  minionEffect(1, 0, 0, 0, gamePtr);
  failed = assertMod(gamePtr->coins,(oldCoins+2));
  if (failed) {
    printf("coins were not gained\n");
  }
  
  //verify that hand was discarded and 4 cards drawn
  clearHand(0,gamePtr);
  gamePtr->whoseTurn = 0;
  gainCard(minion, gamePtr, 2, 0);
  gainCard(ambassador, gamePtr, 2, 0);
  gainCard(estate, gamePtr, 2, 0);
  gainCard(estate, gamePtr, 2, 0);
  gainCard(feast, gamePtr, 2, 0);
  minionEffect(0, 1, 0, 0, gamePtr);
  failed = assertMod(numHandCards(gamePtr),4);
  if (failed) {
    printf("curr player did not gain 4 cards\n");
  }

  //verify that hand was discarded and 4 cards drawn others
  clearHand(0,gamePtr);
  gamePtr->whoseTurn = 0;
  gainCard(estate, gamePtr, 2, 0);
  gamePtr->whoseTurn = 1;
  clearHand(1,gamePtr);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);
  gainCard(estate, gamePtr, 2, 1);

  gamePtr->whoseTurn = 0;
  minionEffect(0, 1, 0, 0, gamePtr);
  gamePtr->whoseTurn = 1;
  failed = assertMod(numHandCards(gamePtr),4);
  if (failed) {
    printf("other player did not gain 4 cards\n");
  }

  printf("Test completed!\n");

  return 0;
}

int main() {
  testMinion();  
}
