/*

CS 362 Assignment 3 -- Unit Test 3
Unit test for dominion.c function discardCard()

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTFUN "discardCard()"


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


int main (int argc, char* argv[]){
	int numPlayers = 2;
	int testPlayer = 0;
	int kc[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; //List borrowed from cardtest4.c
	int rseed = 100;

	int totalTests = 0;
	int passedTests = 0;

	struct gameState *game = newGame();
	struct gameState *testGame = newGame();

	initializeGame(numPlayers, kc, rseed, game);

	// Copy game state into test scenario
	memcpy(testGame, game, sizeof(struct gameState));		
	discardCard(0, testPlayer, testGame, 1);

	printf("\n*********TESTING FUNCTION %s*********\n", TESTFUN);
	printf("******* TEST %d: Cards in hand -= 1 *******\n", totalTests);
	printf("Cards in hand after discard = %d; Target number = %d.....", testGame->handCount[testPlayer], game->handCount[testPlayer] - 1);
	passedTests += assert_(testGame->handCount[testPlayer] == game->handCount[testPlayer] - 1);
	totalTests += 1;

	printf("******* TEST %d: Card in discard pile matches discarded card *******\n", totalTests);
	printf("Card on top of discard pile = %d; Discarded card = %d.....", testGame->discard[testPlayer][testGame->discardCount[testPlayer] - 1], game->hand[testPlayer][0]);
	passedTests += assert_(testGame->discard[testPlayer][testGame->discardCount[testPlayer] - 1] == game->hand[testPlayer][0]);
	totalTests += 1;

	printf("\nUNIT TEST COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);

}

