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





void Game::printHand(Hand current, int cardsDrawn) {
	cout << "\n\n\n" << " | " << current.name << " | " << current.cash << "$" << " | " << endl << endl;

	cout << " | ";

	for(int i = 0; i < cardsDrawn; i++) {
		cout << current.hand[i].suit << current.hand[i].rank << " | ";


		//	for(int i = 0; i < 3; i++) {
		//		cout << "-------\n" <<
		//				"|     |\n" <<
		//				"|  " << hand[i].suit << "  |\n" <<
		//				"|  " << hand[i].rank << "  |\n" <<
		//				"|     |\n" <<
		//				"-------\n\n";
	}

	cout << "\n Current total value: " << current.totalBlackJackValue;

	cout << endl;
}



void shuffle(Card deck[]) {

	srand(time(0));  // initialize seed "randomly"


	for (int i=0; i<52; i++) {
		int r = rand() % 51;  // generate a random position
		Card temp = deck[i]; deck[i] = deck[r]; deck[r] = temp;
	}
}


void playerTurn() {

}



void Game::game(Card deck[]) {




	Hand house;
	house.name = "house";

	Hand player;
	player.name = "player";


	while(true) {

		player.hand.clear();
		player.totalBlackJackValue = 0;
		house.hand.clear();
		house.totalBlackJackValue = 0;

		shuffle(deck);

		player.hand.push_back(deck[0]);
		player.totalBlackJackValue = deck[0].blackjackValue;

		int cardsDrawn = 1;

		do {
			Game::printHand(player, cardsDrawn);
			cout << "\n\nWill you Hit or Stand? ";
			string playerChoice = Tool::readLine();
			playerChoice = Tool::toLower(playerChoice);

			if(playerChoice == "hit") {
				player.hand.push_back(deck[cardsDrawn]);
				if(deck[cardsDrawn].rank == 1) {
					int aceValue;
					while (true) {
											cout << "\nYou drew an ace! would you like its value to be 1 or 11? ";
						if (!Tool::tryReadInt(&aceValue))
							cout << "\nThat's not a number\n";
						else if(aceValue != 1 && aceValue != 11)
							cout << "\nYou can't put that value\n";
						else {
							player.totalBlackJackValue += aceValue;
							break;
						}
					}
				}
				else
					player.totalBlackJackValue += deck[cardsDrawn].blackjackValue;
				cardsDrawn++;
			}
			else if(playerChoice == "stand")
				break;
			else
				cout << "\nThat's not a valid move";
		} while(player.totalBlackJackValue < 21);


		if(player.totalBlackJackValue > 21) {
			Game::printHand(player, cardsDrawn);
			cout << "\nYou busted and have to hand the house the minimal bet of 10$\n";
			player.cash -= 10;
			house.cash += 10;
			continue;
		}



		int playerBet;

		while(true) {
			cout << "\nWhat will you bet [min 10$]? ";
			if (!Tool::tryReadInt(&playerBet)){
				cout << "\nThat's not a number\n";
				continue;
			}

			if(playerBet < 10) {
				cout << "\nThe minimal bet is still 10$\n";
				continue;
			}
			else if(playerBet > player.cash) {
				cout << "\nYou don't even have that much money\n";
				continue;
			}
			else if(playerBet > house.cash) {
				cout << "\nThe house couldn't pay you if you won\n";
				continue;
			}
			else
				break;
		}

		while(true) {
			house.hand.push_back(deck[cardsDrawn]);
			house.totalBlackJackValue += deck[cardsDrawn].blackjackValue;
			Game::printHand(house, cardsDrawn);
			cardsDrawn++;
			if(house.totalBlackJackValue > 21) {
				cout << "\nThe house busted";
				break;
			}
			else
				cout << "\n\nThe house hits ";
		}

		if(house.totalBlackJackValue > 21 ||
				player.totalBlackJackValue > house.totalBlackJackValue) {
			player.cash += playerBet;
			house.cash -= playerBet;
		}
		else if(player.totalBlackJackValue < house.totalBlackJackValue) {
			player.cash -= playerBet;
			house.cash += playerBet;
		}

	}
}
