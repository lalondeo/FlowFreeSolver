#ifndef __SRC_UNSOLVEDGRID
#define __SRC_UNSOLVEDGRID

#include "grid.h"

class UnsolvedGrid : public Grid
{
public:
	UnsolvedGrid(square_color** grid, coordinate size);
	
};

#endif