#include "player.h"

void Player::Initialize()
{
	pos = { 15,300 };	// 中心座標
	radius = 15;		// 半径
	speed = 0;			// 速度
	gravity = 0.0f;		// 重力
	isJamp = false;		//ジャンプ管理フラグ
	isdir = false;		//方向管理フラグ  false = 右　true = 左

	//煙
	for (int i = 0; i < 5; i++)
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
		if (isJamp)
		{
			isJamp = false;
		}
	}
}

void Player::Draw()
{
	DrawGraph(pos.x - radius, pos.y - radius, graphHandle, true);
	DrawBox(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, GetColor(255, 255, 255), false);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "player : %f/%f\n", pos.x, pos.y);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "speed : %f\n", speed);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "isdir : %d", isdir);
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
	if (keys[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE] && !isJamp)
	{
		gravity = -8.0f;
		isJamp = true;
	}
}

void Player::Smoke(char* keys, char* oldkey)
{
	if (keys[KEY_INPUT_RIGHT] && !oldkey[KEY_INPUT_RIGHT])
	{
		for (int i = 0; i < 5; i++)
		{
			//キーが押されたとき再初期化
			particle[i].transform.x = pos.x; //座標をプレイヤーに指定
			particle[i].transform.y = pos.y + radius; //足元を指定する
			particle[i].radius = 7;
			particle[i].speed = 20.0f;
			particle[i].isAlive = false;
			particle[i].angle = 0;
			particle[i].alpha = 255;
			particle[i].color = GetColor(255, 255, 255);
		}
	}

	if (keys[KEY_INPUT_LEFT] && !oldkey[KEY_INPUT_LEFT])
	{
		for (int i = 0; i < 5; i++)
		{
			//キーが押されたとき再初期化
			particle[i].transform.x = pos.x; //座標をプレイヤーに指定
			particle[i].transform.y = pos.y + radius; //足元を指定する
			particle[i].radius = 7;
			particle[i].speed = 20.0f;
			particle[i].isAlive = false;
			particle[i].angle = 0;
			particle[i].alpha = 255;
			particle[i].color = GetColor(255, 255, 255);
		}
	}
}
