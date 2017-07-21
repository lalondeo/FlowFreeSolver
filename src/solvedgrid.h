#ifndef __SRC_SOLVEDGRID
#define __SRC_SOLVEDGRID

#include "grid.h"
#include "unsolvedgrid.h"
#include <vector>
#include <algorithm>

class SolvedGrid : public Grid
{
public:
	SolvedGrid(square_color** _grid, coordinate _size);
	
	UnsolvedGrid * generateUnsolvedGrid();
	
private:
	vector<SquareInPipe*> getColoredSquares(square_color color);
	SquareInPipe* findFirstCandidateSquare(vector<SquareInPipe*> squares);
	
	vector<SquareInPipe*> putSquaresInOrder(vector<SquareInPipe*> squares);
	bool findOrder(SquareInPipe* square, vector<SquareInPipe*> * order, int length);
	
	void applyOrder(vector<SquareInPipe*> squares);
};

#endif