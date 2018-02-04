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

void assert_(int statement){

	if (statement == 0)
		printf("Test FAILED.\n");

	else
		printf("Test OK!\n");
}


int main (int argc, char* argv[]){

	int numPlayers = 2;
	int testPlayer = 0;
	int kc[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; //List borrowed from cardtest4.c
	int rseed = 100;
	int coinBonus = 0;
	int handPos = 0;

	struct gameState *game = newGame();
	struct gameState *testGame = newGame();

	initializeGame(numPlayers, kc, rseed, game);

	// Copy game state into test scenario
	memcpy(testGame, game, sizeof(struct gameState));

	printf("*********Testing card %s*********\n", TESTCARD);
	printf("Number of cards before playing %s = %d.\n", TESTCARD, game->handCount[testPlayer]);

	// Test: call cardEffect() with smithy passed in as card
	cardEffect(smithy, 0, 0, 0, testGame, handPos, &coinBonus);

	// Test 1: Number of cards in hand += 3
	printf("*******TEST 1: Number of cards *******\n");

	// Check number of cards in hand after the fact
	printf("Number of cards after playing %s = %d; Target number = %d.", TESTCARD,
			testGame->handCount[testPlayer], game->handCount[testPlayer] + 2);
	assert_(testGame->handCount[testPlayer] == game->handCount[testPlayer] + 2);




}



