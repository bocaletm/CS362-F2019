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
  printf("Begin Testing mineCard():\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

  // verify that can't choose non-treasure cards
  // invalid first choice
  clearHand(0,gamePtr);
  gainCard(estate, gamePtr, 0, 0);
  gainCard(copper, gamePtr, 0, 0);
  gainCard(baron, gamePtr, 0, 0);
  failed = assertMod(mineCard(0, silver, 0, 0,gamePtr),-1);
  if (!failed) {
    printf("invalid choice1 did not result in error\n");
  }

  // invalid second choice
  clearHand(0,gamePtr);
  gainCard(copper, gamePtr, 0, 0);
  gainCard(estate, gamePtr, 0, 0);
  gainCard(baron, gamePtr, 0, 0);
  failed = assertMod(mineCard(0, estate, 0, 0, gamePtr),-1);
  if (!failed) {
    printf("invalid choice2 did not result in error\n");
  }
  
  //verify that the trade is valid (will improve by 3)
  clearHand(0,gamePtr);
  gainCard(silver, gamePtr, 0, 0);
  gainCard(estate, gamePtr, 0, 0);
  gainCard(baron, gamePtr, 0, 0);
  failed = assertMod(mineCard(0, copper, 0, 0,gamePtr),-1);
  if (!failed) {
    printf("error: invalid trade was allowed \n");
  }
  
  //verify card was gained
  clearHand(0,gamePtr);
  gainCard(copper, gamePtr, 0, 0);
  mineCard(0, gold, 0, 0,gamePtr);
  failed = assertMod(hasCard(0,gamePtr,gold),0);
  if (!failed) {
    printf("error: failed to gain card \n");
  }

  //verify card was discarded
  clearHand(0,gamePtr);
  gainCard(mine, gamePtr, 0, 0);
  gainCard(copper, gamePtr, 0, 0);
  mineCard(0, gold, 0, 0,gamePtr);
  failed = assertMod(hasCard(0,gamePtr,mine),1);
  if (!failed) {
    printf("error: failed to discard current card \n");
  }

  //verify card was trashed 
  clearHand(0,gamePtr);
  gainCard(mine, gamePtr, 0, 0);
  gainCard(copper, gamePtr, 0, 0);
  mineCard(2, gold, 0, 0,gamePtr);
  failed = assertMod(hasCard(0,gamePtr,copper),1);
  if (!failed) {
    printf("error: failed to discard trashed \n");
  }

  printf("Test completed!\n");

  return 0;
}

int main() {
  testMine();  
}
