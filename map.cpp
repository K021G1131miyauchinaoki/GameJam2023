#include "DxLib.h"
#include "Map.h"

void Map::Initialize() {
	r = 30;
	blockTex = LoadGraph("Resource/block.png");
}

void Map::Reset() {
	
	isClear = false;
	count = 0;
	int d[HEIGHT][WIDHT] = {
		{1,1,1,1,1, 1,1,1,1,1,	  1,1,1,1,1},
		{1,0,0,0,0, 0,0,0,0,0,	  0,0,0,0,0},
		{1,0,0,2,3, 4,5,0,0,0,	  0,0,0,0,0},
		{1,0,0,6,7, 8,9,0,0,0,	  0,0,0,0,0},
		{1,0,0,10,0, 11,0,0,0,0,  0,0,0,0,0},

		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
	};
	int ANS[HEIGHT][WIDHT] = {
		{1,1,1,1,1, 1,1,1,1,1,	  1,1,1,1,1},
		{1,0,0,0,0, 0,0,0,0,0,	  0,0,0,0,0},
		{1,0,0,2,3, 4,5,0,0,0,	  0,0,0,0,0},
		{1,0,0,6,7, 8,9,0,0,0,	  0,0,0,0,0},
		{1,0,0,10,11,0, 0,0,0,0,  0,0,0,0,0},

		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
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

void Map::Update() {
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

void Map::Draw() {
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDHT; j++)
		{
			//下地
			if (ground[i][j] == 0)
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * ground[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}
			else if (ground[i][j] == 1)
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * ground[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}

			//オブジェクト
			if (object[i][j] == 2)
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * object[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}
			else if (object[i][j] == 3)
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * object[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}
			else if (object[i][j] ==4 )
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * object[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}
			else if (object[i][j] == 5)
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * object[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}
			else if (object[i][j] ==6 )
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * object[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}
			else if (object[i][j] == 7)
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * object[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}
			else if (object[i][j] == 8)
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * object[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}
			else if (object[i][j] == 9)
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * object[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}
			else if (object[i][j] == 10)
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * object[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}
			else if (object[i][j] == 11)
			{
				DrawRectGraph(space + (r * 2 * j), space*2+(r * 2 * i), r * 2 * object[i][j], 0, r * 2, r * 2, blockTex, true, false);
			}

			
		}
	}
}