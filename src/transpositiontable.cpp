#include "transpositiontable.h"

TranspositionTable::TranspositionTable(uint64_t _numberofpositions, coordinate _size, square_color _number_of_colors) : size(_size), number_of_colors(_number_of_colors), numberofpositions(_numberofpositions)
{
	positionhash = new PositionHash(size, number_of_colors);
	positions = new Position*[numberofpositions]();
	positiongrid = generateEmptyGrid(size);
	positiontempsources = generatetempsources(number_of_colors);
	temphash = 0;
	tempindex = 0;
}

TranspositionTable::~TranspositionTable()
{
	for(uint64_t i = 0; i < numberofpositions; i++)
	{
		Position * position = positions[i];
		if(position != NULL)
			delete positions[i];
	}
	
	delete[] positions;
	
	deleteGrid(positiongrid, size);
	delete[] positiontempsources;
	delete positionhash;
}

bool TranspositionTable::positionwasseenbefore(square_color ** grid, Node* * tempsources)
{
	bool wasseenbefore = false;
	temphash = positionhash->hashPosition(grid, tempsources);
	tempindex = temphash % numberofpositions;
	Position * correspondingposition = positions[tempindex];
	
	if(correspondingposition != NULL &&  correspondingposition->hash == temphash)
	{
		applynodetogrid(correspondingposition->node, positiongrid);
		if(gridsareisometric(grid))
		{
			computetempsources(correspondingposition->node, positiontempsources, number_of_colors);
			wasseenbefore = tempsourcesareidentical(tempsources);
		}

		resetgrid(correspondingposition->node, positiongrid);
	}

	return wasseenbefore;
	
}

void TranspositionTable::inputnode(Node * node)
{
	// To be called immediatly after wasseenbefore was called as this function assumes that the hash of the node was already computed earlier
	
	Position * newposition = new Position(); //positions[tempindex];
	//if(newposition == NULL) newposition = new Position();
	
	newposition->node = node;
	newposition->hash = temphash;
	positions[tempindex] = newposition;
		
}

bool TranspositionTable::gridsareisometric(square_color ** grid)
{
	// Returns true if and only if for all corresponding squares in grid and the position grid, the squares are either both empty or both filled.
	bool isisometric = true;
	for(int i = 0; i < size && isisometric; i++)
		for(int j = 0; j < size && isisometric; j++)
		{
			#ifdef STRONGISOMETRY
			isisometric = (grid[i][j] == positiongrid[i][j]);
			#else
			isisometric = !((grid[i][j] == 0) ^ (positiongrid[i][j] == 0));
			#endif
		}
		
	return isisometric;
}

bool TranspositionTable::tempsourcesareidentical(Node* * tempsources)
{
	bool areidentical = true;
	for(int i = 0; i < number_of_colors && areidentical; i++)
		areidentical = (tempsources[i]->x == positiontempsources[i]->x && tempsources[i]->y == positiontempsources[i]->y);
	
	return areidentical;
}

