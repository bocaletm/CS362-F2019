#include "unittests.h"

/**************
 * UNIT TEST 6:  Incorrect logic for feast case statement
 *************/
int unitTestSix() {
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { ambassador, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;
  struct gameState* gamePtr = &G;

  //rand seed
  time_t seed = time(0); 
  printf("Begin Testing feast case statement\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

  //set the game state
  gamePtr->coins = 0;
  //should not gain any coins as result of playing card
  cardEffect(feast, ambassador, 0, 0, gamePtr, 0, 0);
  failed = assertMod(gamePtr->coins,0);
  if (failed) {
    printf("\tFailed: feast card resulted in gaining extra coins\n");
  } else {
    printf("\tPassed!\n");
  }

  printf("Test completed!\n");

  return 0;
}

int main() {
  unitTestSix();  
}
