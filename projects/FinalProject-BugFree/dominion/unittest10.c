#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "unittests.h"

int main()
{
	struct gameState G;
	int choice1 = 1, choice2 = 2, choice3 = 0, handpos = 0;
	int randomSeed = 1000;
	int numPlayers = 2;
	//int currentPlayer = 0;
	
	int k[10] = {mine, tribute, smithy, baron, minion, ambassador, sea_hag, gardens, village, adventurer};

	initializeGame(numPlayers, k, randomSeed, &G);

	int bonus = 0;

	//set player 1 hand to be able to select curse cards as the card to discard
	G.hand[0][0] = ambassador;
	G.hand[0][1] = curse;
	G.hand[0][2] = curse;
	G.hand[0][3] = curse;
	G.hand[0][4] = curse;

	G.handCount[0] = 5;


	printf("\nTesting For bug in Ambassador card\n");

	int failed = cardEffect(ambassador, choice1, choice2, choice3, &G, handpos, &bonus);

	//with current bug, does not recognize duplicate cards in player's hand to be able to discard
	//once bug is fixed, game can recognize duplicate cards and complete run through of ambassador case
	if (failed >= 0)
	{
		printf("Bug corrected, ambassador bug fixed\n\n");
	}

	else
	{
		printf("Bug detected in ambassador card.  Player not recognized to have enough cards to discard\n\n");
	}
	
	return 0;


}