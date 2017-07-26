#include "Node.h"
#include <assert.h>

Node::Node(square_color _color, coordinate _x, coordinate _y, Node * _predecessor, bool _isfirstchild, bool iscomplete) : 
			color(_color), x(_x), y(_y), predecessor(_predecessor), isfirstchild(_isfirstchild)
{
	assert(color > 0);
	eval = 0;
	lastnodeinpipe = predecessor;
	while(lastnodeinpipe != NULL && lastnodeinpipe->color!= color)
		lastnodeinpipe = lastnodeinpipe->predecessor;
	
	pipelength = ((lastnodeinpipe != NULL) ? lastnodeinpipe->pipelength + 1 : 0);
	depth = ((predecessor != NULL) ? predecessor->depth + 1 : 0);
	if(iscomplete) eval = EVAL_SOLVED;
	
	else
	{
		if(lastnodeinpipe != NULL && lastnodeinpipe->lastnodeinpipe != NULL)
		{
			eval = lastnodeinpipe->eval;
			if(abs(x - lastnodeinpipe->lastnodeinpipe->x) == 2 || abs(y - lastnodeinpipe->lastnodeinpipe->y) == 2)
				eval += 1;
			
			eval = min(EVAL_NORMALMAX, eval); 
		}
		
	}
		
}

Node::~Node()
{
	if(isfirstchild)
		delete predecessor;
}


void computetempsources(Node * node, Node* * tempsources, square_color number_of_colors)
{	

	for(square_color i = 0; i < number_of_colors; i++)
		tempsources[i] = NULL;
	
	square_color n = 0;
	while(node != NULL && n < number_of_colors)
	{
		square_color color = node->color;
		if(tempsources[color - 1] == NULL)
		{ 
			tempsources[color - 1] = node; 
			n++; 
		}
		node = node->predecessor;
	}
}

void applynodetogrid(Node * node, square_color** grid)
{
	//printf("---------\n");
	while(node != NULL)
	{
		//printf("%p\n", node);
		grid[node->y][node->x] = node->color;
		node = node->predecessor;
	}
}

void resetgrid(Node * node, square_color** grid)
{
	while(node != NULL)
	{
		grid[node->y][node->x] = 0;
		node = node->predecessor;
	}
}

