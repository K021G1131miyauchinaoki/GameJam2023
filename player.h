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
	/// ˆÚ“®‚ÆƒWƒƒƒ“ƒv‚ğ‚·‚éˆ×‚Ìˆ—
	/// </summary>
	void Move(char* keys, char* oldkey);//ˆÚ“®ŠÖ”
private:
	Vector2 pos;
	int radius;
	float speed;
	float gravity;

	bool isJamp;
	bool isdir;

	int graphHandle;
};

