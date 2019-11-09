#include "unittest.h"

/**************
 * UNIT TEST 1: BARON
 *************/
int testBaron() {
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;

  // declare the arrays
  int coppers[MAX_HAND]; 
  int silvers[MAX_HAND]; 
  int golds[MAX_HAND];

  //rand seed
  int seed = time(0); 
  printf("Begin Testing baronEffect():\n");

  //new game
  memset(&G, 23, sizeof(struct gameState)); //set the game state
  r = initializeGame(2, k, seed, &G); //initialize a new game

  // verify that 4 coins were added
  gameState->coins = 0;
  baronEffect(1, 0, 1, gameState);
  failed = assertMod(gameState->coins,4);
  if (failed) {
    printf("adding 4 coins failed\n");
  }

  // verify that estate in each hand position (fist,middle,last) is discarded
    //first
  clearHand(0,gameState);
  gainCard(estate, gameState, 0, 0);
  gainCard(mine, gameState, 0, 0);
  gainCard(mine, gameState, 0, 0);
  baronEffect(1, 0, 1, gameState);
  passed = assertMod(hasCard(0,gameState,estate),0);
  if (failed) {
    printf("first card is estate failed\n");
  }

  //middle
  clearHand(0,gameState);
  gainCard(mine, gameState, 0, 0);
  gainCard(estate, gameState, 0, 0);
  gainCard(mine, gameState, 0, 0);
  baronEffect(1, 0, 1, gameState);
  failed = assertMod(hasCard(0,gameState,estate),0);
  if (failed) {
    printf("second card is estate failed\n");
  }

  //last
  clearHand(0,gameState);
  gainCard(mine, gameState, 0, 0);
  gainCard(mine, gameState, 0, 0);
  gainCard(estate, gameState, 0, 0);
  baronEffect(1, 0, 1, gameState);
  failed = assertMod(hasCard(0,gameState,estate),0);
  if (failed) {
    printf("last card is estate failed\n");
  }

  // verify that estate is gained
  // verify that game ends if no estates
  assert(G.coins == something); // check a condition
  assert(some condition);

  // adjust the state of your variables to continue testing
  // comment on what this is going to test 
  memset(&G, 0, sizeof(struct gameState)); 
  r = initializeGame(3, k, seed, &G); 
  G.handCount[p] = handCount; 
  memcpy(G.hand[p], silvers, sizeof(int) * handCount);

  // call the refactored function again 
  myrefactoredfunction(p, &G, bonus);

  // verify that your asserts pass, for the bugs your asserts may fail
  assert(G.coins == something); // check a condition
  assert(some condition);
  assert(some condition);

  printf("Test completed!\n");
}
