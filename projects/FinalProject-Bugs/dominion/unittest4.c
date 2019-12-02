#include "unittests.h"

/**************
 * UNIT TEST 4: gameOver does not loop through all cards
 *************/
int unitTestFour() {
	int failed = 0; //used to keep track of test status

	// set your card array
	int k[10] = { mine, copper, feast, gardens, ambassador, remodel, smithy, village, baron, great_hall };

	// declare the game state
	struct gameState G;
	struct gameState* gamePtr = &G;

	//rand seed
	time_t seed = time(0);
	printf("Begin Testing isGameOver for full card count:\n");

	//new game
	memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
	int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

	// set variables
	gamePtr->supplyCount[salvager] = 0;
	gamePtr->supplyCount[sea_hag] = 0;
	gamePtr->supplyCount[treasure_map] = 0;

	int result = isGameOver(gamePtr);

	if (result != 1)	{
		printf("Failed: isGameOver did not count all cards\n");
	}

	printf("Test completed!\n");

	return 0;
}

int main() {
	unitTestFour();
}
