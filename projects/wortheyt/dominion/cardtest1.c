/*

CS 362 Assignment 3 -- Card Test 1
Unit test for dominion.c card Smithy

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "smithy"

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


int main (int argc, char* argv[]){

	int numPlayers = 2;
	int testPlayer = 0;
	int kc[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; //List borrowed from cardtest4.c
	int rseed = 100;
	int coinBonus = 0;
	int handPos = 0;

	int totalTests = 0;
	int passedTests = 0;

	struct gameState *game = newGame();
	struct gameState *testGame = newGame();

	initializeGame(numPlayers, kc, rseed, game);


	// Copy game state into test scenario
	memcpy(testGame, game, sizeof(struct gameState));

	printf("\n*********TESTING CARD %s*********\n", TESTCARD);
	printf("Number of cards in hand before playing %s = %d.\n", TESTCARD, game->handCount[testPlayer]);
	printf("Number of cards in deck before playing %s = %d.\n\n", TESTCARD, game->deckCount[testPlayer]);

	// Call cardEffect() with smithy passed in as card
	cardEffect(smithy, 0, 0, 0, testGame, handPos, &coinBonus);

	// Test 1: Number of cards in hand += 2
	printf("******* TEST %d: Number of cards in hand *******\n", totalTests);

	// Check number of cards in hand after the fact
	printf("Number of cards in hand after playing %s = %d; Target number = %d....", TESTCARD,
			testGame->handCount[testPlayer], game->handCount[testPlayer] + 2);
	passedTests += assert_(testGame->handCount[testPlayer] == game->handCount[testPlayer] + 2);
	totalTests += 1;

	// Test 2: Number of cards left in deck -= 3
	printf("******* TEST %d: Number of cards in deck *******\n", totalTests);
	printf("Number of cards in deck after playing %s = %d; Target number = %d....", TESTCARD,
			testGame->deckCount[testPlayer], game->deckCount[testPlayer] - 3);
	passedTests += assert_(testGame->deckCount[testPlayer] == game->deckCount[testPlayer] - 3);
	totalTests += 1;

	printf("\nUNIT TEST COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);


	free(game);
	free(testGame);

}



