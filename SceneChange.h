#pragma once
#include "DxLib.h"
class SceneChange
{
public:
	double x = 0;
	double y = 0;

	int sizeX = 0;
	int sizeY = 0;

	int time = 0;
	int timeMax = 180;
	int tex = 0;
	void setTex(int Tex);
	void Initialize();
	void Updeta();
	void Start();
	void End();
	void Reset(int texSizeX,int texSizeY);

	void Draw();
};

