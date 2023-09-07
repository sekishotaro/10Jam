#include "Player.h"
#include "DxLib.h"
#include <Helper.h>
#include <ScrollManager.h>

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

	//if (keys[KEY_INPUT_S] == true)
	//{
	//	moveVec.y += 2.0f;
	//}
	//else if (keys[KEY_INPUT_W] == true)
	//{
	//	moveVec.y -= 2.0f;
	//}

	//if (keys[KEY_INPUT_D] == true)
	//{
	//	moveVec.x += 2.0f;
	//}
	//else if (keys[KEY_INPUT_A] == true)
	//{
	//	moveVec.x -= 2.0f;
	//}

	Move();

	pos.x += moveVec.x;
	pos.y += moveVec.y;
	Clamp(pos.x, 140.f, 1140.f);
	Clamp(pos.y, 80.f, 640.f);
	if (pos.x >= 1140.0f) {
		ScrollManager::GetInstance()->SetMove({ moveVec.x ,moveVec.y });
	} else if (pos.x <= 140.0f) {
		ScrollManager::GetInstance()->SetMove({ moveVec.x ,moveVec.y });
	} else {
		ScrollManager::GetInstance()->SetMove({ 0 ,0 });
	}
	if (pos.y >= 640.0f) {
		ScrollManager::GetInstance()->SetMove({ moveVec.x ,moveVec.y });

	} else if (pos.y <= 80.0f) {
		ScrollManager::GetInstance()->SetMove({ moveVec.x ,moveVec.y });
	} else {
		ScrollManager::GetInstance()->SetMove({ 0 ,0 });
	}

}

void Player::Draw() {
	DrawCircle((int)pos.x, (int)pos.y, radius, GetColor(110.0f, 239.0f, 255.0f), true);
}

void Player::HitChildren() {
	childrenNum++;
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

