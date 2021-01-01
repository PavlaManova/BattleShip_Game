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
			//arrangeYourself();
			printEmptyField();
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
	
}