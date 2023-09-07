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
	//最初のスポーン数
	const int firstSpawnNum = 5;
	std::unique_ptr<Children> child[firstSpawnNum];
	child[0]= std::make_unique<Children>(DirectX:: XMFLOAT2{150.0f, 255.0f}, player_);
	child[1] = std::make_unique<Children>(DirectX::XMFLOAT2{300.0f, 255.0f}, player_);
	child[2] = std::make_unique<Children>(DirectX::XMFLOAT2{450.0f, 255.0f}, player_);
	child[3] = std::make_unique<Children>(DirectX::XMFLOAT2{600.0f, 255.0f}, player_);
	child[4] = std::make_unique<Children>(DirectX::XMFLOAT2{750.0f, 255.0f}, player_);
	for (int i = 0; i < firstSpawnNum;i++) {
		Childrens.push_back(std::move(child[i]));
	}
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
		float positionX = (float)dist(engine);
		float positionY = (float)dist(engine);
		DirectX::XMFLOAT2 pos = { player_->GetPos().x + positionX ,player_->GetPos().y + positionY };
		std::unique_ptr<Children> children = std::make_unique<Children>(pos, player_);
		Childrens.push_back(std::move(children));
		coolTimer_ = 0;
	}
}
