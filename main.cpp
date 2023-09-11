#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "GameJam2023";

const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// Log.tex����������
	SetOutApplicationLogValidFlag(FALSE);

	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0xFF, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	//�~���^�m�F�pgit�m�F�p
	
	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char prev[256] = { 0 };

	//�Q�[�����[�v�p
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

	//�X�e�[�W�I��v�ϐ�
	const int STAGE_MINX = 0;
	const int STAGE_MAXX = 3;
	const int STAGE_MINY = 0;
	const int STAGE_MAXY = 1;
	const int STAGE_MIN = 0;
	const int STAGE_MAX = 7;

	//�]���t�����邽�߂̃����N
	const int RANK_A = 5;
	const int RANK_B = 10;
	const int RANK_C = 20;

	bool A = false;
	bool B = false;
	bool C = false;
	//��r���邽�߂̍s���ϐ����ƂŕύX���邱��
	int movement = 0;



	//�r���ōő�ƍŏ���ύX���邽�߂̕ϐ�
	int oneTtwoMin = 0;
	int oneTtwoMax = 0;

	int selectStageX = STAGE_MINX;
	int selectStageY = STAGE_MINY;
	int selectStage = STAGE_MINX;

	int graphSize = 128*2;
	int graphX = 176;
	int graphY = 128;

	bool isPlay = false;
	// �Q�[�����[�v
	while (true)
	{
		ClearDrawScreen();
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			prev[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);
		//---------  ��������Ƀv���O�������L�q  ---------//

		//�X�V
#pragma region
		switch (gameState)
		{

		case title:
			isPlay = false;
			//���̃V�[����
			if (keys[KEY_INPUT_RETURN] == 1 && prev[KEY_INPUT_RETURN] == 0)
			{
				gameState = select;
			}
			//pause�p
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			break;
		case select:
			//���̃V�[���ցi����j
			if (keys[KEY_INPUT_RETURN] == 1 && prev[KEY_INPUT_RETURN] == 0)
			{
				gameState = game;
			}
			//�X�e�[�W�I������
			//�E�ɍs��
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
			//���ɍs��
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

			//��ɍs��
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
			//���ɍs��
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


			//�X�e�[�W����
			
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
			//pause�p
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			break;
		case game:
			//���̃V�[����
			if (keys[KEY_INPUT_RETURN] == 1 && prev[KEY_INPUT_RETURN] == 0)
			{
				gameState = clear;
			}
			isPlay = true;
			if (1)//�����ɃN���A�t���O������
			{
				//�I�����ꂽ�X�e�[�W���v���C
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
			//pause�p
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			//�����N�m�肳����

			break;
		case clear:
			isPlay = false;
			//���̃V�[����
			if (keys[KEY_INPUT_RETURN] == 1 && prev[KEY_INPUT_RETURN] == 0)
			{
				gameState = title;
			}
			//pause�p
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			break;
		case over:
			isPlay = false;
			//���̃V�[����
			if (keys[KEY_INPUT_RETURN] == 1 && prev[KEY_INPUT_RETURN] == 0)
			{
				gameState = title;
			}
			//pause�p
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				pauseState = gameState;
				gameState = pause;
			}

			break;
		case pause:
			//���ɖ߂�
			if (keys[KEY_INPUT_P] == 1 && prev[KEY_INPUT_P] == 0)
			{
				gameState = pauseState;
			}

			break;
		default:
			break;
		};
#pragma endregion�Q�[�����[�v����

#pragma region
		if (isPlay)
		{
			switch (selectStage)//�X�e�[�W
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
#pragma endregion�X�e�[�W����
		//�`��---------------
		switch (gameState)
		{

		case title://�^�C�g��
			DrawGraph(0, 0, titleTex, TRUE);

			break;
		case select://�X�e�[�W�I�����
			DrawGraph(0, 0, selectTex, TRUE);

			for (int i = 0; i < 2; i++)//�X�e�[�W�\���̏c��
			{
				for (int j = 0; j < 4; j++)//�X�e�[�W�\�L�̉���
				{
					DrawGraph(graphX+graphSize*j, graphY+graphSize*i, mapTex, TRUE);
				}
			}
			//���I�����Ă�X�e�[�W�̘g
			DrawGraph(graphX + selectStageX * graphSize, graphY + selectStageY * graphSize, mapSelectTex, TRUE);
			
			break;
		case game://�v���C
			DrawGraph(0, 0, gameTex, TRUE);

			break;
		case clear://�Q�[���N���A
			DrawGraph(0, 0, clearTex, TRUE);
			//�����Ń����N��\��

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
		case over://�Q�[���I�[�o�[
			DrawGraph(0, 0, overTex, TRUE);

			break;
		case pause://�|�[�Y
			DrawGraph(0, 0, pauseTex, TRUE);

			break;
		default:
			break;
		};


		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;

	
}


