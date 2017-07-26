#ifndef __ACTIVENODESLIST_SRC
#define __ACTIVENODESLIST_SRC

#include "Node.h"
#include <iostream>
#include <cassert>

#define ACTIVENODES_SIZE 100000

class ActiveNodesList
{
public:
	ActiveNodesList();
	
	Node * popFirstNode();
	Node * getNode(uint64_t index);
	uint64_t getnactivenodes();
	void insertnode(Node * node);
	void deletenodes();
	void print();

private:
	Node * activenodes[ACTIVENODES_SIZE];
	uint64_t n_activenodes;
};

#endif