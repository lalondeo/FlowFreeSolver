#include "transpositiontable.h"

TranspositionTable::TranspositionTable(uint64_t _numberofpositions, coordinate _size, square_color _number_of_colors) : size(_size), number_of_colors(_number_of_colors), numberofpositions(_numberofpositions)
{
	positionhash = new PositionHash(size, number_of_colors);
	positions = new Position*[numberofpositions]();
	
	movehashes = new MoveHash*[number_of_colors * 4];
	for(int i = 0; i < number_of_colors*4; i++)
	{
		movehashes[i] = new MoveHash();
		movehashes[i]->hash = 0;
		movehashes[i]->x = 0;
		movehashes[i]->y = 0;
		movehashes[i]->color = 0;
	}
	
	iMovehashes = 0;
	positiongrid = generateEmptyGrid(size);
	positiontempsources = generatetempsources(number_of_colors);
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

uint64_t TranspositionTable::gethash(square_color ** grid)
{
	return positionhash->hashPosition(grid);
}

bool TranspositionTable::positionwasseenbefore(square_color ** grid, Node* * tempsources, coordinate x, coordinate y, square_color color, uint64_t hash)
{
	if(hash == 0) 
		hash = gethash(grid);
	
	bool wasseenbefore = false;
	uint64_t index = hash % numberofpositions;
	Position * correspondingposition = positions[index];
	
	if(correspondingposition != NULL &&  correspondingposition->hash == hash)
	{
		applynodetogrid(correspondingposition->node, positiongrid);
		if(gridsareisometric(grid))
		{
			computetempsources(correspondingposition->node, positiontempsources, number_of_colors);
			wasseenbefore = tempsourcesareidentical(tempsources, x, y, color);
		}

		resetgrid(correspondingposition->node, positiongrid);
	}

	return wasseenbefore;
	
}

void TranspositionTable::inputmove(uint64_t hash, square_color color, coordinate x, coordinate y)
{
	MoveHash * movehash = movehashes[iMovehashes];
	iMovehashes++;
	movehash->hash = hash;
	movehash->color = color;
	movehash->x = x;
	movehash->y = y;
}

void TranspositionTable::inputnode(Node * node, uint64_t hash)
{	
	uint64_t index = hash % numberofpositions;
	Position * newposition = positions[index];
	if(newposition == NULL) 
	{
		newposition = new Position();
		positions[index] = newposition;
	}
	
	newposition->node = node;
	newposition->hash = hash; 
}

void TranspositionTable::inputnode(Node * node, square_color color, coordinate x, coordinate y)
{
	MoveHash * movehash;
	bool success = false;
	for(int i = 0; i < iMovehashes; i++)
	{
		movehash = movehashes[i];
		if(movehash->color == color && movehash->x == x && movehash->y == y)
		{
			success = true;
			break;
		}
	}
	if(!success) printf("%i %i %i %i\n", iMovehashes, color, x, y);
	assert(success); // If this assertion failed, the node's corresponding hash could not be found
	inputnode(node, movehash->hash);
}

void TranspositionTable::resetmovehash()
{
	iMovehashes = 0;
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

bool TranspositionTable::tempsourcesareidentical(Node* * tempsources, coordinate x, coordinate y, square_color color)
{
	bool areidentical = true;
	
	for(int i = 0; i < color - 1 && areidentical; i++)
		areidentical = (tempsources[i]->x == positiontempsources[i]->x && tempsources[i]->y == positiontempsources[i]->y);
	
	areidentical &= positiontempsources[color - 1]->x == x && positiontempsources[color - 1]->y == y;
	
	for(int i = color; i < number_of_colors && areidentical; i++)
		areidentical = (tempsources[i]->x == positiontempsources[i]->x && tempsources[i]->y == positiontempsources[i]->y);
	
	
	
	return areidentical;
}

