#pragma once
#include"Block.h"

class Tetris
{
public://�ÓI�����o�ϐ�
	static const int width = 12;
	static const int height = 16;

public:
	//������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();


private:
	int map[height][width];
	int r = 32;
	Vector2 pos;
};

