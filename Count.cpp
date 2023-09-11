#include "Count.h"
#include <stdio.h>

void Count::Initialize()
{
	for (int i = 0; i < 3; i++)
	{
		count[i] = 0;
	}
	LoadDivGraph("Resource/number.png", 10, 10, 1, 80, 80, graphHandle);
}

void Count::Update(char* keys, char* oldkey)
{
	if (count[2] < 10)//999より下なら
	{
		if (keys[KEY_INPUT_UP] && !oldkey[KEY_INPUT_UP])
		{
			count[0] += 1;//1のくらいに+1する
			if (count[0] >= 10)//10になったなら
			{
				count[0] = 0;//nullから0に戻す
				count[1] += 1;//10の位に+1
			}
			if (count[1] >= 10)//100になったら
			{
				count[1] = 0;//10の位を0に戻す
				count[2] += 1;//100の位に+1
			}

		}
		if (keys[KEY_INPUT_DOWN] && !oldkey[KEY_INPUT_DOWN])
		{
			count[0] += 1;
			if (count[0] >= 10)
			{
				count[0] = 0;
				count[1] += 1;
			}
			if (count[1] >= 10)
			{
				count[1] = 0;
				count[2] += 1;
			}
		}
		if (keys[KEY_INPUT_RIGHT] && !oldkey[KEY_INPUT_RIGHT])
		{
			count[0] += 1;
			if (count[0] >= 10)
			{
				count[0] = 0;
				count[1] += 1;
			}
			if (count[1] >= 10)
			{
				count[1] = 0;
				count[2] += 1;
			}
		}
		if (keys[KEY_INPUT_LEFT] && !oldkey[KEY_INPUT_LEFT])
		{
			count[0] += 1;
			if (count[0] >= 10)
			{
				count[0] = 0;
				count[1] += 1;
			}
			if (count[1] >= 10)
			{
				count[1] = 0;
				count[2] += 1;
			}
		}
	}
	else//もし999になった時
	{
		for (int i = 0; i < 3; i++)
		{
			count[i] = 9;//999に固定する
		}
	}
}

void Count::Draw()
{
	DrawBox(0, 0, 1280, 720, GetColor(122, 0, 0), true);

	DrawGraph(1000, 0, graphHandle[count[0]], true);
	DrawGraph(960, 0, graphHandle[count[1]], true);
	DrawGraph(920, 0, graphHandle[count[2]], true);
	
	//DrawFormatString(900, 0, GetColor(255, 255, 255), "Count ; %d", count);

}
