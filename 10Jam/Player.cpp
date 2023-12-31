#include "Player.h"
#include "DxLib.h"
#include <Helper.h>
#include <ScrollManager.h>
#include "Particle.h"
#include "Sound.h"

Player::Player() :
	hitChildrenSe(Sound::Ins()->LoadFile("Resources/Sound/Sys_Set03-click.ogg")) {
}

Player::~Player() {
}

void Player::initialize() {
	pos = {};
	moveVec = {};
	childrenNum = 0;
}

void Player::TitleInitialize()
{
	pos = { 600.0f, 410.0f };
	pos.x -= 50.0f;
	pos.y += 150.0f;
	titeleRota = 145.0f;
	moveVec = {};
	childrenNum = 0;
}

void Player::Update() {
	if (playerStop == true) return;

	moveVec = {};
	// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
	for (int i = 0; i < 256; i++) {
		oldkeys[i] = keys[i];
	}
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	CoinDash();
	GearDash();
	Dash();
	Move();
	pos.x += moveVec.x;
	pos.y += moveVec.y;
	Clamp(pos.x, 140.f, 1140.f);
	Clamp(pos.y, 80.f, 640.f);

	XMFLOAT2 overMove = {};
	const float kScrollMin = -500.0f;
	const float kScrollMax = 500.0f;

	if ((pos.x > 140.0f && pos.x < 1140.0f)) {
		overMove.x = 0;
	} else {
		overMove.x = moveVec.x;
	}

	if ((pos.y > 80.0f && pos.y < 640.0f)) {
		overMove.y = 0;
	} else {
		overMove.y = moveVec.y;
	}
	moveAdd.x += overMove.x;
	moveAdd.y += overMove.y;

	ScrollManager::GetInstance()->SetMove(overMove);
}

void Player::TitleUpdate()
{
	if (playerStop == true) return;
	moveVec = {};
	static XMFLOAT2 vec = { 0.0f, 3.0f };
	titeleRota += 0.5f;
	float sita = titeleRota * 3.1415f / 108.0f;
	moveVec.x = vec.x * cosf(sita) - vec.y * sinf(sita);
	moveVec.y = vec.x * sinf(sita) - vec.y * cosf(sita);
	pos.x += moveVec.x;
	pos.y += moveVec.y;
}

void Player::Draw() {
	// 本体
	DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(110, 239, 255), true);

	if (isBoost) {
		DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(16, 16, 255), false, 5.0f);
	}
	if (isGear) {
		DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(255, 16, 255), false, 5.0f);
	}
	if (getCoin) {
		DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(255, 255, 0), true);
	}
}

void Player::HitChildren() {
	AddCoin();
	childrenNum++;
	Particle::Ins()->Fireworks(pos, 60u, radius * 3.f, 8ui8, Particle::ColorRGB{ 255, 255, 34 }, true, 8ui8);
	bool ret = Sound::Ins()->Play(hitChildrenSe, true, DX_PLAYTYPE_BACK);
	assert(!ret);
}

void Player::Childrendelete() {
	childrenNum--;
}

void Player::Move() {
	RotaUpdate();

	if (keys[KEY_INPUT_D] == 1) {
		rota -= rotaVal * accel * gear;
	} else if (keys[KEY_INPUT_A] == 1) {
		rota += rotaVal * accel * gear;
	}

	static XMFLOAT2 vec = { 0.0f, 3.0f };

	float sita = rota * 3.1415f / 108.0f;

	moveVec.x = vec.x * cosf(sita) - vec.y * sinf(sita);
	moveVec.y = vec.x * sinf(sita) - vec.y * cosf(sita);
	moveVec.x *= accel;
	moveVec.y *= accel;
	moveVec.x *= coinBoost;
	moveVec.y *= coinBoost;
}

void Player::CoinDash() {
	if (!getCoin) { return; }
	coinFrame += 1.0f;
	coinBoost = 1.1f;
	Clamp(coinFrame, 0.0f, kCoinFrameMax);
	if (coinFrame == kCoinFrameMax) {
		coinBoost = 1.0f;
		coinFrame = 0.0f;
		getCoin = false;
	}
}

void Player::GearDash() {
	if (!isGear) {
		gear = 1.0f;
		return;
	}
	gearFrame++;
	Clamp(gearFrame, 0.0f, kGearFrameMax);
	gear = 2.0f;
	if (gearFrame == kGearFrameMax) {
		gearFrame = 0.0f;
		isGear = false;
	}
}

void Player::Dash() {
	if (!isBoost) {
		accel = 1.0f;
		return;
	}
	accel = 1.5f;
	boostFrame = ++boostFrame % kBoostFrameMax;
	if (boostFrame == 0) {
		isBoost = false;
	}
}

void Player::RotaUpdate() {
	if (ScoreManager::GetScore() >= 4000) {
		rotaVal = 0.5f;
		radius = 28.f;
	} else if (ScoreManager::GetScore() >= 2500) {
		rotaVal = 1.0f;
		radius = 26.f;
	} else if (ScoreManager::GetScore() >= 1750) {
		rotaVal = 1.5f;
		radius = 24.0f;
	} else if (ScoreManager::GetScore() >= 1000) {
		rotaVal = 2.0f;
		radius = 22.0f;
	} else if (ScoreManager::GetScore() >= 500) {
		rotaVal = 2.5f;
		radius = 20.0f;
	}
}
