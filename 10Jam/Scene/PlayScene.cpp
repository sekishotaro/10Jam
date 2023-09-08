#include "PlayScene.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "../Particle.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
}

void PlayScene::Initialize() {
	ScoreManager::GetInstance()->ResetScore();
	backScreen = std::make_unique<BackScreen>();
	player = std::make_unique<Player>();
	cannon_ = std::make_unique<Cannon>();
	cannon_->SetPlayer(player.get());
	cannon_->Initialize();
	accel = std::make_unique<AccelSpot>(DirectX::XMFLOAT2{ 600,200 }, player.get());
	accel->Initialize();
	gear = std::make_unique<GearSpot>(DirectX::XMFLOAT2{ 1000,500 }, player.get());
	gear->Initialize();
	count=GetNowCount();
}

void PlayScene::Update() {
	player->Update();
	cannon_->Update();
	accel->Update();
	gear->Update();

	backScreen->Update();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::TITLE);
	}

	Particle::Ins()->Update();
}

void PlayScene::Draw() {
	backScreen->Draw();
	accel->Draw();
	gear->Draw();
	cannon_->Draw();
	player->Draw();

	Particle::Ins()->Draw();
	DrawFormatString(640,20,GetColor(255,255,255),"%d",(GetNowCount()-count)/1000);
	ScoreManager::GetInstance()->Draw();
}
