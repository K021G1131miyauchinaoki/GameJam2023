#include "SceneChange.h"
#include "Easing.h"
void SceneChange::Initialize()
{
	Reset();
}
void SceneChange::Start()
{

	if (time <= timeMax)
	{
		time = timeMax;
	}
	else
	{
		time++;
	}
	x = Easing::In(x - sizeX, x, time, timeMax);
	y = Easing::In(y - sizeY, y, time, timeMax);

}

void SceneChange::End()
{
	if (time <= timeMax)
	{
		time = timeMax;
	}
	else
	{
		time++;
	}
	x = Easing::In(x - sizeX, x, time, timeMax);
	y = Easing::In(y - sizeY, y, time, timeMax);

}

void SceneChange::Reset()
{
	x = 0;
	y = 0;
	sizeX = 1270;
	sizeY = 720;

	time = 0;
}
