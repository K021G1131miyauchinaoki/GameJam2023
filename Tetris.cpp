#include "Tetris.h"
#include "DxLib.h"

const int Tetris::width;
const int Tetris::height;

void Tetris::Initialize() {
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			map[y][x] = 0;
		}
	}
	pos.x = r;
	pos.y= r;
	map[0][0] = 1;
}

void Tetris::Update() {

}

void Tetris::Draw() {
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (map[y][x] == 0)
			{
				DrawBox((pos.x * x) - r, (pos.y * y) - r-(r/2), (pos.x * x) + r, (pos.y * y) + r - (r / 2), GetColor(255, 255, 255), false);
			}
			else
			{
				DrawBox((pos.x * x) - r, (pos.y * y) - r-(r/2), (pos.x * x) + r, (pos.y * y) + r - (r / 2), GetColor(255, 255, 255), true);
			}
		}
	}
}