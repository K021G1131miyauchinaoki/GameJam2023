#pragma once
#define WIDHT 15
#define HEIGHT 10

class Map
{
public:
	void Reset();
	void Initialize();
	void Update();
	void Draw();
	bool IsClear() { return isClear; }			
private:
	int answer[HEIGHT][WIDHT];
	int object[HEIGHT][WIDHT];
	int ground[HEIGHT][WIDHT];
	int r;
	int count;
	int blockTex;
	bool isClear;
	const int space = 30;
};