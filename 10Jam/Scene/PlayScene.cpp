#include "PlayScene.h"
#include "SceneManager.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
	delete player;
}

void PlayScene::Initialize() {
	player = new Player();
	cannon_ = std::make_unique<Cannon>();
	cannon_->SetPlayer(player);
}

void PlayScene::Update() {
	player->Update();
	cannon_->Update();

	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::TITLE);
	}
}

void PlayScene::Draw() {
	cannon_->Draw();
	player->Draw();
}
