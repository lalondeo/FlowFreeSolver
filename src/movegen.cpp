#include "movegen.h"

void generateMoves(coordinate** moves, square_color** grid, coordinate size, coordinate x, coordinate y)
{
	// To be massively improved, of course
	bool cond0 = (x != size - 1 && grid[y][x+1] == 0);
	bool cond1 = (x != 0        && grid[y][x-1] == 0);
	bool cond2 = (y != size - 1 && grid[y+1][x] == 0);
	bool cond3 = (y != 0        && grid[y-1][x] == 0);
	
	moves[0][0] = cond0 ? x + 1 : -1;
	moves[0][1] = cond0 ? y     : -1;

	moves[1][0] = cond1 ? x - 1 : -1;
	moves[1][1] = cond1 ? y     : -1;

	moves[2][0] = cond2 ? x     : -1;
	moves[2][1] = cond2 ? y + 1 : -1;

	moves[3][0] = cond3 ? x     : -1;
	moves[3][1] = cond3 ? y - 1 : -1;
	


}
