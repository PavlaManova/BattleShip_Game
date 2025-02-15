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
#include <fstream>
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

void checkIfShipThisSizeCanBePlaced(int &shipSize, const Fleet& fleet)
{
	string input;
	while (!thisNumberOfShipsIsNotFull(shipSize, fleet))
	{
		cout << "There are no more ships with this size you can place. Try again with another ship." << endl;
		cout << "Choose the size of the ship:";
		cin >> input;
		shipSize = validateShipSizeInput(input);
	}
}

bool thisNumberOfShipsIsNotFull(int shipSize, const Fleet& fleet)
{
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
		if (fleet.mediumShips == 0)
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
	default:
		break;
	}

	return false;
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

char validateDirectionInput(string input)
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

void checkIfFieldIsUsed(int field[FIELD_SIZE][FIELD_SIZE], int& x, int& y, string& startingField)
{
	string input;
	while (field[x][y] == 1)
	{
		cout << "This field is already used. Try again." << endl;
		cout << "Choose starting field (letter then number of field):";
		cin >> input;
		startingField = validateStartingFieldInput(input);
		getShipCoordinates(startingField, x, y);
	}
}

bool positionIsPossible(int positions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], int shipSize, char direction, int x, int y)
{
	int startPosition = 0;

	//check if the ship-to-be-placed falls within a forbidden area of another ship
	//checking is searching for 1 in a rectangular with width and height according to ship's size and orientation - horizontal or vertical

	switch (direction)
	{
	case 'U':
	{
		startPosition = x - shipSize + 2;

		for (int i = startPosition; i < shipSize + startPosition; i++)
		{
			if (positions[i][y + 1] == 1)
				return false;
		}
		break;
	}
	case 'D':
	{
		startPosition = x + 1;

		for (int i = startPosition; i < shipSize + startPosition; i++)
		{
			if (positions[i][y + 1] == 1)
				return false;
		}
		break;
	}
	case 'L':
	{
		startPosition = y - shipSize + 2;

		for (int j = startPosition; j < shipSize + startPosition; j++)
		{
			if (positions[x + 1][j] == 1)
				return false;
		}

		break;
	}
	case 'R':
	{
		startPosition = y + 1;

		for (int j = startPosition; j < shipSize + startPosition; j++)
		{
			if (positions[x + 1][j] == 1)
				return false;
		}

		break;
	}
	default:
		break;
	}
	return true;
}

bool shipFitsInField(int field[FIELD_SIZE][FIELD_SIZE], int shipSize, char direction, int x, int y)
{
	int start = 0,
		end = 0;

	switch (direction)
	{
	case 'U':
	{
		start = x - shipSize + 1;
		if (start < 0)
			return false;
		break;
	}
	case 'D':
	{
		end = x + shipSize;
		if (end > FIELD_SIZE)
			return false;
		break;
	}
	case 'L':
	{
		start = y - shipSize + 1;
		if (start < 0)
			return false;
		break;
	}
	case 'R':
	{
		end = y + shipSize;
		if (end > FIELD_SIZE)
			return false;
		break;
	}
	default:
		break;
	}
	return true;
}

char validateChoice(int options)
{
	string choice;

	cin >> choice;

	while (choice[1] != '\0')
	{
		if (options == 3)
			cout << "Wrong input. Try again, choose between 1, 2 or 3." << endl << "Choice: ";
		else
			cout << "Wrong input. Try again, choose between 1, 2, 3 or 4." << endl << "Choice: ";
		cin >> choice;
	}

	if (options == 3)
	{
		while (choice[0] != '1' && choice[0] != '2' && choice[0] != '3')
		{
			cout << "Wrong input. Try again, choose between 1, 2 or 3." << endl;
			cout << "Choice: ";
			cin >> choice;
		}
	}
	else
	{
		while (choice[0] != '1' && choice[0] != '2' && choice[0] != '3' && choice[0] != '4')
		{
			cout << "Wrong input. Try again, choose between 1, 2, 3 or 4." << endl;
			cout << "Choice: ";
			cin >> choice;
		}
	}
	return choice[0];
}

void validateStream(ifstream& file)
{
	if (!file.is_open())
	{
		cout << "Something went wrong." << endl;
		exit(-1);
	}
}