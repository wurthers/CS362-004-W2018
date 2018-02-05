/*

CS 362 Assignment 3 -- Card Test 2
Unit test for dominion.c card Adventurer

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "adventurer"

int assert_(int statement){

	if (statement == 0){
		printf("TEST FAILED.\n");
		return 0;
	}

	else{
		printf("TEST OK!\n");
		return 1;
	}
}


// Helper function to count the number of treasures in Deck and Hand
void countTreasures(struct gameState* game, int player, int* trInDeck, int* trInHand){

	int i;

	trInDeck = 0;
	trInHand = 0;

	for (i = 0; i < game->deckCount[player]; i++){
		int cur = game->deck[player][i];
		if (cur == silver || cur == copper || cur == gold)
			trInDeck += 1;
	}

	for (i = 0; i < game->handCount[player]; i++){
		int cur = game->hand[player][i];
		if (cur == silver || cur == copper || cur == gold)
			trInHand += 1;
	}

}


int main (int argc, char* argv[]){

	int numPlayers = 2;
	int testPlayer = 0;
	int kc[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; //List borrowed from cardtest4.c
	int rseed = 100;
	int coinBonus = 0;
	int handPos = 0;
	// int choice1 = 0, choice2 = 0, choice3 = 0;

	int totalTests = 0;
	int passedTests = 0;

	struct gameState *game = newGame();
	struct gameState *testGame = newGame();

	initializeGame(numPlayers, kc, rseed, game);



	// Copy game state into test scenario
	memcpy(testGame, game, sizeof(struct gameState));

	cardEffect(adventurer, 0, 0, 0, testGame, handPos, &coinBonus);

	int trInHand = 0, trInDeck = 0;
	int trInHandTest = 0, trInDeckTest = 0;

	countTreasures(game, testPlayer, &trInDeck, &trInHand);
	countTreasures(testGame, testPlayer, &trInHandTest, &trInDeckTest);



	printf("\n*********TESTING CARD %s*********\n", TESTCARD);

	// In the case that the deck has less than 2 treasures, expect all treasures will be drawn
	if (trInDeck <= 1){
		// Test 1: Number of treasures in hand += 2
		printf("Number of treasures in hand before playing %s = %d.\n", TESTCARD, trInHand);
		printf("Number of treasures in deck before playing %s = %d.\n\n", TESTCARD, trInDeck);

		printf("Number of treasures in hand after playing %s = %d; Target number = %d....", TESTCARD,
			trInHandTest, trInHand + trInDeck);
		passedTests += assert_(trInHandTest == trInHand + trInDeck);
		totalTests += 1;

		printf("Number of treasures in hand after playing %s = %d; Target number = %d....", TESTCARD,
			trInDeckTest, trInDeck - trInDeck);
		passedTests += assert_(trInDeckTest == trInDeck - trInDeck);
		totalTests += 1;

	}

	// Otherwise, expect 2 treasures to be drawn
	else {
		// Test 1: Number of treasures in hand += 2
		printf("Number of treasures in hand before playing %s = %d.\n", TESTCARD, trInHand);
		printf("Number of treasures in deck before playing %s = %d.\n\n", TESTCARD, trInDeck);

		printf("Number of treasures in hand after playing %s = %d; Target number = %d.\n", TESTCARD,
			trInHandTest, trInHand + 2);
		passedTests += assert_(trInHandTest == trInHand + 2);
		totalTests += 1;

		printf("Number of treasures in hand after playing %s = %d; Target number = %d.\n", TESTCARD,
			trInDeckTest, trInDeck - 2);
		passedTests += assert_(trInDeckTest == trInDeck + 2);
		totalTests += 1;
	}

	printf("\nUNIT TEST COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);


	free(game);
	free(testGame);

}