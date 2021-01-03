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
* <file with implementation of validation functions>
*
*/

#include "Validation.h"
#include <iostream>

using namespace std;

int validateShipSizeInput(string input)
{
	while (input.size() != 1)
	{
		cout << "Incorect input. Try again with one of the numbers 2, 3, 4, 6:";
		cin >> input;
	}

	while (input[0] != '2' && input[0] != '3' && input[0] != '4' && input[0] != '6')
	{
		cout << "Incorect input. Try again with one of the numbers 2, 3, 4, 6:";
		cin >> input;
		while (input.size() != 1)
		{
			cout << "Incorect input. Try again with one of the numbers 2, 3, 4, 6:";
			cin >> input;
		}
	}

	return (int)input[0] - 48; //returns the int value of the input '2' -> 2
}

string validateStartingFieldInput(string input)
{
	//---make bool function that returns true if all three are correct - input size is 2; first char is letter; second char is number 
	//---EXCEPTION when field is 10
	//---while the bool function is false cin input - one or more is incorect and call the function again
	//ADD validation with space between letter and number

	while (wrongFieldInput(input))
	{
		cout << "Incorect input. Try again with something like J3:";
		cin >> input;
	}

	return input;

}

bool wrongFieldInput(string input)
{
	if (input.size() != 2)
	{
		//Exception for field 10
		if (input.size() != 3)
			return true;
		else if (input[1] == '1' && input[2] == '0')
		{
			if ((input[0] < 'A' || input[0]>'J') && (input[0] < 'a' || input[0]>'j'))
				return true;
			else return false;
		}
		else
			return true;
	}
	else if ((input[0] < 'A' || input[0]>'J') && (input[0] < 'a' || input[0]>'j'))
		return true;
	else if (input[1] < '1' || input[1] > '9')
		return true;
	else
		return false;
}

char validateOrientationInput(string input)
{
	while (input.size() != 1)
	{
		cout << "Incorect input. Try again with one of the letters U, D, L, R:";
		cin >> input;
	}

	while (input[0] != 'U' && input[0] != 'u' && input[0] != 'D' && input[0] != 'd' && input[0] != 'L' && input[0] != 'l' && input[0] != 'R' && input[0] != 'r')
	{
		cout << "Incorect input. Try again with one of the letters U, D, L, R:";
		cin >> input;
		while (input.size() != 1)
		{
			cout << "Incorect input. Try again with one of the letters U, D, L, R:";
			cin >> input;
		}
	}

	return input[0];
}