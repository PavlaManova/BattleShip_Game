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
void fillPossiblePositions(int positions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], int field[FIELD_SIZE][FIELD_SIZE]);
void changeShip(int field[FIELD_SIZE][FIELD_SIZE]);
void getShipInformation(int& shipSize, string& startingField, char& orientation, int field[FIELD_SIZE][FIELD_SIZE]);
void getShipCoordinates(string field, int& x, int& y);

struct Fleet
{
	int smallShips = 2,
		midiumShips = 3,
		bigShips = 4,
		cruiserShips = 6,
		allShips = 0;
};