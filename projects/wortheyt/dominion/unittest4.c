/*

CS 362 Assignment 3 -- Unit Test 4
Unit test for dominion.c function fullDeckCount()

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


#define TESTFUN "fullDeckCount()"


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

	int i;

	struct gameState *game = newGame();

	initializeGame(numPlayers, kc, rseed, game);

	// Fill the deck with things to count.
	for (i = 0; i < 10; i++){
		game->hand[testPlayer][i] = minion;
		game->discard[testPlayer][i] = sea_hag;
		game->deck[testPlayer][i] = copper;
	}
	game->handCount[testPlayer] = 10;
	game->discardCount[testPlayer] = 10;
	game->deckCount[testPlayer] = 10;

	printf("\n*********TESTING FUNCTION %s*********\n", TESTFUN);
	printf("******* TEST %d: Count Minions *******\n", totalTests);
	printf("Minion count in full deck = %d; Target Number = %d.....", fullDeckCount(testPlayer, minion, game), 10);
	passedTests += assert_(fullDeckCount(testPlayer, minion, game) == 10);
	totalTests += 1;

	printf("******* TEST %d: Count Sea Hags *******\n", totalTests);
	printf("Sea Hag count in full deck = %d; Target Number = %d.....", fullDeckCount(testPlayer, sea_hag, game), 10);
	passedTests += assert_(fullDeckCount(testPlayer, sea_hag, game) == 10);
	totalTests += 1;


	printf("******* TEST %d: Count Copper *******\n", totalTests);
	printf("Copper count in full deck = %d; Target Number = %d.....", fullDeckCount(testPlayer, copper, game), 10);
	passedTests += assert_(fullDeckCount(testPlayer, copper, game) == 10);
	totalTests += 1;

	printf("\nUNIT TEST COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);

	free(game);


}

