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
* <предназначение на файла>
*
*/


#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

void firstOption()
{
	cout << "           >Option 1<             " << endl;
	cout << "            Option 2              " << endl;
	cout << "            Option 3              " << endl;
}

void secondOption()
{
	cout << "            Option 1              " << endl;
	cout << "           >Option 2<             " << endl;
	cout << "            Option 3              " << endl;
}

void thirdOption()
{
	cout << "            Option 1             " << endl;
	cout << "            Option 2             " << endl;
	cout << "           >Option 3<            " << endl;
}



int main()
{

	firstOption();

	int choice = _getch();    
	int temp = 3;   

	while (choice != 13) // Enter - choice is made
	{
		switch (choice)
		{
		case 80:
		{
			temp++;
			break;
		}
		case 72:
		{
			temp--;
			break;
		}
		default: break;
		}

		if (temp % 3 == 0)
		{
			system("CLS");
			firstOption();
		}
		else if (temp % 3 == 1)
		{
			system("CLS");
			secondOption();
		}
		else
		{
			system("CLS");
			thirdOption();
		}

		choice = _getch();

	}

}
