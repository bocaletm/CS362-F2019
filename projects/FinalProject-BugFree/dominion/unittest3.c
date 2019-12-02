#include "unittests.h"

/**************
 * UNIT TEST 3: Remodel case has incorrect conditional statement
 *************/
int unitTestThree() {
	int failed = 0; //used to keep track of test status

	// set your card array
	int k[10] = { mine, copper, feast, gardens, ambassador, remodel, smithy, village, baron, great_hall };

	// declare the game state
	struct gameState G;
	struct gameState* gamePtr = &G;

	//rand seed
	time_t seed = time(0);
	printf("Begin Testing cardEffect for remodel card choices:\n");

	//new game
	memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
	int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

	int result = cardEffect(remodel, curse, gold, 0, gamePtr, 0, 0);

	if (result != -1)	{
		printf("\tFailed: card costs calculated incorrectly\n");
	} else if (result == -1) {
		printf("\tPassed\n");
	}

	printf("Test completed!\n");

	return 0;
}

int main() {
	unitTestThree();
}
