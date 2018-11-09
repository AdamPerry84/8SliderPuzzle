//Adam Perry
//10/28/2018
//This program solves 8 tile slider puzzles using BFS, DFS, A*(# of misplaced tiles), and A*(Manhattan Distance) searches. 
//It prints out the depth, time to solve, and number of nodes expanded to screen and also to excel file. 
//It also shows the path taken to solve the puzzle.

#include<iostream>
#include<fstream>
#include<cstdio>
#include<queue>
#include "MySearches.h"
#include "Board.h"

using namespace std;

int main() {
	Board board;
	MySearches searches;

	int difficulty, search;
	bool inputDifficulty = true, inputSearch = true;
	char showSteps;

	while (inputDifficulty) { //Picking the board layout
		printf("Which board would you like to use?\n"
			"1) Easy\n"
			"2) Medium\n"
			"3) Hard\n"
			"4) Random\n"
			"5) Enter your own\n"
			"6) Exit\n"
			"Select your answer: ");
		cin >> difficulty;
		while (!cin) {  //This checks that a valid data type is read in.
			cin.clear();  //This clears the error flag.
			cin.ignore(numeric_limits<streamsize>::max(), '\n');  //This flushes everything in the buffer.
			cout << "pick 1 - 6 \n";
			cin >> difficulty;
		}
		printf("\n");
		while (difficulty < 1 || difficulty > 6) {  //Checks for invalid inputs, then has user input a valid input.
			printf( "Please input a valid response.\n"
			"Which board would you like to use?\n"
				"1) Easy\n"
				"2) Medium\n"
				"3) Hard\n"
				"4) Random\n"
				"5) Enter your own\n"
				"6) Exit\n"
				"Select your answer: ");
			cin >> difficulty;
			while (!cin) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "pick 1 - 6 \n";
				cin >> difficulty;
			}
		}
		printf("\n");
		switch (difficulty) { //Makes the board of the difficulty stated.
			case 1: board.makeEasy(); break;
			case 2: board.makeMedium(); break;
			case 3: board.makeHard(); break;
			case 4: board.makeRandomBoard(); break;
			case 5: board.makeNewBoard(); break;
			case 6: return 0;
			
		}

		board.printBoard();  //print picked board
		cout << endl;

		inputSearch = true;

		while (inputSearch) {  //Picking the search type
			printf("Which search would you like to use?\n"
				"1) Breadth-First Search\n"
				"2) Depth-First Search \n"
				"3) A* Search (tiles out of place heuristic)\n"
				"4) A* Search (manhattan block heuristic)\n"
				"5) Return to previous menu.\n"
				"6) Close Program. \n"
				"Select your answer: ");
			cin >> search;
			while (!cin) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "pick 1 - 6 \n";
				cin >> search;
			}
			printf("\n");

			while (search < 1 || search > 6) { //Checks for invalid inputs, then has user input a valid input.
				printf( "Please input a valide response.\n"
						"Which search would you like to use?\n"
						"1) Breadth-First Search\n"
						"2) Depth-First Search \n"
						"3) A* Search (tiles out of place heuristic)\n"
						"4) A* Search (manhattan block heuristic)\n"
						"5) Return to previous menu.\n"
						"6) Close Program. \n"
						"Select your answer: ");
				cin >> search;
				while (!cin) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "pick 1 - 6 \n";
					cin >> search;
				}
				printf("\n");
			}

			searches.clearRepeats();  //clear repeats

			switch (search) {  //The different search functions to call
				case 1: searches.BFS(board); break;
				case 2: searches.DFS(board); break;
				case 3: searches.ASearch(board); break;
				case 4: searches.AManSearch(board); break;
				case 5: inputSearch = false; break;
				case 6: return 0;
			}
			if (inputSearch == true) {
				cout << "Would you like to see the steps to reach the solution?\n" //showing the steps
					<< "Select you answer(y == yes, n == no):  ";
				cin >> showSteps;
				if (showSteps == 'y' || showSteps == 'Y') {
					searches.printPath();
					printf("\n");
				}
			}
		}
	}

	system("Pause");
	return 0;
}