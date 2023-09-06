#include "Tetris.h"
#include "DxLib.h"
#include<memory>

const int Tetris::width;
const int Tetris::height;
const int Tetris::minoW;
const int Tetris::minoH;

void Tetris::Initialize() {
	//マップの初期化
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			map[y][x] = 0;
		}
	}

	//横の両端を1にする
	for (size_t i = 0; i < height; i++)
	{
		map[i][0] = map[i][width - 1] = 10;
	}

	//一番下を1にする
	for (size_t i = 0; i < width; i++)
	{
		map[height - 1][i] = 10;
	}

	//ブロックの初期化
	for (size_t i = 0; i < minoH; i++)
	{
		for (size_t j = 0; j < minoW; j++)
		{
			mino[i][j] = 1;
		}
	}

	time = timer;
}

void Tetris::Update() {
	//タイムで１マスずつ落とす
	time--;
	if (time<0)
	{
		minoY++;
		time = timer;
	}
}

void Tetris::Draw() {
	memcpy(display, map, sizeof(map));

	for (size_t y = 0; y < minoH; y++)
	{
		for (size_t x = 0; x < minoW; x++)
		{
			display[minoY+ y][minoX+ x] = mino[y][x];
		}
	}

	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (display[y][x] != 0)
			{
				DrawBox(r - r+ (r *2* x), r - r + (r * 2 * y) - (r / 2), r + r + (r * 2 * x), r + r + (r * 2 * y) - (r / 2), GetColor(255, 255, 255), false);
			}
			else if(display[y][x] == 10)
			{
				DrawBox(r - r+ (r *2* x), r - r + (r * 2 * y) - (r / 2), r + r + (r * 2 * x), r + r + (r * 2 * y) - (r / 2), GetColor(255, 255, 255), false);
			}
		}
	}
}
