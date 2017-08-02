#ifndef __SRC_TREEANALYSIS
#define __SRC_TREEANALYSIS

#ifdef TREEANALYSIS
#include "Node.h"
#include "assert.h"
#include <algorithm>
#include "Grid.h"
#include "eval.h"
#include "Movegen.h"


void createblueprints(Node * node, coordinate size);
void createspans(Node * node, coordinate size);

void moo();
void foobaz(Node * node);
#endif
#endif