#include "Snake.h"

Snake::Snake(int xstart, int ystart)
{
	snakeBlock face(xstart, ystart, '>');
	body.push_back(face);
	length = 1;
	direction = 'E';
}

void Snake::move()
{
	//move every body part exept the head
	for (int i = body.size() - 1; i > 0; i--)
	{
		body[i] = body[i - 1];
	}

	//move the head in a direction
	switch (direction)
	{
	case 'N':
		body.front().x--;
		body.front().symbol = '^';
		break;
	case 'E':
		body.front().y++;
		body.front().symbol = '>';
		break;
	case 'S':
		body.front().symbol = 'v';
		body.front().x++;
		break;
	case 'W':
		body.front().symbol = '<';
		body.front().y--;
		break;

	default:
		break;
	}
}

void Snake::grow()
{
	snakeBlock back = body.back();
	move();
	body.push_back(back);
	length++;
}

bool Snake::checkCollision(int rows, int colums)
{
	//check if the snake's head has collided with the game borders
	if (body.front().x < 0 || body.front().x >= rows  ||
		body.front().y < 0 || body.front().y >= colums)
		return true;

	//check if the snake's head has collided with its own body
	for(int i = 1; i < body.size(); i++){ 
		if (body[i].x == body.front().x &&
			body[i].y == body.front().y)
			return true;
	}
	return false;
}

bool Snake::eatsApple(int applex, int appley)
{
	if (body.front().x == applex && body.front().y == appley)
		return true;
	return false;
}

bool Snake::tryDirectionChange(char direction)
{
	if (this->direction == 'N') {
		if (direction != 'S') {
			this->direction = direction;
			return true;
		}
	}
	else if (this->direction == 'E') {
		if (direction != 'W') {
			this->direction = direction;
			return true;
		}
	}
	else if (this->direction == 'S') {
		if (direction != 'N') {
			this->direction = direction;
			return true;
		}
	}
	else if (this->direction == 'W') {
		if (direction != 'E') {
			this->direction = direction;
			return true;
		}
	}
	return false;
}

int Snake::getLength() {
	return length;
}

char Snake::getDirection() {
	return direction;
}