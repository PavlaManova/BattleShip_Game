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
#include <fstream>
#include "ReadFromFile.h"

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
			chooseReadyArrangement();
			break;
		}
		case 1:
		{
			arrangeYourself();
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
		printBattlefield(field, "Your filed");
		printArrangementOptions(3);

		choice = validateChoice(3);

		switch (choice)
		{
		case '1':
		{
			printBattlefield(field, "Place your ship");
			placeShip(field, possiblePositions);
			break;
		}
		case '2':
		{
			//changeShip(field);
			break;
		}
		case '3':
		{
			printBattlefield(field, "Your field");
			printUnusedShips(fleet);
			break;
		}
		default:
			break;
		}
	}

	while (fleet.allShips < MAX_SHIPS_COUNT)
	{
		printBattlefield(field, "Your filed");
		printArrangementOptions(4);

		choice = validateChoice(4);

		switch (choice)
		{
		case '1':
		{
			printBattlefield(field, "Place your ship");
			placeShip(field, possiblePositions);
			printBattlefield(field, "Your field");
			break;
		}
		case '2':
		{
			//changeShip(field);
			break;
		}
		case '3':
		{
			printBattlefield(field, "Your field");
			printUnusedShips(fleet);
			break;
		}
		case '4':
		{
			break;
		}
		default:
			break;
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

void printUnusedShips(Fleet& fleet)
{
	cout << "You can place:" << endl;
	if (fleet.smallShips != 0)
	{
		cout << fleet.smallShips << " small ships with size 2" << endl;
	}
	if (fleet.mediumShips != 0)
	{
		cout << fleet.mediumShips << " medium ships with size 3" << endl;
	}
	if (fleet.bigShips != 0)
	{
		cout << fleet.bigShips << " big ships with size 4" << endl;
	}
	if (fleet.cruiserShips != 0)
	{
		cout << fleet.bigShips << " cruiser ship with size 6" << endl;
	}

	int total = MAX_SHIPS_COUNT - fleet.allShips;
	if (total == 1)
		cout << "Total of " << total << " ship left." << endl;
	else
		cout << "Total of " << total << " ships left." << endl;

	system("Pause");
}

void chooseReadyArrangement()
{
	ifstream file;
	char fileName[] = "shipsArrangements.txt";
	file.open(fileName);

	int option = FIRST_ARRANGEMENT_OPTION_INDEX,
		choice;

	int sumArrangements = findAllRandomArrangements(file);
	readArrangementFromFile(file, option);
	printChooseRandomArrangementOptions();

	choice = chooseRandomArrangement();

	while (choice != 0) //is chosen
	{
		option += choice;

		if (option > sumArrangements+FIRST_ARRANGEMENT_OPTION_INDEX-1)
		{
			option = FIRST_ARRANGEMENT_OPTION_INDEX;
		}
		if (option < FIRST_ARRANGEMENT_OPTION_INDEX)
		{
			option = sumArrangements + 1;
		}

		readArrangementFromFile(file, option);
		printChooseRandomArrangementOptions();
		choice = chooseRandomArrangement();
	}

	//start game
	file.close();
}