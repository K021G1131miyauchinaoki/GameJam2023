#pragma once
#include "DxLib.h"
#include <vector> 
#include <cmath>  

typedef struct tagVector2Block {
	float x;
	float y;
}Vector2Block;

typedef struct Transform {
	float x = 100;
	float y = 300;
	int radius = 16;
}Transform;

typedef struct Particle {
	Transform transform;	//座標、半径
	int isAlive = 0;		//生存フラグ
	float speed = 10.0f;		//速度
	double angle = 0;			//角度
	int alpha = 255;		//透明度
	unsigned int color;		//色
}Particle;

class Block
{
public:
	void Initialize();
	void Update(char* keys, char* oldkey);
	void Draw();
private:
	Vector2Block pos;
	Vector2Block velocity;
	int radius;
	float speed;
	float gravity;
	float isDamage;

	
	const int MAX_PARTICLE = 3;

	Particle particle[3];
	int g1 = LoadGraph("particle.png");
	int nodamage = LoadGraph("nodamage.png");
	int damage = LoadGraph("damage.png");
};

