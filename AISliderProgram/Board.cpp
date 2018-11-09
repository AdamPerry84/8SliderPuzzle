#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<fstream>
#include "Board.h"

using namespace std;

//ofstream outFile2; //Stream writer to write valid paths to our data file.

Board::Board() {
	int goal[9] = { 1, 2, 3,  //Array of the board's goal state.
					4, 5, 6,
					7, 8, 0 };

	for (int i = 0; i < 9; ++i)  //Transfers the goal state data to the winning board vector.
		correctBoard.push_back(goal[i]);
}

Board::Board(Board &other) {
	for (int i = 0; i < 9; ++i) {
		board.push_back(other.board[i]);
		correctBoard.push_back(other.correctBoard[i]);
	}
}

//Prints board in format
void Board::printBoard() {
//	outFile2.open("results.csv"); // output excel file
	for (int i = 0; i < 9; ++i) {
		if (i % 3 == 0)
			printf("\n");
//		outFile2 << endl;
		printf("%i\t", board[i]);
//		outFile2 << "%i\t" << board[i];
	}
	printf("\n\n");
//	outFile2 << endl;
//	outFile2.close();
}

string Board::stringEquiv() {  //Returns a string representing the board
	string val;
	for (int i = 0; i < 9; ++i)
		val += to_string(board[i]);
	return val;
}

int Board::zeroIndex() {
	for (int i = 0; i < 9; ++i)
		if (board[i] == 0)
			return i;
	return NULL;
}

int Board::manDistance() {
	int num;
	int distance = 0;
	for (int i = 0; i < 9; ++i) {  //Iterates through the board until it finds 0
		num = correctBoard[i];
		for (int j = 0; j < 9; ++j) {
			if (board[j] == num)
				distance += abs(floor(i / 3) - floor(j / 3)) + abs((i % 3) - (j % 3));
		}
	}
	return distance;
}

int Board::misplacedTiles() {
	int tiles = 0;

	for (int i = 0; i < 9; i++) {
		if (correctBoard[i] == 0)
			continue;  //Does not count the empty tile position
		if (board[i] != correctBoard[i])
			++tiles;
	}
	return tiles;
}

//These next two functions are another way to check if board is solvable. I'm experimenting with these.  
// A utility function to count inversions in given array 'arr[]' 
/*int Board::getInvCount(int arr[])
{
	int inv_count = 0;
	for (int i = 0; i < 9 - 1; i++)
		for (int j = i + 1; j < 9; j++)
			// Value 0 is used for empty space 
			if (arr[j] && arr[i] && arr[i] > arr[j])
				inv_count++;
	return inv_count;
}*/

// This function returns true if given puzzle is solvable. 
/*bool Board::isSolvable(int newBoard[3][3])
{
	// Count inversions in given 8 puzzle 
	int invCount = getInvCount((int *)newBoard);

	// return true if inversion count is even. 
	return (invCount % 2 == 0);
}*/

//The next four functions create an array of integers representing the given difficulty arrays, and then transfers the data over to the current board.
void Board::clearBoard() {
	if (!board.empty()) {	//Needed to avoid failed iterator dereferences
		for (int i = 0; i < 9; ++i)
			board.pop_back();
	}
}

void Board::makeEasy() {
	clearBoard();
	int newBoard[9] = { 0, 2, 3,
						1, 5, 6,
						4, 7, 8 };

	for (int i = 0; i < 9; ++i)
		board.push_back(newBoard[i]);
}

void Board::makeMedium() {
	clearBoard();
	int newBoard[9] = { 4, 1, 0,
						7, 5, 2,
						8, 6, 3 };

	for (int i = 0; i < 9; ++i)
		board.push_back(newBoard[i]);
}

void Board::makeHard() {
	clearBoard();
	int newBoard[9] = { 0, 8, 7,
						6, 5, 4,
						3, 2, 1 };

	for (int i = 0; i < 9; ++i)
		board.push_back(newBoard[i]);
}

//Creates a new board from the user's input.
void Board::makeNewBoard() {
	int nextInt = 0;
	for (int i = 0; i < 9; ++i) {
		printf("Enter element %i: ", i);
		cin >> nextInt;
		while (!cin) { //This checks that a valid data type is read in.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Type numbers 0-8 with no repeated numbers. \n";
			cin >> nextInt;
		}
		board.push_back(nextInt);
		printf("\n");
	}
}
//Creates a new random board.
void Board::makeRandomBoard() {
	clearBoard();
	int newBoard[9];
	int ranNum0, ranNum1, ranNum2, ranNum3, ranNum4, ranNum5, ranNum6, ranNum7, ranNum8 = 0;
	srand(time(0));
	ranNum0 = rand() % 9; //Assigning a random number 0-9 to ranNum0.
	ranNum1 = rand() % 9;
		board.push_back(newBoard[0] = ranNum0); //Putting new unique random number into newBoard[0].
		while (ranNum1 == ranNum0) { //Making sure no numbers are repeated.
			ranNum1 = rand() % 9;
		}
		board.push_back(newBoard[1] = ranNum1); 
	ranNum2 = rand() % 9;
		while ((ranNum2 == ranNum0) || (ranNum2 == ranNum1)) {
			ranNum2 = rand() % 9;
		}
		board.push_back(newBoard[2] = ranNum2);
	ranNum3 = rand() % 9;
		while ((ranNum3 == ranNum0) || (ranNum3 == ranNum1) || (ranNum3 == ranNum2)) {
			ranNum3 = rand() % 9;
		}
		board.push_back(newBoard[3] = ranNum3);
	ranNum4 = rand() % 9;
		while ((ranNum4 == ranNum0) || (ranNum4 == ranNum1) || (ranNum4 == ranNum2) || (ranNum4 == ranNum3)) {
			ranNum4 = rand() % 9;
		}
		board.push_back(newBoard[4] = ranNum4);
	ranNum5 = rand() % 9;
		while ((ranNum5 == ranNum0) || (ranNum5 == ranNum1) || (ranNum5 == ranNum2) || (ranNum5 == ranNum3) || (ranNum5 == ranNum4)) {
			ranNum5 = rand() % 9;
		}
		board.push_back(newBoard[5] = ranNum5);
	ranNum6 = rand() % 9;
		while ((ranNum6 == ranNum0) || (ranNum6 == ranNum1) || (ranNum6 == ranNum2) || (ranNum6 == ranNum3) || (ranNum6 == ranNum4) || (ranNum6 == ranNum5)) {
			ranNum6 = rand() % 9;
		}
		board.push_back(newBoard[6] = ranNum6);
	ranNum7=  rand() % 9;
		while ((ranNum7 == ranNum0) || (ranNum7 == ranNum1) || (ranNum7 == ranNum2) || (ranNum7 == ranNum3) || (ranNum7 == ranNum4) || (ranNum7 == ranNum5) || (ranNum7 == ranNum6)) {
			ranNum7 = rand() % 9;
		}
		board.push_back(newBoard[7] = ranNum7);
	ranNum8 = rand() % 9;
		while ((ranNum8 == ranNum0) || (ranNum8 == ranNum1) || (ranNum8 == ranNum2) || (ranNum8 == ranNum3) || (ranNum8 == ranNum4) || (ranNum8 == ranNum5) || (ranNum8 == ranNum6) || (ranNum8 == ranNum7)) {
			ranNum8 = rand() % 9;
		}
		board.push_back(newBoard[8] = ranNum8);
	
}

//Checks the goal state compared to the current state. 
//Returns false if it finds any incorrect tile placements. 
//Otherwise it returns true.
bool Board::checkAnswer() {
	if (board == correctBoard)
		return true;
	return false;
}

//Copies the current board into a temporary board,
//then it moves the desired pieces, and returns the temporary board.
Board Board::makeMove(int index, int destination) {
	Board tmp(*this);
	tmp.board[index] = board[destination];
	tmp.board[destination] = board[index];
	return tmp;
}