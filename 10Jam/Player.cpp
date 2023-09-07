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

	Move();

	pos.x += moveVec.x;
	pos.y += moveVec.y;
	Clamp(pos.x, 140.f, 1140.f);
	Clamp(pos.y, 80.f, 640.f);

	if ((pos.x > 140.0f && pos.x < 1140.0f) && (pos.y > 80.0f && pos.y < 640.0f)) {
		ScrollManager::GetInstance()->SetMove({ 0 ,0 });

	} else {
		ScrollManager::GetInstance()->SetMove({ moveVec.x ,moveVec.y });

	}
}

void Player::Draw() {
	DrawCircleAA(pos.x, pos.y, radius, 64, GetColor(110, 239, 255), true);
}

void Player::HitChildren() {
	childrenNum++;
	Particle::Ins()->Fireworks(pos, 60u, radius * 3.f, 8ui8, Particle::ColorRGB{255, 255, 34});
}

void Player::Move() {
	if (keys[KEY_INPUT_D] == true) {
		rota -= 2.0f;
	} else if (keys[KEY_INPUT_A] == true) {
		rota += 2.0f;
	}

	static XMFLOAT2 vec = { 0.0f, 2.0f };

	if (keys[KEY_INPUT_W] == true) {
		vec = { 0.0f, 2.0f };
	} else if (keys[KEY_INPUT_S] == true) {
		vec = { 0.0f, 0.0f };
	}

	float sita = rota * 3.1415f / 108.0f;

	moveVec.x = vec.x * cos(sita) - vec.y * sin(sita);
	moveVec.y = vec.x * sin(sita) - vec.y * cos(sita);

}

