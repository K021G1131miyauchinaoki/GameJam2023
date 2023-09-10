#include "DxLib.h"
#include "player.h"
#include "Count.h"
#include"map.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "GameJam2023";


// �E�B���h�E����
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// Log.texを消す処理
	SetOutApplicationLogValidFlag(FALSE);

	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);


	
	// 画像などのリソースデータの変数宣言と読み込み

	// ゲームループで使う変数の宣言
	map* m = new map();
	m->Initialize();
	m->Reset();
	Player* player = new Player();
	player->Initialize();
	
	Count* count = new Count();
	count->Initialize();
	// 最新のキーボード情報用

	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	//ゲームループ用
	enum  GameState
	{
		title,
		game,
		over,
		pause,

	};
	GameState gameState = title;
	GameState pauseState;

	int titleTex = LoadGraph("Resource/GameStates/title.png");
	int gameTex = LoadGraph("Resource/GameStates/game.png");
	int overTex = LoadGraph("Resource/GameStates/over.png");
	int pauseTex = LoadGraph("Resource/GameStates/pause.png");
	// ゲームループ
	while (true)
	{
		ClearDrawScreen();
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
		//---------  ここからにプログラムを記述  ---------//

		//更新
		switch (gameState)
		{

		case title:
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				gameState = game;
			}
			//pause用
			if (keys[KEY_INPUT_P] == 1 && oldkeys[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			break;
		case game:
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				gameState = over;
			}
			//pause用
			if (keys[KEY_INPUT_P] == 1 && oldkeys[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}
      player->Update(keys,prev);

		  count->Update(keys, prev);
			m->Update();

			break;
		case over:
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				gameState = title;
			}
			//pause用
			if (keys[KEY_INPUT_P] == 1 && oldkeys[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			break;
		case pause:
			if (keys[KEY_INPUT_P] == 1 && oldkeys[KEY_INPUT_P] == 0)
			{
				gameState = pauseState;
			}

			break;
		default:
			break;
		};
		
		//描画---------------
		switch (gameState)
		{

		case title:
			DrawGraph(0, 0, titleTex, TRUE);

			break;
		case game:
			//DrawGraph(0, 0, gameTex, TRUE);
			m->Draw();
			player->Draw();
			count->Draw();
			break;
		case over:
			DrawGraph(0, 0, overTex, TRUE);

			break;
		case pause:
			DrawGraph(0, 0, pauseTex, TRUE);

			break;
		default:
			break;
		};

		

		for (int i = 0; i < 30; i++)
		{
			//DrawLine(0, 1 * (i * 55.3), WIN_WIDTH, 1 * (i * 55.3), GetColor(255, 0, 0));
			//DrawLine(1 * (i * 55.6), 0, 1 * (i * 55.6), WIN_HEIGHT, GetColor(255, 0, 0));
		}
		

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
