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
#include "AuxiliaryFunctions.h"

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
	int field[FIELD_SIZE][FIELD_SIZE] = { 0 };
	char choice;

	//When a ship is placed it forms a rectangular arount itself with field that are not possible for placing another ship

	int possiblePositions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE] = { 0 }; //made one size bigger square to miss the checks for going outside of the array

	//Place first ship
	printBattlefield(field, "Place your ship");
	placeShip(field, possiblePositions);
	printBattlefield(field, "Your field");

	while (fleet.allShips < 5) //the game can start with minimum of 5 ships 
	{
		cout << "\nChose one of the following options:" << endl;
		cout << "1) place next ship\n2) change position of some of your ships" << endl; //the third option - view board, is shown the whole time
		cout << "Choice: ";

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
			placeShip(field, possiblePositions);
			printBattlefield(field, "Your field");
		}

		/*else
			changeShip(field);*/
			//}
	}

	while (fleet.allShips < MAX_SHIPS_COUNT)
	{
		cout << "\nYou have enough ships to start the game now." << endl;
		cout << "\nChose one of the following options:" << endl;
		cout << "1) place next ship\n2) change position of some of your ships\n3)start game" << endl;
		cout << "Choice: ";

		cin >> choice;

		while (choice != '1' && choice != '2' && choice != '3')
		{
			cout << "Wrong input. Try again, choose between 1, 2 or 3." << endl;
			cout << "Choice: ";
			cin >> choice;
		}

		switch (choice)
		{
		case 1:
		{
			printBattlefield(field, "Place your ship");
			placeShip(field, possiblePositions);
			printBattlefield(field, "Your field");
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		}
	}
}

void placeShip(int field[FIELD_SIZE][FIELD_SIZE], int possiblePositions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE])
{
	int shipSize, x, y;
	string startingField;
	char orientation;

	getShipInformation(shipSize, startingField, orientation, field, fleet);
	getShipCoordinates(startingField, x, y);

	while (!positionIsPossible(possiblePositions, shipSize, orientation, x, y) || !shipFitsInField(field, shipSize, orientation, x, y))
	{
		cout << "This position is not possible. Try again." << endl;
		getShipInformation(shipSize, startingField, orientation, field, fleet);
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
		fillImpossiblePositions(possiblePositions, field);
		break;
	}
	case 'D':
	{
		for (int i = x; i < x + shipSize; i++)
		{
			field[i][y] = 1;
		}
		fillImpossiblePositions(possiblePositions, field);
		break;
	}
	case 'L':
	{
		for (int j = y - shipSize + 1; j <= y; j++)
			field[x][j] = 1;
		fillImpossiblePositions(possiblePositions, field);
		break;
	}
	case 'R':
	{
		for (int j = y; j < y + shipSize; j++)
		{
			field[x][j] = 1;
		}
		fillImpossiblePositions(possiblePositions, field);
		break;
	}
	default:
		break;
	}

	addShipToFleed(shipSize, fleet);
}