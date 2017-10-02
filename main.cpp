#include "game.h"

using namespace std;


int main() {
	cout << "***** BlackJack *****\n\n";

	cout << "Hello, and welcome to this stripped down game of Blackjack.\n\n" <<

			"Your goal is simple: Get the total value of your cards as close to 21 as you can.\n" <<

			"After you're dealt one card you can chose to get an extra card [hit],\n" <<
			"or leave your hand as it is [stand].\n" <<
			"You then place a bet and the house will try to beat you.\n" <<
			"The game is over when either player reaches 0$\n\n" <<

			"The value of Ace is either 1 or 11\n" <<
			"The value of numbered cards is their equal number\n" <<
			"The value of all face-cards is 10.\n\n" <<

			"Good luck!\n\n\n";

	Card deck[52];
	Game::createDeck(deck);
	Tool::pressToContinue();
	Game::game(deck);

	return 0;
}
