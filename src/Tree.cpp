#include "tree.h"

Tree::Tree(coordinate _size, coordinate*** sources, square_color _number_of_colors) : size(_size), number_of_colors(_number_of_colors)
{
	transpositiontable = new TranspositionTable(1e07, size, number_of_colors);
	
	isolvednodes = 0;
	for(int i = 0; i < MAX_NUMBER_OF_SOLVED_NODES; i++)
		solved_nodes[i] = NULL;
	
	analysisgrid = generateEmptyGrid(size);
	
	endsources = new coordinate*[number_of_colors];
	firstnode = new Node(1,  sources[0][0][0], sources[0][0][1], NULL, NULL);
	
	#ifdef TREEANALYSIS
	firstnode->rightsibling = NULL;
	#endif
	
	endsources[0] = new coordinate[2];
	endsources[0][0] = sources[0][1][0];
	endsources[0][1] = sources[0][1][1];
	//analysisgrid[endsources[0][1]][endsources[0][0]] = 1;

	Node * sourcenode = firstnode;
	for(square_color i = 1; i < number_of_colors; i++)
	{
		coordinate** sourcesofcolor = sources[i];
		sourcenode = new Node(i + 1, sourcesofcolor[0][0], sourcesofcolor[0][1], sourcenode, NULL, true); // x, y of starting source
		
		#ifdef TREEANALYSIS
		sourcenode->predecessor->successor = sourcenode;
		sourcenode->rightsibling = NULL;
		#endif
		
		endsources[i] = new coordinate[2];
		// x, y of end source
		endsources[i][0] = sourcesofcolor[1][0];
		endsources[i][1] = sourcesofcolor[1][1];
	}
	nodeslist.insertnode(sourcenode);
	tempsources = generatetempsources(number_of_colors);
	
	moves = new coordinate**[number_of_colors];
	for(int i = 0; i < number_of_colors; i++)
	{
		moves[i] = new coordinate*[4];
		for(int j = 0; j < 4; j++) moves[i][j] = new coordinate[2]();
	}
		
	
	newnodes = new Node*[number_of_colors * 4]();
	
	nodeeval = new NodeEval(analysisgrid, sources, number_of_colors, size);
	movegen = new MoveGenerator(analysisgrid, size, number_of_colors, tempsources, endsources);
	
}

Tree::~Tree()
{
	delete transpositiontable;
	delete movegen;
	delete nodeeval;
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
	
	#ifndef TREEANALYSIS
	nodeslist.deletenodes();
	#endif
}

Node * Tree::getfirstnode()
{
	return firstnode;
}

void Tree::solve(int numberofsolutions)
{
	if(numberofsolutions < 0 || numberofsolutions >= MAX_NUMBER_OF_SOLVED_NODES)
		numberofsolutions = MAX_NUMBER_OF_SOLVED_NODES - 1;
	
	Node * node;
	while(1)
	{
		node = nodeslist.popFirstNode();
		if(node == NULL)
		{
			printf("Fini\n");
			break;
		}
			
		
		else if(node->eval == EVAL_SOLVED)
		{
			solved_nodes[isolvednodes] = node;
			isolvednodes++;
			if(isolvednodes == numberofsolutions) 
				break;
			
		}

		else
			expandNode(node);
	}
	#ifdef LOGGING
	Node * solvingnode;
	for(int i = 0; i < isolvednodes; i++)
	{
		solvingnode = solved_nodes[i];
		applynodetogrid(solvingnode, analysisgrid);
		printGrid(analysisgrid, size);
		logGrid(analysisgrid, size);	
		resetgrid(solvingnode, analysisgrid);
		
	}
	#endif
	
	#ifdef TREEANALYSIS

	printf("Solutions: %i\n", isolvednodes);
	square_color ** grid = generateEmptyGrid(size);
	Node * goodnode;
	for(int i = 0; i < isolvednodes; i++)
	{
		goodnode = solved_nodes[i];
		while(goodnode != NULL && !goodnode->solves)
		{
			goodnode->solves = true;
			goodnode = goodnode->predecessor;
		}
	}
	deleteGrid(grid, size);
	#endif

	
	
}

bool Tree::generatemoves()
{
	bool isok = true;
	coordinate endsource_x, endsource_y, tempsource_x, tempsource_y;
	char count;
	
	for(square_color i = 0; i < number_of_colors; i++)
		for(char j = 0; j < 4; j++)
			moves[i][j][0] = moves[i][j][1] = -1;
		
		
	for(square_color iEndsources = 0; iEndsources < number_of_colors; iEndsources++)
		analysisgrid[endsources[iEndsources][1]][endsources[iEndsources][0]] = iEndsources + 1;
	
	for(square_color i = 0; i < number_of_colors && isok; i++)
	{
		endsource_x = endsources[i][0];
		endsource_y = endsources[i][1];
		
		tempsource_x = tempsources[i]->x;
		tempsource_y = tempsources[i]->y;
		
		if(tempsource_x != endsource_x || tempsource_y != endsource_y)
		{	
			analysisgrid[endsource_y][endsource_x] = 0; 
			movegen->generateMoves(moves[i], tempsource_x, tempsource_y);
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
	
	for(square_color iEndsources = 0; iEndsources < number_of_colors; iEndsources++)
	{
		coordinate x = endsources[iEndsources][0];
		coordinate y = endsources[iEndsources][1];
		if(tempsources[iEndsources]->x != x || tempsources[iEndsources]->y != y )
			analysisgrid[y][x] = 0;
	}
	static int tot = 0;
	static int b = 0;
	
	isok &= prunebadmoves();

	return isok;
}

bool Tree::prunebadmoves()
{
	// Some checking to prune moves such as transpositions or illegal moves
	bool isok = true;
	char count = 0;
	transpositiontable->resetmovehash();
	coordinate** moveofcolor;
	bool istransposition;
	coordinate x, y, endsource_x, endsource_y, tempsource_x, tempsource_y;
	bool isempty;
	for(int i = 0; i < number_of_colors && isok; i++)
	{
		endsource_x = endsources[i][0];
		endsource_y = endsources[i][1];
		
		tempsource_x = tempsources[i]->x;
		tempsource_y = tempsources[i]->y;
		
		if(tempsource_x != endsource_x || tempsource_y != endsource_y)
		{
			moveofcolor = moves[i];
			isempty = true;
			for(int j = 0; j < 4; j++)
				isempty &= moveofcolor[j][0] == -1;
			
			if(!isempty)
			{
				for(int j = 0; j < 4; j++)
				{

					x = moveofcolor[j][0];
					y = moveofcolor[j][1];
					if(x == -1) 
						continue;
					
					analysisgrid[y][x] = i + 1;
					uint64_t hash = transpositiontable->gethash(analysisgrid);
					if(!transpositiontable->positionwasseenbefore(analysisgrid, tempsources, x, y, i + 1, hash))
						transpositiontable->inputmove(hash, i + 1, x, y);
					
					else
						moveofcolor[j][0] = moveofcolor[j][1] = -1;
					
						
					analysisgrid[y][x] = 0;
						
				}
				
				
				movegen->filterIllegalMoves(moveofcolor, i + 1);
				isempty = true;
				for(int j = 0; j < 4; j++)
					isempty &= moveofcolor[j][0] == -1;
				
				if(isempty) 
				{
					isok = false;
					break;
				}
				
			}
		}
	}
	
	return isok;
}

void Tree::expandNode(Node * node)
{
	applynodetogrid(node, analysisgrid);
	computetempsources(node, tempsources, number_of_colors);
	
	int iNewnodes = 0;
	Node * newnode;
	Node * tempsource;
	
	bool canproceed = generatemoves();
	
	if(!canproceed)
		nodeslist.pushdeadnode(node);
	
	else
	{
		for(square_color i = 0; i < number_of_colors; i++)
		{
			tempsource = tempsources[i];	
			for(int j = 0; j < 4; j++)
			{
					if(moves[i][j][0] == -1) 
						continue;
				
					newnode = new Node(i + 1, moves[i][j][0], moves[i][j][1], node, tempsource, iNewnodes == 0);
					newnodes[iNewnodes] = newnode;
					iNewnodes++;
			}
				
		}
		#ifdef TREEANALYSIS
		/*
			iNewnodes is guaranteed to be >0:
			If all pipes are complete, then:
				1) This node constitutes a solution of the grid, in which case we wouldn't have gotten here in the first place.
				2) There is an isolated empty square somewhere in the grid, which would have been blocked by prunebadmoves, which means that this node couldn't have been created.
			If not all pipes were solved, then:
				1) For some pipe there exists a move, in which case iNewnodes>0, as desired.
				2) There are no moves for any pipe (if the pipe is blocked, for example), in which case isok would have been false, in which case we wouldn't have gotten here.
			
			Therefore, if we have reached this far, iNewnodes has to be non-zero, as every other scenario leads to a contradiction.
			
		*/
		node->successor = newnodes[0]; 
		#endif
		
		Node * newnode;
		for(int i = 0; i < iNewnodes; i++)
		{
			newnode = newnodes[i];
			newnode->eval = nodeeval->evaluateNode(newnode);
			nodeslist.insertnode(newnode);
			
			#ifdef TREEANALYSIS
			newnode->rightsibling = (i != iNewnodes - 1 ? newnodes[i+1] : NULL);
			#endif
			
			transpositiontable->inputnode(newnode, newnode->color, newnode->x, newnode->y);
		}
		
	}

	resetgrid(node, analysisgrid);

}
	
