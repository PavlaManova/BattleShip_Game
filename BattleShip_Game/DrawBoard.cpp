#include "drawBoard.h"
#include "Constants.h"
#include <iostream>

using namespace std;

void fillBattlefield(int array[FIELD_SIZE][FIELD_SIZE])
{
	for (int i = 0; i < FIELD_SIZE; i++)
	{
		for (int j = 0; j < FIELD_SIZE; j++)
		{
			switch (array[i][j])
			{
			case 0: {
				cout << "  "; break;
			}
			case 1: {
				cout << "•"; break;
			}
			case 2: {
				cout << (char)219; break;
			}
			case 3: {
				cout << (char)176; break;
			}
			default: break;
			}
		}
		cout << endl;
	}
}

void drawEmptyField()
{
	firstLine();
	printLines();
}

void firstLine()
{
	cout << LEFT_UPPER_CORNER << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE;
	cout << DOUBLE_T << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE;

	for (int i = 0; i < FIELD_SIZE - 1; i++)
		cout << T_DOUBLE_UPPER << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE;
	cout << RIGHT_UPPER_CORNER << endl;

	cout << DOUBLE_VERTICAL_LINE << " \\ " << DOUBLE_VERTICAL_LINE << " " << (char)65 << " ";
	for (int i = 66; i < 65 + FIELD_SIZE; i++)
	{
		cout << VERTICAL_LINE << " " << (char)i << " ";
	}
	cout << DOUBLE_VERTICAL_LINE << endl;

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

void printLines()
{
	//Lines with numbers from 1 to 9
	for (int i = 1; i < FIELD_SIZE; i++)
	{
		cout << DOUBLE_VERTICAL_LINE << " " << i << " " << DOUBLE_VERTICAL_LINE << "   ";

		for (int j = 0; j < FIELD_SIZE - 1; j++)
		{
			cout << VERTICAL_LINE << "   ";
		}

		cout << DOUBLE_VERTICAL_LINE << endl;
		printHorizontalLines();
	}

	//Line 10
	cout << DOUBLE_VERTICAL_LINE << FIELD_SIZE << " " << DOUBLE_VERTICAL_LINE << "   ";

	for (int j = 0; j < FIELD_SIZE - 1; j++)
	{
		cout << VERTICAL_LINE << "   ";
	}

	cout << DOUBLE_VERTICAL_LINE << endl;

	cout << LEFT_LOWER_CORNER << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE
		<< DOUBLE_T_ROTATED << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE;
	for (int i = 0; i < FIELD_SIZE - 1; i++)
		cout << T_DOUBLE_UPPER_ROTATED << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE << DOUBLE_HORIZONTAL_LINE;
	cout << RIGHT_LOWER_CORNER << endl;

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