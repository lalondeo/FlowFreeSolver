#include "main.h"
int main()
{
	square_color truc1[9] = {1, 1, 1, 1, 3, 3, 4, 4, 0};
	square_color truc2[9] = {0, 0, 0, 1, 0, 0, 0, 2, 2 };
	square_color** grid = new char*[9];
	grid[0] = &(truc1[0]);
	
	square_color * objet = &(truc1[0]);
	for(int i = 1; i < 9; i++)
		grid[i] = &(truc2[0]);
	
	SolvedGrid foo = SolvedGrid(grid, 9);
	SquareInPipe * unecase = ((SquareInPipe*)foo.getSquare(0, 0));
	while(unecase != NULL)
	{
		cout << (int)unecase->getX() << ", " << (int)unecase->getY() << endl;
		unecase = unecase->getSuccessor();
	}

}