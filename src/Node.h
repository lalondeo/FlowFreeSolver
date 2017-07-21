#ifndef __SRC_NODE
#define __SRC_NODE
#include "square.h"
class Node
{
public:
	Node(square_color, x, y, Node*);

private:
	square_color color;
	coordinate x;
	coordinate y;
	
	Node * predecessor;
	
};



#endif