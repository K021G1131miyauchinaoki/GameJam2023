#pragma once
#include"Block.h"

class Tetris
{
public://�ÓI�����o�ϐ�
	static const int width = 14;
	static const int height = 17;

public:
	//������
	void Initialize();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();


private:
	int map[height][width];
	int r = 8;
	Vector2 pos;
};

