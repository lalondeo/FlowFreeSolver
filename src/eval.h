#ifndef __SRC_EVAL
#define __SRC_EVAL

#include "Node.h"

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
	
	
};

#endif