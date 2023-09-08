#include "DxLib.h"
#include "map.h"

void map::Initialize() {
	r = 16;
	isClear = false;
	count = 0;
	int d[HEIGHT][WIDHT] = {
		{1,1,1,1,1, 1,1,1,1,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,2,3, 4,5,0,0,1},
		{1,0,0,6,7, 8,9,0,0,1},
		{1,0,0,10,0, 11,0,0,0,1},

		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,1,1,1,1, 1,1,1,1,1},
	};
	int ANS[HEIGHT][WIDHT] = {
		{1,1,1,1,1, 1,1,1,1,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,2,3, 4,5,0,0,1},
		{1,0,0,6,7, 8,9,0,0,1},
		{1,0,0,10,11, 0,0,0,0,1},

		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,0,0,0,0, 0,0,0,0,1},
		{1,1,1,1,1, 1,1,1,1,1},
	};

	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDHT; j++)
		{
			answer[i][j]=ANS[i][j];
			object[i][j] = d[i][j];
			//下地
			//通れない、使わない部分
			if (d[i][j]==1)
			{
				ground[i][j]=1;
			}
			//通れたりその上にオブジェクトが置かれる部分
			else
			{
				ground[i][j] = 0;
			}
		}
	}
}

void map::Update() {
	count = 0;
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDHT; j++)
		{
			if (answer[i][j] == object[i][j])
			{
				count++;
			}
		}
	}
	if (count==HEIGHT*WIDHT)
	{
		isClear = true;
	}
}

void map::Draw() {
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDHT; j++)
		{
			//下地
			if (ground[i][j] == 0)
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(200, 200, 200), true);
			}
			else if (ground[i][j] == 1)
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(100, 100, 100), true);
			}

			//オブジェクト
			if (object[i][j] == 2)
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(50, 0, 0), true);
			}
			if (object[i][j] == 3)
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(0, 50, 0), true);
			}
			if (object[i][j] ==4 )
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(0, 0, 50), true);
			}
			if (object[i][j] == 5)
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(50, 50, 0), true);
			}
			if (object[i][j] ==6 )
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(50, 0, 50), true);
			}
			if (object[i][j] == 7)
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(0, 50, 50), true);
			}
			if (object[i][j] == 8)
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(150, 0, 0), true);
			}
			if (object[i][j] == 9)
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(0, 150, 0), true);
			}
			if (object[i][j] == 10)
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(0, 0, 150), true);
			}
			if (object[i][j] == 11)
			{
				DrawBox(r - r + (r * 2 * j), r - r + (r * 2 * i) - (r / 2), r + r + (r * 2 * j), r + r + (r * 2 * i) - (r / 2), GetColor(150, 150, 0), true);
			}

			
		}
	}
}