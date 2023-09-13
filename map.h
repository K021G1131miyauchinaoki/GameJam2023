#pragma once
#define WIDHT 15
#define HEIGHT 10

class Map
{
public:
	//���Z�b�g
	void Reset(int num);
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
	//���̃}�b�v�ɒl���Z�b�g
	int SetNextMap(int height, int widht) { return object[height][widht] = 0; }
	//���X�̃}�b�v�ɒl���Z�b�g
	int SetAfterNextMap(int height, int widht, int num) { return object[height][widht] = num; }
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