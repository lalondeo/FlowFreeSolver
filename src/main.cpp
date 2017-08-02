#include "main.h"
#include <ctime>
#include <inttypes.h>
#include <stdio.h>
#include "treeanalysis.h"
#include <fstream>
#include <cstdlib>

#define __STDC_FORMAT_MACROS
#include "transpositiontable.h"
int main()
{
	#ifdef LOGGING
	openlogfile();
	#endif
	
	// 5x5: 1---2/--3--/---2-/-4-3-/-1--4
	// 6x6: ------/------/---1--/-213--/453-2-/5-4---
	// 7x7: -------/-1---2-/--2--34/------5/-----67/5413---/-----67
	// 8x8: 1---2---/3----454/1-3--5-6/7----87-/--89----/--9-2--/--------/-------6
	// 9x9: --1------/-2345----/---67----/---------/---28--5-/-------74/--3-----1/------86-/---------
	// 14x14: ----------1--1/--------------/--2345--------/----------67--/------45--8---/------6---9---/--------------/--8A-------7--/--------B-BC--/-3-------D----/-F---F-A--D---/---------9C---/--E----E------/2-------------
	GridInfo * info = readfen("");
	square_color ** foo = generateEmptyGrid(info->size);
	for(int i = 0; i < info->number_of_colors; i++)
		for(int j = 0; j < 2; j++)
			foo[info->sources[i][j][1]][info->sources[i][j][0]] = i + 1;
	
	printGrid(foo, info->size);
	deleteGrid(foo, info->size);
	printf("---\n");

	
	Tree * tree = new Tree(info->size, info->sources, info->number_of_colors);
	clock_t t1 = clock();
	
	tree->solve(1);
	Node * node = tree->getfirstnode();
	//createblueprints(node, 5);
	//createspans(node, 5);
	//printf("%i\n", node->weightofbranch);
	//foobaz(node);
	//moo();


	clock_t t2 = clock();
	delete tree;
	printf("%f sec\n", (double)(t2-t1)/CLOCKS_PER_SEC);
	
	#ifdef LOGGING
	closelogfile();
	#endif
}
