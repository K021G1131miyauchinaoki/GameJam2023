#pragma once
#include"Block.h"

class Tetris
{
public://静的メンバ変数
	static const int width = 14;
	static const int height = 17;
	static const int minoW = 1;
	static const int minoH = 2;

public:
	//初期化
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();


private:
	int map[height][width];
	int display[height][width];
	int mino[minoH][minoW];
	int r = 8;
	int minoType, minoAngle;
	int minoX = 5, minoY = 0;
	int time;
	const int timer=30;
};

