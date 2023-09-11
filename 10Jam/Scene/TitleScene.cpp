#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene() {
}

TitleScene::~TitleScene() {
}

void TitleScene::Initialize() {
}

void TitleScene::Update() {
	backScreen = std::make_unique<BackScreen>();
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	if (keys[KEY_INPUT_RETURN] == 1) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::PLAY);
	}
}

void TitleScene::Draw() {

	backScreen->Draw();

	DrawFormatString(600,300,GetColor(255,255,255),"タイトルです。エンターでプレイ");
}
