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
	CoinDash();
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
		isStop = false;
	} else {
		overMove.x = moveVec.x;
		Clamp(moveAdd.x, kScrollMin, kScrollMax);
		if (pos.x == 140.0f) {
			if (moveAdd.x == kScrollMin) {
				overMove.x = 0;
				moveVec.x = 0.0f;
				isStop = true;
			}
		} else {
			if (moveAdd.x == kScrollMax) {
				overMove.x = 0;
				moveVec.x = 0.0f;
				isStop = true;
			}
		}
	}

	if ((pos.y > 80.0f && pos.y < 640.0f)) {
		overMove.y = 0;
		isStop = false;
	} else {
		overMove.y = moveVec.y;
		Clamp(moveAdd.y, kScrollMin, kScrollMax);
		if (pos.y == 80.0f) {
			if (moveAdd.y == kScrollMin) {
				overMove.y = 0;
				moveVec.y = 0.0f;
				isStop = true;
			}
		} else {
			if (moveAdd.y == kScrollMax) {
				overMove.y = 0;
				moveVec.y = 0.0f;
				isStop = true;
			}
		}
	}
	moveAdd.x += overMove.x;
	moveAdd.y += overMove.y;

	ScrollManager::GetInstance()->SetMove(overMove);
}

void Player::Draw() {
	DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(110, 239, 255), true);
	if (isBoost) {
		DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(110, 110, 255), true);
		DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(10, 125, 10), false, 5.0f);
	}
	if (getCoin) {
		DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(255, 255, 0), true);
	}
}

void Player::HitChildren() {
	AddCoin();
	childrenNum++;
	Particle::Ins()->Fireworks(pos, 60u, radius * 3.f, 8ui8, Particle::ColorRGB{ 255, 255, 34 }, true, 8ui8);
}

void Player::Childrendelete() {
	childrenNum--;
}

void Player::Move() {

	RotaUpdate();

	if (keys[KEY_INPUT_D] == 1) {
		rota -= rotaVal * accel;
	} else if (keys[KEY_INPUT_A] == 1) {
		rota += rotaVal * accel;
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

void Player::Dash() {
	if (!isBoost) {
		accel = 1.0f;
		return;
	}
	boostFrame++;
	Clamp(boostFrame, 0.0f, kBoostFrameMax);
	accel = 1.5f;
	if (boostFrame == kBoostFrameMax) {
		boostFrame = 0.0f;
		isBoost = false;
	}
}

void Player::RotaUpdate() {

	if (ScoreManager::GetScore() >= 2000) {
		rotaVal = 0.5f;
	} else if (ScoreManager::GetScore() >= 2000) {
		rotaVal = 1.0f;
	} else if (ScoreManager::GetScore() >= 1500) {
		rotaVal = 1.5f;
	} else if (ScoreManager::GetScore() >= 1000) {
		rotaVal = 2.0f;
	} else if (ScoreManager::GetScore() >= 500) {
		rotaVal = 2.5f;
	}
}

