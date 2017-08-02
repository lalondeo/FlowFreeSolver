#include "nodeslist.h"
#include "grid.h"

NodesList::NodesList()
{
	activenodes = new Node*[ACTIVENODES_SIZE];
	deadnodes = new Node*[DEADNODES_SIZE];
	n_activenodes = 0;
	n_deadnodes = 0;
	total = 0;
}
NodesList::~NodesList()
{
	delete[] activenodes;
	delete[] deadnodes;
}

Node * NodesList::popFirstNode()
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
Node * NodesList::getNode(uint64_t index)
{
	assert(index < ACTIVENODES_SIZE);
	assert(index >= 0);
	return activenodes[index];
	
}

uint64_t NodesList::getnactivenodes()
{
	return n_activenodes;
}

void NodesList::print()
{
	for(int i = 0; i < n_activenodes; i++)
	{
		Node * node = activenodes[i];
		if(node == NULL) break;
		printf("%i %p %i %i %i\n", i, node, node->x, node->y, node->color);
	}
	printf("---------\n");
}


void NodesList::insertnode(Node * node)
{
	assert(node != NULL);
	assert(n_activenodes + 1 < ACTIVENODES_SIZE);
	int eval = node->eval;

	n_activenodes++;
	activenodes[n_activenodes - 1] = node;
	uint64_t iNode = n_activenodes - 1;
	
	// Since activenodes is already sorted, only one run of insertion sort is needed to insert the node in the right position
	while(iNode > 0 && (activenodes[iNode - 1] == NULL || activenodes[iNode - 1]->eval < eval))
	{
		Node * temp = activenodes[iNode - 1];
		activenodes[iNode - 1] = node;
		activenodes[iNode] = temp;
		
		iNode--;
	}
	
}

void NodesList::pushdeadnode(Node * node)
{
	assert(n_deadnodes < DEADNODES_SIZE);
	deadnodes[n_deadnodes] = node;
	n_deadnodes++;
}

void NodesList::deletenodes()
{
	printf("Total: %i\n", total);
	printf("D: %i\n", n_deadnodes);
	for(uint64_t i = 0; i < n_activenodes; i++)
	{
		delete activenodes[i];
		activenodes[i] = NULL;
	}
	n_activenodes = 0;
	
	for(uint64_t i = 0; i < n_deadnodes; i++)
	{
		delete deadnodes[i];
		deadnodes[i] = NULL;
	}
	
	n_deadnodes = 0;

}