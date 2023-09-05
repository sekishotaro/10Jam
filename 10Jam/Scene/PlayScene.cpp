#include "PlayScene.h"
#include "SceneManager.h"

PlayScene::PlayScene() {
}

PlayScene::~PlayScene() {
	delete player;
	delete children1;
}

void PlayScene::Initialize() {
	player = new Player();
	children1 = new Children(255.0f,255.0f);

}

void PlayScene::Update() {
	player->Update();
	//children1->Update();

	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	if (keys[KEY_INPUT_SPACE] == true) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::TITLE);
	}
}

void PlayScene::Draw() {
	player->Draw();
	children1->Draw();

}
