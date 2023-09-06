#include "block.h"


void Block::Initialize()
{
    pos = { 280, 300 };    // ���S���W
    radius = 20;        // ���a
    speed = 5;            // ���x
    gravity = 0.1f;        // �d��
	isDamage = false;
	//�p�[�e�B�N��
	for (int i = 0; i < MAX_PARTICLE; i++) {
		particle[i].transform.x = 450 / 2;
		particle[i].transform.y = 600 / 2;
		particle[i].transform.radius = 8;
		particle[i].alpha = 255;
		particle[i].color = GetColor(255, 255, 255);
	}
}

void Block::Update(char* keys, char* oldkey)
{
	if (keys[KEY_INPUT_1] && !oldkey[KEY_INPUT_1])
	{
		isDamage = true;
		for (int i = 0; i < MAX_PARTICLE; i++) {
			
		}
	}
	if (keys[KEY_INPUT_0] && !oldkey[KEY_INPUT_0])
	{
		isDamage = false;
		for (int i = 0; i < MAX_PARTICLE; i++) {
			particle[i].isAlive = 0;
		}
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
	//particle[MAX_PARTICLE].angle += 1;

	//��ʂ̒��S����Particle�𔭐�������A�����Ƃ��Ă͕����e�̏����Ǝ��Ă���
	if(isDamage == true){
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (particle[i].isAlive == 0) {
			particle[i].isAlive = 1;
			particle[i].transform.x = pos.x;
			particle[i].transform.y = pos.y;
			particle[i].transform.radius = 1;
			particle[i].angle = rand() % 100;	// �p�x�������_���Ō��߂�
			particle[i].speed = 5.0f;
			particle[i].alpha = 250;			// �����x�����Z�b�g
			particle[i].color = GetColor(255, 255, 255);
			break;
		}
	}

	//�����t���O���I���Ȃ�
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (particle[i].isAlive == 1) {
			//�p�x(angle)�ɂ���Ĉړ�
			particle[i].transform.x += cos(particle[i].angle) * particle[i].speed;
			particle[i].transform.y += sin(particle[i].angle) * particle[i].speed;
			particle[i].transform.y += 5;
			particle[i].alpha -= 5;
			particle[i].speed -= 0.08f;
		}
	}
	}
}

void Block::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (isDamage == false) {
		DrawGraph(pos.x, pos.y, nodamage, true);
	}
	else {
		DrawGraph(pos.x, pos.y, damage, true);
	}
    //DrawBox(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, GetColor(0, 255, 0), true);
    DrawFormatString(0, 15, GetColor(0, 255, 255), "player : %f/%f\n", pos.x, pos.y);
	
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (particle[i].isAlive == 1) {
			//�e�̂̃A���t�@�l�ɂ���ău�����h���[�h�̒l��ς��Ă���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, particle[i].alpha);
			DrawGraph(
				particle[i].transform.x,
				particle[i].transform.y,
				g1,
				TRUE
			);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}