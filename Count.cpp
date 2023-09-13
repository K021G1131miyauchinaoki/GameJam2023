#include "Count.h"
#include <stdio.h>

void Count::Initialize()
{
	for (int i = 0; i < 3; i++)
	{
		count[i] = 0;
	}
	addTimer = 0;
	LoadDivGraph("Resource/number.png", 10, 10, 1, 80, 80, graphHandle);
	backGround = LoadGraph("Resource/backGroung.png");
}

void Count::Update(char* keys, char* oldkey)
{
	if (count[2] < 10)//999��艺�Ȃ�
	{
		//�P�̂ŉ�����Ă���Ȃ�
		if (keys[KEY_INPUT_UP] && !oldkey[KEY_INPUT_UP] && addTimer == 0)
		{
			addTimer = 10;
		}
		if (keys[KEY_INPUT_DOWN] && !oldkey[KEY_INPUT_DOWN] && addTimer == 0)
		{
			addTimer = 10;
		}
		if (keys[KEY_INPUT_RIGHT] && !oldkey[KEY_INPUT_RIGHT] && addTimer == 0)
		{
			addTimer = 10;
		}
		if (keys[KEY_INPUT_LEFT] && !oldkey[KEY_INPUT_LEFT] && addTimer == 0)
		{
			addTimer = 10;
		}
	}
	else //����999�ɂȂ�����
	{
		for (int i = 0; i < 3; i++)
		{
			count[i] = 9;//999�ɌŒ肷��
		}
	}

	if (addTimer != 0)
	{
		addTimer--;
		if (addTimer >= 9)
		{
			AddCount();
		}
	}
}

void Count::Draw()
{
	DrawGraph(0, 0, backGround, true);

	DrawGraph(1120, 570, graphHandle[count[0]], true);
	DrawGraph(1080, 570, graphHandle[count[1]], true);
	DrawGraph(1040, 570, graphHandle[count[2]], true);

	//DrawFormatString(900, 0, GetColor(255, 255, 255), "Count ; %d", count);

}

void Count::Reset()
{
	for (int i = 0; i < 3; i++)
	{
		count[i] = 0;
	}
}

void Count::AddCount()
{
	count[0] += 1;//1�̂��炢��+1����
	if (count[0] >= 10)//10�ɂȂ����Ȃ�
	{
		count[0] = 0;//null����0�ɖ߂�
		count[1] += 1;//10�̈ʂ�+1
	}
	if (count[1] >= 10)//100�ɂȂ�����
	{
		count[1] = 0;//10�̈ʂ�0�ɖ߂�
		count[2] += 1;//100�̈ʂ�+1
	}
}
