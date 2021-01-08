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
* <file with constants>
*
*/

#pragma once
#include <iostream>

using namespace std;

const int FIELD_SIZE = 10,

		  POSITIONS_FIELD_SIZE = FIELD_SIZE + 2,

		  //MIDDLE_CONSOLE = 60,

		  SINGLE_FIELD_SIZE = 3,

		  BOARD_WIDTH = 45,

		  MAX_SHIPS_COUNT = 10,

		  ARROW_UP_KEY = 72,

		  ARROW_DOWN_KEY = 80,
		  
		  INTRODUCTION_CODE=224;


//char codes used for drawing the board
const char DOUBLE_VERTICAL_LINE = (char)186,
		   DOUBLE_HORIZONTAL_LINE = (char)205,
		   RIGHT_UPPER_CORNER = (char)187,
		   LEFT_UPPER_CORNER = (char)201,
		   LEFT_LOWER_CORNER = (char)200,
		   RIGHT_LOWER_CORNER = (char)188,
		   HORIZONTAL_LINE = (char)196,
		   VERTICAL_LINE = (char)179,
		   DOUBLE_T = (char)203,
		   T_DOUBLE_UPPER = (char)209,
		   DOUBLE_T_LEFT = (char)204,
		   DOUBLE_CROSS = (char)206,
		   CROSS_DOUBLE_HORIZONRAL = (char)216,
		   DOUBLE_T_RIGHT = (char)185,
		   DOUBLE_T_ROTATED = (char)202,
		   T_DOUBLE_UPPER_ROTATED = (char)207,
		   T_DOUBLE_UPPER_LEFT = (char)199,
		   CROSS_DOUBLE_VERTICAL = (char)215,
		   CROSS = (char)197,
		   T_DOUBLE_UPPER_RIGHT = (char)182,
		   SOLID_RECTANGLE = (char)219;

const string EMPTY_SPACE = "   ";

//char arrays used for drawing the fields on the board
const char SHIP_SQUARE[] = { SOLID_RECTANGLE, SOLID_RECTANGLE, SOLID_RECTANGLE },
		   MISSED_SQUARE[] = { ' ','o',' ' },
		   HIT_SHIP_SQUARE[] = { ' ','X',' ' };

//int MIDDLE_CONSOLE = 0;


