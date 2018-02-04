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


/*

Preconditions:
	- Game is initialized
	- Card is in player's hand at handPos
	- Card is set for either trash or played pile

Postconditions:
	- Card is no longer in player's hand
	- Card is in appropriate pile
	- No other part of the gaem state is altered

*/


int main (int argc, char* argv[]){




}


int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{
	
	//if card is not trashed, added to Played pile 
	if (trashFlag < 1)
		{
			//add card to played pile
			state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
			state->playedCardCount++;
		}
	
	//set played card to -1
	state->hand[currentPlayer][handPos] = -1;
	
	//remove card from player's hand
	if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
		{
			//reduce number of cards in hand
			state->handCount[currentPlayer]--;
		}
	else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
		{
			//reduce number of cards in hand
			state->handCount[currentPlayer]--;
		}
	else 	
		{
			//replace discarded card with last card in hand
			state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
			//set last card to -1
			state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
			//reduce number of cards in hand
			state->handCount[currentPlayer]--;
		}
	
	return 0;
}