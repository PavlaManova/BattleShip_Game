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

/*enum Ship
{
	small = 2,
	midium = 3,
	big = 4,
	cruiser = 6
};

enum MyShipsCount
{
	small = 0,
	midium = 0,
	big = 0,
	cruiser=0
};

struct Ship
{
	int fileds;
	int counter;
};
*/

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
			//fillBattlefield(field);
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
	printEmptyField();
	int field[FIELD_SIZE][FIELD_SIZE] = { 0 };
	int countShips = 0;

	//while (countShips < 5)
	//{
		printBattlefield(field, "Your field");
		cout << "Chose one of the following options:" << endl;
		cout << "1) place next ship\n2) change position of some of your ships" << endl;//the third option - view board, is shown the whole time
		cout << "Choice: ";

		char choice;
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
			placeShip(field);
		}

		/*else
			changeShip(field);*/
	//}

}

void placeShip(int field[FIELD_SIZE][FIELD_SIZE])
{
	cout << "\"I want to place a ship with width:\"" << endl;
	int shipSize;
	cin >> shipSize;

	cout << "Choose starting field:";
	string startingField;
	char orientation;

}