#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "GameJam2023";

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
	SetBackgroundColor(0x00, 0xFF, 0x00);

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
		clear,
		over,
		pause,

	};
	

	void GameReset();
	GameState gameState = title;
	GameState pauseState;

	int titleTex = LoadGraph("Resource/GameStates/title.png");
	int selectTex = LoadGraph("Resource/GameStates/select.png");
	int gameTex = LoadGraph("Resource/GameStates/game.png");
	int overTex = LoadGraph("Resource/GameStates/over.png");
	int clearTex = LoadGraph("Resource/GameStates/clear.png");
	int pauseTex = LoadGraph("Resource/GameStates/pause.png");
	int mapTex = LoadGraph("Resource/Map/stage.png");
	int mapSelectTex = LoadGraph("Resource/Map/select.png");

	//ステージ選択要変数
	const int STAGE_MINX = 0;
	const int STAGE_MAXX = 3;
	const int STAGE_MINY = 0;
	const int STAGE_MAXY = 1;
	const int STAGE_MIN = 0;
	const int STAGE_MAX = 7;

	//評価付けするためのランク
	const int RANK_A = 5;
	const int RANK_B = 10;
	const int RANK_C = 20;

	bool A = false;
	bool B = false;
	bool C = false;
	//比較するための行動変数あとで変更すること
	int movement = 0;



	//途中で最大と最小を変更するための変数
	int oneTtwoMin = 0;
	int oneTtwoMax = 0;

	int selectStageX = STAGE_MINX;
	int selectStageY = STAGE_MINY;
	int selectStage = STAGE_MINX;

	int graphSize = 128*2;
	int graphX = 176;
	int graphY = 128;

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
				selectStageX ++;
				//selectStage++;
				if (selectStageX >= STAGE_MAXX)
				{
					selectStageX = STAGE_MAXX;
					//selectStage = STAGE_MAXX;
				}
			}
			//左に行く
			if (keys[KEY_INPUT_LEFT] == 1 && prev[KEY_INPUT_LEFT] == 0)
			{
				selectStageX--;
				//selectStage++;
				if (selectStageX <= STAGE_MINX)
				{
					selectStageX = STAGE_MINX;
					//selectStage = STAGE_MINX;
				}
			}

			//上に行く
			if (keys[KEY_INPUT_DOWN] == 1 && prev[KEY_INPUT_DOWN] == 0)
			{
				selectStageY++;
				//selectStage +=4;
				if (selectStageY >= STAGE_MAXY)
				{
					selectStageY = STAGE_MAXY;
					//selectStage = STAGE_MAXY;
				}
			}
			//下に行く
			if (keys[KEY_INPUT_UP] == 1 && prev[KEY_INPUT_UP] == 0)
			{
				selectStageY--;
				//selectStage -= 4;
				if (selectStageY <= STAGE_MINY)
				{
					selectStageY = STAGE_MINY;
					//selectStage = STAGE_MINY;

				}
			}


			//ステージ判定
			
			if (keys[KEY_INPUT_RIGHT] == 1 && prev[KEY_INPUT_RIGHT] == 0)
			{
				selectStage++;
				if (selectStage >= oneTtwoMax)
				{
					selectStage = oneTtwoMax;
				}
			}

			if (keys[KEY_INPUT_LEFT] == 1 && prev[KEY_INPUT_LEFT] == 0)
			{
				
				selectStage--;
				if (selectStage <= oneTtwoMin)
				{
					
					selectStage = oneTtwoMin;
				}
			}
			if (keys[KEY_INPUT_DOWN] == 1 && prev[KEY_INPUT_DOWN] == 0)
			{
				if (selectStageY)
				{
					oneTtwoMax = 7;
					oneTtwoMin = 4;
				}
				else
				{
					oneTtwoMax = 3;
					oneTtwoMin = 0;
				}
				selectStage += 4;
				if(selectStage >= oneTtwoMax)
					
				{
					selectStage = oneTtwoMax;
				}
			}
			if (keys[KEY_INPUT_UP] == 1 && prev[KEY_INPUT_UP] == 0)
			{
				if (selectStageY)
				{
					oneTtwoMax = 7;
					oneTtwoMin = 4;
				}
				else
				{
					oneTtwoMax = 3;
					oneTtwoMin = 0;
				}
				selectStage -= 4;
				if (selectStage <= oneTtwoMin)
				{
					selectStage = oneTtwoMin;
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
				gameState = clear;
			}
			isPlay = true;
			if (1)//ここにクリアフラグを入れる
			{
				//選択されたステージをプレイ
				if (movement < RANK_A)
				{
					A = TRUE;
				}
				else if (movement < RANK_B)
				{
					B = TRUE;
				}
				else if (movement < RANK_C)
				{
					C = TRUE;
				}
				else
				{
					C = TRUE;
				}
			}
			//pause用
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			//ランク確定させる

			break;
		case clear:
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
			case 6:


				break;
			case 7:


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

			for (int i = 0; i < 2; i++)//ステージ表示の縦列
			{
				for (int j = 0; j < 4; j++)//ステージ表記の横列
				{
					DrawGraph(graphX+graphSize*j, graphY+graphSize*i, mapTex, TRUE);
				}
			}
			//今選択してるステージの枠
			DrawGraph(graphX + selectStageX * graphSize, graphY + selectStageY * graphSize, mapSelectTex, TRUE);
			
			break;
		case game://プレイ
			DrawGraph(0, 0, gameTex, TRUE);

			break;
		case clear://ゲームクリア
			DrawGraph(0, 0, clearTex, TRUE);
			//ここでランクを表示

			if (A)
			{
				DrawGraph(0, 0, clearTex, TRUE);
			}
			if (B)
			{
				DrawGraph(0, 0, clearTex, TRUE);
			}
			if (C)
			{
				DrawGraph(0, 0, clearTex, TRUE);
			}





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

	
}


