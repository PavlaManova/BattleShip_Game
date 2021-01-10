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

void validateStream(fstream& file)
{
	if (!file.is_open())
		cout << "Something went wrong. Press any key to return to menu." << endl;
	//---ADD return to startMenu---
}

int findAllRandomArrangements(ifstream& file)
{
	int number,
		counter = 0;

	while (!file.eof())
	{
		file >> number;
		if (number >= 2)
			counter++;
	}

	file.clear();
	file.seekg(0, ios::beg);

	return counter;
}

void readArrangementFromFile(ifstream& file, int &indexOfOption)
{
	int index;
	int field[FIELD_SIZE][FIELD_SIZE] = { 0 };
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
		if (file.eof() && !optionFaund)
		{
			indexOfOption = FIRST_ARRANGEMENT_OPTION_INDEX;

			file.clear();
			file.seekg(0, ios::beg);
		}
	} while (!optionFaund);
	
	printBattlefield(field, "Random Field");
}