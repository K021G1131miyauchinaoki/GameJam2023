#include "block.h"


void Block::Initialize()
{
    pos = { 280, 300 };    // 中心座標
    radius = 20;        // 半径
    speed = 5;            // 速度
    gravity = 0.1f;        // 重力
	isDamage = false;
	//パーティクル
	for (int i = 0; i < MAX_PARTICLE; i++) {
		particle[i].transform.x = 450 / 2;
		particle[i].transform.y = 600 / 2;
		particle[i].transform.radius = 8;
		particle[i].alpha = 255;
		particle[i].color = GetColor(255, 255, 255);
	}
}

void Block::Update(char* keys, char* oldkey)
{
	if (keys[KEY_INPUT_1] && !oldkey[KEY_INPUT_1])
	{
		isDamage = true;
		for (int i = 0; i < MAX_PARTICLE; i++) {
			
		}
	}
	if (keys[KEY_INPUT_0] && !oldkey[KEY_INPUT_0])
	{
		isDamage = false;
		for (int i = 0; i < MAX_PARTICLE; i++) {
			particle[i].isAlive = 0;
		}
	}
	//重力加速
	pos.y += gravity;
	if (pos.y <= 400)	//底についていなければ
	{
		gravity += 0.2f;//加速する
	}
	else				//そこについているならば
	{
		gravity = 0.0f; //加速しない(止める)
	}
	//particle[MAX_PARTICLE].angle += 1;

	//画面の中心からParticleを発生させる、処理としては複数弾の処理と似ている
	if(isDamage == true){
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (particle[i].isAlive == 0) {
			particle[i].isAlive = 1;
			particle[i].transform.x = pos.x;
			particle[i].transform.y = pos.y;
			particle[i].transform.radius = 1;
			particle[i].angle = rand() % 100;	// 角度をランダムで決める
			particle[i].speed = 5.0f;
			particle[i].alpha = 250;			// 透明度をリセット
			particle[i].color = GetColor(255, 255, 255);
			break;
		}
	}

	//生存フラグがオンなら
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (particle[i].isAlive == 1) {
			//角度(angle)によって移動
			particle[i].transform.x += cos(particle[i].angle) * particle[i].speed;
			particle[i].transform.y += sin(particle[i].angle) * particle[i].speed;
			particle[i].transform.y += 5;
			particle[i].alpha -= 5;
			particle[i].speed -= 0.08f;
		}
	}
	}
}

void Block::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (isDamage == false) {
		DrawGraph(pos.x, pos.y, nodamage, true);
	}
	else {
		DrawGraph(pos.x, pos.y, damage, true);
	}
    //DrawBox(pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius, GetColor(0, 255, 0), true);
    DrawFormatString(0, 15, GetColor(0, 255, 255), "player : %f/%f\n", pos.x, pos.y);
	
	for (int i = 0; i < MAX_PARTICLE; i++) {
		if (particle[i].isAlive == 1) {
			//各個体のアルファ値によってブレンドモードの値を変えている
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, particle[i].alpha);
			DrawGraph(
				particle[i].transform.x,
				particle[i].transform.y,
				g1,
				TRUE
			);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
}