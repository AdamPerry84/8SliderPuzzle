#include<cstdio>
#include "MySearches.h"
#include<iostream>
#include<fstream>
#include <cstdlib>

using namespace std;

ofstream outFile; //Stream writer to write valid paths to our data file.

//Finds all possible nodes that could be derived from the parent node.
//Saves them as parent node's children.
void MySearches::successors(Node *parent) {
	if (parent->zeroIndex % 3 == 0)  //Finds possible child if zero tile is in column 0
		parent->children.push_back(new Node(parent->depth + 1, parent->myBoard.makeMove(parent->zeroIndex, parent->zeroIndex + 1), parent->zeroIndex + 1, parent));
	else if (parent->zeroIndex % 3 == 1) {  //Finds possible child if zero tile is in column 1 
		parent->children.push_back(new Node(parent->depth + 1, parent->myBoard.makeMove(parent->zeroIndex, parent->zeroIndex - 1), parent->zeroIndex - 1, parent));
		parent->children.push_back(new Node(parent->depth + 1, parent->myBoard.makeMove(parent->zeroIndex, parent->zeroIndex + 1), parent->zeroIndex + 1, parent));
	}
	else  //Finds possible child if zero tile is in column 2
		parent->children.push_back(new Node(parent->depth + 1, parent->myBoard.makeMove(parent->zeroIndex, parent->zeroIndex - 1), parent->zeroIndex - 1, parent));

	if(parent->zeroIndex < 3)  //Finds possible child if zero tile is in row 0
		parent->children.push_back(new Node(parent->depth + 1, parent->myBoard.makeMove(parent->zeroIndex, parent->zeroIndex + 3), parent->zeroIndex + 3, parent));
	else if (parent->zeroIndex < 6) {  //Finds possible child if zero tile is in row 1
		parent->children.push_back(new Node(parent->depth + 1, parent->myBoard.makeMove(parent->zeroIndex, parent->zeroIndex - 3), parent->zeroIndex - 3, parent));
		parent->children.push_back(new Node(parent->depth + 1, parent->myBoard.makeMove(parent->zeroIndex, parent->zeroIndex + 3), parent->zeroIndex + 3, parent));
	}
	else  //Finds possible child if zero tile is in row 2
		parent->children.push_back(new Node(parent->depth + 1, parent->myBoard.makeMove(parent->zeroIndex, parent->zeroIndex - 3), parent->zeroIndex - 3, parent));
}

//Attempts to find the string representation of the board. if it cannot find it,
//it returns false, otherwise true.
bool MySearches::repeat(string board) {
	if (repeatTracker.find(board) != repeatTracker.end())
		return true;
	return false;
}

//Follows the path upwards from the correct node,
//saving the parent node's it encounters in a vector,
//and then it prints the vector out in reverse order.
void MySearches::printPath() {
	if (answerNode != NULL) {
		vector<Node *> path;
		Node *tmp = answerNode;
		while (tmp != NULL) {
			path.push_back(tmp);
			tmp = tmp->parent;
		}

		for (int i = path.size() - 1; i >= 0; --i)
			(path[i]->myBoard).printBoard();
	}
}

//Prints the statistics gathered from the search.
void MySearches::printReport(int depth, double time, int maxHeld) {
	outFile.open("results.csv"); // output excel file 
	printf("The solution was found at depth %i. \n"
		"The time taken to find the solution was %.0f milliseconds. \n"
		"The number of nodes that were expanded was %i nodes. \n\n",
		depth, time, maxHeld);
	outFile << "The solution was found at depth " << depth << ".\n";
	outFile << "The time taken to find the solution was " << time << " milliseconds.\n";
	outFile << "The number of nodes that were expanded was " << maxHeld << " nodes. \n\n";
	outFile.close();
}

void MySearches::clearRepeats() {
	repeatTracker.clear();
}

//Breadth-First Search
void MySearches::BFS(Board board) {
	deque<Node *> que;

	start = clock();  //Begins the timer.

	Node *node = new Node(0, board, board.zeroIndex());  //Creates a node of the given board. Acts as the "root" to the tree.
	que.push_back(node);  //Adds the original board to the queue.
	repeatTracker.insert(pair<string, Node *>((node->myBoard).stringEquiv(), node));  //Adds root node to the repeat-checker map.

	maxNodes = 1;  //Keeps track of the maximum number of nodes stored in the queue at any given time.

	while (!que.empty()) {  //While there are boards to look at, continue executing.
		node = que.front();  //"Saves" the first node in the queue. On first iteration, this is the root.
		que.pop_front();  //Deletes the first node from the queue. On first iteration, this is the root.

		if ((node->myBoard).checkAnswer()) {  //Checks to see if the root node is the correct answer.
			answerNode = node;  //Saves answer's pointer to print out later.

			finish = clock();  //Ends the time.
			measuredTime = (finish - start) * 1000.0 / CLOCKS_PER_SEC;  //Calculates the difference in time from the end of the counter to the beginning.
			printReport(node->depth, measuredTime, maxNodes);  //Reports statistics.

			return;  //Ends execution.
		}

		successors(node);  //Finds the possible other moves for the saved board, and saves them as children.
		for (unsigned int i = 0; i < (node)->children.size(); ++i) {  //Look at all of the saved node's children.
			if (!repeat((node->children[i])->myBoard.stringEquiv())) {  //If the child was not the answer, check to make sure it is not a repeat. 
				repeatTracker.insert(pair<string, Node *>((node->children[i])->myBoard.stringEquiv(), node->children[i]));  //Since it is not a repeat, add it to the has-seen map.
				que.push_back(node->children[i]);  //Push the board onto the back of the queue(first-in-first-out).
			}

			if (que.size() > maxNodes)  //Update the maximum nodes stored in the queue, if it exceeds the current maximum stored at any given point.
				maxNodes = que.size();
		}
	}
	//If no solution was found, end execution.
	printf("Could not find a solution. \n");
}

//Depth-First Search
void MySearches::DFS(Board board) {
	deque<Node *> que;
	start = clock();

	Node *node = new Node(0, board, board.zeroIndex());
	que.push_front(node);  //Push to the front of the queue, since this is a last-in-first-out search.

	maxNodes = 1;

	repeatTracker.insert(pair<string, Node *>((node->myBoard).stringEquiv(), node));

	while (!que.empty()) {  
		node = que.front();  //Push to the front of the queue, since this is a last-in-first-out search.
		que.pop_front();  //Pop the node that was just saved

		if ((node->myBoard).checkAnswer()) {
			answerNode = node;  //Saves answer's pointer to print out later.

			finish = clock();
			measuredTime = (finish - start) * 1000.0 / CLOCKS_PER_SEC;  //Calculates the difference in time from the end of the counter to the beginning.
			printReport(node->depth, measuredTime, maxNodes);  //Reports statistics.

			return;
		}

		successors(node);  //Finds the possible other moves for the saved board, and saves them as children.
		for (unsigned int i = 0; i < (node)->children.size(); ++i) {  //look at all the saved node's children.
			if (!repeat((node->children[i])->myBoard.stringEquiv())) {  //If the child was not the answer, check to make sure it is not a repeat.
				repeatTracker.insert(pair<string, Node *>((node->children[i])->myBoard.stringEquiv(), node->children[i]));  //Since it is not a repeat, add it to the has-seen map.
				que.push_front(node->children[i]);  //Push the board onto the front of the queue(last-in-first-out).
			}

			if (que.size() > maxNodes)  //Update the maximum nodes stored in the queue, if it exceeds the current maximum stored at any given point.
				maxNodes = que.size();
		}
	}

	//If no solution was found, end execution.
	printf("Could not find a solution. \n");
}

//A* Search (heuristic = misplaced tiles)
void MySearches::ASearch(Board board) {
	start = clock();

	priority_queue<Node *, vector<Node *>, comp> q;  //priority queue
	int answerDistance = 0;

	Node *node = new Node(0, board, board.zeroIndex());
	node->f = node->myBoard.misplacedTiles() + node->depth;

	q.push(node);  //Push to the front of the queue.

	maxNodes = 1;

	repeatTracker.insert(pair<string, Node *>((node->myBoard).stringEquiv(), node));

	while (!q.empty()) {
		node = q.top();
		q.pop();

		if ((node->myBoard).checkAnswer()) {  //Check if node being examined is the answer.
			answerNode = node;  //Saves answer's pointer to print out later.

			finish = clock();
			measuredTime = (finish - start) * 1000.0 / CLOCKS_PER_SEC;  //Calculates the difference in time from the end of the counter to the beginning.
			printReport(node->depth, measuredTime, maxNodes);  //Reports statistics.

			return;
		}

		successors(node);  //Finds the possible other moves for the saved board, and saves them as children.
		for (unsigned int i = 0; i < (node)->children.size(); ++i) {  //look at all the saved node's children.
			if (!repeat((node->children[i])->myBoard.stringEquiv())) {  //If the child was not the answer, check to make sure it is not a repeat.
				repeatTracker.insert(pair<string, Node *>((node->children[i])->myBoard.stringEquiv(), node->children[i]));  //Since it is not a repeat, add it to the has-seen map.
				(node->children[i])->f = (node->children[i])->myBoard.misplacedTiles() + (node->children[i])->depth;  //f = g + h || f = misplaced tiles + depth of child node 
				q.push(node->children[i]);  //Push onto the priority queue.
			}

			if (q.size() > maxNodes)  //Update the maximum nodes stored in the queue, if it exceeds the current maximum stored at any given point.
				maxNodes = q.size();
		}
	}

	//If no solution was found, end execution.
	printf("Could not find a solution. \n");
}

//A* Search (heuristic = manhattan blocks)
//Same code as above, the heuristic is just different.
void MySearches::AManSearch(Board board) {
	start = clock();

	priority_queue<Node *, vector<Node *>, comp> q;
	int answerDistance = 0;

	Node *node = new Node(0, board, board.zeroIndex());
	node->f = node->myBoard.misplacedTiles() + node->depth;

	q.push(node);

	maxNodes = 1;

	repeatTracker.insert(pair<string, Node *>((node->myBoard).stringEquiv(), node));

	while (!q.empty()) {
		node = q.top();
		q.pop();

		if ((node->myBoard).checkAnswer()) {
			answerNode = node;

			finish = clock();
			measuredTime = (finish - start) * 1000.0 / CLOCKS_PER_SEC;
			printReport(node->depth, measuredTime, maxNodes);

			return;
		}

		successors(node);
		for (unsigned int i = 0; i < (node)->children.size(); ++i) {
			if (!repeat((node->children[i])->myBoard.stringEquiv())) {
				repeatTracker.insert(pair<string, Node *>((node->children[i])->myBoard.stringEquiv(), node->children[i]));
				(node->children[i])->f = (node->children[i])->myBoard.manDistance() + (node->children[i])->depth;  //f = g + h || f = manhattan distance + depth of child node; This is the different part.
				q.push(node->children[i]);
			}

			if (q.size() > maxNodes)
				maxNodes = q.size();
		}
	}

	printf("Could not find a solution. \n");
}