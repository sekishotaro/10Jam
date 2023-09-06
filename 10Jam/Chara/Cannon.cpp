#include "Cannon.h"
#include "Helper.h"
#include <DirectXMath.h>
#include <random>
Cannon::Cannon() {


}

Cannon::~Cannon() {
}

void Cannon::Initialize() {
	assert(player_);
}

void Cannon::Update() {
	Spawn();
	for (std::unique_ptr<Children>& children : Childrens) {
		children->Update();
	}

}

void Cannon::Draw() {
	for (std::unique_ptr<Children>& children : Childrens) {
		children->Draw();
	}
}

void Cannon::Spawn() {
	coolTimer_++;
	Clamp(coolTimer_,0.f, kCoolTimer);
	if (coolTimer_==kCoolTimer) {
		std::random_device seed_gen;
		std::default_random_engine engine(seed_gen());

		// -100以上100以下の値を等確率で発生させる
		std::uniform_int_distribution<> dist(-100,100);
		// 一様整数分布で乱数を生成する
		float positionX = dist(engine);
		float positionY = dist(engine);
		DirectX::XMFLOAT2 pos = { player_->GetPos().x + positionX ,player_->GetPos().y + positionY };
		std::unique_ptr<Children> children = std::make_unique<Children>(pos, player_);
		Childrens.push_back(std::move(children));
		coolTimer_ = 0;
	}
}
