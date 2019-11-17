nclude "randomtests.h"

/**************
 * RANDOM TEST 1: BARON
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

  //seed rand
  srand(seed);

  //random param 1 and estate pos
  int param1 = rand() % 2;
  int param2 = 0;
  int param3 = 1;
  int estatePos = rand() % 3;

  if (param1 == 0) {
    // verify that 4 coins were added
    gamePtr->coins = 0;
    baronEffect(param1, param2, param3, gamePtr);
    failed = assertMod(gamePtr->coins,4);
    if (failed) {
      printf("adding 4 coins failed\n");
    }
    // verify that estate in each hand position (fist,middle,last) is discarded
    clearHand(0,gamePtr);
    switch (estatePos) {
      case 0:
        gainCard(estate, gamePtr, 2, 0);
        gainCard(mine, gamePtr, 2, 0);
        gainCard(mine, gamePtr, 2, 0);
        baronEffect(param1, param2, param3, gamePtr);
        failed = assertMod(hasCard(0,gamePtr,estate),0);
        if (failed) {
          printf("first card is estate failed\n");
        }
        break;
      case 1:
        gainCard(mine, gamePtr, 2, 0);
        gainCard(estate, gamePtr, 2, 0);
        gainCard(mine, gamePtr, 2, 0);
        baronEffect(param1, param2, param3, gamePtr);
        failed = assertMod(hasCard(0,gamePtr,estate),0);
        if (failed) {
          printf("second card is estate failed\n");
        }
        break;
      case 2:
        gainCard(mine, gamePtr, 2, 0);
        gainCard(mine, gamePtr, 2, 0);
        gainCard(estate, gamePtr, 2, 0);
        baronEffect(param1, param2, param3, gamePtr);
        failed = assertMod(hasCard(0,gamePtr,estate),0);
        if (failed) {
          printf("last card is estate failed\n");
        }
        break;
    }
  } else {
    // verify that estate is gained
    clearHand(0,gamePtr);
    gainCard(mine, gamePtr, 2, 0);
    gainCard(mine, gamePtr, 2, 0);
    gainCard(mine, gamePtr, 2, 0);
    baronEffect(param1, param2, param3, gamePtr);
    failed = assertMod(hasCard(0,gamePtr,estate),1);
    if (failed) {
      printf("gain estate failed\n");
    }

    // verify that game ends if no estates
    gamePtr->supplyCount[estate] = 1; //set to 1 because function decrements
    baronEffect(param1, param2, param3, gamePtr);
    failed = assertMod(isGameOver(gamePtr),1);
    if (failed) {
      printf("end game due to no estates failed\n");
    }
  } 
 
  printf("Test completed!\n");
 
  return 0;
}

int main() {
  testBaron();  
}
