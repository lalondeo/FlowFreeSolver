#ifndef __SRC_HASHUTILS
#define __SRC_HASHUTILS

#include "Square.h"
#include "Node.h"
#include "Grid.h"
#include <inttypes.h>
#include <cstdlib>
#include <cmath>

class PositionHash
{
public:
	PositionHash(coordinate _size, square_color _number_of_colors);
	~PositionHash();
	
	uint64_t hashPosition(square_color** grid);
	
private:
	coordinate size;
	square_color number_of_colors;
	
	uint64_t *** positionhashkeys; // size x size x number_of_colors
	
};

#endif