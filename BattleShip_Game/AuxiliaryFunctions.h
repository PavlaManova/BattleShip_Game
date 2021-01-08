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
* <file with helping functions>
*
*/

#pragma once
#include "Constants.h"
#include "GameLogic.h"

void positionConsoleWindow();
void getShipInformation(int& shipSize, string& startingField, char& orientation, int field[FIELD_SIZE][FIELD_SIZE], const Fleet& fleet);
void getShipCoordinates(string field, int& x, int& y);
void addShipToFleed(int shipSize, Fleet& fleet);
void fillImpossiblePositions(int positions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], int field[FIELD_SIZE][FIELD_SIZE]);