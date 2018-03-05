/*

CS 362 Assignment 3 -- Unit Test 2
Unit test for dominion.c function endTurn()

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTFUN "endTurn()"


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


	printf("\n*********TESTING FUNCTION %s*********\n", TESTFUN);

	endTurn(testGame);

	printf("******* TEST %d: Player who ended their turn discards *******\n", totalTests);
	printf("Previous player's current discard count = %d; Target number = %d.....", testGame->discardCount[testPlayer],  game->discardCount[testPlayer] + game->handCount[testPlayer]);
	passedTests += assert_(testGame->discardCount[testPlayer] == game->discardCount[testPlayer] + game->handCount[testPlayer]);
	totalTests += 1;


	printf("******* TEST %d: Player who ended their turn draws 5 *******\n", totalTests);
	printf("Previous player's current handcount = %d; Target number = %d.....", testGame->handCount[testPlayer], 5);
	passedTests += assert_(testGame->handCount[testPlayer] == 5);
	totalTests += 1;

	printf("******* TEST %d: Turn phase resets to 0 *******\n", totalTests);
	printf("Current phase = %d; Target number = %d.....", testGame->phase, 0);
	passedTests += assert_(testGame->phase == 0);
	totalTests += 1;

	printf("******* TEST %d: Cycling through players *******\n", totalTests);
	endTurn(testGame);	// Should cycle back to player 0
	printf("Ending turn...Previous player: %d; Current Player: %d....", testGame->whoseTurn, testPlayer);
	passedTests += assert_(testGame->whoseTurn == 0);
	totalTests += 1;

	printf("\nUNIT TEST COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);

	free(game);
	free(testGame);

}
