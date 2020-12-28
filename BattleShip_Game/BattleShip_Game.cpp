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
* <предназначение на файла>
*
*/


#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

const int MIDDLE_CONSOLE = 60;
const int FIELD_SIZE = 10;

void startGameOption();
void exitOption();
int startingMenu();
void setWhiteSpacesLength(string firstLine, string secondLine, int& whiteSpacesFirst, int& whiteSpacesSecond);
void setWhiteSpacesLength(string firstLine, string secondLine, string thirdLine, int& whiteSpacesFirst, int& whiteSpacesSecond, int& whiteSpacesThird);
void printOptions(string firstOption, string secondOption);
void printOptions(string firstOption, string secondOption, string thirdOption);
int arrangeShipsMenu();
void randomArrangementOption();
void playersArrangementOption();
void returnOption();


// 0 - empty field
// 1 - field that had been shoted at but empty
// 2 - ship
// 3 - shoted ship

void fillBattlefield(int array[FIELD_SIZE][FIELD_SIZE]);
void drawEmptyField();
void printLine();

int main()
{
	/*int actionCode = 0;
	actionCode = startingMenu();
	//ADD ---chose player option---
	while (actionCode == 1)
	{
		actionCode = arrangeShipsMenu();
		switch (actionCode)
		{
		case 0:
		{
			//ADD ---reading positions from file---
			break;
		}
		case 1:
		{
			//ADD ---arrange yourself---
			break;
		}
		case 2:
		{
			actionCode=startingMenu(); //Option "Return"
			break;
		}
		default: break;
		}
	}*/
	/*int field[FIELD_SIZE][FIELD_SIZE] =
	{
		{2,2,0,2,0,0,2,2,2,2},
		{0,0,0,1,0,0,0,0,0,0},
		{2,0,0,2,0,2,2,2,0,2},
		{2,0,1,0,0,0,0,0,0,2},
		{2,0,0,0,0,1,1,0,0,0},
		{2,1,0,0,0,2,0,1,0,3},
		{0,0,0,1,0,2,0,0,0,3},
		{3,3,0,0,0,0,0,1,0,2},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,2,2,2,2,2,2}
	};*/
	//fillBattlefield(field);

	drawEmptyField();
}

void setWhiteSpacesLength(string firstLine, string secondLine, int& whiteSpacesFirst, int& whiteSpacesSecond)
{
	whiteSpacesFirst = MIDDLE_CONSOLE + (firstLine.size() / 2);

	int temp = firstLine.size() - secondLine.size();
	if (secondLine.size() % 2 == 1)
		temp++;

	whiteSpacesSecond = whiteSpacesFirst - temp / 2;
}

void setWhiteSpacesLength(string firstLine, string secondLine, string thirdLine, int& whiteSpacesFirst, int& whiteSpacesSecond, int& whiteSpacesThird)
{
	whiteSpacesFirst = MIDDLE_CONSOLE + (firstLine.size() / 2);

	int temp = firstLine.size() - secondLine.size();
	if (secondLine.size() % 2 == 1)
		temp++;

	whiteSpacesSecond = whiteSpacesFirst - temp / 2;

	temp = firstLine.size() - thirdLine.size();
	if (thirdLine.size() % 2 == 1)
		temp++;
	whiteSpacesThird = whiteSpacesFirst - temp / 2;
}

void printOptions(string firstOption, string secondOption)
{
	cout << "\n\n\n\n\n\n\n\n\n";
	int whiteSpacesFirst = 0, whiteSpacesSecond = 0;
	setWhiteSpacesLength(firstOption, secondOption, whiteSpacesFirst, whiteSpacesSecond);
	cout << setw(whiteSpacesFirst) << firstOption << endl;
	cout << setw(whiteSpacesSecond) << secondOption << endl;
}

void printOptions(string firstOption, string secondOption, string thirdOption)
{
	cout << "\n\n\n\n\n\n\n\n\n";
	int whiteSpacesFirst = 0, whiteSpacesSecond = 0, whiteSpacesThird = 0;
	setWhiteSpacesLength(firstOption, secondOption, thirdOption, whiteSpacesFirst, whiteSpacesSecond, whiteSpacesThird);
	cout << setw(whiteSpacesFirst) << firstOption << endl;
	cout << setw(whiteSpacesSecond) << secondOption << endl;
	cout << setw(whiteSpacesThird) << thirdOption << endl;
}

void startGameOption()
{
	printOptions(">New Game<", "Exit");
}

void exitOption()
{
	printOptions("New Game", ">Exit<");
}

int startingMenu()
{
	system("CLS");
	startGameOption();

	int choice = _getch(),
		temp = 0;

	bool endGame = false;
	while (choice != 13) // Enter - choice is made
	{
		switch (choice)
		{
		case 80:
		{
			temp++;
			break;
		}
		case 72:
		{
			temp--;
			break;
		}
		default: break;
		}

		if (temp % 2 == 0)
		{
			system("CLS");
			startGameOption();
			endGame = false;
		}
		else
		{
			system("CLS");
			exitOption();
			endGame = true;
		}

		choice = _getch();
	}

	if (endGame)
		exit(-1);
	else
		return 1;
}

int arrangeShipsMenu() //ADD ---return option---
{
	system("CLS");
	randomArrangementOption();
	int choice = _getch(),
		temp = 0,
		chosenActionCode = 0;

	while (choice != 13) // Enter - choice is made
	{
		switch (choice)
		{
		case 80:
		{
			temp++;
			break;
		}
		case 72:
		{
			temp--;
			break;
		}
		default: break;
		}

		if (temp % 3 == 0)
		{
			system("CLS");
			chosenActionCode = 0;
			randomArrangementOption();
		}
		else if (temp % 3 == 1)
		{
			system("CLS");
			chosenActionCode = 1;
			playersArrangementOption();
		}
		else
		{
			system("CLS");
			chosenActionCode = 2;
			returnOption();
		}

		choice = _getch();
	}
	return chosenActionCode;
}

void randomArrangementOption()
{
	printOptions(">Choose random positions for your ships<", "Arrange your ships", "Return");
}

void playersArrangementOption()
{
	printOptions("Choose random positions for your ships", ">Arrange your ships<", "Return");
}

void returnOption()
{
	printOptions("Choose random positions for your ships", "Arrange your ships", ">Return<");
}

void fillBattlefield(int array[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			switch (array[i][j])
			{
			case 0: {
				cout << "  "; break;
			}
			case 1: {
				cout << "Х"; break;
			}
			case 2: {
				cout << (char)219; break;
			}
			case 3: {
				cout << (char)176; break;
			}
			default: break;
			}
		}
		cout << endl;
	}
}

void drawEmptyField()
{
	//first line
	cout << (char)201 << (char)205 << (char)205 << (char)205;
	for (int i = 0; i < FIELD_SIZE; i++)
		cout << (char)209 << (char)205 << (char)205 << (char)205;
	cout << (char)187 << endl;

	//second line
	cout << (char)186 << " \\ ";
	for (int i = 65; i < 65 + FIELD_SIZE; i++)
	{
		cout << (char)179 << " " << (char)i << " ";
	}
	cout << (char)186 << endl;

	//print line
	printLine();

	for (int i = 1; i < FIELD_SIZE; i++)
	{
		cout << (char)186 << " " << i << " ";

		for (int j = 0; j < FIELD_SIZE; j++)
		{
			cout << (char)179 << "   ";
		}

		cout << (char)186 << endl;
		printLine();
	}


	cout << (char)186 << FIELD_SIZE << " ";

	for (int j = 0; j < FIELD_SIZE; j++)
	{
		cout << (char)179 << "   ";
	}

	cout << (char)186 << endl;

	cout << (char)200 << (char)205 << (char)205 << (char)205;
	for (int i = 0; i < FIELD_SIZE; i++)
		cout << (char)207 << (char)205 << (char)205 << (char)205;
	cout << (char)188 << endl;
}

void printLine()
{
	cout << (char)199;
	for (int i = 0; i < FIELD_SIZE * 3 ; i+=3)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << (char)196;
		}
		cout << (char)197;
	}
	cout << (char)196 << (char)196 << (char)196<< (char)182<<endl;
}
