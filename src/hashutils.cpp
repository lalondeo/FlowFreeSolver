#include "HashUtils.h"

inline uint64_t lrand()
{
	return ((uint64_t)rand() << 32) ^ (rand());
}

PositionHash::PositionHash(coordinate _size, square_color _number_of_colors) : size(_size), number_of_colors(_number_of_colors)
{
	positionhashkeys = new uint64_t*[size];
	for(int i = 0; i < size; i++)
	{
		positionhashkeys[i] = new uint64_t[size];
		for(int j = 0; j < size; j++)
			positionhashkeys[i][j] = lrand();
	}

}

PositionHash::~PositionHash()
{

	for(int i = 0; i < size; i++) delete[] positionhashkeys[i];
	

	delete[] positionhashkeys;
			
		
}

uint64_t PositionHash::hashPosition(square_color** grid, Node* * tempsources)
{
	uint64_t hash = 0;
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(grid[i][j] != 0) 
				hash ^= positionhashkeys[i][j];
	
	
	
	return hash;
}