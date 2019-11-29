#include "unittests.h"

/**************
 * UNIT TEST 8: Incorrect recording of bonus coins from actions in cardEffect
 *************/
int unitTestEight() {
  int passed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { ambassador, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;
  struct gameState* gamePtr = &G;

  //rand seed
  time_t seed = time(0); 
  printf("Begin Testing tribute reveal card loop\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

  //set the game state
  //integer to check bonus
  int bonus = 0;
  
  gamePtr->discardCount[0] = 2;
  gamePtr->deckCount[0] = 2;
  gamePtr->discardCount[1] = 2;
  gamePtr->deckCount[1] = 2;
  
  //make sure coins are incremented twice +2
  gamePtr->coins = 0;
  gamePtr->deck[1][gamePtr->deckCount[1]-1] = copper;
  gamePtr->deck[1][gamePtr->deckCount[1]-1] = silver;

  cardEffect(tribute, 0, 0, 0, gamePtr, 0, &bonus);
  gamePtr->hand[0][0] = estate; //ensure baron bonus
  cardEffect(baron, 0, 0, 0, gamePtr, 0, &bonus);

  passed = assertMod(bonus,0);
  if (!passed) {
    printf("\tFailed: bonus coins not processed\n");
  }

  printf("Test completed!\n");

  return 0;
}

int main() {
  unitTestEight();  
}
