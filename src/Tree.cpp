#include "tree.h"

Tree::Tree(coordinate _size, coordinate*** sources, square_color _number_of_colors) : size(_size), number_of_colors(_number_of_colors)
{

	
	uint64_t numberofpositions = size;
	for(int i = 0; i < 7; i++) numberofpositions *= size;
	
	transpositiontable = new TranspositionTable(numberofpositions, size, number_of_colors);
	
	isolvednodes = 0;
	for(int i = 0; i < MAX_NUMBER_OF_SOLVED_NODES; i++)
		solved_nodes[i] = NULL;
	
	
	analysisgrid = generateEmptyGrid(size);
	
	endsources = new coordinate*[number_of_colors];
	Node * firstnode = new Node(1,  sources[0][0][0], sources[0][0][1], NULL, NULL, false);
	endsources[0] = new coordinate[2];
	endsources[0][0] = sources[0][1][0];
	endsources[0][1] = sources[0][1][1];
	analysisgrid[endsources[0][1]][endsources[0][0]] = 1;
	
	for(square_color i = 1; i < number_of_colors; i++)
	{
		coordinate** sourcesofcolor = sources[i];
		firstnode = new Node(i + 1, sourcesofcolor[0][0], sourcesofcolor[0][1], firstnode, NULL, true); // x, y of starting source
		endsources[i] = new coordinate[2];
		// x, y of end source
		endsources[i][0] = sourcesofcolor[1][0];
		endsources[i][1] = sourcesofcolor[1][1];
		
		analysisgrid[endsources[i][1]][endsources[i][0]] = i + 1;
	}
	activenodes.insertnode(firstnode);
	
	tempsources = generatetempsources(number_of_colors);
	
	moves = new coordinate**[number_of_colors];
	for(int i = 0; i < number_of_colors; i++)
	{
		moves[i] = new coordinate*[4];
		for(int j = 0; j < 4; j++) moves[i][j] = new coordinate[2]();
	}
		
	
	newnodes = new Node*[number_of_colors * 4]();
	
	nodeeval = new NodeEval(&analysisgrid, sources, number_of_colors, size);
	
}

Tree::~Tree()
{
	delete transpositiontable;
	delete[] tempsources;
	delete[] newnodes;
	deleteGrid(analysisgrid, size);
	for(int i = 0; i < number_of_colors; i++)
	{
		delete[] endsources[i];
		for(int j = 0; j < 4; j++) delete[] moves[i][j];
		delete[] moves[i];
	}
	delete[] moves;
	activenodes.deletenodes();
}



void Tree::solve(int numberofsolutions)
{
	if(numberofsolutions < 0 || numberofsolutions >= MAX_NUMBER_OF_SOLVED_NODES)
		numberofsolutions = MAX_NUMBER_OF_SOLVED_NODES - 1;
	
	Node * node;
	while(1)
	{
		node = activenodes.popFirstNode();
		if(node == NULL)
			break;
		
		else if(node->eval == EVAL_SOLVED)
		{
			solved_nodes[isolvednodes] = node;
			isolvednodes++;

			if(isolvednodes == numberofsolutions) break;
		}

		expandNode(node);
	}
	
}

bool Tree::generatemoves()
{
	bool isok = true;
	coordinate endsource_x, endsource_y, tempsource_x, tempsource_y;
	char count;
	
	for(square_color i = 0; i < number_of_colors; i++)
		for(char j = 0; j < 4; j++)
			moves[i][j][0] = moves[i][j][1] = -1;
	
	for(square_color i = 0; i < number_of_colors && isok; i++)
	{
		endsource_x = endsources[i][0];
		endsource_y = endsources[i][1];
		
		tempsource_x = tempsources[i]->x;
		tempsource_y = tempsources[i]->y;
		
		if(tempsource_x != endsource_x || tempsource_y != endsource_y)
		{			
			analysisgrid[endsource_y][endsource_x] = 0; // Temporarily
			generateMoves(moves[i], analysisgrid, size, tempsource_x, tempsource_y);
			analysisgrid[endsource_y][endsource_x] = i + 1; 
			
			count = 0;
			for(char j = 0; j < 4; j++)
				if(moves[i][j][0] != -1) count++;
			
			if(count == 0) 
				isok = false;
			
			
			else if(count == 1)
			{
				for(square_color j = 0; j < number_of_colors; j++)
				{
					if(j == i) continue;
					for(char k = 0; k < 4; k++)
						moves[j][k][0] = moves[j][k][1] = -1;
				
				}
				break;
			}
			
			
		}
	}
	
	return isok;
}

void test(square_color ** grid, coordinate** endsources, coordinate size)
{
	for(int i = 0; i < size; i++) for(int j = 0; j < size; j++)
	{
		square_color couleur = grid[i][j];
		if(couleur != 0)
			assert(j == endsources[couleur - 1][0] && i == endsources[couleur - 1][1]);
		
	}
}
	

void Tree::expandNode(Node * node)
{

	applynodetogrid(node, analysisgrid);
	computetempsources(node, tempsources, number_of_colors);
	
	int iNewnodes = 0;
	Node * basenode = node;
	Node * newnode;
	Node * tempsource;
	bool isfirstchild = true;
	for(int i = 0; i < number_of_colors * 4; i++)
		newnodes[i] = NULL;

	
	if(generatemoves())
	{
		
		for(square_color iEndsources = 0; iEndsources < number_of_colors; iEndsources++)
		{
			coordinate x = endsources[iEndsources][0];
			coordinate y = endsources[iEndsources][1];
			if(tempsources[iEndsources]->x != x || tempsources[iEndsources]->y != y )
				analysisgrid[y][x] = 0;
		}
		
		for(square_color i = 0; i < number_of_colors; i++)
		{
		
			coordinate endsourceofcolor_x = endsources[i][0];
			coordinate endsourceofcolor_y = endsources[i][1];
			tempsource = tempsources[i];

			if((endsourceofcolor_x != tempsource->x) || (endsourceofcolor_y != tempsource->y)) // Pipe is not complete, therefore we should expand its last square
			{

				for(int j = 0; j < 4; j++)
				{
					if(moves[i][j][0] == -1) 
						continue;
				
					newnode = new Node(i + 1, moves[i][j][0], moves[i][j][1], basenode, tempsource, isfirstchild, (moves[i][j][0] == endsourceofcolor_x && moves[i][j][1] == endsourceofcolor_y));
					// Aimed at making sure that the move in question wasn't analyzed previously
					analysisgrid[moves[i][j][1]][moves[i][j][0]] = i + 1;
					tempsources[i] = newnode;
					
					if(!transpositiontable->positionwasseenbefore(analysisgrid, tempsources))
					{
						transpositiontable->inputnode(newnode);
						newnodes[iNewnodes] = newnode;
						iNewnodes++;	
						isfirstchild = false;
					}
					else
					{
						newnode->isfirstchild = false;
						delete newnode;
					}
					
					tempsources[i] = tempsource;
					analysisgrid[moves[i][j][1]][moves[i][j][0]] = 0;

				}
				
			}
		}
		
		
		for(int i = 0; i < iNewnodes; i++)
		{
			newnodes[i]->eval = nodeeval->evaluateNode(newnodes[i]);
			activenodes.insertnode(newnodes[i]);
		}
		
	}
	
	
	resetgrid(node, analysisgrid);
	for(square_color iEndsources = 0; iEndsources < number_of_colors; iEndsources++)
		analysisgrid[endsources[iEndsources][1]][endsources[iEndsources][0]] = iEndsources + 1;

}
	


