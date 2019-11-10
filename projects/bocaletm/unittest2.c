#include "unittests.h"

/**************
 * UNIT TEST 2: MINE
 *************/
int testMine() {
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;
  struct gameState* gamePtr = &G;

  //rand seed
  time_t seed = time(0); 
  printf("Begin Testing mineEffect():\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

  // verify that can't choose non-treasure cards
  // invalid first choice
  clearHand(0,gamePtr);
  gainCard(estate, gamePtr, 0, 0);
  gainCard(copper, gamePtr, 0, 0);
  gainCard(baron, gamePtr, 0, 0);
  failed = assertMod(mineEffect(0, silver, 0, 0,gamePtr),-1);
  if (!failed) {
    printf("invalid choice1 did not result in error\n");
  }

  // invalid second choice
  clearHand(0,gamePtr);
  gainCard(copper, gamePtr, 0, 0);
  gainCard(estate, gamePtr, 0, 0);
  gainCard(baron, gamePtr, 0, 0);
  failed = assertMod(mineEffect(0, estate, 0, 0, gamePtr),-1);
  if (!failed) {
    printf("invalid choice2 did not result in error\n");
  }
  
  //verify that the trade is valid (will improve by 3)
  clearHand(0,gamePtr);
  gainCard(copper, gamePtr, 0, 0);
  gainCard(estate, gamePtr, 0, 0);
  gainCard(baron, gamePtr, 0, 0);
  failed = assertMod(mineEffect(0, gold, 0, 0,gamePtr),-1);
  if (!failed) {
    printf("error: invalid trade was allowed \n");
  }
 
    //last
  clearHand(0,gamePtr);
  gainCard(mine, gamePtr, 0, 0);
  gainCard(mine, gamePtr, 0, 0);
  gainCard(estate, gamePtr, 0, 0);
  baronEffect(1, 0, 1, gamePtr);
  failed = assertMod(hasCard(0,gamePtr,estate),0);
  if (failed) {
    printf("last card is estate failed\n");
  }

  // verify that estate is gained
  clearHand(0,gamePtr);
  gainCard(mine, gamePtr, 0, 0);
  gainCard(mine, gamePtr, 0, 0);
  gainCard(mine, gamePtr, 0, 0);
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
  testMine();  
}
