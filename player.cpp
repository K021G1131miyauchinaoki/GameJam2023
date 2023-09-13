#include "player.h"

void Player::Initialize()
{
	initialPos = { 60,90 };//マップチップでいうところの[0][0]の座標
	radius = 30;		// 半径
	endframe = 10.0f;
	//煙
	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		particle[i].transform.x = 0;
		particle[i].transform.y = 0;
		particle[i].radius = 7;
		particle[i].speed = 20.0f;
		particle[i].isAlive = false;
		particle[i].angle = 0;
		particle[i].alpha = 255;
		particle[i].color = GetColor(255, 255, 255);
	}

	LoadDivGraph("Resource/Player/player.png", 8, 4, 2, 60, 60, graphHandle);
	soundHandle[0] = LoadSoundMem("Resource/BGM/playerMove.mp3");
	soundHandle[1] = LoadSoundMem("Resource/BGM/Kick.mp3");
}

void Player::Reset(int num) {
	switch (num)
	{
	case 0:
		pos = { initialPos.x + 421,initialPos.y + 61 };
	case 1:
		pos = { initialPos.x + 541,initialPos.y +181 };
	case 2:
		pos = { initialPos.x + 541,initialPos.y + 181 };
	case 3:
		pos = { initialPos.x + 541,initialPos.y + 181 };
	case 4:
		pos = { initialPos.x + 541,initialPos.y + 181 };
	case 5:
		pos = { initialPos.x + 541,initialPos.y + 181 };
	case 6:
		pos = { initialPos.x + 541,initialPos.y + 181 };
	case 7:
		pos = { initialPos.x + 541,initialPos.y + 181 };
	default:
		break;
	}
		// 中心座標
	//イージング
	easingflag = false;
	frame = 0;
	KickTimer = 0;
	isdir = 0;		//方向管理フラグ  0 = 右　1 = 左　2 = 上　3 = 下
	isKick = false;
	isMove = false;		//移動管理フラグ
}

void Player::Update(char* keys, char* oldkey)
{
	Smoke(keys, oldkey);
	Move(keys, oldkey);
	playerArray.x = static_cast<int>((pos.x - initialPos.x) / 60);
	playerArray.y = static_cast<int>((pos.y - initialPos.y) / 60);

}

void Player::Draw()
{
	if (isdir == 0)//右
	{
		DrawGraph(pos.x - radius, pos.y - radius, graphHandle[2], true);
		if (KickTimer != 0)
		{
			DrawGraph(pos.x - radius, pos.y - radius, graphHandle[6], true);
		}
	}
	else if (isdir == 1)//左
	{
		DrawGraph(pos.x - radius, pos.y - radius, graphHandle[1], true);
		if (KickTimer != 0)
		{
			DrawGraph(pos.x - radius, pos.y - radius, graphHandle[5], true);
		}
	}
	else if (isdir == 2)//上
	{
		DrawGraph(pos.x - radius, pos.y - radius, graphHandle[3], true);
		if (KickTimer != 0)
		{
			DrawGraph(pos.x - radius, pos.y - radius, graphHandle[7], true);
		}
	}
	else//下
	{
		DrawGraph(pos.x - radius, pos.y - radius, graphHandle[0], true);
		if (KickTimer != 0)
		{
			DrawGraph(pos.x - radius, pos.y - radius, graphHandle[4], true);
		}
	}
	
	for (int i = 0; i < 5; i++) {
		if (jumpParticle[i].isAlive == 1) {
			//各個体のアルファ値によってブレンドモードの値を変えている
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, jumpParticle[i].alpha);
			DrawGraph(
				jumpParticle[i].transform.x,
				jumpParticle[i].transform.y,
				graphHandle[0],
				TRUE
			);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//DrawFormatString(0, 0, GetColor(255, 0, 0), "player : %f/%f\n", playerArray.x, playerArray.y);

}

void Player::Move(char* keys, char* oldkey)
{
	isKick = false;
	int num = 0;
	startX = pos.x;
	startY = pos.y;
	//StopSoundMem(soundHandle[1]);
	//移動
	if (!map->IsClear())
	{
		if (keys[KEY_INPUT_RIGHT] && !oldkey[KEY_INPUT_RIGHT] && easingflag == false)
		{
			if (map->GetNextMap(static_cast<int>(playerArray.y), static_cast<int>(playerArray.x) + 1) == 0)
			{
				//イージング
				easingflag = true;
				endX = pos.x += 60;
			}
			else if (map->GetNextMap(playerArray.y, playerArray.x + 1) >= 4
				&& map->GetAfterNextMap(playerArray.y, playerArray.x + 2) == 0
				&& map->GetNextMap(playerArray.y, playerArray.x + 1) < 10)
			{
				//コードが長くなるのでGetNextMapを変数に格納
				num = map->GetNextMap(playerArray.y, playerArray.x + 1);
				//次々マップチップに次のマップチップを代入
				map->SetAfterNextMap(playerArray.y, playerArray.x + 2, num);
				//次のマップチップに0を代入
				map->SetNextMap(playerArray.y, playerArray.x + 1);
				isKick = true;
			}
			isdir = 0;
		}
		else if (keys[KEY_INPUT_LEFT] && !oldkey[KEY_INPUT_LEFT] && easingflag == false)
		{
			if (map->GetNextMap(static_cast<int>(playerArray.y), static_cast<int>(playerArray.x) - 1) == 0)
			{
				//イージング
				easingflag = true;
				endX = pos.x -= 60;
			}
			else if (map->GetNextMap(playerArray.y, playerArray.x - 1) >= 4
				&& map->GetAfterNextMap(playerArray.y, playerArray.x - 2) == 0
				&& map->GetNextMap(playerArray.y, playerArray.x - 1) < 10)
			{
				num = map->GetNextMap(playerArray.y, playerArray.x - 1);
				map->SetAfterNextMap(playerArray.y, playerArray.x - 2, num);
				map->SetNextMap(playerArray.y, playerArray.x - 1);
				isKick = true;
			}
			isdir = 1;
		}
		else if (keys[KEY_INPUT_UP] && !oldkey[KEY_INPUT_UP] && easingflag == false)
		{
			if (map->GetNextMap(static_cast<int>(playerArray.y) - 1, static_cast<int>(playerArray.x)) == 0)
			{
				//イージング
				easingflag = true;
				endX = pos.y -= 60;
			}
			else if (map->GetNextMap(playerArray.y - 1, playerArray.x) >= 4
				&& map->GetAfterNextMap(playerArray.y - 2, playerArray.x) == 0
				&& map->GetNextMap(playerArray.y - 1, playerArray.x) < 10)
			{
				num = map->GetNextMap(playerArray.y - 1, playerArray.x);
				map->SetAfterNextMap(playerArray.y - 2, playerArray.x, num);
				map->SetNextMap(playerArray.y - 1, playerArray.x);
				isKick = true;
			}
			isdir = 2;
		}

		else if (keys[KEY_INPUT_DOWN] && !oldkey[KEY_INPUT_DOWN] && easingflag == false)
		{
			if (map->GetNextMap(static_cast<int>(playerArray.y) + 1, static_cast<int>(playerArray.x)) == 0)
			{
				//イージング
				easingflag = true;
				endX = pos.y += 60;
			}
			else if (map->GetNextMap(playerArray.y + 1, playerArray.x) >= 4
				&& map->GetAfterNextMap(playerArray.y + 2, playerArray.x) == 0
				&& map->GetNextMap(playerArray.y + 1, playerArray.x) < 10)
			{
				num = map->GetNextMap(playerArray.y + 1, playerArray.x);
				map->SetAfterNextMap(playerArray.y + 2, playerArray.x, num);
				map->SetNextMap(playerArray.y + 1, playerArray.x);
				isKick = true;
			}

			isdir = 3;
		}

		if (easingflag == 1)
		{
			StopSoundMem(soundHandle[0]);
			frame++;
			x = frame / endframe;
			y = frame / endframe;
			if (isdir == 0 || isdir == 1)
			{
				ChangeVolumeSoundMem(130, soundHandle[0]);
				PlaySoundMem(soundHandle[0], DX_PLAYTYPE_BACK, true);
				pos.x = startX + (endX - startX) * (EZ(x));
			}
			else
			{
				ChangeVolumeSoundMem(130, soundHandle[0]);
				PlaySoundMem(soundHandle[0], DX_PLAYTYPE_BACK, true);
				pos.y = startY + (endX - startY) * (EZ(y));
			}
			if (frame > endframe)
			{
				easingflag = 0;
				frame = 0;
			}
		}

		if (isKick)
		{
			ChangeVolumeSoundMem(150, soundHandle[1]);
			PlaySoundMem(soundHandle[1], DX_PLAYTYPE_BACK, true);
			KickTimer = 10;
		}
		if (KickTimer != 0)
		{
			KickTimer--;
			if (KickTimer <= 0)
			{
				KickTimer = 0;
			}
		}
	}
}

void Player::Smoke(char* keys, char* oldkey)
{
	//if (isMove == false) {
	//		for (int i = 0; i < 5; i++) {
	//			if (jumpParticle[i].isAlive == 0) {
	//				jumpParticle[i].isAlive = 1;
	//				jumpParticle[i].transform.x = pos.x + rand() % 30-30;
	//				jumpParticle[i].transform.y = pos.y + rand() % 10;
	//				jumpParticle[i].angle = rand() % 100;	// 角度をランダムで決める
	//				jumpParticle[i].speed = rand() % 2;
	//				jumpParticle[i].alpha = 250;			// 透明度をリセット
	//				jumpParticle[i].color = GetColor(255, 255, 255);
	//				break;
	//			}
	//		}
	//		//生存フラグがオンなら
	//		for (int i = 0; i < 5; i++) {
	//			if (jumpParticle[i].isAlive == 1) {
	//				jumpParticle[i].alpha -= 20;
	//			}
	//		}
	//	}
}
