#include "unittests.h"

/**************
 * UNIT TEST 1: discardCard function does not work with mine or tribute cards
 *************/
int unitTestOne() {
	int failed = 0; //used to keep track of test status

	// set your card array
	int k[10] = { mine, copper, feast, gardens, ambassador, remodel, smithy, village, baron, great_hall };

	// declare the game state
	struct gameState G;
	struct gameState* gamePtr = &G;

	//rand seed
	time_t seed = time(0);
	printf("Begin Testing cardEffect for trash card:\n");

	//new game
	memset(gamePtr, 23, sizeof(struct gameState)); //set the game state
	int r = initializeGame(2, k, (int)seed, gamePtr); //initialize a new game

	int playedCardCountOld = gamePtr->playedCardCount;

	cardEffect(mine, copper, silver, 0, gamePtr, 0, 0);


	if (playedCardCountOld != gamePtr->playedCardCount)	{
		printf("Failed: did not trash card\n");
	}

	printf("Test completed!\n");

	return 0;
}

int main() {
	unitTestOne();
}
