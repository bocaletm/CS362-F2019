#include "unittests.h"

/**************
 * UNIT TEST 2: Mine cardEffect function incorrectly checks cost of trashed card
 *************/
int unitTestTwo() {
	int failed = 0; //used to keep track of test status

	// set your card array
	int k[10] = { mine, copper, feast, gardens, ambassador, remodel, smithy, village, baron, great_hall };

	// declare the game state
	struct gameState G;
	struct gameState* gamePtr = &G;

	//rand seed
	time_t seed = time(0);
	printf("Begin Testing Mine for trashed card cost:\n");

	//new game
	memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
	int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

	int result = cardEffect(mine, curse, gold, 0, gamePtr, 0, 0);

	if (result != -1)	{
		printf("Failed: cost of gained treasure exceeds cost of trashed\n");
	}

	printf("Test completed!\n");

	return 0;
}

int main() {
	unitTestTwo();
}
