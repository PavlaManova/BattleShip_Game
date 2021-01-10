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
* <file with implementation of helping functions>
*
*/

#include "AuxiliaryFunctions.h"
#include "Constants.h"
#include "GameLogic.h"
#include "Validation.h"
#include <Windows.h> //for positioning the console window

int consoleWidth = 0;
int consoleHeight = 0;

void positionConsoleWindow()
{
	//Finding the user's screen resolution
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//the new sizes of console window -> proportional
	consoleWidth = 9 * screenWidth / 10;
	consoleHeight = 4 * screenHeight / 5;

	//centrate window by adding equal indentation on all four sides of the screen
	int indentWidth = (screenWidth - consoleWidth) / 2;
	int indentHeight = (screenHeight - consoleHeight) / 2;

	HWND hwnd = GetConsoleWindow();
	MoveWindow(hwnd, indentWidth, indentHeight, consoleWidth, consoleHeight, TRUE);
}

int getConsoleWidth()
{
	return consoleWidth / 8; //returns the size in characters (console width 8 ~ 1 char width)
}

int getConsoleHeight()
{
	return consoleHeight / 20; //returns the size in characters (console height 20 ~ 1 char height)
}

void getPlaceShipInfo(int& shipSize, string& startingField, char& direction, int field[FIELD_SIZE][FIELD_SIZE], const Fleet& fleet)
{
	string input;
	cout << "Choose the size of the ship (2, 3, 4 or 6):";
	cin >> input;
	shipSize = validateShipSizeInput(input);

	checkIfShipThisSizeCanBePlaced(shipSize, fleet);


	cout << "Choose starting field (letter then number of field):";
	cin >> input;
	startingField = validateStartingFieldInput(input);

	int x, y;
	getShipCoordinates(startingField, x, y);

	checkIfFieldIsUsed(field, x, y, startingField);

	cout << "Choose a direction for the ship. Choose between (U)p, (D)own, (L)eft, (R)ight:";
	cin >> input;
	direction = validateDirectionInput(input);
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

void getChangeShipInfo(int field[FIELD_SIZE][FIELD_SIZE], const Fleet& fleet, int& x, int& y)
{
	string shipField, input;

	cout << "Choose one field from the ship you want to change (letter then number of field):";
	cin >> input;
	shipField = validateStartingFieldInput(input);

	getShipCoordinates(shipField, x, y);

	while (!(field[x][y] == 1))
	{
		cout << "There is no ship on this position. Try again." << endl;
		cin >> input;
		shipField = validateStartingFieldInput(input);
		getShipCoordinates(shipField, x, y);
	}
}

void fillImpossiblePositions(int positions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], int field[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 1; i < FIELD_SIZE + 1; i++)
	{
		for (int j = 1; j < FIELD_SIZE + 1; j++)
		{
			if (field[i - 1][j - 1] == 1) //there is ship
			{
				//make an area with impossible fields to place another ship
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

void addShipToFleed(int shipSize, Fleet& fleet)
{
	switch (shipSize)
	{
	case 2:
	{
		fleet.smallShips--;
		break;
	}
	case 3:
	{
		fleet.mediumShips--;
		break;
	}
	case 4:
	{
		fleet.bigShips--;
		break;
	}
	case 6:
	{
		fleet.cruiserShips--;
		break;
	}
	default:
		break;
	}

	fleet.allShips++;
}

void clearShip(int field[FIELD_SIZE][FIELD_SIZE], int possiblePositions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], const int x, const int y)
{
	char direction;
	int tempField[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE];
	getArrayValueWithSqaureOfZeroes(field, tempField); // to eliminate the checks for going outside the array

	int tempX = x + 1,
		tempY = y + 1;
	cout << x << " - " << y << endl;
	field[x][y] = 0;

	while (tempField[tempX - 1][y + 1] == 1 || tempField[tempX + 1][y + 1] == 1 || tempField[x + 1][tempY - 1] == 1 || tempField[x + 1][tempY + 1] == 1)
	{
		/*tempX = x + 1;
		tempY = y + 1;*/

		tempField[tempX][tempY] = 0;
		field[x][y] = 0;
		possiblePositions[tempX - 1][y] = 0;
		possiblePositions[tempX - 1][y + 1] = 0;
		possiblePositions[tempX - 1][y + 2] = 0;
		possiblePositions[x][tempY - 1] = 0;
		possiblePositions[x + 1][tempY - 1] = 0;
		possiblePositions[x + 2][tempY - 1] = 0;
		possiblePositions[tempX + 1][y] = 0;
		possiblePositions[tempX + 1][y + 1] = 0;
		possiblePositions[tempX + 1][y + 2] = 0;
		possiblePositions[x][tempY + 1] = 0;
		possiblePositions[x + 1][tempY + 1] = 0;
		possiblePositions[x + 2][tempY + 1] = 0;

		while (tempField[tempX - 1][y + 1] == 1)
		{
			field[tempX - 2][y] = 0;
			/*possiblePositions[tempX - 1][y] = 0;
			possiblePositions[tempX - 1][y + 1] = 0;
			possiblePositions[tempX - 1][y + 2] = 0;*/

			possiblePositions[tempX - 2][y] = 0;
			possiblePositions[tempX - 2][y + 1] = 0;
			possiblePositions[tempX - 2][y + 2] = 0;

			possiblePositions[tempX ][y] = 0;
			possiblePositions[tempX ][y + 1] = 0;
			possiblePositions[tempX ][y + 2] = 0;

			possiblePositions[x][tempY - 1] = 0;
			possiblePositions[x + 1][tempY - 1] = 0;
			possiblePositions[x + 2][tempY - 1] = 0;
			possiblePositions[x][tempY + 1] = 0;
			possiblePositions[x + 1][tempY + 1] = 0;
			possiblePositions[x + 2][tempY + 1] = 0;




			tempField[tempX - 1][y + 1] == 0;
			tempX--;
			cout << 1;
		}
		tempX = x + 1;
		while (tempField[tempX + 1][y + 1] == 1)
		{
			field[tempX - 1][y] = 0;
			possiblePositions[tempX + 1][y] = 0;
			possiblePositions[tempX + 1][y + 1] = 0;
			possiblePositions[tempX + 1][y + 2] = 0;
			tempField[tempX + 1][y + 1] == 0;
			tempX++;
			cout << 2;
		}

		while (tempField[x + 1][tempY - 1] == 1)
		{
			field[x][tempY - 1] = 0;
			possiblePositions[x + 1][tempY - 1] = 0;
			possiblePositions[x + 2][tempY - 1] = 0;
			possiblePositions[x + 3][tempY - 1] = 0;
			tempField[x + 1][tempY - 1] == 0;
			tempY--;
			cout << 3;
		}
		tempY = y + 1;
		while (tempField[x + 1][tempY + 1] == 1)
		{
			field[x][tempY] = 0;
			possiblePositions[x + 1][tempY + 1] = 0;
			possiblePositions[x + 2][tempY + 1] = 0;
			possiblePositions[x + 3][tempY + 1] = 0;
			tempField[x + 1][tempY + 1] == 0;
			tempY++;
			cout << 4;
		}
		tempX = x + 1;
		tempY = y + 1;
	}
}

void getArrayValueWithSqaureOfZeroes(int source[FIELD_SIZE][FIELD_SIZE], int destination[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE])
{
	//make a frame of zeroes
	for (int j = 0; j < POSITIONS_FIELD_SIZE; j++)
	{
		destination[0][j] = 0;
		destination[POSITIONS_FIELD_SIZE - 1][j] = 0;
		destination[j][0] = 0;
		destination[j][POSITIONS_FIELD_SIZE - 1] = 0;
	}

	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			destination[i + 1][j + 1] = source[i][j];
		}
	}
}