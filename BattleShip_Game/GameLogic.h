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
* <file with functions for game logic>
*
*/

#pragma once

#include "Constants.h"

using namespace std;

void startGame();
void arrangeYourself();
void placeShip(int field[FIELD_SIZE][FIELD_SIZE], int possiblePositions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE]);
void changeShip(int field[FIELD_SIZE][FIELD_SIZE]);

struct Fleet
{
	int smallShips = 4,
		midiumShips = 3,
		bigShips = 2,
		cruiserShips = 1,
		allShips = 0;
};