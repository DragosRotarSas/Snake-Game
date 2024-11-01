#include <iostream>
#include <vector>
#include <conio.h>
#include <thread>
#include <chrono>
#include <queue>
#include <ctime>
#include <random>

#include "Snake.h"
#include "Apple.h"

using namespace std;

const int rows = 10;
const int colums = 20;
const int targetLength = 20;

char table[rows][colums];

void gameStart();
void initTable();
void gameInit(Apple &apple, Snake& player);

void addAppleToTable(Apple &apple);
void addPlayerToTable(Snake& player);

void displayCurrentLength(Snake& player);
void displayTable();

void draw(Apple& apple, Snake& player);

bool playerHasWon(Snake& player);

queue<char> inputBuffer;

void handleInput(Snake& player, atomic<bool>& running)
{
	while (running) 
	{
		if (_kbhit()) 
		{
			char direction = _getch();
			if (direction == 'w' || direction == 'W') {
				direction = 'N';
				inputBuffer.push(direction);
			}
			else if (direction == 'a' || direction == 'A') {
				direction = 'W';
				inputBuffer.push(direction);
			}
			else if (direction == 's' || direction == 'S') {
				direction = 'S';
				inputBuffer.push(direction);
			}
			else if (direction == 'd' || direction == 'D') {
				direction = 'E';
				inputBuffer.push(direction);
			}
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

int main()
{
	gameStart();
	Snake player(rows / 2, colums / 2);
	Apple apple(rows / 3, colums / 3);

	gameInit(apple, player);
	atomic<bool> running(true);
	thread inputThread(handleInput, ref(player), ref(running));

	while (true)
	{
		while (!inputBuffer.empty()) 
		{
			//check if the new direction is the same as the current one
			if (player.getDirection() == inputBuffer.front()) {
				inputBuffer.pop();
				continue;
			}

			//attempt to change the player's direction to the new one from the buffer
			if (player.tryDirectionChange(inputBuffer.front())) {
				inputBuffer.pop();
				break;
			}
			//the direction change was not possible
			else {
				inputBuffer.pop();
			}
		}

		player.move();
		if (player.checkCollision(rows, colums)) {
			running = false;
			break;
		}
		if (player.eatsApple(apple.x, apple.y)) {
			player.grow();
			apple.generateNewPosition(player, rows, colums);
		}

		draw(apple, player);
		this_thread::sleep_for(chrono::milliseconds(300));
	}

	inputThread.join();
	system("cls");
	if (playerHasWon(player)) {
		cout << "You have won!" << "\n" << "Congratulations!";
	}
	else {
		cout << "You have lost!";
	}
	return 0;
}

void gameStart()
{
	cout << "Control the snake using WASD.\nReach a length of at least 20 to win.\nPress any key to start the game!";
	char waitForButtonPress = _getch();
	system("cls");
}

void gameInit(Apple &apple, Snake& player)
{
	srand(time(nullptr));
	draw(apple, player);
}

void initTable()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < colums; j++)
		{
			table[i][j] = '_';
		}
	}
}

void addAppleToTable(Apple &apple)
{
	table[apple.x][apple.y] = apple.symbol;
}

void addPlayerToTable(Snake& player)
{
	for (auto bodyPart : player.body)
	{
		table[bodyPart.x][bodyPart.y] = bodyPart.symbol;
	}
}

void displayCurrentLength(Snake& player)
{
	cout << "Current length: " << player.getLength() << "\n";
}

void displayTable()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < colums; j++)
		{
			cout << table[i][j];
		}
		cout << "\n";
	}
}

void draw(Apple &apple, Snake &player)
{
	
	initTable();
	addAppleToTable(apple);
	addPlayerToTable(player);

	system("cls");
	displayCurrentLength(player);
	displayTable();
}

bool playerHasWon(Snake &player)
{
	return player.getLength() >= targetLength;
}