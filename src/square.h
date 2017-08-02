#ifndef __SRC_SQUARE
#define __SRC_SQUARE
/*
	Used to represent the color of a square. 0 represents an empty square and colors start by 1 up to (theoretically) infinity.
	In case you want to change the type, please make sure that it can handle negative numbers and number_of_color + 1, as these are used in the 
	move generator.

*/
typedef char square_color;
typedef char coordinate; // Location in cartesian coordinates of the square in the grid
typedef short int coordinate_squared; // For area-related calculations
#include "stdio.h"

inline int coordinatetonumber(coordinate x, coordinate y, coordinate size) 
{
	return (x*size + y);
}


class Square 
{
public:
	Square(coordinate _x, coordinate _y, square_color _color, Square* partialneighborhood [2]);
	~Square();
	
	coordinate getX();
	coordinate getY();
	square_color getColor();
	void setColor(square_color color);
	
	enum ADJACENTSQUARES {TOTHERIGHT, UPPER, TOTHELEFT, LOWER};
	Square* getAdjacentSquare(ADJACENTSQUARES position);
	Square* getAdjacentSquare(int index);
	
	void setSquareToTheRight(Square* squaretotheright);
	void setLowerSquare(Square* lowersquare);

	
	static Square * squareFactory(coordinate _x, coordinate _y, square_color _color, Square* partialneighborhood [2]);
	
protected:
	coordinate x;
	coordinate y;
	square_color color;
	
	Square** neighborhood; // index -> position: Trigonometric convention. (cos(index*pi/2), sin(index*pi/2)). Obviously 4 items.

};

class SquareInPipe: public Square
{
public:
	SquareInPipe(coordinate _x, coordinate _y, square_color _color,  Square* partialneighborhood [2]);
	~SquareInPipe();
	
	SquareInPipe * getSuccessor();
	SquareInPipe * getPredecessor();
	void setSuccessor(SquareInPipe*);
	void setPredecessor(SquareInPipe*);
	
	static Square * squareInPipeFactory(coordinate _x, coordinate _y, square_color _color, Square* partialneighborhood [2]);

private:
	SquareInPipe* predecessor;
	SquareInPipe*  successor;
};



#endif



