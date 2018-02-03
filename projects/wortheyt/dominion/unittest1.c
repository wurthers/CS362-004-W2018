/*

CS 362 Assignment 3 -- Unit Test 1
Unit test for dominion.c function shuffle()


*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"



int main (int argc, char* argv[]){




}




int shuffle(int player, struct gameState *state) {
 

	int newDeck[MAX_DECK];
	int newDeckPos = 0;
	int card;
	int i;

	if (state->deckCount[player] < 1)
		return -1;
	qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), compare); 
	/* SORT CARDS IN DECK TO ENSURE DETERMINISM! */

	while (state->deckCount[player] > 0) {
		card = floor(Random() * state->deckCount[player]);
		newDeck[newDeckPos] = state->deck[player][card];
		newDeckPos++;
		for (i = card; i < state->deckCount[player]-1; i++) {
			state->deck[player][i] = state->deck[player][i+1];
		}
		state->deckCount[player]--;
	}
	for (i = 0; i < newDeckPos; i++) {
		state->deck[player][i] = newDeck[i];
		state->deckCount[player]++;
	}

	return 0;
}