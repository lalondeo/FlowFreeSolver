#ifndef __SRC_NODE
#define __SRC_NODE
#include "square.h"
#include <cstdlib>
#include <algorithm>

#define EVAL_SOLVED 1000000000
#define EVAL_NORMALMAX 999999999
using namespace std;

class Node
{
public:
	Node(square_color _color, coordinate _x, coordinate _y, Node*, bool _isfirstchild = false, bool iscomplete = false);
	~Node();
	
	square_color getColor();
	
	square_color color;
	coordinate x;
	coordinate y;
	bool isfirstchild;
	
	int eval;
	coordinate_squared depth;
	coordinate_squared pipelength;
	//coordinate_squared distance_to_target;
	
	
	Node * predecessor;
	Node * lastnodeinpipe;
	
	
};
void applynodetogrid(Node* node, square_color** grid); // Applies the node and all its predecessors into the grid
void resetgrid(Node* node, square_color** grid); // The inverse of applynodetogrid
void computetempsources(Node* node, Node ** tempsources, square_color number_of_colors); // Computes the temporary sources for every incomplete pipe of the node and its predecessors
inline Node* * generatetempsources(square_color number_of_colors)
{
	return new Node*[number_of_colors]();
}



#endif