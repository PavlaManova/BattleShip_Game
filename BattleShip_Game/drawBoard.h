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

void printBattlefield(int array[FIELD_SIZE][FIELD_SIZE], string text);
void printTextAboveField(string text);
void printEmptyField();
void printHorizontalLines();
void printFirstLine();
void printLines(int array[FIELD_SIZE][FIELD_SIZE]);
void symbol(int code);
void printLastLine(int array[FIELD_SIZE][FIELD_SIZE]);
void printLowerBorder();

