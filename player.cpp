#include "player.h"

void Player::Initialize()
{
	pos = { 225,300 };	//íÜêSç¿ïW
	radius = 20;		//îºåa
	speed = 5;
}

void Player::Update(char* keys, char* oldkey)
{
	if (keys[KEY_INPUT_RIGHT] && oldkey[KEY_INPUT_RIGHT])
	{
		pos.x += speed;
	}
	if (keys[KEY_INPUT_LEFT] && oldkey[KEY_INPUT_LEFT])
	{
		pos.x -= speed;
	}
}

void Player::Draw()
{
	DrawBox(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, GetColor(255, 255, 255), true);
}
