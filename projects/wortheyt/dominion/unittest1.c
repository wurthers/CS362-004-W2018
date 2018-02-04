/*

CS 362 Assignment 3 -- Unit Test 1
Unit test for dominion.c function shuffle()

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


/* 
Preconditions:
	- The game has been initialized
	- The player has a deck of cards

Postconditions:
	- The player's deck is not in the same order it started in
	- The player's deck is in a sufficiently random order
	- Nothing else in the gamestate has been changed
*/



void assert_(int statement){

	if (statement == 0)
		printf("Test FAILED.\n");

	else
		printf("Test OK!\n");

}


int main (int argc, char* argv[]){

	int numPlayers = 4;
	int kc[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; //List borrowed from cardtest4.c
	int rseed = 100;

	struct gameState *game1 = newGame();
	struct gameState *game2 = newGame();


	initializeGame(numPlayers, kc, rseed, game1);
	initializeGame(numPlayers, kc, rseed, game2);

	printf("Checking that both gameStates are identical: ");
	assert_(memcmp(game1, game2, sizeof(struct gameState)) == 0);


	printf("Shuffling decks in game 1...\n");
	int testPlayer;

	for (testPlayer = 0; testPlayer < numPlayers; testPlayer++){

		// Testing code here

	}

	printf("Shuffling decks in game 2...\n");
	for (testPlayer = 0; testPlayer < numPlayers; testPlayer++)
		shuffle(testPlayer, game1);

	printf("Checking that both gameStates are identical: ");
	assert_(memcmp(game1, game2, sizeof(struct gameState)) == 0);


	// struct gameState *before;
	
	// memcpy(&before, &game1, sizeof(struct gameState));




	// printf("Game initialized.\n");


	free(game1);
	free(game2);
}



// int shuffle(int player, struct gameState *state) {

// 	int newDeck[MAX_DECK];
// 	int newDeckPos = 0;
// 	int card;
// 	int i;

// 	if (state->deckCount[player] < 1)
// 		return -1;
// 	qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), compare); 
// 	/* SORT CARDS IN DECK TO ENSURE DETERMINISM! */

// 	while (state->deckCount[player] > 0) {
// 		card = floor(Random() * state->deckCount[player]);
// 		newDeck[newDeckPos] = state->deck[player][card];
// 		newDeckPos++;
// 		for (i = card; i < state->deckCount[player]-1; i++) {
// 			state->deck[player][i] = state->deck[player][i+1];
// 		}
// 		state->deckCount[player]--;
// 	}
// 	for (i = 0; i < newDeckPos; i++) {
// 		state->deck[player][i] = newDeck[i];
// 		state->deckCount[player]++;
// 	}

// 	return 0;
// }