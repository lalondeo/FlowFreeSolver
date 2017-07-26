#include "main.h"
#include <ctime>
#include <inttypes.h>
#include <stdio.h>

#define __STDC_FORMAT_MACROS
#include "transpositiontable.h"
int main()
{
	coordinate*** sources = new coordinate**[2];
	for(int i = 0; i < 2; i++)
	{
		sources[i] = new coordinate*[2];
		for(int j = 0; j < 2; j++)
			sources[i][j] = new coordinate[2];
	}
	sources[0][0][0] = 0;
	sources[0][0][1] = 0;
	sources[0][1][0] = 0;
	sources[0][1][1] = 4;
	sources[1][0][0] = 1;
	sources[1][0][1] = 0;
	sources[1][1][0] = 4;
	sources[1][1][1] = 4;

	


	/*
	TranspositionTable foo = TranspositionTable(1e08, 7, 2);
	Node * foobar = new Node(1, 0, 0, new Node(2, 4, 3, NULL, false, false), false, false);
	Node * foobaz = new Node(2, 3, 3, new Node(1, 0, 0, NULL, false, false), false, false);
	square_color ** grid = generateEmptyGrid(7);
	Node* * tempsources = generatetempsources(2);
	applynodetogrid(foobar, grid);
	computetempsources(foobar, tempsources, 2);
	foo.inputnode(foobar, grid, tempsources);
	resetgrid(foobar, grid);
	
	applynodetogrid(foobaz, grid);
	computetempsources(foobaz, tempsources, 2);
	std::cout << foo.inputnode(foobaz, grid, tempsources) << std::endl;
	resetgrid(foobaz, grid);
	*/
	clock_t t1 = clock();
	Tree foobar = Tree(5, sources, 2);

	

	foobar.solve(1);
	
	clock_t t2 = clock();
	printf("Temps: %d\n", (t2-t1)/CLOCKS_PER_SEC);




}