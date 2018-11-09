#ifndef _MySearches
#define _MySearches

#include <cstdio>
#include <vector>
#include <deque>
#include <unordered_map>
#include <queue>
#include <string>
#include <ctime>
#include "board.h"

using namespace std;

class MySearches {
public:
	struct Node {
		Node(int deep, Board board, int zIndex, Node *myParent = NULL) {
			myBoard = board;
			depth = deep;
			parent = myParent;
			zeroIndex = zIndex;
		};
		int depth;
		vector<Node *> children;
		Node *parent;
		Board myBoard;
		int zeroIndex;
		int manhattanDistance;
		int f;
	};

	struct comp {
		bool operator()(Node *a, Node *b) {
			return a->f > b->f;
		}
	};

	bool repeat(string board);
	void printPath();
	void printReport(int depth, double time, int queNodes);

	void BFS(Board board);
	void DFS(Board board);
	void AManSearch(Board board);
	void ASearch(Board board);

	void clearRepeats();

	void successors(Node *parent);


private:
	unordered_map<string, Node *> repeatTracker;
	Node *answerNode;

	clock_t start;
	clock_t finish;
	unsigned int maxNodes;
	double measuredTime;
};

#endif


