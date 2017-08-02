#ifndef __SRC_MOVEGEN
#define __SRC_MOVEGEN

#include "square.h"
#include "Node.h"
#include "Grid.h"

#define CURRENTZEROPATH -1
#define PREVIOUSZEROPATH -2

#define MAXDEPTH 10
using namespace std;

class MoveGenerator
{
public:
	MoveGenerator(square_color** _analysisgridpointer, coordinate _size, square_color _number_of_colors, Node* * _tempsources, coordinate ** _endsources);
	void generateMoves(coordinate** moves, coordinate x, coordinate y);
	void filterIllegalMoves(coordinate** moves, square_color color);
	bool testEndsources(coordinate x, coordinate y, square_color color);
	
private:
	coordinate size;
	square_color number_of_colors;
	square_color** analysisgridpointer;

	
	void generateLegalMoves(coordinate** moves, coordinate x, coordinate y);
	
	void updategrid();
	void setupgrid(square_color color);
	void resetgrid();
	
	bool testZeros(coordinate x, coordinate y, square_color color, coordinate d = 3);
	bool testZero(coordinate x, coordinate y, coordinate_squared depth = 0);

	
	const square_color tempsourceval;
	Node* * tempsources;
	coordinate ** endsources;
	
	coordinate** * zeromoves;

};


#endif