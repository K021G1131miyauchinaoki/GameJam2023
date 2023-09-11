#pragma once
#define WIDHT 15
#define HEIGHT 10

class Map
{
public:
	//リセット
	void Reset();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw();
	//クリア判定
	bool IsClear() { return isClear; }
	//次のマップ番号取得
	int GetNextMap(int height, int widht) { return object[height][widht]; }
	//次々のマップ
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