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
	//particle[MAX_PARTICLE].angle += 1;

	//��ʂ̒��S����Particle�𔭐�������A�����Ƃ��Ă͕����e�̏����Ǝ��Ă���
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (particle[i].isAlive == 0) {
			particle[i].isAlive = 1;
			/*particle[i].transform.x = WIN_WIDTH / 2;
			particle[i].transform.y = WIN_HEIGHT / 2;*/
			particle[i].transform.x = pos.x;
			particle[i].transform.y = pos.y;
			particle[i].transform.radius = 1;
			particle[i].angle = rand() % 361;	// �p�x�������_���Ō��߂�
			
			particle[i].alpha = 255;			// �����x�����Z�b�g
			particle[i].color = GetColor(255, 255, 255);
			break;
		}
	}

	//�����t���O���I���Ȃ�
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (particle[i].isAlive == 1) {
			//�p�x(angle)�ɂ���Ĉړ�

			particle[i].transform.x += cos(particle[i].angle) * particle[i].speed;
			//particle[i].transform.y += sin(particle[i].angle) * particle[i].speed;

			particle[i].transform.y += sin(particle[i].angle) * particle[i].speed;
			particle[i].transform.radius = 5;		//�~�̃T�C�Y��傫������
			particle[i].alpha -= 2;				//���񂾂񓧖��ɂ���

			//��ʊO�ɏo����������̓A���t�@�l��0�ȉ��ɂȂ�����
			if (particle[i].transform.x + particle[i].transform.radius <= 0 ||
				particle[i].transform.x - particle[i].transform.radius >= 450 ||
				particle[i].transform.y + particle[i].transform.radius <= 0 ||
				particle[i].transform.y - particle[i].transform.radius >= 600 ||
				particle[i].alpha <= 0) {
				particle[i].isAlive = 0;
			}
		}
	}

}

void Block::Draw()
{
    DrawBox(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, GetColor(0, 255, 0), true);
    DrawFormatString(0, 15, GetColor(0, 255, 255), "player : %f/%f\n", pos.x, pos.y);

	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (particle[i].isAlive == 1) {
			//�e�̂̃A���t�@�l�ɂ���ău�����h���[�h�̒l��ς��Ă���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
			DrawGraph(
				particle[i].transform.x,
				particle[i].transform.y,
				g1,
				TRUE
			);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

			DrawGraph(pos.x - radius, pos.y - radius, nodamage, true);
		}
	}
}