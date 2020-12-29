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
#include "drawBoard.h"

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

