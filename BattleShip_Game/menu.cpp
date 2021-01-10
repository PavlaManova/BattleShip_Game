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
* <file with declaration of menu functions>
*
*/

#include "Menu.h"
#include "Constants.h"
#include <conio.h>
#include <iomanip>
#include "AuxiliaryFunctions.h" //for concole window height and width

void startingMenu()
{
	system("CLS");
	startGameOption();

	int choice = _getch(),
		temp = 0;

	if (choice == INTRODUCTION_CODE) //ignore code 224 ("introduction code") that _getch() returns first when arrow key is pressed
		choice = _getch();

	bool endGame = false;

	while (choice != ENTER) // choice is made
	{
		if (choice == ARROW_DOWN_KEY)
			temp++;
		else if (choice == ARROW_UP_KEY)
			temp--;

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
		if (choice == INTRODUCTION_CODE)
			choice = _getch();
	}

	if (endGame)
		exit(0);
	else
		return;
}

int arrangeShipsMenu() //ADD ---return option---
{
	system("CLS");
	randomArrangementOption();
	int choice = _getch(),
		temp = 0,
		chosenActionCode = 0;

	if (choice == INTRODUCTION_CODE)
		choice = _getch();

	while (choice != ENTER) // Enter - choice is made
	{
		if (choice == ARROW_DOWN_KEY)
			temp++;
		else if (choice == ARROW_UP_KEY)
			temp--;

		if (abs(temp) % 3 == 0)
		{
			system("CLS");
			chosenActionCode = 0;
			randomArrangementOption();
		}
		else if (abs(temp) % 3 == 1)
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
		if (choice == INTRODUCTION_CODE)
			choice = _getch();
	}
	return chosenActionCode;
}

void setWhiteSpacesLength(string firstLine, string secondLine, int& whiteSpacesFirst, int& whiteSpacesSecond)
{
	whiteSpacesFirst = getConsoleWidth() / 2 + (firstLine.size() / 2);

	int temp = firstLine.size() - secondLine.size();
	if (secondLine.size() % 2 == 1)
		temp++;

	whiteSpacesSecond = whiteSpacesFirst - temp / 2;
}

void setWhiteSpacesLength(string firstLine, string secondLine, string thirdLine, int& whiteSpacesFirst, int& whiteSpacesSecond, int& whiteSpacesThird)
{
	whiteSpacesFirst = getConsoleWidth() / 2 + (firstLine.size() / 2);

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
	for (int i = 0; i < getConsoleHeight() / 2; i++)
		cout << endl;

	int whiteSpacesFirst = 0, whiteSpacesSecond = 0;
	setWhiteSpacesLength(firstOption, secondOption, whiteSpacesFirst, whiteSpacesSecond);
	cout << setw(whiteSpacesFirst) << firstOption << endl << endl;
	cout << setw(whiteSpacesSecond) << secondOption << endl;
}

void printOptions(string firstOption, string secondOption, string thirdOption)
{
	for (int i = 0; i < getConsoleHeight() / 2; i++)
		cout << endl;
	int whiteSpacesFirst = 0, whiteSpacesSecond = 0, whiteSpacesThird = 0;
	setWhiteSpacesLength(firstOption, secondOption, thirdOption, whiteSpacesFirst, whiteSpacesSecond, whiteSpacesThird);
	cout << setw(whiteSpacesFirst) << firstOption << endl << endl;
	cout << setw(whiteSpacesSecond) << secondOption << endl << endl;
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

void printArrangementOptions(int options)
{
	if (options == 4)
		cout << "You have enough ships to start the game now.\n" << endl;
	cout << "Chose one of the following options:" << endl;
	cout << "1) place next ship" << endl;
	cout << "2) change position of some of your ships" << endl;
	cout << "3) check how many ships you have left to place on the board" << endl; //the fourth option - view board, is shown the whole time	
	if (options == 4)
	{
		cout << "4) start game" << endl;
	}
	cout << "Choice: ";
}

void printChooseRandomArrangementOptions()
{
	cout << "<-Privious";
	int whiteSpaces = (getConsoleWidth() - 25) / 2;
	for (int i = 0; i < whiteSpaces; i++)
		cout << " ";
	cout << "Choose - Enter";
	for (int i = 0; i < whiteSpaces; i++)
		cout << " ";
	cout << "Next->";
}

int chooseRandomArrangement()
{
	int choice = _getch();
	if (choice == INTRODUCTION_CODE)
		choice = _getch();

	switch (choice)
	{
	case ARROW_RIGHT_KEY:
	{
		return 1;
		break;
	}
	case ARROW_LEFT_KEY:
	{
		return (-1);
	}
	case ENTER:
	{
		return 0;
		break;
	}
	default:
		break;
	}
}
