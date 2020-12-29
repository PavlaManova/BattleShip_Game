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
//#include <stdlib.h>
#include "drawBoard.h"
#include "Constants.h"
#include "Menu.h"

using namespace std;

int main()
{
	/*int actionCode = 0;
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
	int field[FIELD_SIZE][FIELD_SIZE] =
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
	};
	fillBattlefield(field);

	//printEmptyField();
}


