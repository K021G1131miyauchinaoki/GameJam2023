#include "player.h"

void Player::Initialize()
{
	pos = { 225,300 };	// 中心座標
	radius = 20;		// 半径
	speed = 0;			// 速度
	gravity = 0.0f;		// 重力
}

void Player::Update(char* keys, char* oldkey)
{
	//移動
	if (keys[KEY_INPUT_RIGHT] && oldkey[KEY_INPUT_RIGHT])
	{
		if (speed <= 5)
		{
			speed += 0.2f;
		}
	}
	else if (keys[KEY_INPUT_LEFT] && oldkey[KEY_INPUT_LEFT])
	{
		if (speed >= -5)
		{
			speed -= 0.2f;
		}
	}
	else
	{
		speed = 0.0f;
	}
	pos.x += speed;
	//ジャンプ
	if (keys[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
	{
		gravity = -8.0f;
	}
	//重力加速
	pos.y += gravity;
	if (pos.y <= 400)	//底についていなければ
	{
		gravity += 0.2f;//加速する
	}
	else				//そこについているならば
	{
		gravity = 0.0f; //加速しない(止める)
	}
}

void Player::Draw()
{
	DrawBox(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, GetColor(255, 255, 255), true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "player : %f/%f\n", pos.x, pos.y);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "speed : %f\n", speed);
}
