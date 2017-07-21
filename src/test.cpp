#include <iostream>
#include <vector>
#include <algorithm>


int main()
{
	int** foobar = new int*[3];
	
	char** foobar2 = (char**)foobar;
	std::cout << foobar2[0] << " " << foobar[0];
	
	
}