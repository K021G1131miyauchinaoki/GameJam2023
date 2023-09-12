#pragma once
#include "DxLib.h"

class Count
{
public:
	void Initialize();
	void Update(char* keys, char* oldkey);
	void Draw();

	void AddCount();
private:
	int graphHandle[10];
	int backGround;
	char strNum[4];
	int count[3];
};

