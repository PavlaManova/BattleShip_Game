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
#include <iomanip>

using namespace std;

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
			firstPlayer.hasChosenBoard = false;
			secondPlayer.hasChosenBoard = false;
			printPlayer("Player 1");
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

	while (fleet.allShips < MAX_SHIPS_COUNT)
	{
		printBattlefield(field, "Your filed");

		if (fleet.allShips < 5)
		{
			printArrangementOptions(3);

			choice = validateChoice(3);
		}
		else
		{
			printArrangementOptions(4);

			choice = validateChoice(4);
		}

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
			playerCanStartPlaying(firstPlayer, secondPlayer, field, fleet);
			if (secondPlayer.hasChosenBoard)
				canStartGame = true;
			return;
			break;
		}
		default:
			break;
		}
	}

	//all ships have been placed
	playerCanStartPlaying(firstPlayer, secondPlayer, field, fleet);
	if (secondPlayer.hasChosenBoard)
		canStartGame = true;

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
	int x, y, shipLength = 0;
	getChangeShipInfo(field, fleet, x, y);
	clearShip(field, x, y, FIELD_SIZE, FIELD_SIZE, shipLength);
	removeShipFromFleed(fleet, shipLength);
	fillImpossiblePositions(possiblePositions, field);
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
	ifstream file;
	char fileName[] = "shipsArrangements.txt";

	file.open(fileName);

	validateStream(file);

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

	int x, y;
	bool hit = true,
		firstPlayerTurn = true,
		isEndGame = false;

	while (!isEndGame)
	{
		hit = true;
		if (firstPlayerTurn)
		{
			while (hit)
			{
				printBattlefield(secondPlayer.firedField, "First player's turn");
				chooseFieldToShoot(x, y);
				if (secondPlayer.field[x][y] == 1)
				{
					while (secondPlayer.firedField[x][y] != 0)
					{
						cout << "You have already shooted at this field. Try again." << endl;
						chooseFieldToShoot(x, y);
					}

					secondPlayer.firedField[x][y] = 3;
					hit = true;
					if (allShipsAreSunk(secondPlayer))
						endGame();

					printBattlefield(secondPlayer.firedField, "First player's turn");
					cout << "You hit! It's your turn again." << endl;
					system("Pause");
				}
				else
				{
					while (secondPlayer.firedField[x][y] != 0)
					{
						cout << "You have already shooted at this field. Try again." << endl;
						chooseFieldToShoot(x, y);
					}
					secondPlayer.firedField[x][y] = 2;
					hit = false;
					firstPlayerTurn = false;
					printBattlefield(secondPlayer.firedField, "First player's turn");
					cout << "You missed!" << endl;
					system("Pause");
				}
			}
		}
		else
		{
			hit = true;
			while (hit)
			{
				printBattlefield(firstPlayer.firedField, "Second player's turn");
				chooseFieldToShoot(x, y);
				if (firstPlayer.field[x][y] == 1)
				{
					while (firstPlayer.firedField[x][y] != 0)
					{
						cout << "You have already shooted at this field. Try again." << endl;
						chooseFieldToShoot(x, y);
					}

					firstPlayer.firedField[x][y] = 3;
					hit = true;
					if (allShipsAreSunk(firstPlayer))
						endGame();

					printBattlefield(firstPlayer.firedField, "Second player's turn");
					cout << "You hit! It's your turn again." << endl;
				}
				else
				{
					while (firstPlayer.firedField[x][y] != 0)
					{
						cout << "You have already shooted at this field. Try again." << endl;
						chooseFieldToShoot(x, y);
					}
					firstPlayer.firedField[x][y] = 2;
					hit = false;
					printBattlefield(firstPlayer.firedField, "Second player's turn");
					cout << "You missed!" << endl;
					system("Pause");
				}
			}
			firstPlayerTurn = true;
		}
	}
}

void chooseFieldToShoot(int& x, int& y)
{
	string chosedField, input;

	cout << "Choose field and shoot (letter then number of field):";
	cin >> input;

	chosedField = validateStartingFieldInput(input);
	getShipCoordinates(chosedField, x, y);
}

bool shipIsSunk(Player& player, const int x, const int y)
{
	char orientation = 'm'; //v-vertical h-horizontal
	if (player.firedField[x - 1][y] == 3 || player.field[x - 1][y] == 1 || player.firedField[x + 1][y] == 3 || player.field[x + 1][y] == 1)
		orientation = 'v';
	else if (player.firedField[x][y - 1] == 3 || player.field[x][y - 1] == 1 || player.firedField[x][y + 1] == 3 || player.field[x][y + 1] == 1)
		orientation = 'h';

	int startIndex = 0,
		tempX = x - 1,
		tempY = y - 1,
		temp = 0,
		shipLength = 1;
	bool isSunk = true;

	if (orientation == 'v')
	{
		startIndex = x;
		while (player.field[tempX][y] == 1)
		{
			startIndex = tempX;
			tempX--;
		}
		temp = startIndex;
		while (player.field[temp + 1][y] == 1)
		{
			shipLength++;
			temp++;
		}
		for (int i = startIndex; i < startIndex + shipLength; i++)
		{
			if (player.firedField[i][y] != 3)
			{
				isSunk = false;
				break;
			}
		}
	}
	else
	{
		startIndex = y;
		while (player.field[x][tempY] == 1 && tempY >= 0)
		{
			startIndex = tempY;
			tempY--;
		}
		temp = startIndex;
		while (player.field[x][temp + 1] == 1)
		{
			shipLength++;
			temp++;
		}
		for (int i = startIndex; i < startIndex + shipLength; i++)
		{
			if (player.firedField[x][i] != 3)
			{
				isSunk = false;
				break;
			}
		}
	}

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{

		}
	}

	if (isSunk)
		return true;
	else
		return false;
}

bool allShipsAreSunk(Player& player)
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			if (player.field[i][j] == 1)
			{
				if (player.firedField[i][j] != 3)
					return false;
			}
		}
	}
	return true;
}

void endGame()
{
	printTextInTheMiddleOfConsole("Congratulations!");

	string secondLine = "You Won!";

	int whiteSpaces = getConsoleWidth() / 2 + secondLine.size();
	cout << setw(whiteSpaces) << "You Won!" << endl;

	exit(-1);
}