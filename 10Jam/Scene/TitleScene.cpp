#include "TitleScene.h"
#include "SceneManager.h"
#include "../Particle.h"
#include "../Children.h"
#include "../Bloom.h"
#include <ScrollManager.h>

TitleScene::TitleScene() {
	ScrollManager::GetInstance()->Reset();
}

TitleScene::~TitleScene() {
}

void TitleScene::Initialize() {
	cannon = std::make_unique<Cannon>();
	player = std::make_unique<Player>();
	player->TitleInitialize();
	cannon->SetPlayer(player.get());
	cannon->TitleInitialize();
	backScreen = std::make_unique<BackScreen>();

}

void TitleScene::Update() {
	// 最新のキーボード情報を取得
	GetHitKeyStateAll(keys);
	player->TitleUpdate();
	cannon->TitleUpdate();
	Particle::Ins()->Update();

	player->playerStop = cannon->deleteChilFlag;
	if (keys[KEY_INPUT_RETURN] == 1) {
		// パーティクルを消す
		Particle::Ins()->Clear();
		Children::End();
		SceneManager::GetInstance()->ChangeScene(SceneManager::SceneName::PLAY);
	}
}



void TitleScene::Draw() {
	// 描画先をmainScreenにする
	SetDrawScreen(Bloom::Ins()->mainScreen);
	ClearDrawScreen();

	backScreen->Draw();
	cannon->Draw();
	player->Draw();

	Particle::Ins()->Draw();

	DrawFormatString(600, 300, GetColor(255, 255, 255), "タイトルです。エンターでプレイ");
	//DrawFormatString(600, 300, GetColor(255, 255, 255), "%.0f,%.0f,",player->GetPos().x, player->GetPos().y);

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// mainScreenの内容を描画する
	DrawGraphF(0, 0, Bloom::Ins()->mainScreen, FALSE);

	// ぼかしたものを描画する
	Bloom::Ins()->UpdateBloomScreen();
	Bloom::Ins()->DrawBloomScreen();


}
