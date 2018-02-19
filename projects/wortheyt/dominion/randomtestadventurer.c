/*

CS 362 Assignment 4 -- Random Tester 3
Random tester for dominion.c card Adventurer

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>

#define TESTCARD "adventurer"


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


// Helper function to count the number of treasures in Deck and Hand
void countTreasures(struct gameState* game, int player, int *trInDeck, int *trInHand){

	int i;

	*trInDeck = 0;
	*trInHand = 0;

	for (i = 0; i < game->deckCount[player]; i++){
		int cur = game->deck[player][i];
		if (cur == silver || cur == copper || cur == gold)
			*trInDeck += 1;
	}

	for (i = 0; i < game->handCount[player]; i++){
		int cur = game->hand[player][i];
		if (cur == silver || cur == copper || cur == gold)
			*trInHand += 1;
	}

}

// Generate a random deck with a fixed number of treasures
void generateDeck(struct gameState* game, int player, int kc[10], int decksize, int treasures){

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

	int numTests = 100;	// How many full cycles of the test suite to run?

	int numPlayers;
	int testPlayer;
	int kc[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; //List borrowed from cardtest4.c; //List borrowed from cardtest4.c
	int rseed = 100;
	int coinBonus;
	int handPos;
	coinBonus = 0; // cardEffect expects a 0 passed in from playCard()
	// int choice1 = 0, choice2 = 0, choice3 = 0;

	int totalTests = 0;
	int passedTests = 0;

	// Values to use when counting treasure results
	int trInHand = 0, trInDeck = 0;
	int trInHandTest = 0, trInDeckTest = 0;	

	// // Instantiate some games.
	struct gameState *pre = newGame();	// Storage for pre-card game state
	struct gameState *post = newGame();	// The game we're going to operate on
	struct gameState clean = { 0 };		// clean will be used to erase structs every loop

	int n;
	// Main Testing Loop : Rnage = 0-numTests
	for (n = 0; n < numTests; n++){

		printf("On Test Loop #%d\n", n);
		printf("Random Parameters:\n");
		numPlayers = (rand() % 3) + 2; // MAX_PLAYERS == 4, so we'll be kind. Range 2-4
		testPlayer = (rand() % 4);	// testPlayer; Range 0-3

		printf("Number of players: %d\n", numPlayers);
		printf("Testing player: %d\n", testPlayer);

		// Initialize game to start
		initializeGame(numPlayers, kc, rseed, post);


		// Values to Test:
		// numPlayers -- Range = 1-4
		// kc -- Generate random list of cards
		// testPlayer -- Range = 1-4
		// handPos -- Range = 1-7


		// Pick a hand slot and stick the adventurer card there
		handPos = 0;
		post->hand[testPlayer][handPos] = adventurer;
		printf("Card at hand position: %d\n", handPos);

		// Randomize a deck
		int decksize = (rand() % MAX_DECK - 1) + 1; 	// Decksize should be between 1 and MAX_DECK
		int treasures = (rand() % decksize);		// Ensure fewer treasures than the decksize

		printf("Using a deck of size: %d\n", decksize);
		printf("Number of treasures in deck: %d\n", treasures);

		generateDeck(post, testPlayer, kc, decksize, treasures);

		printf("Deck generation complete\n");

		// Copy game state to compare later
		memcpy(pre, post, sizeof(struct gameState));

		// Call CardEffect() using card name and default parameters
		cardEffect(adventurer, 0, 0, 0, post, handPos, &coinBonus);

		// Determine number of treasures in hands and decks, before and after call to adventurer
		countTreasures(pre, testPlayer, &trInDeck, &trInHand);
		countTreasures(post, testPlayer, &trInHandTest, &trInDeckTest);


		if (trInDeck < 2){

			printf("Testing <2 treasure in deck...\n\n");	

			// Test: Number of cards in hand after == number before
			printf("******* TEST %d: Number of cards in hand *******\n", totalTests);
			printf("Number of cards in hand after playing %s = %d; Target number = %d....", TESTCARD,
					post->handCount[testPlayer], pre->handCount[testPlayer]);
			passedTests += assert_(post->handCount[testPlayer] == pre->handCount[testPlayer]);
			totalTests += 1;

			// Test: Number of cards left in deck -= 1
			printf("******* TEST %d: Number of cards in deck *******\n", totalTests);
			printf("Number of cards in deck after playing %s = %d; Target number = %d....", TESTCARD,
					post->deckCount[testPlayer], pre->deckCount[testPlayer] - 3);
			passedTests += assert_(post->deckCount[testPlayer] == pre->deckCount[testPlayer] - 1);
			totalTests += 1;

			// Test: Number of treasures in hand += 2
			// printf("Number of treasures in hand before playing %s = %d.\n", TESTCARD, trInHand);
			// printf("Number of treasures in deck before playing %s = %d.\n\n", TESTCARD, trInDeck);

			printf("******* TEST %d: Number of treasures in hand *******\n", totalTests);
			printf("Number of treasures in hand after playing %s = %d; Target number = %d....", TESTCARD,
				trInHandTest, trInHand + trInDeck);
			passedTests += assert_(trInHandTest == trInHand + trInDeck);
			totalTests += 1;

			printf("******* TEST %d: Number of treasures in deck *******\n", totalTests);
			printf("Number of treasures in deck after playing %s = %d; Target number = %d....", TESTCARD,
				trInDeckTest, trInDeck - trInDeck);
			passedTests += assert_(trInDeckTest == trInDeck - trInDeck);
			totalTests += 1;

		}

		else if (trInDeck >= 2){

			printf("Testing with more than two treasures in deck...\n\n");

			// Test: Number of cards in hand after += 1
			printf("******* TEST %d: Number of cards in hand *******\n", totalTests);
			printf("Number of cards in hand after playing %s = %d; Target number = %d.....", TESTCARD,
					post->handCount[testPlayer], pre->handCount[testPlayer] + 1);
			passedTests += assert_(post->handCount[testPlayer] == pre->handCount[testPlayer] + 1);
			totalTests += 1;

			// Test: Number of cards left in deck -= 2
			printf("******* TEST %d: Number of cards in deck *******\n", totalTests);
			printf("Number of cards in deck after playing %s = %d; Target number = %d.....", TESTCARD,
					post->deckCount[testPlayer], pre->deckCount[testPlayer] - 2);
			passedTests += assert_(post->deckCount[testPlayer] == pre->deckCount[testPlayer] - 2);
			totalTests += 1;

			// Test: Number of treasures in hand += 2
			printf("******* TEST %d: Number of treasures in hand *******\n", totalTests);
			printf("Number of treasures in hand after playing %s = %d; Target number = %d.....", TESTCARD,
				trInHandTest, trInHand + 2);
			passedTests += assert_(trInHandTest == trInHand + 2);
			totalTests += 1;

			// Test: Number of treasures in deck -= 2
			printf("******* TEST %d: Number of treasures in deck *******\n", totalTests);
			printf("Number of treasures in deck after playing %s = %d; Target number = %d.....", TESTCARD,
				trInDeckTest, trInDeck - 2);
			passedTests += assert_(trInDeckTest == trInDeck - 2);
			totalTests += 1;

		}

	// Cleanup
	*post = clean;
	*pre = clean;

	}


	// Generate random values within some range
	

	// Loop for some large number of tests
	// Call function to verify gamestate and assert test metrics

	// DO SOME TESTS

	printf("\nUNIT TEST COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);

	free(pre);
	free(post);


}
