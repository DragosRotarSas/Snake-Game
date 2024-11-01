#pragma once

#include "Snake.h"

class Apple
{
public:
	int x, y;
	char symbol;

	Apple(int xstart, int ystart);

	void generateNewPosition(const Snake &player, int rows, int colums);
};