/*

CS 362 Assignment 4 -- Random Tester 1
Random tester for dominion.c card Village

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>


#define TESTCARD "village"


int assert_(int statement){

	if (statement == 0){
		printf("TEST FAILED.\n\n");
		return 0;
	}

	else{
		printf("TEST OK!\n\n");
		return 1;
	}
}

// Generate a random deck with an arbitrary number of treasures
void generateDeck(struct gameState* game, int player, int kc[10], int decksize){

	if (decksize > MAX_DECK)
		decksize = MAX_DECK;

	if (decksize < 1)
		decksize = 1;

	int i;
	int card;

	for (i = 0; i < decksize; i++){
		card = (rand() % 14);

		if (card < 10){
			card = kc[card]; // If not a treasure, use a kingdom card
		}

		else if (card >= 10){ // copper = 4, silver = 5, gold = 6
			card = card - 6; // Transpose to one of the treasure cards
		}

		game->deck[player][i] = card;

	}
	
	game->deckCount[player] = decksize;

}


int main (int argc, char* argv[]){

	srand(time(NULL));

	int numTests = 10;	// How many full cycles of the test suite to run?

	int numPlayers;
	int testPlayer;
	int kc[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; //List borrowed from cardtest4.c; //List borrowed from cardtest4.c
	int rseed = 100;
	int coinBonus;
	int handPos = 0;
	coinBonus = 0; // cardEffect expects a 0 passed in from playCard()


	int totalTests = 0;
	int passedTests = 0;

	// // Instantiate some games.
	struct gameState *pre = newGame();	// Storage for pre-card game state
	struct gameState *post = newGame();	// The game we're going to operate on
	struct gameState clean = { 0 };		// clean will be used to erase structs every loop

	int n;
	// Main Testing Loop : Rnage = 0-numTests
	for (n = 0; n < numTests; n++) {

		printf("On Test Loop #%d\n", n);
		printf("Random Parameters:\n");
		numPlayers = (rand() % 3) + 2;	// MAX_PLAYERS == 4, so we'll be kind. Range 2-4
		testPlayer = (rand() % 4);		// testPlayer; Range 0-3

		printf("Number of players: %d\n", numPlayers);
		printf("Testing player: %d\n", testPlayer);

		// Initialize game to start
		initializeGame(numPlayers, kc, rseed, post);

		int decksize = (rand() % MAX_DECK - 1) + 1; 	// Decksize should be between 1 and MAX_DECK
		generateDeck(post, testPlayer, kc, decksize);

		handPos = 0;					// This is bound to cause some issues
		post->hand[testPlayer][handPos] = village;

		// Copy game state into test scenario
		memcpy(pre, post, sizeof(struct gameState));

		// Call CardEffect() using card name and default parameters
		cardEffect(village, 0, 0, 0, post, handPos, &coinBonus);


		printf("\n********* TESTING CARD %s *********\n", TESTCARD);
		printf("Number of cards in hand before playing %s = %d.\n", TESTCARD, pre->handCount[testPlayer]);
		printf("Number of cards in deck before playing %s = %d.\n\n", TESTCARD, pre->deckCount[testPlayer]);

		// Call cardEffect() with smithy passed in as card
		cardEffect(village, 0, 0, 0, post, handPos, &coinBonus);

		// Test: Number of cards in hand after == number before
		printf("******* TEST %d: Number of cards in hand *******\n", totalTests);
		printf("Number of cards in hand after playing %s = %d; Target number = %d....", TESTCARD, post->handCount[testPlayer], pre->handCount[testPlayer]);
		passedTests += assert_(post->handCount[testPlayer] == pre->handCount[testPlayer]);
		totalTests += 1;

		// Test: Number of cards left in deck -= 1
		printf("******* TEST %d: Number of cards in deck *******\n", totalTests);
		printf("Number of cards in deck after playing %s = %d; Target number = %d....", TESTCARD, post->deckCount[testPlayer], pre->deckCount[testPlayer] - 3);
		passedTests += assert_(post->deckCount[testPlayer] == pre->deckCount[testPlayer] - 1);
		totalTests += 1;

		// Test: Number of actions after playing += 1 [accounting for the action used by playing this card]
		printf("******* TEST %d: Number of actions *******\n", totalTests);
		printf("Number of actions after playing %s = %d; Target number = %d....", TESTCARD,
				post->numActions, pre->numActions + 1);
		passedTests += assert_(post->numActions == pre->numActions + 1);
		totalTests += 1;

		*pre = clean;
		*post = clean;

	}

	printf("\n RANDOM TESTING COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);

	free(pre);
	free(post);	

}