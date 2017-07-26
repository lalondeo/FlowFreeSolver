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
	
	tempsourceshashkeys = new uint64_t**[number_of_colors];
	for(int i = 0; i < number_of_colors; i++)
	{
		tempsourceshashkeys[i] = new uint64_t*[size];
		for(int j = 0; j < size; j++)
		{
			tempsourceshashkeys[i][j] = new uint64_t[size];
			for(int k = 0; k < size; k++)
				tempsourceshashkeys[i][j][k] = lrand();
		}
	}
}

PositionHash::~PositionHash()
{
	for(int i = 0; i < number_of_colors; i++)
	{
		for(int j = 0; j < size; j++)
			delete[] tempsourceshashkeys[i][j];
		
		delete[] tempsourceshashkeys[i];
	}
	for(int i = 0; i < size; i++) delete[] positionhashkeys[i];
	
	delete[] tempsourceshashkeys;
	delete[] positionhashkeys;
			
		
}

uint64_t PositionHash::hashPosition(square_color** grid, Node* * tempsources)
{
	uint64_t hash = 0;
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(grid[i][j] != 0) 
				hash ^= positionhashkeys[i][j];
	
	
	for(int i = 0; i < number_of_colors; i++)
		hash ^= tempsourceshashkeys[tempsources[i]->color - 1][tempsources[i]->y][tempsources[i]->x];
	
	
	return hash;
}