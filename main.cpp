#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "GameJam2023";

// ウィンドウ横幅
const int WIN_WIDTH = 450;

// ウィンドウ縦幅
const int WIN_HEIGHT = 600;

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
	//ミヤタ確認用git確認用
	
	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char prev[256] = { 0 };

	//ゲームループ用
	enum  GameState
	{
		title,
		select,
		game,
		over,
		pause,

	};
	enum Stage
	{
		zero,
		one,
		two,
		three,
		four,
		five
	};

	void GameReset();
	GameState gameState = title;
	GameState pauseState;

	int titleTex = LoadGraph("Resource/GameStates/title.png");
	int selectTex = LoadGraph("Resource/GameStates/select.png");
	int gameTex = LoadGraph("Resource/GameStates/game.png");
	int overTex = LoadGraph("Resource/GameStates/over.png");
	int pauseTex = LoadGraph("Resource/GameStates/pause.png");

	//ステージ選択要変数
	const int STAGE_MIN = 0;
	const int STAGE_MAX = 5;
	int selectStage = STAGE_MIN;

	bool isPlay = false;
	// ゲームループ
	while (true)
	{
		ClearDrawScreen();
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i)
		{
			prev[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
		//---------  ここからにプログラムを記述  ---------//

		//更新
#pragma region
		switch (gameState)
		{

		case title:
			isPlay = false;
			//次のシーンへ
			if (keys[KEY_INPUT_RETURN] == 1 && prev[KEY_INPUT_RETURN] == 0)
			{
				gameState = select;
			}
			//pause用
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			break;
		case select:
			//次のシーンへ（決定）
			if (keys[KEY_INPUT_RETURN] == 1 && prev[KEY_INPUT_RETURN] == 0)
			{
				gameState = game;
			}
			//ステージ選択する
			//右に行く
			if (keys[KEY_INPUT_RIGHT] == 1 && prev[KEY_INPUT_RIGHT] == 0)
			{
				selectStage ++;
				if (selectStage >= STAGE_MAX)
				{
					selectStage = STAGE_MAX;
				}
			}
			//左に行く
			if (keys[KEY_INPUT_LEFT] == 1 && prev[KEY_INPUT_LEFT] == 0)
			{
				selectStage--;
				if (selectStage >= STAGE_MIN)
				{
					selectStage = STAGE_MIN;
				}
			}



			//pause用
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			break;
		case game:
			//次のシーンへ
			if (keys[KEY_INPUT_RETURN] == 1 && prev[KEY_INPUT_RETURN] == 0)
			{
				gameState = over;
			}
			isPlay = true;
			//選択されたステージをプレイ

			if(selectStage)
			//pause用
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			break;
		case over:
			isPlay = false;
			//次のシーンへ
			if (keys[KEY_INPUT_RETURN] == 1 && prev[KEY_INPUT_RETURN] == 0)
			{
				gameState = title;
			}
			//pause用
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			break;
		case pause:
			//元に戻る
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				gameState = pauseState;
			}

			break;
		default:
			break;
		};
#pragma endregionゲームループ処理
#pragma region
		if (isPlay)
		{
			switch (selectStage)//ステージ
			{
			case 0:
				

				break;
			case 1:
				

				break;
			case 2:
				

				break;
			case 3:
				

				break;
			case 4:
				

				break;
			case 5:
				

				break;
			default:
				break;
			}
		}
#pragma endregionステージ処理
		//描画---------------
		switch (gameState)
		{

		case title://タイトル
			DrawGraph(0, 0, titleTex, TRUE);

			break;
		case select://ステージ選択画面
			DrawGraph(0, 0, selectTex, TRUE);

			break;
		case game://プレイ
			DrawGraph(0, 0, gameTex, TRUE);

			break;
		case over://ゲームオーバー
			DrawGraph(0, 0, overTex, TRUE);

			break;
		case pause://ポーズ
			DrawGraph(0, 0, pauseTex, TRUE);

			break;
		default:
			break;
		};


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

	void GameReset()
	{
		isPlay = false;
		int selectStage = STAGE_MIN;
	}
}


