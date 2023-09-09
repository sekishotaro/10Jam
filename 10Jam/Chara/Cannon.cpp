#include "Cannon.h"
#include "Helper.h"
#include <DirectXMath.h>
#include <random>
#include <ScoreManager.h>
#include <vector>
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
	//全フレームで削除処理があった場合残った子供の移動処理
	if (deleteChilFlag == true)
	{
		//残った子供が0人の場合はスルー
		if (Children::GetTracChildrenNum() <= 0)
		{
			deleteChilFlag = false;
		}
		else
		{
			//子供を移動させる。
			for (std::unique_ptr<Children>& children : Childrens) {
				if (children->freeFlag == true) continue;
				children->ChilAlignment(time, alignmentMaxTime);
			}

			//時間がたったら終わり
			if (TimeProgress() == true)
			{
				deleteChilFlag = false;
				time = 0.0f;
			}
			else
			{
				return;
			}
		}
	}
	
	Spawn();
	for (std::unique_ptr<Children>& children : Childrens) {
		children->Update();
	}
	

	//削除するか確認
	if (Children::DleteCheck() == false) return;
	//連結子供削除フラグ
	deleteChilFlag = true;
	//残りの連結子供の数
	int TracChildrenNum = Children::GetTracChildrenNum();
	int HitNum = Children::GetHitNum();
	int num = TracChildrenNum - HitNum;
	//残りの連結子供の数分番号1から位置と移動量を保存
	DirectX::XMFLOAT2* a = new DirectX::XMFLOAT2[num];
	std::vector<DirectX::XMFLOAT2>* moveChil = new std::vector<DirectX::XMFLOAT2>[num];
	
	//削除する子供の判別
	for (std::unique_ptr<Children>& children : Childrens)
	{
		children->DleteChildrenCheck();
		//削除しない子供ならcontinue
		if (children->deleteFlag == false) continue;
		// 連結番号
		int Anum = children->GetRestraintTh();
		if (num == 0) continue;
		if (Anum > num) continue;
		

		a[Anum -1] = children->GetPos();
		moveChil[Anum - 1] = children->GetRestrainMoveVec();
	}
	//削除する子供を削除
	for (auto itr = Childrens.begin(); itr != Childrens.end();)
	{
		if (itr->get()->deleteFlag == true)
		{
			itr = Childrens.erase(itr);
			Children::trackChildrenNum--;
		}
		else
		{
			++itr;
		}
	}
	//残った子供の処理
	int count = 0;
	for (std::unique_ptr<Children>& children : Childrens) {
		if (children->freeFlag == true) continue;
		children->TrackChilOrganize(a[count], moveChil[count], count);
		count++;
	}
	const int score = 100;
	ScoreManager::GetInstance()->AddScore(Children::GetHitNum()* score);
	delete[] a;
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

bool Cannon::TimeProgress()
{
	float flame = 60.0f;
	time += 1.0f / flame;

	if (time >= alignmentMaxTime) return true;
	return false;
}
