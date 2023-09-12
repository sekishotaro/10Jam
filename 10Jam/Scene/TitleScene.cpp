#include "TitleScene.h"
#include "SceneManager.h"

TitleScene::TitleScene() {
}

TitleScene::~TitleScene() {
}

void TitleScene::Initialize() {
	cannon = std::make_unique<Cannon>();
	player = std::make_unique<Player>();
	cannon->SetPlayer(player.get());
	cannon->TitleInitialize();
	backScreen = std::make_unique<BackScreen>();

}

void TitleScene::Update() {
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	player->Update();
	cannon->TitleUpdate();
	if (keys[KEY_INPUT_RETURN] == 1) {
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::PLAY);
	}
}

void TitleScene::Draw() {

	backScreen->Draw();
	cannon->TitleDraw();
	player->Draw();

	DrawFormatString(600,300,GetColor(255,255,255),"タイトルです。エンターでプレイ");
}
