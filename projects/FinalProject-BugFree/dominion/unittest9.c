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
	//int choice1 = 0, choice2 = 1, choice3 = 0, handpos = 0;
	int randomSeed = 1000;
	int numPlayers = 2;
	//int currentPlayer = 0;
	
	int k[10] = {mine, tribute, smithy, baron, minion, ambassador, sea_hag, gardens, village, adventurer};

	initializeGame(numPlayers, k, randomSeed, &G);

	int bonus = 0;

	//prepare game to allow for cards to be revealed in Tribute card effect
	G.discardCount[0] = 2;
  	G.deckCount[0] = 4;
  	G.discardCount[1] = 2;
  	G.deckCount[1] = 4;
	
	//Set cards to be revealed in tribute card
	G.deck[1][G.deckCount[1]-1] = silver;
	
	G.deck[1][G.deckCount[1]-3] = silver;
	

	G.coins = 0;
	G.numActions = 0;
	G.playedCardCount = 0;


	printf("\nTesting For bug in Tribute card\n");

	cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
	

	if (G.numActions > 0)
	{		
		printf("Card not handled correctly, duplicate card added actions instead of no effect\n\n");
	}

	else
	{
		printf("Card handled correctly, no bug\n\n");
	}



	return 0;


}