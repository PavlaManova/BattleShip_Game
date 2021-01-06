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
* <file with implementation of game logic>
*
*/

#include "GameLogic.h"
#include "Menu.h"
#include "drawBoard.h"
#include "Constants.h"
#include "Validation.h"

Fleet fleet;

void startGame()
{
	int actionCode = 0;
	actionCode = startingMenu();
	//ADD ---choose player option---
	while (actionCode == 1)
	{
		actionCode = arrangeShipsMenu();
		switch (actionCode)
		{
		case 0:
		{
			//ADD ---reading positions from file---
			system("CLS");
			printEmptyField();
			break;
		}
		case 1:
		{
			//ADD ---arrange yourself---
			arrangeYourself();
			//printEmptyField();
			actionCode = 0;
			break;
		}
		case 2:
		{
			actionCode = startingMenu(); //Option "Return"
			break;
		}
		default: break;
		}

	}
}

void arrangeYourself()
{
	int field[FIELD_SIZE][FIELD_SIZE] =
	{
	{1, 1, 0, 1, 0, 0, 1, 1, 1, 1},
	{ 0,0,0,1,0,0,0,0,0,0 },
	{ 1,0,0,1,0,1,1,1,0,1 },
	{ 1,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0 },
	{ 1,0,0,0,0,1,0,0,0,1 },
	{ 0,0,0,0,0,1,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,1,1,1,1,1,1 }
	};

	int positions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE] = { 0 };

	fillPossiblePositions(positions,field);

	//Place first ship
	printBattlefield(field, "Place your ship");

	placeShip(field,positions);

	printBattlefield(field, "Your field");


	/*
	//while (countShips < 5)
	//{
	printBattlefield(field, "Your field");
	cout << "Chose one of the following options:" << endl;
	cout << "1) place next ship\n2) change position of some of your ships" << endl;//the third option - view board, is shown the whole time
	cout << "Choice: ";

	char choice;
	cin >> choice;

	while (choice != '1' && choice != '2')
	{
		cout << "Wrong input. Try again, choose between 1 or 2." << endl;
		cout << "Choice: ";
		cin >> choice;
	}

	if (choice == '1')
	{
		printBattlefield(field, "Place your ship");
		placeShip(field);
		printBattlefield(field, "Your field");
	}
	*/
	/*else
		changeShip(field);*/
		//}

}

void placeShip(int field[FIELD_SIZE][FIELD_SIZE], int possiblePositions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE])
{
	int shipSize, x, y;
	string startingField;
	char orientation;

	//int possiblePositions[FIELD_SIZE + 2][FIELD_SIZE + 2] = { 0 }; //make one size bigger square to miss the checks for going outside of the array

	getShipInformation(shipSize, startingField, orientation, field);
	getShipCoordinates(startingField, x, y);

	while (!positionIsPossible(possiblePositions, shipSize, orientation, x, y))
	{
		cout << "This position is not possible. Try again." << endl;
		getShipInformation(shipSize, startingField, orientation, field);
		getShipCoordinates(startingField, x, y);
	}

	switch (orientation)
	{
	case 'U':
	{
		for (int i = x - shipSize + 1; i <= x; i++)
		{
			field[i][y] = 1;
		}
		fillPossiblePositions(possiblePositions, field);
		break;
	}
	case 'D':
	{
		for (int i = x; i < x + shipSize; i++)
		{
			field[i][y] = 1;
		}
		fillPossiblePositions(possiblePositions, field);
		break;
	}
	case 'L':
	{
		for (int j = y - shipSize + 1; j <= y; j++)
			field[x][j] = 1;
		fillPossiblePositions(possiblePositions, field);
		break;
	}
	case 'R':
	{
		for (int j = y; j < y + shipSize; j++)
		{
			field[x][j] = 1;
		}
		fillPossiblePositions(possiblePositions, field);
		break;
	}
	default:
	{
		cout << "Something went wrong." << endl;
		exit(-1);
	}
	}
}

void getShipInformation(int& shipSize, string& startingField, char& orientation, int field[FIELD_SIZE][FIELD_SIZE])
{
	string input;
	cout << "Choose the size of the ship (2, 3, 4 or 6):";
	cin >> input;
	shipSize = validateShipSizeInput(input);

	while (!canPlaceShipThisSize(shipSize, fleet))
	{
		cout << "There are no more ships with this size you can place. Try again with another ship." << endl;
		cout << "Choose the size of the ship:";
		cin >> input;
		shipSize = validateShipSizeInput(input);
	}

	cout << "Choose starting field (letter then number of field):";
	cin >> input;
	startingField = validateStartingFieldInput(input);

	int x, y;
	getShipCoordinates(startingField, x, y);

	while (field[x][y] == 1)
	{
		cout << "This field is already used. Try again." << endl;
		cout << "Choose starting field (letter then number of field):";
		cin >> input;
		startingField = validateStartingFieldInput(input);
		getShipCoordinates(startingField, x, y);
	}

	cout << "Choose a direction for the ship. Choose between (U)p, (D)own, (L)eft, (R)ight:";
	cin >> input;
	orientation = validateOrientationInput(input);
}

void getShipCoordinates(string field, int& x, int& y)
{
	y = field[0] - 65;
	if (field.size() == 2)
	{
		x = field[1] - 49;
	}
	else
		x = 9;
}

void fillPossiblePositions(int positions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], int field[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 1; i < FIELD_SIZE + 1; i++)
	{
		for (int j = 1; j < FIELD_SIZE + 1; j++)
		{
			if (field[i - 1][j - 1] == 1) //there is ship
			{
				positions[i - 1][j - 1] = 1;
				positions[i - 1][j] = 1;
				positions[i - 1][j + 1] = 1;
				positions[i][j - 1] = 1;
				positions[i][j] = 1;
				positions[i][j + 1] = 1;
				positions[i + 1][j - 1] = 1;
				positions[i + 1][j] = 1;
				positions[i + 1][j + 1] = 1;
			}
		}
	}
}