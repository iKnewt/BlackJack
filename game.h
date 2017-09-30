#ifndef GAME_H
#define GAME_H

#include "tool.h"
#include <vector>

struct Card {
	int rank;
	int blackjackValue;
	char suit;
};

class Player {
public:
	void printHand();
	void clearHand();
	void placeBet(const Player& otherPlayer);

	string name;
	vector<Card> hand;
	int totalBlackJackValue = 0;
	int cash = 100;
	int bet = 0;
	int cardsDrawn = 0;
};

class Game {
public:
	static void game(Card deck[]);
	static void createDeck(Card deckCard[]);
	static void printBoard(Player house, Player player);
};

#endif // GAME_H
