/*

CS 362 Assignment 3 -- Unit Test 4
Unit test for dominion.c function buyCard()

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main (int argc, char* argv[]){




}



int buyCard(int supplyPos, struct gameState *state) {
	int who;
	if (DEBUG){
		printf("Entering buyCard...\n");
	}

	// I don't know what to do about the phase thing.

	who = state->whoseTurn;

	if (state->numBuys < 1){
		if (DEBUG)
			printf("You do not have any buys left\n");
		return -1;
	} else if (supplyCount(supplyPos, state) <1){
		if (DEBUG)
			printf("There are not any of that type of card left\n");
		return -1;
	} else if (state->coins < getCost(supplyPos)){
		if (DEBUG) 
			printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
		return -1;
	} else {
		state->phase=1;
		//state->supplyCount[supplyPos]--;
		gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)
	
		state->coins = (state->coins) - (getCost(supplyPos));
		state->numBuys--;
		if (DEBUG)
			printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
	}

	//state->discard[who][state->discardCount[who]] = supplyPos;
	//state->discardCount[who]++;
		
	return 0;
}
