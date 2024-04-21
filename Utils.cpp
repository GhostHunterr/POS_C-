#include <iostream>
#include <limits>

#include "Utils.h"

using namespace std;
using namespace sdds;


namespace sdds
{
	//Clears input buffer.
	void clearInputBuffer()
	{
		//Clears the error state.
		cin.clear();

		//Discards the input in input buffer.
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}