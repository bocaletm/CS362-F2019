#include "unittests.h"

/**************
 * UNIT TEST 7: Tribute card extra iteration for tributeRevealedCards
 *************/
int unitTestSeven() {
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { tribute, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

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
  //meke sure any player will trigger tribute reveal cards
  gamePtr->discardCount[0] = 2;
  gamePtr->deckCount[0] = 2;
  gamePtr->discardCount[1] = 2;
  gamePtr->deckCount[1] = 2;
  
  //make sure coins are incremented twice +2
  gamePtr->coins = 0;
  gamePtr->deck[1][gamePtr->deckCount[1]-1] = copper;
  gamePtr->deck[1][gamePtr->deckCount[1]-1] = silver;
  
  cardEffect(tribute, 0, 0, 0, gamePtr, 0, 0);
  failed = assertMod(gamePtr->coins,4);
  if (failed) {
    printf("\tFailed: tribute revealed loop\n");
  }

  printf("Test completed!\n");

  return 0;
}

int main() {
  unitTestSeven();  
}
