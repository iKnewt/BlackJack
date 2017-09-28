#ifndef GAME_H
#define GAME_H

#include "tool.h"
#include <vector>


struct Card {
	int rank;
	int blackjackValue;
	char suit;
};

struct Hand
{
	string name;
	vector<Card> hand;
	int totalBlackJackValue = 0;
	int cash = 100;
	int bet = 0;
};

class Game
{
public:
	static void game(Card deck[]);
	static void createDeck(Card deckCard[]);
	static void printHand(Hand current, int cardsDrawn);


};

#endif // GAME_H
