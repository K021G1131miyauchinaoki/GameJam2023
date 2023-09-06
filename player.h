#pragma once
#include "DxLib.h"

typedef struct tagVector2 {
	float x;
	float y;
}Vector2;

typedef struct Particle {
	Vector2 transform;	//���W
	int radius=7;			//���a
	int isAlive = 0;		//�����t���O
	float speed = 20.0f;		//���x
	double angle = 0;			//�p�x
	int alpha = 255;		//�����x
	unsigned int color;		//�F
}Particle;

class Player
{
public:
	void Initialize();
	void Update(char* keys,char* oldkey);
	void Draw();
private:
	/// <summary>
	/// �ړ��ƃW�����v������ׂ̏���
	/// </summary>
	void Move(char* keys, char* oldkey);//�ړ��֐�
private:
	Vector2 pos;
	int radius;
	float speed;
	float gravity;

	bool isJamp;
	bool isdir;

	int graphHandle;

	Particle particle[5];
};

