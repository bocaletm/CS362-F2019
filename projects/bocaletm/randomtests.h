#ifndef DOMINION_RANDOM_TESTS
#define DOMINION_RANDOM_TESTS

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "dominion_helpers.h"
#include "dominion.h"

void clearHand(int player, struct gameState *state);
int hasCard(int player, struct gameState *state, int card);
int assertMod(int a, int b); 
int testBaron(int counter);
int testMine();
int testAmbassador();
int testMinion(int counter);
int testTribute();

#endif
