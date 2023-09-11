#include "player.h"

void Player::Initialize()
{
	initialPos = { 60,90 };//マップチップでいうところの[0][0]の座標
	pos = { initialPos.x+60,initialPos.y+60 };	// 中心座標
	radius = 30;		// 半径
	speed = { 0,0 };	// 速度
	isdir = 0;		//方向管理フラグ  0 = 右　1 = 左　2 = 上　3 = 下
	isMove = false;		//移動管理フラグ
	//イージング
	easingflag = false;
	frame = 0;
	endframe = 50.0f;
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
	DrawFormatString(0, 15, GetColor(255, 255, 255), "playerArray : %f\n", playerArray.x);
	DrawFormatString(0, 30, GetColor(255, 255, 255), "playerArray : %f\n", playerArray.y);
	DrawFormatString(0, 45, GetColor(0, 0, 0), "EZ : %d\n", easingflag);
	DrawFormatString(0, 60, GetColor(0, 0, 0), "EZframe : %d\n", frame);
	DrawFormatString(0, 75, GetColor(0, 0, 0), "EZendframe : %d\n", endframe);
}

void Player::Move(char* keys, char* oldkey)
{
	speed = { 0 ,0 }; //移動を止める
	//移動
	if (keys[KEY_INPUT_RIGHT] && !oldkey[KEY_INPUT_RIGHT] && easingflag == false)
	{
		if (map->GetNextMap(static_cast<int>(playerArray.y), static_cast<int>(playerArray.x) + 1) == 0)
		{
			speed.x = 60; //DrawLineで引いた線に近い値
		}
		isdir = 0;
		//イージング
		frame = 0;
		easingflag = true;
		startX = pos.x;
		endX = pos.x+= 60;
	}
	else if (keys[KEY_INPUT_LEFT] && !oldkey[KEY_INPUT_LEFT] && easingflag == false)
	{
		if (map->GetNextMap(static_cast<int>(playerArray.y), static_cast<int>(playerArray.x) - 1) == 0)
		{
			speed.x = -60;
		}
		isdir = 1;
		//イージング
		frame = 0;
		easingflag = true;
		startX = pos.x;
		endX = pos.x -= 60;
	}
	else if (keys[KEY_INPUT_UP] && !oldkey[KEY_INPUT_UP] && easingflag == false)
	{
		if (map->GetNextMap(static_cast<int>(playerArray.y) - 1, static_cast<int>(playerArray.x)) == 0)
		{
			speed.y = -60;
		}
		isdir = 2;
		//イージング
		frame = 0;
		easingflag = true;
		startY = pos.y;
		endX = pos.y -= 60;
	}

	else if (keys[KEY_INPUT_DOWN] && !oldkey[KEY_INPUT_DOWN] && easingflag == false)
	{
		if (map->GetNextMap(static_cast<int>(playerArray.y) + 1, static_cast<int>(playerArray.x)) == 0)
		{
			speed.y = 60;
		}
		isdir = 3;
		//イージング
		frame = 0;
		easingflag = true;
		startY = pos.y;
		endX = pos.y += 60;
	}

	else
	{
		speed = { 0 ,0 }; //移動を止める
		startX = pos.x;
		startY = pos.y;
	}
	pos += speed; //現在の座標から移動する

	if (easingflag == 1)
	{
		frame++;
	}
	if (frame == endframe)
	{
		easingflag = 0;
	}

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
	if (keys[KEY_INPUT_SPACE] && !oldkey[KEY_INPUT_SPACE])
	{
		if (isdir == 0)//右
		{

		}
		else if (isdir == 1)//左
		{

		}
		else if (isdir == 2)//上
		{

		}
		else if (isdir == 3)//下
		{

		}
	}
	
}
