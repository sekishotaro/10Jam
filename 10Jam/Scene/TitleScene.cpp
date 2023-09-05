#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene() {
}

TitleScene::~TitleScene() {
}

void TitleScene::Initialize() {
}

void TitleScene::Update() {
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	if (keys[KEY_INPUT_RETURN] == true) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::PLAY);
	}
}

void TitleScene::Draw() {
}
