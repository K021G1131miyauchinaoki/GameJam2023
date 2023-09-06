#pragma once
#include "DxLib.h"

typedef struct tagVector2 {
	float x;
	float y;
}Vector2;

class Player
{
public:
	void Initialize();
	void Update(char* keys,char* oldkey);
	void Draw();
private:
	/// <summary>
	/// 移動とジャンプをする為の処理
	/// </summary>
	void Move(char* keys, char* oldkey);//移動関数
private:
	Vector2 pos;
	int radius;
	float speed;
	float gravity;

	bool isJamp;
	bool isdir;

	int graphHandle;
};

