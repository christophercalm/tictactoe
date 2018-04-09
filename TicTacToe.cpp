/*
things still to write:
user input data protectiong: ex. right now, player 2 can play on the same tile player 1 just played,
overriding their moves. Also protecting against the user entering bad values, like N or 929241. Users
should only be able to enter X or O (ideally only X if they are player 1 and O if they are player 2).
checkIfWon() already has this protection, looping until the user enters Y or N.
*/

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

bool won = false; //if the game has been won
bool player1 = true; //checks which player is active
bool playAgain = true;
int input; //the player input
string game[9] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; //array for the game

//redraw() clears whatever is in the console and draws the game board with the most recent values
//prevents the console from filling up with old data
bool redraw() {
	system("cls");
	cout << "Let's play Tic-Tac-Toe!\n\n";
	cout << "Player 1: X | Player 2: O\n\n";
	cout << "	" << game[0] << " | " << game[1] << " | " << game[2] << "\n";
	cout << "	----------\n";
	cout << "	" << game[3] << " | " << game[4] << " | " << game[5] << "\n";
	cout << "	----------\n";
	cout << "	" << game[6] << " | " << game[7] << " | " << game[8] << "\n\n";
	return player1; //returns the next player (this is used to check the winner)
}

//this asks for player input. This and redraw() are separate so that the board can be redrawn at the
//end of the game without asking for user input again
void playerInput() {
	if (player1) {
		cout << "Player 1, enter your move: ";
		cin >> input;
		game[input - 1] = "X";
		player1 = false; //sets the player to player 2
	}
	else {
		cout << "Player 2, enter your move: ";
		cin >> input;
		game[input - 1] = "O";
		player1 = true; //sets the player to player 1
	}
}
//checkIfWon() does just that - checks all possible winning combos and returns true if one is met
bool checkIfWon() {
	if ((game[0] == game[1] && game[1] == game[2])
		|| (game[3] == game[4] && game[4] == game[5])
		|| (game[6] == game[7] && game[7] == game[8])
		|| (game[0] == game[3] && game[3] == game[6])
		|| (game[1] == game[4] && game[4] == game[7])
		|| (game[2] == game[5] && game[5] == game[8])
		|| (game[0] == game[4] && game[4] == game[8])
		|| (game[2] == game[4] && game[4] == game[6]))
		won = true;
	else
		won = false;
	return won;
}

//this runs when someone wins the game
//announces the winner and asks if the players want to play again
bool youWon() {
	string playAgainString;
	if (player1)
		cout << "Player 2 won!\n\n";
	else
		cout << "Player 1 won!\n\n";
	cout << "Would you like to play again?\n";
	while (true) {
		cout << "Y or N: ";
		cin >> playAgainString;
		if (playAgainString == "Y") {
			playAgain = true;
			break;
		}
		else if (playAgainString == "N") {
			playAgain = false;
			break;
		}
		else
			cout << "That's not a valid input. Please try again.\n";
	}
	return playAgain;
}

//this resets the game board in the event of a player starting a new game
void reset() {
	game[0] = "1";	game[1] = "2";	game[2] = "3";
	game[3] = "4";	game[4] = "5";	game[5] = "6";
	game[6] = "7";	game[7] = "8";	game[8] = "9";
	won = false;
	player1 = true;
	input = 0;
}

//loops redraw(), playerInput() and checkIfWon() until checkIfWon() returns true, then prints the winner
//and asks the user if they'd like to close the program or play again.
int main() {
	while (playAgain) {
		while (!won) {
			redraw();
			playerInput();
			checkIfWon();
		}
		redraw(); //redraws the final board
		if (won) {
			youWon();
			reset();
		}
	}
	cout << "\nUntil next time!";
	Sleep(3000);	
}