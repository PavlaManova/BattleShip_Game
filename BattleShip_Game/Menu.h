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
* <file with menu options functions>
*
*/

#pragma once

#include <iostream>
using namespace std;

void startingMenu();
void startGameOption();
void exitOption();
void setWhiteSpacesLength(string firstLine, string secondLine, int& whiteSpacesFirst, int& whiteSpacesSecond);
void setWhiteSpacesLength(string firstLine, string secondLine, string thirdLine, int& whiteSpacesFirst, int& whiteSpacesSecond, int& whiteSpacesThird);
void printOptions(string firstOption, string secondOption);
void printOptions(string firstOption, string secondOption, string thirdOption);
int arrangeShipsMenu();
void randomArrangementOption();
void playersArrangementOption();
void returnOption();
void printArrangementOptions(int options);
void printChooseRandomArrangementOptions();
int chooseRandomArrangement();