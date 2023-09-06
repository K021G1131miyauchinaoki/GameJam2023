#pragma once
#include"Block.h"

class Tetris
{
public://�ÓI�����o�ϐ�
	static const int width = 14;
	static const int height = 17;
	static const int minoW = 1;
	static const int minoH = 2;

public:
	//������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();


private:
	int map[height][width];
	int display[height][width];
	int mino[minoH][minoW];
	int r = 8;
	int minoType, minoAngle;
	int minoX = 5, minoY = 0;
	int time;
	const int timer=30;
};

