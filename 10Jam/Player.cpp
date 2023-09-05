#include "Player.h"
#include "DxLib.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::initialize()
{
	pos = {};
	moveVec = {};
}

void Player::Update()
{
	moveVec = {};

	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; i++)
	{
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);

	if (keys[KEY_INPUT_S] == true)
	{
		moveVec.y += 2.0f;
	}
	else if (keys[KEY_INPUT_W] == true)
	{
		moveVec.y -= 2.0f;
	}

	if (keys[KEY_INPUT_D] == true)
	{
		moveVec.x += 2.0f;
	}
	else if (keys[KEY_INPUT_A] == true)
	{
		moveVec.x -= 2.0f;
	}

	pos.x += moveVec.x;
	pos.y += moveVec.y;
}

void Player::Draw()
{
	DrawCircle((int)pos.x, (int)pos.y, (int)10.0f, GetColor(0, 0, 255), true);
}
