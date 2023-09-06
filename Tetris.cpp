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
	for (size_t i = 0; i < height; i++)
	{
		//‰¡‚Ì—¼’[‚ð1‚É‚·‚é
		map[i][0] = map[i][width - 1] = 10;
	}

	for (size_t i = 0; i < width; i++)
	{
		//ˆê”Ô‰º‚ð1‚É‚·‚é
		map[height - 1][i] = 10;
	}

	pos.x = r;
	pos.y= r;
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
				DrawBox(r - r+ (r *2* x), r - r + (r * 2 * y) - (r / 2), r + r + (r * 2 * x), r + r + (r * 2 * y) - (r / 2), GetColor(255, 255, 255), false);
			}
			if(map[y][x] == 10)
			{
				DrawBox(r - r+ (r *2* x), r - r + (r * 2 * y) - (r / 2), r + r + (r * 2 * x), r + r + (r * 2 * y) - (r / 2), GetColor(255, 255, 255), true);
			}
		}
	}
}