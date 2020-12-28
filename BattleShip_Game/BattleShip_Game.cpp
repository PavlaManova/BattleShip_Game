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

void startGameOption();
void exitOption();
void startingMenu();
void setWhiteSpacesLength(string firstLine, string secondLine, int& whiteSpacesFirst, int& whiteSpacesSecond);
void setWhiteSpacesLength(string firstLine, string secondLine, string thirdLine, int& whiteSpacesFirst, int& whiteSpacesSecond, int& whiteSpacesThird);
void printOptions(string firstOption, string secondOption);
void printOptions(string firstOption, string secondOption, string thirdOption);
void arrangeShipsMenu();
void randomArrangementOption();
void playersArrangementOption();
void returnOption();

int main()
{

	startingMenu();
	//ADD ---chose player option---
	arrangeShipsMenu();

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
	setWhiteSpacesLength(firstOption, secondOption,thirdOption, whiteSpacesFirst, whiteSpacesSecond,whiteSpacesThird);
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

void startingMenu()
{
	startGameOption();

	int choice = _getch(),
		temp = 2;

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
}

void arrangeShipsMenu() //ADD ---return option---
{
	system("CLS");
	randomArrangementOption();
	int choice = _getch(),
		temp = 0;

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
			randomArrangementOption();
		}
		else if(temp%3==1)
		{
			system("CLS");
			playersArrangementOption();
		}
		else
		{
			system("CLS");
			returnOption();
		}

		choice = _getch();
	}
}

void randomArrangementOption()
{
	printOptions(">Choose random positions for your ships<", "Arrange your ships","Return");
}

void playersArrangementOption()
{
	printOptions("Choose random positions for your ships", ">Arrange your ships<","Return");
}

void returnOption()
{
	printOptions("Choose random positions for your ships", "Arrange your ships", ">Return<");
}
