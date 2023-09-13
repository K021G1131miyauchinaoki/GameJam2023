#include "SceneChange.h"
#include "Easing.h"

void SceneChange::Initialize()
{
	
}
void SceneChange::Updeta()
{
	

}
void SceneChange::Start()
{

	if (time >= timeMax)
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

void SceneChange::setTex(int Tex)
{
	tex = Tex;
}

void SceneChange::End()
{
	if (time >= timeMax)
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

void SceneChange::Reset(int texSizeX, int texSizeY)
{
	x = 0.0;
	y = 0.0;
	sizeX = texSizeX;
	sizeY = texSizeY;
	timeMax = 180;
	time = 0;
}

void SceneChange::Draw()
{
	DrawGraph(x, y, tex, true);
}
