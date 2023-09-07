#include "PlayScene.h"
#include "SceneManager.h"
#include "ScoreManager.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
}

void PlayScene::Initialize() {
	ScoreManager::GetInstance()->ResetScore();
	player = std::make_unique<Player>();
	cannon_ = std::make_unique<Cannon>();
	cannon_->SetPlayer(player.get());
	cannon_->Initialize();
}

void PlayScene::Update() {
	player->Update();
	cannon_->Update();
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::TITLE);
	}
}

void PlayScene::Draw() {
	cannon_->Draw();
	player->Draw();

	ScoreManager::GetInstance()->Draw();
}
