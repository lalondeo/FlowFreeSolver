#include "Node.h"
#include <assert.h>

int blah = 0;
int bluh = 0;

Node::Node(square_color _color, coordinate _x, coordinate _y, Node * _predecessor, Node * _lastnodeinpipe, bool _isfirstchild) : 
			color(_color), x(_x), y(_y), predecessor(_predecessor), lastnodeinpipe(_lastnodeinpipe), isfirstchild(_isfirstchild)
{
	assert(color > 0);
	eval = 0;
	pipelength = ((lastnodeinpipe != NULL) ? lastnodeinpipe->pipelength + 1 : 0);
	depth = ((predecessor != NULL) ? predecessor->depth + 1 : 0);

	#ifdef TREEANALYSIS
	span = 0;
	weightofbranch = 0;
	successor = NULL;
	rightsibling = NULL;
	solves = false;
	#endif
}

Node::~Node()
{
	/* if TREEANALYSIS is defined, the tree will not delete all nodes, but rather return the head node. The nodes will therefore be deleted
		by deleting the head node. */
	#ifdef TREEANALYSIS
	Node * child = successor;
	Node * temp;
	while(child != NULL)
	{
		temp = child->rightsibling;
		delete child;
		child = temp;
	}
	
	#else
	/* If not, the tree will delete every final node. */
	if(isfirstchild)
		delete predecessor;	
	#endif
}


void computetempsources(Node * node, Node* * tempsources, square_color number_of_colors)
{	
	for(int i = 0; i < number_of_colors; i++)
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

