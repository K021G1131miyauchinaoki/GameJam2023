#pragma once
#define WIDHT 10
#define HEIGHT 10

class map
{
public:
	void Reset();
	void Initialize();
	void Update();
	void Draw();
	bool IsClear() { return isClear; }			
private:
	int answer[10][10];
	int object[10][10];
	int ground[10][10];
	int r;
	int count;
	int blockTex;
	bool isClear;
};