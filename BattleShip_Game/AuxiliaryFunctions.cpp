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
* <file with implementation of helping functions>
*
*/

#include "AuxiliaryFunctions.h"
#include "Constants.h"

void getValue(int source[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE], int destination[FIELD_SIZE][FIELD_SIZE])
{
	int k = 0,
		l = 0;
	for (int i = 1; i < POSITIONS_FIELD_SIZE - 1; i++)
	{
		for (int j = 1; j < POSITIONS_FIELD_SIZE - 1; j++)
		{
			destination[k][l] = source[i][j];
			l++;
		}
		k++;
		l = 0;
	}
}

void print(int source[POSITIONS_FIELD_SIZE][POSITIONS_FIELD_SIZE])
{
	for (int i = 0; i < POSITIONS_FIELD_SIZE; i++)
	{
		for (int j = 0; j < POSITIONS_FIELD_SIZE; j++)
		{
			cout << source[i][j];
		}
		cout << endl;
	}
}