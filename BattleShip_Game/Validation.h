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
* <file with validation functions>
*
*/

#pragma once

#include <iostream>
#include "Constants.h"
#include "GameLogic.h"

using namespace std;

int validateShipSizeInput(string input);
string validateStartingFieldInput(string input);
char validateOrientationInput(string input);
bool wrongFieldInput(string input);
bool positionIsPossible(int positions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], int shipSize, char orientation, int x, int y);
bool canPlaceShipThisSize(int shipSize, Fleet& fleet);
bool shipFitsInField(int field[FIELD_SIZE][FIELD_SIZE], int shipSize, char orientation, int x, int y);