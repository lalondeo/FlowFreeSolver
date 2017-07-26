#include "activenodeslist.h"

ActiveNodesList::ActiveNodesList()
{
	n_activenodes = 0;
}

Node * ActiveNodesList::popFirstNode()
{
	Node * result = activenodes[0];
	if(result != NULL)
	{
		activenodes[0] = NULL;
		n_activenodes--;
		
		for(int i = 0; i < n_activenodes; i++)
		{
			Node * temp = activenodes[i];
			activenodes[i] = activenodes[i+1];
			activenodes[i+1] = temp;
		}
	}
	return result;
}
Node * ActiveNodesList::getNode(uint64_t index)
{
	assert(index < ACTIVENODES_SIZE);
	assert(index >= 0);
	return activenodes[index];
	
}

uint64_t ActiveNodesList::getnactivenodes()
{
	return n_activenodes;
}

void ActiveNodesList::print()
{
	for(int i = 0; i < n_activenodes; i++)
	{
		Node * node = activenodes[i];
		if(node == NULL) break;
		printf("%i %p %i %i %i\n", i, node, node->x, node->y, node->color);
	}
	printf("---------\n");
}


void ActiveNodesList::insertnode(Node * node)
{
	assert(node != NULL);
	assert(n_activenodes + 1 < ACTIVENODES_SIZE);
	int eval = node->eval;

	n_activenodes++;
	activenodes[n_activenodes - 1] = node;
	uint64_t iNode = n_activenodes - 1;
	while(iNode > 0 && (activenodes[iNode - 1] == NULL || activenodes[iNode - 1]->eval < eval))
	{
		Node * temp = activenodes[iNode - 1];
		activenodes[iNode - 1] = node;
		activenodes[iNode] = temp;
		
		iNode--;
	}
	
}

void ActiveNodesList::deletenodes()
{
	for(int i = 0; i < n_activenodes; i++)
	{
		delete activenodes[n_activenodes];
		activenodes[n_activenodes] = NULL;
	}
	n_activenodes = 0;

}