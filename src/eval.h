#ifndef __SRC_EVAL
#define __SRC_EVAL

#include "Node.h"
#include <algorithm>
#include <cmath>

inline coordinate getdistance(coordinate x1, coordinate y1, coordinate x2, coordinate y2) 
{
	return (std::max(abs(y2-y1), abs(x2-x1)));
}

inline coordinate getdistance(Node * n1, Node * n2) 
{
	return (getdistance(n1->x, n1->y, n2->x, n2->y));
}

class NodeEval
{
public:
	NodeEval(square_color** * _analysisgridpointer, coordinate *** _sources, square_color _number_of_colors, coordinate _size);
	
	int evaluateNode(Node * node);


private:
	square_color** * analysisgridpointer;
	coordinate *** sources;
	square_color number_of_colors;
	coordinate size;
	
	coordinate * distances;
	
	
};



#endif