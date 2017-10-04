#include "game.h"

using namespace std;

// the code is slightly different than the assignment, I'm sorry, but next time I'll try to limit myself to the assignment
// I've made a deck of cards to work with that gets shuffeled and you draw from the top
// this is because I wanted to print the cards to screen to make it feel a little more like blackjack

// I wanted to challenge myself, but I have not looked up any solutions for any of the full functions, methods or the full game online
// I've only looked at documentation for specific things such as how to get a random number, how to use classes, vectors etc

// I've tried fixing the mistakes I made from last compulsory, mainly the text in the headers and trying to use classes
// I've still got a long way to go but I'm trying to get a hang of it.





int main() {
	cout << "***** BlackJack *****\n\n";

	cout << "Hello, and welcome to this stripped down game of Blackjack.\n\n" <<

			"Your goal is simple: Get the total value of your cards as close to 21 as you can.\n" <<

			"You can chose to draw as many cards as you like [hit],\n" <<
			"or leave your hand as it is [stand].\n" <<
			"You then place a bet and the house will try to beat you.\n" <<
			"The game is over when either player reaches 0$\n\n" <<

			"The value of Ace is either 1 or 11\n" <<
			"The value of numbered cards is their equal number\n" <<
			"The value of all face-cards is 10.\n\n" <<

			"Good luck!\n\n\n";
	Card deck[52]; // declare array for holing 52 cards
	Game::createDeck(deck); // creates the elements of the array deck
	Tool::pressToContinue(); // pauses the game so the player ha stime to read the rules before moving on

	string yesNo = "y";
	while(yesNo != "n") { // a loop so that the player can chose to play again at the end of the game
		Game::game(deck); // runs the main game

		while(true) { // a loop that runs as long as the user input is invalid
		cout << "\n\nWhould you like to play again [y/n]? ";
		yesNo = Tool::readLine();
		yesNo = Tool::toLower(yesNo); // makes the answer lower case
		if(yesNo == "y" || yesNo == "n")
			break; // jumps out of the loop if the player has a valid input
		else
			cout << "Invalid input.";
		}
	}
	return 0;
}
