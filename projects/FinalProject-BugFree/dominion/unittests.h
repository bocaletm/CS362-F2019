#ifndef DOMINION_UNIT_TESTS
#define DOMINION_UNIT_TESTS

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "dominion_helpers.h"
#include "dominion.h"

void clearHand(int player, struct gameState *state);
int hasCard(int player, struct gameState *state, int card);
int assertMod(int a, int b); 
int unitTestFive();
int unitTestSix();
int unitTestSeven();

#endif
