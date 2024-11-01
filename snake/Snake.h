#pragma once

#include <vector>

using namespace std;

class snakeBlock
{
public :
	int x, y;
	char symbol;
	snakeBlock(int x, int y, char symbol) {
		this->x = x;
		this->y = y;
		this->symbol = symbol;
	}
};

class Snake
{
private:
	int length;
	char direction;
	
public:
	vector<snakeBlock> body;

	Snake(int xstart, int ystart);
	
	void move();
	bool checkCollision(int rows, int colums);

	void grow();
	bool eatsApple(int applex, int appley);

	bool tryDirectionChange(char direction);

	char getDirection();
	int getLength();
};