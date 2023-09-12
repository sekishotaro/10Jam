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
	//最初のスポーン数
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
	//全フレームで削除処理があった場合残った子供の移動処理
	if (deleteChilFlag == true) {
		//残った子供が0人の場合はスルー
		if (Children::GetTracChildrenNum() <= 0) {
			deleteChilFlag = false;
		} else {
			//子供を移動させる。
			for (std::unique_ptr<Children>& children : Childrens) {
				if (children->freeFlag == true) continue;
				children->ChilAlignment(time, alignmentMaxTime);
			}

			//時間がたったら終わり
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

	//削除するか確認
	if (Children::DleteCheck() == false) return;
	//連結子供削除フラグ(整列の為)
	deleteChilFlag = true;
	//整列で並び替える数
	int alignmentNum = Children::GetHitNum();
	int tracChilNum = Children::GetTracChildrenNum();
	int remainder = Children::GetTracChildrenNum() - Children::GetHitNum();
	//整列数が(整列全体数-当たった番号)より多い場合はあまりの数にする。
	if (alignmentNum > remainder) {
		alignmentNum = remainder;
	}

	//残りの連結子供の数分番号1から位置と移動量を保存
	DirectX::XMFLOAT2* a = new DirectX::XMFLOAT2[alignmentNum];
	std::vector<DirectX::XMFLOAT2>* moveChil = new std::vector<DirectX::XMFLOAT2>[alignmentNum];
	//削除する子供の判別
	for (std::unique_ptr<Children>& children : Childrens) {
		children->SetIsSlow(true);
		children->DleteChildrenCheck();
		//削除しない子供ならcontinue
		if (children->deleteFlag == false) continue;
		// 連結番号
		int RestraintTh = children->GetRestraintTh();	//連結番号
		if (alignmentNum < RestraintTh) continue;

		a[RestraintTh - 1] = children->GetPos();
		moveChil[RestraintTh - 1] = children->GetRestrainMoveVec();
	}
	//削除する子供を削除
	for (auto itr = Childrens.begin(); itr != Childrens.end();) {
		if (itr->get()->deleteFlag == true) {
			itr = Childrens.erase(itr);
			Children::trackChildrenNum--;
		} else {
			++itr;
		}
	}
	//残った子供の処理
	int count = 1;
	for (std::unique_ptr<Children>& children : Childrens) {
		if (children->freeFlag == true) continue;
		int numA = tracChilNum - (tracChilNum - remainder);
		int numB = children->GetRestraintTh();
		if (numB <= numA) continue;

		//カウントが保存個数を超えたらエラー
		if (count > alignmentNum) { assert(0); }

		//後ろから数えて消した子供の数分置き換える。
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
	//最初のスポーン数
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
	//全フレームで削除処理があった場合残った子供の移動処理
	if (deleteChilFlag == true) {
		//残った子供が0人の場合はスルー
		if (Children::GetTracChildrenNum() <= 0) {
			deleteChilFlag = false;
		} else {
			//子供を移動させる。
			for (std::unique_ptr<Children>& children : Childrens) {
				if (children->freeFlag == true) continue;
				children->ChilAlignment(time, alignmentMaxTime);
			}

			//時間がたったら終わり
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
	//削除するか確認
	if (Children::DleteCheck() == false) return;
	//連結子供削除フラグ(整列の為)
	deleteChilFlag = true;
	//整列で並び替える数
	int alignmentNum = Children::GetHitNum();
	int tracChilNum = Children::GetTracChildrenNum();
	int remainder = Children::GetTracChildrenNum() - Children::GetHitNum();
	//整列数が(整列全体数-当たった番号)より多い場合はあまりの数にする。
	if (alignmentNum > remainder) {
		alignmentNum = remainder;
	}

	//残りの連結子供の数分番号1から位置と移動量を保存
	DirectX::XMFLOAT2* a = new DirectX::XMFLOAT2[alignmentNum];
	std::vector<DirectX::XMFLOAT2>* moveChil = new std::vector<DirectX::XMFLOAT2>[alignmentNum];
	//削除する子供の判別
	for (std::unique_ptr<Children>& children : Childrens) {
		children->SetIsSlow(true);
		children->DleteChildrenCheck();
		//削除しない子供ならcontinue
		if (children->deleteFlag == false) continue;
		// 連結番号
		int RestraintTh = children->GetRestraintTh();	//連結番号
		if (alignmentNum < RestraintTh) continue;

		a[RestraintTh - 1] = children->GetPos();
		moveChil[RestraintTh - 1] = children->GetRestrainMoveVec();
	}
	//削除する子供を削除
	for (auto itr = Childrens.begin(); itr != Childrens.end();) {
		if (itr->get()->deleteFlag == true) {
			itr = Childrens.erase(itr);
			Children::trackChildrenNum--;
		}
		else {
			++itr;
		}
	}
	//残った子供の処理
	int count = 1;
	for (std::unique_ptr<Children>& children : Childrens) {
		if (children->freeFlag == true) continue;
		int numA = tracChilNum - (tracChilNum - remainder);
		int numB = children->GetRestraintTh();
		if (numB <= numA) continue;

		//カウントが保存個数を超えたらエラー
		if (count > alignmentNum) { assert(0); }

		//後ろから数えて消した子供の数分置き換える。
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

		// -100以上100以下の値を等確率で発生させる
		std::uniform_int_distribution<> dist(-100, 100);
		// 一様整数分布で乱数を生成する
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
		// -100以上100以下の値を等確率で発生させる
		std::uniform_int_distribution<> dist(140, 1140);
		std::uniform_int_distribution<> distY(80, 640);

		// 一様整数分布で乱数を生成する
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
