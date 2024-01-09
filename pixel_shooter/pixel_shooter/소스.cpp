#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>


struct BULLET {
	int x;
	int y;
	bool fire;
};

char bg[25][80];

int playerX, playerY;
int enemyX, enemyY;

BULLET playerBullet[20];

void ClearScreen();
void GameMain();
void PrintScreen();
void KeyControl();
void BulletDraw();
void PlayerDraw();
void EnemyDraw();
void EnemyMove();
void ClashEnemyAndBullet();

int main(void)
{
	srand((unsigned)time(NULL));
	playerX = 0;
	playerY = 12;

	enemyX = 75;
	enemyY = 12;

	for (int i = 0; i < 20; i++) {
		playerBullet[i].x = 0;
		playerBullet[i].y = 0;
		playerBullet[i].fire = false;
	}

	int dwTime = GetTickCount64();

	while (true) {
		if (dwTime + 50 < GetTickCount64()) {
			dwTime = GetTickCount64();
			ClearScreen();
			GameMain();
			PrintScreen();
		}
	}
}

void ClearScreen()
{
	system("cls");

	for (int y = 0; y < 25; y++)
	{
		for (int x = 0; x < 80; x++)
		{
			bg[y][x] = ' ';
		}
	}
}

void GameMain()
{
	KeyControl();
	BulletDraw();
	PlayerDraw();
	EnemyMove();
	EnemyDraw();
	ClashEnemyAndBullet();
}

void PrintScreen()
{
	bg[24][79] = '\0';
	printf("%s", bg);
}

void KeyControl()
{
	if (_kbhit()) {
		char pressKey = _getch();

		switch (pressKey) {
		case 72:
			if (playerY > 1) playerY--;
			break;
		case 75:
			if (playerX > 0) playerX--;
			break;
		case 77:
			if (playerX < 75) playerX++;
			break;
		case 80:
			if (playerY < 23) playerY++;
			break;
		case 32 :
			for (int i = 0; i < 20; i++)
			{
				if (!playerBullet[i].fire)
				{
					playerBullet[i].fire = true;
					playerBullet[i].x = playerX + 3;
					playerBullet[i].y = playerY;
					break;
				}
			}
			break;
		}
	}
}

void BulletDraw()
{
	for (int i = 0; i < 20; i++)
	{
		if (playerBullet[i].fire)
		{
			bg[playerBullet[i].y][playerBullet[i].x - 1] = '=';
			bg[playerBullet[i].y][playerBullet[i].x] = '>';
			playerBullet[i].x++;

			if (playerBullet[i].x > 79)
				playerBullet[i].fire = false;
		}
	}
}

void PlayerDraw()
{
	bg[playerY - 1][playerX + 1] = '-';
	bg[playerY - 1][playerX] = 'l';
	bg[playerY][playerX] = 'O';
	bg[playerY][playerX + 1] = '-';
	bg[playerY][playerX + 2] = '-';
	bg[playerY][playerX + 3] = '-';
	bg[playerY][playerX + 4] = '}';
	bg[playerY + 1][playerX] = 'l';
	bg[playerY + 1][playerX + 1] = '-';

}

void EnemyDraw()
{
	bg[enemyY][enemyX - 2] = '<';
	bg[enemyY][enemyX - 1] = '~';
	bg[enemyY][enemyX] = 'O';
	bg[enemyY][enemyX + 1] = '~';
	bg[enemyY][enemyX + 2] = 'O';
	bg[enemyY][enemyX + 3] = '~';
	bg[enemyY][enemyX + 2] = 'O';
}

void EnemyMove()
{
	enemyX--;
	if (enemyX < 2)
	{
		enemyX = 77;
		enemyY = (rand() % 20) + 2;
	}
}

void ClashEnemyAndBullet()
{
	for (int i = 0; i < 20; i++) {
		if (playerBullet[i].fire && playerBullet[i].y == enemyY) {
			if (playerBullet[i].x >= (enemyX - 1) && playerBullet[i].x <= (enemyX + 1)) {
				enemyX = 77;
				enemyY = (rand() % 20) + 2;
				playerBullet[i].fire = false;
			}
		}
	}
}
