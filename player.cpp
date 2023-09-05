#include "player.h"

void Player::Initialize()
{
	pos = { 225,300 };	// ���S���W
	radius = 20;		// ���a
	speed = 0;			// ���x
	gravity = 0.0f;		// �d��
}

void Player::Update(char* keys, char* oldkey)
{
	//�ړ�
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
	//�W�����v
	if (keys[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
	{
		gravity = -8.0f;
	}
	//�d�͉���
	pos.y += gravity;
	if (pos.y <= 400)	//��ɂ��Ă��Ȃ����
	{
		gravity += 0.2f;//��������
	}
	else				//�����ɂ��Ă���Ȃ��
	{
		gravity = 0.0f; //�������Ȃ�(�~�߂�)
	}
}

void Player::Draw()
{
	DrawBox(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, GetColor(255, 255, 255), true);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "player : %f/%f\n", pos.x, pos.y);
	DrawFormatString(0, 15, GetColor(255, 255, 255), "speed : %f\n", speed);
}
