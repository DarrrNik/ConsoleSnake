#include "ConsoleSnake.h"

std::string _map = 
	"##################\n"
	"#                #\n"
	"#                #\n"
	"#                #\n"
	"#                #\n"
	"#                #\n"
	"#                #\n"
	"#                #\n"
	"#                #\n"
	"##################\n" 
;

DRCT snkDir = RIGHT;

bool isGame = true;

int snkX[MAX_SNAKE_LEN] = { (MAP_WIDTH - 2) / 2 };
int snkY[MAX_SNAKE_LEN] = { (MAP_HEIGHT - 1) / 2 };
int snkLen = 1;
char snkSymb = 'O';


int foodX = 1 + (rand() % (MAP_WIDTH - 3));
int foodY = 1 + (rand() % (MAP_HEIGHT - 2));
char foodSymb = '*';

void PlaySnake()
{
	std::cout.tie(0);
	srand(time(0));
	int time = clock();
	while (isGame) {

		if (snkDir != DOWN && GetKeyState('W') & 0x8000) snkDir = UP;
		if (snkDir != RIGHT && GetKeyState('A') & 0x8000) snkDir = LEFT;
		if (snkDir != UP && GetKeyState('S') & 0x8000) snkDir = DOWN;
		if (snkDir != LEFT && GetKeyState('D') & 0x8000) snkDir = RIGHT;

		if ((clock() - time) / CLOCKS_PER_SEC < 0.000000005) continue;
		time = clock();

		for (int i = snkLen - 2; i >= 0; --i) {
			snkX[i + 1] = snkX[i];
			snkY[i + 1] = snkY[i];
		}

		switch (snkDir) {
		case UP:
			--snkY[0];
			break;
		case DOWN:
			++snkY[0];
			break;
		case LEFT:
			--snkX[0];
			break;
		case RIGHT:
			++snkX[0];
			break;
		default:
			break;
		}
		_map[foodY * MAP_WIDTH + foodX] = foodSymb;

		if (snkX[0] == foodX && snkY[0] == foodY) {
			++snkLen;
			foodY = 1 + (rand() % (MAP_HEIGHT - 2));
			foodX = 1 + (rand() % (MAP_WIDTH - 3));
		}

		for (int i = 0; i < snkLen; ++i)
			_map[snkY[i] * MAP_WIDTH + snkX[i]] = snkSymb;
		CursorToXY(0, 0);
		//printf("%s", &(_map[0]));
		std::cout << _map;
		for (int i = 0; i < snkLen; ++i)
			_map[snkY[i] * MAP_WIDTH + snkX[i]] = ' ';
		if (snkX[0] <= 0 || snkX[0] >= MAP_WIDTH - 2 || snkY[0] <= 0 || snkY[0] >= MAP_HEIGHT - 1) isGame = false;
		for (int i = 1; i < snkLen; ++i)
			if (snkX[0] == snkX[i] && snkY[0] == snkY[i]) isGame = false;
	}
	std::cout << "GAME OVER.\nYOUR SCORE: " << snkLen << std::endl;
}

void CursorToXY(int x, int y)
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
