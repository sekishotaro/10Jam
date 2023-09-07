#include "Player.h"
#include "DxLib.h"
#include <Helper.h>
#include <ScrollManager.h>
#include "Particle.h"

Player::Player() {
}

Player::~Player() {
}

void Player::initialize() {
	pos = {};
	moveVec = {};
	childrenNum = 0;
}

void Player::Update() {
	moveVec = {};

	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	Dash();
	Move();
	pos.x += moveVec.x;
	pos.y += moveVec.y;
	Clamp(pos.x, 140.f, 1140.f);
	Clamp(pos.y, 80.f, 640.f);

	XMFLOAT2 a = {};

	if ((pos.x > 140.0f && pos.x < 1140.0f)) {
		a.x = 0;

	} else {
		a.x = moveVec.x;

	}

	if ((pos.y > 80.0f && pos.y < 640.0f)) {
		a.y = 0;

	}
	else {
		a.y = moveVec.y;

	}

	ScrollManager::GetInstance()->SetMove(a);
}

void Player::Draw() {
	DrawCircleAA(pos.x,pos.y, radius,64, GetColor(110, 239, 255), true);
}

void Player::HitChildren() {
	childrenNum++;
	Particle::Ins()->Fireworks(pos, 60u, radius * 3.f, 8ui8, Particle::ColorRGB{255, 255, 34});
}

void Player::Childrendelete()
{
	childrenNum--;
}

void Player::Move()
{
	if (keys[KEY_INPUT_D] == 1)
	{
		rota -= 2.0f;
	} else if (keys[KEY_INPUT_A] == 1) {
		rota += 2.0f;
	}

	static XMFLOAT2 vec = { 0.0f, 3.0f };

	if (keys[KEY_INPUT_W] == 1) {
		vec = { 0.0f, 3.0f };
	} else if (keys[KEY_INPUT_S] == 1) {
		vec = { 0.0f, 0.0f };
	}

	float sita = rota * 3.1415f / 108.0f;

	moveVec.x = vec.x * cosf(sita) - vec.y * sinf(sita);
	moveVec.y = vec.x * sinf(sita) - vec.y * cosf(sita);
	moveVec.x *=accel;
	moveVec.y *=accel;

}

void Player::Dash() {
	if(!isBoost){
		accel = 1.0f;
		return;
	}
	boostFrame++;
	Clamp(boostFrame,0.0f, kBoostFrameMax);
	accel = 1.5f;
	if (boostFrame== kBoostFrameMax) {
		boostFrame = 0.0f;
		isBoost = false;
	}
}

