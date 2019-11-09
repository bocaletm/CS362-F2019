#include "unittest.h"

/**************
 * check if player has card
 **************/
int hasCard(int player, struct gameState *state, int card) {
  int hasIt = 0;
  int handCount = numHandCards(player,state); 
  int i;
  for (i=0;i<handCount;i++) {
    if (gameState->hand[i] == card) {
      hasIt = 1;
      break;
    }
  }
  return hasIt;
}

/**************
 * clear a player's hand
 **************/
void clearHand(int player,struct gameState* state) {
  int handCount = numHandCards(player,state); 
  int i;
  for (i=0;i<handCount;i++) {
    discardCard(i,player,state,0);
  }
}

/**************
 * modified assert function
 **************/
int assertMod(int a, int b) {
  if (a == b) {
    return 0; 
  } else { 
    return 1;
  }
}
