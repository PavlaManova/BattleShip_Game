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
* <file with functions for reading ship arrangements from txt file>
*
*/

#pragma once

#include <fstream>
#include "Constants.h"

using namespace std;

void readArrangementFromFile(ifstream& file, int &indexOfOption, int field[FIELD_SIZE][FIELD_SIZE]);
int findAllRandomArrangements(ifstream& file);
