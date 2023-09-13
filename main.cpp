#include "DxLib.h"
#include "player.h"
#include "Count.h"
#include"Map.h"
#include "Easing.h"
#include "SceneChange.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "3028_カイロボ";

const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;


struct Tex
{
	double x;
	double y;

	int sizex;
	int sizey;

	int time;
	int Maxtime;

	bool change;
	bool flag;
};

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
	int soundHandle[4];
	soundHandle[0] = LoadSoundMem("Resource/BGM/taitle.mp3");
	soundHandle[1] = LoadSoundMem("Resource/BGM/gamePlay.mp3");
	soundHandle[2] = LoadSoundMem("Resource/BGM/clear.mp3");
	soundHandle[3] = LoadSoundMem("resource/BGM/select.mp3");


	// ゲームループで使う変数の宣言
	//マップ
	Map* map = new Map();
	map->Initialize();
	//プレイヤー
	Player* player = new Player();
	player->Initialize();
	player->SetMap(map);
	//カウント
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
		select,
		game,
		clear,
	};
	

	void GameReset();
	GameState gameState = title;
	GameState pauseState;
	GameState next;

	int titleTex = LoadGraph("Resource/GameStates/title.png");
	int selectTex = LoadGraph("Resource/GameStates/select.png");
	int gameTex = LoadGraph("Resource/GameStates/game.png");
	int overTex = LoadGraph("Resource/GameStates/over.png");
	int clearTex = LoadGraph("Resource/GameStates/clear.png");
	int pauseTex = LoadGraph("Resource/GameStates/pause.png");
	int mapTex = LoadGraph("Resource/Map/stage.png");
	int mapSelectTex = LoadGraph("Resource/Map/select.png");

	int sceneTex = LoadGraph("Resource/Scene/TitleName.png");
	int backTex = LoadGraph("Resource/Scene/back.png");

	int numTex= LoadGraph("Resource/Map/num.png");


	const int STAGE_MINX = 0;
	const int STAGE_MAXX = 3;
	const int STAGE_MINY = 0;
	const int STAGE_MAXY = 1;
	const int STAGE_MIN = 0;
	const int STAGE_MAX = 7;

	const int RANK_A = 5;
	const int RANK_B = 10;
	const int RANK_C = 20;

	bool A = false;
	bool B = false;
	bool C = false;
	
	int movement = 0;
	
	int oneTtwoMin = 0;
	int oneTtwoMax = 3;

	int selectStageX = STAGE_MINX;
	int selectStageY = STAGE_MINY;
	int selectStage = STAGE_MINX;

	int graphSize = 128*2;
	int graphX = 176;
	int graphY = 128;

	bool isPlay = false;
	//シーン移行用

	int texX = 0;
	int texY = 0;

	bool endflag = false;
	int time = 0;
	int MaxTime = 60;
	float TexX;
	float TexY;
	
	int timeS = 0;
	float TexXS;
	float TexYS;

	Tex sceneTitle;
	sceneTitle.x = 0 - 1280;
	sceneTitle.y = 0 ;
	sceneTitle.sizex = 1280;
	sceneTitle.sizey = 720;
	sceneTitle.Maxtime = 120;
	sceneTitle.time = 0;
	sceneTitle.flag = false;

	Tex back;
	back.x = 0 - 1280;
	back.y = 0;
	back.sizex = 1280;
	back.sizey = 720;
	back.Maxtime = 120;
	back.time = 0;
	back.flag = false;
	back.change = false;

	bool initFlag1 = false;
	bool initFlag = false;
	int isbgm = 0;

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
		//シーン移行用


#pragma region
		//更新
		switch (gameState)
		{

		case title:
			isPlay = false;
			
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				ChangeVolumeSoundMem(120, soundHandle[3]);
				PlaySoundMem(soundHandle[3], DX_PLAYTYPE_BACK, true);
				next = select;
				sceneTitle.flag = true;
				
			}

			break;
		case select:
			
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				ChangeVolumeSoundMem(120, soundHandle[3]);
				PlaySoundMem(soundHandle[3], DX_PLAYTYPE_BACK, true);
				next = game;
				sceneTitle.flag = true;
				//gameState = game;
			}
			
			if (keys[KEY_INPUT_RIGHT] == 1 && oldkeys[KEY_INPUT_RIGHT] == 0)
			{
				ChangeVolumeSoundMem(120, soundHandle[3]);
				PlaySoundMem(soundHandle[3], DX_PLAYTYPE_BACK, true);
				selectStageX ++;
				//selectStage++;
				if (selectStageX >= STAGE_MAXX)
				{
					selectStageX = STAGE_MAXX;
					//selectStage = STAGE_MAXX;
				}
			}
			
			if (keys[KEY_INPUT_LEFT] == 1 && oldkeys[KEY_INPUT_LEFT] == 0)
			{
				ChangeVolumeSoundMem(120, soundHandle[3]);
				PlaySoundMem(soundHandle[3], DX_PLAYTYPE_BACK, true);
				selectStageX--;
				//selectStage++;
				if (selectStageX <= STAGE_MINX)
				{
					selectStageX = STAGE_MINX;
					//selectStage = STAGE_MINX;
				}
			}

			
			if (keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0)
			{
				ChangeVolumeSoundMem(120, soundHandle[3]);
				PlaySoundMem(soundHandle[3], DX_PLAYTYPE_BACK, true);
				selectStageY++;
				//selectStage +=4;
				if (selectStageY >= STAGE_MAXY)
				{
					selectStageY = STAGE_MAXY;
					//selectStage = STAGE_MAXY;
				}
			}
			
			if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0)
			{
				ChangeVolumeSoundMem(120, soundHandle[3]);
				PlaySoundMem(soundHandle[3], DX_PLAYTYPE_BACK, true);
				selectStageY--;
				//selectStage -= 4;
				if (selectStageY <= STAGE_MINY)
				{
					selectStageY = STAGE_MINY;
					//selectStage = STAGE_MINY;

				}
			}
			
			if (keys[KEY_INPUT_RIGHT] == 1 && oldkeys[KEY_INPUT_RIGHT] == 0)
			{
				selectStage++;
				if (selectStage >= oneTtwoMax)
				{
					selectStage = oneTtwoMax;
				}
			}

			if (keys[KEY_INPUT_LEFT] == 1 && oldkeys[KEY_INPUT_LEFT] == 0)
			{
				
				selectStage--;
				if (selectStage <= oneTtwoMin)
				{
					
					selectStage = oneTtwoMin;
				}
			}
			if (keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0)
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

				if (initFlag1 == false) {
					//1回だけ行う処理
					initFlag1 = true;
					selectStage += 4;
					initFlag = false;
				}
				/*if(selectStage >= oneTtwoMax)
				{
					selectStage = oneTtwoMax;
				}*/
			}
			if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0)
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

				if (initFlag == false) {
					//1回だけ行う処理
					initFlag = true;
					selectStage -= 4;
					initFlag1 = false;
				}
				
				/*if (selectStage <= oneTtwoMin)
				{
					selectStage = oneTtwoMin;

				}*/

				}
			
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				gameState = game;
				player->Reset();
				count->Reset();
				map->Reset(selectStage);
			}

			break;
		case game:
			//selectに戻る用
			if (keys[KEY_INPUT_T] == 1 && oldkeys[KEY_INPUT_T] == 0)
			{
				pauseState = gameState;
				gameState = select;
			}
			if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0)
			{
				player->Reset();
				count->Reset();
				map->Reset(selectStage);

			}
			isPlay = true;
			if (1)//ランキング
			{
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

			//更新処理
			player->Update(keys, oldkeys);
			count->Update(keys, oldkeys);
			map->Update();
			break;
		case clear:
			isPlay = false;
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				ChangeVolumeSoundMem(120, soundHandle[3]);
				PlaySoundMem(soundHandle[3], DX_PLAYTYPE_BACK, true);
				next = title;
				sceneTitle.flag = true;
			}
			
			break;
		};
#pragma endregion �Q�[�����[�v����

#pragma region
		if (isPlay)
		{
			switch (selectStage)
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
#pragma endregion �X�e�[�W����




		if (sceneTitle.flag)
		{
			back.change = false;
			if (sceneTitle.time >= sceneTitle.Maxtime)
			{
				sceneTitle.time = sceneTitle.Maxtime;
				back.change = true;
				
			}
			else
			{
				sceneTitle.time++;
			}


			sceneTitle.x = Easing::In(sceneTitle.x , 0, sceneTitle.time, sceneTitle.Maxtime);
			back.x = Easing::In(back.x, 0, sceneTitle.time, sceneTitle.Maxtime);

			
		}
		else
		{
			sceneTitle.time = 0;
		}

		if (back.change)
		{
			sceneTitle.flag = false;
			gameState = next;
			if (back.time >= back.Maxtime -40)
			{
				back.change = false;
				back.time = back.Maxtime;
				
			}
			else
			{
				back.time++;
			}

			sceneTitle.x = Easing::In(sceneTitle.x, sceneTitle.sizex * -1, back.time, sceneTitle.Maxtime);
			back.x = Easing::In(back.x, back.sizex * -1, back.time, back.Maxtime);

		}

		if (sceneTitle.flag == false && back.change == false)
		{
			sceneTitle.time = 0;
			back.time = 0;

			sceneTitle.x = 0 - 1280;
			sceneTitle.y = 0;

		}

		//描画---------------
		switch (gameState)
		{
			
		case title:
			if (isbgm == 0)
			{
				ChangeVolumeSoundMem(80, soundHandle[0]);
				PlaySoundMem(soundHandle[0], DX_PLAYTYPE_LOOP, true);
				isbgm += 1;
			}

			DrawGraph(0, 0, titleTex, TRUE);
		
			break;

		case select:
			if (isbgm == 1)
			{
				StopSoundMem(soundHandle[0]);
				StopSoundMem(soundHandle[2]);
				ChangeVolumeSoundMem(80, soundHandle[1]);
				PlaySoundMem(soundHandle[1], DX_PLAYTYPE_LOOP, true);
				isbgm += 1;
			}

			DrawGraph(0, 0, selectTex, TRUE);

			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					DrawGraph(graphX+graphSize*j, graphY+graphSize*i, mapTex, TRUE);
					
					DrawRectGraph(graphX + graphSize * j, graphY + graphSize * i, 128 * (i + j + 3 * i), 0, 128, 128, numTex, true, false);
				}
			}
			
			DrawGraph(graphX + selectStageX * graphSize, graphY + selectStageY * graphSize, mapSelectTex, TRUE);
			
			break;
        
		case game:
			count->Draw();
			map->Draw();
			player->Draw();
			break;
        
		case clear:
			if (isbgm == 2)
			{
				StopSoundMem(soundHandle[1]);
				ChangeVolumeSoundMem(80, soundHandle[2]);
				PlaySoundMem(soundHandle[2], DX_PLAYTYPE_LOOP, true);
				isbgm -= 1;
			}

			DrawGraph(0, 0, clearTex, TRUE);
			

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
		default:
			break;
		};

		DrawGraph(back.x, back.y, backTex, TRUE);
		DrawGraph(sceneTitle.x, sceneTitle.y, sceneTex, TRUE);
		
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


