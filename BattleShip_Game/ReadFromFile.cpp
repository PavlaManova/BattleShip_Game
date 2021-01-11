/**
*
* Solution to course project #5
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Pavla Manova
* @idnumber 62613
* @compiler VC
*
* <file with implementation of functions for reading ship arrangements from txt file>
*
*/

#include "ReadFromFile.h"
#include <fstream>
#include "Constants.h"
#include "drawBoard.h"

using namespace std;

int findAllRandomArrangements(ifstream& file)
{
	//indexes of ready boards in the file start from 2 -> for not to be mixed with the board values of 0 and 1

	//start reading file from beggining
	file.clear();
	file.seekg(0, ios::beg);

	int number,
		counter = 0;

	while (!file.eof())
	{
		file >> number;
		if (number >= 2)
			counter++;
	}

	return counter;
}

void readArrangementFromFile(ifstream& file, int& indexOfOption, int field[FIELD_SIZE][FIELD_SIZE])
{
	int index;
	bool optionFaund = false;

	//start reading file from beggining
	file.clear();
	file.seekg(0, ios::beg);

	do
	{
		file >> index;
		if (index >= 2)
		{
			if (index == indexOfOption)
			{
				for (int i = 0; i < FIELD_SIZE; i++)
				{
					for (int j = 0; j < FIELD_SIZE; j++)
						file >> field[i][j];
				}
				optionFaund = true;
			}
		}
		if (file.eof() && !optionFaund) //return to the first option
		{
			indexOfOption = FIRST_ARRANGEMENT_OPTION_INDEX;

			//return to beggining of file
			file.clear();
			file.seekg(0, ios::beg);
		}
	} while (!optionFaund);
}