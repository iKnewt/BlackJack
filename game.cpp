#include "game.h"
#include <time.h>
#include <random>

enum class PlayerMove : int {
	Hit = 1,
	Stand = 2,
	Ace = 3,
};

static const string CARD_NAMES[] = { // used to print cards to screen without storing strings within each card
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


void Player::sumBlackjackValue() {
	totalBlackJackValue = 0; // resets the players previous score
	int handSize = hand.size(); // stores the total amount of elements in a vector as an int
	for(int i = 0; i < handSize; i++) { // loops for each element in the vector hand
		totalBlackJackValue += hand[i].blackjackValue; // adds that cards blackjackvalue to the player's total to show score
	}
}


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
			cout << "\nThat's not a number\n"; // error message if user input is not an int
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
	cout << "\n\n\n" << " | " << name << " | " << cash << "$" << " | " << endl << endl; // prints player name and cash amount
	for(int i = 0; i < cardsDrawn; i++) { // runs for each card the player has (I realize I could use the hand.size() funtion here too, but discovered that a little too late to edit it in
		cout << " | " << CARD_NAMES[hand[i].rank - 1] << " of " << SUIT_NAMES[hand[i].suit] << endl; // prints the corresponding strings from const arrays to print cards to screen
	}
	cout << "\n Current total value: " << totalBlackJackValue; // displays current jackblackvalue the player has in their hand
	cout << endl;
}

void Game::printBoard(Player& house, Player& player) { // prints the game board

	player.sumBlackjackValue(); // makes sure the printed board has accurate blackjackvalues on it
	house.sumBlackjackValue(); // I ran out of time to fingure out where to better place these, I know they shouldn't be here as they in no may relate to printing the board and it makes no sense to have them here

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

bool Game::testForWinner(Player& house, Player& player) { // tests if either player or house has won
	if(player.cash < 10) { // I chose to have anyone with less than 10 in cash be the loser, as 10 is the minimum bet
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

	//	Game::printBoard(*house, *player);

	cout << "\nhouse turn\n";

	do {

				for(int i = 0; i > 10; i++) {
					if(house->hand[i].rank == 1) { // if any cards
						if (house->totalBlackJackValue + 11 >= 21) {
							cout << "The house chose to value the Ace as 1";
						}
						else {
							cout << "The house chose to value the Ace as 11";
							house->totalBlackJackValue += 11;
						}
					}
				}


		if(house->totalBlackJackValue > 21) { // runs if the house has gotten a higher value than 21 and breaks out of the loop if it has
			cout << "\nThe house busted";
			break;
		}
		cout << "\n\nThe house hits "; // house keeps hitting if it hasn't busted
		house->cardsDrawn++;
		house->hand.push_back(deck[house->cardsDrawn + player->cardsDrawn]);

		int handSize = house->hand.size();  // I didn't have the time to comment on and test this fully, but it should let the house decide if it should put the ace value as 1 or 11
		for(int i = 0; i < handSize; i++) {
			if(house->hand[i].rank == 1) {
				int aceValue = 1;
				if(house->totalBlackJackValue <= 10)
					house->hand[i].blackjackValue = 11;
				else
					house->hand[i].blackjackValue = 1;

				cout << "The house set the value of " << SUIT_NAMES[house->hand[i].suit] << " to be " << aceValue << endl;
				house->sumBlackjackValue();
			}
		}

		Game::printBoard(*house, *player);
		Tool::pressToContinue();
	} while(house->totalBlackJackValue < player->totalBlackJackValue); // ensures that the house keeps hitting until it gets a higher score than the player

}

void playerHit(Card deck[], Player& player) {
	player.hand.push_back(deck[player.cardsDrawn]);
	player.cardsDrawn++;
}

bool changeAce(Player& player) {
	int handSize = player.hand.size();
	for(int i = 0; i < handSize; i++) {
		if(player.hand[i].rank == 1) {
			int aceValue;
			while (true) {
				cout << "What value would you like the Ace of " << SUIT_NAMES[player.hand[i].suit] << " to be [1 or 11]?";
				if (!Tool::tryReadInt(&aceValue))
					cout << "\nThat's not a number\n";
				else if(aceValue != 1 && aceValue != 11)
					cout << "\nYou can't put that value\n";
				else
					player.hand[i].blackjackValue = aceValue;
				break;
			}
			return true;
		}
	}
	return false;
}


PlayerMove getPlayerMove() {
	cout << "\n\n1. Hit"
			"\n2. Stand"
			"\n3. Change the value of an ace\n";

	int playerMove;
	while (!Tool::tryReadInt(&playerMove))
		cout << "\nThat's not a valid move\n";
	return (PlayerMove)playerMove;
}

bool playerTurn(Card deck[], Player* house, Player* player) {

	char exit = 'n';
	while(exit == 'n') { // runs as long as the player doesn't chose to stand
		Game::printBoard(*house, *player);
		switch (getPlayerMove()) {
			case PlayerMove::Hit:
				playerHit(deck, *player);
				break;
			case PlayerMove::Stand:
				exit = 'y'; // breaks out of the loop
				break;
			case PlayerMove::Ace:
				changeAce(*player);
				break;
			default:
				break;
		}

		player->sumBlackjackValue(); // calculates the player blackjack value

		while(player->totalBlackJackValue > 21) { // runs as long as the player has busted
			Game::printBoard(*house, *player);

			if (player->totalBlackJackValue -10 <= 21 && // runs if there is a possibility changing an ace could help you not bust by changing it from 11 to 1
					changeAce(*player)){ // forces the player to look at their aces, this isn't fully implemented yet as I ran out of time
				player->sumBlackjackValue();
				continue;
			}
			else if (player->totalBlackJackValue > 21) {
			cout << "\nYou busted and have to hand the house the minimal bet of 10$\n";
			player->cash -= 10;
			house->cash += 10;
			Tool::pressToContinue();
			return false;
			}
		}
	}
	return true;
}

void Game::checkRoundWinner(Player& house, Player& player) { // checks who won the game
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
}

void Game::game(Card deck[]) { // main game

	Player house; // creates a house
	house.name = "house";

	Player player; // creates a player
	player.name = "player";

	while(!Game::testForWinner(house, player)) {

		player.clearHand(); // resets the hands for future rounds
		house.clearHand();

		shuffle(deck);

		if(!playerTurn(deck, &house, &player)) // runs as long as player turn returns true, which is as long as they haven't busted
			continue; // restarts round if the player has busted
		player.placeBet(house);
		houseTurn(deck, &house, &player);

		checkRoundWinner(house, player);

		Tool::pressToContinue();
	}
}
