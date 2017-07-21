#include "unsolvedgrid.h"

UnsolvedGrid::UnsolvedGrid(square_color** _grid, coordinate size) : Grid(_grid, size)
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
		{
			Square * square = grid[i][j];
			square_color color = square->getColor();
			if(color != 0)
			{
				if(sources[color - 1][0] != NULL)
					sources[color - 1][1] = square;
				
				else
					sources[color - 1][0] = square;
				
			}
		}
	
}
