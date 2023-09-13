#include "DxLib.h"
#include "Map.h"
#include<memory>
void Map::Initialize() {
	r = 30;
	blockTex = LoadGraph("Resource/block.png");
}

void Map::Reset(int num) {
	
	isClear = false;
	count = 0;
	if (num == 0)//----------------------------------ステージ1-----------------------------------
	{
		int strat0[HEIGHT][WIDHT] = {
			{1,1,1,1,1, 1, 1,1, 1,1, 1,1,1,1,1},
			{1,1,1,1,0, 0, 0,0, 0,0, 0,1,1,1,1},
			{1,1,1,1,0, 0, 0,0, 0,0, 0,1,1,1,1},
			{1,1,1,1,0, 0, 0,5, 0,0, 0,1,1,1,1},
			{1,1,1,1,0, 2,11,0,11,3, 0,1,1,1,1},
						
			{1,1,1,1,0, 0,0,0,0,0, 0,1,1,1,1},
			{1,1,1,1,0, 0,0,0,0,0, 0,1,1,1,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};
		int ANS0[HEIGHT][WIDHT] = {
			{1,1,1,1,1, 1, 1,1, 1,1, 1,1,1,1,1},
			{1,1,1,1,0, 0, 0,0, 0,0, 0,1,1,1,1},
			{1,1,1,1,0, 0, 0,0, 0,0, 0,1,1,1,1},
			{1,1,1,1,0, 0, 0,0, 0,0, 0,1,1,1,1},
			{1,1,1,1,0, 2,11,5,11,3, 0,1,1,1,1},

			{1,1,1,1,0, 0,0,0,0,0, 0,1,1,1,1},
			{1,1,1,1,0, 0,0,0,0,0, 0,1,1,1,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};

		for (size_t i = 0; i < HEIGHT; i++)
		{
			for (size_t j = 0; j < WIDHT; j++)
			{
				answer[i][j] = ANS0[i][j];
				object[i][j] = strat0[i][j];
				//下地
				//通れない、使わない部分
				if (strat0[i][j] == 1)
				{
					ground[i][j] = 1;
				}
				//通れたりその上にオブジェクトが置かれる部分
				else
				{
					ground[i][j] = 0;
				}
			}
		}
	}
	if (num == 1)	//----------------------------------ステージ2-----------------------------------	
	{
		int strat1[HEIGHT][WIDHT] = {
			{1,1,1,1,1, 1, 1,1, 1,1, 1,1,1,1,1},
			{1,1,1,1,1, 1, 1,1, 1,1, 1,1,1,1,1},
			{1,1,1,0,0, 1, 1,1, 1,1, 1,0,1,1,1},
			{1,1,1,0,0, 1, 0,0, 0,1, 0,0,1,1,1},
			{1,1,1,0,0, 2, 0,0, 0,3, 0,0,1,1,1},

			{1,1,1,0,0, 0,0,0,0,0, 0,0,1,1,1},
			{1,1,1,0,0, 0,0,0,0,0, 0,0,1,1,1},
			{1,1,1,0,0, 0,0,0,0,0, 0,0,1,1,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};
		int ANS1[HEIGHT][WIDHT] = {
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
				answer[i][j] = ANS1[i][j];
				object[i][j] = strat1[i][j];
				//下地
				//通れない、使わない部分
				if (strat1[i][j] == 1)
				{
					ground[i][j] = 1;
				}
				//通れたりその上にオブジェクトが置かれる部分
				else
				{
					ground[i][j] = 0;
				}
			}
		}
	}
	if (num == 2) //----------------------------------ステージ3-----------------------------------	
	{
		int strat2[HEIGHT][WIDHT] = {
		{1,1,1,1,1, 1,1,1,1,1,	  1,1,1,1,1},
		{1,0,0,0,0, 0,0,0,0,0,	  0,0,0,0,0},
		{1,0,0,2,3, 4,0,0,0,0,	  0,0,0,0,0},
		{1,0,0,6,7, 8,9,0,0,0,	  0,0,0,0,0},
		{1,0,0,10,11, 0,0,0,0,0,  0,0,0,0,0},

		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,5},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};
		int ANS2[HEIGHT][WIDHT] = {
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
				answer[i][j] = ANS2[i][j];
				object[i][j] = strat2[i][j];
				//下地
				//通れない、使わない部分
				if (strat2[i][j] == 1)
				{
					ground[i][j] = 1;
				}
				//通れたりその上にオブジェクトが置かれる部分
				else
				{
					ground[i][j] = 0;
				}
			}
		}
	}
	if (num == 3)//----------------------------------ステージ4-----------------------------------
	{
		int strat3[HEIGHT][WIDHT] = {
		{1,1,1,1,1, 1,1,1,1,1,	  1,1,1,1,1},
		{1,0,0,0,0, 0,0,0,0,0,	  0,0,0,0,0},
		{1,0,0,2,3, 4,0,0,0,0,	  0,0,0,0,0},
		{1,0,0,6,7, 8,9,0,0,0,	  0,0,0,5,0},
		{1,0,0,10,11, 0,0,0,0,0,  0,0,0,0,0},

		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};
		int ANS3[HEIGHT][WIDHT] = {
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
				answer[i][j] = ANS3[i][j];
				object[i][j] = strat3[i][j];
				//下地
				//通れない、使わない部分
				if (strat3[i][j] == 1)
				{
					ground[i][j] = 1;
				}
				//通れたりその上にオブジェクトが置かれる部分
				else
				{
					ground[i][j] = 0;
				}
			}
		}
	}
	if (num == 4)//----------------------------------ステージ5-----------------------------------	
	{
		int strat4[HEIGHT][WIDHT] = {
		{1,1,1,1,1, 1,1,1,1,1,	  1,1,1,1,1},
		{1,0,0,0,0, 0,0,0,0,0,	  0,0,0,0,0},
		{1,0,0,2,3, 4,0,0,0,0,	  0,0,0,0,0},
		{1,0,0,6,7, 8,9,0,0,0,	  0,0,0,0,0},
		{1,0,0,10,11, 0,0,0,0,0,  0,0,0,0,0},

		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,5,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
		{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};
		int ANS4[HEIGHT][WIDHT] = {
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
				answer[i][j] = ANS4[i][j];
				object[i][j] = strat4[i][j];
				//下地
				//通れない、使わない部分
				if (strat4[i][j] == 1)
				{
					ground[i][j] = 1;
				}
				//通れたりその上にオブジェクトが置かれる部分
				else
				{
					ground[i][j] = 0;
				}
			}
		}
	}
	if (num == 5)//----------------------------------ステージ6-----------------------------------	
	{
		int strat5[HEIGHT][WIDHT] = {
			   {1,1,1,1,1, 1,1,1,1,1,	  1,1,1,1,1},
			   {1,0,0,0,0, 0,0,0,0,0,	  0,0,0,0,0},
			   {1,0,0,2,3, 4,0,0,0,0,	  5,0,0,0,0},
			   {1,0,0,6,7, 8,9,0,0,0,	  0,0,0,0,0},
			   {1,0,0,10,11, 0,0,0,0,0,  0,0,0,0,0},

			   {1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
			   {1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
			   {1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
			   {1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
			   {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};
		int ANS5[HEIGHT][WIDHT] = {
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
				answer[i][j] = ANS5[i][j];
				object[i][j] = strat5[i][j];
				//下地
				//通れない、使わない部分
				if (strat5[i][j] == 1)
				{
					ground[i][j] = 1;
				}
				//通れたりその上にオブジェクトが置かれる部分
				else
				{
					ground[i][j] = 0;
				}
			}
		}
	}
	if (num == 6)//----------------------------------ステージ7-----------------------------------
	{
		int strat6[HEIGHT][WIDHT] = {
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
			{1,0,0,0,0, 0,0,8,0,0, 11,0,9,0,1},
			{1,0,0,0,0, 0,0,0,0,0, 0,0,0,2,1},
			{1,0,0,8,0, 0,0,0,0,0, 0,0,0,0,1},
			{1,0,0,0,0, 0,10,0,0,0, 0,0,4,0,1},

			{1,0,0,0,0, 1,3,11,5,5, 0,0,7,0,1},
			{1,0,0,0,0, 1,1,0,0,0, 0,6,5,0,1},
			{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1},
			{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};
		int ANS6[HEIGHT][WIDHT] = {
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
			{1,0,0,0,0, 0,0,8,5,5, 11,5,9,0,1},
			{1,0,0,0,0, 0,8,7,0,0, 0,0,6,2,1},
			{1,0,0,0,0, 0,4,0,0,0, 0,0,0,0,1},
			{1,0,0,0,0, 0,10,0,0,0, 0,0,0,0,1},
										   
			{1,0,0,0,0, 1,3,11,0,0, 0,0,0,0,1},
			{1,0,0,0,0, 1,1,0,0,0, 0,0,0,0,1},
			{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1},
			{1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};

		for (size_t i = 0; i < HEIGHT; i++)
		{
			for (size_t j = 0; j < WIDHT; j++)
			{
				answer[i][j] = ANS6[i][j];
				object[i][j] = strat6[i][j];
				//下地
				//通れない、使わない部分
				if (strat6[i][j] == 1)
				{
					ground[i][j] = 1;
				}
				//通れたりその上にオブジェクトが置かれる部分
				else
				{
					ground[i][j] = 0;
				}
			}
		}
	}
	if (num == 7)//----------------------------------ステージ8-----------------------------------
	{
		int strat7[HEIGHT][WIDHT] = {
			{1,1,1,1,1, 1,1,1,1,1,	1,1,1,1,1},
			{1,0,0,1,0, 3,0,0,0,0,	0,1,2,9,1},
			{1,0,0,11,0, 4,0,0,0,0,	0,0,1,4,1},
			{1,0,5,0,0, 8,0,0,4,0,	0,4,0,0,1},
			{1,4,0,7,0, 0,0,0,0,0,  0,0,0,4,1},

			{1,4,0,0,0, 0,0,0,0,0, 5,0,0,4,1},
			{1,4,0,8,0, 0,5,0,0,0, 0,0,0,0,1},
			{1,4,0,0,0, 0,0,0,0,0, 0,0,0,4,1},
			{1,6,5,5,5, 5,5,5,0,5, 5,5,5,7,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};
		int ANS7[HEIGHT][WIDHT] = {
			{1,1,1,1,1, 1,1,1,1,1,	1,1,1,1,1},
			{1,0,0,1,8, 3,0,0,0,0,	0,1,2,9,1},
			{1,0,0,11,4, 0,0,0,0,0,	0,0,1,4,1},
			{1,8,5,5,7, 0,0,0,0,0,	0,0,0,4,1},
			{1,4,0,0,0, 0,0,0,0,0,  0,0,0,4,1},

			{1,4,0,0,0, 0,0,0,0,0, 0,0,0,4,1},
			{1,4,0,0,0, 0,0,0,0,0, 0,0,0,4,1},
			{1,4,0,0,0, 0,0,0,0,0, 0,0,0,4,1},
			{1,6,5,5,5, 5,5,5,5,5, 5,5,5,7,1},
			{1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
		};      
		
		for (size_t i = 0; i < HEIGHT; i++)
		{
			for (size_t j = 0; j < WIDHT; j++)
			{
				answer[i][j] = ANS7[i][j];
				object[i][j] = strat7[i][j];
				//下地
				//通れない、使わない部分
				if (strat7[i][j] == 1)
				{
					ground[i][j] = 1;
				}
				//通れたりその上にオブジェクトが置かれる部分
				else
				{
					ground[i][j] = 0;
				}
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