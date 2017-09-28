#ifndef GAME_H
#define GAME_H

#include "tool.h"
#include <vector>


struct Card {
	int rank;
	int blackjackValue;
	char suit;
};

class Game
{
public:
	static void game();
	static void createDeck(Card deckCard[]);
	static void printHand(vector<Card>, int handSize);


};

#endif // GAME_H
