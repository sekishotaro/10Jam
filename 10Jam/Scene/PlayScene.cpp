#include "PlayScene.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "../Particle.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
	delete player;
	delete children1;
	delete children2;

	Particle::Ins()->Clear();
}

void PlayScene::Initialize() {
	ScoreManager::GetInstance()->ResetScore();
	player = new Player();
	cannon_ = std::make_unique<Cannon>();
	cannon_->SetPlayer(player);
	children1 = new Children({150.0f, 255.0f},player);
	children2 = new Children({300.0f, 255.0f},player);
	children3 = new Children({450.0f, 255.0f},player);
	children4 = new Children({600.0f, 255.0f},player);
	children5 = new Children({750.0f, 255.0f},player);
}

void PlayScene::Update() {
	player->Update();
	cannon_->Update();
	children1->Update();
	children2->Update();
	children3->Update();
	children4->Update();
	children5->Update();
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::TITLE);
	}

	Particle::Ins()->Update();
}

void PlayScene::Draw() {
	cannon_->Draw();
	player->Draw();
	children1->Draw();
	children2->Draw();
	children3->Draw();
	children4->Draw();
	children5->Draw();


	Particle::Ins()->Draw();

	ScoreManager::GetInstance()->Draw();
}
