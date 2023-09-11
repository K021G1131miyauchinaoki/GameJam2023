#pragma once
#include "DxLib.h"

class Count
{
public:
	void Initialize();
	void Update(char* keys, char* oldkey);
	void Draw();
private:
	int graphHandle[10];
	char strNum[4];
	int count[3];
};

