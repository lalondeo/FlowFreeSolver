#ifdef TREEANALYSIS
#include "treeanalysis.h"


inline bool isvalid(coordinate x, coordinate y, coordinate size)
{
	return std::min(x, y) >= 0 && std::max(x, y) < size;
}

void _createblueprints(Node * node, coordinate size, bool haspredecessor = false)
{
	if(!haspredecessor)
		node->positionblueprint = 0;
	else
		node->positionblueprint = node->predecessor->positionblueprint;
	
	int shiftval = 1 << coordinatetonumber(node->x, node->y, size);

	node->positionblueprint += shiftval;
	
	Node * sibling = node->successor;
	while(sibling != NULL)
	{
		_createblueprints(sibling, size, true);
		sibling = sibling->rightsibling;
	}
}

void createblueprints(Node * node, coordinate size)
{
	assert(size * size <= sizeof(node->positionblueprint) * 8);
	_createblueprints(node, size);
	
}




void createspans(Node * node, coordinate size)
{
	node->weightofbranch = 1;
	node->span = node->positionblueprint;
	
	if(node->successor != NULL)
	{
		Node * sibling = node->successor;
		while(sibling != NULL)
		{
			createspans(sibling, size);
			node->span = sibling->span | node->span;
			node->weightofbranch += sibling->weightofbranch;
			
			sibling = sibling->rightsibling;
		}
		
	}

}

int foo[37] = {};
void foobaz(Node * node)
{
	foo[node->depth]++;
	Node * child = node->successor;
	while(child != NULL)
	{
		foobaz(child);
		child = child->rightsibling;
	}
}

void moo()
{
	for(int i = 0; i < 37; i++)
		printf("- %i: %i\n", i, foo[i]);
}
#endif