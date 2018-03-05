/*

CS 362 Assignment 4 -- Random Tester 2
Random tester for dominion.c card Baron

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>

#define TESTCARD "baron"


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


// Function to count the number of estates in player's hand
void countEstates(struct gameState *game, int player, int *numEstHand, int *numEstDiscard){

	int i;
	int cur;
	*numEstHand = 0;
	*numEstDiscard = 0;

	for (i = 0; i < game->handCount[player]; i++){
		cur = game->hand[player][i];
		if (cur == estate)
			*numEstHand += 1;
	}

	for (i = 0; i < game->discardCount[player]; i++){
		cur = game->discard[player][i];
		if (cur == estate)
			*numEstDiscard += 1;
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
	int handPos;
	int choice1;
	coinBonus = 0; // cardEffect expects a 0 passed in from playCard()


	int totalTests = 0;
	int passedTests = 0;

	// // Instantiate some games.
	struct gameState *pre = newGame();	// Storage for pre-card game state
	struct gameState *post = newGame();	// The game we're going to operate on
	struct gameState clean = { 0 };		// clean will be used to erase structs every loop

	int estPreHand, estPostHand;
	int estPreDiscard, estPostDiscard;

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

		choice1 = rand() % 2;
		handPos = 0;					// This is bound to cause some issues
		
		post->hand[testPlayer][handPos] = baron;

		if (rand() % 2 == 1)
			post->hand[testPlayer][handPos + 1] = estate; // Coin flip on whether to guarantee an estate

		// Copy game state into test scenario
		memcpy(pre, post, sizeof(struct gameState));

		// Call CardEffect() using card name and default parameters
		cardEffect(baron, choice1, 0, 0, post, handPos, &coinBonus);

		// Count estates before and after playing card [in both hand and discard piles]
		countEstates(pre, testPlayer, &estPreHand, &estPreDiscard);
		countEstates(post, testPlayer, &estPostHand, &estPostDiscard);

		printf("\n*********TESTING CARD %s WITH CHOICE %d *********\n\n", TESTCARD, choice1);

		printf("******* TEST %d: Number of Buys after playing *******\n", totalTests);
		printf("Number of Buys after playing %s = %d; Target number = %d....", TESTCARD,
				post->numBuys, pre->numBuys + 1);
		passedTests += assert_(post->numBuys == pre->numBuys + 1);
		totalTests += 1;

		if (choice1 == 0){	// Don't Discard
			printf("Not Discarding -- Gain an Estate!\n");

			printf("******* TEST %d: Number of cards in hand *******\n", totalTests);
			// Number of cards after the fact should be -= 1
			printf("Number of cards in hand after playing %s = %d; Target number = %d....", TESTCARD,
					post->handCount[testPlayer], pre->handCount[testPlayer]);
			passedTests += assert_(post->handCount[testPlayer] == pre->handCount[testPlayer]);
			totalTests += 1;

			// Check number of estates in hand before and after
			printf("******* TEST %d: Number of Estates in hand ********\n", totalTests);
			printf("Number of estates in hand after playing %s = %d; Target number = %d....", TESTCARD,
					estPostHand, estPreHand);
			passedTests += assert_(estPostHand == estPreHand);
			totalTests += 1;

			// Check number of coins before and after
			printf("******* TEST %d: Number of Coins ********\n", totalTests);
			printf("Number of coins after playing %s = %d; Target number = %d....", TESTCARD,
					post->coins, pre->coins);
			passedTests += assert_(post->coins == pre->coins);
			totalTests += 1;
		}

		else if (choice1 == 1){
			printf("Discarding Estate!\n");

			printf("******* TEST %d: Number of cards in hand *******\n", totalTests);
			// Number of cards after the fact should be -= 2, accounting for discarded card
			printf("Number of cards in hand after playing %s = %d; Target number = %d....", TESTCARD,
					post->handCount[testPlayer], pre->handCount[testPlayer] - 2);
			passedTests += assert_(post->handCount[testPlayer] == pre->handCount[testPlayer] - 2);
			totalTests += 1;

			// Check number of estates in hand before and after
			printf("******* TEST %d: Number of Estates in hand ********\n", totalTests);
			printf("Number of estates in hand after playing %s = %d; Target number = %d....", TESTCARD,
					estPostHand, estPreHand - 1);
			passedTests += assert_(estPostHand == estPreHand - 1);
			totalTests += 1;

			// Check number of coins before and after
			printf("******* TEST %d: Number of Coins ********\n", totalTests);
			printf("Number of coins after playing %s = %d; Target number = %d....", TESTCARD,
				post->coins, pre->coins + 4);
			passedTests += assert_(post->coins == pre->coins + 4);
			totalTests += 1;
		}
		

		// Check number of estates in discard before and after
		printf("******* TEST %d: Number of Estates in discard ********\n", totalTests);
		printf("Number of estates in discard after playing %s = %d; Target number = %d....", TESTCARD,
				estPostDiscard, estPreDiscard + 1);
		passedTests += assert_(estPostDiscard == estPreDiscard + 1);
		totalTests += 1;


	// Cleanup
	*post = clean;
	*pre = clean;

	}

	printf("\n RANDOM TESTING COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);

	free(post);
	free(pre);

}