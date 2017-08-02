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


#define STRONGISOMETRY

struct Position
{
	uint64_t hash;
	Node * node;
};

struct MoveHash
{
	uint64_t hash;
	square_color color;
	coordinate x;
	coordinate y;
};

class TranspositionTable
{
public:
	TranspositionTable(uint64_t _numberofpositions, coordinate _size, square_color _number_of_colors);
	~TranspositionTable();
	
	bool positionwasseenbefore(square_color ** grid, Node* * tempsources, coordinate x, coordinate y, square_color color, uint64_t hash = 0);
	void inputmove(uint64_t hash, square_color color, coordinate x, coordinate y);
	
	void inputnode(Node * node, uint64_t hash);
	void inputnode(Node * node, square_color color, coordinate x, coordinate y);
	void resetmovehash();
	uint64_t gethash(square_color ** grid);
	
private:
	Position* * positions;
	
	MoveHash* * movehashes;
	int iMovehashes;
	
	const coordinate size;
	const uint64_t numberofpositions;
	const square_color number_of_colors;
	PositionHash * positionhash;
	
	square_color ** positiongrid;
	Node* * positiontempsources;
	
	bool gridsareisometric(square_color ** grid);
	bool tempsourcesareidentical(Node* *, coordinate x, coordinate y, square_color color);
	
	
	
	
};

#endif