#include "game.h"
#include <time.h>
#include <random>


static const string CARD_NAMES[] = {
	"Ace",
	"Two",
	"Three",
	"Four",
	"Five",
	"Six",
	"Seven",
	"Eight",
	"Nine",
	"Ten",
	"Jack",
	"Queen",
	"King",
};

static const string SUIT_NAMES[] = {
	"Diamonds",
	"Clubs",
	"Hearts",
	"Spades",
};

void Player::clearHand() { // makes the players ready for a new round by clearing their hand
	hand.resize(0); // sets the size of the hand vector to 0, and deletes all elements
	totalBlackJackValue = 0; // resets the blackjack score
	bet = 0; // resets the bet
	cardsDrawn = 0; // resets the counter for how many cards the player has drawn
}

void Player::placeBet(const Player& otherPlayer) {
	while(true) {
		cout << "\nWhat will you bet [min 10$]? ";
		if (!Tool::tryReadInt(&bet)){ // reads a userInput, returns true if it's an Int and saves that int in player.bet
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
	for(int i = 0; i < cardsDrawn; i++) {
		cout << " | " << CARD_NAMES[hand[i].rank - 1] << " of " << SUIT_NAMES[hand[i].suit] << endl;
	}
	cout << "\n Current total value: " << totalBlackJackValue;
	cout << endl;
}

void Game::printBoard(Player house, Player player) {
	house.printHand();
	cout << "\n\n\n";
	player.printHand();
}

void Game::createDeck(Card deckCard[]) { // creates a full deck of cards
	for(int i = 0; i < 52;) { // loops
		for(int suitInt = 0; suitInt < 4; suitInt++) {
			for(int rank = 1; rank < 14; rank++) { // there are 13 cards of each suit [Ace-King]
				deckCard[i].suit = suitInt; // the current card is assigned a suit [0-3]
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

bool Game::testForWinner(Player& house, Player& player) {
	if(player.cash < 10) {
		cout << "\nYou don't have enough money to make another bet, the house wins.\n"
				"Better luck next time.\n";
		return true;
	}
	if(house.cash < 10) {
		cout << "\nThe house doesn't have enough money to keep playing, you win.\n"
				"Congratulations on beating the house!\n";
		return true;
	}
	return false;
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
		//		for(int i = 0; i > 10; i++) {
		//			if(house->hand[i].rank == 1) { // if any cards
		//				if (house->totalBlackJackValue + 11 >= 21) {
		//					cout << "The house chose to value the Ace as 1";
		//					house->totalBlackJackValue += 1;
		//				}
		//				else {
		//					cout << "The house chose to value the Ace as 11";
		//					house->totalBlackJackValue += 11;
		//				}
		//			}
		//		}


		if(house->totalBlackJackValue > 21) { // runs if the house has gotten a higher value than 21 and breaks out of the loop if it has
			cout << "\nThe house busted";
			break;
		}
		cout << "\n\nThe house hits "; // house keeps hitting if it hasn't busted
		house->cardsDrawn++;
		house->hand.push_back(deck[house->cardsDrawn + player->cardsDrawn]);

		if(deck[house->cardsDrawn + player->cardsDrawn].rank == 1) { // if the drawn card is an ace
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
		Game::printBoard(*house, *player);
		Tool::pressToContinue();
	} while(house->totalBlackJackValue < player->totalBlackJackValue); // ensures that the house keeps hitting until it gets a highers score than the player
}

bool playerTurn(Card deck[], Player* house, Player* player) {

	do {
		Game::printBoard(*house, *player);

		//		cout << "\n\nWill you Hit, Stand or change the value of an Ace? ";
		cout << "\n\nWill you Hit or Stand? ";
		string playerChoice = Tool::readLine();
		playerChoice = Tool::toLower(playerChoice);

		if(playerChoice == "hit") {
			player->hand.push_back(deck[player->cardsDrawn]);
			if(deck[player->cardsDrawn].rank == 1) {
				int aceValue;
				while (true) {
					cout << "\nYou drew an ace! would you like its value to be 1 or 11? ";
					if (!Tool::tryReadInt(&aceValue))
						cout << "\nThat's not a number\n";
					else if(aceValue != 1 && aceValue != 11)
						cout << "\nYou can't put that value\n";
					else {
						player->totalBlackJackValue += aceValue;
						break;
					}
				}
			}
			else {
				player->totalBlackJackValue += deck[player->cardsDrawn].blackjackValue;
			}
			player->cardsDrawn++;
		}
		else if(playerChoice == "stand")
			break;
		//		else if(playerChoice == "ace") {

		//			for(int i = 0; i > player->hand.size(); i++) {
		//				if(house->hand[i].rank == 1) {
		//					int aceValue;
		//					while (true) {
		//						cout << "";
		//						if (!Tool::tryReadInt(&aceValue))
		//							cout << "\nThat's not a number\n";
		//						else if(aceValue != 1 && aceValue != 11)
		//							cout << "\nYou can't put that value\n";
		//						else {
		//							player->totalBlackJackValue += aceValue;
		//							break;
		//						}
		//					}
		//				}


		//			}




		//		}
		else
			cout << "\nThat's not a valid move";
	} while(player->totalBlackJackValue <= 21);

	if(player->totalBlackJackValue > 21) {
		//player.printHand();
		Game::printBoard(*house, *player);
		cout << "\nYou busted and have to hand the house the minimal bet of 10$\n";
		player->cash -= 10;
		house->cash += 10;
		Tool::pressToContinue();
		return true;
		//		continue;
	}
	return false;
}

void Game::game(Card deck[]) {

	Player house;
	house.name = "house";

	Player player;
	player.name = "player";

	while(!Game::testForWinner(house, player)) {

		player.clearHand();
		house.clearHand();

		shuffle(deck);


		if(playerTurn(deck, &house, &player))
			continue;
		player.placeBet(house);
		houseTurn(deck, &house, &player);

		if(house.totalBlackJackValue > 21 ||
				player.totalBlackJackValue > house.totalBlackJackValue) {
			if(house.totalBlackJackValue > 21)
				cout << "\nThe house busted";\
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







