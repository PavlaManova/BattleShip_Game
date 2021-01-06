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
* <file with implementation of validation functions>
*
*/

#include <iostream>
#include "Validation.h"
#include "GameLogic.h"
#include "Constants.h"
#include "AuxiliaryFunctions.h"

using namespace std;

int validateShipSizeInput(string input)
{
	while (input.size() != 1)
	{
		cout << "Incorect input. Try again with one of the numbers 2, 3, 4, 6:";
		cin >> input;
	}

	while (input[0] != '2' && input[0] != '3' && input[0] != '4' && input[0] != '6')
	{
		cout << "Incorect input. Try again with one of the numbers 2, 3, 4, 6:";
		cin >> input;
		while (input.size() != 1)
		{
			cout << "Incorect input. Try again with one of the numbers 2, 3, 4, 6:";
			cin >> input;
		}
	}

	return (int)input[0] - 48; //returns the int value of the input '2' -> 2
}

bool canPlaceShipThisSize(int shipSize, Fleet& fleet)
{
	if (fleet.allShips > MAX_SHIPS_COUNT)
		return false;

	switch (shipSize)
	{
	case 2:
	{
		if (fleet.smallShips == 0)
			return false;
		else
			return true;
		break;
	}
	case 3:
	{
		if (fleet.midiumShips == 0)
			return false;
		else
			return true;
		break;
	}
	case 4:
	{
		if (fleet.bigShips == 0)
			return false;
		else
			return true;
		break;
	}
	case 6:
	{
		if (fleet.cruiserShips == 0)
			return false;
		else
			return true;
		break;
	}
	}

}

string validateStartingFieldInput(string input)
{
	//---ADD validation with space between letter and number---

	while (wrongFieldInput(input))
	{
		cout << "Incorect input. Try again with something like J3:";
		cin >> input;
	}

	if (input[0] >= 'a' || input[0] <= 'j')
		input[0] -= 32;

	return input;

}

bool wrongFieldInput(string input)
{
	if (input.size() != 2)
	{
		//Exception for field 10
		if (input.size() != 3)
			return true;
		else if (input[1] == '1' && input[2] == '0')
		{
			if ((input[0] < 'A' || input[0]>'J') && (input[0] < 'a' || input[0]>'j'))
				return true;
			else return false;
		}
		else
			return true;
	}
	else if ((input[0] < 'A' || input[0]>'J') && (input[0] < 'a' || input[0]>'j'))
		return true;
	else if (input[1] < '1' || input[1] > '9')
		return true;
	else
		return false;
}

char validateOrientationInput(string input)
{
	while (input.size() != 1)
	{
		cout << "Incorect input. Try again with one of the letters U, D, L, R:";
		cin >> input;
	}

	while (input[0] != 'U' && input[0] != 'u' && input[0] != 'D' && input[0] != 'd' && input[0] != 'L' && input[0] != 'l' && input[0] != 'R' && input[0] != 'r')
	{
		cout << "Incorect input. Try again with one of the letters U, D, L, R:";
		cin >> input;
		while (input.size() != 1)
		{
			cout << "Incorect input. Try again with one of the letters U, D, L, R:";
			cin >> input;
		}
	}

	if (input[0] == 'u' || input[0] == 'd' || input[0] == 'l' || input[0] == 'r') //return upper letter for easier work
		input[0] -= 32;
	return input[0];
}

/*bool shipFitsInField(int fieldl[FIELD_SIZE][FIELD_SIZE], int shipSize, char orientation, int x, int y)
{
	if(x)
}
*/
bool positionIsPossible(int positions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], int shipSize, char orientation, int x, int y)
{
	/*if (!shipFitsTheField(positions,))
		return false;*/

	//When a ship is placed it forms a rectangular arount itself with field that are not possible for placing another ship

	//coordinates of this forbbiden area
	int width = 0,
		heigth = 0,
		startingPointX = 0,
		startingPointY = 0;

	switch (orientation)
	{
	case 'U':
	{
		width = 3;
		heigth = shipSize + 2;
		startingPointX = x - shipSize + 1;
		startingPointY = y;

		for (int i = startingPointX; i < heigth + startingPointY; i++)
		{
			for (int j = startingPointY; j < width + startingPointX; j++)
			{
				if (positions[i][j] == 1)
					return false;
			}
		}

		break;
	}
	case 'D':
	{
		width = 3;
		heigth = shipSize + 2;
		startingPointX = x;
		startingPointY = y;

		for (int i = startingPointX; i < heigth + startingPointY; i++)
		{
			for (int j = startingPointY; j < width + startingPointX; j++)
			{
				if (positions[i][j] == 1)
					return false;
			}
		}
		break;
	}
	case 'L':
	{
		width = shipSize + 2;
		heigth = 3;
		startingPointX = x;
		startingPointY = y - shipSize + 1;

		for (int i = startingPointX; i < heigth + startingPointY; i++)
		{
			for (int j = startingPointY; j < width + startingPointX; j++)
			{
				if (positions[i][j] == 1)
					return false;
			}
		}
		break;
	}
	case 'R':
	{
		width = shipSize + 2;
		heigth = 3;
		startingPointX = x;
		startingPointY = y;

		for (int i = startingPointX; i < heigth + startingPointY; i++)
		{
			for (int j = startingPointY; j < width + startingPointX; j++)
			{
				if (positions[i][j] == 1)
					return false;
			}
		}
		break;
	}
	default:
	{
		cout << "Something went wrong." << endl;
		exit(-1);
	}
	}
}