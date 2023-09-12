#include "Cannon.h"
#include "Helper.h"
#include <DirectXMath.h>
#include <random>
#include <ScoreManager.h>
#include <vector>
#include "../Particle.h"

#define DEG_TO_RAD(deg)  ((deg) / 180.0 * 3.14159265358979323846)

using namespace DirectX;
Cannon::Cannon() {


}

Cannon::~Cannon() {
}

void Cannon::Initialize() {
	assert(player_);
	//�ŏ��̃X�|�[����
	const int firstSpawnNum = 5;
	std::unique_ptr<Children> child[firstSpawnNum];
	child[0] = std::make_unique<Children>(DirectX::XMFLOAT2{ 150.0f, 255.0f }, player_);
	child[1] = std::make_unique<Children>(DirectX::XMFLOAT2{ 300.0f, 255.0f }, player_);
	child[2] = std::make_unique<Children>(DirectX::XMFLOAT2{ 450.0f, 255.0f }, player_);
	child[3] = std::make_unique<Children>(DirectX::XMFLOAT2{ 600.0f, 255.0f }, player_);
	child[4] = std::make_unique<Children>(DirectX::XMFLOAT2{ 750.0f, 255.0f }, player_);
	for (int i = 0; i < firstSpawnNum; i++) {
		Childrens.push_back(std::move(child[i]));
	}
	std::unique_ptr<AccelSpot> accel = std::make_unique<AccelSpot>(DirectX::XMFLOAT2{ 600,200 }, player_);
	accel->Initialize();
	std::unique_ptr<GearSpot> gear = std::make_unique<GearSpot>(DirectX::XMFLOAT2{ 1000,500 }, player_);
	gear->Initialize();

	accels.push_back(std::move(accel));
	gears.push_back(std::move(gear));
}

void Cannon::Update() {
	//�S�t���[���ō폜�������������ꍇ�c�����q���̈ړ�����
	if (deleteChilFlag == true) {
		//�c�����q����0�l�̏ꍇ�̓X���[
		if (Children::GetTracChildrenNum() <= 0) {
			deleteChilFlag = false;
		} else {
			//�q�����ړ�������B
			for (std::unique_ptr<Children>& children : Childrens) {
				if (children->freeFlag == true) continue;
				children->ChilAlignment(time, alignmentMaxTime);
			}

			//���Ԃ���������I���
			if (TimeProgress() == true) {
				deleteChilFlag = false;
				time = 0.0f;
			} else {
				return;
			}
		}
	}
	Spawn();
	SpotSpawn();
	for (std::unique_ptr<Children>& children : Childrens) {
		children->Update();
	}
	for (std::unique_ptr<AccelSpot>& accel : accels) {
		accel->Update();
	}	for (std::unique_ptr<GearSpot>& gear : gears) {
		gear->Update();
	}

	//�폜���邩�m�F
	if (Children::DleteCheck() == false) return;
	//�A���q���폜�t���O(����̈�)
	deleteChilFlag = true;
	//����ŕ��ёւ��鐔
	int alignmentNum = Children::GetHitNum();
	int tracChilNum = Children::GetTracChildrenNum();
	int remainder = Children::GetTracChildrenNum() - Children::GetHitNum();
	//���񐔂�(����S�̐�-���������ԍ�)��葽���ꍇ�͂��܂�̐��ɂ���B
	if (alignmentNum > remainder) {
		alignmentNum = remainder;
	}

	//�c��̘A���q���̐����ԍ�1����ʒu�ƈړ��ʂ�ۑ�
	DirectX::XMFLOAT2* a = new DirectX::XMFLOAT2[alignmentNum];
	std::vector<DirectX::XMFLOAT2>* moveChil = new std::vector<DirectX::XMFLOAT2>[alignmentNum];
	//�폜����q���̔���
	for (std::unique_ptr<Children>& children : Childrens) {
		children->SetIsSlow(true);
		children->DleteChildrenCheck();
		//�폜���Ȃ��q���Ȃ�continue
		if (children->deleteFlag == false) continue;
		// �A���ԍ�
		int RestraintTh = children->GetRestraintTh();	//�A���ԍ�
		if (alignmentNum < RestraintTh) continue;

		a[RestraintTh - 1] = children->GetPos();
		moveChil[RestraintTh - 1] = children->GetRestrainMoveVec();
	}
	//�폜����q�����폜
	for (auto itr = Childrens.begin(); itr != Childrens.end();) {
		if (itr->get()->deleteFlag == true) {
			itr = Childrens.erase(itr);
			Children::trackChildrenNum--;
		} else {
			++itr;
		}
	}
	//�c�����q���̏���
	int count = 1;
	for (std::unique_ptr<Children>& children : Childrens) {
		if (children->freeFlag == true) continue;
		int numA = tracChilNum - (tracChilNum - remainder);
		int numB = children->GetRestraintTh();
		if (numB <= numA) continue;

		//�J�E���g���ۑ����𒴂�����G���[
		if (count > alignmentNum) { assert(0); }

		//��납�琔���ď������q���̐����u��������B
		children->TrackChilOrganize(a[count - 1], moveChil[count - 1], count - 1);
		count++;
	}

	Particle::Ins()->Fireworks(player_->GetPos(),
		120u,
		128.f,
		64ui8,
		Particle::ColorRGB{ 0xff,0x22,0x22 },
		true, 3ui8);

	constexpr int scoreUnit = 100;
	ScoreManager::GetInstance()->AddScore(Children::GetHitNum() * scoreUnit, 1u, player_->GetPos());
	aditionaltime += 3;
	delete[] a;
	delete[] moveChil;
	Children::TrackChilHitNumReset();
}

void Cannon::TitleInitialize() {
	//�ŏ��̃X�|�[����
	const int firstSpawnNum = 12;
	std::unique_ptr<Children> child[firstSpawnNum];

	child[0] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(0.f)) * 200.0f, 360 + (cosf((float)DEG_TO_RAD(0.f)) * 200.0f) }, player_,true);
	child[1] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(30.f)) * 200.0f, 360 + (cosf((float)DEG_TO_RAD(30.f)) * 200.0f) }, player_,true);
	child[2] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(60.f)) * 200.0f, 360 + (cosf((float)DEG_TO_RAD(60.f)) * 200.0f) }, player_,true);
	child[3] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(90.f)) * 200.0f, 360 + (cosf((float)DEG_TO_RAD(90.f)) * 200.0f) }, player_,true);
	child[4] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(120.f)) * 200.0f,360 + (cosf((float)DEG_TO_RAD(120.f)) * 200.0f) }, player_,true);
	child[5] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(150.f)) * 200.0f,360 + (cosf((float)DEG_TO_RAD(150.f)) * 200.0f) }, player_,true);
	child[6] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(180.f)) * 200.0f,360 + (cosf((float)DEG_TO_RAD(180.f)) * 200.0f) }, player_,true);
	child[7] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(210.f)) * 200.0f,360 + (cosf((float)DEG_TO_RAD(210.f)) * 200.0f) }, player_,true);
	child[8] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(240.f)) * 200.0f,360 + (cosf((float)DEG_TO_RAD(240.f)) * 200.0f) }, player_, true);
	child[9] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(270.f)) * 200.0f,360 + (cosf((float)DEG_TO_RAD(270.f)) * 200.0f) }, player_, true);
	child[10] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(300.f)) * 200.0f,360 + (cosf((float)DEG_TO_RAD(300.f)) * 200.0f) }, player_, true);
	child[11] = std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(330.f)) * 200.0f,360 + (cosf((float)DEG_TO_RAD(330.f)) * 200.0f) }, player_, true);

	for (int i = 0; i < firstSpawnNum; i++) {
		Childrens.push_back(std::move(child[i]));
	}

}

void Cannon::TitleUpdate() {
	//�S�t���[���ō폜�������������ꍇ�c�����q���̈ړ�����
	if (deleteChilFlag == true) {
		//�c�����q����0�l�̏ꍇ�̓X���[
		if (Children::GetTracChildrenNum() <= 0) {
			deleteChilFlag = false;
		} else {
			//�q�����ړ�������B
			for (std::unique_ptr<Children>& children : Childrens) {
				if (children->freeFlag == true) continue;
				children->ChilAlignment(time, alignmentMaxTime);
			}

			//���Ԃ���������I���
			if (TimeProgress() == true) {
				deleteChilFlag = false;
				time = 0.0f;
			} else {
				return;
			}
		}
	}
	TitleSpawn();
	for (std::unique_ptr<Children>& children : Childrens) {
		children->Update();
	}
	//�폜���邩�m�F
	if (Children::DleteCheck() == false) return;
	//�A���q���폜�t���O(����̈�)
	deleteChilFlag = true;
	//����ŕ��ёւ��鐔
	int alignmentNum = Children::GetHitNum();
	int tracChilNum = Children::GetTracChildrenNum();
	int remainder = Children::GetTracChildrenNum() - Children::GetHitNum();
	//���񐔂�(����S�̐�-���������ԍ�)��葽���ꍇ�͂��܂�̐��ɂ���B
	if (alignmentNum > remainder) {
		alignmentNum = remainder;
	}

	//�c��̘A���q���̐����ԍ�1����ʒu�ƈړ��ʂ�ۑ�
	DirectX::XMFLOAT2* a = new DirectX::XMFLOAT2[alignmentNum];
	std::vector<DirectX::XMFLOAT2>* moveChil = new std::vector<DirectX::XMFLOAT2>[alignmentNum];
	//�폜����q���̔���
	for (std::unique_ptr<Children>& children : Childrens) {
		children->SetIsSlow(true);
		children->DleteChildrenCheck();
		//�폜���Ȃ��q���Ȃ�continue
		if (children->deleteFlag == false) continue;
		// �A���ԍ�
		int RestraintTh = children->GetRestraintTh();	//�A���ԍ�
		if (alignmentNum < RestraintTh) continue;

		a[RestraintTh - 1] = children->GetPos();
		moveChil[RestraintTh - 1] = children->GetRestrainMoveVec();
	}
	//�폜����q�����폜
	for (auto itr = Childrens.begin(); itr != Childrens.end();) {
		if (itr->get()->deleteFlag == true) {
			itr = Childrens.erase(itr);
			Children::trackChildrenNum--;
		}
		else {
			++itr;
		}
	}
	//�c�����q���̏���
	int count = 1;
	for (std::unique_ptr<Children>& children : Childrens) {
		if (children->freeFlag == true) continue;
		int numA = tracChilNum - (tracChilNum - remainder);
		int numB = children->GetRestraintTh();
		if (numB <= numA) continue;

		//�J�E���g���ۑ����𒴂�����G���[
		if (count > alignmentNum) { assert(0); }

		//��납�琔���ď������q���̐����u��������B
		children->TrackChilOrganize(a[count - 1], moveChil[count - 1], count - 1);
		count++;
	}

	delete[] a;
	delete[] moveChil;
	Children::TrackChilHitNumReset();
}

void Cannon::TitleDraw() {
	for (std::unique_ptr<Children>& children : Childrens) {
		children->Draw();
	}
}

void Cannon::TitleSpawn() {
	tFrame++;
	Clamp(tFrame, 0.f, kFrameMax);
	if (tFrame == kFrameMax) {
		for (std::unique_ptr<Children>& children : Childrens) {
			if (!children->freeFlag) {
				float rad =  (i * 30.f);
				std::unique_ptr<Children> child;
				child= std::make_unique<Children>(DirectX::XMFLOAT2{ 640 + sinf((float)DEG_TO_RAD(rad)) * 200.0f, 360 + (cosf((float)DEG_TO_RAD(rad)) * 200.0f) }, player_, true);
				Childrens.push_back(std::move(child));
				i++;
				break;
			}
		}
		tFrame = 0;
	}





}

void Cannon::Draw() {
	for (std::unique_ptr<AccelSpot>& accel : accels) {
		accel->Draw();
	}	for (std::unique_ptr<GearSpot>& gear : gears) {
		gear->Draw();
	}
	for (std::unique_ptr<Children>& children : Childrens) {
		children->Draw();
	}
}

void Cannon::Spawn() {
	coolTimer_++;
	Clamp(coolTimer_, 0.f, kCoolTimer);
	if (coolTimer_ == kCoolTimer) {
		std::random_device seed_gen;
		std::default_random_engine engine(seed_gen());

		// -100�ȏ�100�ȉ��̒l�𓙊m���Ŕ���������
		std::uniform_int_distribution<> dist(-100, 100);
		// ��l�������z�ŗ����𐶐�����
		float positionX = (float)dist(engine);
		float positionY = (float)dist(engine);
		DirectX::XMFLOAT2 pos = { player_->GetPos().x + positionX ,player_->GetPos().y + positionY };
		std::unique_ptr<Children> children = std::make_unique<Children>(pos, player_);
		Childrens.push_back(std::move(children));
		coolTimer_ = 0;
	}
}

void Cannon::SpotSpawn() {
	int nowscore = ScoreManager::GetInstance()->GetScore();
	if (nowscore > mScore + 500) {
		mScore = nowscore;
		isSpawn = true;
	}
	if (nowscore > mGscore + 1000) {
		mGscore = nowscore;
		isSpawnGear = true;
	}
	if (isSpawn || isSpawnGear) {
		std::random_device seed_gen;
		std::default_random_engine engine(seed_gen());
		// -100�ȏ�100�ȉ��̒l�𓙊m���Ŕ���������
		std::uniform_int_distribution<> dist(140, 1140);
		std::uniform_int_distribution<> distY(80, 640);

		// ��l�������z�ŗ����𐶐�����
		float positionX = (float)dist(engine);
		float positionY = (float)distY(engine);

		if (isSpawn) {
			if (accels.size() > 2) {
				accels.pop_front();
			}
			std::unique_ptr<AccelSpot> accel = std::make_unique<AccelSpot>(DirectX::XMFLOAT2{ positionX,positionY }, player_);
			accel->Initialize();
			accels.push_back(std::move(accel));
			isSpawn = false;
		} else {
			if (gears.size() > 1) {
				gears.pop_front();
			}
			std::unique_ptr<GearSpot> gear = std::make_unique<GearSpot>(DirectX::XMFLOAT2{ positionX,positionY }, player_);
			gear->Initialize();
			gears.push_back(std::move(gear));
			isSpawnGear = false;
		}
	}

}

bool Cannon::TimeProgress() {
	if (time >= alignmentMaxTime) return true;
	float flame = 60.0f;
	time += 1.0f / flame;
	return false;
}
