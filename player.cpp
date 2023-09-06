#include "player.h"

void Player::Initialize()
{
	pos = { 15,300 };	// ���S���W
	radius = 15;		// ���a
	speed = 0;			// ���x
	gravity = 0.0f;		// �d��
	isJamp = false;		//�W�����v�Ǘ��t���O
	isdir = false;		//�����Ǘ��t���O  false = �E�@true = ��
	isMove = false;		//�ړ��Ǘ��t���O
	//��
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
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		DrawCircle(particle[i].transform.x, particle[i].transform.y, particle[i].radius, particle[i].color, false);
	}

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
	if (keys[KEY_INPUT_RIGHT] && !oldkey[KEY_INPUT_RIGHT] ||
		keys[KEY_INPUT_LEFT] && !oldkey[KEY_INPUT_LEFT])
	{
		isMove = true;
	}
	else
	{
		isMove = false;
	}

	//��ʂ̒��S����Particle�𔭐�������A�����Ƃ��Ă͕����e�̏����Ǝ��Ă���
	if (isMove == true) {
		for (int i = 0; i < MAX_PARTICLE; i++) {
			if (particle[i].isAlive == 0) {
				particle[i].isAlive = 1;
				particle[i].transform.x = pos.x;
				particle[i].transform.y = pos.y + radius;
				particle[i].radius = 7;
				particle[i].angle = rand() % 100;	// �p�x�������_���Ō��߂�
				particle[i].speed = 5.0f;
				particle[i].alpha = 250;			// �����x�����Z�b�g
				particle[i].color = GetColor(255, 255, 255);
				break;
			}
		}
	}

	//�����t���O���I���Ȃ�
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (particle[i].isAlive == 1) {
			//�p�x(angle)�ɂ���Ĉړ�
			particle[i].transform.x += cos(particle[i].angle) * particle[i].speed;
			particle[i].transform.y += sin(particle[i].angle) * particle[i].speed;
			particle[i].transform.y -= 5;
			particle[i].alpha -= 5;
			particle[i].speed -= 0.08f;
		}
	}
}
