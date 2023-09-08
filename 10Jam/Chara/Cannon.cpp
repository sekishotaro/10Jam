#include "Cannon.h"
#include "Helper.h"
#include <DirectXMath.h>
#include <random>
#include <ScoreManager.h>
Cannon::Cannon() {


}

Cannon::~Cannon() {
}

void Cannon::Initialize() {
	assert(player_);
	//�ŏ��̃X�|�[����
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
	
	//�폜���邩�m�F
	if (Children::DleteCheck() == false) return;
	//�폜����q���̔���
	for (std::unique_ptr<Children>& children : Childrens)
	{
		children->DleteChildrenCheck();
	}
	//�폜����q�����폜
	for (auto itr = Childrens.begin(); itr != Childrens.end();)
	{

		if (itr->get()->deleteFlag == true)
		{
			itr = Childrens.erase(itr);
		}
		else
		{
			++itr;
		}
	}
	//�c�����q���̏���
	for (std::unique_ptr<Children>& children : Childrens) {
		children->TrackChilOrganize();
	}
	constexpr int scoreUnit = 100;
	ScoreManager::GetInstance()->AddScore(Children::GetHitNum() * scoreUnit, 1u, player_->GetPos());
	Children::TrackChilHitNumReset();
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

		// -100�ȏ�100�ȉ��̒l�𓙊m���Ŕ���������
		std::uniform_int_distribution<> dist(-100,100);
		// ��l�������z�ŗ����𐶐�����
		float positionX = (float)dist(engine);
		float positionY = (float)dist(engine);
		DirectX::XMFLOAT2 pos = { player_->GetPos().x + positionX ,player_->GetPos().y + positionY };
		std::unique_ptr<Children> children = std::make_unique<Children>(pos, player_);
		Childrens.push_back(std::move(children));
		coolTimer_ = 0;
	}
}
