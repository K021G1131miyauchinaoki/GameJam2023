#pragma once
#include "DxLib.h"
#include "Vector2.h"
#include <cmath>  

typedef struct Particle {
	Vector2 transform;	//座標
	int radius=7;			//半径
	int isAlive = 0;		//生存フラグ
	float speed = 20.0f;		//速度
	double angle = 0;			//角度
	int alpha = 255;		//透明度
	unsigned int color;		//色
}Particle;

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

	/// <summary>
	/// 移動開始時に煙を出す為の処理
	/// </summary>
	void Smoke(char* keys, char* oldkey);//演出用関数

	Vector2 GetPlayerArray(){}

private:
//プレイヤー
	Vector2 pos;
	Vector2	initialPos;
	Vector2 playerArray;
	int radius;
	Vector2 speed;
	float gravity;

	bool isJump;
	bool isdir;
	bool isMove;

	int graphHandle;
//パーティクル
	const int MAX_PARTICLE = 5;
	Particle particle[5];
	Particle jumpParticle[5];
};

