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
	Transform transform;	//���W�A���a
	int isAlive = 0;		//�����t���O
	float speed = 10.0f;		//���x
	double angle = 0;			//�p�x
	int alpha = 255;		//�����x
	unsigned int color;		//�F
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

