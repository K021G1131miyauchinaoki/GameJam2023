#include "player.h"

void Player::Initialize()
{
	pos = { 60,90 };	// 中心座標
	radius = 30;		// 半径
	speed = { 0,0 };			// 速度
	gravity = 0.0f;		// 重力
	isJump = false;		//ジャンプ管理フラグ
	isdir = 0;		//方向管理フラグ  0 = 右　1 = 左　2 = 上　3 = 下
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
	DrawFormatString(0, 0, GetColor(255, 0, 0), "player : %f/%f\n", pos.x, pos.y);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "speed : %f\n", speed.x);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "speed : %f\n", speed.y);
}

void Player::Move(char* keys, char* oldkey)
{
	//移動
	if (keys[KEY_INPUT_RIGHT] && !oldkey[KEY_INPUT_RIGHT])
	{
		speed.x = 60; //DrawLineで引いた線に近い値
		isdir = 0;
	}
	else if (keys[KEY_INPUT_LEFT] && !oldkey[KEY_INPUT_LEFT])
	{
		speed.x = -60;
		isdir = 1;
	}
	else if (keys[KEY_INPUT_UP] && !oldkey[KEY_INPUT_UP])
	{
		speed.y = -60;
		isdir = 2;
	}

	else if (keys[KEY_INPUT_DOWN] && !oldkey[KEY_INPUT_DOWN])
	{
		speed.y = 60;
		isdir = 3;
	}

	else
	{
		speed = { 0 ,0 }; //移動を止める
	}
	pos += speed; //現在の座標から移動する
}

void Player::Smoke(char* keys, char* oldkey)
{
	if (isMove == false) {
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

void Player::Kick(char* keys, char* oldkey)
{
	if (isdir == 0&& 
		keys[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])//右
	{
		
	}
	else if (isdir == 1 &&
		keys[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])//左
	{
		
	}
	else if (isdir == 2 &&
		keys[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])//上
	{
		
	}

	else if (isdir == 3 &&
		keys[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])//下
	{
		
	}
}
