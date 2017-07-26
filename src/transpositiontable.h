#ifndef __SRC_TRANSPOSITIONTABLE
#define __SRC_TRANSPOSITIONTABLE
#include "HashUtils.h"
#include "Node.h"
#include "Grid.h"
#include <iostream>
#include <cassert>
#define __STDC_FORMAT_MACROS
/* Zobrist hashing and transposition tables (used primarily in chess engines)
 Thanks to my bff kz04px OuO and the code he wrote for Monochrome at https://github.com/CPirc/Monochrome/blob/master/tt.cpp
*/

struct Position
{
	uint64_t hash;
	Node * node;
};

class TranspositionTable
{
public:
	TranspositionTable(uint64_t _numberofpositions, coordinate _size, square_color _number_of_colors);
	~TranspositionTable();
	
	bool positionwasseenbefore(square_color ** grid, Node* * tempsources);
	void inputnode(Node * node);
	uint64_t gettempindex();
	void deleteindex(uint64_t index);
	
//private:
	Position* * positions;
	const coordinate size;
	const uint64_t numberofpositions;
	const square_color number_of_colors;
	PositionHash * positionhash;
	
	uint64_t temphash;
	uint64_t tempindex;
	
	square_color ** positiongrid;
	Node* * positiontempsources;
	
	bool gridsareisometric(square_color ** grid);
	bool tempsourcesareidentical(Node* * );
	
	
	
	
};

#endif