#include "Count.h"

void Count::Initialize()
{
	count = 0;
}

void Count::Update(char* keys, char* oldkey)
{
	if (keys[KEY_INPUT_UP] && !oldkey[KEY_INPUT_UP])
	{
		count += 1;
	}
	if (keys[KEY_INPUT_DOWN] && !oldkey[KEY_INPUT_DOWN])
	{
		count += 1;
	}
	if (keys[KEY_INPUT_RIGHT] && !oldkey[KEY_INPUT_RIGHT])
	{
		count += 1;
	}
	if (keys[KEY_INPUT_LEFT] && !oldkey[KEY_INPUT_LEFT])
	{
		count += 1;
	}
}

void Count::Draw()
{
	DrawFormatString(900, 0, GetColor(255, 255, 255), "Count ; %d", count);
}
