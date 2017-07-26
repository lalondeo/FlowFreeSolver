#ifndef __SRC_SQUARE
#define __SRC_SQUARE
typedef char square_color; // 0 => Empty square, 1 => First color, ...
typedef char coordinate; // Location in cartesian coordinates of the square in the grid
typedef short int coordinate_squared; // For area-related calculations
#include "stdio.h"

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



