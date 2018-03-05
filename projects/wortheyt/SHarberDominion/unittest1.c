/*

CS 362 Assignment 3 -- Unit Test 1
Unit test for dominion.c function isGameOver()

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTFUN "isGameOver()"

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

	int numPlayers = 4;
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

	// Set 3 arbitrary supply piles to empty
	testGame->supplyCount[smithy] = 0;
	testGame->supplyCount[great_hall] = 0;
	testGame->supplyCount[mine] = 0;


	printf("\n*********TESTING FUNCTION %s*********\n", TESTFUN);

	printf("******* TEST %d: Default case - game not over *******\n", totalTests);
	passedTests += assert_(isGameOver(game) == 0);
	totalTests += 1;


	printf("******* TEST %d: 3 Supply Piles empty *******\n", totalTests);
	// Set 3 arbitrary supply piles to empty
	testGame->supplyCount[smithy] = 0;
	testGame->supplyCount[great_hall] = 0;
	testGame->supplyCount[mine] = 0;

	printf("Game is Over == %d....", isGameOver(testGame));
	passedTests += assert_(isGameOver(testGame) == 1);
	totalTests += 1;


	printf("******* TEST %d: Province Pile empty *******\n", totalTests);
	memcpy(testGame, game, sizeof(struct gameState));
	testGame->supplyCount[province] = 0;
	printf("Game is Over == %d....", isGameOver(testGame));	
	passedTests += assert_(isGameOver(testGame) == 1);
	totalTests += 1;

	printf("\nUNIT TEST COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);

	free(game);
	free(testGame);
}

