/*

CS 362 Assignment 3 -- Card Test 4
Unit test for dominion.c card Village

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "village"

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
	int kc[10] = {adventurer, baron, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room}; //List borrowed from cardtest4.c
	int rseed = 100;
	int coinBonus = 0;
	int handPos = 0;

	int totalTests = 0;
	int passedTests = 0;

	struct gameState *game = newGame();
	struct gameState *testGame = newGame();

	initializeGame(numPlayers, kc, rseed, game);

	// Guarantee the player has an estate to discard
	game->hand[testPlayer][0] = village;

	// Copy game state into test scenario
	memcpy(testGame, game, sizeof(struct gameState));

	printf("\n********* TESTING CARD %s *********\n", TESTCARD);
	printf("Number of cards in hand before playing %s = %d.\n", TESTCARD, game->handCount[testPlayer]);
	printf("Number of cards in deck before playing %s = %d.\n\n", TESTCARD, game->deckCount[testPlayer]);

	// Call cardEffect() with smithy passed in as card
	cardEffect(village, 0, 0, 0, testGame, handPos, &coinBonus);

	// Test: Number of cards in hand after == number before
	printf("******* TEST %d: Number of cards in hand *******\n", totalTests);
	printf("Number of cards in hand after playing %s = %d; Target number = %d....", TESTCARD, testGame->handCount[testPlayer], game->handCount[testPlayer]);
	passedTests += assert_(testGame->handCount[testPlayer] == game->handCount[testPlayer]);
	totalTests += 1;

	// Test: Number of cards left in deck -= 1
	printf("******* TEST %d: Number of cards in deck *******\n", totalTests);
	printf("Number of cards in deck after playing %s = %d; Target number = %d....", TESTCARD, testGame->deckCount[testPlayer], game->deckCount[testPlayer] - 3);
	passedTests += assert_(testGame->deckCount[testPlayer] == game->deckCount[testPlayer] - 1);
	totalTests += 1;

	// Test: Number of actions after playing += 1 [accounting for the action used by playing this card]
	printf("******* TEST %d: Number of actions *******\n", totalTests);
	printf("Number of actions after playing %s = %d; Target number = %d....", TESTCARD,
			testGame->numActions, game->numActions + 1);
	passedTests += assert_(testGame->numActions == game->numActions + 1);
	totalTests += 1;

	free(game);
	free(testGame);	

}