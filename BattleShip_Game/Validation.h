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

using namespace std;

int validateShipSizeInput(string input);
string validateStartingFieldInput(string input);
char validateOrientationInput(string input);
bool wrongFieldInput(string input);