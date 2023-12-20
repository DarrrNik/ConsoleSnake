#pragma once

#define MAP_WIDTH (19)
#define MAP_HEIGHT (10)
#define MAX_SNAKE_LEN ((MAP_WIDTH - 3) * (MAP_HEIGHT - 2))

#include <string>
#include <iostream>
#include <Windows.h>

typedef enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
} DRCT;

void PlaySnake();

void CursorToXY(int x, int y);