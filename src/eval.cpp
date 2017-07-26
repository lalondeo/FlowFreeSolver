#include "eval.h"

NodeEval::NodeEval(square_color** * _analysisgridpointer, coordinate *** _sources, square_color _number_of_colors, coordinate _size) : 
	analysisgridpointer(_analysisgridpointer), sources(_sources), number_of_colors(_number_of_colors), size(_size)
{}

int NodeEval::evaluateNode(Node * node)
{
	int evaluation = 0;
	if(node->lastnodeinpipe != NULL)
	{
		square_color node_color = node->color;
		coordinate x = node->x;
		coordinate y = node->y;
		
	}
	
	
}