#include "game.h"
#include <time.h>
#include <random>


void Player::clearHand() {
	//	hand.clear();
	hand.resize(0);
	totalBlackJackValue = 0;
	bet = 0;
	cardsDrawn = 0;
}

void Player::placeBet(Player& otherPlayer) {
	while(true) {
		cout << "\nWhat will you bet [min 10$]? ";
		if (!Tool::tryReadInt(&bet)){ // reads a userInput, returns true if it's an Int and saves that int in playerBet
			cout << "\nThat's not a number\n";
			continue;
		}

		if(bet < 10) {
			cout << "\nThe minimal bet is still 10$\n";
			continue;
		}
		else if(bet > cash) {
			cout << "\nYou don't even have that much money\n";
			continue;
		}
		else if(bet > otherPlayer.cash) {
			cout << "\nThe house couldn't pay you if you won\n";
			continue;
		}
		else // if the userInput passes all the criterias, it passes into the else, which is the only way to break out of this loop.
			break;
	}
}

void Player::printHand() { // prints a players hand to screen
	cout << "\n\n\n" << " | " << name << " | " << cash << "$" << " | " << endl << endl;
	cout << " | ";
	for(int i = 0; i < cardsDrawn; i++) {
		cout << hand[i].suit << hand[i].rank << " | ";
		//	for(int i = 0; i < 3; i++) {
		//		cout << "-------\n" <<
		//				"|     |\n" <<
		//				"|  " << hand[i].suit << "  |\n" <<
		//				"|  " << hand[i].rank << "  |\n" <<
		//				"|     |\n" <<
		//				"-------\n\n";
	}
	cout << "\n Current total value: " << totalBlackJackValue;
	cout << endl;
}





void Game::printBoard(Player player, Player house) {

	house.printHand();

	cout << "\n\n\n\n\n\n\n\n";

	player.printHand();
}





void Game::createDeck(Card deckCard[]) { // creates a full deck of cards
	for(int i = 0; i < 52;) { // loops
		for(int suitInt = 0; suitInt < 4; suitInt++) {
			char suit;

			switch (suitInt) { // assigns the four different suits to the cards (clubs, diamonds, spades and hearts)
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

			for(int rank = 1; rank < 14; rank++) { // there are 13 cards of each suit [Ace-King]
				deckCard[i].suit = suit; // the current card is assigned a suit [A-D]
				deckCard[i].rank = rank; // the current card is assigned a rank [1-13]
				if(rank >= 10)
					deckCard[i].blackjackValue = 10; // all face cards in blackjack have the value 10
				else
					deckCard[i].blackjackValue = rank; // all other cards have the same value as their rank, expect Ace, but that's dealt with elsewhere
				i++; // adds +1 to the original for-loop that adds to the original array
			}
		}
	}
}

void shuffle(Card deck[]) { // shuffels the positions of elements in an array (by moving data around), in this case a deck of cards

	srand(time(0));
	for (int i=0; i<52; i++) {
		int r = rand() % 51; // generates a random number within the range 0-51
		Card temp = deck[i]; // creates a temporary card that duplicates the data of the current for-loop-card
		deck[i] = deck[r]; // puts the data from the random card selected into the current for-loop-card
		deck[r] = temp; // puts the data from the orginial current for-loop-card into the random card via the temp card
		// this means the random card and current card swaps data, effectively shuffling the element-data around the array
	}
}


void houseTurn(Card deck[], Player* house, Player* player) {
	cout << "\nhouse turn\n";


	do {
		if(house->totalBlackJackValue > 21) {
			cout << "\nThe house busted";
			break;
		}
		cout << "\n\nThe house hits ";
		house->cardsDrawn++;
		house->hand.push_back(deck[house->cardsDrawn + player->cardsDrawn]);

		if(deck[house->cardsDrawn + player->cardsDrawn].rank == 1) {
			if (house->totalBlackJackValue + 11 >= 21) {
				cout << "The house chose to value the Ace as 1";
				house->totalBlackJackValue += 1;
			}
			else {
				cout << "The house chose to value the Ace as 11";
				house->totalBlackJackValue += 11;
			}
		}
		else
			house->totalBlackJackValue += deck[house->cardsDrawn + player->cardsDrawn].blackjackValue;

		//house.printHand();
		Game::printBoard(*player, *house);
		Tool::pressToContinue();
	} while(house->totalBlackJackValue < player->totalBlackJackValue);
}

void Game::game(Card deck[]) {

	Player house;
	house.name = "house";

	Player player;
	player.name = "player";








	while(true) {

		player.clearHand();
		house.clearHand();

		shuffle(deck);

		player.hand.push_back(deck[player.cardsDrawn]);
		player.totalBlackJackValue = deck[player.cardsDrawn].blackjackValue;

		player.cardsDrawn++;



		do {

			Game::printBoard(player, house);




			//player.printHand();
			cout << "\n\nWill you Hit or Stand? ";
			string playerChoice = Tool::readLine();
			playerChoice = Tool::toLower(playerChoice);



			if(playerChoice == "hit") {
				player.hand.push_back(deck[player.cardsDrawn]);
				if(deck[player.cardsDrawn].rank == 1) {
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
					player.totalBlackJackValue += deck[player.cardsDrawn].blackjackValue;
				player.cardsDrawn++;
			}
			else if(playerChoice == "stand")
				break;
			else
				cout << "\nThat's not a valid move";
		} while(player.totalBlackJackValue < 21);


		if(player.totalBlackJackValue > 21) {
			//player.printHand();
			Game::printBoard(player,house);
			cout << "\nYou busted and have to hand the house the minimal bet of 10$\n";
			player.cash -= 10;
			house.cash += 10;
			Tool::pressToContinue();
			continue;
		}


		player.placeBet(house);

		houseTurn(deck, &house, &player);


		if(house.totalBlackJackValue > 21 ||
				player.totalBlackJackValue > house.totalBlackJackValue) {
			cout << "\nYou win";
			player.cash += player.bet;
			house.cash -= player.bet;
		}
		else if(player.totalBlackJackValue < house.totalBlackJackValue) {
			cout << "\nThe house wins";
			player.cash -= player.bet;
			house.cash += player.bet;
		}
		else if(player.totalBlackJackValue == house.totalBlackJackValue)
			cout << "\nIt's a draw";

		Tool::pressToContinue();
	}
}
