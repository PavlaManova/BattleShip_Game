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

struct Fleet
{
	int smallShips = 4,
		mediumShips = 3,
		bigShips = 2,
		cruiserShips = 1,
		allShips = 0;
};

struct Player
{
	Fleet fleet;
	bool hasChosenBoard = false;
	int field[FIELD_SIZE][FIELD_SIZE] = { 0 };
	int firedField[FIELD_SIZE][FIELD_SIZE] = { 0 };
};

void startGame();
void arrangeYourself();
void placeShip(int field[FIELD_SIZE][FIELD_SIZE], int possiblePositions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE]);
void changeShip(int field[FIELD_SIZE][FIELD_SIZE], int possiblePositions[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE]);
void printUnusedShips(Fleet& fleet);
void chooseReadyArrangement();
void startPlaying();
void playerIsShootingAt(Player& player, string textAboveField);
bool shipIsSunk(Player& player, const int x, const int y);
void endGame();

