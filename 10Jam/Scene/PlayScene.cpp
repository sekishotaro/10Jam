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
}

void PlayScene::Update() {
	player->Update();
	cannon_->Update();
	accel->Update();
	backScreen->Update();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::TITLE);
	}

	Particle::Ins()->Update();
}

void PlayScene::Draw() {
	backScreen->Draw();
	accel->Draw();
	cannon_->Draw();
	player->Draw();

	Particle::Ins()->Draw();

	ScoreManager::GetInstance()->Draw();
}
