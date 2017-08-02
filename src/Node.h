#ifndef __SRC_NODE
#define __SRC_NODE
#include "square.h"
#include <cstdlib>
#include <algorithm>


//#define TREEANALYSIS
#pragma once


using namespace std;

class Node
{
public:
	Node(square_color _color, coordinate _x, coordinate _y, Node* _predecessor, Node* _lastnodeinpipe, bool _isfirstchild = false);
	~Node();
	
	square_color getColor();
	
	square_color color;
	const coordinate x;
	const coordinate y;
	
	int eval;
	coordinate_squared depth;
	coordinate_squared pipelength;
	
	bool isfirstchild;
	
	Node * predecessor;
	Node * lastnodeinpipe;

	#ifdef TREEANALYSIS
	Node * successor;
	Node * rightsibling;
	
	int positionblueprint;
	
	int span;
	int weightofbranch;
	bool solves;
	#endif
	
	
	
};
void applynodetogrid(Node* node, square_color** grid); // Applies the node and all its predecessors into the grid
void resetgrid(Node* node, square_color** grid); // The inverse of applynodetogrid
void computetempsources(Node* node, Node ** tempsources, square_color number_of_colors); // Computes the temporary sources for every incomplete pipe of the node and its predecessors
inline Node* * generatetempsources(square_color number_of_colors)
{
	return new Node*[number_of_colors]();
}



#endif