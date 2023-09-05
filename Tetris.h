#pragma once
#include"Block.h"

class Tetris
{
public://静的メンバ変数
	static const int width = 12;
	static const int height = 16;

public:
	//初期化
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();


private:
	int map[height][width];
	int r = 32;
	Vector2 pos;
};

