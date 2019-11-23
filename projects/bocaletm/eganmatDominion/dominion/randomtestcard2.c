#include "randomtests.h"

/**************
 * RANDOM TEST 2: MINION
 *************/
int testMinion(int counter){
  int failed = 0; //used to keep track of test status

  // set your card array
  int k[10] = { minion, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

  // declare the game state
  struct gameState G;
  struct gameState* gamePtr = &G;

  //rand seed
  time_t seed = time(0) - counter; 
  printf("Begin Testing minionCard():\n");

  //new game
  memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
  int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game
  //seed rand
  //srand(seed);

  //random 
  int param1 = rand() % 2;
  int param2 = param1 ^ 1;
  int param3 = rand() % 2;
  int param4 = 0;
  int randCard = (rand() % (24 - 1 + 1)) + 1;
  
  clearHand(0,gamePtr);
  minionCard(param1, param2, param3, param4, gamePtr);
  if (param1) {
    //verify that coins increased
    int oldCoins = gamePtr->coins; 
    minionCard(param1, param2, param3, param4, gamePtr);
    failed = assertMod(gamePtr->coins,(oldCoins+2));
    if (failed) {
      printf("coins were not gained\n");
    }
  } else  if (param2) {
    // verify that card is discarded
    clearHand(param3,gamePtr);
    gainCard(randCard, gamePtr, 2, param3);
    minionCard(param1, param2, param3, param4, gamePtr);
    failed = assertMod(hasCard(param3,gamePtr,randCard),1);
    if (failed) {
      printf("card was not discarded\n");
    }

    //verify that hand was discarded and 4 cards drawn
    clearHand(param3,gamePtr);
    gamePtr->whoseTurn = param3;
    gainCard(minion, gamePtr, 2, param3);
    gainCard(ambassador, gamePtr, 2, param3);
    gainCard(estate, gamePtr, 2, param3);
    gainCard(estate, gamePtr, 2, param3);
    gainCard(feast, gamePtr, 2, param3);
    minionCard(param1, param2, param3, param4, gamePtr);
    failed = assertMod(numHandCards(gamePtr),4);
    if (failed) {
      printf("curr player did not gain 4 cards\n");
    }

    //verify that hand was discarded and 4 cards drawn others
    clearHand(0,gamePtr);
    gamePtr->whoseTurn = param3;
    gainCard(estate, gamePtr, 2, param3);
    gamePtr->whoseTurn = param3 ^ 1;
    clearHand(param3 ^ 1,gamePtr);
    gainCard(estate, gamePtr, 2, param3 ^ 1);
    gainCard(estate, gamePtr, 2, param3 ^ 1);
    gainCard(estate, gamePtr, 2, param3 ^ 1);
    gainCard(estate, gamePtr, 2, param3 ^ 1);
    gainCard(estate, gamePtr, 2, param3 ^ 1);

    gamePtr->whoseTurn = param3;
    minionCard(param1, param2, param3, param4, gamePtr);
    gamePtr->whoseTurn = param3 ^ 1;
    failed = assertMod(numHandCards(gamePtr),4);
    if (failed) {
      printf("other player did not gain 4 cards\n");
    }

  }
  
  printf("Test completed!\n");

  return 0;
}

int main() {
  //rand seed
  time_t seed = time(0); 

  //seed rand
  srand(seed);

  int counter = 1000;
  while (counter > 0) {
    testMinion(counter);  
    counter--;
  }
}
