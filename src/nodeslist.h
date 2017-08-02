#ifndef __NODESLIST_SRC
#define __NODESLIST_SRC

#include "Node.h"
#include <iostream>
#include <cassert>

#define ACTIVENODES_SIZE 1000000
#define DEADNODES_SIZE 1000000

class NodesList
{
public:
	NodesList();
	~NodesList();
	Node * popFirstNode();
	Node * getNode(uint64_t index);
	uint64_t getnactivenodes();
	void insertnode(Node * node);
	
	void pushdeadnode(Node * node);
	void deletenodes();
	void print();

private:
	Node ** activenodes;
	Node ** deadnodes;
	
	uint64_t n_activenodes;
	uint64_t n_deadnodes;
	
	uint64_t total;
};

#endif