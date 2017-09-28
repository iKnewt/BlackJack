#include "game.h"
#include <time.h>
#include <random>


void Game::createDeck(Card deckCard[]) {
	for(int i = 0; i < 52;) {
		for(int suitInt = 0; suitInt < 4; suitInt++) {
			char suit;

			switch (suitInt) {
				case 0:
					suit = 'A';
					break;
				case 1:
					suit = 'B';
					break;
				case 2:
					suit = 'C';
					break;
				case 3:
					suit = 'D';
					break;
				default:
					break;
			}

			for(int rank = 1; rank < 14; rank++) {
				deckCard[i].suit = suit;
				deckCard[i].rank = rank;
				if(rank >= 10)
					deckCard[i].blackjackValue = 10;
				else
					deckCard[i].blackjackValue = rank;
				//				cout << deckCard[i].suit << deckCard[i].rank << "\tBlackjack Value: " << deckCard[i].blackjackValue << endl;
				i++;
			}
		}
	}
}





void Game::printHand(vector<Card> hand,int handSize) {

	cout << " | ";

	for(int i = 0; i < handSize; i++) {
		cout << hand[i].suit << hand[i].rank << " | ";


		//	for(int i = 0; i < 3; i++) {
		//		cout << "-------\n" <<
		//				"|     |\n" <<
		//				"|  " << hand[i].suit << "  |\n" <<
		//				"|  " << hand[i].rank << "  |\n" <<
		//				"|     |\n" <<
		//				"-------\n\n";
	}
	cout << endl;
}



void shuffle(Card deck[]) {

	srand(time(0));  // initialize seed "randomly"


		for (int i=0; i<52; i++) {
			int r = rand() % 51;  // generate a random position
			Card temp = deck[i]; deck[i] = deck[r]; deck[r] = temp;
		}
}

struct Hand
{
	vector<Card> hand;
	int handSize = 1;

	int cash = 100;
};



void Game::game() {

	Card deckCard[51];
	Game::createDeck(deckCard);

	shuffle(deckCard);

	Hand player;

	player.hand.push_back(deckCard[0]);

	while(true) {
		Game::printHand(player.hand, player.handSize);
		cout << "Will you Hit or Stand? ";
		string playerChoice = Tool::readLine();
		playerChoice = Tool::toLower(playerChoice);

		if(playerChoice == "hit") {
			player.hand.push_back(deckCard[player.handSize]);
			player.handSize++;
		}
		else
			break;
	}


//	vector<Card> playerHand;
//	playerHand.push_back(deckCard[0]);

//	int playerHandSize = 1;

//	while(true) {
//		Game::printHand(playerHand, playerHandSize);
//		cout << "Will you Hit or Stand? ";
//		string playerChoice = Tool::readLine();
//		playerChoice = Tool::toLower(playerChoice);

//		if(playerChoice == "hit") {
//			playerHand.push_back(deckCard[playerHandSize]);
//			playerHandSize++;
//		}
//		else
//			break;
//	}



}
