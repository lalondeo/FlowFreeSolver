#ifndef __SRC_TREE
#define __SRC_TREE

#include "Node.h"
#include "activenodeslist.h"
#include "movegen.h"
#include <iostream>
#include "stdio.h"
#include "SolvedGrid.h"
#include "math.h"
#include <algorithm>
#include "transpositiontable.h"
#include <cassert>

#define MAX_NUMBER_OF_SOLVED_NODES 10

class Tree
{
public:
	Tree(coordinate size, coordinate*** sources, square_color _number_of_colors);
	~Tree();
	
	void solve(int numberofsolutions);

private:
	ActiveNodesList activenodes;
	TranspositionTable * transpositiontable;
	square_color ** analysisgrid;

	coordinate size;
	square_color number_of_colors;
	coordinate** endsources;
	
	coordinate*** moves; // 4 x 2.
	Node* * newnodes;
	
	Node* * tempsources;
	
	void expandNode(Node * node);
	bool generatemoves();
	
	Node * solved_nodes[MAX_NUMBER_OF_SOLVED_NODES];
	int isolvednodes;
	
	
	
	

	
	
	
};



#endif