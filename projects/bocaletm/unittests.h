#ifndef DOMINION_UNIT_TESTS
#define DOMINION_UNIT_TESTS

#include "dominion_helpers.h"

void clearHand(int player, struct gameState *state);
int hasCard(int player, struct gameState *state, int card);
int testBaron();
int testMine();
int testAmbassador();
int testMinion();
int testTribute();

#endif
