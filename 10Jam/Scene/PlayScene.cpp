#include "PlayScene.h"
#include "SceneManager.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
	delete player;
	delete children1;
	delete children2;
}

void PlayScene::Initialize() {
	player = new Player();
	children1 = new Children(150.0f, 255.0f);
	children2 = new Children(300.0f, 255.0f);
	children3 = new Children(450.0f, 255.0f);
	children4 = new Children(600.0f, 255.0f);
	children5 = new Children(750.0f, 255.0f);
}

void PlayScene::Update() {
	player->Update();
	children1->Update(*player);
	children2->Update(*player);
	children3->Update(*player);
	children4->Update(*player);
	children5->Update(*player);
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::TITLE);
	}
}

void PlayScene::Draw() {
	player->Draw();
	children1->Draw();
	children2->Draw();
	children3->Draw();
	children4->Draw();
	children5->Draw();
}
