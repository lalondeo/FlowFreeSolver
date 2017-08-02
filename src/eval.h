#ifndef __SRC_EVAL
#define __SRC_EVAL

#include "Node.h"
#include <algorithm>
#include <cmath>

using namespace std;
#define EVAL_SOLVED 1000000000
#define EVAL_NORMALMAX 999999999

inline coordinate getdistance(coordinate x1, coordinate y1, coordinate x2, coordinate y2) 
{
	// When dealing with discrete coordinates, the distance between two points is the max between |dx| and |dy|
	return (max(abs(y2-y1), abs(x2-x1)));
}

inline coordinate getdistance(Node * n1, Node * n2) 
{
	return (getdistance(n1->x, n1->y, n2->x, n2->y));
}

class NodeEval
{
public:
	NodeEval(square_color** _analysisgridpointer, coordinate *** _sources, square_color _number_of_colors, coordinate _size);
	
	int evaluateNode(Node * node);

	static void changeX(int newx);
private:
	square_color** analysisgridpointer;
	coordinate *** sources;
	square_color number_of_colors;
	coordinate size;
	
	static int x;
	coordinate * distances;
	
	
};



#endif