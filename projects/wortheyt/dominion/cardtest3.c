/*

CS 362 Assignment 3 -- Card Test 3
Unit test for dominion.c card Baron

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "baron"

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


// Function to count the number of estates in player's hand
void countEstates(struct gameState *game, int player, int *numEstHand, int *numEstDiscard){

	int i;
	int cur;
	*numEstHand = 0;
	*numEstDiscard = 0;

	for (i = 0; i < game->handCount[player]; i++){
		cur = game->hand[player][i];
		if (cur == estate)
			*numEstHand += 1;
	}

	for (i = 0; i < game->discardCount[player]; i++){
		cur = game->discard[player][i];
		if (cur == estate)
			*numEstDiscard += 1;
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
	int choice1;

	int totalTests = 0;
	int passedTests = 0;

	struct gameState *game = newGame();
	struct gameState *testGame = newGame();

	initializeGame(numPlayers, kc, rseed, game);

	int estPreHand, estPostHand;
	int estPreDiscard, estPostDiscard;

	// Guarantee the player has an estate to discard
	game->hand[testPlayer][0] = baron;
	game->hand[testPlayer][1] = estate;


	for (choice1 = 0; choice1 < 2; choice1++){
		// Copy game state into test scenario
		memcpy(testGame, game, sizeof(struct gameState));
		// Call CardEffect() using card name and default parameters
		cardEffect(baron, choice1, 0, 0, testGame, handPos, &coinBonus);

		// Count estates before and after playing card [in both hand and discard piles]
		countEstates(game, testPlayer, &estPreHand, &estPreDiscard);
		countEstates(testGame, testPlayer, &estPostHand, &estPostDiscard);

		printf("\n*********TESTING CARD %s WITH CHOICE %d *********\n\n", TESTCARD, choice1);

		printf("******* TEST %d: Number of Buys after playing *******\n", totalTests);
		printf("Number of Buys after playing %s = %d; Target number = %d....", TESTCARD,
				testGame->numBuys, game->numBuys + 1);
		passedTests += assert_(testGame->numBuys == game->numBuys + 1);
		totalTests += 1;


		if (choice1 == 0){	// Don't Discard
			printf("Not Discarding -- Gain an Estate!\n");

			printf("******* TEST %d: Number of cards in hand *******\n", totalTests);
			// Number of cards after the fact should be -= 1
			printf("Number of cards in hand after playing %s = %d; Target number = %d....", TESTCARD,
					testGame->handCount[testPlayer], game->handCount[testPlayer]);
			passedTests += assert_(testGame->handCount[testPlayer] == game->handCount[testPlayer]);
			totalTests += 1;

			// Check number of estates in hand before and after
			printf("******* TEST %d: Number of Estates in hand ********\n", totalTests);
			printf("Number of estates in hand after playing %s = %d; Target number = %d....", TESTCARD,
					estPostHand, estPreHand);
			passedTests += assert_(estPostHand == estPreHand);
			totalTests += 1;

			// Check number of coins before and after
			printf("******* TEST %d: Number of Coins ********\n", totalTests);
			printf("Number of coins after playing %s = %d; Target number = %d....", TESTCARD,
					testGame->coins, game->coins);
			passedTests += assert_(testGame->coins == game->coins);
			totalTests += 1;
		}

		else if (choice1 == 1){
			printf("Discarding Estate!\n");

			printf("******* TEST %d: Number of cards in hand *******\n", totalTests);
			// Number of cards after the fact should be -= 2, accounting for discarded card
			printf("Number of cards in hand after playing %s = %d; Target number = %d....", TESTCARD,
					testGame->handCount[testPlayer], game->handCount[testPlayer] - 2);
			passedTests += assert_(testGame->handCount[testPlayer] == game->handCount[testPlayer] - 2);
			totalTests += 1;

			// Check number of estates in hand before and after
			printf("******* TEST %d: Number of Estates in hand ********\n", totalTests);
			printf("Number of estates in hand after playing %s = %d; Target number = %d....", TESTCARD,
					estPostHand, estPreHand - 1);
			passedTests += assert_(estPostHand == estPreHand - 1);
			totalTests += 1;

			// Check number of coins before and after
			printf("******* TEST %d: Number of Coins ********\n", totalTests);
			printf("Number of coins after playing %s = %d; Target number = %d....", TESTCARD,
				testGame->coins, game->coins + 4);
			passedTests += assert_(testGame->coins == game->coins + 4);
			totalTests += 1;
		}

		// Check number of estates in discard before and after
		printf("******* TEST %d: Number of Estates in discard ********\n", totalTests);
		printf("Number of estates in discard after playing %s = %d; Target number = %d....", TESTCARD,
				estPostDiscard, estPreDiscard + 1);
		passedTests += assert_(estPostDiscard == estPreDiscard + 1);
		totalTests += 1;
			
	}

	printf("\nUNIT TEST COMPLETED: %d / %d TESTS PASSED.\n\n", passedTests, totalTests);

	free(game);
	free(testGame);

}
