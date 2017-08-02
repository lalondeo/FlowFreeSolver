#ifndef __SRC_TREE
#define __SRC_TREE

#include "Node.h"
#include "nodeslist.h"
#include "movegen.h"
#include "stdio.h"
#include "SolvedGrid.h"
#include "math.h"
#include <algorithm>
#include "transpositiontable.h"
#include <cassert>
#include "eval.h"

#define MAX_NUMBER_OF_SOLVED_NODES 100

class Tree
{
public:
	Tree(coordinate size, coordinate*** sources, square_color _number_of_colors);
	~Tree();
	
	void solve(int numberofsolutions);
	Node * getfirstnode();

private:
	NodesList nodeslist;
	TranspositionTable * transpositiontable;
	square_color ** analysisgrid;
	Node * firstnode;

	coordinate size;
	square_color number_of_colors;
	coordinate ** endsources;
	
	coordinate*** moves; // 4 x 2.
	Node* * newnodes;
	
	Node* * tempsources;
	void expandNode(Node * node);
	bool generatemoves();
	bool prunebadmoves();
	
	bool issamepos(coordinate * pos, Node * node);
	bool removeoverlappingmoves();
	
	Node * solved_nodes[MAX_NUMBER_OF_SOLVED_NODES];
	int isolvednodes;
	
	NodeEval * nodeeval;
	MoveGenerator * movegen;
	
	
	
	

	
	
	
};



#endif