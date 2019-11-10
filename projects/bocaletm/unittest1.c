#include "unittests.h"

/**************
 * UNIT TEST 1: BARON
 *************/
int testBaron() {
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;
  struct gameState* gamePtr = &G;

  //rand seed
  time_t seed = time(0); 
  printf("Begin Testing baronEffect():\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

  // verify that 4 coins were added
  gamePtr->coins = 0;
  baronEffect(1, 0, 1, gamePtr);
  failed = assertMod(gamePtr->coins,4);
  if (failed) {
    printf("adding 4 coins failed\n");
  }

  // verify that estate in each hand position (fist,middle,last) is discarded
    //first
  clearHand(0,gamePtr);
  gainCard(estate, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  baronEffect(1, 0, 1, gamePtr);
  failed = assertMod(hasCard(0,gamePtr,estate),0);
  if (failed) {
    printf("first card is estate failed\n");
  }

    //middle
  clearHand(0,gamePtr);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(estate, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  baronEffect(1, 0, 1, gamePtr);
  failed = assertMod(hasCard(0,gamePtr,estate),0);
  if (failed) {
    printf("second card is estate failed\n");
  }

    //last
  clearHand(0,gamePtr);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(estate, gamePtr, 2, 0);
  baronEffect(1, 0, 1, gamePtr);
  failed = assertMod(hasCard(0,gamePtr,estate),0);
  if (failed) {
    printf("last card is estate failed\n");
  }

  // verify that estate is gained
  clearHand(0,gamePtr);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  baronEffect(0, 0, 1, gamePtr);
  failed = assertMod(hasCard(0,gamePtr,estate),1);
  if (failed) {
    printf("gain estate failed\n");
  }

  // verify that game ends if no estates
  gamePtr->supplyCount[estate] = 1; //set to 1 because function decrements
  baronEffect(0, 0, 1, gamePtr);
  failed = assertMod(isGameOver(gamePtr),1);
  if (failed) {
    printf("end game due to no estates failed\n");
  }

  printf("Test completed!\n");

  return 0;
}

int main() {
  testBaron();  
}
