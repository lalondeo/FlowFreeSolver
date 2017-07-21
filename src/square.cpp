#include "square.h"

Square::Square(coordinate _x, coordinate _y, square_color _color, Square* partialneighborhood[2])
{
	x = _x;
	y = _y;
	color = _color;
	neighborhood = new Square*[4];
	neighborhood[1] = partialneighborhood[0]; // upper
	neighborhood[2] = partialneighborhood[1]; // to the left
	neighborhood[0] = NULL;
	neighborhood[3] = NULL;
	
	if(partialneighborhood[0] != NULL) partialneighborhood[0]->setLowerSquare(this);
	if(partialneighborhood[1] != NULL) partialneighborhood[1]->setSquareToTheRight(this);
	delete[] partialneighborhood;
}

Square::~Square()
{
	delete[] neighborhood;
}
coordinate Square::getX()
{
	return x;
}
coordinate Square::getY()
{
	return y;
}
square_color Square::getColor()
{
	return color;
}

void Square::setColor(square_color _color)
{
	color = _color;
}

void Square::setSquareToTheRight(Square* squaretotheright)
{
	neighborhood[0] = squaretotheright;
}

void Square::setLowerSquare(Square* lowersquare)
{
	neighborhood[3] = lowersquare;
}


Square* Square::getAdjacentSquare(int index)
{
	return neighborhood[index];
}

Square* Square::getAdjacentSquare(ADJACENTSQUARES position)
{
	return neighborhood[position];
}

Square * Square::squareFactory(coordinate _x, coordinate _y, square_color _color, Square* partialneighborhood [2])
{
	return new Square(_x, _y, _color, partialneighborhood);
}


SquareInPipe::SquareInPipe(coordinate _x, coordinate _y, square_color _color, Square* partialneighborhood[2]) : Square(_x, _y, _color, partialneighborhood)
{
	predecessor = successor = NULL; // for now
}

Square * SquareInPipe::squareInPipeFactory(coordinate _x, coordinate _y, square_color _color, Square* partialneighborhood [2])
{
	return new SquareInPipe(_x, _y, _color, partialneighborhood);
}

SquareInPipe* SquareInPipe::getPredecessor()
{
	return predecessor;
}

SquareInPipe* SquareInPipe::getSuccessor()
{
	return successor;
}

void SquareInPipe::setPredecessor(SquareInPipe* _predecessor)
{
	predecessor = _predecessor;
}
void SquareInPipe::setSuccessor(SquareInPipe* _successor)
{
	successor = _successor;
}