#include "player.h"

void Player::Initialize()
{
	initialPos = { 60,90 };//マップチップでいうところの[0][0]の座標
	pos = { initialPos.x+60,initialPos.y+60 };	// 中心座標
	radius = 30;		// 半径
	isdir = 0;		//方向管理フラグ  0 = 右　1 = 左　2 = 上　3 = 下
	isMove = false;		//移動管理フラグ
	//イージング
	easingflag = false;
	frame = 0;
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

	graphHandle = LoadGraph("Resource/jamtest.png");
}

void Player::Update(char* keys, char* oldkey)
{
	Smoke(keys, oldkey);
	Move(keys, oldkey);
	Kick(keys, oldkey);
	playerArray.x = static_cast<int>((pos.x - initialPos.x) / 60);
	playerArray.y = static_cast<int>((pos.y - initialPos.y) / 60);

}

void Player::Draw()
{
	DrawGraph(pos.x - radius, pos.y - radius, graphHandle, true);
	DrawBox(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, GetColor(255, 255, 255), false);
	for (int i = 0; i < 5; i++) {
		if (jumpParticle[i].isAlive == 1) {
			//各個体のアルファ値によってブレンドモードの値を変えている
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, jumpParticle[i].alpha);
			DrawGraph(
				jumpParticle[i].transform.x,
				jumpParticle[i].transform.y,
				graphHandle,
				TRUE
			);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawFormatString(0, 0, GetColor(255, 0, 0), "player : %f/%f\n", pos.x, pos.y);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "playerArray : %f\n", playerArray.y);
	DrawFormatString(0, 45, GetColor(0, 0, 0), "EZ : %d\n", easingflag);
	DrawFormatString(0, 60, GetColor(0, 0, 0), "EZframe : %d\n", frame);
	DrawFormatString(0, 75, GetColor(0, 0, 0), "EZendframe : %d\n", endframe);
}

void Player::Move(char* keys, char* oldkey)
{
	startX = pos.x;
	startY = pos.y;
	//移動
	if (keys[KEY_INPUT_RIGHT] && !oldkey[KEY_INPUT_RIGHT] && easingflag == false)
	{
		if (map->GetNextMap(static_cast<int>(playerArray.y), static_cast<int>(playerArray.x) + 1) == 0)
		{
			//イージング
			easingflag = true;
			endX = pos.x += 60;
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
		isdir = 3;
		
	}

	else
	{
	}

	if (easingflag == 1)
	{
		frame++;
		x = frame / endframe;
		y = frame / endframe;
		if (isdir == 0 || isdir == 1)
		{
			pos.x = startX + (endX - startX) * (EZ(x));
		}
		else
		{
			pos.y = startY + (endX - startY) * (EZ(y));
		}
		if (frame > endframe)
		{
			easingflag = 0;
			frame = 0;
		}
	}
	


	
	
}

void Player::Smoke(char* keys, char* oldkey)
{
	if (isMove == false) {
			for (int i = 0; i < 5; i++) {
				if (jumpParticle[i].isAlive == 0) {
					jumpParticle[i].isAlive = 1;
					jumpParticle[i].transform.x = pos.x + rand() % 30-30;
					jumpParticle[i].transform.y = pos.y + rand() % 10;
					jumpParticle[i].angle = rand() % 100;	// 角度をランダムで決める
					jumpParticle[i].speed = rand() % 2;
					jumpParticle[i].alpha = 250;			// 透明度をリセット
					jumpParticle[i].color = GetColor(255, 255, 255);
					break;
				}
			}
			//生存フラグがオンなら
			for (int i = 0; i < 5; i++) {
				if (jumpParticle[i].isAlive == 1) {
					jumpParticle[i].alpha -= 20;
				}
			}
		}
}

void Player::Kick(char* keys, char* oldkey)
{
	int num = 0;
	if (easingflag == false)
	{
		if (keys[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
		{
			if (isdir == 0)//右
			{
				if (map->GetNextMap(playerArray.y, playerArray.x + 1) >= 2
					&& map->GetAfterNextMap(playerArray.y, playerArray.x + 2) == 0)
				{
					//コードが長くなるのでGetNextMapを変数に格納
					num = map->GetNextMap(playerArray.y, playerArray.x + 1);
					//次々マップチップに次のマップチップを代入
					map->SetAfterNextMap(playerArray.y, playerArray.x + 2, num);
					//次のマップチップに0を代入
					map->SetNextMap(playerArray.y, playerArray.x + 1);
				}
			}
			else if (isdir == 1)//左
			{
				if (map->GetNextMap(playerArray.y, playerArray.x - 1) >= 2
					&& map->GetAfterNextMap(playerArray.y, playerArray.x - 2) == 0)
				{
					num = map->GetNextMap(playerArray.y, playerArray.x - 1);
					map->SetAfterNextMap(playerArray.y, playerArray.x - 2, num);
					map->SetNextMap(playerArray.y, playerArray.x - 1);
				}
			}
			else if (isdir == 2)//上
			{
				if (map->GetNextMap(playerArray.y - 1, playerArray.x) >= 2
					&& map->GetAfterNextMap(playerArray.y - 2, playerArray.x) == 0)
				{
					num = map->GetNextMap(playerArray.y - 1, playerArray.x);
					map->SetAfterNextMap(playerArray.y - 2, playerArray.x, num);
					map->SetNextMap(playerArray.y - 1, playerArray.x);
				}
			}
			else if (isdir == 3)//下
			{
				if (map->GetNextMap(playerArray.y + 1, playerArray.x) >= 2
					&& map->GetAfterNextMap(playerArray.y + 2, playerArray.x) == 0)
				{
					num = map->GetNextMap(playerArray.y + 1, playerArray.x);
					map->SetAfterNextMap(playerArray.y + 2, playerArray.x, num);
					map->SetNextMap(playerArray.y + 1, playerArray.x);
				}
			}
		}
	}
}
