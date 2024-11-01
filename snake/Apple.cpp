#include "Apple.h"
#include <random>

Apple::Apple(int xstart, int ystart) {
	x = xstart;
	y = ystart;
	symbol = 'A';
}

void Apple::generateNewPosition(const Snake &player, int rows, int columns)
{
	while (true)
	{
		int row = rand() % rows;
		int column = rand() % columns;

		bool isOccupied = false;
		for (const auto &bodyPart : player.body) 
		{
			if (bodyPart.x == row && bodyPart.y == column) {
				isOccupied = true;
				break;
			}
		}
		if (!isOccupied) {
			x = row;
			y = column;
			return;
		}
	}
}