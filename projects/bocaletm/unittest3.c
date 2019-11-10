#include "unittests.h"

/**************
 * UNIT TEST 3: AMBASSADOR
 *************/
int testAmbassador() {
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;
  struct gameState* gamePtr = &G;

  //rand seed
  time_t seed = time(0); 
  printf("Begin Testing ambassadorEffect():\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

  // verify that invalid choices are not allowed
  clearHand(0,gamePtr);
  failed = assertMod(ambassadorEffect(1, -1, 0, 0, gamePtr),-1);
  if (failed) {
    printf("invalid choice2 allowed\n");
  }

  clearHand(0,gamePtr);
  failed = assertMod(ambassadorEffect(1, 3, 0, 0, gamePtr),-1);
  if (failed) {
    printf("invalid choice2 allowed\n");
  }

  clearHand(0,gamePtr);
  failed = assertMod(ambassadorEffect(1, 0, 1, 0, gamePtr),-1);
  if (failed) {
    printf("invalid choice1 allowed\n");
  }

  // verify that supply count of discarded card is increased
  clearHand(0,gamePtr);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(ambassador, gamePtr, 2, 0);
  gainCard(copper, gamePtr, 2, 0);
  gainCard(copper, gamePtr, 2, 0);
  gainCard(copper, gamePtr, 2, 0);
  gamePtr->supplyCount[mine] = 0;
  ambassadorEffect(0, 1, 1, 0, gamePtr);
  failed = assertMod(gamePtr->supplyCount[mine],0);
  if (failed) {
    printf("supply of discarded card did not increase\n");
  }
  
  // verify that other player gains card
  clearHand(1,gamePtr);
  clearHand(0,gamePtr);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(ambassador, gamePtr, 0, 0);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  gamePtr->supplyCount[mine] = 0;
  ambassadorEffect(0, 1, 1, 0, gamePtr);
  failed = assertMod(hasCard(1,gamePtr,mine),0);
  if (failed) {
    printf("other players failed to gain discarded card\n");
  }

  //verify that  played card discarded
  clearHand(0,gamePtr);
  gainCard(ambassador, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  gainCard(mine, gamePtr, 2, 0);
  gamePtr->supplyCount[mine] = 0;
  ambassadorEffect(1, 1, 0, 0, gamePtr);
  failed = assertMod(hasCard(0,gamePtr,mine),0);
  if (failed) {
    printf("played card not discarded\n");
  }

  //verify that not allowed to discard more than we have
  clearHand(0,gamePtr);
  gainCard(ambassador, gamePtr, 0, 0);
  gainCard(mine, gamePtr, 0, 0);
  gamePtr->supplyCount[mine] = 0;
  failed = assertMod(ambassadorEffect(1, 2, 0, 0, gamePtr),-1);
  if (failed) {
    printf("allowed to discard more cards than player has\n");
  }

  //verify that returned cards are trashed
  clearHand(0,gamePtr);
  gainCard(ambassador, gamePtr, 2, 0);
  gainCard(copper, gamePtr, 2, 0);
  gainCard(copper, gamePtr, 2, 0);
  gamePtr->supplyCount[mine] = 0;
  ambassadorEffect(1, 2, 0, 0, gamePtr);
  failed = assertMod(hasCard(0,gamePtr,copper),0);
  if (failed) {
    printf("returned cards not trashed\n");
  }

  printf("Test completed!\n");

  return 0;
}

int main() {
  testAmbassador();  
}
