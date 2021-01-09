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
void checkIfShipThisSizeCanBePlaced(int shipSize, const Fleet& fleet);
bool thisNumberOfShipsIsNotFull(int shipSize,const Fleet& fleet);
string validateStartingFieldInput(string input);
bool wrongFieldInput(string input);
void checkIfFieldIsUsed(int field[FIELD_SIZE][FIELD_SIZE], int& x, int& y, string& startingField);
char validateOrientationInput(string input);
bool positionIsPossible(int positions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], int shipSize, char orientation, int x, int y);
bool shipFitsInField(int field[FIELD_SIZE][FIELD_SIZE], int shipSize, char orientation, int x, int y);
char validateChoice(int options);