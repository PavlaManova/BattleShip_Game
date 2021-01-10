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
Player firstPlayer;
Player secondPlayer;
bool canStartGame = false;

void startGame()
{
	int actionCode;

	printPlayer("Player 1");

	startingMenu();

	while (!canStartGame)
	{
		actionCode = arrangeShipsMenu();
		switch (actionCode)
		{
		case 0:
		{
			chooseReadyArrangement();
			break;
		}
		case 1:
		{
			arrangeYourself();
			break;
		}
		case 2:
		{
			startingMenu(); //Option "Return"
			break;
		}
		default:
			break;
		}
		if (firstPlayer.hasChosenBoard && !secondPlayer.hasChosenBoard)
		{
			printPlayer("Player 2");
		}
	}

	startPlaying();
}

void arrangeYourself()
{
	int field[FIELD_SIZE][FIELD_SIZE] = { 0 };
	char choice;
	Fleet tempFleet;

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
			printBattlefield(field, "Change ship's position");
			changeShip(field, possiblePositions);
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
			printBattlefield(field, "Change ship's position");
			changeShip(field, possiblePositions);
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
			if (!firstPlayer.hasChosenBoard)
			{
				firstPlayer.hasChosenBoard = true;
				getArrayValue(field, firstPlayer.field);
				getShipsCount(fleet, firstPlayer);

				//restart fleet for second player
				fleet = tempFleet;
			}
			else
			{
				secondPlayer.hasChosenBoard = true;
				getArrayValue(field, secondPlayer.field);
				getShipsCount(fleet, secondPlayer);
				canStartGame = true;
			}
			return;
			break;
		}
		default:
			break;
		}
	}

	if (fleet.allShips == MAX_SHIPS_COUNT)
	{
		if (!firstPlayer.hasChosenBoard)
		{

			firstPlayer.hasChosenBoard = true;
			getArrayValue(field, firstPlayer.field);
			firstPlayer.fleet = fleet;

			//restart fleet for second player
			fleet = tempFleet;
		}
		else
		{
			secondPlayer.hasChosenBoard = true;
			getArrayValue(field, secondPlayer.field);
			secondPlayer.fleet = fleet;
			canStartGame = true;
		}
	}
}

void placeShip(int field[FIELD_SIZE][FIELD_SIZE], int possiblePositions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE])
{
	int shipSize, x, y;
	string startingField;
	char direction;

	getPlaceShipInfo(shipSize, startingField, direction, field, fleet);
	getShipCoordinates(startingField, x, y);

	while (!positionIsPossible(possiblePositions, shipSize, direction, x, y) || !shipFitsInField(field, shipSize, direction, x, y))
	{
		cout << "This position is not possible. Try again." << endl;
		getPlaceShipInfo(shipSize, startingField, direction, field, fleet);
		getShipCoordinates(startingField, x, y);
	}

	switch (direction)
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

void changeShip(int field[FIELD_SIZE][FIELD_SIZE], int possiblePositions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE])
{
	int x, y;
	getChangeShipInfo(field, fleet, x, y);
	clearShip(field, possiblePositions, x, y);
	printBattlefield(field, "Place your ship");
	placeShip(field, possiblePositions);
	printBattlefield(field, "Your field");
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
		cout << fleet.cruiserShips << " cruiser ship with size 6" << endl;
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
	//printPlayer(firstPlayer);

	ifstream file;
	char fileName[] = "shipsArrangements.txt";
	file.open(fileName);

	int option = FIRST_ARRANGEMENT_OPTION_INDEX,
		choice,
		field[FIELD_SIZE][FIELD_SIZE];


	int sumArrangements = findAllRandomArrangements(file);
	readArrangementFromFile(file, option, field);
	printBattlefield(field, "Random Field");
	printChooseRandomArrangementOptions();

	choice = chooseRandomArrangement();

	while (choice != 0) //is chosen
	{
		option += choice;

		if (option > sumArrangements + FIRST_ARRANGEMENT_OPTION_INDEX - 1)
		{
			option = FIRST_ARRANGEMENT_OPTION_INDEX;
		}
		if (option < FIRST_ARRANGEMENT_OPTION_INDEX)
		{
			option = sumArrangements + 1;
		}

		readArrangementFromFile(file, option, field);
		printBattlefield(field, "Random Field");
		printChooseRandomArrangementOptions();
		choice = chooseRandomArrangement();
	}

	//start game
	Fleet tempFleet;
	tempFleet.allShips = MAX_SHIPS_COUNT;
	if (!firstPlayer.hasChosenBoard)
	{
		firstPlayer.hasChosenBoard = true;
		getArrayValue(field, firstPlayer.field);
		firstPlayer.fleet = tempFleet;
	}
	else
	{
		secondPlayer.hasChosenBoard = true;
		getArrayValue(field, secondPlayer.field);
		secondPlayer.fleet = tempFleet;
		canStartGame = true;
	}
	file.close();
}

void startPlaying()
{
	system("CLS");

	printBattlefield(secondPlayer.field, "First player's turn");
}