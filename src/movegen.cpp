#include "movegen.h"

inline bool isvalid(coordinate x, coordinate y, coordinate size)
{
	return min(x, y) >= 0 && max(x, y) < size;
}
MoveGenerator::MoveGenerator(square_color** _analysisgridpointer, coordinate _size, square_color _number_of_colors, Node* * _tempsources, coordinate ** _endsources) : 
 analysisgridpointer(_analysisgridpointer), size(_size), number_of_colors(_number_of_colors), tempsourceval(_number_of_colors + 1), tempsources(_tempsources), endsources(_endsources)
{

}

void MoveGenerator::generateMoves(coordinate** moves, coordinate x, coordinate y)
{
	generateLegalMoves(moves, x, y);
}

void MoveGenerator::filterIllegalMoves(coordinate** moves, square_color color)
{
	bool isok;
	for(int i = 0; i < 4; i++)
	{
		coordinate * move = moves[i];
		if(move[0] == -1) continue;
		
		isok = true;
		for(int j = 0; j < 2 && isok; j++)
		{
			switch(j)
			{
				case 0:
					isok &= testZeros(move[0], move[1], color); 
					break;
				case 1:
					isok &= testEndsources(move[0], move[1], color);
					break;
			}
		}
		if(!isok)
			move[0] = move[1] = -1;
	}
}

void MoveGenerator::generateLegalMoves(coordinate** moves, coordinate x, coordinate y)
{
	bool cond0 = (x != size - 1 && analysisgridpointer[y][x+1] <= 0);
	bool cond1 = (x != 0        && analysisgridpointer[y][x-1] <= 0);
	bool cond2 = (y != size - 1 && analysisgridpointer[y+1][x] <= 0);
	bool cond3 = (y != 0        && analysisgridpointer[y-1][x] <= 0);
	
	moves[0][0] = cond0 ? x + 1 : -1;
	moves[0][1] = cond0 ? y     : -1;

	moves[1][0] = cond1 ? x - 1 : -1;
	moves[1][1] = cond1 ? y     : -1;

	moves[2][0] = cond2 ? x     : -1;
	moves[2][1] = cond2 ? y + 1 : -1;

	moves[3][0] = cond3 ? x     : -1;
	moves[3][1] = cond3 ? y - 1 : -1;
	

}


void MoveGenerator::setupgrid(square_color color)
{
	Node * tempsource;
	for(int i = 0; i < number_of_colors; i++)
	{
		tempsource = tempsources[i];
		if((i + 1 != color) && (endsources[i][0] != tempsource->x || endsources[i][1] != tempsource->y))
			analysisgridpointer[tempsource->y][tempsource->x] = tempsourceval;
		
	}
}
void MoveGenerator::updategrid()
{
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(analysisgridpointer[i][j] == CURRENTZEROPATH)
				analysisgridpointer[i][j] = PREVIOUSZEROPATH;
		
}
void MoveGenerator::resetgrid()
{
	square_color color;
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
		{
			color = analysisgridpointer[i][j];
			if(color < 0 || color > number_of_colors) 
				analysisgridpointer[i][j] = 0;
		}
	for(int i = 0; i < number_of_colors; i++)
	{
		if(tempsources[i] != NULL)
			analysisgridpointer[tempsources[i]->y][tempsources[i]->x] = i + 1;
	}
}

bool MoveGenerator::testEndsources(coordinate x, coordinate y, square_color color)
{
	coordinate es_x, es_y, ts_x, ts_y, x2, y2;
	bool issamecolor;
	bool result = true;
	bool endsourceisvalid;
	for(int i = 0; i < number_of_colors && result; i++)
	{
		es_x = endsources[i][0];
		es_y = endsources[i][1];
		issamecolor = i + 1 == color;
		if((es_x != x || es_y != y || issamecolor) && (tempsources[i]->x != es_x || tempsources[i]->y != es_y))
		{
			analysisgridpointer[y][x] = color;
			endsourceisvalid = false;
			// Pipe is not finished, therefore we need to see if it can be.
			ts_x = (issamecolor) ? x : tempsources[i]->x;
			ts_y = (issamecolor) ? y : tempsources[i]->y;
			analysisgridpointer[ts_y][ts_x] = tempsourceval;
			for(int j = 0; j < 4 && !endsourceisvalid; j++)
			{
				switch(j)
				{
					case 0: x2 = es_x + 1; y2 = es_y; break;
					case 1: x2 = es_x - 1; y2 = es_y; break;
					case 2: x2 = es_x; y2 = es_y + 1; break;
					case 3: x2 = es_x; y2 = es_y - 1; break;
				}
				
				if(isvalid(x2, y2, size))
				{
					if(analysisgridpointer[y2][x2] == 0)
					{
						endsourceisvalid |= testZero(x2, y2);
						updategrid();
					}
					else if(analysisgridpointer[y2][x2] == tempsourceval)
						endsourceisvalid = true;
					
				}
			}
			resetgrid();
			result |= endsourceisvalid;
		}	
	}
	analysisgridpointer[y][x] = 0;
	
	return result;
}	

bool MoveGenerator::testZeros(coordinate x, coordinate y, square_color color, coordinate d)
{
	bool isok = true;
	setupgrid(color);
	if(endsources[color-1][0] == x && endsources[color-1][1] == y)
		analysisgridpointer[y][x] = color;
	
	else
		analysisgridpointer[y][x] = tempsourceval;
	
	for(int i = x - d; i <= x + d && isok; i++)
		for(int j = y - d; j <= y + d && isok; j++)
			if(isvalid(i, j, size) && analysisgridpointer[j][i] == 0)
			{
				isok &= testZero(i, j, 0);
				if(isok)
					updategrid();
				

			}
			
	resetgrid();
	analysisgridpointer[y][x] = 0;
	return isok;
	
}

bool MoveGenerator::testZero(coordinate x, coordinate y, coordinate_squared depth)
{
	int x2, y2;
	analysisgridpointer[y][x] = CURRENTZEROPATH;
	bool result = true;
	square_color color;
	if(depth != MAXDEPTH)
	{
		result = false;
		for(int i = 0; i < 4 && !result; i++)
		{
			switch(i)
			{
				case 0: x2 = x + 1; y2 = y; break;
				case 1: x2 = x - 1; y2 = y; break;
				case 2: x2 = x; y2 = y + 1; break;
				case 3: x2 = x; y2 = y - 1; break;
			}
			
			if(isvalid(x2, y2, size))
			{
				color = analysisgridpointer[y2][x2];
				switch(color)
				{
					case PREVIOUSZEROPATH: result = true; goto end; break;
					case  0: result |= testZero(x2, y2, depth + 1); break;
					default:
						if(color == number_of_colors + 1) 
						{result = true; goto end;} break;
					
				}
			}
		}
	}
	end:
	return result;
}
