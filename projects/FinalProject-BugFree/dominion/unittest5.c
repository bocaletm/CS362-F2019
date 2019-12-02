#include "unittests.h"

/**************
 * UNIT TEST 5: scoreFor function uses wrong count variable
 *************/
int unitTestFive() {
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;
  struct gameState* gamePtr = &G;

  //rand seed
  time_t seed = time(0); 
  printf("Begin Testing scoreFor() count variable:\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

  //set the game state
  gamePtr->handCount[0] = 0;
  gamePtr->discardCount[0] = 0;
  gamePtr->deckCount[0] = 1;
  gamePtr->deck[0][0] = province; //should add 6 points
  failed = assertMod(scoreFor(0,gamePtr),6);
  if (failed) {
    printf("\tFailed: did not score deckCount\n");
  } else {
    printf("\tPassed!\n");
  }

  printf("Test completed!\n");

  return 0;
}

int main() {
  unitTestFive();  
}
