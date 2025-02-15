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
#include "drawBoard.h"
#include <conio.h>

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
	//input A1 -> the letter is for columns (index y); the number is for rows (index x)

	y = field[0] - 65; //from the ASCII code of the letter -> number between 0 and 9

	if (field.size() == 2)
	{
		x = field[1] - 49;
	}
	else
		x = 9; //A10 for example
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
	//clear the possible positions array because of the change ship option
	//when ship is placed its forbidden area can overlap with another ship's foribidden area

	for (int i = 0; i < POSITIONS_FIELD_SIZE; i++)
	{
		for (int j = 0; j < POSITIONS_FIELD_SIZE; j++)
			positions[i][j] = 0;
	}
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

void getArrayValue(int source[FIELD_SIZE][FIELD_SIZE], int destination[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			destination[i][j] = source[i][j];
		}
	}
}

void getShipsCount(Fleet& fleet, Player& player)
{
	//if the player has chosen to start with less than 10 ships

	Fleet tempFleet;
	player.fleet.smallShips = tempFleet.smallShips - fleet.smallShips;
	player.fleet.mediumShips = tempFleet.mediumShips - fleet.mediumShips;
	player.fleet.bigShips = tempFleet.bigShips - fleet.bigShips;
	player.fleet.cruiserShips = tempFleet.cruiserShips - fleet.cruiserShips;
	player.fleet.allShips = fleet.allShips;
}

void removeShipFromFleed(Fleet& fleet, int shipLength)
{
	switch (shipLength)
	{
	case 2:
	{
		fleet.smallShips++;
		break;
	}
	case 3:
	{
		fleet.mediumShips++;
		break;
	}
	case 4:
	{
		fleet.bigShips++;
		break;
	}
	case 6:
	{
		fleet.cruiserShips++;
		break;
	}
	default:
		break;
	}
	fleet.allShips--;
}

char getShipOrientation(Player& player, const int x, const int y)
{
	if (x - 1 >= 0)
	{
		if (x + 1 < FIELD_SIZE)
		{
			if (player.firedField[x - 1][y] == 3 || player.field[x - 1][y] == 1 || player.firedField[x + 1][y] == 3 || player.field[x + 1][y] == 1)
				return 'v';
		}
		else
		{
			if (player.firedField[x - 1][y] == 3 || player.field[x - 1][y] == 1)
				return 'v';
		}
	}
	else
	{
		if (player.firedField[x + 1][y] == 3 || player.field[x + 1][y] == 1)
			return 'v';
	}

	if (y - 1 >= 0)
	{
		if (y + 1 < FIELD_SIZE)
		{
			if (player.firedField[x][y - 1] == 3 || player.field[x][y - 1] == 1 || player.firedField[x][y + 1] == 3 || player.field[x][y + 1] == 1)
				return 'h';
		}
		else
		{
			if (player.firedField[x][y - 1] == 3 || player.field[x][y - 1] == 1)
				return 'h';
		}
	}
	else
	{
		if (player.firedField[x][y + 1] == 3 || player.field[x][y + 1] == 1)
			return 'h';
	}
}

void chooseFieldToShoot(int& x, int& y, int& previousX, int& previousY, bool& firstShot)
{
	string chosedField,
		input,
		rowNumber;

	bool fieldOutsideBoard = true;

	while (fieldOutsideBoard)
	{
		if (firstShot)
		{
			cout << "Choose field and shoot (letter then number of field):";
			cin >> input;
			chosedField = validateStartingFieldInput(input);
			getShipCoordinates(chosedField, x, y);
			previousX = x;
			previousY = y;
			firstShot = false;
			fieldOutsideBoard = false;
		}
		else
		{
			cout << "Choose field and shoot OR press the arrow in the direction you want:";

			int keyPressed = _getch();

			if (keyPressed == INTRODUCTION_CODE)
			{
				keyPressed = _getch();
				switch (keyPressed)
				{
				case ARROW_UP_KEY:
				{
					if (previousX == 0)
					{
						cout << "This field is outside the board. Try again." << endl;
					}
					else
					{
						x = previousX - 1;
						y = previousY;
						previousX = x;
						fieldOutsideBoard = false;
					}
					break;
				}
				case ARROW_DOWN_KEY:
				{
					if (previousX == FIELD_SIZE - 1)
					{
						cout << "This field is outside the board. Try again." << endl;
					}
					else
					{
						x = previousX + 1;
						y = previousY;
						previousX = x;
						fieldOutsideBoard = false;
					}
					break;
				}
				case ARROW_LEFT_KEY:
				{
					if (previousY == 0)
					{
						cout << "This field is outside the board. Try again." << endl;
					}
					else
					{
						x = previousX;
						y = previousY - 1;
						previousY = y;
						fieldOutsideBoard = false;
					}
					break;
				}
				case ARROW_RIGHT_KEY:
				{
					if (previousY == FIELD_SIZE - 1)
					{
						cout << "This field is outside the board. Try again." << endl;
					}
					else
					{
						x = previousX;
						y = previousY + 1;
						previousY = y;
						fieldOutsideBoard = false;
					}
					break;
				}
				default:
					break;
				}
			}
			else if ((keyPressed > 64 && keyPressed < 75) || (keyPressed > 96 && keyPressed < 107)) //if the key pressed is between A and J or a and j
			{
				cout << (char)keyPressed; //_getch() gets the code for the key that is pressed but the key value does not show on the console
										  //it is printed so that the player can see which field he has chosed 
				input = (char)keyPressed;
				cin >> rowNumber;
				input += rowNumber;
				chosedField = validateStartingFieldInput(input);
				getShipCoordinates(chosedField, x, y);
				previousX = x;
				previousY = y;
				fieldOutsideBoard = false;
			}
			else
			{
				fieldOutsideBoard = true;
			}
		}
	}
}

void chageFieldAroundSunkShip(Player& player, const char orientation, const int startIndex, const int x, const int y, const int shipLength)
{
	if (orientation == 'v')
	{
		for (int i = startIndex - 1; i < shipLength + 1 + startIndex; i++)
		{
			if (i >= 0 && i < FIELD_SIZE)
			{
				if (y - 1 >= 0)
					player.firedField[i][y - 1] = 2;
				if (y + 1 < FIELD_SIZE)
					player.firedField[i][y + 1] = 2;
			}
		}
		if (startIndex - 1 >= 0)
			player.firedField[startIndex - 1][y] = 2;
		if (startIndex + shipLength < FIELD_SIZE)
			player.firedField[startIndex + shipLength][y] = 2;
	}
	else
	{
		for (int i = startIndex - 1; i < shipLength + 1 + startIndex; i++)
		{
			if (i >= 0 && i < FIELD_SIZE)
			{
				if (x - 1 >= 0)
					player.firedField[x - 1][i] = 2;
				if (x + 1 < FIELD_SIZE)
					player.firedField[x + 1][i] = 2;
			}
		}
		if (startIndex - 1 >= 0)
			player.firedField[x][startIndex - 1] = 2;
		if (startIndex + shipLength < FIELD_SIZE)
			player.firedField[x][startIndex + shipLength] = 2;
	}
}

int clearShip(int field[FIELD_SIZE][FIELD_SIZE], int x, int y, const int n, const int m, int& shipLength)
{
	static const int dx[] = { 0,0,1,-1 };
	static const int dy[] = { 1,-1,0,0 };
	static const int numMoves = 4;

	//  Terminal checks
	// failure state:
	if (x < 0 || x >= m || y < 0 || y >= n)
	{
		// out of the array
		return -1;
	}

	if (field[x][y] == 0)
		return -1;

	//clear ship
	if (field[x][y] != 0)
	{
		field[x][y] = 0;
		shipLength++;
	}

	// Try recursively to find a way in any possible direction
	int pathLen = -1;
	for (int direction = 0; pathLen < 0 && direction < numMoves; ++direction)
	{
		pathLen = clearShip(field, x + dx[direction], y + dy[direction], n, m, shipLength);
	}
	return pathLen;
}

void playerCanStartPlaying(Player& firstPlayer, Player& secondPlayer, int field[FIELD_SIZE][FIELD_SIZE], Fleet& fleet)
{
	Fleet tempFleet;

	if (!firstPlayer.hasChosenBoard)
	{
		firstPlayer.hasChosenBoard = true;
		getArrayValue(field, firstPlayer.field);
		getShipsCount(fleet, firstPlayer);

		//clear fleet for second player
		fleet = tempFleet;
	}
	else
	{
		secondPlayer.hasChosenBoard = true;
		getArrayValue(field, secondPlayer.field);
		getShipsCount(fleet, secondPlayer);
	}
}