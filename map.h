#pragma once
#define WIDHT 15
#define HEIGHT 10

class Map
{
public:
	//���Z�b�g
	void Reset();
	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//�N���A����
	bool IsClear() { return isClear; }
	//���̃}�b�v�ԍ��擾
	int GetNextMap(int height, int widht) { return object[height][widht]; }
	//���X�̃}�b�v
	int GetAfterNextMap(int height, int widht) { return object[height][widht]; }

	int SetNextMap(int height, int widht) { return object[height][widht]; }
	int SetAfterNextMap(int height, int widht) { return object[height][widht]; }
private:
	int answer[HEIGHT][WIDHT];
	int object[HEIGHT][WIDHT];
	int ground[HEIGHT][WIDHT];
	int r;
	int count;
	int blockTex;
	bool isClear;
	const int space = 30;
};