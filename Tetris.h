#pragma once
#include"Block.h"

class Tetris
{
public://静的メンバ変数
	static const int width = 14;
	static const int height = 17;

public:
	//初期化
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw();


private:
	int map[height][width];
	int r = 8;
	Vector2 pos;
};

