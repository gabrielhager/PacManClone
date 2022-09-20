/****************************************************************

File: PacmanSource.cpp

Description:

Gabriel's Project 3 (CSCI110) replicates the classic arcade game Pacman. Players use the WASD keys to move around the map
and collect dots while trying to avoid the enemy ghosts. The game is over when EITHER the player collects all dots on the
level, or comes into contact with one of the enemy ghosts.

Author: Gabriel Hager 

Class: CSCI 110

Date: 4/18/17


I hereby certify that this program is entirely my own work.

*****************************************************************/

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
using namespace std;

// Global Variables
const int ROWS = 30;
const int COLS = 28;
char maze[ROWS][COLS];

//Proto Types
void DrawHeader();
void DrawMaze(int& playerScore);
int PlayerMovement();
int GhostMovement(int xCoord, int yCoord, int xGhost, int yGhost);

// LEVEL 1 (ONLY LEVEL)
char maze1[ROWS][COLS] = {
	{ 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219 },		// 219 = Wall
	{ 219, 'O', 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 219, 219, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 219 },		// 250 = Dot
	{ 219, 250, 219, 219, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 219, 219, 250, 219 },
	{ 219, 250, 219, 219, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 219, 219, 250, 219 },
	{ 219, 250, 219, 219, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 219, 219, 250, 219 },
	{ 219, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 219 },		// All Dot Road
	{ 219, 250, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 250, 219 },
	{ 219, 250, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 250, 219 },
	{ 219, 250, 250, 250, 250, 250, 250, 219, 219, 250, 250, 250, 250, 219, 219, 250, 250, 250, 250, 219, 219, 250, 250, 250, 250, 250, 250, 219 },
	{ 219, 219, 219, 219, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 219, 219, 219, 219 },
	{ 219, 219, 219, 219, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 219, 219, 219, 219 },
	{ 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219 },
	{ 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219 },		// Top Ghost Block
	{ 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250 },
	{ 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219 },		// CROSSING MID
	{ 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219 },
	{ 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219 },		// "READY!"
	{ 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219 },
	{ 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219 },
	{ 219, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 219, 219, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 219 },
	{ 219, 250, 219, 219, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 219, 219, 250, 219 },
	{ 219, 250, 219, 219, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 250, 219, 219, 219, 219, 250, 219 },
	{ 219, 250, 250, 250, 219, 219, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 219, 219, 250, 250, 250, 219 },		// THIS IT THE ROW TO START ON
	{ 219, 219, 219, 250, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 250, 219, 219, 219 },
	{ 219, 219, 219, 250, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 250, 219, 219, 219 },
	{ 219, 250, 250, 250, 250, 250, 250, 219, 219, 250, 250, 250, 250, 219, 219, 250, 250, 250, 250, 219, 219, 250, 250, 250, 250, 250, 250, 219 },
	{ 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219 },
	{ 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219, 219, 250, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 250, 219 },		//
	{ 219, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 219 },		// Last row of dots
	{ 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219 },


};

// MAIN
int main() {
	// Local Variables
	int score = 0;
	char replay;
	bool isTrue = true;

	// Outputs program header
	DrawHeader();

	do {

		// Explains the rules for the game
		cout << "Here are the rules:" << endl;
		cout << "1) Move using <w> up, <a> left, <s> down, <d> right" << endl;
		cout << "2) Avoid the Ghost." << endl;
		cout << "3) Collect all the dots to win!" << endl << endl;



		system("pause");	// Used to allow user to read the rules and levels before playing
		cout << endl;


		system("cls");		// Used to clear console

		// Copy a different array in to maze so we only need one DrawMaze and PlayerMovement function
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++)
				maze[i][j] = maze1[i][j];
		}
		DrawMaze(score);				// Outputs maze with copied values
		score = PlayerMovement();		// Used to output the players score returned by PlayerMovement


		// Ending screen
		cout << endl;
		cout << "Final score: " << score << endl << endl;
		system("pause");
		cout << endl;
		score = 0;

		// Ask user if they want to play again
		cout << "Would you like to play again?" << endl;
		cout << "<y> to play again, <q> to quit: ";
		cin >> replay;

		while (replay != 'y' && replay != 'q') {
			cout << "<y> to play again, <q> to quit: ";
			cin >> replay;
		}
		if (replay == 'q') {
			isTrue = false;
		}
		system("cls");
	} while (isTrue);

	cout << "Thank you for playing!!!" << endl;
	cout << "Goodbye" << endl;

	return 0;
}

// Program heading
void DrawHeader() {
	const int ROWS = 17;
	const int COLS = 37;
	int heading[ROWS][COLS] = {
		{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0 },
		{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0 },
		{ 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0 },
		{ 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
		{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 },
	};

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			switch (heading[i][j]) {		// Converts the elements to different symbols and then outputs the new elements
			case 0:
				cout << " ";
				break;
			case 1:
				cout << char(178);
				break;
			}
		}
		cout << endl;
	}
	cout << "By Gabriel Hager" << endl << endl << endl;
	system("pause");	// Used to separate the header from the rest of the program
	system("cls");		// Used to clear header from the console
	return;
};


// Function to draw out the maze
void DrawMaze(int& playerScore) {
	system("Color 18");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}
	cout << "Score: " << playerScore << endl;
	//cout << endl;
	return;
}

// Function for the players moves
int PlayerMovement() {
	char playerControls = ' ';
	bool gameWon = false;
	bool gameLost = false;
	int xCoord = 1;
	int yCoord = 1;
	int xGhost = 26;
	int yGhost = 1;
	int xGhost2 = 26;
	int yGhost2 = 28;
	int playerScore = 0;
	int ghostDirection = -1;

	while (!gameWon && !gameLost) {
		//Player input
		playerControls = _getch();
		Sleep(150);					// Used to allow user to see their input before outputting the new updated maze

		//Move Right
		if (playerControls == 'd' && maze[yCoord][xCoord + 1] != char(219)) {
			if (maze[yCoord][xCoord + 1] == char(250)) {						// Adds one point for each dot picked up
				playerScore = playerScore + 1;
			}
			maze[yCoord][xCoord] = ' ';											// Updates the previous position to become a space
			xCoord++;															// Update the x-coordinate
			maze[yCoord][xCoord] = '<';											// Moves the position of the player
		}
		//Move Left
		if (playerControls == 'a' && maze[yCoord][xCoord - 1] != char(219)) {
			if (maze[yCoord][xCoord - 1] == char(250)) {
				playerScore = playerScore + 1;
			}
			maze[yCoord][xCoord] = ' ';
			xCoord--;
			maze[yCoord][xCoord] = '>';
		}
		//Move UP
		if (playerControls == 'w' && maze[yCoord - 1][xCoord] != char(219)) {
			if (maze[yCoord - 1][xCoord] == char(250)) {
				playerScore = playerScore + 1;
			}
			maze[yCoord][xCoord] = ' ';
			yCoord--;
			maze[yCoord][xCoord] = 'V';
		}
		//Move Down
		if (playerControls == 's' && maze[yCoord + 1][xCoord] != char(219)) {
			if (maze[yCoord + 1][xCoord] == char(250)) {
				playerScore = playerScore + 1;
			}
			maze[yCoord][xCoord] = ' ';
			yCoord++;
			maze[yCoord][xCoord] = char(94);
		}

		ghostDirection = GhostMovement(xCoord, yCoord, xGhost, yGhost);

		switch (ghostDirection)														// Moves Ghost 1
		{
		case 0:
			maze[yGhost][xGhost] = maze[yGhost][xGhost + 1];
			xGhost++;
			maze[yGhost][xGhost] = char(234);
			break;
		case 1:
			maze[yGhost][xGhost] = maze[yGhost][xGhost - 1];
			xGhost--;
			maze[yGhost][xGhost] = char(234);
			break;
		case 2:
			maze[yGhost][xGhost] = maze[yGhost - 1][xGhost];
			yGhost--;
			maze[yGhost][xGhost] = char(234);
			break;
		case 3:
			maze[yGhost][xGhost] = maze[yGhost + 1][xGhost];
			yGhost++;
			maze[yGhost][xGhost] = char(234);
			break;
		case 5:
			gameLost = true;
			break;
		}

		// Ghost 2
		switch (GhostMovement(xCoord, yCoord, xGhost2, yGhost2))						// Moves Ghost 2
		{
		case 0:
			maze[yGhost2][xGhost2] = maze[yGhost2][xGhost2 + 1];
			xGhost2++;
			maze[yGhost2][xGhost2] = char(234);
			break;
		case 1:
			maze[yGhost2][xGhost2] = maze[yGhost2][xGhost2 - 1];
			xGhost2--;
			maze[yGhost2][xGhost2] = char(234);
			break;
		case 2:
			maze[yGhost2][xGhost2] = maze[yGhost2 - 1][xGhost2];
			yGhost2--;
			maze[yGhost2][xGhost2] = char(234);
			break;
		case 3:
			maze[yGhost2][xGhost2] = maze[yGhost2 + 1][xGhost2];
			yGhost2++;
			maze[yGhost2][xGhost2] = char(234);
			break;
		case 5:
			cout << "YOU LOSE!" << endl;
			gameWon = true;
			break;
		}

		system("cls");

		// VICTORY
		if (playerScore == 293) {
			cout << "YOU WIN!!!" << endl;
			gameWon = true;
		}
		// GAME OVER
		if (maze[yCoord][xCoord] == maze[yGhost][xGhost] || maze[yCoord][xCoord] == maze[yGhost2][xGhost2]) {
			cout << "YOU LOSE!" << endl;
			gameLost = true;
		}
		DrawMaze(playerScore);			// Redraws the maze with the updated coordinates

	}
	return playerScore;					// Returns the players score
}

// Function for enemy movement
int GhostMovement(int xCoord, int yCoord, int xGhost, int yGhost) {

	int moveDirection;

	if (maze[yCoord][xCoord] == maze[yGhost][xGhost])					// If player and ghost collide, end game
	{
		moveDirection = 5;
		return moveDirection;
	}

	// DECIDE WHERE CAN MOVE (Check for walls and player location, attemp to move towards player if possible, otherwise move to a "legal" spot
	if ((maze[yGhost][xGhost + 1] != char(219)) && xCoord > xGhost) {
		moveDirection = 0;
	}
	else if ((maze[yGhost][xGhost - 1] != char(219)) && xCoord < xGhost) {
		moveDirection = 1;
	}
	// When x-Coords are equal
	else if (((maze[yGhost + 1][xGhost] != char(219)) || (maze[yGhost - 1][xGhost] != char(219)) || (maze[yGhost][xGhost - 1] != char(219)) || (maze[yGhost][xGhost + 1] != char(219))) && xCoord == xGhost) {
		if (maze[yGhost + 1][xGhost] != char(219)) {
			moveDirection = 3;
		}
		else if (maze[yGhost - 1][xGhost] != char(219)) {
			moveDirection = 2;
		}
		else if (maze[yGhost][xGhost + 1] != char(219)) {
			moveDirection = 0;
		}
		else if (maze[yGhost][xGhost - 1] != char(219)) {
			moveDirection = 1;
		}
	}
	else if ((maze[yGhost - 1][xGhost] != char(219)) && yCoord < yGhost) {
		moveDirection = 2;
	}
	else if ((maze[yGhost + 1][xGhost] != char(219)) && yCoord >= yGhost) {
		moveDirection = 3;
	}
	// When y-Coords are equal
	else if (((maze[yGhost][xGhost - 1] != char(219)) || (maze[yGhost][xGhost + 1] != char(219)) || (maze[yGhost + 1][xGhost] != char(219)) || (maze[yGhost - 1][xGhost] != char(219))) && yCoord == yGhost) {
		if (maze[yGhost][xGhost + 1] != char(219)) {
			moveDirection = 0;
		}
		else if (maze[yGhost][xGhost + 1] != char(219)) {
			moveDirection = 1;
		}
		else if (maze[yGhost + 1][xGhost] != char(219)) {
			moveDirection = 3;
		}
		else if (maze[yGhost - 1][xGhost] != char(219)) {
			moveDirection = 2;
		}
	}
	// Any missed cases will come here causing the ghost to not move at all until a recognized movement is possible
	else {
		moveDirection = 4;
	}

	return moveDirection;		// Returns Ghost Move Direction
}

