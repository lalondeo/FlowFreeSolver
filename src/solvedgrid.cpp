#include "SolvedGrid.h"

SolvedGrid::SolvedGrid(square_color** _grid, coordinate _size) : Grid(_grid, _size, &SquareInPipe::squareInPipeFactory)
{

	for(square_color color = 1; color <= number_of_colors; color++)
	{
		vector<SquareInPipe*> squares = putSquaresInOrder(getColoredSquares(color));

		applyOrder(squares);

		setSources(color, squares.front(), squares.back()); // The sources are necessarily the first and last squares of the pipe

	}

	
}

vector<SquareInPipe*> SolvedGrid::getColoredSquares(square_color color)
{
	vector<SquareInPipe*> result = vector<SquareInPipe*>();
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
		{
			SquareInPipe * square = (SquareInPipe*)getSquare(i, j);
			if(square->getColor() == color) result.push_back(square);
		}
	return result;
}

UnsolvedGrid * SolvedGrid::generateUnsolvedGrid()
{
	square_color** newgrid = generateEmptyGrid(size);
	for(square_color i = 0; i < number_of_colors; i++)
	{
		Square** sourcesofcolor = sources[i];
		for(int j = 0; j < 2; i++)
			newgrid[sourcesofcolor[j]->getY()][sourcesofcolor[j]->getX()] = sourcesofcolor[j]->getColor();
	}
	
	UnsolvedGrid * result = new UnsolvedGrid(newgrid, size);
	deleteGrid(newgrid, size);
	return result;
}

SquareInPipe* SolvedGrid::findFirstCandidateSquare(vector<SquareInPipe*> squares)
{
	square_color color = squares[0]->getColor();
	SquareInPipe* result = NULL;
	for(int i = 0; i < squares.size(); i++)
	{
		SquareInPipe* square = squares[i];
		int n = 0;
		for(int index = 0; index < 4 && n < 2; index++)
			if(square->getAdjacentSquare(index) == NULL)
				n++;
		
		if(n == 1)
		{
			result = square;
			break;
		}
	}
	
	return result;
}

vector<SquareInPipe*> SolvedGrid::putSquaresInOrder(vector<SquareInPipe*> squares)
{
	vector<SquareInPipe*> result = vector<SquareInPipe*>();
	SquareInPipe * firstCandidateSquare = findFirstCandidateSquare(squares);
	if(firstCandidateSquare == NULL)
	{
		for(int i = 0; i < squares.size(); i++)
		{

			bool success = findOrder(squares[0], &result, squares.size());
			if(success) break;
		}
	}
	
	else
	{
		findOrder(firstCandidateSquare, &result, squares.size());
	}
	
	return result;
}

bool SolvedGrid::findOrder(SquareInPipe* square, vector<SquareInPipe*> * order, int length)
{

	for(int index = 0; index < 4; index++)
	{
		SquareInPipe* adjacentSquare = (SquareInPipe*)square->getAdjacentSquare(index);

		if(adjacentSquare != NULL && adjacentSquare->getColor() == square->getColor() && count(order->begin(), order->end(), adjacentSquare) == 0)
		{
			order->push_back(adjacentSquare);
			if(order->size() == length || findOrder(adjacentSquare, order, length))
				return true;
			
			else 
				order->pop_back(); 
		}
	}
	return false;
}

void SolvedGrid::applyOrder(vector<SquareInPipe*> order)
{
	int length = order.size();
	for(int i = 1; i < length - 1; i++)
	{
		order[i]->setPredecessor(order[i-1]);
		order[i]->setSuccessor(order[i+1]);
	}
	
	order[0]->setSuccessor(order[1]);
	order[length - 1]->setPredecessor(order[length - 2]);
}