#include "player.h"

void Player::Initialize()
{
	pos = { 15,300 };	// ���S���W
	radius = 15;		// ���a
	speed = 0;			// ���x
	gravity = 0.0f;		// �d��
	isJump = false;		//�W�����v�Ǘ��t���O
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
			//�e�̂̃A���t�@�l�ɂ���ău�����h���[�h�̒l��ς��Ă���
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
					jumpParticle[i].angle = rand() % 100;	// �p�x�������_���Ō��߂�
					jumpParticle[i].speed = rand() % 2;
					jumpParticle[i].alpha = 250;			// �����x�����Z�b�g
					jumpParticle[i].color = GetColor(255, 255, 255);
					break;
				}
			}
			//�����t���O���I���Ȃ�
			for (int i = 0; i < 5; i++) {
				if (jumpParticle[i].isAlive == 1) {
					jumpParticle[i].alpha -= 20;
				}
			}

		}
}
