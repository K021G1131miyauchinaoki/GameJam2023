#include "player.h"

void Player::Initialize()
{
	pos = { 15,300 };	// ���S���W
	radius = 15;		// ���a
	speed = 0;			// ���x
	gravity = 0.0f;		// �d��
	isJamp = false;		//�W�����v�Ǘ��t���O
	isdir = false;		//�����Ǘ��t���O  false = �E�@true = ��

	//��
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
	//�d�͉���
	pos.y += gravity;
	if (pos.y <= 400)	//��ɂ��Ă��Ȃ����
	{
		gravity += 0.5f;//��������
	}
	else				//�����ɂ��Ă���Ȃ��
	{
		gravity = 0.0f; //�������Ȃ�(�~�߂�)
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
	//�ړ�
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

	//�W�����v
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
			//�L�[�������ꂽ�Ƃ��ď�����
			particle[i].transform.x = pos.x; //���W���v���C���[�Ɏw��
			particle[i].transform.y = pos.y + radius; //�������w�肷��
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
			//�L�[�������ꂽ�Ƃ��ď�����
			particle[i].transform.x = pos.x; //���W���v���C���[�Ɏw��
			particle[i].transform.y = pos.y + radius; //�������w�肷��
			particle[i].radius = 7;
			particle[i].speed = 20.0f;
			particle[i].isAlive = false;
			particle[i].angle = 0;
			particle[i].alpha = 255;
			particle[i].color = GetColor(255, 255, 255);
		}
	}
}
