#ifndef _Board
#define _Board

#include<iostream>
#include<cstdio>
#include<vector>
#include<string>

using namespace std;

class Board {
private:
	vector<int> board; //Current Board
	vector<int> correctBoard; //Correct Board (Answer)

public:
	void printBoard();

	Board(); //Constructor
	Board(Board &); //Copy-Constructor
	~Board() {}; //De-Constructor

	void clearBoard(); //Clears the board.
	void makeEasy(); //Make the "easy" board set-up
	void makeMedium(); //Make the "medium" board set-up
	void makeHard(); //Make the "hard" board set-up
	void makeNewBoard(); //Make a custom board
	void makeRandomBoard(); //Make a random board

	int zeroIndex(); //Returns the index at which the empty tile slot can be found.
	int manDistance(); //Returns the manhattan distance of the board.
	int misplacedTiles(); //Returns the number of tiles out of their correct position.

	string stringEquiv(); //Turns the board into a string. Used in the hashing for repeats.

	bool checkAnswer(); //Checks if current board is == answer
	Board makeMove(int index, int destination); //Makes a move from index to destination

};

#endif