/*

CS 362 Assignment 3 -- Unit Test 2
Unit test for dominion.c function endTurn()


*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main (int argc, char* argv[]){




}



int endTurn(struct gameState *state) {
	int k;
	int i;
	int currentPlayer = whoseTurn(state);
	
	//Discard hand
	for (i = 0; i < state->handCount[currentPlayer]; i++){
		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
		state->hand[currentPlayer][i] = -1;//Set card to -1
	}
	state->handCount[currentPlayer] = 0;//Reset hand count
		
	//Code for determining the player
	if (currentPlayer < (state->numPlayers - 1)){ 
		state->whoseTurn = currentPlayer + 1;//Still safe to increment
	}
	else{
		state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
	}

	state->outpostPlayed = 0;
	state->phase = 0;
	state->numActions = 1;
	state->coins = 0;
	state->numBuys = 1;
	state->playedCardCount = 0;
	state->handCount[state->whoseTurn] = 0;

	//int k; move to top
	//Next player draws hand
	for (k = 0; k < 5; k++){
		drawCard(state->whoseTurn, state);//Draw a card
	}

	//Update money
	updateCoins(state->whoseTurn, state , 0);

	return 0;
}