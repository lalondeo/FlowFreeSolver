#include "Node.h"

Node::Node(square_color _color, coordinate _x, coordinate _y, Node * _predecessor) : 
			color(_color), x(_x), y(_y), predecessor(_predecessor)
{}