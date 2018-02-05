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

	game->hand[testPlayer][0] = adventurer;

	// Copy game state into test scenario
	memcpy(testGame, game, sizeof(struct gameState));

	printf("Starting with only one treasure...\n");
	testGame->deck[testPlayer][0] = copper;
	testGame->deck[testPlayer][1] = smithy;
	testGame->deck[testPlayer][2] = baron;
	testGame->deck[testPlayer][3] = adventurer;
	testGame->deck[testPlayer][4] = village;

	// Call CardEffect() using card name and default parameters
	cardEffect(adventurer, 0, 0, 0, testGame, handPos, &coinBonus);

	int trInHand = 0, trInDeck = 0;
	int trInHandTest = 0, trInDeckTest = 0;

	countTreasures(game, testPlayer, &trInDeck, &trInHand);
	countTreasures(testGame, testPlayer, &trInHandTest, &trInDeckTest);


	printf("\n*********TESTING CARD %s*********\n", TESTCARD);

	// In the case that the deck has less than 2 treasures, expect all treasures will be drawn

	printf("Testing <2 treasure in deck...\n\n");	

	// Test: Number of cards in hand after == number before
	printf("******* TEST %d: Number of cards in hand *******\n", totalTests);
	printf("Number of cards in hand after playing %s = %d; Target number = %d....", TESTCARD,
			testGame->handCount[testPlayer], game->handCount[testPlayer]);
	passedTests += assert_(testGame->handCount[testPlayer] == game->handCount[testPlayer]);
	totalTests += 1;

	// Test: Number of cards left in deck -= 1
	printf("******* TEST %d: Number of cards in deck *******\n", totalTests);
	printf("Number of cards in deck after playing %s = %d; Target number = %d....", TESTCARD,
			testGame->deckCount[testPlayer], game->deckCount[testPlayer] - 3);
	passedTests += assert_(testGame->deckCount[testPlayer] == game->deckCount[testPlayer] - 1);
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



	// Reset game state and copy back in original
	memset(testGame, 0, sizeof(struct gameState));
	memcpy(testGame, game, sizeof(struct gameState));

	// Inserting treasures to ensure >= 2
	testGame->deck[testPlayer][0] = copper;
	testGame->deck[testPlayer][1] = silver;

	// Call CardEffect() using card name and default parameters
	cardEffect(adventurer, 0, 0, 0, testGame, handPos, &coinBonus);

	countTreasures(game, testPlayer, &trInDeck, &trInHand);
	countTreasures(testGame, testPlayer, &trInHandTest, &trInDeckTest);


	printf("Testing with more than two treasures in deck...\n\n");

	// Test: Number of cards in hand after += 1
	printf("******* TEST %d: Number of cards in hand *******\n", totalTests);
	printf("Number of cards in hand after playing %s = %d; Target number = %d.....", TESTCARD,
			testGame->handCount[testPlayer], game->handCount[testPlayer] + 1);
	passedTests += assert_(testGame->handCount[testPlayer] == game->handCount[testPlayer] + 1);
	totalTests += 1;

	// Test: Number of cards left in deck -= 2
	printf("******* TEST %d: Number of cards in deck *******\n", totalTests);
	printf("Number of cards in deck after playing %s = %d; Target number = %d.....", TESTCARD,
			testGame->deckCount[testPlayer], game->deckCount[testPlayer] - 2);
	passedTests += assert_(testGame->deckCount[testPlayer] == game->deckCount[testPlayer] - 2);
	totalTests += 1;

	// Test: Number of treasures in hand += 2
	printf("******* TEST %d: Number of treasures in hand *******\n", totalTests);
	printf("Number of treasures in hand after playing %s = %d; Target number = %d.....", TESTCARD,
		trInHandTest, trInHand + 2);
	passedTests += assert_(trInHandTest == trInHand + 2);
	totalTests += 1;

	// Test: Number of treasures in deck -= 2
	printf("******* TEST %d: Number of treasures in deck *******\n", totalTests);
	printf("Number of treasures in hand after playing %s = %d; Target number = %d.....", TESTCARD,
		trInDeckTest, trInDeck - 2);
	passedTests += assert_(trInDeckTest == trInDeck - 2);
	totalTests += 1;



	printf("\nUNIT TEST COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);


	free(game);
	free(testGame);

}