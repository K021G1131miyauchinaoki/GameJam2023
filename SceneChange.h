#pragma once
class SceneChange
{
public:
	int x;
	int y;

	int sizeX;
	int sizeY;

	int time;
	int timeMax;

	void Initialize();
	void Start();
	void End();
	void Reset();
};

