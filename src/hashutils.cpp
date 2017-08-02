#include "HashUtils.h"

inline int irand()
{
	return rand() ^ (rand() << 16);
}
inline uint64_t lrand()
{
	return ((uint64_t)irand() << 32) ^ ((uint64_t)irand());
}

PositionHash::PositionHash(coordinate _size, square_color _number_of_colors) : size(_size), number_of_colors(_number_of_colors)
{
	positionhashkeys = new uint64_t**[size];
	for(int i = 0; i < size; i++)
	{
		positionhashkeys[i] = new uint64_t*[size];
		for(int j = 0; j < size; j++)
		{
			positionhashkeys[i][j] = new uint64_t[number_of_colors];
			for(int k = 0; k < number_of_colors; k++)
				positionhashkeys[i][j][k] = lrand();
		}
	}

}

PositionHash::~PositionHash()
{

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			delete[] positionhashkeys[i][j];
		delete[] positionhashkeys[i];
	}

	delete[] positionhashkeys;
			
		
}

uint64_t PositionHash::hashPosition(square_color** grid)
{
	uint64_t hash = 0;
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
				hash ^= positionhashkeys[i][j][grid[i][j] - 1];
	
	return hash;
}