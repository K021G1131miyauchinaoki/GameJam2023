#include "player.h"

void Player::Initialize()
{
	pos = { 15,300 };	// 中心座標
	radius = 15;		// 半径
	speed = 0;			// 速度
	gravity = 0.0f;		// 重力
	isJump = false;		//ジャンプ管理フラグ
	isdir = false;		//方向管理フラグ  false = 右　true = 左
	isMove = false;		//移動管理フラグ
	//煙
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		particle[i].transform.x = 0;
		particle[i].transform.y = 0;
		particle[i].radius = 7;
		particle[i].speed = 20.0f;
		particle[i].isAlive = false;
		particle[i].angle = 0;
		particle[i].alpha = 255;
		particle[i].color = GetColor(255, 255, 255);
	}
	

	graphHandle = LoadGraph("Resource/jamtest.png");
}

void Player::Update(char* keys, char* oldkey)
{
	Smoke(keys, oldkey);
	Move(keys, oldkey);
	//重力加速
	pos.y += gravity;
	if (pos.y <= 400)	//底についていなければ
	{
		gravity += 0.5f;//加速する
	}
	else				//そこについているならば
	{
		gravity = 0.0f; //加速しない(止める)
		if (isJump)
		{
			isJump = false;
			for (int i = 0; i < 5; i++) {
				jumpParticle[i].isAlive = false;
			}
		}
	}
}

void Player::Draw()
{
	DrawGraph(pos.x - radius, pos.y - radius, graphHandle, true);
	DrawBox(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, GetColor(255, 255, 255), false);
	for (int i = 0; i < 5; i++) {
		if (jumpParticle[i].isAlive == 1) {
			//各個体のアルファ値によってブレンドモードの値を変えている
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, jumpParticle[i].alpha);
			DrawGraph(
				jumpParticle[i].transform.x,
				jumpParticle[i].transform.y,
				graphHandle,
				TRUE
			);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "player : %f/%f\n", pos.x, pos.y);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "speed : %f\n", speed);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "isdir : %d", isdir);
	DrawFormatString(0, 45, GetColor(255, 255, 255), "isdir : %d", jumpParticle[0].isAlive);
}

void Player::Move(char* keys, char* oldkey)
{
	//移動
	if (keys[KEY_INPUT_RIGHT] && oldkey[KEY_INPUT_RIGHT])
	{
		if (speed <= 5)
		{
			speed += 0.4f;
		}
		if (speed < 0)
		{
			speed = 0;
		}

		if (isdir)
		{
			isdir = false;
		}
	}
	else if (keys[KEY_INPUT_LEFT] && oldkey[KEY_INPUT_LEFT])
	{
		if (speed >= -5)
		{
			speed -= 0.4f;
		}
		if (speed > 0)
		{
			speed = 0;
		}
		if (!isdir)
		{
			isdir = true;
		}
	}
	else
	{
		speed = 0.0f;
	}
	pos.x += speed;

	//ジャンプ
	if (keys[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE] && !isJump)
	{
		gravity = -8.0f;
		isJump = true;
		for (int i = 0; i < 5; i++) {
			jumpParticle[i].isAlive = false;
		}
	}
	
}

void Player::Smoke(char* keys, char* oldkey)
{
	if (isJump == false) {
			for (int i = 0; i < 5; i++) {
				if (jumpParticle[i].isAlive == 0) {
					jumpParticle[i].isAlive = 1;
					jumpParticle[i].transform.x = pos.x + rand() % 30-30;
					jumpParticle[i].transform.y = pos.y + rand() % 10;
					jumpParticle[i].angle = rand() % 100;	// 角度をランダムで決める
					jumpParticle[i].speed = rand() % 2;
					jumpParticle[i].alpha = 250;			// 透明度をリセット
					jumpParticle[i].color = GetColor(255, 255, 255);
					break;
				}
			}
			//生存フラグがオンなら
			for (int i = 0; i < 5; i++) {
				if (jumpParticle[i].isAlive == 1) {
					jumpParticle[i].alpha -= 20;
				}
			}
		}
}
