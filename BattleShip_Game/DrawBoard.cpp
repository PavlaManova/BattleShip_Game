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
* <file with functions for drawing game board>
*
*/

#include "drawBoard.h"
#include "Constants.h"
#include "AuxiliaryFunctions.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;

void printIndent()
{
	int whiteSpacesIndent = (getConsoleWidth() - BOARD_WIDTH) / 2 + 5;
	for (int i = 0; i < abs(whiteSpacesIndent); i++)
	{
		cout << " ";
	}
}

void printTextInTheMiddleOfConsole(string text)
{
	system("CLS");

	for (int i = 0; i < getConsoleHeight() / 2; i++)
		cout << endl;

	int whiteSpaces = getConsoleWidth() / 2 + (text.size() / 2);

	cout << setw(whiteSpaces) << text << endl;
}

void printPlayer(string text)
{
	int keyPressed,
		whiteSpaces;

	string secondLine = "Press Enter To Continue";

	printTextInTheMiddleOfConsole(text);

	whiteSpaces = getConsoleWidth() / 2 + secondLine.size() / 2;
	cout << endl << setw(whiteSpaces) << secondLine << endl;

	keyPressed = _getch();
	while (keyPressed != ENTER)
		keyPressed = _getch();
}

void printTextAboveField(string text)
{
	cout << endl;
	printIndent();
	text = ' ' + text + ' '; //append text for better visualization

	int sameCharacters = (BOARD_WIDTH - text.size()) / 2; //=
	for (int i = 0; i < sameCharacters; i++)
		cout << DOUBLE_HORIZONTAL_LINE;
	cout << text;

	if (text.size() % 2 == 0)
		sameCharacters++;

	for (int i = 0; i < sameCharacters; i++)
		cout << DOUBLE_HORIZONTAL_LINE;
	cout << endl;
}

void printBattlefield(int array[FIELD_SIZE][FIELD_SIZE], string text)
{
	system("CLS");
	printTextAboveField(text);
	printFirstLine();
	printLines(array);
	printLastLine(array);
}

void printFirstLine()
{
	printIndent();
	cout << LEFT_UPPER_CORNER << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE;
	cout << DOUBLE_T << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE;

	for (int i = 0; i < FIELD_SIZE - 1; i++)
		cout << T_DOUBLE_UPPER << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE;
	cout << RIGHT_UPPER_CORNER << endl;

	printIndent();

	cout << DOUBLE_VERTICAL_LINE << EMPTY_SPACE << DOUBLE_VERTICAL_LINE << " " << (char)65 << " ";
	for (int i = 66; i < 65 + FIELD_SIZE; i++)
	{
		cout << VERTICAL_LINE << " " << (char)i << " ";
	}
	cout << DOUBLE_VERTICAL_LINE << endl;

	printIndent();

	cout << DOUBLE_T_LEFT << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_CROSS;
	for (int i = 0; i < FIELD_SIZE * 3 - 4; i += 3)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << DOUBLE_HORIZONTAL_LINE;
		}
		cout << CROSS_DOUBLE_HORIZONRAL;
	}
	cout << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_T_RIGHT << endl;
}

void printLines(int array[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 0; i < FIELD_SIZE - 1; i++)
	{
		printIndent();
		cout << DOUBLE_VERTICAL_LINE << " " << i + 1 << " " << DOUBLE_VERTICAL_LINE;
		symbol(array[i][0]);

		for (int j = 0; j < FIELD_SIZE - 1; j++)
		{
			cout << VERTICAL_LINE;
			symbol(array[i][j + 1]);
		}

		cout << DOUBLE_VERTICAL_LINE << endl;
		printIndent();
		printHorizontalLines();
	}
}

void printHorizontalLines()
{
	cout << T_DOUBLE_UPPER_LEFT << HORIZONTAL_LINE << HORIZONTAL_LINE << HORIZONTAL_LINE << CROSS_DOUBLE_VERTICAL;
	for (int i = 0; i < (FIELD_SIZE - 1) * 3; i += 3)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << HORIZONTAL_LINE;
		}
		cout << CROSS;
	}
	cout << HORIZONTAL_LINE << HORIZONTAL_LINE << HORIZONTAL_LINE << T_DOUBLE_UPPER_RIGHT << endl;
}

void symbol(int code)
{
	char output[SINGLE_FIELD_SIZE + 1] = { 0 };
	output[SINGLE_FIELD_SIZE] = '\0';
	switch (code)
	{
	case 0: {
		cout << EMPTY_SPACE;
		break;
	}
	case 1: {
		cout << SHIP_SQUARE;
		break;
	}
	case 2: {
		cout << MISSED_SQUARE;
		break;
	}
	case 3: {
		cout << HIT_SHIP_SQUARE;
		break;
	}
	default:break;
	}
}

void printLastLine(int array[FIELD_SIZE][FIELD_SIZE])
{
	printIndent();
	cout << DOUBLE_VERTICAL_LINE << FIELD_SIZE << " " << DOUBLE_VERTICAL_LINE;
	symbol(array[FIELD_SIZE - 1][0]);

	for (int j = 0; j < FIELD_SIZE - 1; j++)
	{
		cout << VERTICAL_LINE;
		symbol(array[FIELD_SIZE - 1][j + 1]);
	}

	cout << DOUBLE_VERTICAL_LINE << endl;

	printLowerBorder();
}

void printLowerBorder()
{
	printIndent();
	cout << LEFT_LOWER_CORNER << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE
		<< DOUBLE_T_ROTATED << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE;
	for (int i = 0; i < FIELD_SIZE - 1; i++)
		cout << T_DOUBLE_UPPER_ROTATED << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE;
	cout << RIGHT_LOWER_CORNER << endl;
}