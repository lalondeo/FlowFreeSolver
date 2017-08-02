#include "Grid.h"

Grid::Grid(coordinate size)
{
	square_color ** grid = generateEmptyGrid(size);
	Grid(grid, size);
	
}

Grid::Grid(square_color** grid, coordinate size)
{
	Grid(grid, size, &Square::squareFactory);
}

Grid::Grid(square_color** _grid, coordinate _size, Square * (*factory) (coordinate, coordinate, square_color, Square* [2]))
{
	originalgrid = _grid;
	size = _size;
	grid = new Square**[size];
	number_of_colors = 0;
	
	for(int i = 0; i < size; i++)
	{
		grid[i] = new Square*[size];
		for(int j = 0; j < size; j++)
		{
			Square* partialneighborhood[2];
			partialneighborhood[0] = (i != 0) ? grid[i-1][j] : NULL;
			partialneighborhood[1] = (j != 0) ? grid[i][j-1] : NULL;
			grid[i][j] = (*factory)(j, i, _grid[i][j], partialneighborhood);
			
			if(_grid[i][j] > number_of_colors) 
				number_of_colors = _grid[i][j];
			
		}
	}
	
	// Initialize sources and set to null - it's up to the children to find them
	sources = new Square**[number_of_colors];
	for(int i = 0; i < number_of_colors; i++)
	{
		sources[i] = new Square*[2];
		sources[i][0] = NULL;
		sources[i][1] = NULL;
	}
	
	
}

Grid::~Grid()
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			delete grid[i][j];
		
		delete[] grid[i];
	}
	delete[] grid;

	for(int i = 0; i < number_of_colors; i++)
	{
		sources[i][0] = sources[i][1] = NULL;
		delete[] sources[i]; // Squares were deallocated in the previous step
	}
	
	delete[] sources;
	deleteGrid(originalgrid, size);
		
}

void Grid::print()
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			cout << (int)grid[i][j]->getColor() << " ";
		
		cout << endl;
	}
}

Square* Grid::getSquare(coordinate x, coordinate y)
{
	return grid[y][x];
}

coordinate Grid::getSize()
{
	return size;
}

square_color Grid::getNumberOfColors()
{
	return number_of_colors;
}

Square** Grid::getSources(square_color color)
{
	return sources[color - 1];
}

void Grid::setSources(square_color color, Square* first_source, Square* second_source)
{
	sources[color - 1][0] = first_source;
	sources[color - 1][1] = second_source;
	
}

square_color chartocolor(char character)
{
	square_color result;
	if(isdigit(character))
		result = character - '0';
	else
		result = character - 'A' + 10;
	
	return result;
}
char colortochar(square_color color)
{
	char result;
	if(color == 0) 
		result = ' ';
	
	else if(color < 10)
		result = color + '0';
	else
		result = 'A' + color - 10;
	
	return result;
}

square_color ** generateEmptyGrid(coordinate size)
{
	square_color** grid = new square_color*[size];
	for(int i = 0; i < size; i++)
	{
		grid[i] = new square_color[size];
		for(int j = 0; j < size; j++)
			grid[i][j] = 0;
	}
	return grid;
}
void deleteGrid(square_color** grid, coordinate size)
{
	for(int i = 0; i < size; i++) delete[] grid[i];
	delete[] grid;
}

void printGrid(square_color** grid, coordinate size)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
			printf("%c ", colortochar(grid[i][j]));
		printf("\n");
	}
}

#ifdef LOGGING
ofstream logfile;
void openlogfile()
{
	logfile.open(LOGFILEPATH);
}

void logGrid(square_color ** grid, coordinate size)
{
	assert(logfile.is_open());
	for(int y = 0; y < size; y++)
	{
		for(int x = 0; x < size; x++)
			logfile << (int)grid[y][x];
	}
		
	logfile << "\n";
}

void closelogfile()
{
	logfile.close();
}

uint64_t reducegrid(square_color ** grid, coordinate size)
{
	uint64_t resultat = 0;
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			resultat += (grid[i][j] == 0 ? 0 : 1) << coordinatetonumber(i, j, size);
	
	return resultat;
}


GridInfo * readfen(string fen)
{
	GridInfo * result = new GridInfo();
	result->size = 0;
	result->number_of_colors = 0;
	char character;
	int color;
	bool sizeisfixed = false;
	for(int i = 0; i < fen.size(); i++)
	{
		character = fen[i];
		if(isalnum(character))
			result->number_of_colors = max(chartocolor(character), result->number_of_colors);
		
		
		if(character != '/' && !sizeisfixed) result->size++;
		else if(character == '/') sizeisfixed = true;
	}
	
	result->sources = new coordinate**[result->number_of_colors];
	for(int i = 0; i < result->number_of_colors; i++)
		result->sources[i] = new coordinate*[2]();
	
	
	int x = 0;
	int y = 0;
	int sourceindex;
	for(int i = 0; i < fen.size(); i++)
	{
		character = fen[i];
		if(character == '/')
		{
			x = 0;
			y++;
		}
		else
		{
			if(isalnum(character) && character != '0')
			{
				sourceindex = chartocolor(character) - 1;
				
				if(result->sources[sourceindex][0] == NULL)
				{
					result->sources[sourceindex][0] = new coordinate[2];
					result->sources[sourceindex][0][0] = x;
					result->sources[sourceindex][0][1] = y;
				}
				else
				{
					result->sources[sourceindex][1] = new coordinate[2];
					result->sources[sourceindex][1][0] = x;
					result->sources[sourceindex][1][1] = y;
				}
			}
			x++;
		
		}
	}
	return result;
	
}
#endif
