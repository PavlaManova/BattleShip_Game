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
int getConsoleWidth();
int getConsoleHeight();
void getPlaceShipInfo(int& shipSize, string& startingField, char& direction, int field[FIELD_SIZE][FIELD_SIZE], const Fleet& fleet);
void getShipCoordinates(string field, int& x, int& y);
void getChangeShipInfo(int field[FIELD_SIZE][FIELD_SIZE], const Fleet& fleet, int& x, int& y);
void addShipToFleed(int shipSize, Fleet& fleet);
void removeShipFromFleed(Fleet& fleet, int shipLength);
void fillImpossiblePositions(int positions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], int field[FIELD_SIZE][FIELD_SIZE]);
void getArrayValueWithSqaureOfZeroes(int source[FIELD_SIZE][FIELD_SIZE], int destination[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE]);
void getArrayValue(int source[FIELD_SIZE][FIELD_SIZE], int destination[FIELD_SIZE][FIELD_SIZE]);
void getShipsCount(Fleet& fleet, Player& player);
void chageFieldAroundSunkShip(Player& player, const char orientation, const int startIndex, const int otherCoordinate, const int shipLength);
int clearShip(int field[FIELD_SIZE][FIELD_SIZE], int x, int y, const int n, const int m, int& shipLength);
void playerCanStartPlaying(Player& firstPlayer, Player& secondPlayer, int field[FIELD_SIZE][FIELD_SIZE], Fleet& fleet);