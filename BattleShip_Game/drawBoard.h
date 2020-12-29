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
* <file with drawing functions>
*
*/

#pragma once
#include "Constants.h"

void fillBattlefield(int array[FIELD_SIZE][FIELD_SIZE]);
//void drawField(int array[FIELD_SIZE][FIELD_SIZE]);
void printEmptyField();
void printHorizontalLines();
void printFirstLine();
void printLines();
void printLines(int array[FIELD_SIZE][FIELD_SIZE]);
void printPlayerOne();
void printPlayerTwo();
void symbol(int code);
void printLastLine();
void printLastLine(int array[FIELD_SIZE][FIELD_SIZE]);
void printLowerBorder();

